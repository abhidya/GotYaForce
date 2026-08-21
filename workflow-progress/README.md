# Port workflow: RUNNING

*Generated 2026-08-21T04:19:19.371941Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (healthy_progress) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 22/1396 settled (3 green, 19 staged) |
| **Retries outstanding** | 0 |
| **Untouched** | 1370 |
| **Last transition** | 2026-08-21T04:19:19.371941Z |
| **Last green** | 2026-08-21T04:19:19.371941Z (`auto-c0011-004`) |
| **Last product commit** | `0d343c079fd33bfa015bd70b5698b31240c247f6` |
| **Current model** | `unsloth/Qwen3.8-27B-GGUF` @ 262144 ctx |
| **Driver** | running |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
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
| 2026-08-21T00:10:58.153178Z | `auto-c0034-018` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T00:10:49.092310Z | `auto-c0035-002` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T00:10:41.677199Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 262144 ctx. |
| 2026-08-20T23:14:14.902202Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-20T22:41:00.850847Z | `auto-c0002-001` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-20T22:40:49.277067Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 262144 ctx. |
| 2026-08-20T22:40:49.292661Z | `auto-c0002-000` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-20T21:36:28.874503Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-20T21:28:57.255507Z | `auto-c0001-018` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_0017380_ declared void but their results are assigned; no header edit ca |
| 2026-08-20T16:40:58.854179Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-20T16:40:55.928569Z | `auto-c0001-016` | gate_failed | wasm-link | 1 | not linked: unit.c:64:11: warning: cast to smaller integer type 'byte' (aka 'unsigned char') from 'float *' [- |
| 2026-08-20T11:37:48.143618Z | `auto-c0001-015` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_00156cc_ declared void but their results are assigned; no header edit ca |
| 2026-08-20T11:37:45.493210Z | `auto-c0001-014` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-20T11:06:09.012032Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-20T11:06:06.055666Z | `auto-c0001-013` | gate_failed | wasm-link | 1 | not linked: unit.c:421:30: error: pointer cannot be cast to type 'float'   421 \|       dVar7 = (double)(float |
| 2026-08-20T08:06:03.039975Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-20T08:06:00.010464Z | `auto-c0001-011` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-20T06:15:12.193225Z | `auto-c0001-005` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-20T05:48:06.303774Z | `auto-c0001-004` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-20T05:47:59.551235Z | `auto-c0001-003` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-20T05:23:19.375532Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-20T05:23:16.752439Z | `auto-c0001-002` | retryable | compile-fix | 1 | compile-fix returned no code block: len=6645 fences=1 head='```c\n/* gnt4_shim.h — POC stage-2 "header + arena |
| 2026-08-20T05:01:00.658558Z | `auto-c0001-001` | retryable | compile-fix | 1 | compile-fix returned no code block: len=7466 fences=1 head='```c\n/* gnt4_shim.h — POC stage-2 "header + arena |
| 2026-08-20T04:34:59.447192Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-20T04:34:56.600038Z | `auto-c0000-018` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-20T04:10:38.024144Z | `auto-c0000-016` | retryable | compile-fix | 1 | compile-fix returned no code block |
| 2026-08-20T03:50:51.066902Z | `auto-c0000-015` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_0009a14_ declared void but their results are assigned; no header edit ca |
| 2026-08-20T03:50:48.343301Z | `auto-c0000-014` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_0009598_ declared void but their results are assigned; no header edit ca |
| 2026-08-20T03:49:26.221492Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-20T03:49:23.375646Z | `auto-c0000-013` | gate_failed | wasm-link | 1 | not linked: unit.c:6:6: error: conflicting types for 'zz_0008f18_' unit.c:7:6: error: conflicting types for 'z |
| 2026-08-20T00:34:14.800588Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-20T00:34:11.804492Z | `auto-c0000-011` | gate_failed | wasm-link | 1 | not linked: /usr/bin/bash: -c: line 1: syntax error near unexpected token `(' /usr/bin/bash: -c: line 1: `sour |
| 2026-08-19T21:59:06.645075Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 262144 ctx. |
