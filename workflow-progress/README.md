# Port workflow: IDLE

*Generated 2026-08-26T06:59:59.333006Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `IDLE` (idle) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 106/1396 settled (3 green, 103 staged) |
| **Retries outstanding** | 149 |
| **Untouched** | 1130 |
| **Last transition** | 2026-08-26T06:59:59.333006Z |
| **Last green** | 2026-08-26T06:26:05.318522Z (`auto-c0054-003`) |
| **Last product commit** | `0516a3307e195881d82f5fb10ce236905204d59f` |
| **Active model** | `-` @ - ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | stopped |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-26T06:59:22.634473Z | `auto-c0001-005` | deferred | manual-revoke | 1 | verdict revoked and requeued: behaviorally wrong vs console: 200/200 dolphin-trace captures diverge on w348 (r |
| 2026-08-26T06:59:02.341374Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-26T06:47:47.000880Z | `auto-c0054-004` | gate_failed | assembly | 1 | assembly gate link failed before promotion: -1;       \|                                                  ~~ ~ |
| 2026-08-26T06:26:05.318522Z | `auto-c0054-003` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:22:13.443847Z | `auto-c0054-002` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:18:06.449254Z | `auto-c0054-001` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:14:03.174828Z | `auto-c0054-000` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:09:41.009476Z | `auto-c0053-018` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:05:10.220254Z | `auto-c0053-017` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T06:00:09.601311Z | `auto-c0053-016` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_01ba750_ declared void but their results are assigned; no header edit ca |
| 2026-08-26T06:00:06.178042Z | `auto-c0053-008` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_01b7894_ declared void but their results are assigned; no header edit ca |
| 2026-08-26T06:00:02.714102Z | `auto-c0053-007` | gate_failed | wasm-link | 1 | not linked: .\gnt4_shim.h:188:80: error: unterminated /* comment unit.c:156:86: error: subscripted value is no |
| 2026-08-26T04:33:53.400740Z | `auto-c0053-006` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: canonical_header_ambiguous: auto-c0053-006 declares zz_008 |
| 2026-08-26T04:01:34.891104Z | `auto-c0053-005` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T03:37:17.602528Z | `auto-c0053-004` | gate_failed | assembly | 1 | assembly gate canonicalize failed before promotion: canonical_header_ambiguous: auto-c0011-012 declares FUN_80 |
| 2026-08-26T03:12:01.813822Z | `auto-c0053-003` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-26T02:44:01.567665Z | `auto-c0053-002` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:43:48.704874Z | `auto-c0053-001` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:43:35.615442Z | `auto-c0053-000` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:43:22.464314Z | `auto-c0052-018` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:43:09.685481Z | `auto-c0052-015` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:42:56.644387Z | `auto-c0046-005` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:42:43.837447Z | `auto-c0046-004` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:42:30.877631Z | `auto-c0046-003` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:42:17.985867Z | `auto-c0046-002` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:42:04.775671Z | `auto-c0044-002` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:41:51.736841Z | `auto-c0044-001` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:41:38.712947Z | `auto-c0044-000` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:41:25.588093Z | `auto-c0043-015` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:41:12.664331Z | `auto-c0043-014` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:40:59.232878Z | `auto-c0043-013` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:40:45.745771Z | `auto-c0043-012` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:40:32.732700Z | `auto-c0043-011` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_016e7fc_ declared void but their results are assigned; no header edit ca |
| 2026-08-26T02:40:29.088233Z | `auto-c0043-010` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:40:15.722441Z | `auto-c0043-009` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:40:02.687870Z | `auto-c0043-008` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:39:49.479997Z | `auto-c0043-006` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:39:36.562833Z | `auto-c0043-005` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:39:22.268232Z | `auto-c0043-004` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:39:08.590818Z | `auto-c0043-003` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:38:54.550432Z | `auto-c0043-002` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:38:41.301267Z | `auto-c0043-001` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:38:28.379468Z | `auto-c0043-000` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:38:15.321953Z | `auto-c0042-018` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:38:02.282385Z | `auto-c0042-017` | structural_ineligible | extract | 1 | verbatim .c is self-contradictory: zz_0167334_ declared void but their results are assigned; no header edit ca |
| 2026-08-26T02:37:59.061851Z | `auto-c0042-016` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:37:45.900787Z | `auto-c0042-015` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:37:32.971585Z | `auto-c0042-014` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:37:19.863922Z | `auto-c0042-013` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
| 2026-08-26T02:37:06.975514Z | `auto-c0041-013` | retryable | compile-fix | 1 | compile-fix LLM: 500 Server Error: Internal Server Error for url: http://127.0.0.1:8888/v1/chat/completions \| |
