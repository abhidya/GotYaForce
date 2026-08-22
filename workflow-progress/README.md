# Port workflow: RUNNING

*Generated 2026-08-22T21:38:32.410178Z - machine-written, do not edit.*

| | |
|---|---|
| **State** | `RUNNING` (possibly_stuck) |
| **Current unit** | `-` |
| **Current stage** | `-` (attempt 0) |
| **Queue progress** | 23/1396 settled (3 green, 20 staged) |
| **Retries outstanding** | 1 |
| **Untouched** | 1368 |
| **Last transition** | 2026-08-22T21:38:32.410178Z |
| **Last green** | 2026-08-21T16:20:45.850788Z (`auto-c0033-010`) |
| **Last product commit** | `0901d3cd24820364d3e0649b848757eb3bccb5e0` |
| **Active model** | `C:\Users\manny\.cache\huggingface\hub\models--unsloth--Qwen3.8-27B-GGUF\snapshots\4ca720788d1e01f1bff70c033e0d0028fd02e502` @ 71296 ctx |
| **Configured model** | `unsloth/Qwen3.8-27B-GGUF` |
| **Driver** | running |

## Last 50 transitions

| time | unit | result | stage | attempt | detail |
|---|---|---|---|---|---|
| 2026-08-22T21:38:32.410178Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-21T22:07:59.479820Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T22:00:29.212518Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-21T22:00:29.288948Z | `auto-c0035-006` | deferred | assembly | 4 | interrupted before a verdict; requeued |
| 2026-08-21T21:57:43.919978Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T20:50:34.558550Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T20:45:52.410452Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-21T20:45:52.522020Z | `auto-c0018-018` | deferred | assembly | 3 | interrupted before a verdict; requeued |
| 2026-08-21T20:44:18.827648Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T20:28:45.140310Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T20:26:53.076657Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T20:26:18.786459Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-21T20:26:18.903814Z | `auto-c0033-011` | deferred | port | 0 | interrupted before a verdict; requeued |
| 2026-08-21T16:21:20.036764Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T16:20:45.850788Z | `auto-c0033-010` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T16:20:31.989206Z | `auto-c0033-009` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T16:20:15.842453Z | `auto-c0033-008` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T16:20:02.384641Z | `auto-c0033-007` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T16:19:48.574372Z | `auto-c0033-006` | staged | commit | 1 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T16:19:40.835252Z | `auto-c0035-006` | gate_failed | assembly | 4 | assembly gate link failed before promotion: m_asm --export-if-defined=__start_em_lib_deps --export-if-defined= |
| 2026-08-21T16:19:12.855874Z | `auto-c0018-018` | gate_failed | assembly | 3 | assembly gate merge failed before promotion: header merge refused: 1 contested conflict(s); no silent winner i |
| 2026-08-21T15:58:44.998526Z | `auto-c0029-013` | staged | commit | 2 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T15:44:29.191111Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-21T15:44:29.242091Z | `auto-c0018-018` | deferred | manual-revoke | 2 | interrupted before a verdict; requeued |
| 2026-08-21T15:42:56.396349Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T15:41:00.425774Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T15:26:25.074848Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T15:16:34.667615Z | `auto-c0035-002` | staged | commit | 4 | compile-only staging artifact (UNVERIFIED, not integrated) |
| 2026-08-21T15:16:28.119037Z | `-` | running | machine | 0 | Driver running on unsloth/Qwen3.8-27B-GGUF @ 60000 ctx. |
| 2026-08-21T15:16:28.154914Z | `auto-c0029-013` | deferred | manual-revoke | 1 | interrupted before a verdict; requeued |
| 2026-08-21T15:15:38.205887Z | `-` | starting | machine | 0 | Manual pause lifted; resuming heavy work. |
| 2026-08-21T15:14:25.343118Z | `auto-c0035-002` | deferred | diagnosis-invalidate | 3 | diagnosis invalidated: control-plane misroute: attempt 3 passed build+assembly; terminal stage artifact-instal |
| 2026-08-21T13:36:57.057687Z | `-` | manual_paused | machine | 0 | Manually paused by owner (rig gate). |
| 2026-08-21T13:35:16.971877Z | `auto-c0035-002` | gate_failed | artifact-install | 3 | artifact install refused after assembly pass: artifact destination already exists with a different preimage: D |
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
