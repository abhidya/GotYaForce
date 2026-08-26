# Port workflow: RUNNING

*Generated 2026-08-26T02:11:31.333398Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (healthy_progress) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 99/1396 settled (3 green, 96 staged) |
| **Retries outstanding** | 97 |
| **Untouched** | 1194 |
| **Last transition** | 2026-08-26T02:11:31.333398Z |
| **Last green** | 2026-08-26T01:15:01.475553Z (`auto-c0025-002`) |
| **Last product commit** | `514c85759591ae3def65a08e204128438e43e7d6` |
| **Active model** | `unsloth/Qwen3.8-27B-GGUF` @ 60000 ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | running |

**Repeated recent failure classes**

- `compile-fix:compile-fix LLM: 500 Server Error: Internal Server Error for` x45

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-26T02:11:31.333398Z | `auto-c0039-015` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:11:18.396493Z | `auto-c0039-014` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:11:05.541216Z | `auto-c0039-013` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:10:52.674249Z | `auto-c0039-012` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:10:39.551290Z | `auto-c0039-010` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_01515b8_ declared void but their results are assigned; no header edit ca |
| 2026-08-26T02:10:36.248614Z | `auto-c0039-009` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:10:23.243868Z | `auto-c0039-008` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:10:10.389033Z | `auto-c0039-007` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:09:57.159169Z | `auto-c0039-006` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:09:43.056573Z | `auto-c0039-005` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:09:30.303614Z | `auto-c0039-004` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:09:17.255007Z | `auto-c0039-003` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:09:04.413778Z | `auto-c0039-002` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:08:51.461824Z | `auto-c0039-001` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:08:38.273378Z | `auto-c0038-018` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:08:25.445156Z | `auto-c0035-011` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:08:12.337306Z | `auto-c0035-010` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:07:59.300602Z | `auto-c0034-006` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:07:46.470127Z | `auto-c0034-005` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:07:33.667169Z | `auto-c0034-004` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:07:20.334437Z | `auto-c0034-003` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:07:07.581173Z | `auto-c0034-002` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:06:54.700226Z | `auto-c0032-002` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:06:41.853679Z | `auto-c0032-001` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:06:28.686887Z | `auto-c0032-000` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:06:15.877961Z | `auto-c0031-018` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:06:03.228157Z | `auto-c0031-017` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:05:50.266872Z | `auto-c0031-016` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:05:37.457871Z | `auto-c0031-014` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:05:24.583385Z | `auto-c0031-013` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:05:11.723051Z | `auto-c0031-012` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
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
