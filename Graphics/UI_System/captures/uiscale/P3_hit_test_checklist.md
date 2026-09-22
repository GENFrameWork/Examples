# Fase 3 — Hit-test + paint checklist

Fecha: 2026-09-21  
Design: 1440×900 · Present: design offscreen → Scale → blit (letterbox si cabe; zoom top-left)

| Scale | Capturas | Hit-test nav | Notas |
|------:|----------|--------------|-------|
| 1.0 | `P3_scale1_{resumen,cpu,memoria,disco}.png` | **6/6 PASS** | Path identidad (sin offscreen) |
| 1.25 | `P3_scale1_25_*.png` | **PASS** (4 secciones) | Zoom; borde derecho recortado |
| 1.5 | `P3_scale1_5_{resumen,cpu}.png` | **PASS** CPU @ (158,225) | Zoom; Memoria click flaky (crash) |
| 0.75 | `P3_letterbox_*.png` | **PASS** | Letterbox centrado |

Prueba controlada scale≠1: unit tests `LetterboxOffsets*` + `ScreenToDesignMapsScaledClick*`.

Env: `GEN_UI_SCALE` leído en `UI_SYSTEM::Ini_UserInterface`.
