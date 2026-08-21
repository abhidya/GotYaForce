# Port workflow: IDLE

*Generated 2026-08-21T13:28:42.824083Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `IDLE` (idle) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 16/1396 settled (3 green, 13 staged) |
| **Retries outstanding** | 1 |
| **Untouched** | 1375 |
| **Last transition** | 2026-08-21T13:28:42.824083Z |
| **Last green** | 2026-08-21T13:28:42.824083Z (`auto-c0011-005`) |
| **Last product commit** | `dfec894b44c0383098025a866601bbd1cc73aead` |
| **Active model** | `-` @ - ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | stopped |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-21T13:28:42.824083Z | `auto-c0011-005` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:28:31.613924Z | `auto-c0002-001` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:28:19.134620Z | `auto-c0001-005` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:27:48.635216Z | `auto-c0035-006` | deferred | manual-revoke | 3 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1898-1899; timestamp=2026-08-21T05:37:2 |
| 2026-08-21T13:27:37.209776Z | `auto-c0035-002` | deferred | manual-revoke | 2 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1877-1878; timestamp=2026-08-21T05:36:2 |
| 2026-08-21T13:27:24.217425Z | `auto-c0029-013` | deferred | manual-revoke | 1 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1595-1596; timestamp=2026-08-21T01:57:3 |
| 2026-08-21T13:27:12.064014Z | `auto-c0028-017` | deferred | manual-revoke | 1 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1843-1844; timestamp=2026-08-21T05:06:5 |
| 2026-08-21T13:27:00.646271Z | `auto-c0028-016` | deferred | manual-revoke | 1 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1833-1834; timestamp=2026-08-21T05:06:4 |
| 2026-08-21T13:26:45.200769Z | `auto-c0028-015` | deferred | manual-revoke | 1 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1823-1824; timestamp=2026-08-21T05:06:3 |
| 2026-08-21T13:26:26.032246Z | `auto-c0028-014` | deferred | manual-revoke | 1 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1813-1814; timestamp=2026-08-21T05:06:2 |
| 2026-08-21T13:26:09.583673Z | `auto-c0028-013` | deferred | manual-revoke | 1 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1803-1804; timestamp=2026-08-21T05:06:1 |
| 2026-08-21T13:25:58.635853Z | `auto-c0019-002` | deferred | manual-revoke | 1 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1780-1781; timestamp=2026-08-21T04:21:1 |
| 2026-08-21T13:25:46.596394Z | `auto-c0019-001` | deferred | manual-revoke | 1 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1770-1771; timestamp=2026-08-21T04:21:0 |
| 2026-08-21T13:25:27.887467Z | `auto-c0018-018` | deferred | manual-revoke | 2 | verdict revoked and requeued: assembly eligibility audit: events.jsonl:1661-1662; timestamp=2026-08-21T04:18:0 |
| 2026-08-21T12:09:44.045851Z | `auto-c0029-014` | deferred | manual-revoke | 1 | verdict revoked and requeued: Legacy pre-transaction promotion b96586649c8ca84c2d7a220c2aecb0eca017ebcc was pu |
| 2026-08-21T11:42:19.166344Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T11:25:19.650124Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T09:28:06.851661Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T08:57:34.711639Z | `auto-c0029-014` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T08:56:57.296370Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-21T08:56:57.111838Z | `auto-c0029-012` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-21T08:55:01.924134Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T08:45:45.758222Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T08:44:00.797387Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T08:43:31.339185Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T08:39:06.722394Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T08:31:27.450905Z | `-` | running | machine | 0 | Driver running. |
| 2026-08-21T08:31:03.783917Z | `-` | blocked | machine | 0 | Blocked: serving slot not ready: load request failed: 400 Client Error: Bad Request for url: http://127.0.0.1: |
| 2026-08-21T07:12:44.407214Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T07:12:26.010755Z | `-` | blocked | machine | 0 | Blocked: serving slot not ready: load request failed: 400 Client Error: Bad Request for url: http://127.0.0.1: |
| 2026-08-21T07:11:40.555467Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T07:04:30.565961Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T06:59:22.879546Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 262144 ctx. |
| 2026-08-21T06:59:22.917050Z | `auto-c0029-002` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-21T06:36:15.218821Z | `-` | blocked | machine | 0 | Blocked: serving slot not ready: load request failed: 409 Client Error: Conflict for url: http://127.0.0.1:888 |
| 2026-08-21T06:32:16.292260Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T06:31:32.810041Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T06:31:14.210535Z | `-` | blocked | machine | 0 | Blocked: chat contract preflight failed: {"error":{"message":"Lost connection to the model server. It may have |
| 2026-08-21T06:30:05.278129Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T06:19:41.497528Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T06:18:39.114382Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 262144 ctx. |
| 2026-08-21T06:18:39.137531Z | `auto-c0029-001` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-21T06:17:50.709687Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T06:11:19.918797Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T06:03:21.957050Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 262144 ctx. |
| 2026-08-21T06:03:22.023149Z | `auto-c0029-000` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-21T06:02:29.449906Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T06:02:17.484599Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T06:01:37.664052Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T05:37:17.022664Z | `auto-c0035-006` | staged | commit | 3 | compile-only staging artifact (UNVERIFIED, not integrated) |
