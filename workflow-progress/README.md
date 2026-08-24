# Port workflow: RUNNING

*Generated 2026-08-24T17:59:03.549246Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (healthy_progress) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 78/1396 settled (3 green, 75 staged) |
| **Retries outstanding** | 20 |
| **Untouched** | 1294 |
| **Last transition** | 2026-08-24T17:59:03.549246Z |
| **Last green** | 2026-08-24T17:37:10.252553Z (`auto-c0010-001`) |
| **Last product commit** | `b5529bd2a0d641665cdfd1bc83a0a71e1bcc097d` |
| **Active model** | `unsloth/Qwen3.8-27B-GGUF` @ 60000 ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | running |

**Repeated recent failure classes**

- `assembly:assembly gate canonicalize failed before promotion: owner_va` x2

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-24T17:59:03.549246Z | `auto-c0010-002` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_004beb8_ |
| 2026-08-24T17:37:10.252553Z | `auto-c0010-001` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T17:14:47.639074Z | `auto-c0010-000` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_0045ef4_ |
| 2026-08-24T16:43:33.203204Z | `auto-c0057-008` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T16:40:39.211623Z | `auto-c0053-015` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T16:37:46.563449Z | `auto-c0052-017` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_004beb8_ |
| 2026-08-24T16:17:39.852480Z | `auto-c0052-016` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T16:14:46.969617Z | `auto-c0046-000` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T16:11:48.310710Z | `auto-c0043-018` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T15:43:31.798277Z | `auto-c0043-017` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T15:22:30.219454Z | `auto-c0043-016` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T15:01:00.654400Z | `auto-c0041-005` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T14:57:57.298914Z | `auto-c0039-011` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T14:54:49.790014Z | `auto-c0039-000` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T14:51:41.980469Z | `auto-c0035-009` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T14:31:03.822380Z | `auto-c0031-015` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T14:11:08.630942Z | `auto-c0029-011` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
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
