# Port workflow: RUNNING

*Generated 2026-08-21T13:35:10.394751Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (healthy_progress) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 16/1396 settled (3 green, 13 staged) |
| **Retries outstanding** | 1 |
| **Untouched** | 1375 |
| **Last transition** | 2026-08-21T13:35:10.394751Z |
| **Last green** | 2026-08-21T13:30:55.951566Z (`collision-core`) |
| **Last product commit** | `f6b8b65d202671ac397c104d3ed13f1bccbfbb52` |
| **Active model** | `unsloth/Qwen3.8-27B-GGUF` @ 60000 ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | running |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-21T13:35:10.394751Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-21T13:35:10.431247Z | `auto-c0033-005` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-21T13:33:37.947361Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T13:30:55.951566Z | `collision-core` | green | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:30:39.420895Z | `auto-c0053-010` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:30:26.298668Z | `auto-c0053-009` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:30:14.071673Z | `auto-c0035-005` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:30:02.758007Z | `auto-c0034-018` | staged | artifact-digest-backfill | 2 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:29:50.123303Z | `auto-c0029-015` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:29:37.507648Z | `auto-c0011-010` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:29:26.223078Z | `auto-c0011-009` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:29:15.938781Z | `auto-c0011-008` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:29:04.816702Z | `auto-c0011-007` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
| 2026-08-21T13:28:53.986587Z | `auto-c0011-006` | staged | artifact-digest-backfill | 1 | legacy artifact digest sanctioned: one-time canonical digest binding for surviving pre-digest green; remote pu |
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
