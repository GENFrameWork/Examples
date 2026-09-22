# UIScale — capturas de validación (UI_System)

Baseline y regresiones visuales del roadmap Opción A (`GEN/UserInterface/GEN_UI_Scale_Roadmap.md`).

## Resolución baseline (Fase 0)

| Medida | Valor |
|--------|-------|
| Design canvas (`Ini_Graphics`) | **1440 × 900** |
| GetWindowRect / GetClientRect al arrancar | **1440 × 900** (borderless; coincide) |
| Exe | `CMake/Build/Windows/intel64/ui_system.exe` |

Detalle runtime: `P0_window_metrics.md` (regenerado por el script de captura).

## Reproducir Fase 0

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p0_baseline.ps1
```

El script lanza `ui_system`, captura secciones vía `PrintWindow` (fallback `CopyFromScreen`) y hace clic en centros de hit-targets.

## Archivos P0

| Archivo | Contenido |
|---------|-----------|
| `P0_resumen.png` | Sección Resumen (default) |
| `P0_cpu.png` | Nav CPU → historial CPU en slot inferior izquierdo |
| `P0_memoria.png` | Nav Memoria → historial RAM |
| `P0_disco.png` | Nav Disco → barras por volumen |
| `P0_disco_page2.png` | Tras `disk_next` → página **2 / 4** |
| `P0_disco_page1.png` | Tras `disk_prev` → vuelve a **1 / 4** |
| `P0_hit_test_checklist.md` | Controles y PASS/FAIL |

## Fase 1 — scale = 1.0

API viva en `UI_LAYOUT` (`designWidth`/`designHeight`/`uiScale`). Opt-in por stylesheet.
UI_System fija design **1440×900** + `uiScale=1.0` (debe verse igual que P0).

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p1_scale1.ps1
```

| Archivo | Contenido |
|---------|-----------|
| `P1_scale1_resumen.png` … `disco*.png` | Mismas secciones que P0 |
| `P1_scale1_window_metrics.md` | Runtime 1440×900 |

## Fase 2 — input screen→design (scale = 1.0)

`ScreenToDesign` / `DesignToScreen` + `MapScreenToDesign` antes de `IsWithin`. AABB siguen en design px.
Con scale 1.0 la conversión es identidad → visual/hit-test = P0/P1.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p2_scale1.ps1
```

| Archivo | Contenido |
|---------|-----------|
| `P2_scale1_*.png` | Mismas secciones; nav + disk pager PASS |

## Fase 3 — paint scale + letterbox

Design offscreen + `UIScale_Present`. Env `GEN_UI_SCALE` (UI_System).

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p3_scale.ps1 -Scale 1.0 -Prefix P3_scale1
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p3_scale.ps1 -Scale 1.25 -Prefix P3_scale125
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p3_scale.ps1 -Scale 1.5 -Prefix P3_scale15
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p3_scale.ps1 -Scale 0.75 -Prefix P3_letterbox
```

| Archivo | Contenido |
|---------|-----------|
| `P3_scale1_*.png` | scale 1.0 identity |
| `P3_scale1_25_cpu.png` / `P3_scale125_*` | zoom 1.25 |
| `P3_scale1_5_cpu.png` / `P3_scale15_*` | zoom 1.5 |
| `P3_letterbox_*.png` | scale 0.75 + letterbox |
| `P3_hit_test_checklist.md` | PASS/FAIL |

## Fase 4 — zoom runtime

`Layouts_SetUIScale` + teclas numpad `+`/`−` (y `-` principal). Persistencia `[general] uiscale`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p4_zoom.ps1
```

| Archivo | Contenido |
|---------|-----------|
| `P4_before_scale1.png` | scale 1.0 |
| `P4_after_scale15.png` | tras dos `+` → 1.5 |
| `P4_after_scale125.png` | tras un `−` → 1.25 |
| `P4_zoom_checklist.md` | checklist |

## Fase 5 — autofit ventana

`scale = min(sw/dw, sh/dh)`. Ini `uiscale_autofit=si`. Resize → recalc.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p5_autofit.ps1
```

| Archivo | Contenido |
|---------|-----------|
| `P5_fit_1440x900.png` | fit ≈ 1.0 |
| `P5_fit_720x450.png` | fit ≈ 0.5 |
| `P5_fit_1600x900.png` | fit ≈ 1.0 + pillarbox |
| `P5_autofit_checklist.md` | checklist |

## Fase 6 — min hit-target

`minHitSize=44` design px. Expande solo AABB de hit en `PreSelectElement`; paint sin cambios.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p6_minhit.ps1
```

| Archivo | Contenido |
|---------|-----------|
| `P6_scale075_disco.png` | Disco a scale 0.75 |
| `P6_scale075_disk_margin_hit.png` | Clic en margen expandido (fuera paint) |
| `P6_minhit_checklist.md` | checklist |

## Coordenadas de clic (design / client px)

Ypos XML bottom-anchored: `top = ypos − height`, centro = `top + height/2`.

| Target | Elemento XML | Centro (cx, cy) |
|--------|--------------|-----------------|
| Resumen | `nav-resumen-btn` | (105, 94) |
| CPU | `nav-cpu-btn` | (105, 150) |
| Memoria | `nav-memoria-btn` | (105, 206) |
| Disco | `nav-disco-btn` | (105, 318) |
| Disco prev | `disk_prev_btn` | (682, 786) |
| Disco next | `disk_next_btn` | (966, 786) |

## Criterio de salida Fase 0

- [x] Resolución documentada
- [x] Capturas `P0_*` (Resumen / CPU / Memoria / Disco)
- [x] Checklist hit-test
- [x] `UnitTests_UserInterface` 276 PASS
