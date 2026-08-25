# Port workflow: RUNNING

*Generated 2026-08-25T15:57:33.884878Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (healthy_progress) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 93/1396 settled (3 green, 90 staged) |
| **Retries outstanding** | 31 |
| **Untouched** | 1268 |
| **Last transition** | 2026-08-25T15:57:33.884878Z |
| **Last green** | 2026-08-25T14:58:12.930676Z (`auto-c0035-004`) |
| **Last product commit** | `8dd1a752de29ab13db2a2da0c50f4ce177bf4d21` |
| **Active model** | `unsloth/Qwen3.8-27B-GGUF` @ 60000 ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | running |

**Repeated recent failure classes**

- `assembly:assembly gate canonicalize failed before promotion: owner_va` x3

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-25T15:57:33.884878Z | `auto-c0011-012` | gate_failed | assembly | 7 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_007c800_ |
| 2026-08-25T15:54:12.789899Z | `auto-c0053-013` | gate_failed | artifact-install | 4 | artifact install refused after assembly pass: artifact preimage has no eligible revoked lifecycle |
| 2026-08-25T15:27:54.049222Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-25T15:27:50.323590Z | `auto-c0043-007` | gate_failed | assembly | 2 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected FUN_8016d39 |
| 2026-08-25T15:01:42.227993Z | `auto-c0030-014` | gate_failed | assembly | 2 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected apply_actor |
| 2026-08-25T14:58:12.930676Z | `auto-c0035-004` | staged | commit | 6 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-25T14:27:15.499561Z | `auto-c0029-012` | gate_failed | assembly | 5 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_0006fb4_ |
| 2026-08-25T13:31:47.616846Z | `auto-c0029-002` | staged | commit | 5 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-25T13:05:29.790679Z | `auto-c0019-000` | staged | commit | 6 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-25T13:01:09.678544Z | `auto-c0011-012` | gate_failed | assembly | 6 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_007c800_ |
| 2026-08-25T12:57:25.355978Z | `auto-c0011-011` | staged | commit | 6 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-25T12:52:59.319115Z | `auto-c0011-004` | staged | commit | 6 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-25T12:47:58.440284Z | `auto-c0053-013` | gate_failed | wasm-link | 3 | not linked: wasm-ld: error: C:\Users\manny\AppData\Local\Temp\emscripten_temp_0eul7rvn\unit.o: undefined symbo |
| 2026-08-25T12:02:52.923154Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-25T12:01:17.981024Z | `auto-c0053-012` | gate_failed | wasm-link | 4 | not linked: unit.c:81:36: error: use of undeclared identifier 'FUN_801b9adc'; did you mean 'FUN_801b8a1c'? uni |
| 2026-08-25T10:21:07.897675Z | `auto-c0035-004` | gate_failed | assembly | 5 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-25T09:45:44.359960Z | `auto-c0029-012` | gate_failed | assembly | 4 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_0006fb4_ |
| 2026-08-25T09:07:27.626328Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-25T09:07:23.417032Z | `auto-c0029-002` | gate_failed | assembly | 4 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-25T08:34:44.889846Z | `auto-c0019-000` | gate_failed | assembly | 5 | assembly gate link failed before promotion: _start_em_asm --export-if-defined=__stop_em_asm --export-if-define |
| 2026-08-25T08:29:38.440541Z | `auto-c0011-012` | gate_failed | artifact-install | 5 | artifact install refused after assembly pass: legacy revoked artifact proof failed: legacy-commit-invalid |
| 2026-08-25T08:24:36.165008Z | `auto-c0011-011` | gate_failed | artifact-install | 5 | artifact install refused after assembly pass: legacy revoked artifact proof failed: legacy-commit-invalid |
| 2026-08-25T08:19:04.268884Z | `auto-c0011-004` | gate_failed | artifact-install | 5 | artifact install refused after assembly pass: legacy revoked artifact proof failed: legacy-commit-invalid |
| 2026-08-25T08:13:01.298723Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-25T08:13:02.856228Z | `auto-c0053-013` | deferred | assembly | 2 | interrupted before a verdict; requeued |
| 2026-08-25T06:06:53.512808Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-25T06:06:53.623325Z | `auto-c0053-012` | deferred | assembly | 3 | interrupted before a verdict; requeued |
| 2026-08-25T04:32:10.554522Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-25T04:17:03.809356Z | `auto-c0050-006` | gate_failed | wasm-link | 4 | not linked: wasm-ld: error: C:\Users\manny\AppData\Local\Temp\emscripten_temp_73qpxf7_\unit.o: undefined symbo |
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
