// =============================================================================
// tev.ts — the TEV combiner: GX pipeline state translated into a GLSL shader.
//
// WHY THIS FILE EXISTS. The Flipper's fragment stage is not a fixed blend of
// texture and vertex colour: it is a chain of up to 16 stages, each computing
//
//     out = (d  (+/-)  ((1 - c) * a + c * b)  +  bias) * scale
//
// over four selectable inputs, with per-stage konstant selection, per-stage
// channel/texture swap tables, four shared colour registers that stages read
// and write, and an alternative compare mode. `docs/gx-hle-host.md` named this
// "the largest single block of unimplemented entry points and the one most
// responsible for the frame looking wrong rather than empty", because a host
// that ignores it draws every multi-stage and every textured effect as a flat
// vertex colour. This module turns the latched TEV state into a generated
// fragment shader, which is the only faithful way to express it — there is no
// fixed-function GL state that encodes a programmable combiner.
//
// PROVENANCE. The register packings that settle the field widths, the field
// positions and the argument orders are read out of this game's own decompiled
// SDK (research/decomp/ghidra-export/chunk_0067.c) and are labelled [CORPUS] at
// each enum in enums.ts. What the corpus CANNOT show is what a given field
// value means to the silicon, and the combiner equation itself is nowhere in
// the decompiled bodies — those parts are [SDK] and are marked here too.
//
// CLAIM BAR, unchanged: framebuffer-equivalent, never pixel-identical. The GX
// TEV computes in a signed 10-bit fixed-point space with hardware-defined
// rounding at every stage; this generates float math. Even a TEV translation
// that is structurally exact is not bit-exact, and nothing here has ever been
// compared against a captured GameCube frame.
// =============================================================================

import {
  GXAlphaOp,
  GXChannelID,
  GXCompare,
  GXTevAlphaArg,
  GXTevBias,
  GXTevColorArg,
  GXTevKColorSel,
  GXTevMode,
  GXTevOp,
  GXTevRegID,
  GXTevScale,
  GX_TEXMAP_NULL,
} from "./enums.js";

/** The output half of one TEV stage — colour or alpha. */
export interface GxTevOpState {
  /** GXTevOp. Values >= 2 are the compare ops. */
  op: number;
  /** GXTevBias. Ignored for compare ops (the hardware forces the field to 3). */
  bias: number;
  /** GXTevScale. Doubles as the compare-width field for compare ops. */
  scale: number;
  clamp: boolean;
  /** GXTevRegID this stage writes. */
  outReg: number;
}

/** One TEV stage, exactly the state the ROM can program per stage. */
export interface GxTevStage {
  /** GXSetTevOrder texmap, or GX_TEXMAP_NULL when the stage samples nothing. */
  texMap: number;
  /** GXSetTevOrder texcoord id (0..7), or 0xff for GX_TEXCOORD_NULL. */
  texCoord: number;
  /** GXSetTevOrder rasterized colour channel (GXChannelID). */
  channel: number;
  /** GXSetTevColorIn (a, b, c, d) as GXTevColorArg. */
  colorIn: [number, number, number, number];
  /** GXSetTevAlphaIn (a, b, c, d) as GXTevAlphaArg. */
  alphaIn: [number, number, number, number];
  colorOp: GxTevOpState;
  alphaOp: GxTevOpState;
  /** GXSetTevKColorSel. */
  kColorSel: number;
  /** GXSetTevKAlphaSel. */
  kAlphaSel: number;
  /** GXSetTevSwapMode ras_sel (index into the swap table). */
  rasSwap: number;
  /** GXSetTevSwapMode tex_sel. */
  texSwap: number;
}

/** GXSetAlphaCompare state. */
export interface GxAlphaCompare {
  comp0: number;
  ref0: number;
  op: number;
  comp1: number;
  ref1: number;
}

export const DEFAULT_ALPHA_COMPARE: GxAlphaCompare = {
  comp0: GXCompare.ALWAYS,
  ref0: 0,
  op: GXAlphaOp.AND,
  comp1: GXCompare.ALWAYS,
  ref1: 0,
};

/** One row of the TEV swap table: which source channel each output takes. */
export type GxSwapRow = [number, number, number, number];

/**
 * The SDK's reset swap table: four rows, the first an identity.
 * [SDK] — GXInit's table contents are not in the decompiled export. The
 * identity row is forced rather than guessed: an un-programmed swap must not
 * permute anything, because a permuting default would silently recolour every
 * draw in the game.
 */
export const DEFAULT_SWAP_TABLE: GxSwapRow[] = [
  [0, 1, 2, 3],
  [0, 0, 0, 3],
  [1, 1, 1, 3],
  [2, 2, 2, 3],
];

const passthroughOp = (): GxTevOpState => ({
  op: GXTevOp.ADD,
  bias: GXTevBias.ZERO,
  scale: GXTevScale.SCALE_1,
  clamp: true,
  outReg: GXTevRegID.TEVPREV,
});

/**
 * Expand `GXSetTevOp(stage, mode)` into the stage state it installs.
 *
 * The STRUCTURE is corpus-settled: gnt4_GXSetTevOp_bl @0x80229bac selects
 * between two table pairs on `stage == 0`, and the pairs are five entries
 * apart. The stage-0 pair feeds the RASTERIZED colour into the combiner while
 * the other pair feeds the PREVIOUS stage's output, which is what that branch
 * is for. The five modes' actual input tuples live in ROM data
 * (DAT_803aad30 / DAT_803aad58) that is not in the C export, so the tuples
 * below are the documented SDK expansions — [SDK], corroborated only by the
 * fact that the ROM pairs mode 4 exclusively with GX_TEXMAP_NULL and mode 0
 * exclusively with a real texmap (see GXTevMode in enums.ts).
 */
export function tevStageFromOp(base: GxTevStage, stage: number, mode: number): GxTevStage {
  const cArg = stage === 0 ? GXTevColorArg.RASC : GXTevColorArg.CPREV;
  const aArg = stage === 0 ? GXTevAlphaArg.RASA : GXTevAlphaArg.APREV;
  const Z = GXTevColorArg.ZERO;
  const AZ = GXTevAlphaArg.ZERO;
  let colorIn: [number, number, number, number];
  let alphaIn: [number, number, number, number];
  switch (mode) {
    case GXTevMode.MODULATE:
      colorIn = [Z, GXTevColorArg.TEXC, cArg, Z];
      alphaIn = [AZ, GXTevAlphaArg.TEXA, aArg, AZ];
      break;
    case GXTevMode.DECAL:
      colorIn = [cArg, GXTevColorArg.TEXC, GXTevColorArg.TEXA, Z];
      alphaIn = [aArg, AZ, AZ, AZ];
      break;
    case GXTevMode.BLEND:
      colorIn = [cArg, GXTevColorArg.ONE, GXTevColorArg.TEXC, Z];
      alphaIn = [AZ, GXTevAlphaArg.TEXA, aArg, AZ];
      break;
    case GXTevMode.REPLACE:
      colorIn = [Z, Z, Z, GXTevColorArg.TEXC];
      alphaIn = [AZ, AZ, AZ, GXTevAlphaArg.TEXA];
      break;
    case GXTevMode.PASSCLR:
      colorIn = [Z, Z, Z, cArg];
      alphaIn = [AZ, AZ, AZ, aArg];
      break;
    default:
      // The corpus proves there are exactly five modes (the two table pairs
      // are 5 entries apart). A sixth is the ROM and the host disagreeing, so
      // it must not be silently absorbed.
      throw new Error(
        `GXSetTevOp: mode ${mode} is outside the 5-entry table the ROM's own ` +
          `gnt4_GXSetTevOp_bl indexes (0..4) — refusing to guess a combiner program`,
      );
  }
  return { ...base, colorIn, alphaIn, colorOp: passthroughOp(), alphaOp: passthroughOp() };
}

/**
 * A freshly reset TEV stage.
 *
 * Defaulted to the `GXSetTevOp(stage, GX_PASSCLR)` expansion — the rasterized
 * colour passed straight through. That is deliberate and it is the LEAST
 * flattering safe choice available: it reproduces exactly what this host drew
 * before the TEV existed, so an un-programmed draw cannot change appearance
 * merely because the combiner landed. It is NOT a claim about GXInit's reset
 * state, which the corpus does not show.
 */
export function defaultTevStage(stage: number): GxTevStage {
  const base: GxTevStage = {
    texMap: GX_TEXMAP_NULL,
    texCoord: 0xff,
    channel: GXChannelID.COLOR0A0,
    colorIn: [0, 0, 0, 0],
    alphaIn: [0, 0, 0, 0],
    colorOp: passthroughOp(),
    alphaOp: passthroughOp(),
    kColorSel: GXTevKColorSel.CONST_1,
    kAlphaSel: GXTevKColorSel.CONST_1,
    rasSwap: 0,
    texSwap: 0,
  };
  return tevStageFromOp(base, stage, GXTevMode.PASSCLR);
}

// =============================================================================
// Shader generation
// =============================================================================

/** Everything the generated fragment shader depends on. */
export interface GxTevShaderConfig {
  numTevStages: number;
  stages: GxTevStage[];
  swapTable: GxSwapRow[];
  alphaCompare: GxAlphaCompare;
  /** Number of texgen outputs the vertex stage produces (GXSetNumTexGens). */
  numTexGens: number;
  /** Number of colour channels the vertex stage produces (GXSetNumChans). */
  numChans: number;
  /** Texmap slots that actually have a decoded texture bound. A stage that
   *  selects an unbound map must NOT quietly sample black — it is reported. */
  boundTexMaps: readonly boolean[];
}

/** What a generated program needs at draw time, and what it could not honour. */
export interface GxTevShaderResult {
  key: string;
  fragmentSource: string;
  /** Texmap units the shader samples, so the caller binds exactly those. */
  sampledTexMaps: number[];
  /** Deviations this translation made. Never empty just because it compiled. */
  diagnostics: string[];
}

const SWZ = ["r", "g", "b", "a"];

function swizzle(expr: string, row: GxSwapRow): string {
  if (row[0] === 0 && row[1] === 1 && row[2] === 2 && row[3] === 3) return expr;
  const sel = row.map((c) => SWZ[c & 3] ?? "r").join("");
  return `(${expr}).${sel}`;
}

/**
 * The konstant selector table.
 *
 * Values 0x00-0x07 are the eight documented fractional constants, 0x0c-0x0f
 * select a konst register's RGB, and 0x10-0x1f select one component of one
 * konst register broadcast across all three. Width is [CORPUS] (5 bits, from
 * gnt4_GXSetTevKColorSel_bl); the mapping of value to constant is [SDK],
 * corroborated by the ROM selecting 0x0c..0x0f for stages 0..3's colours and
 * 0x1c..0x1f for the same stages' alphas.
 */
function konstColorExpr(sel: number): string | null {
  if (sel >= 0 && sel <= 7) {
    const v = (8 - sel) / 8;
    return `vec3(${v.toFixed(6)})`;
  }
  if (sel >= GXTevKColorSel.K0 && sel <= GXTevKColorSel.K3) return `uKonst[${sel - GXTevKColorSel.K0}].rgb`;
  if (sel >= 0x10 && sel <= 0x1f) {
    const comp = SWZ[(sel - 0x10) >> 2] ?? "r";
    return `vec3(uKonst[${(sel - 0x10) & 3}].${comp})`;
  }
  return null;
}

function konstAlphaExpr(sel: number): string | null {
  if (sel >= 0 && sel <= 7) return ((8 - sel) / 8).toFixed(6);
  if (sel >= 0x10 && sel <= 0x1f) {
    const comp = SWZ[(sel - 0x10) >> 2] ?? "r";
    return `uKonst[${(sel - 0x10) & 3}].${comp}`;
  }
  // 0x08-0x0b are reserved and 0x0c-0x0f (the RGB selectors) are not legal for
  // alpha: a three-component konst has no single alpha. Refuse rather than
  // pick a channel.
  return null;
}

const COLOR_ARG_EXPR: Record<number, string> = {
  [GXTevColorArg.CPREV]: "tevPrev.rgb",
  [GXTevColorArg.APREV]: "vec3(tevPrev.a)",
  [GXTevColorArg.C0]: "tevReg0.rgb",
  [GXTevColorArg.A0]: "vec3(tevReg0.a)",
  [GXTevColorArg.C1]: "tevReg1.rgb",
  [GXTevColorArg.A1]: "vec3(tevReg1.a)",
  [GXTevColorArg.C2]: "tevReg2.rgb",
  [GXTevColorArg.A2]: "vec3(tevReg2.a)",
  [GXTevColorArg.TEXC]: "texColor.rgb",
  [GXTevColorArg.TEXA]: "vec3(texColor.a)",
  [GXTevColorArg.RASC]: "rasColor.rgb",
  [GXTevColorArg.RASA]: "vec3(rasColor.a)",
  [GXTevColorArg.ONE]: "vec3(1.0)",
  [GXTevColorArg.HALF]: "vec3(0.5)",
  [GXTevColorArg.KONST]: "konstColor",
  [GXTevColorArg.ZERO]: "vec3(0.0)",
};

const ALPHA_ARG_EXPR: Record<number, string> = {
  [GXTevAlphaArg.APREV]: "tevPrev.a",
  [GXTevAlphaArg.A0]: "tevReg0.a",
  [GXTevAlphaArg.A1]: "tevReg1.a",
  [GXTevAlphaArg.A2]: "tevReg2.a",
  [GXTevAlphaArg.TEXA]: "texColor.a",
  [GXTevAlphaArg.RASA]: "rasColor.a",
  [GXTevAlphaArg.KONST]: "konstAlpha",
  [GXTevAlphaArg.ZERO]: "0.0",
};

const BIAS_TERM: Record<number, string> = {
  [GXTevBias.ZERO]: "",
  [GXTevBias.ADDHALF]: " + 0.5",
  [GXTevBias.SUBHALF]: " - 0.5",
};

const SCALE_FACTOR: Record<number, number> = {
  [GXTevScale.SCALE_1]: 1,
  [GXTevScale.SCALE_2]: 2,
  [GXTevScale.SCALE_4]: 4,
  [GXTevScale.DIVIDE_2]: 0.5,
};

const REG_NAME = ["tevPrev", "tevReg0", "tevReg1", "tevReg2"];

/**
 * The compare ops' comparison width.
 *
 * The ENCODING is corpus-settled (gnt4_GXSetTevColorOp_bl forces bias to 3 and
 * routes `op & 6` into the scale field), the MEANING of each width value is
 * [SDK]. `gt` comes from the op's low bit, which the same body routes to the
 * register's subtract bit.
 */
function compareExpr(op: number, alpha: boolean): { cond: string; note: string | null } {
  const gt = (op & 1) === 0;
  const cmp = gt ? ">" : "==";
  if (alpha) {
    // The alpha combiner only has the 8-bit comparison.
    return { cond: `(cmpA ${cmp} cmpB)`, note: null };
  }
  switch (op & 6) {
    case 2:
      return { cond: `(cmpA.r ${cmp} cmpB.r)`, note: null };
    case 4:
      return { cond: `(dot(cmpA.rg, vec2(1.0, 256.0)) ${cmp} dot(cmpB.rg, vec2(1.0, 256.0)))`, note: null };
    case 6:
      return {
        cond: `(dot(cmpA, vec3(1.0, 256.0, 65536.0)) ${cmp} dot(cmpB, vec3(1.0, 256.0, 65536.0)))`,
        note: null,
      };
    default:
      // RGB8: the hardware compares each channel independently and selects
      // per-channel. Expressed with a mix() below rather than a scalar branch.
      return { cond: "PERCHANNEL", note: null };
  }
}

function compareFunc(func: number): string | null {
  switch (func) {
    case GXCompare.NEVER:
      return "false";
    case GXCompare.LESS:
      return "(a < r)";
    case GXCompare.EQUAL:
      return "(a == r)";
    case GXCompare.LEQUAL:
      return "(a <= r)";
    case GXCompare.GREATER:
      return "(a > r)";
    case GXCompare.NEQUAL:
      return "(a != r)";
    case GXCompare.GEQUAL:
      return "(a >= r)";
    case GXCompare.ALWAYS:
      return "true";
    default:
      return null;
  }
}

/**
 * Generate the fragment shader for one TEV configuration.
 *
 * Deterministic in its input, so `key` is a sound program-cache key.
 */
export function generateTevShader(config: GxTevShaderConfig): GxTevShaderResult {
  const diagnostics: string[] = [];
  const sampled = new Set<number>();
  const stageCount = Math.max(1, Math.min(config.numTevStages, 16));
  if (config.numTevStages > 16) {
    diagnostics.push(
      `GXSetNumTevStages(${config.numTevStages}) exceeds the hardware's 16 stages — only 16 were generated`,
    );
  }
  const body: string[] = [];

  for (let i = 0; i < stageCount; i++) {
    const stage = config.stages[i];
    if (!stage) {
      diagnostics.push(`TEV stage ${i} is inside GXSetNumTevStages but was never programmed — treated as pass-through`);
      continue;
    }
    body.push(`  // ---- TEV stage ${i} ----`);

    // --- the rasterized colour this stage reads ---------------------------
    let ras = "vec4(0.0)";
    if (stage.channel === GXChannelID.COLOR0 || stage.channel === GXChannelID.COLOR0A0) ras = "vChan0";
    else if (stage.channel === GXChannelID.COLOR1 || stage.channel === GXChannelID.COLOR1A1) ras = "vChan1";
    else if (stage.channel === GXChannelID.ALPHA0) ras = "vec4(vChan0.a)";
    else if (stage.channel === GXChannelID.ALPHA1) ras = "vec4(vChan1.a)";
    else if (stage.channel !== GXChannelID.NULL_CHAN) {
      diagnostics.push(`TEV stage ${i}: unknown rasterized channel ${stage.channel} — read as zero`);
    }
    const rasRow = config.swapTable[stage.rasSwap & 3] ?? DEFAULT_SWAP_TABLE[0];
    body.push(`  rasColor = ${swizzle(ras, rasRow as GxSwapRow)};`);

    // --- the texture this stage samples ------------------------------------
    if (stage.texMap === GX_TEXMAP_NULL || stage.texCoord > 7) {
      body.push("  texColor = vec4(0.0);");
    } else if (!config.boundTexMaps[stage.texMap]) {
      // LOUD: the stage asked for a texture the host has not uploaded. Drawing
      // it as black is a wrong frame that renders, so it is named.
      diagnostics.push(
        `TEV stage ${i} selects GX_TEXMAP${stage.texMap} but no decoded texture is bound to that slot — sampled as transparent black`,
      );
      body.push("  texColor = vec4(0.0);");
    } else if (stage.texCoord >= config.numTexGens) {
      diagnostics.push(
        `TEV stage ${i} reads GX_TEXCOORD${stage.texCoord} but GXSetNumTexGens declared only ${config.numTexGens} — sampled at (0,0)`,
      );
      sampled.add(stage.texMap);
      body.push(`  texColor = texture(uTex${stage.texMap}, vec2(0.0));`);
    } else {
      sampled.add(stage.texMap);
      const tc = `vTexCoord${stage.texCoord}`;
      body.push(`  texColor = texture(uTex${stage.texMap}, ${tc}.xy / max(${tc}.z, 1e-6));`);
    }
    const texRow = config.swapTable[stage.texSwap & 3] ?? DEFAULT_SWAP_TABLE[0];
    body.push(`  texColor = ${swizzle("texColor", texRow as GxSwapRow)};`);

    // --- konstants ----------------------------------------------------------
    const kc = konstColorExpr(stage.kColorSel);
    if (kc === null) {
      diagnostics.push(
        `TEV stage ${i}: konst colour selector 0x${stage.kColorSel.toString(16)} is not a documented GXTevKColorSel — read as zero rather than guessed`,
      );
    }
    body.push(`  konstColor = ${kc ?? "vec3(0.0)"};`);
    const ka = konstAlphaExpr(stage.kAlphaSel);
    if (ka === null) {
      diagnostics.push(
        `TEV stage ${i}: konst alpha selector 0x${stage.kAlphaSel.toString(16)} is not a documented GXTevKAlphaSel — read as zero rather than guessed`,
      );
    }
    body.push(`  konstAlpha = ${ka ?? "0.0"};`);

    // --- colour combine -----------------------------------------------------
    body.push(...emitCombine(i, stage, false, diagnostics));
    // --- alpha combine ------------------------------------------------------
    body.push(...emitCombine(i, stage, true, diagnostics));
  }

  // --- alpha compare (GXSetAlphaCompare) -----------------------------------
  const ac = config.alphaCompare;
  const c0 = compareFunc(ac.comp0);
  const c1 = compareFunc(ac.comp1);
  let alphaTest = "";
  if (c0 === null || c1 === null) {
    diagnostics.push(
      `GXSetAlphaCompare uses compare function(s) ${ac.comp0}/${ac.comp1} the host does not translate — the alpha test was NOT applied`,
    );
  } else if (!(ac.comp0 === GXCompare.ALWAYS && ac.comp1 === GXCompare.ALWAYS)) {
    const t0 = c0.replace(/\ba\b/g, "tevPrev.a").replace(/\br\b/g, (ac.ref0 / 255).toFixed(6));
    const t1 = c1.replace(/\ba\b/g, "tevPrev.a").replace(/\br\b/g, (ac.ref1 / 255).toFixed(6));
    const combine =
      ac.op === GXAlphaOp.AND
        ? `(${t0} && ${t1})`
        : ac.op === GXAlphaOp.OR
          ? `(${t0} || ${t1})`
          : ac.op === GXAlphaOp.XOR
            ? `(${t0} != ${t1})`
            : `(${t0} == ${t1})`;
    alphaTest = `  if (!${combine}) discard;\n`;
  }

  const texUniforms = [...sampled]
    .sort((a, b) => a - b)
    .map((m) => `uniform sampler2D uTex${m};`)
    .join("\n");
  const coordVaryings = Array.from(
    { length: Math.max(0, Math.min(config.numTexGens, 8)) },
    (_, i) => `in vec3 vTexCoord${i};`,
  ).join("\n");

  const fragmentSource = `#version 300 es
precision highp float;
precision highp sampler2D;
in vec4 vChan0;
in vec4 vChan1;
${coordVaryings}
${texUniforms}
uniform vec4 uKonst[4];
uniform vec4 uTevReg[4];
out vec4 outColor;

void main() {
  vec4 tevPrev = uTevReg[0];
  vec4 tevReg0 = uTevReg[1];
  vec4 tevReg1 = uTevReg[2];
  vec4 tevReg2 = uTevReg[3];
  vec4 rasColor = vec4(0.0);
  vec4 texColor = vec4(0.0);
  vec3 konstColor = vec3(0.0);
  float konstAlpha = 0.0;
  vec3 cA, cB, cC, cD, cmpA, cmpB;
  float aA, aB, aC, aD, cmpAa, cmpBa;
${body.join("\n")}
  outColor = tevPrev;
${alphaTest}}
`;

  return {
    key: fragmentSource,
    fragmentSource,
    sampledTexMaps: [...sampled].sort((a, b) => a - b),
    diagnostics,
  };
}

/**
 * Emit one half (colour or alpha) of one stage.
 *
 * The equation is the documented GX combiner. It is [SDK]: no decompiled body
 * in this corpus computes it — the SDK only packs selector indices into BP
 * registers and the arithmetic happens in silicon.
 */
function emitCombine(index: number, stage: GxTevStage, alpha: boolean, diagnostics: string[]): string[] {
  const out: string[] = [];
  const op = alpha ? stage.alphaOp : stage.colorOp;
  const args = alpha ? stage.alphaIn : stage.colorIn;
  const table = alpha ? ALPHA_ARG_EXPR : COLOR_ARG_EXPR;
  const names = alpha ? ["aA", "aB", "aC", "aD"] : ["cA", "cB", "cC", "cD"];
  const dst = REG_NAME[op.outReg & 3] ?? "tevPrev";
  const field = alpha ? "a" : "rgb";
  const zero = alpha ? "0.0" : "vec3(0.0)";

  for (let i = 0; i < 4; i++) {
    const sel = args[i] ?? 0;
    const expr = table[sel];
    if (expr === undefined) {
      diagnostics.push(
        `TEV stage ${index} ${alpha ? "alpha" : "colour"} input ${"abcd"[i]}: selector ${sel} is outside the documented ` +
          `GXTev${alpha ? "Alpha" : "Color"}Arg range — read as zero rather than guessed`,
      );
      out.push(`  ${names[i]} = ${zero};`);
    } else {
      out.push(`  ${names[i]} = ${expr};`);
    }
  }

  if (op.op >= GXTevOp.COMP_R8_GT) {
    // Compare mode. The hardware ignores bias and scale here — the corpus
    // proves it, because gnt4_GXSetTevColorOp_bl overwrites the bias field
    // with 3 and puts the comparison width into the scale field.
    out.push(`  ${alpha ? "cmpAa" : "cmpA"} = ${names[0]};`);
    out.push(`  ${alpha ? "cmpBa" : "cmpB"} = ${names[1]};`);
    if (alpha) {
      const gt = (op.op & 1) === 0;
      out.push(`  ${dst}.a = aD + ((cmpAa ${gt ? ">" : "=="} cmpBa) ? aC : 0.0);`);
    } else {
      const { cond } = compareExpr(op.op, false);
      if (cond === "PERCHANNEL") {
        const gt = (op.op & 1) === 0;
        out.push(
          `  ${dst}.rgb = cD + mix(vec3(0.0), cC, vec3(${gt ? "greaterThan" : "equal"}(cmpA, cmpB)));`,
        );
      } else {
        out.push(`  ${dst}.rgb = cD + (${cond} ? cC : vec3(0.0));`);
      }
    }
  } else {
    const sign = op.op === GXTevOp.SUB ? "-" : "+";
    const bias = BIAS_TERM[op.bias] ?? "";
    if (op.bias === GXTevBias.COMPARE) {
      // bias == 3 with a non-compare op is a state the hardware cannot hold;
      // the corpus shows the SDK only ever writes 3 on the compare path.
      diagnostics.push(
        `TEV stage ${index} ${alpha ? "alpha" : "colour"}: bias field is 3 (the hardware's compare marker) on an ` +
          `ADD/SUB op — the bias was dropped`,
      );
    }
    const scale = SCALE_FACTOR[op.scale] ?? 1;
    const mixExpr = alpha
      ? `mix(aA, aB, aC)`
      : `mix(cA, cB, cC)`;
    const d = names[3];
    const expr = `(${d} ${sign} ${mixExpr}${bias})${scale === 1 ? "" : ` * ${scale.toFixed(1)}`}`;
    // Clamp semantics: when the stage clamps, GX clamps the result to [0,1].
    // When it does not, the value stays in the signed 10-bit register range,
    // which this approximates as [-4, 4) — the range those registers can hold.
    const clamped = op.clamp
      ? `clamp(${expr}, ${alpha ? "0.0" : "vec3(0.0)"}, ${alpha ? "1.0" : "vec3(1.0)"})`
      : `clamp(${expr}, ${alpha ? "-4.0" : "vec3(-4.0)"}, ${alpha ? "4.0" : "vec3(4.0)"})`;
    out.push(`  ${dst}.${field} = ${clamped};`);
  }
  return out;
}
