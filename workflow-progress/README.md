# Port workflow: RUNNING

*Generated 2026-08-23T19:48:57.311797Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (healthy_progress) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 49/1396 settled (3 green, 46 staged) |
| **Retries outstanding** | 18 |
| **Untouched** | 1326 |
| **Last transition** | 2026-08-23T19:48:57.311797Z |
| **Last green** | 2026-08-23T19:48:57.311797Z (`auto-c0050-005`) |
| **Last product commit** | `788b184b95fa43e92e285bc62b2435fecb4374a0` |
| **Active model** | `unsloth/Qwen3.8-27B-GGUF` @ 60000 ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | running |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-23T19:48:57.311797Z | `auto-c0050-005` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T19:24:47.313085Z | `auto-c0049-018` | gate_failed | assembly | 2 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-23T19:03:21.190722Z | `auto-c0049-017` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T18:44:10.432066Z | `auto-c0035-007` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T18:18:06.278937Z | `auto-c0035-004` | gate_failed | assembly | 2 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_8008387 |
| 2026-08-23T17:46:56.798184Z | `auto-c0035-003` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T17:42:34.118364Z | `auto-c0035-001` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T17:38:44.853905Z | `auto-c0033-011` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T17:14:21.333532Z | `auto-c0033-005` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T16:51:32.849153Z | `auto-c0029-014` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T16:47:53.273547Z | `auto-c0029-012` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_80047aa |
| 2026-08-23T16:19:59.828978Z | `auto-c0029-002` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_00c74ec_ |
| 2026-08-23T15:23:35.358303Z | `auto-c0029-001` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_0006dc8_ |
| 2026-08-23T14:57:00.712595Z | `auto-c0029-000` | gate_failed | assembly | 1 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-23T14:06:46.079321Z | `auto-c0028-018` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_0007030_ |
| 2026-08-23T13:45:22.582156Z | `auto-c0028-017` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T13:41:38.443640Z | `auto-c0028-016` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T13:38:14.809236Z | `auto-c0028-015` | gate_failed | assembly | 2 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_8010342 |
| 2026-08-23T13:35:20.434084Z | `auto-c0028-014` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T13:31:39.182679Z | `auto-c0028-013` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T13:27:48.153342Z | `auto-c0019-003` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T13:05:34.628508Z | `auto-c0019-002` | gate_failed | assembly | 2 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_800bae6 |
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
