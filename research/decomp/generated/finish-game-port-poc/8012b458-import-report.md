# OGhidra import report: 0x8012b458

- Artifact schema: 1
- Model: unsloth/Qwen3.6-35B-A3B-MTP-GGUF:UD-IQ3_S
- Prompt revision: port-1to1-artifact-v1
- Structured-output mode: json_schema
- Artifact verification: verified
- OGhidra integration status before the trusted importer profile: blocked
- GotYaForce importer profile: candidate
- Generated candidate: `research/decomp/generated/finish-game-port-poc/fn_8012b458.generated.ts`
- Eligible for automatic verification: **yes**

## Recovered Eagle Jet facts

| Fact | Status |
| --- | --- |
| effectMode | recovered |
| timerSeed | recovered |
| retireHitbox | recovered |
| soundCue | recovered |
| parts607 | recovered |
| parts61b | recovered |
| timerDecrement | recovered |
| expiryCompare | recovered |
| cleanup | recovered |
| cleanupCooldown | recovered |
| cleanupBits | recovered |
| cleanupCue | recovered |

## Blocking dependencies

- None

## Import decision

A compilable isolated candidate was emitted. Production registration remains unchanged until automatic compile, differential, ROM, and browser gates pass.

## Automatic compilation and behavior verification

- Generated TypeScript compilation: **passed**
- Automatic behavior comparison: **passed**
- Generated scenarios: 12
- Handwritten scenarios: 0
- Passed scenarios: 12/12
- Independent oracle: existing GotYaForce family implementation
- Machine-readable result: `research/decomp/generated/finish-game-port-poc/8012b458-auto-verification.json`
