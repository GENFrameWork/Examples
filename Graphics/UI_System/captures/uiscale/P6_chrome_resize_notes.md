# Video review 2026-09-21 — Window Chrome maximize / resize

Source: `Desktop/2026-09-21 21-55-44.mp4`

## Issues observed

1. **Black window while dragging resize** — `UpdateSize` recreates empty canvases; main loop blocked in modal drag; `UpdateViewports` presented black.
2. **Ini Save on every CHANGESIZE** — stalled interactive resize.
3. **Maximize button no-op when already max** — `Maximize(true)` returned early; no restore path for SetWindowPos growth.
4. **Asymmetric letterbox** during transitions — stale present offsets.

## Fixes

- CHANGESIZE: `ApplyFit` or `PrepareLayout` + immediate `Update()`; no `Save()`.
- Chrome maximize: toggle grow ↔ restore; remember pre-maximize rect.
- `UIScale_Present`: recompute transform every frame; letterbox uses layout bg color.
