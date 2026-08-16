# Port workflow: RUNNING

*Generated 2026-08-16T11:51:05.004615Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (active_no_green) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 2/1520 settled (2 green, 0 staged) |
| **Retries outstanding** | 19 |
| **Untouched** | 1496 |
| **Last transition** | 2026-08-16T11:51:05.004615Z |
| **Last green** | never (`-`) |
| **Last product commit** | `-` |
| **Current model** | `unsloth/Qwen3.6-27B-MTP-GGUF` @ 32768 ctx |
| **Driver** | running |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-16T11:51:05.004615Z | `auto-c0000-012` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T11:51:01.893443Z | `auto-c0000-009` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T11:50:58.791077Z | `auto-c0000-003` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T11:50:56.131648Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T11:50:56.076647Z | `auto-c0000-001` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T11:50:56.131648Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T11:48:46.885886Z | `-` | starting | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-16T11:41:50.392030Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-16T11:40:07.991906Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
