# Fase 2 — Hit-test checklist (scale = 1.0)

Fecha: 2026-09-21  
Canvas: 1440×900 · uiScale: 1.0 (ScreenToDesign = identidad)  
Método: capturas `P2_scale1_*` vía `capture_p2_scale1.ps1`

| # | Control | Centro design | Resultado |
|---|---------|---------------|-----------|
| 1 | Resumen (default) | (105, 94) | **PASS** `P2_scale1_resumen.png` |
| 2 | CPU | (105, 150) | **PASS** `P2_scale1_cpu.png` |
| 3 | Memoria | (105, 206) | **PASS** `P2_scale1_memoria.png` |
| 4 | Disco | (105, 318) | **PASS** `P2_scale1_disco.png` |
| 5 | disk_next | (966, 786) | **PASS** `P2_scale1_disco_page2.png` |
| 6 | disk_prev | (682, 786) | **PASS** `P2_scale1_disco_page1.png` |

Prueba controlada scale≠1: unit test `ScreenToDesignMapsScaledClickOntoDesignHitBox` (scale 1.5).

**Total: 6/6 PASS** (+ math/AABB unit tests).
