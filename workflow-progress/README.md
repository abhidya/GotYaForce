# Port workflow: IDLE

*Generated 2026-08-21T07:11:40.555467Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `IDLE` (idle) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 27/1396 settled (3 green, 24 staged) |
| **Retries outstanding** | 1 |
| **Untouched** | 1364 |
| **Last transition** | 2026-08-21T07:11:40.555467Z |
| **Last green** | 2026-08-21T05:37:17.022664Z (`auto-c0035-006`) |
| **Last product commit** | `5f124e6c2c27b51e33707835954aa1138a56197e` |
| **Current model** | `unsloth/Qwen3.8-27B-GGUF` @ ? ctx |
| **Driver** | stopped |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-21T07:11:40.555467Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T07:04:30.565961Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T06:59:22.879546Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 262144 ctx. |
| 2026-08-21T06:59:22.917050Z | `auto-c0029-002` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-21T06:36:15.218821Z | `-` | blocked | machine | 0 | Blocked: serving slot not ready: load request failed: 409 Client Error: Conflict for url: http://127.0.0.1:888 |
| 2026-08-21T06:32:16.292260Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T06:31:32.810041Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T06:31:14.210535Z | `-` | blocked | machine | 0 | Blocked: chat contract preflight failed: {"error":{"message":"Lost connection to the model server. It may have |
| 2026-08-21T06:30:05.278129Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T06:19:41.497528Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T06:18:39.114382Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 262144 ctx. |
| 2026-08-21T06:18:39.137531Z | `auto-c0029-001` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-21T06:17:50.709687Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T06:11:19.918797Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T06:03:21.957050Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 262144 ctx. |
| 2026-08-21T06:03:22.023149Z | `auto-c0029-000` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-21T06:02:29.449906Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T06:02:17.484599Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T06:01:37.664052Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T05:37:17.022664Z | `auto-c0035-006` | staged | commit | 3 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T05:36:29.101246Z | `auto-c0034-018` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T05:36:19.438496Z | `auto-c0035-002` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T05:36:11.624972Z | `auto-c0028-018` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-21T05:36:11.633601Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 262144 ctx. |
| 2026-08-21T05:35:19.940452Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T05:32:46.855768Z | `auto-c0035-006` | deferred | d5-migrate | 2 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 5 |
| 2026-08-21T05:32:44.108102Z | `auto-c0035-002` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 3 |
| 2026-08-21T05:32:41.518455Z | `auto-c0034-018` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 1 |
| 2026-08-21T05:32:38.739592Z | `auto-c0019-000` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 1 |
| 2026-08-21T05:32:35.641606Z | `auto-c0011-012` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 3 |
| 2026-08-21T05:32:32.957068Z | `auto-c0011-011` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 1 |
| 2026-08-21T05:32:30.299436Z | `auto-c0011-004` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 4 |
| 2026-08-21T05:32:27.546076Z | `auto-c0001-014` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 1 |
| 2026-08-21T05:32:24.926916Z | `auto-c0001-012` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 7 |
| 2026-08-21T05:32:22.372064Z | `auto-c0001-011` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 1 |
| 2026-08-21T05:32:19.701274Z | `auto-c0001-010` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 1 |
| 2026-08-21T05:32:18.421572Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T05:32:16.900246Z | `auto-c0001-007` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 1 |
| 2026-08-21T05:32:14.024387Z | `auto-c0001-004` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 1 |
| 2026-08-21T05:32:11.218690Z | `auto-c0001-003` | deferred | d5-migrate | 1 | verdict revoked: D5-6 migration: artifact predates the d5-fp-reinterpret transform and its extractions carry 6 |
| 2026-08-21T05:06:54.849862Z | `auto-c0028-017` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T05:06:41.378483Z | `auto-c0028-016` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T05:06:31.944737Z | `auto-c0028-015` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T05:06:21.902337Z | `auto-c0028-014` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T05:06:12.498587Z | `auto-c0028-013` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T05:05:46.845122Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-21T05:05:44.024948Z | `auto-c0019-003` | gate_failed | wasm-link | 1 | not linked: unit.c:137:43: error: too many arguments to function call, expected 0, have 2   137 \|   (*(code * |
| 2026-08-21T04:21:07.638815Z | `auto-c0019-002` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:20:57.937597Z | `auto-c0019-001` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:20:48.109112Z | `auto-c0019-000` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
