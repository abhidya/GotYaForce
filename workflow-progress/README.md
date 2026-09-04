# Port workflow: IDLE

*Generated 2026-09-04T00:04:24.402438Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `IDLE` (idle) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 104/1396 settled (1 verified, 103 staged [compile_only, UNVERIFIED], 2 unknown tier) |
| **Retries outstanding** | 147 |
| **Untouched** | 1133 |
| **Last transition** | 2026-09-04T00:04:24.402438Z |
| **Last green** | 2026-08-26T07:34:28.953704Z (`auto-c0053-013`) |
| **Last product commit** | `218911ab5e2455c447e5beec8efe9e95e7c8f2ec` |
| **Active model** | `-` @ - ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | stopped |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-09-04T00:04:24.402438Z | `-` | leased-out | machine | 0 | GPU leased to omr-sweep (priority 1); slot drained and free. |
| 2026-09-04T00:03:16.385323Z | `-` | provider_paused | machine | 0 | Provider paused; model released until it answers. |
| 2026-08-30T06:32:04.169944Z | `-` | leased-out | machine | 0 | GPU leased to omr-sweep (priority 1); slot drained and free. |
| 2026-08-30T06:31:12.438687Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-30T06:30:06.668411Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-30T06:28:39.724335Z | `-` | leased-out | machine | 0 | GPU leased to omr-sweep (priority 1); slot drained and free. |
| 2026-08-30T06:28:18.673772Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-30T05:30:20.332652Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-29T22:34:15.787776Z | `-` | leased-out | machine | 0 | GPU leased to omr-sweep (priority 1); slot drained and free. |
| 2026-08-29T22:33:54.218156Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-29T22:33:30.104744Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-29T22:33:09.531529Z | `auto-c0025-002` | deferred | manual-revoke | 1 | verdict revoked and requeued: corpus correction landed on main as 747bc061 (chunk_0025.c:712/717/734/740): 0x8 |
| 2026-08-29T21:29:50.608532Z | `-` | leased-out | machine | 0 | Rehydrated an active GPU lease to omr-sweep across a restart; the slot is the lessee's, not the port's to reap |
| 2026-08-29T21:24:22.038146Z | `-` | leased-out | machine | 0 | GPU leased to omr-sweep (priority 1); slot drained and free. |
| 2026-08-29T21:22:04.190118Z | `auto-c0030-014` | deferred | compile-fix | 4 | provider unavailable, unit not blamed: Custom API stream error: Lost connection to the model server. It may ha |
| 2026-08-29T21:18:27.295999Z | `-` | yielding | machine | 0 | Yielding the GPU to omr-sweep at the next port unit boundary. |
| 2026-08-29T21:02:12.551555Z | `auto-c0030-014` | deferred | assembly | 4 | interrupted before a verdict; requeued |
| 2026-08-29T21:02:11.857941Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-29T20:50:47.435309Z | `-` | blocked | machine | 0 | Blocked: serving slot not ready: unsloth/Qwen3.8-27B-GGUF not ready at context>=60000 within 900s (resident=D: |
| 2026-08-29T20:05:02.520921Z | `-` | blocked | machine | 0 | Blocked: serving slot not ready: load request failed: HTTPConnectionPool(host='127.0.0.1', port=8888): Read ti |
| 2026-08-29T19:38:40.784679Z | `-` | blocked | machine | 0 | Blocked: serving slot not ready: unsloth/Qwen3.8-27B-GGUF not ready at context>=60000 within 900s (resident=D: |
| 2026-08-29T19:12:21.844950Z | `-` | blocked | machine | 0 | Blocked: chat contract preflight failed: HTTPConnectionPool(host='127.0.0.1', port=8888): Read timed out. (rea |
| 2026-08-29T18:57:10.990585Z | `-` | leased-out | machine | 0 | GPU leased to omr-sweep (priority 2); slot drained and free. |
| 2026-08-29T18:51:22.616907Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-29T18:50:54.130452Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-29T18:50:28.717996Z | `-` | blocked | machine | 0 | Blocked: chat contract preflight failed: HTTPConnectionPool(host='127.0.0.1', port=8888): Read timed out. (rea |
| 2026-08-29T18:44:53.323412Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-29T15:19:19.952253Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-26T17:00:28.169537Z | `-` | leased-out | machine | 0 | GPU leased to omr-sweep (priority 1); slot drained and free. |
| 2026-08-26T17:00:06.372126Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-26T16:45:59.680375Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-26T07:54:21.791283Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-26T07:34:39.759624Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-26T07:34:28.953704Z | `auto-c0053-013` | staged | commit | 6 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T07:03:31.057949Z | `auto-c0054-005` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-26T07:03:29.192023Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-26T07:00:24.960699Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-26T06:59:22.634473Z | `auto-c0001-005` | deferred | manual-revoke | 1 | verdict revoked and requeued: behaviorally wrong vs console: 200/200 dolphin-trace captures diverge on w348 (r |
| 2026-08-26T06:59:02.341374Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-26T06:47:47.000880Z | `auto-c0054-004` | gate_failed | assembly | 1 | assembly gate link failed before promotion: -1;       \|                                                  ~~ ~ |
| 2026-08-26T06:26:05.318522Z | `auto-c0054-003` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:22:13.443847Z | `auto-c0054-002` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:18:06.449254Z | `auto-c0054-001` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:14:03.174828Z | `auto-c0054-000` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:09:41.009476Z | `auto-c0053-018` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:05:10.220254Z | `auto-c0053-017` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:00:09.601311Z | `auto-c0053-016` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_01ba750_ declared void but their results are assigned; no header edit ca |
| 2026-08-26T06:00:06.178042Z | `auto-c0053-008` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_01b7894_ declared void but their results are assigned; no header edit ca |
| 2026-08-26T06:00:02.714102Z | `auto-c0053-007` | gate_failed | wasm-link | 1 | not linked: .\gnt4_shim.h:188:80: error: unterminated /* comment unit.c:156:86: error: subscripted value is no |
| 2026-08-26T04:33:53.400740Z | `auto-c0053-006` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: canonical_header_ambiguous: auto-c0053-006 declares zz_008 |
