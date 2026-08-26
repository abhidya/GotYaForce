# Port workflow: RUNNING

*Generated 2026-08-26T02:04:58.813089Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (healthy_progress) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 99/1396 settled (3 green, 96 staged) |
| **Retries outstanding** | 67 |
| **Untouched** | 1225 |
| **Last transition** | 2026-08-26T02:04:58.813089Z |
| **Last green** | 2026-08-26T01:15:01.475553Z (`auto-c0025-002`) |
| **Last product commit** | `514c85759591ae3def65a08e204128438e43e7d6` |
| **Active model** | `unsloth/Qwen3.8-27B-GGUF` @ 60000 ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | running |

**Repeated recent failure classes**

- `compile-fix:compile-fix LLM: 500 Server Error: Internal Server Error for` x15

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-26T02:04:58.813089Z | `auto-c0031-011` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:04:46.118064Z | `auto-c0031-010` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:04:32.772938Z | `auto-c0031-009` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:04:19.332809Z | `auto-c0031-003` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:04:06.264052Z | `auto-c0031-001` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:03:53.046170Z | `auto-c0031-000` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:03:39.900465Z | `auto-c0030-018` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:03:26.914759Z | `auto-c0030-017` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T01:40:48.314055Z | `auto-c0030-016` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T01:40:35.329679Z | `auto-c0030-015` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T01:40:22.138767Z | `auto-c0029-010` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T01:40:09.355601Z | `auto-c0029-009` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T01:39:56.325918Z | `auto-c0025-006` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T01:39:43.357807Z | `auto-c0025-005` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T01:39:30.361560Z | `auto-c0025-004` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T01:15:01.475553Z | `auto-c0025-002` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T00:46:58.609972Z | `auto-c0025-001` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:46:45.841181Z | `auto-c0025-000` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:46:32.967251Z | `auto-c0024-018` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:46:20.174016Z | `auto-c0024-017` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:46:07.214268Z | `auto-c0024-016` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T00:45:54.315665Z | `auto-c0024-015` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
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
