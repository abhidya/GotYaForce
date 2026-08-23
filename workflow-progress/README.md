# Port workflow: IDLE

*Generated 2026-08-23T13:03:05.856427Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `IDLE` (idle) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 36/1396 settled (3 green, 33 staged) |
| **Retries outstanding** | 17 |
| **Untouched** | 1340 |
| **Last transition** | 2026-08-23T13:03:05.856427Z |
| **Last green** | 2026-08-23T13:02:56.503413Z (`auto-c0019-001`) |
| **Last product commit** | `ab2c47b985000997bfb3fdb7536231b176214c42` |
| **Active model** | `-` @ - ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | stopped |

**Repeated recent failure classes**

- `assembly:assembly gate link failed before promotion: _start_em_asm --` x3

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-23T13:03:05.856427Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-23T13:02:56.503413Z | `auto-c0019-001` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T12:59:12.516168Z | `auto-c0019-000` | gate_failed | assembly | 2 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-23T12:55:32.774481Z | `auto-c0011-012` | gate_failed | artifact-install | 2 | artifact install refused after assembly pass: artifact preimage has no eligible revoked lifecycle |
| 2026-08-23T12:50:15.976235Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-23T12:50:13.219849Z | `auto-c0011-011` | gate_failed | assembly | 2 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-23T12:46:32.213130Z | `auto-c0011-004` | gate_failed | assembly | 2 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-23T12:42:25.910430Z | `auto-c0053-014` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T12:21:27.193973Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-23T12:21:24.196267Z | `auto-c0053-013` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_00097b4_ |
| 2026-08-23T11:19:23.779521Z | `auto-c0053-012` | gate_failed | assembly | 1 | assembly gate link failed before promotion: link gate: these symbols are UNDEFINED across the assembled units  |
| 2026-08-23T10:43:28.563373Z | `auto-c0053-011` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T10:38:44.366378Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-23T10:38:41.147863Z | `auto-c0050-008` | gate_failed | wasm-link | 1 | not linked: In file included from unit.c:1: .\gnt4_shim.h:200:18: error: expected ';' after top level declarat |
| 2026-08-23T09:18:13.618410Z | `auto-c0050-007` | retryable | compile-fix | 1 | stuck: identical diagnostics after applied fix |
| 2026-08-23T08:44:28.165111Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-23T08:44:24.506768Z | `auto-c0050-006` | gate_failed | wasm-link | 1 | not linked: In file included from unit.c:1: .\gnt4_shim.h:177:1: error: unterminated /* comment   177 \| /* PT |
| 2026-08-23T07:19:26.896523Z | `auto-c0050-005` | retryable | compile-fix | 1 | stuck: identical diagnostics after applied fix |
| 2026-08-23T06:17:53.680719Z | `auto-c0050-004` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T06:14:16.923342Z | `auto-c0050-003` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T05:50:19.898878Z | `auto-c0050-002` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T05:26:24.982227Z | `auto-c0050-001` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T05:02:44.142015Z | `auto-c0050-000` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T04:37:14.222238Z | `auto-c0049-018` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_004beb8_ |
| 2026-08-23T03:56:58.871325Z | `auto-c0049-017` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_001ab6c_ |
| 2026-08-23T03:39:03.431622Z | `auto-c0049-016` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T03:09:45.237668Z | `auto-c0035-008` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T03:06:12.002112Z | `auto-c0035-007` | gate_failed | assembly | 1 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-23T02:04:52.133452Z | `auto-c0035-004` | retryable | compile-fix | 1 | stuck: identical diagnostics after applied fix |
| 2026-08-23T00:41:33.731614Z | `auto-c0035-006` | staged | commit | 7 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T00:33:15.961570Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-23T00:33:13.104625Z | `auto-c0035-003` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: canonical_header_ambiguous: auto-c0035-003 declares FUN_80 |
| 2026-08-22T23:38:47.231847Z | `auto-c0035-001` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_013138c_ |
| 2026-08-22T23:35:29.882739Z | `auto-c0035-006` | gate_failed | assembly | 6 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_801336a |
| 2026-08-22T23:09:52.118914Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-22T23:09:41.685168Z | `auto-c0035-000` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-22T23:06:09.168198Z | `auto-c0018-018` | staged | commit | 4 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-22T22:37:33.018904Z | `auto-c0035-006` | gate_failed | assembly | 5 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_801336a |
| 2026-08-22T21:56:47.752408Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-22T21:56:47.843302Z | `auto-c0018-018` | deferred | assembly | 3 | interrupted before a verdict; requeued |
| 2026-08-22T21:46:57.682224Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-22T21:46:57.779786Z | `auto-c0035-006` | deferred | assembly | 4 | interrupted before a verdict; requeued |
| 2026-08-22T21:38:32.735448Z | `auto-c0018-018` | deferred | assembly | 3 | interrupted before a verdict; requeued |
| 2026-08-22T21:38:32.410178Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-21T22:07:59.479820Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T22:00:29.212518Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-21T22:00:29.288948Z | `auto-c0035-006` | deferred | assembly | 4 | interrupted before a verdict; requeued |
| 2026-08-21T21:57:43.919978Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T20:50:34.558550Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T20:45:52.410452Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
