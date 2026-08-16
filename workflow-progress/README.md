# Port workflow: PAUSED

*Generated 2026-08-16T14:19:03.458590Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `PAUSED` (provider_paused) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 2/1520 settled (2 green, 0 staged) |
| **Retries outstanding** | 19 |
| **Untouched** | 1499 |
| **Last transition** | 2026-08-16T14:19:03.458590Z |
| **Last green** | never (`-`) |
| **Last product commit** | `-` |
| **Current model** | `unsloth/Qwen3.6-27B-MTP-GGUF` @ ? ctx |
| **Driver** | stopped |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-16T14:19:03.458590Z | `-` | provider_paused | machine | 0 | Provider paused; model released until it answers. |
| 2026-08-16T14:18:21.644947Z | `auto-c0000-003` | deferred | compile-fix | 0 | provider unavailable, unit not blamed: Custom API returned no assistant content or tool-call arguments (finish |
| 2026-08-16T13:15:34.365231Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T13:10:39.165851Z | `-` | provider_paused | machine | 0 | Provider paused; model released until it answers. |
| 2026-08-16T13:09:56.179240Z | `auto-c0000-003` | deferred | compile-fix | 0 | provider unavailable, unit not blamed: Custom API returned no assistant content or tool-call arguments |
| 2026-08-16T12:48:38.478014Z | `auto-c0000-001` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T12:18:39.792453Z | `auto-c0000-001` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T12:18:39.831453Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T12:14:34.777346Z | `-` | starting | machine | 0 | Manual pause lifted; re-arming the empty grace. |
| 2026-08-16T12:14:17.811259Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-16T12:13:17.673994Z | `auto-c0000-001` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T12:13:17.727516Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T11:51:12.769635Z | `auto-c0001-004` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T11:51:07.610912Z | `auto-c0000-015` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T11:51:05.004615Z | `auto-c0000-012` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T11:51:01.893443Z | `auto-c0000-009` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T11:50:58.791077Z | `auto-c0000-003` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T11:50:56.131648Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T11:50:56.076647Z | `auto-c0000-001` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T11:50:56.131648Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T11:48:46.885886Z | `-` | starting | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-16T11:41:50.392030Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-16T11:40:07.991906Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
