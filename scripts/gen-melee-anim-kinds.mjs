#!/usr/bin/env node
// Generate packages/combat/src/data/meleeAnimKinds.json: per borg -> action-script bank ->
// per (group,slot) -> ordered decoded events (HIT-kind arms + anim context).
//
// DERIVED (2026-07-04 session, motion-event decode):
// - The per-animation byte-code streams walked by zz_004c050_ (chunk_0006.c:1523) are NOT
//   in pl####mot.bin. They are static boot.dol tables bound per family ctor:
//     actor+0x1d80 = family action-script bank (e.g. G RED ctor 0x8018ccfc ->
//                    0x80366220, chunk_0046.c:4808)
//     actor+0x1d84 = shared action-script bank (usually 0x802bc080; G RED 0x802bcc64)
//   (+0x1d88/+0x1d8c are the parallel anim-descriptor banks, zz_004d1f4_ chunk_0006.c:2210.)
// - Bank layout (zz_004beb8_ chunk_0006.c:1461/1476-1490):
//     bank base: s16 group-offset array (offsets relative to base; -1 = no group;
//                first offset / 2 = group count in practice, walker below is bound-based)
//     group ptr: s16 slot-offset array (relative to group ptr) -> byte-code stream.
//   Anim-group byte 0x80 flag selects the shared bank (group = byte & 0x7f).
// - Stream record format (opcode table PTR_FUN_802d0da0 @ 0x802d0da0, 18 entries 0x00-0x11;
//   record sizes verified from each handler's `*streamPtr += N` in the DOL):
//     op 0x00 wait/terminator (4B): byte1 = mode (bit0 end-of-script; bit1 frame relative
//              to anim end; bit2 percent-of-anim; bit3 realtime countdown; else absolute
//              anim frame; val -1 + mode 0 = wait for anim end), s16@2 = value.
//              Interpreter zz_004cd24_ (chunk_0006.c:1996) resumes at record+4 when met.
//     op 0x01 playAnim (8B, FUN_8004c298): byte1 = anim group (|0x80 shared), byte2 = slot.
//     op 0x0d blendAnim (8B, FUN_8004c7fc): same byte1/byte2 meaning.
//     op 0x02/0x03 (8B), all remaining ops (4B).
//     op 0x0a ARM HIT (4B, FUN_8004c6b4 chunk_0006.c:1727): byte1 = HIT kind (>0) ->
//              zz_008ac80_(actor, kind) spawns the hit.bin remap entries (frame window
//              activeStart/activeEnd comes from the hit.bin record, chunk_0013.c:1351-1413);
//              byte2/byte3 = status-effect id/arg (actor+0x6f8/+0x6f9).
//     op 0x09 fireChild (4B, FUN_8004c67c -> zz_0099e70_): s16@2 low byte = child variant.
// - Validation (pl0615 G RED): 27 distinct armHit kinds extracted from its family bank,
//   27/27 present in its hit.bin remap table (attackHitTables.json), including all melee
//   kinds 1-15,17,18. Shared banks carry no armHit events (movement/reaction anims).
//
// Usage: node scripts/gen-melee-anim-kinds.mjs [GG4E]
import fs from "node:fs";
import path from "node:path";

const repoRoot = path.resolve(".");
const region = process.argv[2] ?? "GG4E";
const DOL_PATH = path.join(repoRoot, "user-data", region, "disc", "sys", "boot.dol");
const CMD_PATH = path.join(repoRoot, "packages", "combat", "src", "data", "commandMoveTables.json");
const HIT_PATH = path.join(repoRoot, "packages", "combat", "src", "data", "attackHitTables.json");
const OUT_PATH = path.join(repoRoot, "packages", "combat", "src", "data", "meleeAnimKinds.json");

const dol = fs.readFileSync(DOL_PATH);
const cmd = JSON.parse(fs.readFileSync(CMD_PATH, "utf8"));
const hit = JSON.parse(fs.readFileSync(HIT_PATH, "utf8"));

const sectionOffsets = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(i * 4));
const sectionAddresses = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x48 + i * 4));
const sectionSizes = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x90 + i * 4));
function offsetFor(a) {
  for (let i = 0; i < 18; i++)
    if (sectionSizes[i] > 0 && a >= sectionAddresses[i] && a < sectionAddresses[i] + sectionSizes[i])
      return sectionOffsets[i] + (a - sectionAddresses[i]);
  return null;
}
const readU32 = (a) => {
  const o = offsetFor(a >>> 0);
  return o === null ? null : dol.readUInt32BE(o);
};
const readS16 = (a) => {
  const o = offsetFor(a >>> 0);
  return o === null ? null : dol.readInt16BE(o);
};
const readU8 = (a) => {
  const o = offsetFor(a >>> 0);
  return o === null ? null : dol.readUInt8(o);
};
const sign16 = (v) => (v & 0x8000 ? (v & 0xffff) - 0x10000 : v & 0xffff);
const hex = (v) => "0x" + (v >>> 0).toString(16);

// ---------- ctor scan: recover +0x1d80/+0x1d84 stores per borg ----------
// Borg-id-aware straight-line emulation (compare handling as in
// scripts/gen-command-move-tables.mjs collectConstructorStoresForBorg) plus bl-following
// (as in scripts/scan-damage-table-bindings.mjs) because several families bind the banks
// in a shared base-init reached via bl.
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
function branchConditionMet(word, cr0) {
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

function collectBankStores(ctorAddress, borgValue) {
  const stores = new Map(); // actor offset -> value (last write wins, call order)
  const visit = (entry, depth, visited) => {
    if (depth > 3 || visited.has(entry)) return;
    visited.add(entry);
    const regs = Array.from({ length: 32 }, () => null);
    let cr0 = null;
    let pc = entry;
    for (let steps = 0; steps < 1200; steps++) {
      const word = readU32(pc);
      if (word === null) return;
      const op = word >>> 26;
      const rt = (word >>> 21) & 31;
      const ra = (word >>> 16) & 31;
      const simm = sign16(word);
      const rawImm = word & 0xffff;
      let next = pc + 4;
      if (op === 15 && ra === 0) regs[rt] = ((rawImm << 16) >>> 0);
      else if (op === 14)
        regs[rt] = ra === 0 ? simm >>> 0 : regs[ra] !== null ? (regs[ra] + simm) >>> 0 : null;
      else if (op === 10) cr0 = regs[ra] === null ? null : compareValues(regs[ra] >>> 0, rawImm);
      else if (op === 11) cr0 = regs[ra] === null ? null : compareValues(regs[ra] | 0, simm);
      else if (op === 32) regs[rt] = regs[ra] !== null ? readU32(regs[ra] + simm) : null;
      else if (op === 34) {
        const av = ra === 3 ? actorLoadValue(simm, borgValue) : null;
        regs[rt] = av !== null ? av & 0xff : regs[ra] !== null ? readU8(regs[ra] + simm) : null;
      } else if (op === 42) {
        const av = ra === 3 ? actorLoadValue(simm, borgValue) : null;
        regs[rt] = av !== null ? sign16(av) : regs[ra] !== null ? readS16(regs[ra] + simm) : null;
      } else if (op === 36) {
        if (ra === 3 && (simm === 0x1d80 || simm === 0x1d84)) stores.set(simm, regs[rt]);
      } else if (op === 16) {
        const taken = branchConditionMet(word, cr0);
        if (taken) {
          const raw = word & 0xfffc;
          const disp = raw >= 0x8000 ? raw - 0x10000 : raw;
          next = (word & 2) !== 0 ? disp >>> 0 : (pc + disp) >>> 0;
          if (next <= pc) return; // backward conditional = loop; bail
        }
      } else if (op === 18) {
        let li = word & 0x03fffffc;
        if (li & 0x02000000) li -= 0x04000000;
        const target = (word & 2) !== 0 ? li >>> 0 : (pc + li) >>> 0;
        if (word & 1) {
          visit(target, depth + 1, visited);
          for (let r = 0; r <= 12; r++) if (r !== 3) regs[r] = null;
          cr0 = null;
        } else {
          next = target;
          if (target <= pc) return;
        }
      } else if (op === 19 && (word & 0xfc0007fe) === 0x4c000020) {
        // bclr: conditional returns matter (variant guards like pl0511's
        // `lha r0,0x3e8(r3); cmpwi 0x511; bnelr` at 0x801e799c-0x801e79a4)
        const taken = branchConditionMet(word, cr0);
        if (taken || taken === null) return; // unknown condition: stop (conservative)
      } else if ([33, 35, 40, 41, 43, 46, 48, 50].includes(op) || op === 31) regs[rt] = null;
      pc = next;
    }
  };
  visit(ctorAddress, 0, new Set());
  return stores;
}

// ---------- bank parsing ----------
// Verified table conventions (pl0615 family/shared banks, 0x802bf040, 0x802bc080):
// - group offset array: entry count = smallest positive offset / 2 (the first slot table
//   starts immediately after the group array); -1 = unused group; negative offsets are
//   valid cross-bank backrefs (e.g. 0x802bcc64 group 0 -> 0x802bc088 in the common bank).
// - slot offset arrays: -1 sentinel terminates every table; non-last tables are also
//   bounded by the next table's start (both rules agree on all sampled banks).

const OP_SIZE8 = new Set([0x01, 0x02, 0x03, 0x0d]);

// Decode one stream. streamStarts = set of all slot stream addresses in this bank, used
// to cut the designed fall-through chains at the next slot's entry point.
function decodeStream(addr, streamStarts) {
  const events = [];
  let p = addr;
  let frame = 0;
  let frameKind = "start"; // start | abs | relEnd | pct | timer | animEnd
  let lastAnim = null;
  let sawWait = false;
  for (let n = 0; n < 400; n++) {
    if (n > 0 && sawWait && streamStarts.has(p) && p !== addr)
      return { events, end: "fallsThrough", fallsThroughTo: hex(p) };
    const op = readU8(p);
    if (op === null || op > 0x11) {
      // ran into non-stream data; drop anything after the last wait (junk guard)
      let lastWait = -1;
      for (let i = events.length - 1; i >= 0; i--)
        if (events[i].op === "wait") {
          lastWait = i;
          break;
        }
      return { events: events.slice(0, lastWait + 1), end: "truncated" };
    }
    if (op === 0x00) {
      const mode = readU8(p + 1);
      const val = readS16(p + 2);
      events.push({ op: "wait", mode, val });
      sawWait = true;
      if (mode & 1) return { events, end: "terminated" };
      if (mode & 8) {
        frame = (frameKind === "abs" ? frame : 0) + val;
        frameKind = "timer";
      } else if (mode & 2) {
        frame = val;
        frameKind = "relEnd";
      } else if (mode & 4) {
        frame = val;
        frameKind = "pct";
      } else if (val >= 0) {
        frame = val;
        frameKind = "abs";
      } else {
        frame = null;
        frameKind = "animEnd";
      }
      p += 4;
      continue;
    }
    const len = OP_SIZE8.has(op) ? 8 : 4;
    const b = [];
    for (let i = 0; i < len; i++) b.push(readU8(p + i));
    if (op === 0x01 || op === 0x0d) {
      lastAnim = { shared: !!(b[1] & 0x80), group: b[1] & 0x7f, slot: b[2] };
      frame = 0;
      frameKind = "start";
      events.push({ op: op === 0x01 ? "playAnim" : "blendAnim", ...lastAnim });
    } else if (op === 0x0a) {
      const kind = (b[1] << 24) >> 24;
      events.push({
        op: "armHit",
        kind,
        frame,
        frameKind,
        statusId: b[2],
        statusArg: b[3],
        anim: lastAnim, // null = arms before the first playAnim of this stream
      });
    } else if (op === 0x09) {
      events.push({ op: "fireChild", variant: (b[3] << 24) >> 24 });
    }
    p += len;
  }
  return { events, end: "iterationLimit" };
}

function parseBank(base) {
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
  const slotTables = new Map();
  const streamStarts = new Set();
  for (const gp of distinct) {
    // -1 sentinel is the primary terminator (every sampled table ends with one, and
    // cross-bank backref tables have no in-bank next-table bound); the next distinct
    // table start acts as a safety cap only.
    const next = distinct.find((s) => s > gp);
    const count = next ? Math.floor((next - gp) / 2) : 0x2000;
    const slots = [];
    for (let i = 0; i < count; i++) {
      const v = readS16(gp + i * 2);
      if (v === null || v === -1) break;
      slots.push(gp + v);
    }
    slotTables.set(gp, slots);
    for (const s of slots) if (s !== null) streamStarts.add(s);
  }
  const groups = groupPtrs.map((gp, g) =>
    gp === null ? null : { group: g, groupPtr: gp, slots: slotTables.get(gp) },
  );
  return { groups, streamStarts };
}

// ---------- run over all borgs ----------
const borgIds = Object.keys(cmd.borgs).sort();
const bankCache = new Map(); // bank address -> decoded {groups: {g: {s: {events,end}}}} (hit slots only)
const bankStats = new Map();

function decodeBank(base) {
  const key = hex(base);
  if (bankCache.has(key)) return bankCache.get(key);
  const { groups, streamStarts } = parseBank(base);
  const out = {};
  let slotCount = 0;
  let hitSlotCount = 0;
  let eventCount = 0;
  for (const g of groups) {
    if (!g) continue;
    for (let s = 0; s < g.slots.length; s++) {
      const addr = g.slots[s];
      if (addr === null) continue;
      slotCount++;
      const { events, end, fallsThroughTo } = decodeStream(addr, streamStarts);
      const hits = events.filter((e) => e.op === "armHit" && e.kind > 0);
      if (hits.length === 0) continue;
      hitSlotCount++;
      eventCount += events.length;
      out[`g${g.group}`] ??= {};
      out[`g${g.group}`][`s${s}`] = {
        streamAddress: hex(addr),
        end,
        ...(fallsThroughTo ? { fallsThroughTo } : {}),
        events,
      };
    }
  }
  const decoded = { groups: out };
  bankCache.set(key, decoded);
  bankStats.set(key, { slotCount, hitSlotCount, eventCount });
  return decoded;
}

const borgs = {};
const unresolved = [];
const bankless = [];
const validation = { checked: 0, clean: 0, mismatched: [] };
for (const id of borgIds) {
  const ctor = parseInt(cmd.borgs[id].constructorAddress, 16);
  const borgValue = parseInt(id.slice(2), 16);
  const stores = collectBankStores(ctor, borgValue);
  const isBank = (v) => typeof v === "number" && v >= 0x80000000;
  const family = isBank(stores.get(0x1d80)) ? stores.get(0x1d80) : null;
  const shared = isBank(stores.get(0x1d84)) ? stores.get(0x1d84) : null;
  if (!family && !shared) {
    // explicit `li r5,0` stores = genuinely bankless (code-driven borg, e.g. the
    // pl0d##/pl0e## bosses; zz_004beb8_ early-returns when +0x1d80/84 are 0)
    if (stores.get(0x1d80) === 0 || stores.get(0x1d84) === 0) bankless.push(id);
    else unresolved.push(id);
    continue;
  }
  const entry = { familyBank: family ? hex(family) : null, sharedBank: shared ? hex(shared) : null };
  const kinds = new Set();
  for (const bank of [family, shared]) {
    if (!bank) continue;
    const decoded = decodeBank(bank);
    for (const g of Object.values(decoded.groups))
      for (const slot of Object.values(g))
        for (const e of slot.events) if (e.op === "armHit" && e.kind > 0) kinds.add(e.kind);
  }
  entry.hitKinds = [...kinds].sort((a, b) => a - b);
  // validate against the borg's hit.bin remap table
  const remap = hit.borgs?.[id]?.kinds;
  if (remap) {
    validation.checked++;
    const remapKinds = new Set(Object.keys(remap).map(Number));
    const bad = entry.hitKinds.filter((k) => !remapKinds.has(k));
    if (bad.length === 0) validation.clean++;
    else {
      validation.mismatched.push({ id, kindsNotInRemap: bad });
      entry.kindsNotInRemap = bad;
    }
  }
  borgs[id] = entry;
}

const banks = Object.fromEntries([...bankCache.entries()].sort());
const totalHitSlots = [...bankStats.values()].reduce((a, v) => a + v.hitSlotCount, 0);
const totalEvents = [...bankStats.values()].reduce((a, v) => a + v.eventCount, 0);

const payload = {
  _meta: {
    source: "user-data/<region>/disc/sys/boot.dol (action-script banks bound at actor+0x1d80/+0x1d84)",
    generator: "scripts/gen-melee-anim-kinds.mjs",
    evidence:
      "zz_004beb8_/zz_004c050_/FUN_8004c6b4 chunk_0006.c:1431-1747; zz_004cd24_ chunk_0006.c:1996; " +
      "opcode table PTR_FUN_802d0da0 @0x802d0da0 (18 handlers, record sizes verified from DOL); " +
      "research/decomp/movement-hit-decode-2026-07-04.md section 2",
    format:
      "banks[addr].groups.gN.sM.events = ordered stream events; armHit.kind feeds zz_008ac80_ " +
      "(hit.bin remap -> hitbox records; active frame window comes from the hit.bin record, " +
      "not the stream); armHit.frame/frameKind = wait context when armed (start = anim start); " +
      "anim = last playAnim/blendAnim before the arm (group byte 0x80 flag -> shared descriptor bank)",
    region,
    borgs: Object.keys(borgs).length,
    banklessBorgs: bankless,
    unresolvedBorgs: unresolved,
    distinctBanks: bankCache.size,
    hitBearingSlots: totalHitSlots,
    totalEventsInHitSlots: totalEvents,
    validation: {
      borgsCheckedAgainstHitBinRemap: validation.checked,
      clean: validation.clean,
      mismatched: validation.mismatched,
    },
  },
  banks,
  borgs,
};

fs.writeFileSync(OUT_PATH, JSON.stringify(payload, null, 1) + "\n");
console.log(
  `meleeAnimKinds.json: ${Object.keys(borgs).length}/${borgIds.length} borgs, ` +
    `${bankCache.size} distinct banks, ${totalHitSlots} hit-bearing slots, ` +
    `validation ${validation.clean}/${validation.checked} clean` +
    (validation.mismatched.length
      ? `; MISMATCHED: ${validation.mismatched.map((m) => `${m.id}(${m.kindsNotInRemap})`).join(", ")}`
      : "") +
    (bankless.length ? `; bankless (code-driven): ${bankless.join(",")}` : "") +
    (unresolved.length ? `; UNRESOLVED: ${unresolved.join(",")}` : ""),
);
