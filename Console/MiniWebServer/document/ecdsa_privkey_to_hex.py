#!/usr/bin/env python3
# -------------------------------------------------------------------------------------------------------------------
#
# ecdsa_privkey_to_hex.py
#
# Convierte una clave privada EC en formato PEM "SEC1" (la que genera
# `openssl ecparam -genkey`, con cabecera "-----BEGIN EC PRIVATE KEY-----")
# al formato que espera APPFLOWWEBSERVER::Ini_LoadTLSPrivateKey_ECDSA():
# un fichero de texto con UNA sola linea en hexadecimal, con el escalar
# privado D.
#
# No depende de ninguna libreria externa (solo la libreria estandar de
# Python), asi que no hace falta tener instalado "cryptography" ni nada
# parecido.
#
# Uso:
#   python3 ecdsa_privkey_to_hex.py <clave_privada.pem> <salida.hex>
#
# Ejemplo:
#   python3 ecdsa_privkey_to_hex.py ecdsa_p256_key.pem ecdsa_p256_priv.hex
#
# -------------------------------------------------------------------------------------------------------------------

import base64
import re
import sys


def der_read_tlv(data, offset):
    """Lee un TLV (Tag-Length-Value) DER a partir de 'offset'. Devuelve (tag, value_bytes, nuevo_offset)."""

    tag = data[offset]
    offset += 1

    length_byte = data[offset]
    offset += 1

    if length_byte & 0x80:
        # Forma larga: el byte de longitud indica cuantos bytes siguen componen la longitud real.
        num_len_bytes = length_byte & 0x7F
        length = int.from_bytes(data[offset:offset + num_len_bytes], "big")
        offset += num_len_bytes
    else:
        # Forma corta: el propio byte ES la longitud.
        length = length_byte

    value = data[offset:offset + length]
    offset += length

    return tag, value, offset


def extract_ec_private_scalar_hex(pem_path):
    """Extrae el escalar privado D (el campo 'privateKey' de la estructura SEC1 ECPrivateKey) y lo
    devuelve como una cadena hexadecimal, sin separadores ni saltos de linea."""

    with open(pem_path, "r") as f:
        pem_text = f.read()

    match = re.search(
        r"-----BEGIN EC PRIVATE KEY-----(.*?)-----END EC PRIVATE KEY-----",
        pem_text,
        re.S,
    )

    if not match:
        raise ValueError(
            "No se ha encontrado un bloque 'EC PRIVATE KEY' (SEC1) en '%s'.\n"
            "Si el fichero tiene la cabecera '-----BEGIN PRIVATE KEY-----' (formato PKCS#8) en vez de\n"
            "'-----BEGIN EC PRIVATE KEY-----', conviertelo primero con:\n"
            "    openssl ec -in %s -out %s_sec1.pem" % (pem_path, pem_path, pem_path)
        )

    der = base64.b64decode(match.group(1))

    # ECPrivateKey ::= SEQUENCE { version INTEGER, privateKey OCTET STRING, parameters [0] ..., publicKey [1] ... }

    tag, seq_value, _ = der_read_tlv(der, 0)
    if tag != 0x30:
        raise ValueError("Formato DER inesperado en '%s': se esperaba una SEQUENCE al principio." % pem_path)

    offset = 0

    tag, _version_bytes, offset = der_read_tlv(seq_value, offset)
    if tag != 0x02:
        raise ValueError("Formato DER inesperado en '%s': falta el INTEGER de version." % pem_path)

    tag, privatekey_bytes, offset = der_read_tlv(seq_value, offset)
    if tag != 0x04:
        raise ValueError("Formato DER inesperado en '%s': falta el OCTET STRING de la clave privada." % pem_path)

    return privatekey_bytes.hex()


def main():
    if len(sys.argv) != 3:
        sys.stderr.write("Uso: python3 %s <clave_privada.pem> <salida.hex>\n" % sys.argv[0])
        sys.exit(1)

    pem_path = sys.argv[1]
    out_path = sys.argv[2]

    hexvalue = extract_ec_private_scalar_hex(pem_path)

    with open(out_path, "w") as f:
        f.write(hexvalue + "\n")

    print("OK: escalar privado (%d bytes) escrito en '%s'." % (len(hexvalue) // 2, out_path))
    print("Contenido: %s" % hexvalue)


if __name__ == "__main__":
    main()