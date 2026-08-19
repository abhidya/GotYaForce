# Port workflow: PAUSED

*Generated 2026-08-19T17:00:16.611438Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `PAUSED` (provider_paused) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 9/1520 settled (3 green, 6 staged) |
| **Retries outstanding** | 6 |
| **Untouched** | 1505 |
| **Last transition** | 2026-08-19T17:00:16.611438Z |
| **Last green** | 2026-08-19T12:51:42.040810Z (`auto-c0000-008`) |
| **Last product commit** | `d72a33e403787f6f498aebf7f4b0bf429048251b` |
| **Current model** | `unsloth/Qwen3.8-27B-GGUF` @ 32768 ctx |
| **Driver** | running |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-19T17:00:16.611438Z | `auto-c0000-010` | deferred | compile-fix | 0 | provider unavailable, unit not blamed: Custom API returned no assistant content or tool-call arguments (finish |
| 2026-08-19T14:20:11.003240Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 32768 ctx. |
| 2026-08-19T14:17:33.415996Z | `-` | provider_paused | machine | 0 | Provider paused; model released until it answers. |
| 2026-08-19T14:17:12.817172Z | `auto-c0000-010` | deferred | compile-fix | 0 | provider unavailable, unit not blamed: Custom API returned no assistant content or tool-call arguments (finish |
| 2026-08-19T12:51:44.893788Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-19T12:51:42.040810Z | `auto-c0000-008` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-19T12:28:58.879769Z | `auto-c0000-007` | gate_failed | wasm-link | 1 | not linked: unit.c:70:87: error: incompatible pointer types passing 'undefined **' (aka 'unsigned char **') to |
| 2026-08-19T10:57:33.205941Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-19T10:57:30.475654Z | `auto-c0000-006` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-19T10:45:21.646761Z | `auto-c0000-005` | gate_failed | wasm-link | 1 | not linked: ...ed. emcc: error: ''D:\GotYaForce\research\tools\emsdk/upstream/bin\clang.exe' -target wasm32-un |
| 2026-08-19T08:28:48.229801Z | `auto-c0000-004` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-19T08:28:14.884268Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-19T08:28:11.839516Z | `auto-c0000-002` | gate_failed | wasm-link | 1 | not linked: Setting up EMSDK environment (suppress these messages with EMSDK_QUIET=1) Adding directories to PA |
| 2026-08-19T06:24:13.531584Z | `auto-c0000-000` | gate_failed | wasm-link | 1 | not linked: Setting up EMSDK environment (suppress these messages with EMSDK_QUIET=1) Adding directories to PA |
| 2026-08-19T05:01:02.791780Z | `collision-core` | green | commit | 1 | oracle green: 20000/20000, 28121/32153 |
| 2026-08-19T05:00:48.792410Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 32768 ctx. |
| 2026-08-19T04:58:56.085640Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-19T04:50:57.775646Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-19T04:50:47.275223Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-19T04:50:44.410966Z | `auto-c0001-013` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-19T03:34:49.740030Z | `auto-c0001-012` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-19T02:58:02.302302Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 32768 ctx. |
| 2026-08-19T02:58:02.317938Z | `auto-c0001-011` | retryable | port | 1 | unexpected fault: [WinError 5] Access is denied: 'D:\\GotYaForce\\research\\decomp\\generated\\finish-game-por |
| 2026-08-19T02:55:30.044009Z | `-` | provider_paused | machine | 0 | Provider paused; model released until it answers. |
| 2026-08-19T02:55:12.975917Z | `auto-c0001-011` | deferred | compile-fix | 0 | provider unavailable, unit not blamed: Custom API returned no assistant content or tool-call arguments (finish |
| 2026-08-19T02:33:12.020547Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 32768 ctx. |
| 2026-08-19T02:29:47.625283Z | `-` | provider_paused | machine | 0 | Provider paused; model released until it answers. |
| 2026-08-19T02:29:29.476910Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-19T01:53:19.137019Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-19T01:53:07.779693Z | `auto-c0001-011` | deferred | compile-fix | 0 | provider unavailable, unit not blamed: Custom API returned no assistant content or tool-call arguments (finish |
| 2026-08-19T01:31:06.753430Z | `auto-c0001-010` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-19T01:30:49.624847Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 32768 ctx. |
| 2026-08-19T01:30:49.682400Z | `auto-c0001-009` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-18T23:36:48.222295Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-18T23:36:48.245266Z | `auto-c0001-008` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-18T23:33:20.003789Z | `-` | starting | machine | 0 | Manual pause lifted; re-arming the empty grace. |
| 2026-08-18T23:26:55.506626Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-18T22:49:21.218893Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-17T06:30:21.356839Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-16T23:48:22.669559Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-16T23:45:59.952896Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-16T23:43:38.821886Z | `auto-c0001-007` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-16T23:43:30.536469Z | `auto-c0001-006` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T23:43:30.601468Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T23:17:29.796816Z | `auto-c0001-005` | gate_failed | wasm-link | 1 | not linked: /bin/bash: line 1: cygpath: command not found /bin/bash: line 1: cygpath: command not found /bin/b |
| 2026-08-16T21:29:50.696861Z | `auto-c0001-004` | gate_failed | wasm-link | 1 | not linked: /bin/bash: line 1: cygpath: command not found /bin/bash: line 1: cygpath: command not found /bin/b |
| 2026-08-16T19:55:31.079161Z | `auto-c0000-015` | gate_failed | wasm-link | 1 | not linked: /bin/bash: line 1: cygpath: command not found /bin/bash: line 1: cygpath: command not found /bin/b |
| 2026-08-16T18:20:10.231491Z | `auto-c0000-012` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-16T18:20:10.295491Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.6-27B-MTP-GGUF @ 32768 ctx. |
| 2026-08-16T17:45:48.175663Z | `-` | palworld_protected | machine | 0 | 1 Palworld player(s) connected. |
