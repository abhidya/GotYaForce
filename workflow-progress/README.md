# Port workflow: RUNNING

*Generated 2026-08-26T00:45:41.471107Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (active_no_green) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 98/1396 settled (3 green, 95 staged) |
| **Retries outstanding** | 46 |
| **Untouched** | 1247 |
| **Last transition** | 2026-08-26T00:45:41.471107Z |
| **Last green** | 2026-08-25T23:39:56.962508Z (`auto-c0019-016`) |
| **Last product commit** | `2ca0bb90ac96cd9958494ef0d96a8b318e7426e2` |
| **Active model** | `unsloth/Qwen3.8-27B-GGUF` @ 60000 ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | running |

**Repeated recent failure classes**

- `compile-fix:compile-fix LLM: 500 Server Error: Internal Server Error for` x18

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-26T00:45:41.471107Z | `auto-c0024-014` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:45:28.748581Z | `auto-c0024-012` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:45:16.015656Z | `auto-c0024-011` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:45:02.648221Z | `auto-c0021-017` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:44:49.908068Z | `auto-c0021-015` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:44:37.163395Z | `auto-c0021-014` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:44:24.278185Z | `auto-c0021-013` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:44:11.179172Z | `auto-c0021-007` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: FUN_800cc270 declared void but their results are assigned; no header edit c |
| 2026-08-26T00:44:07.765163Z | `auto-c0021-006` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:43:54.850706Z | `auto-c0021-005` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:43:42.015408Z | `auto-c0021-004` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:43:29.168657Z | `auto-c0021-003` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:43:16.289132Z | `auto-c0021-002` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:43:03.499204Z | `auto-c0021-001` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:42:50.346711Z | `auto-c0021-000` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:42:37.426055Z | `auto-c0020-018` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:42:24.237930Z | `auto-c0020-017` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:42:10.855932Z | `auto-c0020-016` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:41:57.724341Z | `auto-c0020-013` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:15:35.115812Z | `auto-c0020-011` | gate_failed | assembly | 1 | assembly gate link failed before promotion:       ~~ ~~~~~^~~~~~~~~~~~~~~~ auto-c0020-007/unit.c:170:51: note: |
| 2026-08-25T23:39:56.962508Z | `auto-c0019-016` | staged | commit | 3 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-25T22:21:48.246460Z | `auto-c0030-014` | gate_failed | assembly | 4 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected apply_actor |
| 2026-08-25T22:18:31.246813Z | `auto-c0011-012` | staged | commit | 8 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-25T22:13:43.451290Z | `auto-c0053-013` | gate_failed | artifact-install | 5 | artifact install refused after assembly pass: artifact preimage has no eligible revoked lifecycle |
| 2026-08-25T22:08:18.184368Z | `-` | stopped_at_boundary | machine | 0 |  |
| 2026-08-25T22:08:12.947308Z | `auto-c0020-010` | gate_failed | wasm-link | 1 | not linked: In file included from unit.c:1: .\gnt4_shim.h:191:1: error: unterminated /* comment   191 \| /* ex |
| 2026-08-25T20:40:04.641119Z | `auto-c0052-017` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-25T20:05:55.656045Z | `auto-c0025-003` | gate_failed | wasm-link | 2 | not linked: s] unit.c:272:24: warning: operator '>>' has lower precedence than '-'; '-' will be evaluated firs |
| 2026-08-25T18:49:57.556833Z | `auto-c0020-007` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-25T18:45:09.116891Z | `auto-c0019-016` | gate_failed | assembly | 2 | assembly gate canonicalize failed before promotion: owner_variant_abi_incompatible: Clang rejected zz_00088a4_ |
| 2026-08-25T17:52:31.513699Z | `auto-c0043-007` | gate_failed | wasm-link | 3 | not linked: unit.c:4:1: error: expected ')' unit.c:96:36: error: too many arguments to function call, expected |
| 2026-08-25T16:27:43.235751Z | `auto-c0030-014` | gate_failed | assembly | 3 | assembly gate canonicalize failed before promotion: canonical_header_ambiguous: auto-c0030-014 declares apply_ |
| 2026-08-25T16:02:26.029432Z | `auto-c0029-012` | staged | commit | 6 | compile-only staging artifact (UNVERIFIED, not integrated) |
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
