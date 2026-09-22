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

Salida (esta sesión): `Build/Android/arm64-v8a/ui_system.apk` (+ `ui_system-aligned.apk`). Link OK; `UI_System.cpp` + APK packaging OK.

## Checklist dispositivo / emulador

Sin dispositivo adb en esta sesión (`adb devices` vacío). Al tener device/emulator:

1. `adb install -r <apk>`
2. Abrir UI_System; logcat debe mostrar `[UI_System] Android UIScale=1.0 design=1440x900`
3. Rotar / config change → log `[ANDROID] OnConfigurationChanged: keep design 1440x900` (sin resize a nativo)
4. Captura landscape + portrait → `PP_android_landscape.png` / `PP_android_portrait.png`
5. Verificar: dashboard legible letterboxed; touch sobre cards/nav acierta (no offset)

## Notas

- `GEN_UI_SCALE` env es portable (también Android) pero el path Android ignora overrides de scale Present.
- Track B (`@media`) sigue diferido; Android no reflowa XML — solo letterbox.
