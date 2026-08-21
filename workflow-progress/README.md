# Port workflow: IDLE

*Generated 2026-08-21T05:35:19.940452Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `IDLE` (idle) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 24/1396 settled (3 green, 21 staged) |
| **Retries outstanding** | 1 |
| **Untouched** | 1367 |
| **Last transition** | 2026-08-21T05:35:19.940452Z |
| **Last green** | 2026-08-21T05:06:54.849862Z (`auto-c0028-017`) |
| **Last product commit** | `5c923c5d696385455c850141a744c57da68f5bb2` |
| **Current model** | `unsloth/Qwen3.8-27B-GGUF` @ ? ctx |
| **Driver** | stopped |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
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
| 2026-08-21T04:20:38.215999Z | `auto-c0011-012` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:20:26.832974Z | `auto-c0011-011` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:20:15.791271Z | `auto-c0011-010` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:20:04.674340Z | `auto-c0011-009` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:19:53.034319Z | `auto-c0011-008` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:19:41.058572Z | `auto-c0011-007` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:19:28.928472Z | `auto-c0011-006` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:19:19.371941Z | `auto-c0011-004` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:19:09.971776Z | `auto-c0035-006` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T04:18:08.317289Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-21T04:18:02.807350Z | `auto-c0018-018` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T03:02:18.947843Z | `auto-c0053-010` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T03:01:52.234508Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-21T03:01:44.434678Z | `auto-c0053-009` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T02:40:35.565882Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-21T02:40:29.857487Z | `auto-c0035-006` | retryable | compile-fix | 1 | stuck: identical diagnostics after applied fix |
| 2026-08-21T01:58:25.770912Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-21T01:58:18.512173Z | `auto-c0035-005` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T01:58:06.366051Z | `auto-c0029-015` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T01:57:39.076057Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-21T01:57:33.430678Z | `auto-c0029-013` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T01:40:39.058131Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-21T01:40:35.568087Z | `auto-c0018-018` | gate_failed | wasm-link | 1 | not linked: In file included from unit.c:1: .\gnt4_shim.h:127:9: error: expected ';' after top level declarato |
| 2026-08-21T00:11:04.806655Z | `auto-c0011-005` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
