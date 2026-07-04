#!/usr/bin/env node
// Generate packages/combat/src/data/actionStreamTables.json: per borg -> per
// (actionIndex +0x580, variantIndex +0x581) -> {bank, group, seedSlot, airSeedSlot,
// chainCallback, engine, config, evidence} for the melee/charge/dash action-script
// stream selection chain.
//
// Source chain (research/decomp/cue-script-stream-decode-2026-07-04.md, "Fleet
// extraction recipe"):
// - cue table at actor+0x4f0 maps cueId -> [fullBodyState(+0x5da), upperBodyState(+0x5db)]
//   (zz_006a6fc_/zz_006a750_, chunk_0009.c:835-880). Full-body states dispatch through
//   PTR_LAB_802d36a8 (FUN_80055568, chunk_0006.c:7793-7798); state 61 = FUN_80065dfc =
//   `(**(actor+0x4b4))()` (chunk_0008.c:2724-2731) - the per-family attack virtual.
// - the +0x4b4 virtual dispatches a jump table indexed by actor+0x580 (actionIndex),
//   handlers dispatch per-borg-id variant tables indexed by actor+0x581 (e.g. G RED root
//   zz_018d24c_ chunk_0046.c:5063, a1 FUN_8018dd9c chunk_0047.c:283-291), leaves load a
//   static config into r4 and call a shared engine which dispatches phaseTable[+0x540];
//   phase 0 seeds actor+0x6ea from the config and plays the stream via
//   zz_004beb8_(rate, actor, 0xf, group, slot) (chunk_0006.c:1445-1490, r3=actor r4=mask
//   r5=group r6=slot; group 3 = melee strikes, 4 = charge/air specials, 2 = dash rams).
// - airborne selection reads (actor+0x5e0 & 0x40): FUN_80179850 chunk_0044.c:3934-3936
//   (seed = config[1] when set), zz_007454c_ chunk_0010.c:1687 (slot = airborne ? 1 : 0).
// - chain callbacks live inside the config struct (config+0x10 invoked by FUN_801780e4
//   chunk_0044.c:3141-3143, config+0x14 by FUN_80177fd4 chunk_0044.c:3094-3096) and may
//   override +0x581 (FUN_8018ded0 chunk_0047.c:335-341: re-issue command, +0x581 = 6).
//
// Method: concrete PowerPC emulation of the DOL text against a synthetic actor with
// +0x580/+0x581/+0x3e8 preset per (borg, actionIndex, variantIndex); every
// zz_004beb8_(mask==0xf) call reached is captured with slot-byte provenance. Unknown
// branches fork (bounded); branches on (+0x5e0 & 0x40) are labelled ground/air.
//
// Usage: node scripts/gen-action-stream-tables.mjs [GG4E]
import fs from "node:fs";
import path from "node:path";

const repoRoot = path.resolve(".");
const region = process.argv[2] ?? "GG4E";
const DOL_PATH = path.join(repoRoot, "user-data", region, "disc", "sys", "boot.dol");
const CMD_PATH = path.join(repoRoot, "packages", "combat", "src", "data", "commandMoveTables.json");
const MELEE_PATH = path.join(repoRoot, "packages", "combat", "src", "data", "meleeAnimKinds.json");
const OUT_PATH = path.join(repoRoot, "packages", "combat", "src", "data", "actionStreamTables.json");
const REPORT = "research/decomp/cue-script-stream-decode-2026-07-04.md";

const dol = fs.readFileSync(DOL_PATH);
const cmd = JSON.parse(fs.readFileSync(CMD_PATH, "utf8"));
const melee = JSON.parse(fs.readFileSync(MELEE_PATH, "utf8"));

// ---------- DOL section mapping (as scripts/scan-damage-table-bindings.mjs) ----------
const sectionOffsets = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(i * 4));
const sectionAddresses = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x48 + i * 4));
const sectionSizes = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x90 + i * 4));
function offsetFor(a) {
  a = a >>> 0;
  for (let i = 0; i < 18; i++)
    if (sectionSizes[i] > 0 && a >= sectionAddresses[i] && a < sectionAddresses[i] + sectionSizes[i])
      return sectionOffsets[i] + (a - sectionAddresses[i]);
  return null;
}
function isText(a) {
  a = a >>> 0;
  for (let i = 0; i < 7; i++)
    if (sectionSizes[i] > 0 && a >= sectionAddresses[i] && a < sectionAddresses[i] + sectionSizes[i]) return true;
  return false;
}
const readU32 = (a) => {
  const o = offsetFor(a);
  return o === null ? null : dol.readUInt32BE(o);
};
const readU8 = (a) => {
  const o = offsetFor(a);
  return o === null ? null : dol.readUInt8(o);
};
const readS16 = (a) => {
  const o = offsetFor(a);
  return o === null ? null : dol.readInt16BE(o);
};
const sign16 = (v) => (v & 0x8000 ? (v & 0xffff) - 0x10000 : v & 0xffff);
const hex = (v) => "0x" + (v >>> 0).toString(16);

// ---------- constants ----------
const BEB8 = 0x8004beb8; // zz_004beb8_ stream player (chunk_0006.c:1431)
const FULL_STATE_TABLE = 0x802d36a8; // PTR_LAB_802d36a8 (chunk_0006.c:7798)
const ACTOR = 0x7e000000;
const ACTOR_SIZE = 0x4000;
const STACK = 0x7f0f0000;
const SENTINEL = 0x7ffffffc;
const AIRBORNE_OFFSET = 0x5e0;
const AIRBORNE_MASK = 0x40;

// run caps
const MAX_PATHS = 256;
const MAX_STEPS_TOTAL = 500000;
const MAX_STEPS_PATH = 40000;
const MAX_FUNC_DEPTH = 24;

// ---------- discover the full-body states that invoke actor+0x4b4 ----------
// FUN_80065dfc = `(**(code **)(actor + 0x4b4))()`; find every state slot whose handler
// loads +0x4b4 and bctr's within its first instructions.
function readsVirtual4b4(fn) {
  if (!isText(fn)) return false;
  let saw4b4 = false;
  for (let pc = fn; pc < fn + 0x60; pc += 4) {
    const w = readU32(pc);
    if (w === null) return false;
    const op = w >>> 26;
    if (op === 32 && ((w >>> 16) & 31) === 3 && sign16(w) === 0x4b4) saw4b4 = true;
    if ((w & 0xfc0007fe) === 0x4c000420 && saw4b4) return true; // bcctr
    if ((w & 0xfc0007fe) === 0x4c000020 && ((w >>> 21) & 31) === 20) return false; // blr
  }
  return false;
}
const virtualStates = [];
for (let s = 0; s < 0x50; s++) {
  const fn = readU32(FULL_STATE_TABLE + s * 4);
  if (fn !== null && readsVirtual4b4(fn)) virtualStates.push(s);
}
if (!virtualStates.includes(61)) {
  console.error("gen-action-stream-tables: state 61 does not read +0x4b4; chain broken");
  process.exit(1);
}

// ---------- small-data registers (r2/r13) from __init_registers ----------
const dolEntry = dol.readUInt32BE(0xe0);
let R2 = null;
let R13 = null;
{
  // scan the first instructions reachable from the entry (entry usually bl's
  // __init_registers first; scan entry and its first bl target)
  const scan = (base) => {
    const hi = {};
    for (let pc = base; pc < base + 0x100; pc += 4) {
      const w = readU32(pc);
      if (w === null) break;
      const op = w >>> 26;
      const rt = (w >>> 21) & 31;
      if (op === 15 && ((w >>> 16) & 31) === 0) hi[rt] = (w & 0xffff) << 16;
      else if (op === 24 && hi[(w >>> 21) & 31] !== undefined) {
        // ori rt,rs,imm with rs==rt from lis
        const rs = (w >>> 21) & 31;
        const ra = (w >>> 16) & 31;
        if ((ra === 2 || ra === 13) && hi[rs] !== undefined) {
          const v = (hi[rs] | (w & 0xffff)) >>> 0;
          if (ra === 2) R2 = v;
          if (ra === 13) R13 = v;
        }
      } else if (op === 14 && hi[(w >>> 16) & 31] !== undefined) {
        const ra = (w >>> 16) & 31;
        if (rt === 2 || rt === 13) {
          const v = (hi[ra] + sign16(w)) >>> 0;
          if (rt === 2) R2 = v;
          if (rt === 13) R13 = v;
        }
      }
    }
  };
  scan(dolEntry);
  const w0 = readU32(dolEntry);
  if (w0 !== null && w0 >>> 26 === 18 && (w0 & 1)) {
    let li = w0 & 0x03fffffc;
    if (li & 0x02000000) li -= 0x04000000;
    scan((dolEntry + li) >>> 0);
  }
}

// ---------- relevance prescan: which bl targets are worth descending into ----------
const relevanceCache = new Map();
function isRelevantCallee(fn, depth = 0) {
  if (fn === BEB8) return true;
  const key = fn;
  if (relevanceCache.has(key)) return relevanceCache.get(key);
  relevanceCache.set(key, false); // cycle guard
  if (!isText(fn)) return false;
  let relevant = false;
  for (let pc = fn, n = 0; n < 600; pc += 4, n++) {
    const w = readU32(pc);
    if (w === null) break;
    const op = w >>> 26;
    if ((w & 0xfc0007fe) === 0x4c000420) {
      relevant = true; // bcctr: dispatch or config callback
      break;
    }
    if ((w & 0xfc0007fe) === 0x4c000020 && ((w >>> 21) & 31) === 20 && (((w >>> 16) & 31) & 3) === 0 && ((w >>> 21) & 31) === 20) {
      break; // unconditional blr = end of function
    }
    if (op === 38 || op === 44 || op === 36) {
      const simm = sign16(w);
      if (simm === 0x580 || simm === 0x581 || simm === 0x6ea || simm === 0x6ee) {
        relevant = true;
        break;
      }
    }
    if (op === 18 && (w & 1)) {
      let li = w & 0x03fffffc;
      if (li & 0x02000000) li -= 0x04000000;
      const t = (w & 2) !== 0 ? li >>> 0 : (pc + li) >>> 0;
      if (t === BEB8) {
        relevant = true;
        break;
      }
      if (depth < 2 && isRelevantCallee(t, depth + 1)) {
        relevant = true;
        break;
      }
    }
  }
  relevanceCache.set(key, relevant);
  return relevant;
}

// ---------- value model ----------
// null                      = unknown
// {v, src?, tag?, as?}      = known 32-bit; src = DOL byte address it was loaded from;
//                             tag = 'action'|'variant'|'phase'|'borgid' (dispatch index
//                             taint); as = actor offset it was loaded from
// {unk: true, as?}          = unknown with actor-offset provenance
// {flags: true}             = the raw word at actor+0x5e0 (state flags)
// {air: shift}              = (airborneBit(0x40) << shift), airborneBit in {0,1}
// {fmask: M}                = flags-derived value that is zero iff (+0x5e0 & M) == 0
const K = (v, extra) => (extra ? { v: v >>> 0, ...extra } : { v: v >>> 0 });
const vOf = (x) => (x !== null && x !== undefined && x.v !== undefined ? x.v : null);
const isAir = (x) => x !== null && x !== undefined && x.air !== undefined;
const isFmask = (x) => x !== null && x !== undefined && x.fmask !== undefined;

function rotl32(v, n) {
  return ((v << n) | (v >>> (32 - n))) >>> 0;
}
function maskFromMbMe(mb, me) {
  // IBM bit numbering: bit 0 = MSB
  let m = 0;
  if (mb <= me) for (let i = mb; i <= me; i++) m |= 1 << (31 - i);
  else {
    for (let i = mb; i <= 31; i++) m |= 1 << (31 - i);
    for (let i = 0; i <= me; i++) m |= 1 << (31 - i);
  }
  return m >>> 0;
}

// ---------- actor/stack byte memory ----------
class ByteMem {
  constructor(parent) {
    this.map = parent ? new Map(parent.map) : new Map();
  }
  storeVal(base, size, value) {
    const known = vOf(value);
    for (let i = 0; i < size; i++) {
      if (known === null) this.map.set(base + i, { b: null });
      else {
        const byte = (known >>> ((size - 1 - i) * 8)) & 0xff;
        this.map.set(base + i, i === 0 ? { b: byte, meta: value } : { b: byte });
      }
    }
  }
  load(base, size, signed) {
    let v = 0;
    let meta = null;
    for (let i = 0; i < size; i++) {
      const e = this.map.get(base + i);
      if (!e || e.b === null) return null;
      if (i === 0 && e.meta) meta = e.meta;
      v = ((v << 8) | e.b) >>> 0;
    }
    if (signed) {
      const bits = size * 8;
      if (bits < 32 && v & (1 << (bits - 1))) v = (v - (1 << bits)) >>> 0 === v ? v : (v - 2 ** bits) >>> 0;
      if (bits === 8 && v & 0x80) v = (v | 0xffffff00) >>> 0;
      if (bits === 16 && v & 0x8000) v = (v | 0xffff0000) >>> 0;
    }
    const out = K(v);
    if (meta) {
      if (meta.src !== undefined) out.src = meta.src;
      if (meta.tag !== undefined) out.tag = meta.tag;
    }
    return out;
  }
  has(base, size) {
    for (let i = 0; i < size; i++) if (!this.map.has(base + i)) return false;
    return true;
  }
}

const ACTOR_TAGS = { 0x580: "action", 0x581: "variant", 0x540: "phase", 0x3e8: "borgid", 0x3e7: "borgid", 0x3e9: "borgid" };

function initialActorMem(borgValue, ai, vi) {
  const m = new ByteMem();
  const put = (off, size, v, tag) => m.storeVal(off, size, tag ? K(v, { tag }) : K(v));
  put(0x3e7, 1, (borgValue >> 8) & 0xff, "borgid");
  put(0x3e8, 1, (borgValue >> 8) & 0xff, "borgid");
  put(0x3e9, 1, borgValue & 0xff, "borgid");
  put(0x580, 1, ai & 0xff, "action");
  put(0x581, 1, vi & 0xff, "variant");
  for (let i = 0; i < 8; i++) put(0x540 + i, 1, 0, i === 0 ? "phase" : undefined);
  // +0x5da/+0x5db current states (attack = 61/0 per the report's cue dumps)
  put(0x5da, 1, 61);
  put(0x5db, 1, 0);
  return m;
}

// ---------- emulator ----------
function crBit(cr, bit, flagDecisions) {
  if (cr === null || cr === undefined) return null;
  if (cr.flagsMask !== undefined) {
    const decided = flagDecisions.get(cr.flagsMask);
    if (decided === undefined) return null;
    const eq = decided === 0;
    return bit === 2 ? eq : bit === 0 ? false : bit === 1 ? !eq : false;
  }
  return bit === 0 ? cr.lt : bit === 1 ? cr.gt : bit === 2 ? cr.eq : cr.so ?? false;
}

function cmpResult(l, r, signed) {
  const a = signed ? l | 0 : l >>> 0;
  const b = signed ? r | 0 : r >>> 0;
  return { lt: a < b, gt: a > b, eq: a === b };
}

function runLeaf(rootAddr, borgValue, ai, vi, opts = {}) {
  const chainMode = !!opts.chainMode;
  const maxSteps = chainMode ? 4000 : MAX_STEPS_TOTAL;
  const maxPathSteps = chainMode ? 2000 : MAX_STEPS_PATH;
  const maxPaths = chainMode ? 24 : MAX_PATHS;

  const result = { calls: [], dispatches: [], stateStores: [], commandReissues: [], childSpawns: [], neutralReturns: 0, capped: false, killed: 0, completed: 0 };
  const seenCalls = new Set();
  const seenDispatch = new Set();

  const basePath = () => ({
    pc: rootAddr,
    regs: (() => {
      const r = new Array(32).fill(null);
      r[1] = K(STACK);
      r[3] = K(ACTOR);
      if (R2 !== null) r[2] = K(R2);
      if (R13 !== null) r[13] = K(R13);
      return r;
    })(),
    cr: new Array(8).fill(null),
    ctr: null,
    lr: SENTINEL,
    ca: null,
    mem: initialActorMem(borgValue, ai, vi),
    stk: new ByteMem(),
    stack: [{ entry: rootAddr, ret: SENTINEL }],
    steps: 0,
    forks: 0,
    flags: new Map(), // +0x5e0 mask -> 0 (clear) | 1 (set), decided by forks
    redirect: null, // runtime +0x581 override stored on this path (variant redirect)
    pcalls: 0, // channel-0 stream calls made on this path (combo ladder position)
  });

  const queue = [basePath()];
  let totalSteps = 0;

  const fork = (p) => {
    if (queue.length + 1 > maxPaths) {
      result.capped = true;
      return null;
    }
    const q = {
      pc: p.pc,
      regs: p.regs.slice(),
      cr: p.cr.slice(),
      ctr: p.ctr,
      lr: p.lr,
      ca: p.ca,
      mem: new ByteMem(p.mem),
      stk: new ByteMem(p.stk),
      stack: p.stack.map((f) => ({ ...f })),
      steps: p.steps,
      forks: p.forks + 1,
      flags: new Map(p.flags),
      redirect: p.redirect,
      pcalls: p.pcalls,
    };
    return q;
  };

  const flagsOf = (p) => Object.fromEntries([...p.flags.entries()].map(([m, v]) => [hex(m), v]));
  const isBaseline = (p) => [...p.flags.values()].every((v) => v === 0);
  const isAirOnly = (p) => p.flags.get(AIRBORNE_MASK) === 1 && [...p.flags.entries()].every(([m, v]) => m === AIRBORNE_MASK || v === 0);

  const recordCall = (p, pc) => {
    const mask = vOf(p.regs[4]);
    // stream channels are bits 0-3 (arm loop in zz_004beb8_ chunk_0006.c:1481-1489);
    // helper-originated calls with masks like 0xc0/0xc1 arm nothing and are skipped
    if (mask === null || (mask & 0xf) === 0) return;
    const g = p.regs[5];
    const s = p.regs[6];
    const pseq = mask & 1 ? p.pcalls++ : null;
    const call = {
      pc: hex(pc),
      mask,
      pseq,
      group: vOf(g),
      slot: isAir(s) && s.air === 0 ? "airbit" : vOf(s),
      slotSrc: s && s.src !== undefined ? s.src : null,
      slotActorSrc: s && s.as !== undefined ? s.as : null,
      slotBias: s && s.bias !== undefined ? s.bias : 0,
      flags: flagsOf(p),
      baseline: isBaseline(p),
      airOnly: isAirOnly(p),
      redirect: p.redirect,
      inFunc: hex(p.stack[p.stack.length - 1].entry),
    };
    const key = JSON.stringify(call);
    if (!seenCalls.has(key)) {
      seenCalls.add(key);
      result.calls.push(call);
    }
  };

  const clobber = (p) => {
    p.regs[0] = null;
    for (let r = 3; r <= 12; r++) p.regs[r] = null;
    p.cr.fill(null);
    p.ctr = null;
    p.ca = null;
  };

  const materializeFlag = (p, mask, bit) => {
    p.flags.set(mask, bit);
    for (let r = 0; r < 32; r++) {
      const x = p.regs[r];
      if (isAir(x) && mask === AIRBORNE_MASK) p.regs[r] = K(bit << x.air);
      else if (isFmask(x) && x.fmask === mask) p.regs[r] = bit === 0 ? K(0) : null;
    }
  };

  while (queue.length > 0 && totalSteps < maxSteps) {
    const p = queue.pop();
    let alive = true;
    while (alive && p.steps < maxPathSteps && totalSteps < maxSteps) {
      p.steps++;
      totalSteps++;
      const pc = p.pc;
      const w = readU32(pc);
      if (w === null || !isText(pc)) {
        result.killed++;
        alive = false;
        break;
      }
      const op = w >>> 26;
      const rt = (w >>> 21) & 31;
      const ra = (w >>> 16) & 31;
      const rb = (w >>> 11) & 31;
      const simm = sign16(w);
      const uimm = w & 0xffff;
      let next = (pc + 4) >>> 0;

      const ea = (baseReg, disp) => {
        const b = vOf(p.regs[baseReg]);
        return b === null ? null : (b + disp) >>> 0;
      };
      const memFor = (addr) => {
        if (addr >= ACTOR && addr < ACTOR + ACTOR_SIZE) return { mem: p.mem, base: addr - ACTOR, actor: true };
        if (addr >= STACK - 0x10000 && addr < STACK + 0x2000) return { mem: p.stk, base: addr - (STACK - 0x10000), actor: false };
        return null;
      };
      const doLoad = (addr, size, signed) => {
        if (addr === null) return null;
        const region = memFor(addr);
        if (region) {
          if (region.actor) {
            const off = region.base;
            if (size === 4 && off === AIRBORNE_OFFSET && !region.mem.has(off, 4)) return { flags: true };
            const got = region.mem.load(off, size, signed);
            if (got === null) return { unk: true, as: off };
            if (ACTOR_TAGS[off] && got.tag === undefined) got.tag = ACTOR_TAGS[off];
            got.as = off;
            return got;
          }
          const got = region.mem.load(region.base, size, signed);
          return got === null ? null : got;
        }
        const o = offsetFor(addr);
        if (o === null) return null;
        let v;
        if (size === 1) v = signed ? dol.readInt8(o) : dol.readUInt8(o);
        else if (size === 2) v = signed ? dol.readInt16BE(o) : dol.readUInt16BE(o);
        else v = dol.readUInt32BE(o);
        return K(v >>> 0, { src: addr });
      };
      const doStore = (addr, size, value) => {
        if (addr === null) return;
        const region = memFor(addr);
        if (!region) return; // writes to globals: ignored
        if (region.actor) {
          const off = region.base;
          if (value !== null && vOf(value) !== null && (off === 0x580 || off === 0x581)) {
            result.stateStores.push({ offset: off, value: vOf(value), pc: hex(pc) });
            if (off === 0x581 && !chainMode) p.redirect = vOf(value);
          }
          region.mem.storeVal(off, size, value === null ? null : value);
        } else {
          region.mem.storeVal(region.base, size, value === null ? null : value);
        }
      };
      const setCr0 = (value) => {
        if (value === null) p.cr[0] = null;
        else if (isAir(value)) p.cr[0] = { flagsMask: AIRBORNE_MASK };
        else if (isFmask(value)) p.cr[0] = { flagsMask: value.fmask };
        else {
          const v = vOf(value);
          p.cr[0] = v === null ? null : cmpResult(v, 0, true);
        }
      };

      switch (op) {
        case 7: {
          // mulli
          const a = vOf(p.regs[ra]);
          p.regs[rt] = a === null ? null : K(Math.imul(a, simm));
          break;
        }
        case 8: {
          // subfic
          const a = vOf(p.regs[ra]);
          if (a === null) {
            p.regs[rt] = null;
            p.ca = null;
          } else {
            const res = (simm - a) | 0;
            p.regs[rt] = K(res);
            p.ca = (~a >>> 0) + ((simm >>> 0) >>> 0) + 1 > 0xffffffff;
          }
          break;
        }
        case 10: {
          // cmplwi
          const crf = (w >>> 23) & 7;
          const a = p.regs[ra];
          if (isAir(a) && uimm === 0) p.cr[crf] = { flagsMask: AIRBORNE_MASK };
          else if (isFmask(a) && uimm === 0) p.cr[crf] = { flagsMask: a.fmask };
          else {
            const av = vOf(a);
            p.cr[crf] = av === null ? null : cmpResult(av, uimm, false);
          }
          break;
        }
        case 11: {
          // cmpwi
          const crf = (w >>> 23) & 7;
          const a = p.regs[ra];
          if (isAir(a) && simm === 0) p.cr[crf] = { flagsMask: AIRBORNE_MASK };
          else if (isFmask(a) && simm === 0) p.cr[crf] = { flagsMask: a.fmask };
          else {
            const av = vOf(a);
            p.cr[crf] = av === null ? null : cmpResult(av, simm >>> 0, true);
          }
          break;
        }
        case 12:
        case 13: {
          // addic(.)
          const a = vOf(p.regs[ra]);
          if (a === null) {
            p.regs[rt] = null;
            p.ca = null;
            if (op === 13) p.cr[0] = null;
          } else {
            const res = (a + simm) >>> 0;
            p.regs[rt] = K(res);
            p.ca = (a >>> 0) + (simm >>> 0) > 0xffffffff;
            if (op === 13) setCr0(p.regs[rt]);
          }
          break;
        }
        case 14: {
          // addi
          if (ra === 0) p.regs[rt] = K(simm);
          else {
            const av = p.regs[ra];
            const a = vOf(av);
            if (a !== null) p.regs[rt] = K(a + simm);
            else if (av && av.unk && av.as !== undefined)
              p.regs[rt] = { unk: true, as: av.as, bias: (av.bias ?? 0) + simm }; // runtime cursor +- constant
            else p.regs[rt] = null;
          }
          break;
        }
        case 15: {
          // addis
          if (ra === 0) p.regs[rt] = K((uimm << 16) >>> 0);
          else {
            const a = vOf(p.regs[ra]);
            p.regs[rt] = a === null ? null : K(a + ((uimm << 16) | 0));
          }
          break;
        }
        case 16: {
          // bc
          const bo = rt;
          const biField = (w >>> 16) & 31;
          let ctrOk = true;
          if (!(bo & 4)) {
            const c = vOf(p.ctr);
            if (c === null) {
              result.killed++;
              alive = false;
              break;
            }
            const nc = (c - 1) >>> 0;
            p.ctr = K(nc);
            ctrOk = bo & 2 ? nc === 0 : nc !== 0;
          }
          let condOk = true;
          if (!(bo & 16)) {
            const bit = crBit(p.cr[biField >> 2], biField & 3, p.flags);
            condOk = bit === null ? null : bo & 8 ? bit : !bit;
          }
          let taken;
          if (condOk === null) taken = null;
          else taken = ctrOk && condOk;
          const disp = (() => {
            const raw = w & 0xfffc;
            const d = raw >= 0x8000 ? raw - 0x10000 : raw;
            return (w & 2) !== 0 ? d >>> 0 : (pc + d) >>> 0;
          })();
          if (taken === null) {
            const crv = p.cr[biField >> 2];
            const flagMask = crv && crv.flagsMask !== undefined ? crv.flagsMask : null;
            const q = fork(p);
            if (q) {
              // q takes the branch, p falls through
              q.pc = disp;
              if (flagMask !== null && !p.flags.has(flagMask) && (biField & 3) === 2) {
                // cr eq is true when (+0x5e0 & mask) == 0 (flag clear)
                const takenBit = bo & 8 ? 0 : 1; // branch-if-eq lands on the clear side
                materializeFlag(q, flagMask, takenBit);
                materializeFlag(p, flagMask, takenBit === 0 ? 1 : 0);
              }
              queue.push(q);
            }
            // fall through on p
          } else if (taken) next = disp;
          if (w & 1) p.lr = (pc + 4) >>> 0;
          break;
        }
        case 17:
          result.killed++;
          alive = false;
          break;
        case 18: {
          // b/bl
          let li = w & 0x03fffffc;
          if (li & 0x02000000) li -= 0x04000000;
          const target = (w & 2) !== 0 ? li >>> 0 : (pc + li) >>> 0;
          if (w & 1) {
            // bl
            if (target === BEB8) {
              recordCall(p, pc);
              clobber(p);
              p.lr = (pc + 4) >>> 0;
            } else if (target === 0x8006a3d0) {
              // zz_006a3d0_ command re-issue (chain callbacks); record + opaque
              result.commandReissues.push({ pc: hex(pc), args: [vOf(p.regs[4]), vOf(p.regs[5]), vOf(p.regs[6])] });
              clobber(p);
              p.lr = (pc + 4) >>> 0;
            } else if (target === 0x80099e70 || target === 0x800e19a8) {
              // zz_0099e70_/zz_00e19a8_ child (projectile) spawns; record + opaque
              result.childSpawns.push({ pc: hex(pc), fn: hex(target), args: [vOf(p.regs[4]), vOf(p.regs[5])] });
              clobber(p);
              p.lr = (pc + 4) >>> 0;
            } else if (target === 0x8006a474 || target === 0x8006a5a4) {
              // zz_006a474_/zz_006a5a4_ return-to-neutral; record + opaque
              result.neutralReturns++;
              clobber(p);
              p.lr = (pc + 4) >>> 0;
            } else if (!chainMode && isRelevantCallee(target) && p.stack.length < MAX_FUNC_DEPTH) {
              p.lr = (pc + 4) >>> 0;
              p.stack.push({ entry: target, ret: (pc + 4) >>> 0 });
              next = target;
            } else {
              clobber(p);
              p.lr = (pc + 4) >>> 0;
            }
          } else if (target === BEB8 || target === 0x8006a3d0 || target === 0x80099e70 || target === 0x800e19a8) {
            // tail call to a recorded special: record, then behave like a return
            if (target === BEB8) recordCall(p, pc);
            else if (target === 0x8006a3d0)
              result.commandReissues.push({ pc: hex(pc), args: [vOf(p.regs[4]), vOf(p.regs[5]), vOf(p.regs[6])] });
            else result.childSpawns.push({ pc: hex(pc), fn: hex(target), args: [vOf(p.regs[4]), vOf(p.regs[5])] });
            const lr = p.lr;
            if (lr === SENTINEL || lr === null || typeof lr !== "number") {
              if (lr === SENTINEL) result.completed++;
              else result.killed++;
              alive = false;
              break;
            }
            const topIdx = p.stack.length - 1;
            if (topIdx > 0 && p.stack[topIdx].ret === lr) p.stack.pop();
            next = lr;
          } else {
            const top = p.stack[p.stack.length - 1];
            if (target < top.entry || target > pc + 0x8000) {
              top.entry = target; // tail call
            }
            next = target;
          }
          break;
        }
        case 19: {
          const xo = (w >>> 1) & 0x3ff;
          if (xo === 16) {
            // bclr
            const bo = rt;
            const biField = (w >>> 16) & 31;
            let condOk = true;
            if (!(bo & 16)) {
              const bit = crBit(p.cr[biField >> 2], biField & 3, p.flags);
              condOk = bit === null ? null : bo & 8 ? bit : !bit;
            }
            let ctrOk = true;
            if (!(bo & 4)) {
              const c = vOf(p.ctr);
              if (c === null) {
                result.killed++;
                alive = false;
                break;
              }
              const nc = (c - 1) >>> 0;
              p.ctr = K(nc);
              ctrOk = bo & 2 ? nc === 0 : nc !== 0;
            }
            const doRet = () => {
              const lr = p.lr;
              if (lr === SENTINEL) {
                result.completed++;
                return false;
              }
              if (lr === null || typeof lr !== "number") {
                result.killed++;
                return false;
              }
              const topIdx = p.stack.length - 1;
              if (topIdx > 0 && p.stack[topIdx].ret === lr) p.stack.pop();
              p.pc = lr;
              return true;
            };
            let taken = condOk === null ? null : condOk && ctrOk;
            if (taken === null) {
              const q = fork(p);
              if (q) {
                // q returns, p falls through
                const qAlive = (() => {
                  const lr = q.lr;
                  if (lr === SENTINEL || lr === null || typeof lr !== "number") {
                    if (lr === SENTINEL) result.completed++;
                    else result.killed++;
                    return false;
                  }
                  const topIdx = q.stack.length - 1;
                  if (topIdx > 0 && q.stack[topIdx].ret === lr) q.stack.pop();
                  q.pc = lr;
                  return true;
                })();
                if (qAlive) queue.push(q);
              }
            } else if (taken) {
              if (!doRet()) {
                alive = false;
                break;
              }
              next = p.pc;
            }
          } else if (xo === 528) {
            // bcctr
            const target = p.ctr;
            const tv = vOf(target);
            if (tv === null || !isText(tv)) {
              if (w & 1) {
                // bctrl through unknown pointer: treat as opaque call
                clobber(p);
                p.lr = (pc + 4) >>> 0;
              } else {
                result.killed++;
                alive = false;
              }
              break;
            }
            if (target.dispatch) {
              const d = target.dispatch;
              const baseline = isBaseline(p);
              const key = `${d.kind}:${d.table}:${d.index}:${tv}:${baseline}`;
              if (!seenDispatch.has(key)) {
                seenDispatch.add(key);
                result.dispatches.push({
                  kind: d.kind,
                  table: hex(d.table),
                  index: d.index,
                  target: hex(tv),
                  inFunc: hex(p.stack[p.stack.length - 1].entry),
                  r4: vOf(p.regs[4]),
                  baseline,
                });
              }
            }
            if (w & 1) {
              p.lr = (pc + 4) >>> 0;
              if (p.stack.length < MAX_FUNC_DEPTH) p.stack.push({ entry: tv, ret: (pc + 4) >>> 0 });
              next = tv;
            } else {
              p.stack[p.stack.length - 1].entry = tv;
              next = tv;
            }
          } else if (xo === 150 || xo === 278 || xo === 598 || xo === 854) {
            // isync/dcbt-ish/sync: no-op
          } else {
            // cr logical ops etc: conservatively drop all cr state
            p.cr.fill(null);
          }
          break;
        }
        case 20: {
          // rlwimi
          const s = vOf(p.regs[rt]);
          const a = vOf(p.regs[ra]);
          const sh = rb;
          const mb = (w >>> 6) & 31;
          const me = (w >>> 1) & 31;
          if (s === null || a === null) p.regs[ra] = null;
          else {
            const m = maskFromMbMe(mb, me);
            p.regs[ra] = K((rotl32(s, sh) & m) | (a & ~m));
          }
          if (w & 1) setCr0(p.regs[ra]);
          break;
        }
        case 21: {
          // rlwinm
          const src = p.regs[rt];
          const sh = rb;
          const mb = (w >>> 6) & 31;
          const me = (w >>> 1) & 31;
          const m = maskFromMbMe(mb, me);
          let out = null;
          if (src !== null && src !== undefined && src.flags) {
            // rotate/mask of the +0x5e0 flags word: which source bits feed the result?
            const srcMask = rotl32(m, (32 - sh) & 31);
            const rotPos = (6 + sh) % 32; // LSB position of the airborne bit after rotl
            if (srcMask === AIRBORNE_MASK && m === (1 << rotPos) >>> 0) out = { air: rotPos };
            else if (srcMask !== 0) out = { fmask: srcMask };
            else out = K(0);
          } else if (isAir(src)) {
            const rotPos = (src.air + sh) % 32;
            if (m === (1 << rotPos) >>> 0) out = { air: rotPos };
            else if ((m & ((1 << rotPos) >>> 0)) === 0) out = K(0);
            else out = { fmask: AIRBORNE_MASK };
          } else if (isFmask(src)) {
            out = m === 0 ? K(0) : { fmask: src.fmask };
          } else {
            const sv = vOf(src);
            if (sv !== null) {
              out = K(rotl32(sv, sh) & m);
              if (src.tag) out.tag = src.tag;
            }
          }
          p.regs[ra] = out;
          if (w & 1) setCr0(out);
          break;
        }
        case 24: {
          // ori
          const s = p.regs[rt];
          if (uimm === 0) p.regs[ra] = s; // mr
          else {
            const sv = vOf(s);
            p.regs[ra] = sv === null ? null : K(sv | uimm);
          }
          break;
        }
        case 25: {
          const sv = vOf(p.regs[rt]);
          p.regs[ra] = sv === null ? null : K(sv | ((uimm << 16) >>> 0));
          break;
        }
        case 26: {
          const sv = vOf(p.regs[rt]);
          p.regs[ra] = sv === null ? null : K(sv ^ uimm);
          break;
        }
        case 27: {
          const sv = vOf(p.regs[rt]);
          p.regs[ra] = sv === null ? null : K(sv ^ ((uimm << 16) >>> 0));
          break;
        }
        case 28: {
          // andi.
          const s = p.regs[rt];
          let out = null;
          if (s !== null && s !== undefined && s.flags) {
            if (uimm === AIRBORNE_MASK) out = { air: 6 };
            else if (uimm !== 0) out = { fmask: uimm };
            else out = K(0);
          } else if (isAir(s)) {
            if (uimm & ((1 << s.air) >>> 0)) out = s;
            else out = K(0);
          } else if (isFmask(s)) {
            out = uimm === 0 ? K(0) : { fmask: s.fmask };
          } else {
            const sv = vOf(s);
            out = sv === null ? null : K(sv & uimm);
          }
          p.regs[ra] = out;
          setCr0(out);
          break;
        }
        case 29: {
          const sv = vOf(p.regs[rt]);
          const out = sv === null ? null : K(sv & ((uimm << 16) >>> 0));
          p.regs[ra] = out;
          setCr0(out);
          break;
        }
        case 31: {
          const xo = (w >>> 1) & 0x3ff;
          const rc = w & 1;
          const A = () => vOf(p.regs[ra]);
          const B = () => vOf(p.regs[rb]);
          const S = () => vOf(p.regs[rt]);
          switch (xo) {
            case 0: {
              const crf = (w >>> 23) & 7;
              const a = A();
              const b = B();
              p.cr[crf] = a === null || b === null ? null : cmpResult(a, b, true);
              break;
            }
            case 32: {
              const crf = (w >>> 23) & 7;
              const a = A();
              const b = B();
              p.cr[crf] = a === null || b === null ? null : cmpResult(a, b, false);
              break;
            }
            case 23: // lwzx
            case 87: // lbzx
            case 279: // lhzx
            case 343: {
              // lhax
              const a = A();
              const b = B();
              const addr = a === null || b === null ? null : (a + b) >>> 0;
              const size = xo === 23 ? 4 : xo === 87 ? 1 : 2;
              const signed = xo === 343;
              let out = doLoad(addr, size, signed);
              if (out !== null && out !== undefined && out.v !== undefined && addr !== null && xo === 23) {
                // dispatch-table detection: one operand carries an index taint
                const idxOp = p.regs[ra] && p.regs[ra].tag ? p.regs[ra] : p.regs[rb] && p.regs[rb].tag ? p.regs[rb] : null;
                if (idxOp && ["action", "variant", "phase", "borgid"].includes(idxOp.tag)) {
                  out.dispatch = { kind: idxOp.tag, table: (addr - vOf(idxOp)) >>> 0, index: vOf(idxOp) >> 2 };
                }
                out.src = addr;
              }
              p.regs[rt] = out === undefined ? null : out;
              break;
            }
            case 151: // stwx
            case 215: // stbx
            case 407: {
              // sthx
              const a = A();
              const b = B();
              const addr = a === null || b === null ? null : (a + b) >>> 0;
              const size = xo === 151 ? 4 : xo === 215 ? 1 : 2;
              doStore(addr, size, p.regs[rt]);
              break;
            }
            case 24: {
              // slw
              const s = S();
              const b = B();
              p.regs[ra] = s === null || b === null ? null : K((b & 32 ? 0 : s << (b & 31)) >>> 0);
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 536: {
              // srw
              const s = S();
              const b = B();
              p.regs[ra] = s === null || b === null ? null : K(b & 32 ? 0 : s >>> (b & 31));
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 792: {
              // sraw
              const s = S();
              const b = B();
              p.regs[ra] = s === null || b === null ? null : K((s | 0) >> Math.min(b & 63, 31));
              p.ca = null;
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 824: {
              // srawi
              const s = S();
              p.regs[ra] = s === null ? null : K((s | 0) >> rb);
              p.ca = null;
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 26: {
              // cntlzw
              const s = S();
              p.regs[ra] = s === null ? null : K(Math.clz32(s));
              break;
            }
            case 28: {
              const s = S();
              const b = B();
              p.regs[ra] = s === null || b === null ? null : K(s & b);
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 60: {
              const s = S();
              const b = B();
              p.regs[ra] = s === null || b === null ? null : K(s & ~b);
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 124: {
              const s = S();
              const b = B();
              p.regs[ra] = s === null || b === null ? null : K(~(s | b));
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 444: {
              // or (mr when rs==rb)
              if (rt === rb) {
                p.regs[ra] = p.regs[rt];
              } else {
                const s = S();
                const b = B();
                p.regs[ra] = s === null || b === null ? null : K(s | b);
              }
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 316: {
              const s = S();
              const b = B();
              p.regs[ra] = s === null || b === null ? null : K(s ^ b);
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 476: {
              const s = S();
              const b = B();
              p.regs[ra] = s === null || b === null ? null : K(~(s & b));
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 40: {
              // subf
              const a = A();
              const b = B();
              p.regs[rt] = a === null || b === null ? null : K(b - a);
              if (rc) setCr0(p.regs[rt]);
              break;
            }
            case 8: {
              // subfc
              const a = A();
              const b = B();
              if (a === null || b === null) {
                p.regs[rt] = null;
                p.ca = null;
              } else {
                p.regs[rt] = K(b - a);
                p.ca = (b >>> 0) >= (a >>> 0);
              }
              if (rc) setCr0(p.regs[rt]);
              break;
            }
            case 104: {
              const a = A();
              p.regs[rt] = a === null ? null : K(-a);
              if (rc) setCr0(p.regs[rt]);
              break;
            }
            case 266: {
              const a = A();
              const b = B();
              if (a !== null && b !== null) p.regs[rt] = K(a + b);
              else {
                const unkOp = a === null ? p.regs[ra] : p.regs[rb];
                const known = a === null ? b : a;
                if (known !== null && unkOp && unkOp.unk && unkOp.as !== undefined)
                  p.regs[rt] = { unk: true, as: unkOp.as, bias: (unkOp.bias ?? 0) + known };
                else p.regs[rt] = null;
              }
              if (rc) setCr0(p.regs[rt]);
              break;
            }
            case 10: {
              // addc
              const a = A();
              const b = B();
              if (a === null || b === null) {
                p.regs[rt] = null;
                p.ca = null;
              } else {
                p.regs[rt] = K(a + b);
                p.ca = (a >>> 0) + (b >>> 0) > 0xffffffff;
              }
              break;
            }
            case 136: {
              // subfe
              const a = A();
              const b = B();
              if (a === null || b === null || p.ca === null) {
                p.regs[rt] = null;
                p.ca = null;
              } else {
                const sum = (~a >>> 0) + (b >>> 0) + (p.ca ? 1 : 0);
                p.regs[rt] = K(sum);
                p.ca = sum > 0xffffffff;
              }
              if (rc) setCr0(p.regs[rt]);
              break;
            }
            case 138: {
              // adde
              const a = A();
              const b = B();
              if (a === null || b === null || p.ca === null) {
                p.regs[rt] = null;
                p.ca = null;
              } else {
                const sum = (a >>> 0) + (b >>> 0) + (p.ca ? 1 : 0);
                p.regs[rt] = K(sum);
                p.ca = sum > 0xffffffff;
              }
              break;
            }
            case 202: {
              // addze
              const a = A();
              if (a === null || p.ca === null) {
                p.regs[rt] = null;
                p.ca = null;
              } else {
                const sum = (a >>> 0) + (p.ca ? 1 : 0);
                p.regs[rt] = K(sum);
                p.ca = sum > 0xffffffff;
              }
              break;
            }
            case 235: {
              const a = A();
              const b = B();
              p.regs[rt] = a === null || b === null ? null : K(Math.imul(a, b));
              break;
            }
            case 491: {
              const a = A();
              const b = B();
              p.regs[rt] = a === null || b === null || (a | 0) === 0 ? null : K(((b | 0) / (a | 0)) | 0);
              break;
            }
            case 459: {
              const a = A();
              const b = B();
              p.regs[rt] = a === null || b === null || a >>> 0 === 0 ? null : K(Math.floor((b >>> 0) / (a >>> 0)));
              break;
            }
            case 954: {
              // extsb (preserves dispatch-index taint)
              const s = p.regs[rt];
              if (s === null || s === undefined) p.regs[ra] = null;
              else if (isAir(s)) p.regs[ra] = s;
              else {
                const sv = vOf(s);
                if (sv === null) p.regs[ra] = s.unk ? s : null;
                else {
                  const out = K((sv << 24) >> 24);
                  if (s.tag) out.tag = s.tag;
                  if (s.src !== undefined) out.src = s.src;
                  if (s.as !== undefined) out.as = s.as;
                  p.regs[ra] = out;
                }
              }
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 922: {
              const s = p.regs[rt];
              const sv = vOf(s);
              if (sv === null) p.regs[ra] = null;
              else {
                const out = K((sv << 16) >> 16);
                if (s.tag) out.tag = s.tag;
                if (s.src !== undefined) out.src = s.src;
                if (s.as !== undefined) out.as = s.as;
                p.regs[ra] = out;
              }
              if (rc) setCr0(p.regs[ra]);
              break;
            }
            case 339: {
              // mfspr
              const spr = ((w >>> 16) & 31) | (((w >>> 11) & 31) << 5);
              if (spr === 8) p.regs[rt] = typeof p.lr === "number" ? K(p.lr) : null;
              else if (spr === 9) p.regs[rt] = p.ctr;
              else p.regs[rt] = null;
              break;
            }
            case 467: {
              // mtspr
              const spr = ((w >>> 16) & 31) | (((w >>> 11) & 31) << 5);
              if (spr === 8) p.lr = vOf(p.regs[rt]);
              else if (spr === 9) p.ctr = p.regs[rt];
              break;
            }
            case 19: // mfcr
              p.regs[rt] = null;
              break;
            case 144: // mtcrf
              p.cr.fill(null);
              break;
            case 598: // sync
            case 86: // dcbf
            case 54: // dcbst
            case 278: // dcbt
            case 246: // dcbtst
            case 982: // icbi
              break;
            case 1014: {
              // dcbz: zero the cache line
              const a = ra === 0 ? 0 : A();
              const b = B();
              if (a !== null && b !== null) {
                const base = ((a + b) & ~31) >>> 0;
                for (let i = 0; i < 32; i += 4) doStore((base + i) >>> 0, 4, K(0));
              }
              break;
            }
            default:
              p.regs[rt] = null;
              if (rc) p.cr[0] = null;
              break;
          }
          break;
        }
        case 32: // lwz
        case 33: {
          const addr = ea(ra, simm);
          const out = doLoad(addr, 4, false);
          p.regs[rt] = out === undefined ? null : out;
          if (op === 33 && addr !== null) p.regs[ra] = K(addr);
          break;
        }
        case 34: // lbz
        case 35: {
          const addr = ea(ra, simm);
          const out = doLoad(addr, 1, false);
          p.regs[rt] = out === undefined ? null : out;
          if (op === 35 && addr !== null) p.regs[ra] = K(addr);
          break;
        }
        case 36: // stw
        case 37: {
          const addr = ea(ra, simm);
          doStore(addr, 4, p.regs[rt]);
          if (op === 37 && addr !== null) p.regs[ra] = K(addr);
          break;
        }
        case 38: // stb
        case 39: {
          const addr = ea(ra, simm);
          doStore(addr, 1, p.regs[rt]);
          if (op === 39 && addr !== null) p.regs[ra] = K(addr);
          break;
        }
        case 40: // lhz
        case 41: {
          const addr = ea(ra, simm);
          const out = doLoad(addr, 2, false);
          p.regs[rt] = out === undefined ? null : out;
          if (op === 41 && addr !== null) p.regs[ra] = K(addr);
          break;
        }
        case 42: // lha
        case 43: {
          const addr = ea(ra, simm);
          const out = doLoad(addr, 2, true);
          p.regs[rt] = out === undefined ? null : out;
          if (op === 43 && addr !== null) p.regs[ra] = K(addr);
          break;
        }
        case 44: // sth
        case 45: {
          const addr = ea(ra, simm);
          doStore(addr, 2, p.regs[rt]);
          if (op === 45 && addr !== null) p.regs[ra] = K(addr);
          break;
        }
        case 46: {
          // lmw
          const base = ea(ra, simm);
          if (base !== null) for (let r = rt; r < 32; r++) p.regs[r] = doLoad((base + (r - rt) * 4) >>> 0, 4, false) ?? null;
          else for (let r = rt; r < 32; r++) p.regs[r] = null;
          break;
        }
        case 47: {
          // stmw
          const base = ea(ra, simm);
          if (base !== null) for (let r = rt; r < 32; r++) doStore((base + (r - rt) * 4) >>> 0, 4, p.regs[r]);
          break;
        }
        case 48:
        case 49:
        case 50:
        case 51:
          // lfs/lfsu/lfd/lfdu: FPRs untracked
          if (op === 49 || op === 51) {
            const addr = ea(ra, simm);
            if (addr !== null) p.regs[ra] = K(addr);
          }
          break;
        case 52:
        case 53:
        case 54:
        case 55: {
          // stfs/stfsu/stfd/stfdu: store unknown bytes
          const addr = ea(ra, simm);
          doStore(addr, op >= 54 ? 8 : 4, null);
          if (op === 53 || op === 55) {
            if (addr !== null) p.regs[ra] = K(addr);
          }
          break;
        }
        case 56:
        case 57:
        case 60:
        case 61:
          // psq_l / psq_st (GameCube paired singles)
          break;
        case 4:
        case 59:
        case 63:
          // paired-single / float arithmetic; fcmp sets a cr field
          if (op === 63 || op === 4) {
            const xo = (w >>> 1) & 0x3ff;
            if (xo === 0 || xo === 32) p.cr[(w >>> 23) & 7] = null;
          }
          break;
        default:
          p.regs[rt] = null;
          break;
      }
      if (alive) p.pc = next;
      if (!alive) break;
      if (p.pc === undefined || p.pc === null) {
        result.killed++;
        break;
      }
    }
    if (alive && p.steps >= maxPathSteps) result.capped = true;
  }
  if (totalSteps >= maxSteps) result.capped = true;
  return result;
}

// ---------- constructor walk: +0x4b4 / +0x4f0 / +0x1d80 / +0x1d84 ----------
// Adapted from scripts/gen-melee-anim-kinds.mjs collectBankStores (borg-id-aware
// straight-line emulation with bl-following), extended to capture value provenance.
function actorLoadValue(offset, borgValue) {
  if (offset === 0x3e8) return borgValue;
  if (offset === 0x3e9) return borgValue & 0xff;
  if (offset === 0x3e7) return (borgValue >> 8) & 0xff;
  return null;
}
function compareValues(left, right) {
  if (left === right) return { lt: false, gt: false, eq: true };
  return { lt: left < right, gt: left > right, eq: false };
}
function ctorBranchTaken(word, cr0) {
  const bo = (word >>> 21) & 0x1f;
  const bi = (word >>> 16) & 0x1f;
  if (bo === 20) return true;
  if (!cr0) return null;
  const bit = bi & 3;
  const value = bit === 0 ? cr0.lt : bit === 1 ? cr0.gt : bit === 2 ? cr0.eq : false;
  if (bo === 12) return value;
  if (bo === 4) return !value;
  return null;
}
const CTOR_OFFSETS = new Set([0x4b4, 0x4f0, 0x1d80, 0x1d84]);
function collectCtorStores(ctorAddress, borgValue) {
  const stores = new Map();
  const visit = (entry, depth, visited) => {
    if (depth > 3 || visited.has(entry)) return;
    visited.add(entry);
    const regs = Array.from({ length: 32 }, () => null);
    const srcs = Array.from({ length: 32 }, () => null);
    let cr0 = null;
    let pc = entry;
    for (let steps = 0; steps < 1600; steps++) {
      const word = readU32(pc);
      if (word === null) return;
      const op = word >>> 26;
      const rt = (word >>> 21) & 31;
      const ra = (word >>> 16) & 31;
      const simm = sign16(word);
      const rawImm = word & 0xffff;
      let next = pc + 4;
      if (op === 15 && ra === 0) {
        regs[rt] = (rawImm << 16) >>> 0;
        srcs[rt] = null;
      } else if (op === 14) {
        regs[rt] = ra === 0 ? simm >>> 0 : regs[ra] !== null ? (regs[ra] + simm) >>> 0 : null;
        srcs[rt] = null;
      } else if (op === 10) cr0 = regs[ra] === null ? null : compareValues(regs[ra] >>> 0, rawImm);
      else if (op === 11) cr0 = regs[ra] === null ? null : compareValues(regs[ra] | 0, simm);
      else if (op === 32) {
        if (regs[ra] !== null) {
          const addr = (regs[ra] + simm) >>> 0;
          regs[rt] = readU32(addr);
          srcs[rt] = regs[rt] === null ? null : addr;
        } else {
          regs[rt] = null;
          srcs[rt] = null;
        }
      } else if (op === 34) {
        const av = ra === 3 ? actorLoadValue(simm, borgValue) : null;
        regs[rt] = av !== null ? av & 0xff : regs[ra] !== null ? readU8(regs[ra] + simm) : null;
        srcs[rt] = null;
      } else if (op === 42) {
        const av = ra === 3 ? actorLoadValue(simm, borgValue) : null;
        regs[rt] = av !== null ? sign16(av) : regs[ra] !== null ? readS16(regs[ra] + simm) : null;
        srcs[rt] = null;
      } else if (op === 36) {
        if (ra === 3 && CTOR_OFFSETS.has(simm) && regs[rt] !== null) {
          stores.set(simm, { value: regs[rt], srcAddr: srcs[rt], pc });
        }
      } else if (op === 16) {
        const taken = ctorBranchTaken(word, cr0);
        if (taken) {
          const raw = word & 0xfffc;
          const disp = raw >= 0x8000 ? raw - 0x10000 : raw;
          next = (word & 2) !== 0 ? disp >>> 0 : (pc + disp) >>> 0;
          if (next <= pc) return;
        }
      } else if (op === 18) {
        let li = word & 0x03fffffc;
        if (li & 0x02000000) li -= 0x04000000;
        const target = (word & 2) !== 0 ? li >>> 0 : (pc + li) >>> 0;
        if (word & 1) {
          visit(target, depth + 1, visited);
          for (let r = 0; r <= 12; r++)
            if (r !== 3) {
              regs[r] = null;
              srcs[r] = null;
            }
          cr0 = null;
        } else {
          next = target;
          if (target <= pc) return;
        }
      } else if (op === 19 && (word & 0xfc0007fe) === 0x4c000020) {
        const taken = ctorBranchTaken(word, cr0);
        if (taken || taken === null) return;
      } else if ([33, 35, 40, 41, 43, 46, 48, 50].includes(op) || op === 31) {
        regs[rt] = null;
        srcs[rt] = null;
      }
      pc = next;
    }
  };
  visit(ctorAddress, 0, new Set());
  return stores;
}

// ---------- bank parsing (clone of gen-melee-anim-kinds.mjs conventions) ----------
const bankLayoutCache = new Map();
function parseBankLayout(base) {
  if (bankLayoutCache.has(base)) return bankLayoutCache.get(base);
  const rawGroups = [];
  {
    let minPos = Infinity;
    for (let i = 0; ; i++) {
      if (i * 2 >= Math.min(minPos, 0x200)) break;
      const v = readS16(base + i * 2);
      if (v === null) break;
      rawGroups.push(v);
      if (v > 0) minPos = Math.min(minPos, v);
    }
  }
  const groupPtrs = rawGroups.map((v) => (v === -1 ? null : base + v));
  const distinct = [...new Set(groupPtrs.filter((p) => p !== null))].sort((a, b) => a - b);
  const slotCounts = new Map();
  for (const gp of distinct) {
    // the -1 sentinel is the true slot-table terminator; a "next table" bound is NOT
    // safe because family banks can interleave (e.g. 0x8032744c's group array starts 12
    // bytes into 0x80327440's, sharing slot tables)
    let n = 0;
    for (let i = 0; i < 0x40; i++) {
      const v = readS16(gp + i * 2);
      if (v === null || v === -1) break;
      n++;
    }
    slotCounts.set(gp, n);
  }
  const layout = groupPtrs.map((gp) => (gp === null ? null : slotCounts.get(gp)));
  bankLayoutCache.set(base, layout);
  return layout;
}

// ---------- cue table ----------
function decodeCueTable(addr) {
  const entries = [];
  for (let cue = 0; cue < 48; cue++) {
    const f = readU8(addr + cue * 2);
    const u = readU8(addr + cue * 2 + 1);
    if (f === null || u === null) return null;
    entries.push([(f << 24) >> 24, (u << 24) >> 24]);
  }
  return entries;
}

// ---------- per-borg walk ----------
const leafRunCache = new Map();
function cachedRun(root, borgValue, ai, vi) {
  const key = `${root}:${borgValue}:${ai}:${vi}`;
  if (leafRunCache.has(key)) return leafRunCache.get(key);
  const res = runLeaf(root, borgValue, ai, vi);
  leafRunCache.set(key, res);
  return res;
}

function interpretRun(res, ai, vi, familyBank, sharedBank) {
  const out = { diagnostics: {} };
  const actionDisp = res.dispatches.find((d) => d.kind === "action");
  const variantDisp = res.dispatches.find((d) => d.kind === "variant");
  const phaseDisps = res.dispatches.filter((d) => d.kind === "phase");
  out.actionTable = actionDisp ? actionDisp.table : null;
  out.handler = actionDisp ? actionDisp.target : null;
  out.variantTable = variantDisp ? variantDisp.table : null;
  out.leaf = variantDisp ? variantDisp.target : actionDisp ? actionDisp.target : null;
  const phase = phaseDisps.find((d) => d.baseline) ?? phaseDisps[0] ?? null;
  out.engine = phase ? phase.inFunc : null;
  out.phaseTable = phase ? phase.table : null;
  out.phaseHandler = phase ? phase.target : null;
  let config = null;
  if (phase && phase.r4 !== null) {
    if (phase.r4 >= 0x80000000 && offsetFor(phase.r4) !== null && !isText(phase.r4)) config = { kind: "pointer", address: hex(phase.r4) };
    else if (phase.r4 < 0x10000) config = { kind: "param", value: phase.r4 };
  }
  out.config = config;

  // baseline = every +0x5e0 flag fork taken on the clear side (grounded, neutral state)
  // AND no runtime +0x581 redirect on the path; air = only the 0x40 (airborne) fork set;
  // everything else = conditional stream. The primary stream is the one armed on channel
  // 0 (mask bit 0: full-body 0xf, or dash channel masks 1/3); other channels (e.g. the
  // dash mask-2 overlay) are additional streams.
  const isPrimary = (c) => (c.mask & 1) !== 0 && c.pseq === 0; // first channel-0 stream on the path
  const isFollowUp = (c) => (c.mask & 1) !== 0 && c.pseq > 0; // +0x6ea combo-ladder continuation
  const baselineCalls = res.calls.filter((c) => c.baseline && c.redirect === null);
  const airCalls = res.calls.filter((c) => c.airOnly && c.redirect === null);
  const condCalls = res.calls.filter((c) => !(c.baseline && c.redirect === null) && !(c.airOnly && c.redirect === null));
  const distinct = (calls) => {
    const seen = new Map();
    for (const c of calls) seen.set(`${c.group}:${c.slot}`, c);
    return [...seen.values()];
  };
  const g = distinct(baselineCalls.filter(isPrimary));
  const a = distinct(airCalls.filter(isPrimary));
  const secondary = distinct(baselineCalls.filter((c) => (c.mask & 1) === 0));
  const followUps = distinct(baselineCalls.filter(isFollowUp));
  out.calls = res.calls;
  out.capped = res.capped;
  out.childSpawns = res.childSpawns;

  const applyBank = (group) => {
    if (group === null) return { bank: familyBank, group };
    if (group & 0x80) return { bank: sharedBank, group: group & 0x7f };
    return { bank: familyBank, group };
  };

  if (g.length === 1) {
    const c = g[0];
    const { bank, group } = applyBank(c.group);
    out.bank = bank;
    out.group = group;
    if (c.slot === "airbit") {
      out.seedSlot = 0;
      out.airSeedSlot = 1;
      out.seedSource = "slot = (actor+0x5e0 & 0x40) ? 1 : 0";
    } else {
      out.seedSlot = c.slot;
      out.seedSource = c.slotSrc !== null ? `config byte @${hex(c.slotSrc)}` : c.slotActorSrc !== null ? `runtime actor+${hex(c.slotActorSrc)}${c.slotBias ? "+" + c.slotBias : ""}` : c.slot !== null ? "immediate" : null;
    }
    if (out.airSeedSlot === undefined && a.length === 1 && a[0].slot !== null && a[0].slot !== "airbit") {
      out.airSeedSlot = a[0].slot;
      out.airSeedSource = a[0].slotSrc !== null ? `config byte @${hex(a[0].slotSrc)}` : "immediate";
    } else if (a.length > 1) {
      out.diagnostics.airCandidates = a.map((c2) => ({ group: c2.group, slot: c2.slot }));
    }
    out.resolved = out.seedSlot !== null && out.seedSlot !== undefined;
    if (!out.resolved && c.slotActorSrc !== null) {
      // runtime cursor (e.g. +0x6ee dash-anim cursor): structure resolved, slot dynamic
      out.resolved = true;
      out.seedSlot = null;
      out.seedSource = `runtime actor+${hex(c.slotActorSrc)}${c.slotBias ? "+" + c.slotBias : ""}`;
    } else if (!out.resolved && c.group !== null) {
      // slot value not statically recoverable (computed cursor); group/bank proven
      out.resolved = true;
      out.seedSlot = null;
      out.seedSource = "runtime (slot not statically recoverable)";
    }
  } else if (g.length === 0 && a.length === 1) {
    const c = a[0];
    const { bank, group } = applyBank(c.group);
    out.bank = bank;
    out.group = group;
    out.seedSlot = null;
    out.airSeedSlot = c.slot === "airbit" ? 1 : c.slot;
    out.resolved = out.airSeedSlot !== null;
    out.diagnostics.note = "air path only";
  } else if (g.length > 1 && new Set(g.map((c) => c.group)).size === 1 && g.every((c) => typeof c.slot === "number")) {
    // one stream site, several concrete slots picked by runtime state (dash direction /
    // pose counters like +0x1dfc, upper-body state): emit the provable candidate set
    const { bank, group } = applyBank(g[0].group);
    out.bank = bank;
    out.group = group;
    out.seedSlot = null;
    out.slotCandidates = g.map((c) => c.slot).sort((x, y) => x - y);
    out.seedSource = "runtime-conditional (see slotCandidates)";
    if (a.length === 1 && typeof a[0].slot === "number") out.airSeedSlot = a[0].slot;
    out.resolved = true;
  } else if (g.length > 1) {
    out.resolved = false;
    out.diagnostics.groundCandidates = g.map((c) => ({ group: c.group, slot: c.slot, src: c.slotSrc !== null ? hex(c.slotSrc) : null }));
  } else if (secondary.length > 0) {
    // only non-channel-0 streams (rare): report the first as the leaf's stream
    const c = secondary[0];
    const { bank, group } = applyBank(c.group);
    out.bank = bank;
    out.group = group;
    out.seedSlot = c.slot === "airbit" ? 0 : c.slot;
    out.seedSource = c.slotActorSrc !== null ? `runtime actor+${hex(c.slotActorSrc)}${c.slotBias ? "+" + c.slotBias : ""}` : c.slotSrc !== null ? `config byte @${hex(c.slotSrc)}` : "immediate";
    out.resolved = true;
    out.diagnostics.note = `channel mask ${hex(c.mask)} only`;
  } else {
    out.resolved = false;
    out.diagnostics.note =
      res.childSpawns.length > 0
        ? "no stream; child/projectile spawn observed"
        : res.neutralReturns > 0
          ? "no stream; leaf returns to neutral state (zz_006a474_/zz_006a5a4_)"
          : res.capped
            ? "no stream call reached (run capped)"
            : "no stream call reached (code-driven or shot-only action)";
  }
  if (secondary.length > 0 && g.length === 1)
    out.additionalStreams = secondary.map((c) => {
      const { bank, group } = applyBank(c.group);
      return { mask: hex(c.mask), bank, group, slot: c.slot === "airbit" ? "airbit" : c.slot };
    });
  if (followUps.length > 0) {
    const emitted2 = new Set(g.map((c) => `${c.group}:${c.slot}`));
    const fu = followUps.filter((c) => !emitted2.has(`${c.group}:${c.slot}`) && c.slot !== null);
    if (fu.length > 0)
      out.comboFollowUps = fu.map((c) => {
        const { bank, group } = applyBank(c.group);
        return { bank, group, slot: c.slot };
      });
  }

  // conditional streams reached under other +0x5e0 state flags (e.g. 0x2000 jump-state
  // redirects in FUN_8018e0f8-style leaves); informational, excluding duplicates
  const emitted = new Set([...g, ...a].map((c) => `${c.group}:${c.slot}`));
  const cond = distinct(condCalls).filter((c) => !emitted.has(`${c.group}:${c.slot}`) && c.slot !== null);
  if (cond.length > 0)
    out.conditional = cond.map((c) => ({ flags: c.flags, group: c.group, slot: c.slot === "airbit" ? "airbit" : c.slot }));
  return out;
}

// chain callbacks: scan config words for text pointers whose mini-emulation stores an
// immediate to +0x581 (variant override) or +0x580
function discoverChainCallbacks(configAddr, borgValue, ai, vi) {
  const found = [];
  for (let off = 0; off <= 0x1c; off += 4) {
    const wv = readU32(configAddr + off);
    if (wv === null || !isText(wv) || wv % 4 !== 0) continue;
    const res = runLeaf(wv, borgValue, ai, vi, { chainMode: true });
    const overrides = res.stateStores.filter((s) => s.offset === 0x581);
    const actionOverrides = res.stateStores.filter((s) => s.offset === 0x580);
    if (overrides.length > 0 || actionOverrides.length > 0) {
      found.push({
        configOffset: hex(off),
        address: hex(wv),
        setsVariant: overrides.length ? overrides[overrides.length - 1].value : null,
        setsAction: actionOverrides.length ? actionOverrides[actionOverrides.length - 1].value : null,
        reissuesCommand: res.commandReissues.length > 0 ? res.commandReissues[0].args : null,
      });
    }
  }
  return found;
}

// ---------- main ----------
const meleeBankSet = new Set(Object.keys(melee.banks ?? {}));
const borgs = {};
const unresolvedGlobal = [];
let leavesTotal = 0;
let leavesResolved = 0;
let joinChecked = 0;
let joinOk = 0;
let joinHitStream = 0;
const familiesWalked = new Set();

const borgIds = Object.keys(cmd.borgs).sort();
for (const id of borgIds) {
  const info = cmd.borgs[id];
  const borgValue = parseInt(id.slice(2), 16);
  const ctorAddr = parseInt(info.constructorAddress, 16);
  const entry = {
    name: info.name,
    borgNumber: info.borgNumber,
    constructorAddress: info.constructorAddress,
    root: null,
    rootResolution: null,
    cueTable: null,
    familyBank: melee.borgs?.[id]?.familyBank ?? null,
    sharedBank: melee.borgs?.[id]?.sharedBank ?? null,
    actionTable: null,
    actions: {},
    unresolved: [],
  };

  // 1. resolve the +0x4b4 virtual and the +0x4f0 cue table
  const stores = collectCtorStores(ctorAddr, borgValue);
  const s4b4 = stores.get(0x4b4);
  const s4f0 = stores.get(0x4f0);
  let root = s4b4 && isText(s4b4.value) ? s4b4.value : null;
  let cueTableAddr = s4f0 && offsetFor(s4f0.value) !== null ? s4f0.value : null;
  if (root !== null) entry.rootResolution = `ctor store @${hex(s4b4.pc)}${s4b4.srcAddr ? ` (vector word @${hex(s4b4.srcAddr)})` : ""}`;
  if (root === null && info.pointerLabelAddress) {
    // vector inference: +0x4ec root label sits at vectorBase+0x38, +0x4b4 = word 0,
    // +0x4f0 = word 15 (same layout proven for 0x80365538 and 0x802d47b8)
    const base = parseInt(info.pointerLabelAddress, 16) - 0x38;
    const w0 = readU32(base);
    const w15 = readU32(base + 0x3c);
    if (w0 !== null && isText(w0)) {
      root = w0;
      entry.rootResolution = `vector inference (pointerLabel-0x38 = ${hex(base)})`;
      if (cueTableAddr === null && w15 !== null && offsetFor(w15) !== null) cueTableAddr = w15;
    }
  }
  entry.root = root === null ? null : hex(root);
  entry.cueTable = cueTableAddr === null ? null : hex(cueTableAddr);
  if (!entry.familyBank && stores.get(0x1d80) && stores.get(0x1d80).value >= 0x80000000) entry.familyBank = hex(stores.get(0x1d80).value);
  if (!entry.sharedBank && stores.get(0x1d84) && stores.get(0x1d84).value >= 0x80000000) entry.sharedBank = hex(stores.get(0x1d84).value);

  if (root === null) {
    entry.unresolved.push({ reason: "actor+0x4b4 virtual not recovered from ctor" });
    unresolvedGlobal.push({ borg: id, reason: "no +0x4b4 root" });
    borgs[id] = entry;
    continue;
  }
  familiesWalked.add(root);

  // 2. collect (actionIndex, variantIndex) pairs from command records whose cue maps to
  //    a full-body state that invokes the +0x4b4 virtual (state 61)
  const cueStates = cueTableAddr !== null ? decodeCueTable(cueTableAddr) : null;
  const pairs = new Map(); // key -> {ai, vi, via}
  const table = info.tableId ? cmd.tables[info.tableId] : null;
  if (table) {
    for (const type of table.types) {
      for (const rec of type.records) {
        if (rec.disabled || rec.actionIndex < 0 || rec.cueId < 0) continue;
        if (cueStates) {
          const st = cueStates[rec.cueId]?.[0];
          if (st === undefined || !virtualStates.includes(st)) continue;
        }
        const key = `${rec.actionIndex}:${rec.variantIndex}`;
        if (!pairs.has(key))
          pairs.set(key, { ai: rec.actionIndex, vi: rec.variantIndex, via: `command record type ${type.type} @${rec.address}` });
      }
    }
  }
  if (pairs.size === 0) {
    entry.unresolved.push({ reason: cueStates ? "no command records route to the +0x4b4 attack states" : "cue table missing; no pairs derived" });
    borgs[id] = entry;
    continue;
  }

  // 3. walk each pair (+ chain-discovered variants)
  const done = new Set();
  const work = [...pairs.values()];
  while (work.length > 0) {
    const { ai, vi, via } = work.shift();
    const key = `${ai}:${vi}`;
    if (done.has(key)) continue;
    done.add(key);
    leavesTotal++;
    const res = cachedRun(root, borgValue, ai, vi);
    const parsed = interpretRun(res, ai, vi, entry.familyBank, entry.sharedBank);
    if (parsed.actionTable && !entry.actionTable) entry.actionTable = parsed.actionTable;

    const actionKey = String(ai);
    entry.actions[actionKey] ??= { handler: parsed.handler, variantTable: parsed.variantTable, variants: {} };
    if (parsed.variantTable && !entry.actions[actionKey].variantTable) entry.actions[actionKey].variantTable = parsed.variantTable;

    const leafOut = {
      leaf: parsed.leaf,
      engine: parsed.engine,
      phaseTable: parsed.phaseTable,
      config: parsed.config,
      bank: parsed.bank ?? null,
      group: parsed.group ?? null,
      seedSlot: parsed.seedSlot ?? null,
      slotCandidates: parsed.slotCandidates ?? null,
      seedSource: parsed.seedSource ?? null,
      airSeedSlot: parsed.airSeedSlot ?? null,
      airSeedSource: parsed.airSeedSource ?? null,
      additionalStreams: parsed.additionalStreams ?? null,
      comboFollowUps: parsed.comboFollowUps ?? null,
      conditional: parsed.conditional ?? null,
      childSpawns: parsed.childSpawns?.length ? parsed.childSpawns : null,
      chainCallback: null,
      discoveredVia: via,
      evidence: `emulated ${hex(root)} with +0x580=${ai} +0x581=${vi}; stream call(s): ${res.calls
        .map((c) => {
          const f = Object.entries(c.flags)
            .map(([m, v]) => `${m}=${v}`)
            .join(",");
          return `${c.pc}(m${hex(c.mask)},g${c.group},s${c.slot}${f ? `,+0x5e0:${f}` : ""}${c.redirect !== null ? `,->v${c.redirect}` : ""})`;
        })
        .join(" ") || "none"}`,
    };

    // runtime +0x581 redirects (e.g. FUN_8018e0f8 jump-state -> variant 5): walk them too
    for (const st of res.stateStores) {
      if (st.offset === 0x581 && st.value !== vi && st.value >= 0 && st.value < 32) {
        const nk = `${ai}:${st.value}`;
        if (!done.has(nk) && !work.some((wk) => `${wk.ai}:${wk.vi}` === nk))
          work.push({ ai, vi: st.value, via: `runtime +0x581 redirect @${st.pc} from (${ai},${vi})` });
      }
    }

    if (parsed.resolved) {
      leavesResolved++;
      // chain callbacks from the config struct
      if (parsed.config?.kind === "pointer") {
        const cbs = discoverChainCallbacks(parseInt(parsed.config.address, 16), borgValue, ai, vi);
        if (cbs.length > 0) {
          leafOut.chainCallback = cbs[0];
          if (cbs.length > 1) leafOut.chainCallbacks = cbs;
          for (const cb of cbs) {
            if (cb.setsVariant !== null) {
              const nk = `${cb.setsAction ?? ai}:${cb.setsVariant}`;
              if (!done.has(nk)) work.push({ ai: cb.setsAction ?? ai, vi: cb.setsVariant, via: `chain callback ${cb.address} from (${ai},${vi}) config+${cb.configOffset}` });
            }
          }
        }
      }
      // join validation against the melee anim-kind bank layout
      if (leafOut.bank && leafOut.group !== null) {
        joinChecked++;
        const layout = parseBankLayout(parseInt(leafOut.bank, 16));
        const slotCount = layout[leafOut.group] ?? null;
        const bankPresent = meleeBankSet.has(leafOut.bank);
        const checkSlots = [
          ...(leafOut.seedSlot !== null ? [leafOut.seedSlot] : []),
          ...(leafOut.slotCandidates ?? []),
          ...(leafOut.airSeedSlot !== null ? [leafOut.airSeedSlot] : []),
        ];
        const slotInRange = slotCount !== null && checkSlots.every((s) => s < slotCount);
        leafOut.join = { bankPresent, groupSlotCount: slotCount, slotInRange };
        if (bankPresent && slotInRange) joinOk++;
        const hitStream = leafOut.seedSlot !== null && melee.banks?.[leafOut.bank]?.groups?.[`g${leafOut.group}`]?.[`s${leafOut.seedSlot}`] !== undefined;
        leafOut.join.hitStream = hitStream;
        if (hitStream) joinHitStream++;
      }
    } else {
      entry.unresolved.push({ action: ai, variant: vi, reason: parsed.diagnostics.note ?? "ambiguous", diagnostics: parsed.diagnostics, evidence: leafOut.evidence });
      unresolvedGlobal.push({ borg: id, action: ai, variant: vi, reason: parsed.diagnostics.note ?? "ambiguous" });
    }
    entry.actions[actionKey].variants[String(vi)] = leafOut;
  }
  borgs[id] = entry;
}

// ---------- ground-truth validation ----------
const failures = [];
function expectLeaf(id, ai, vi, want) {
  const leaf = borgs[id]?.actions?.[String(ai)]?.variants?.[String(vi)];
  if (!leaf) {
    failures.push(`${id} (${ai},${vi}): leaf missing`);
    return;
  }
  for (const [k, v] of Object.entries(want)) {
    const got = leaf[k];
    if (got !== v) failures.push(`${id} (${ai},${vi}): ${k} = ${JSON.stringify(got)}, want ${JSON.stringify(v)}`);
  }
}

// A) G RED family (ctor 0x8018ccfc; roster: pl0615 G RED, pl0629 NEO G RED, pl062a G BLACK).
// The report's "pl0615" validation rows (seeds 25/26/27/28/29/30/33) are byte-for-byte the
// DEFAULT branch of FUN_8018dd9c (variant table 0x80365614) - in the DOL that branch is
// taken by id 0x629 (NEO G RED), while id 0x615 selects 0x803655d4 and 0x62a 0x803655f4
// (chunk_0047.c:283-291). The air-B row (g4 s0) is the FUN_8018e888 default id branch,
// which id 0x615 takes (0x629 seeds +0x6ea=1, 0x62a seeds 4; chunk_0047.c:806-835).
// Both are validated below against their DOL-true owners.
if (borgs["pl0629"]) {
  const b = borgs["pl0629"];
  if (b.root !== "0x8018d24c") failures.push(`pl0629: root ${b.root} != 0x8018d24c`);
  if (b.actionTable !== "0x80365588") failures.push(`pl0629: actionTable ${b.actionTable} != 0x80365588`);
  if (b.actions["1"]?.variantTable !== "0x80365614") failures.push(`pl0629: a1 variantTable ${b.actions["1"]?.variantTable} != 0x80365614`);
  expectLeaf("pl0629", 1, 0, { engine: "0x80177dd8", group: 3, seedSlot: 25 });
  expectLeaf("pl0629", 1, 1, { engine: "0x80179280", group: 3, seedSlot: 29 });
  expectLeaf("pl0629", 1, 2, { engine: "0x80177dd8", group: 3, seedSlot: 28 });
  expectLeaf("pl0629", 1, 3, { engine: "0x80178394", group: 3, seedSlot: 30 });
  expectLeaf("pl0629", 1, 4, { engine: "0x80178394", group: 3, seedSlot: 33 });
  expectLeaf("pl0629", 1, 6, { engine: "0x80179280", group: 3, seedSlot: 27 });
  if (b.actions["1"]?.variants?.["0"]?.config?.address !== "0x80365664")
    failures.push(`pl0629 (1,0): config ${JSON.stringify(b.actions["1"]?.variants?.["0"]?.config)} != 0x80365664`);
  const chain = b.actions?.["1"]?.variants?.["0"]?.chainCallback;
  if (!chain || chain.setsVariant !== 6) failures.push(`pl0629 (1,0): chainCallback -> v6 missing (got ${JSON.stringify(chain)})`);
  const airLeaf = b.actions?.["2"] ? Object.values(b.actions["2"].variants)[0] : null;
  if (!airLeaf || airLeaf.group !== 4 || airLeaf.seedSlot !== 1)
    failures.push(`pl0629 a2: want g4 s1 (FUN_8018e888 0x629 branch), got ${JSON.stringify(airLeaf && { group: airLeaf.group, seedSlot: airLeaf.seedSlot })}`);
  const chargeLeaf = b.actions?.["3"] ? Object.values(b.actions["3"].variants)[0] : null;
  if (!chargeLeaf || chargeLeaf.group !== 4 || chargeLeaf.seedSlot !== 2 || chargeLeaf.airSeedSlot !== 2)
    failures.push(`pl0629 a3: want g4 s2/s2, got ${JSON.stringify(chargeLeaf && { group: chargeLeaf.group, seedSlot: chargeLeaf.seedSlot, airSeedSlot: chargeLeaf.airSeedSlot })}`);
} else failures.push("pl0629 missing from roster");
if (borgs["pl0615"]) {
  const b = borgs["pl0615"];
  if (b.root !== "0x8018d24c") failures.push(`pl0615: root ${b.root} != 0x8018d24c`);
  if (b.actions["1"]?.variantTable !== "0x803655d4")
    failures.push(`pl0615 a1 variantTable ${b.actions["1"]?.variantTable} != 0x803655d4 (FUN_8018dd9c 0x615 branch)`);
  expectLeaf("pl0615", 1, 0, { engine: "0x80177dd8", group: 3, seedSlot: 0 });
  const airLeaf = b.actions?.["2"] ? Object.values(b.actions["2"].variants)[0] : null;
  if (!airLeaf || airLeaf.group !== 4 || airLeaf.seedSlot !== 0)
    failures.push(`pl0615 a2: want g4 s0 (report air row), got ${JSON.stringify(airLeaf && { group: airLeaf.group, seedSlot: airLeaf.seedSlot })}`);
  const chargeLeaf = b.actions?.["3"] ? Object.values(b.actions["3"].variants)[0] : null;
  if (!chargeLeaf || chargeLeaf.group !== 4 || chargeLeaf.seedSlot !== 2 || chargeLeaf.airSeedSlot !== 2)
    failures.push(`pl0615 a3: want g4 s2/s2 (report charge row), got ${JSON.stringify(chargeLeaf && { group: chargeLeaf.group, seedSlot: chargeLeaf.seedSlot, airSeedSlot: chargeLeaf.airSeedSlot })}`);
} else failures.push("pl0615 missing from roster");

// B) pl0200 Sword Knight
if (borgs["pl0200"]) {
  const b = borgs["pl0200"];
  if (b.root !== "0x80073f3c") failures.push(`pl0200: root ${b.root} != 0x80073f3c`);
  if (b.actions["1"]?.variantTable !== "0x802d4844") failures.push(`pl0200: a1 variantTable ${b.actions["1"]?.variantTable} != 0x802d4844`);
  expectLeaf("pl0200", 1, 0, { group: 3, seedSlot: 0 });
  expectLeaf("pl0200", 1, 1, { group: 3, seedSlot: 3 });
  expectLeaf("pl0200", 1, 2, { group: 3, seedSlot: 4 });
  const chargeActions = Object.entries(b.actions).filter(([, a]) =>
    Object.values(a.variants).some((v) => v.group === 4),
  );
  const chargeLeaf = chargeActions.flatMap(([, a]) => Object.values(a.variants)).find((v) => v.group === 4);
  if (!chargeLeaf || chargeLeaf.seedSlot !== 0 || chargeLeaf.airSeedSlot !== 1)
    failures.push(`pl0200 charge: want g4 s0 ground / s1 air, got ${JSON.stringify(chargeLeaf && { group: chargeLeaf.group, seedSlot: chargeLeaf.seedSlot, airSeedSlot: chargeLeaf.airSeedSlot })}`);
} else failures.push("pl0200 missing from roster");

// ---------- emit ----------
const output = {
  _meta: {
    generatedBy: "scripts/gen-action-stream-tables.mjs",
    source: `user-data/${region}/disc/sys/boot.dol`,
    report: REPORT,
    method:
      "concrete PPC emulation of the +0x4b4 attack virtual per (borg, actionIndex +0x580, variantIndex +0x581); " +
      "captures zz_004beb8_(rate, actor, 0xf, group, slot) stream calls with config-byte provenance; " +
      "airborne forks labelled via (actor+0x5e0 & 0x40); chain callbacks discovered from config struct words " +
      "that store an immediate to actor+0x581",
    evidence: {
      stateDispatch: "FUN_80055568 chunk_0006.c:7793-7798; state 61 = FUN_80065dfc chunk_0008.c:2724-2731",
      familyDispatch: "zz_018d24c_ chunk_0046.c:5063; FUN_8018dd9c chunk_0047.c:283-291; FUN_80073f3c chunk_0010.c:1380-1386",
      streamPlayer: "zz_004beb8_ chunk_0006.c:1431-1492 (bank +0x1d80/+0x1d84, group offset, slot offset)",
      engines:
        "zz_0177dd8_/zz_0178394_/zz_0178b6c_/zz_0179280_ (group 3, phase tables 0x80352b08/18/2c/40), " +
        "zz_0179814_/zz_0179d20_/zz_0179fcc_ (group 4, 0x80352b54/0x804347a8/0x80352b64), " +
        "zz_015809c_/zz_0158688_/zz_0158a94_ (group 3, immediate seed, 0x80343c00-28); chunk_0044.c/chunk_0040.c",
      airborne: "FUN_80179850 chunk_0044.c:3934-3936; zz_007454c_ chunk_0010.c:1687",
      chainCallbacks: "FUN_801780e4 chunk_0044.c:3141-3143 (config+0x10); FUN_80177fd4 chunk_0044.c:3094-3096 (config+0x14); FUN_8018ded0 chunk_0047.c:335-341",
    },
    virtualStates,
    coverage: {
      rosterBorgs: borgIds.length,
      borgsWithRoot: Object.values(borgs).filter((b) => b.root !== null).length,
      familyRootsWalked: familiesWalked.size,
      leavesTotal,
      leavesResolved,
      leavesUnresolved: leavesTotal - leavesResolved,
      joinChecked,
      joinOk,
      joinCoverage: joinChecked > 0 ? +(joinOk / joinChecked).toFixed(4) : null,
      joinHitStreams: joinHitStream,
    },
    groundTruth: {
      failures,
      note:
        "the report's 'G RED pl0615' melee validation rows (seeds 25/26/27/28/29/30/33, table 0x80365614) are " +
        "the DEFAULT borg-id branch of FUN_8018dd9c, which in the DOL belongs to id 0x629 (NEO G RED); id 0x615 " +
        "selects 0x803655d4 (seed-0 ladder) and 0x62a selects 0x803655f4 (chunk_0047.c:283-291). The report's " +
        "air row (g4 s0) belongs to id 0x615 (FUN_8018e888 default branch; 0x629 seeds +0x6ea=1, 0x62a seeds 4). " +
        "Both borgs are validated against their DOL-true tables here; the charge row (g4 s2/s2) holds for both.",
    },
    format:
      "borgs[id].actions[actionIndex].variants[variantIndex] = {leaf, engine, phaseTable, config, bank, group, " +
      "seedSlot (config ground seed; combo ladder replays with +0x6ea auto-increment), airSeedSlot, chainCallback " +
      "{address, configOffset, setsVariant}, join (vs meleeAnimKinds.json bank layout)}; seedSlot null + seedSource " +
      "runtime:* = dynamic cursor (+0x6ee dash rams)",
  },
  borgs,
  unresolved: unresolvedGlobal,
};

fs.mkdirSync(path.dirname(OUT_PATH), { recursive: true });
fs.writeFileSync(OUT_PATH, JSON.stringify(output, null, 1) + "\n");
console.log(
  `actionStreamTables.json: ${output._meta.coverage.borgsWithRoot}/${borgIds.length} borgs rooted, ` +
    `${familiesWalked.size} family roots, ${leavesResolved}/${leavesTotal} leaves resolved, ` +
    `join ${joinOk}/${joinChecked} (${(100 * (joinOk / Math.max(joinChecked, 1))).toFixed(1)}%), ` +
    `${joinHitStream} hit-bearing streams`,
);
if (failures.length > 0) {
  console.error("GROUND TRUTH FAILURES:");
  for (const f of failures) console.error("  " + f);
  process.exit(1);
}
console.log("ground truth: G RED family + pl0200 Sword Knight validated OK");
