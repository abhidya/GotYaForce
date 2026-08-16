# Port workflow: RUNNING

*Generated 2026-08-16T21:29:50.696861Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (active_no_green) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 2/1520 settled (2 green, 0 staged) |
| **Retries outstanding** | 21 |
| **Untouched** | 1497 |
| **Last transition** | 2026-08-16T21:29:50.696861Z |
| **Last green** | never (`-`) |
| **Last product commit** | `-` |
| **Current model** | `unsloth/Qwen3.6-27B-MTP-GGUF` @ 32768 ctx |
| **Driver** | running |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-16T21:29:50.696861Z | `auto-c0001-004` | gate_failed | wasm-link | 1 | not linked: /bin/bash: line 1: cygpath: command not found /bin/bash: line 1: cygpath: command not found /bin/b |
| 2026-08-16T19:55:31.079161Z | `auto-c0000-015` | gate_failed | wasm-link | 1 | not linked: /bin/bash: line 1: cygpath: command not found /bin/bash: line 1: cygpath: command not found /bin/b |
| 2026-08-16T18:20:10.231491Z | `auto-c0000-012` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T18:20:10.295491Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T17:45:48.175663Z | `-` | palworld_protected | machine | 0 | 1 Palworld player(s) connected. |
| 2026-08-16T17:08:36.498164Z | `auto-c0000-009` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T17:08:36.537184Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T16:29:38.141609Z | `-` | palworld_protected | machine | 0 | 1 Palworld player(s) connected. |
| 2026-08-16T16:26:47.713366Z | `auto-c0000-003` | deferred | compile-fix | 0 | interrupted before a verdict; requeued |
| 2026-08-16T16:26:47.779367Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T16:13:17.711235Z | `-` | palworld_protected | machine | 0 | 1 Palworld player(s) connected. |
| 2026-08-16T15:07:53.664088Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T15:04:31.439256Z | `-` | provider_paused | machine | 0 | Provider paused; model released until it answers. |
| 2026-08-16T15:03:59.762414Z | `auto-c0000-003` | deferred | compile-fix | 0 | provider unavailable, unit not blamed: Custom API returned no assistant content or tool-call arguments (finish |
| 2026-08-16T14:22:33.672800Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
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
