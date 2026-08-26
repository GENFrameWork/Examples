# Soporte ECDSA para firma TLS del servidor (DIOSTREAMTLS / DIOWEBSERVER)

## Resumen

Hasta ahora `DIOSTREAMTLS`/`DIOWEBSERVER` solo podían firmar el handshake TLS 1.3 del lado servidor con RSA. La capa de *negociación* de firma (`DIOSTREAMTLS13HANDSHAKESERVER::SignatureScheme_Select()`, `DIOSTREAMTLSSIGNATURE::IsSupported()`/`Verify()`) ya era genérica y sabía manejar ECDSA (incluso podía verificar firmas ECDSA como cliente). Lo que faltaba era la firma del lado servidor: `CIPHERECDSA` no tenía `Sign()`, y la carga de credenciales solo aceptaba claves RSA.

Este documento resume la implementación añadida y cómo generar y comprobar credenciales ECDSA para probarla.

## Ficheros modificados

| Fichero | Cambio |
|---|---|
| `GEN/Cipher/CipherECDSA.h` / `.cpp` | Nuevo `CIPHERECDSA::Sign()` (firma ECDSA estándar sobre P-256/P-384/P-521, salida DER `ECDSA-Sig-Value`). `SetKey()` extendido para aceptar también la clave privada, con comprobación de integridad opcional frente a la clave pública. |
| `GEN/DataIO/Streams/TLS/DIOStreamTLSConfig.cpp` | `SetLocalPrivateKey()` generalizado: acepta tanto `CIPHERKEYTYPE_RSA_PRIVATE` como `CIPHERKEYTYPE_ECDSA_SECP{256,384,521}R1_PRIVATE`. |
| `GEN/DataIO/Streams/TLS/DIOStreamTLSSignature.h` / `.cpp` | `Sign()` generalizado: además de RSA-PSS, firma con `CIPHERECDSA` para los tres esquemas ECDSA soportados. |
| `GEN/AppFlow/APPFlowWebServer.h` / `.cpp` | `Ini_LoadTLSCredentials()` decodifica primero el certificado (`CIPHERCERTIFICATEX509::Decode()`) para saber qué tipo de clave privada espera, y carga el fichero de clave privada en el formato correspondiente (RSA: 3 líneas hex; ECDSA: 1 línea hex, ver `Ini_LoadTLSPrivateKey_ECDSA()`). `Ini_BuildTLSConfig()` ofrece ahora los 3 esquemas de firma ECDSA además del RSA existente. |

Curvas soportadas para firma de servidor: **P-256, P-384, P-521** (las que `CIPHERECDSA` implementa a nivel de aritmética de curva). El intercambio de claves (ECDHE vía X25519) es un mecanismo aparte y no se ha visto afectado por este cambio.

## Cómo generar claves y certificados de prueba

### 1. Clave privada y certificado autofirmado (openssl)

Para cada curva (sustituye `prime256v1` por `secp384r1` o `secp521r1` según el caso):

```bash
openssl ecparam -name prime256v1 -genkey -noout -out ecdsa_p256_key.pem
openssl req -new -x509 -key ecdsa_p256_key.pem -out ecdsa_p256_cert.pem -days 365 -subj "/CN=localhost"
```

### 2. Convertir la clave privada al formato que espera el servidor

El código espera un fichero de texto plano con **una sola línea en hexadecimal**: el escalar privado D. Se convierte con el script `ecdsa_privkey_to_hex.py` (sin dependencias externas, solo Python 3 estándar — parsea a mano la estructura DER `ECPrivateKey` del PEM SEC1):

```bash
python3 ecdsa_privkey_to_hex.py ecdsa_p256_key.pem ecdsa_p256_priv.hex
```

Si el PEM tiene la cabecera `-----BEGIN PRIVATE KEY-----` (PKCS#8) en vez de `-----BEGIN EC PRIVATE KEY-----` (SEC1), el script lo detecta y explica cómo convertirlo primero con `openssl ec -in ... -out ..._sec1.pem`.

Verificado generando las tres curvas y comparando byte a byte con la salida de `openssl ec -text -noout`: coincide exactamente (32 / 48 / 66 bytes para P-256 / P-384 / P-521).

### 3. Certificado en DER "en crudo"

El certificado se carga tal cual (bytes DER), sin ninguna transformación adicional:

```bash
openssl x509 -in ecdsa_p256_cert.pem -outform DER -out ecdsa_p256_cert.der
```

### 4. Apuntar el `.ini` del servidor a los ficheros generados

```ini
[webserver]
istls            = si
path_privatekey  = /ruta/a/ecdsa_p256_priv.hex
path_certificate = /ruta/a/ecdsa_p256_cert.der
```

Repetir los pasos 1-3 con `secp384r1` / `secp521r1` para probar las otras dos curvas.

## Cómo se comprueba

### A. Handshake TLS 1.3 con `openssl s_client`

Fuerza el esquema de firma de la curva a probar para confirmar que el servidor firma realmente con `CIPHERECDSA::Sign()` (y no cae en RSA):

```bash
openssl s_client -connect localhost:90 -tls1_3 -sigalgs ecdsa_secp256r1_sha256 -groups X25519 -showcerts
```

(sustituir `ecdsa_secp256r1_sha256` por `ecdsa_secp384r1_sha384` / `ecdsa_secp521r1_sha512` según la curva).

Qué mirar en la salida:

- `Peer signature type: ecdsa_secp*` — confirma que el servidor negoció y firmó con ECDSA, no con RSA.
- `New, TLSv1.3, Cipher is ...` — el handshake completo (intercambio de claves + autenticación del servidor) terminó con éxito.
- `Verify return code: 18 (self-signed certificate)` — **esperado y benigno**: solo indica que el certificado es autofirmado y no está en la cadena de confianza del sistema, igual que pasaría con un certificado RSA autofirmado. Un fallo real de la firma (el caso que de verdad preocupaba) se manifestaría como un error durante el propio handshake (p.ej. `decrypt error` / `bad signature`), no como un aviso de verificación de cadena tras completarlo con éxito.

**Resultado de las pruebas realizadas** (2026-08-26): las tres curvas verificadas con éxito.

| Curva | `Peer signature type` | `Server public key` | Handshake |
|---|---|---|---|
| P-256 | `ecdsa_secp256r1_sha256` | 256 bit | OK, `TLS_AES_128_GCM_SHA256` |
| P-384 | `ecdsa_secp384r1_sha384` | 384 bit | OK, `TLS_AES_128_GCM_SHA256` |
| P-521 | `ecdsa_secp521r1_sha512` | 521 bit | OK, `TLS_AES_128_GCM_SHA256` |

### B. Prueba de extremo a extremo (navegador + WebSocket)

Dado el historial previo de este proyecto (bug de concurrencia en WebSocket sobre TLS, ya corregido), la prueba definitiva es repetir el flujo completo con un certificado ECDSA activo:

1. Navegar a `https://localhost:90` con el certificado ECDSA configurado; aceptar la excepción de seguridad del certificado autofirmado.
2. Pulsar "Run WebSocket" y confirmar que la secuencia completa (conexión → hello → cierre) funciona igual que con RSA.

*(Pendiente de confirmación por el usuario en el entorno real.)*

### C. Caso negativo opcional

Para confirmar que la comprobación de integridad de `CIPHERECDSA::SetKey()` funciona, se puede mezclar deliberadamente una clave privada de una curva con el certificado de otra (p.ej. clave P-384 con certificado P-256): el arranque del servidor debería fallar limpiamente en `Ini_LoadTLSCredentials()` / `SetLocalPrivateKey()`, sin arrancar a medias.
