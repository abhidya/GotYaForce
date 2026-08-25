# Port workflow: IDLE

*Generated 2026-08-25T03:10:45.932770Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `IDLE` (idle) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 88/1396 settled (3 green, 85 staged) |
| **Retries outstanding** | 36 |
| **Untouched** | 1268 |
| **Last transition** | 2026-08-25T03:10:45.932770Z |
| **Last green** | 2026-08-24T23:38:51.149010Z (`auto-c0020-000`) |
| **Last product commit** | `1923f3a6e9f877677045111f1893bdbf33dc636b` |
| **Active model** | `-` @ - ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | stopped |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-25T03:10:45.932770Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-25T03:10:42.432975Z | `auto-c0020-009` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_800c617 |
| 2026-08-25T02:46:49.712626Z | `auto-c0020-008` | gate_failed | wasm-link | 1 | not linked: unit.c:56:10: error: assigning to 'undefined8' (aka 'unsigned long long') from incompatible type ' |
| 2026-08-25T01:08:18.916123Z | `auto-c0020-006` | retryable | compile-fix | 1 | compile-fix LLM: Serving context 16384 < required 17596 and reload failed: 409 Client Error: Conflict for url: |
| 2026-08-25T01:08:13.852401Z | `auto-c0020-005` | retryable | compile-fix | 1 | compile-fix LLM: Serving context 16384 < required 18333 and reload failed: 409 Client Error: Conflict for url: |
| 2026-08-25T01:08:08.643463Z | `auto-c0020-004` | retryable | compile-fix | 1 | compile-fix LLM: Serving context 16384 < required 22940 and reload failed: 409 Client Error: Conflict for url: |
| 2026-08-25T01:08:03.275133Z | `auto-c0020-003` | retryable | compile-fix | 1 | compile-fix LLM: Serving context 16384 < required 16548 and reload failed: 409 Client Error: Conflict for url: |
| 2026-08-25T01:07:57.506101Z | `auto-c0020-002` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_800c1ed |
| 2026-08-25T00:38:56.825983Z | `auto-c0020-001` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: canonical_header_ambiguous: auto-c0020-000 declares zz_000 |
| 2026-08-24T23:38:51.149010Z | `auto-c0020-000` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T23:08:48.006233Z | `auto-c0019-018` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T23:04:54.542163Z | `auto-c0019-017` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T22:41:37.647680Z | `auto-c0019-015` | retryable | compile-fix | 1 | compile-fix LLM: Serving context 16384 < required 20481 and reload failed: 409 Client Error: Conflict for url: |
| 2026-08-24T22:41:30.771202Z | `auto-c0019-014` | retryable | compile-fix | 1 | compile-fix LLM: Serving context 16384 < required 17388 and reload failed: 409 Client Error: Conflict for url: |
| 2026-08-24T22:41:24.565340Z | `auto-c0019-012` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_800be8e |
| 2026-08-24T22:15:06.292061Z | `auto-c0019-011` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T21:50:16.436449Z | `auto-c0019-010` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T21:25:45.730585Z | `auto-c0019-008` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T21:22:11.220108Z | `auto-c0019-007` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T21:18:56.272065Z | `auto-c0019-006` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_800bc2d |
| 2026-08-24T21:16:39.755443Z | `auto-c0019-005` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T21:13:32.062605Z | `auto-c0019-004` | gate_failed | wasm-link | 1 | not linked: unit.c:22:47: error: use of undeclared identifier 'FLOAT_80438528' unit.c:23:15: error: use of und |
| 2026-08-24T19:50:10.132660Z | `auto-c0010-012` | retryable | compile-fix | 1 | compile-fix LLM: Serving context 16384 < required 17173 and reload failed: 409 Client Error: Conflict for url: |
| 2026-08-24T19:49:55.554497Z | `auto-c0010-009` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T19:27:40.251967Z | `auto-c0010-005` | gate_failed | wasm-link | 1 | not linked: .\gnt4_shim.h:170:15: error: conflicting types for 'gnt4_PSVECMag_bl' unit.c:129:13: error: assign |
| 2026-08-24T18:22:28.078952Z | `auto-c0010-004` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-24T18:01:25.183116Z | `auto-c0010-003` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_0072438_ |
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
