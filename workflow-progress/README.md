# Port workflow: RUNNING

*Generated 2026-08-24T13:51:39.341560Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (active_no_green) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 64/1396 settled (3 green, 61 staged) |
| **Retries outstanding** | 17 |
| **Untouched** | 1311 |
| **Last transition** | 2026-08-24T13:51:39.341560Z |
| **Last green** | 2026-08-24T12:30:28.410265Z (`auto-c0024-013`) |
| **Last product commit** | `ccbd9e8590c433d16cd9d891c8b009c8c8921db9` |
| **Active model** | `unsloth/Qwen3.8-27B-GGUF` @ 60000 ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | running |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-24T13:51:39.341560Z | `auto-c0025-003` | gate_failed | wasm-link | 1 | not linked: ing: operator '>>' has lower precedence than '+'; '+' will be evaluated first [-Wshift-op-parenthe |
| 2026-08-24T12:30:28.410265Z | `auto-c0024-013` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T12:26:57.091581Z | `auto-c0021-016` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T12:23:27.275122Z | `auto-c0020-012` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T12:19:58.070405Z | `auto-c0020-007` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_800c5a6 |
| 2026-08-24T11:29:58.213695Z | `auto-c0010-011` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T11:25:54.234067Z | `auto-c0031-002` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_011243c_ declared void but their results are assigned; no header edit ca |
| 2026-08-24T11:25:50.934608Z | `auto-c0019-016` | gate_failed | wasm-link | 1 | not linked: link gate: these symbols are UNDEFINED and became wasm imports, but they are not gnt4_* SDK functi |
| 2026-08-24T10:26:29.795376Z | `auto-c0019-013` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T09:57:52.169712Z | `auto-c0046-001` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T09:54:03.175978Z | `auto-c0010-010` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T09:49:53.239020Z | `auto-c0043-007` | gate_failed | wasm-link | 1 | not linked: .\gnt4_shim.h:209:20: error: expected ';' after top level declarator unit.c:102:34: error: use of  |
| 2026-08-24T08:19:26.053800Z | `auto-c0040-016` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T08:15:33.673039Z | `auto-c0030-014` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_004beb8_ |
| 2026-08-24T07:51:39.861359Z | `auto-c0019-009` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T07:48:06.548187Z | `auto-c0035-004` | gate_failed | assembly | 4 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-24T07:16:45.427273Z | `auto-c0029-012` | gate_failed | assembly | 3 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-24T06:04:33.041275Z | `auto-c0029-002` | gate_failed | assembly | 3 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_0104f20_ |
| 2026-08-24T05:35:58.193403Z | `auto-c0029-001` | staged | commit | 3 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T05:12:56.455725Z | `auto-c0029-000` | gate_failed | wasm-link | 3 | not linked: unit.c:112:9: error: assigning to 'undefined8' (aka 'unsigned long long') from incompatible type ' |
| 2026-08-24T03:56:26.710331Z | `auto-c0028-015` | staged | commit | 4 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T03:53:07.548145Z | `auto-c0019-000` | gate_failed | assembly | 4 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_800bae6 |
| 2026-08-24T03:51:12.947999Z | `auto-c0011-012` | gate_failed | artifact-install | 4 | artifact install refused after assembly pass: legacy revoked artifact proof failed: legacy-commit-invalid |
| 2026-08-24T03:47:52.618706Z | `auto-c0011-011` | gate_failed | artifact-install | 4 | artifact install refused after assembly pass: legacy revoked artifact proof failed: legacy-commit-invalid |
| 2026-08-24T03:44:25.939236Z | `auto-c0011-004` | gate_failed | artifact-install | 4 | artifact install refused after assembly pass: legacy revoked artifact proof failed: legacy-commit-invalid |
| 2026-08-24T03:40:51.386594Z | `auto-c0053-013` | gate_failed | assembly | 2 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-24T02:52:40.969627Z | `auto-c0053-012` | gate_failed | assembly | 3 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-24T02:19:14.462630Z | `auto-c0050-006` | gate_failed | assembly | 3 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_01a4a40_ |
| 2026-08-24T01:57:00.051943Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-24T01:56:49.350787Z | `auto-c0049-018` | staged | commit | 3 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T01:19:29.218320Z | `auto-c0035-004` | gate_failed | assembly | 3 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_80047aa |
| 2026-08-24T00:49:59.114356Z | `auto-c0029-012` | gate_failed | assembly | 2 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-24T00:26:17.588659Z | `auto-c0029-002` | gate_failed | assembly | 2 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-24T00:01:19.489860Z | `auto-c0029-001` | gate_failed | assembly | 2 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_0197ad8_ |
| 2026-08-23T23:35:23.317406Z | `auto-c0029-000` | gate_failed | assembly | 2 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-23T23:11:48.369042Z | `auto-c0028-018` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T22:53:06.907723Z | `auto-c0028-015` | gate_failed | assembly | 3 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_8010342 |
| 2026-08-23T22:50:46.664154Z | `auto-c0019-002` | staged | commit | 3 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T22:47:20.972951Z | `auto-c0019-000` | gate_failed | artifact-install | 3 | artifact install refused after assembly pass: legacy revoked artifact proof failed: legacy-commit-invalid |
| 2026-08-23T22:43:58.554806Z | `auto-c0011-012` | gate_failed | artifact-install | 3 | artifact install refused after assembly pass: legacy revoked artifact proof failed: legacy-commit-invalid |
| 2026-08-23T22:40:26.947973Z | `auto-c0011-011` | gate_failed | artifact-install | 3 | artifact install refused after assembly pass: legacy revoked artifact proof failed: legacy-commit-invalid |
| 2026-08-23T22:36:47.690743Z | `auto-c0011-004` | gate_failed | artifact-install | 3 | artifact install refused after assembly pass: legacy revoked artifact proof failed: legacy-commit-invalid |
| 2026-08-23T22:32:58.697290Z | `auto-c0053-013` | deferred | assembly | 1 | interrupted before a verdict; requeued |
| 2026-08-23T22:00:59.312938Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-23T22:00:55.895283Z | `auto-c0053-012` | gate_failed | assembly | 2 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_801b9ad |
| 2026-08-23T21:26:21.692805Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-23T21:25:09.016615Z | `auto-c0050-008` | gate_failed | wasm-link | 2 | not linked: unit.c:75:29: error: too many arguments to function call, expected 1, have 16 unit.c:78:21: error: |
| 2026-08-23T20:14:46.912010Z | `auto-c0050-007` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-23T20:10:48.090603Z | `auto-c0050-006` | gate_failed | assembly | 2 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_01a452c_ |
| 2026-08-23T19:48:57.311797Z | `auto-c0050-005` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
