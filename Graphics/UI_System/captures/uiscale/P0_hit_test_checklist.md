# Fase 0 — Hit-test checklist (UI_System)

Fecha: 2026-09-21  
Canvas: 1440×900 (client = design)  
Método: clics sintéticos en centros de botones root-level + captura visual

Convención ypos XML: anclaje inferior → `top = ypos − height`.

## Sidebar (`nav-*-btn`)

| # | Control | XML | AABB (x,y,w,h) → centro | Esperado | Resultado |
|---|---------|-----|-------------------------|----------|-----------|
| 1 | Resumen | `nav-resumen-btn` | (0,70,210,48) → (105,94) | Highlight Resumen; slot fecha/hora | **PASS** (`P0_resumen.png`) |
| 2 | CPU | `nav-cpu-btn` | (0,126,210,48) → (105,150) | Highlight CPU; chart histórico CPU | **PASS** (`P0_cpu.png`) |
| 3 | Memoria | `nav-memoria-btn` | (0,182,210,48) → (105,206) | Highlight Memoria; chart histórico RAM | **PASS** (`P0_memoria.png`) |
| 4 | Disco | `nav-disco-btn` | (0,294,210,48) → (105,318) | Highlight Disco; barras por volumen | **PASS** (`P0_disco.png`) |

## Card Disco — pager (`disk_*_btn`)

| # | Control | XML | AABB → centro | Esperado | Resultado |
|---|---------|-----|---------------|----------|-----------|
| 5 | Disco next | `disk_next_btn` | (946,766,40,40) → (966,786) | Contador **2 / 4**; volumen D: | **PASS** (`P0_disco_page2.png`) |
| 6 | Disco prev | `disk_prev_btn` | (662,766,40,40) → (682,786) | Contador **1 / 4**; volumen C: | **PASS** (`P0_disco_page1.png`) |

## Resumen

| Área | PASS | FAIL |
|------|------|------|
| Sidebar (4) | 4 | 0 |
| Card pager (2) | 2 | 0 |
| **Total** | **6** | **0** |

Baseline hit-test congelado para comparar en fases con `uiScale ≠ 1`.
