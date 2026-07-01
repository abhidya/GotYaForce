#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const exportDir = path.join(repoRoot, "research", "decomp", "ghidra-export");
const indexPath = path.join(repoRoot, "research", "decomp", "index", "function-evidence-index.json");
const outDir = path.join(repoRoot, "research", "decomp", "index");
const outJson = path.join(outDir, "cpu-ai-evidence.json");
const outMd = path.join(outDir, "cpu-ai-evidence.md");

if (!fs.existsSync(indexPath)) {
  throw new Error(`missing function evidence index: ${rel(indexPath)}; run npm run index:decomp first`);
}

const functionIndex = JSON.parse(fs.readFileSync(indexPath, "utf8"));
const functions = new Map(functionIndex.functions.map((fn) => [fn.address.toLowerCase(), fn]));

const anchors = [
  {
    address: "0x801962c4",
    inferredName: "challenge_force_slot_team_setup",
    system: "Challenge CPU/player slot setup",
    summary:
      "Builds Challenge slot/team state and force roster entries before active actors spawn.",
    evidence: [
      ref("chunk_0048.c", "PTR_DAT_80433934[iVar4 + 0xcb] = 0xff"),
      ref("chunk_0048.c", "PTR_DAT_80433934[iVar4 + 0xcb] = 1"),
      ref("chunk_0048.c", "PTR_DAT_80433934[iVar4 + 0x5a] = PTR_DAT_80433934[iVar4 + 0x5a] +"),
      ref("chunk_0048.c", "*(undefined *)(param_9 + 0x88) = PTR_DAT_80433934[*(char *)(param_9 + 0x96) + 0xcb]"),
    ],
    relatedWebModules: ["packages/missions/src/challenge.ts", "packages/combat/src/battle.ts"],
  },
  {
    address: "0x8002bb14",
    inferredName: "battle_frame_target_action_dispatch",
    system: "Per-frame CPU/player shared target and action dispatch",
    summary:
      "Main active actor loop resets slot target/effect state, runs target/contact passes, applies target reactions, and dispatches per-slot action updates.",
    evidence: [
      ref("chunk_0003.c", "*(undefined4 *)(&DAT_803b06a8 + pcVar10[0x3e4] * 4) = 0"),
      ref("chunk_0003.c", "(&DAT_8043612c)[pcVar10[0x3e4]] = 0"),
      ref("chunk_0003.c", "zz_00681e4_((int)pcVar10,(int)(char)(&DAT_8043612c)[pcVar10[0x3e4]])"),
      ref("chunk_0003.c", "zz_006abd4_((int)pcVar10,*(int *)(&DAT_803b06a8 + pcVar10[0x3e4] * 4))"),
      ref("chunk_0003.c", "dVar25 = (double)zz_00680d4_((int)pcVar10,0)"),
    ],
    relatedWebModules: ["packages/combat/src/ai.ts", "packages/combat/src/battle.ts", "packages/combat/src/combat.ts"],
  },
  {
    address: "0x8002cb20",
    inferredName: "mutual_actor_contact_mask_update",
    system: "Actor eligibility / contact mask update",
    summary:
      "Pairwise active actor pass gated by mutual 0x71e/0x71f slot masks before contact-vector update.",
    evidence: [
      ref("chunk_0003.c", "((int)pcVar4[0x71e] & 1 << (int)pcVar3[0x3e4])"),
      ref("chunk_0003.c", "((int)pcVar3[0x71f] & 1 << (int)pcVar4[0x3e4])"),
      ref("chunk_0003.c", "zz_0035ca4_((int)pcVar4,(float *)(pcVar3 + 0x1cc))"),
    ],
    relatedWebModules: ["packages/combat/src/ai.ts", "packages/combat/src/combat.ts"],
  },
  {
    address: "0x8002e2a8",
    inferredName: "resolve_hitbox_target_effects_and_damage",
    system: "Hitbox target effects, target memory, and damage dispatch",
    summary:
      "Shared hit/effect resolver. It writes target pointers, last-enemy markers, effect deltas, damage accounting, knockback direction, base damage, and HP subtraction.",
    evidence: [
      ref("chunk_0003.c", "*(char **)(&DAT_803b06a8 + pcVar16[0x3e4] * 4) = pcVar18"),
      ref("chunk_0003.c", "pcVar18[2000] = pcVar16[0x3e4]"),
      ref("chunk_0003.c", "pcVar18[0x7d1] = '\\x0f'"),
      ref("chunk_0003.c", "(&DAT_8043612c)[pcVar18[0x3e4]]"),
      ref("chunk_0003.c", "zz_00300bc_(param_1,param_2,(int)*(char *)(puVar17 + 7))"),
      ref("chunk_0003.c", "uVar10 = zz_003cd5c_(puVar17,iVar19,pcVar18)"),
      ref("chunk_0003.c", "uVar10 = zz_003d344_((int)pcVar18,(short)uVar10)"),
    ],
    relatedWebModules: ["packages/combat/src/combat.ts", "packages/combat/src/ai.ts"],
  },
  {
    address: "0x800681e4",
    inferredName: "apply_actor_param_tier_delta_63",
    system: "Actor param-tier modifier applied from per-slot effect delta",
    summary:
      "Applies the signed DAT_8043612c slot delta to actor+0x74a with a narrower [-63, 63] clamp, then refreshes table-backed actor params.",
    evidence: [
      ref("chunk_0008.c", "iVar1 = (int)*(char *)(param_1 + 0x74a)"),
      ref("chunk_0008.c", "if (iVar2 < 0x40)"),
      ref("chunk_0008.c", "*(undefined2 *)(param_1 + 0x750) = 900"),
      ref("chunk_0008.c", "zz_006817c_(param_1,iVar1)"),
    ],
    relatedWebModules: ["packages/combat/src/stats.ts", "packages/combat/src/combat.ts"],
  },
  {
    address: "0x8006ab04",
    inferredName: "start_forced_move_to_point",
    system: "Forced move / point reaction",
    summary:
      "Stores a per-slot world target vector and enters a movement/action state. This is evidence for target-vector mechanics, not enough by itself to rename CPU decision code.",
    evidence: [
      ref("chunk_0009.c", "*(undefined4 *)(param_1 + 0x7bc) = *param_2"),
      ref("chunk_0009.c", "*(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x1000"),
      ref("chunk_0009.c", "zz_006a7b4_(param_1,0x23)"),
    ],
    relatedWebModules: ["packages/combat/src/movement.ts", "packages/combat/src/ai.ts"],
  },
  {
    address: "0x8006abd4",
    inferredName: "react_to_slot_target_object",
    system: "Stored target reaction",
    summary:
      "Consumes DAT_803b06a8 target pointer, reads target object type/category, enters status/action state, and plays a side-aware cue.",
    evidence: [
      ref("chunk_0009.c", "if (*(char *)(param_2 + 0x4a0) == '\\0')"),
      ref("chunk_0009.c", "zz_006a868_(param_1,*(undefined2 *)(param_2 + 1000),*(undefined1 *)(param_2 + 0x3ec))"),
      ref("chunk_0009.c", "*(undefined2 *)(param_1 + 0x49a) = 900"),
      ref("chunk_0009.c", "zz_0176ec0_(param_1,*(undefined1 *)(param_1 + 0x88),1)"),
    ],
    relatedWebModules: ["packages/combat/src/ai.ts", "packages/combat/src/combat.ts"],
  },
  {
    address: "0x8010d880",
    inferredName: "set_slot_action_handler",
    system: "Per-slot action handler dispatch",
    summary:
      "Writes a slot's action handler from a 6-entry mode table when the slot is active. This is the final shared dispatch path reached after target/effect resolution.",
    evidence: [
      ref("chunk_0030.c", "PTR_DAT_8043394c[0x30] & 1 << slot_index"),
      ref("chunk_0030.c", "(&DAT_803c735c)[slot_index] = (&PTR_DAT_80325af4)[action_mode % 6]"),
      ref("chunk_0030.c", "(&DAT_803c736c)[slot_index] = 0"),
    ],
    relatedWebModules: ["packages/combat/src/battle.ts", "packages/combat/src/ai.ts"],
  },
];

const fieldAliases = [
  {
    owner: "ActiveBorgObject",
    offset: "0x83",
    inferredName: "action_state",
    confidence: "evidence-backed",
    evidence: [ref("chunk_0003.c", "if (pcVar18[0x83] == '\\0')"), ref("chunk_0003.c", "case '\\x10':")],
  },
  {
    owner: "ActiveBorgObject",
    offset: "0x88",
    inferredName: "match_side_from_slot_table",
    confidence: "confirmed",
    evidence: [ref("chunk_0048.c", "*(undefined *)(param_9 + 0x88) = PTR_DAT_80433934[*(char *)(param_9 + 0x96) + 0xcb]")],
  },
  {
    owner: "ActiveBorgObject",
    offset: "0x3e4",
    inferredName: "active_slot_index",
    confidence: "confirmed",
    evidence: [ref("chunk_0003.c", "pcVar10[0x3e4] * 4"), ref("chunk_0003.c", "1 << (int)pcVar3[0x3e4]")],
  },
  {
    owner: "ActiveBorgObject",
    offset: "0x71e/0x71f",
    inferredName: "mutual_actor_slot_masks",
    confidence: "evidence-backed",
    evidence: [ref("chunk_0003.c", "pcVar4[0x71e] & 1 << (int)pcVar3[0x3e4]"), ref("chunk_0003.c", "pcVar3[0x71f] & 1 << (int)pcVar4[0x3e4]")],
  },
  {
    owner: "ActiveBorgObject",
    offset: "2000 / 0x7d1",
    inferredName: "last_enemy_slot_and_timer",
    confidence: "evidence-backed",
    evidence: [ref("chunk_0003.c", "pcVar18[2000] = pcVar16[0x3e4]"), ref("chunk_0003.c", "pcVar18[0x7d1] = '\\x0f'"), ref("chunk_0003.c", "pcVar10[2000] = -1")],
  },
  {
    owner: "ActiveBorgObject",
    offset: "0x74a/0x74b/0x74c/0x74d/0x74e/0x750",
    inferredName: "param_tier_state",
    confidence: "evidence-backed",
    evidence: [ref("chunk_0008.c", "*(char *)(param_1 + 0x74a)"), ref("chunk_0008.c", "*(char *)(param_1 + 0x74b)"), ref("chunk_0008.c", "*(undefined2 *)(param_1 + 0x750) = 900")],
  },
  {
    owner: "Global",
    offset: "DAT_803b06a8",
    inferredName: "slot_target_object_ptrs",
    confidence: "confirmed",
    evidence: [ref("chunk_0003.c", "*(undefined4 *)(&DAT_803b06a8 + pcVar10[0x3e4] * 4) = 0"), ref("chunk_0003.c", "*(char **)(&DAT_803b06a8 + pcVar16[0x3e4] * 4) = pcVar18"), ref("chunk_0003.c", "zz_006abd4_((int)pcVar10,*(int *)(&DAT_803b06a8 + pcVar10[0x3e4] * 4))")],
  },
  {
    owner: "Global",
    offset: "DAT_8043612c",
    inferredName: "slot_param_tier_delta",
    confidence: "evidence-backed",
    evidence: [ref("chunk_0003.c", "(&DAT_8043612c)[pcVar10[0x3e4]] = 0"), ref("chunk_0003.c", "(&DAT_8043612c)[pcVar18[0x3e4]] ="), ref("chunk_0003.c", "zz_00681e4_((int)pcVar10,(int)(char)(&DAT_8043612c)[pcVar10[0x3e4]])")],
  },
  {
    owner: "Global",
    offset: "DAT_803b06c0/DAT_803b06c4/DAT_803b06c8",
    inferredName: "slot_world_target_vec3",
    confidence: "evidence-backed",
    evidence: [ref("chunk_0003.c", "(&DAT_803b06c0 + iVar11)"), ref("chunk_0003.c", "zz_006ab04_((int)pcVar10")],
  },
  {
    owner: "PTR_DAT_80433934",
    offset: "slot+0xcb / slot+0xcc",
    inferredName: "slot_match_side",
    confidence: "confirmed",
    evidence: [ref("chunk_0048.c", "PTR_DAT_80433934[iVar4 + 0xcb] = 0"), ref("chunk_0048.c", "PTR_DAT_80433934[iVar4 + 0xcc] = 0")],
  },
];

const report = {
  generatedAt: new Date().toISOString(),
  generatedBy: rel(fileURLToPath(import.meta.url)),
  sourceIndex: rel(indexPath),
  principle:
    "CPU AI porting must use original target/action/effect code and confirmed slot/team data. These names are evidence labels; unconfirmed decision-brain code remains unrenamed.",
  classAliases: [
    {
      inferredName: "ActiveBorgObject",
      originalClassName: null,
      confidence: "struct alias only",
      evidence: "Repeated DAT_803c4e84 active loop with 0x1e00 stride and active fields. No original C++ class name confirmed yet.",
    },
    {
      inferredName: "MatchState",
      originalClassName: null,
      confidence: "struct alias only",
      evidence: "PTR_DAT_80433934 carries match/force/slot state, active slot masks, rosters, and per-side values.",
    },
    {
      inferredName: "cTeam",
      originalClassName: "cTeam",
      confidence: "symbol-map confirmed",
      evidence: "0x802a3938 cTeam::GetPlayer(int)",
    },
    {
      inferredName: "cPlayer",
      originalClassName: "cPlayer",
      confidence: "symbol-map confirmed",
      evidence: "0x802807ac cPlayer::ClearSwapControllerTimer(void)",
    },
  ],
  functionAnchors: anchors.map((anchor) => enrichAnchor(anchor)),
  fieldAliases,
  portingNotes: [
    "Do not implement CPU AI as nearest-enemy-only long term. Original code keeps per-slot target object pointers and short-lived last-enemy slot memory.",
    "Keep object+0x88 as match side/team from PTR_DAT_80433934[slot+0xcb]. It is not a borg display type.",
    "DAT_8043612c is an effect-driven signed param-tier delta, not proven CPU desire/input.",
    "The CPU decision-brain function is not fully isolated by this pass; current evidence covers shared target/effect/action dispatch used by CPU and player-controlled actors.",
  ],
};

fs.mkdirSync(outDir, { recursive: true });
fs.writeFileSync(outJson, `${JSON.stringify(report, null, 2)}\n`);
fs.writeFileSync(outMd, renderMarkdown(report));

console.log("cpu ai evidence");
console.log(`anchors: ${report.functionAnchors.length}`);
console.log(`fields: ${report.fieldAliases.length}`);
console.log(`wrote ${rel(outJson)}`);
console.log(`wrote ${rel(outMd)}`);

function enrichAnchor(anchor) {
  const fn = functions.get(anchor.address.toLowerCase());
  return {
    ...anchor,
    currentFunctionName: fn?.currentFunctionName ?? null,
    symbolMapName: fn?.symbolMapName ?? null,
    indexedInferredName: fn?.inferredName ?? null,
    sourceRef: fn?.sourceRef ?? null,
    callers: fn?.callers.slice(0, 12) ?? [],
    callees: fn?.callees.slice(0, 16) ?? [],
    globalReferences: fn?.globalReferences.slice(0, 24) ?? [],
    constants: fn?.constants.slice(0, 32) ?? [],
  };
}

function ref(chunkFile, needle) {
  const full = path.join(exportDir, chunkFile);
  const lines = fs.readFileSync(full, "utf8").split(/\r?\n/);
  const line = lines.findIndex((candidate) => candidate.includes(needle)) + 1;
  return {
    sourceRef: line > 0 ? `research/decomp/ghidra-export/${chunkFile}:${line}` : null,
    needle,
  };
}

function renderMarkdown(data) {
  const lines = [];
  lines.push("# CPU AI / Targeting Evidence");
  lines.push("");
  lines.push(`Generated: ${data.generatedAt}`);
  lines.push("");
  lines.push("## Principle");
  lines.push("");
  lines.push(data.principle);
  lines.push("");
  lines.push("## Function Anchors");
  lines.push("");
  lines.push("| Address | Current name | Inferred name | System | Source |");
  lines.push("| --- | --- | --- | --- | --- |");
  for (const fn of data.functionAnchors) {
    lines.push(
      `| ${fn.address} | \`${fn.currentFunctionName ?? ""}\` | \`${fn.inferredName}\` | ${fn.system} | \`${fn.sourceRef ?? ""}\` |`,
    );
  }
  lines.push("");
  for (const fn of data.functionAnchors) {
    lines.push(`### ${fn.address} ${fn.inferredName}`);
    lines.push("");
    lines.push(fn.summary);
    lines.push("");
    lines.push(`- Current function: \`${fn.currentFunctionName ?? ""}\``);
    lines.push(`- Callers: ${fn.callers.map((caller) => `${caller.address} \`${caller.name}\``).join(", ") || "none indexed"}`);
    lines.push(`- Callees: ${fn.callees.map((callee) => `${callee.address} \`${callee.name}\``).join(", ") || "none indexed"}`);
    lines.push(`- Related web modules: ${fn.relatedWebModules.map((module) => `\`${module}\``).join(", ")}`);
    lines.push("- Evidence:");
    for (const item of fn.evidence) lines.push(`  - \`${item.sourceRef ?? "not found"}\` contains \`${item.needle}\``);
    lines.push("");
  }
  lines.push("## Field / Struct Aliases");
  lines.push("");
  lines.push("| Owner | Offset/global | Inferred name | Confidence | Evidence |");
  lines.push("| --- | --- | --- | --- | --- |");
  for (const field of data.fieldAliases) {
    lines.push(
      `| ${field.owner} | \`${field.offset}\` | \`${field.inferredName}\` | ${field.confidence} | ${field.evidence.map((item) => `\`${item.sourceRef ?? "not found"}\``).join("<br>")} |`,
    );
  }
  lines.push("");
  lines.push("## Class Aliases");
  lines.push("");
  for (const alias of data.classAliases) {
    lines.push(`- \`${alias.inferredName}\`: ${alias.confidence}; ${alias.evidence}`);
  }
  lines.push("");
  lines.push("## Porting Notes");
  lines.push("");
  for (const note of data.portingNotes) lines.push(`- ${note}`);
  lines.push("");
  return `${lines.join("\n")}\n`;
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll("\\", "/");
}
