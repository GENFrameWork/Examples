# Fase 6 — Min hit-target checklist

Fecha: 2026-09-21
Design: 1440×900 · `minHitSize=44` design px · paint AABB sin cambios

## Política

| Caso | Paint | Hit (UIScale activo) |
|------|-------|----------------------|
| `disk_prev_btn` / `disk_next_btn` | 40×40 | ≥ 44×44 centrado |
| Unit test paint 24×24 | 24×24 | ≥ 44×44 |
| Layout XML-only (UI_Options) | — | sin expand (legacy) |

Ypos bottom-anchored. Expand: `mid = y − height/2` fijo.

## Hit-test (scale 0.75)

Paint `disk_prev`: (662,766)–(702,806). Expand pad=2 → hit (660,764)–(704,808).

| # | Acción | Design px | Esperado | Resultado |
|---|--------|-----------|----------|-----------|
| 1 | Nav Disco | (105, 318) | Sección Disco | **PASS** `P6_scale075_disco.png` |
| 2 | Clic **fuera** paint, **dentro** hit (margen izq.) | (661, 786) | Cicla disco (mismo efecto que centro) | **PASS** → `4/4` Backup 2 (`P6_scale075_disk_margin_hit.png`) |
| 3 | Clic centro `disk_next` | (966, 786) | Contador avanza | **PASS** (script) |
| 4 | Visual | — | Botones se ven 40×40 (no crecen al paint) | **PASS** (paint idéntico; solo hit expandido) |

## Capturas

| Archivo | Contenido |
|---------|-----------|
| `P6_scale075_disco.png` | Disco a scale 0.75 (paint idéntico a P3) |
| `P6_scale075_disk_margin_hit.png` | Tras clic en margen expandido |
| `P6_minhit_checklist.md` | este archivo |

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\capture_p6_minhit.ps1
```
