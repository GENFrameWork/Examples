# Track P — Android 5.3 (UIScale + design canvas)

## Contrato

| Capa | Responsabilidad |
|------|-----------------|
| Design canvas | Fijo 1440×900 (`SetDesignSize` + Ini graphics) |
| Fit visual | GLES letterbox (`GRPANDROIDBlitGLES`) |
| Touch | `MapWindowToCanvas` (native → design) |
| UIScale Present | **1.0** (identidad; no doble-escalar) |

## Código

- `UI_System.cpp` `#ifdef ANDROID`: fuerza `SetUIScaleForFit(1.0)` + `UIScale_PrepareLayout`; ignora autofit Windows-style.
- `UI_System.cpp` `CHANGESIZE` Android: reafirma design size + scale 1.0 (no `Layouts_ApplyFitUIScale` contra framebuffer nativo).
- `MainProcANDROID.cpp` `OnConfigurationChanged` + `GRP_OPENGL_ACTIVE`: **no** `UpdateSize(native)`; log + `PostEvent(CHANGESIZE)`.

## Build

```text
cd Examples/Graphics/UI_System/CMake
cmake --preset 9-android-arm64
cmake --build --preset 9-android-arm64
```

Salida: `Build/Android/arm64-v8a/ui_system.apk`.

## Smoke dispositivo / emulador — ✅ cerrado (2026-09-22)

**Entorno:** AVD `GEN_UI_Smoke_API34` (Android 14, `google_apis` x86_64, ABI list incluye `arm64-v8a`).  
**APK:** `com.gen.ui_system` / `android.app.NativeActivity` (`screenOrientation=landscape`).  
**Nota:** no hay teléfono ADB usable en la sesión (Xiaomi 14T Pro visible en MTP sin interfaz ADB operativa).

| Check | Resultado |
|-------|-----------|
| `adb install -r ui_system.apk` | Success |
| Launch + dashboard visible | ✅ capturas |
| Design canvas fijo | ✅ `GEN_BLIT SIZES canvas=1440x900 screen=1440x900` |
| Fit = surface nativa | ✅ `surface=2400x1022` / `surface=1600x852` |
| Touch (sidebar + card) | ✅ proceso sigue vivo |
| Portrait | N/A (manifest landscape); 2.ª captura = landscape estrecho |

### Capturas

- `PP_android_landscape.png` — wm 2400×1080 → surface 2400×1022
- `PP_android_landscape_narrow.png` — wm 1600×900 → surface 1600×852  
  (`PP_android_portrait.png` = copia del narrow por naming del checklist)
- `PP_android_log_excerpt.txt` — líneas `GEN_BLIT SIZES`

### Evidencia clave

```text
SIZES canvas=1440x900 screen=1440x900 surface=2400x1022 texture=1440x900
SIZES canvas=1440x900 screen=1440x900 surface=1600x852  texture=1440x900
```

Canvas de autoría no se reescribe al tamaño nativo; GLES letterbox adapta.

## Notas

- `GEN_UI_SCALE` env es portable pero el path Android ignora overrides de scale Present.
- Track B (`@media`) sigue diferido; Android no reflowa XML — solo letterbox.
- Re-smoke físico: activar depuración USB en el Xiaomi y repetir `adb install` + capturas.
