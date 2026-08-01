#!/usr/bin/env node
// Generate packages/combat/src/data/chargeFireChildFrames.generated.json:
// per B-charge borg (actionIndex 3) -> {bank, group, slot, fireChildEvents, decode}.
//
// WHY THIS EXISTS
//   The captured meleeAnimKinds.json records stream events only for HIT-bearing slots
//   and — for the charge streams — the beam is NOT spawned by a captured melee-style
//   armHit. G RED's family bank 0x80366220 g4s2 (the B-charge stream) was assumed
//   (packages/combat/src/families/shared-charge.ts:21,251) to spawn its beam via stream
//   op 0x09 fireChild. This script walks the RAW bank bytes at every charge borg's
//   (bank, group, slot) and reports the truth: which charge streams actually contain a
//   fireChild op, at what frame, with what variant — and which do not (beam then
//   spawns via the engine's cfg+0x14 release callback, e.g. zz_00e19a8_ for G RED;
//   chunk_0047.c:1003-1013).
//
// METHOD
//   - DOL section map + readU8/readS16/readU32 (same harness as gen-melee-anim-kinds.mjs
//     and gen-action-stream-tables.mjs).
//   - parseBank() and decodeStream() are 1:1 ports of gen-melee-anim-kinds.mjs:311-298,
//     using the op-length table DERIVED from the DOL handler `*streamPtr += N` walks
//     (8B for {0x01,0x02,0x03,0x0d}, 4B otherwise; see stream-vm.ts:22-41 OP_SIZE).
//   - Wait-frame context is tracked exactly as in the validated walker
//     (gen-melee-anim-kinds.mjs:191-230): bit0 mode = terminator, bit1 relEnd, bit2 pct,
//     bit3 timer, mode==0 & val>=0 abs, mode==0 & val<0 animEnd. fireChild's frame is
//     the live wait-context frame at the op (mirrors how armHit.frame is published).
//   - Bank/group/slot for each (borg, action 3, variant) is read from the already-
//     validated actionStreamTables.json (concrete-PPC-emulation provenance, see its
//     _meta.evidence). Variants sharing a stream dedupe to one walk.
//
// USAGE: node scripts/gen-charge-firechild-frames.mjs [GG4E]
import fs from "node:fs";
import path from "node:path";

const repoRoot = path.resolve(".");
const region = process.argv[2] ?? "GG4E";
const DOL_PATH = path.join(repoRoot, "user-data", region, "disc", "sys", "boot.dol");
const TABLES_PATH = path.join(
  repoRoot,
  "packages",
  "combat",
  "src",
  "data",
  "actionStreamTables.json",
);
const OUT_PATH = path.join(
  repoRoot,
  "packages",
  "combat",
  "src",
  "data",
  "chargeFireChildFrames.generated.json",
);

const dol = fs.readFileSync(DOL_PATH);
const tables = JSON.parse(fs.readFileSync(TABLES_PATH, "utf8"));

// ---------- DOL section mapping (as gen-action-stream-tables.mjs) ----------
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
const readU8 = (a) => { const o = offsetFor(a); return o === null ? null : dol.readUInt8(o); };
const readS16 = (a) => { const o = offsetFor(a); return o === null ? null : dol.readInt16BE(o); };
const readU32 = (a) => { const o = offsetFor(a); return o === null ? null : dol.readUInt32BE(o); };
const hex = (v) => "0x" + (v >>> 0).toString(16);

// ---------- bank parsing (1:1 port of gen-melee-anim-kinds.mjs:311-347) ----------
// To bound group arrays against interleaved neighbor banks we collect every bank base
// referenced by ANY borg's action-3 entry first (same trick gen-melee uses with
// allBankBases; here the universe is just the charge banks, which is sufficient because
// shared/family bases are already mutually distinct in the corpus).
const allBankBases = new Set();

function parseBank(base) {
  const rawGroups = [];
  let minPos = Infinity;
  for (let i = 0; ; i++) {
    if (i * 2 >= Math.min(minPos, 0x200)) break;
    if (i > 0 && allBankBases.has(base + i * 2)) break;
    const v = readS16(base + i * 2);
    if (v === null) break;
    rawGroups.push(v);
    if (v > 0) minPos = Math.min(minPos, v);
  }
  const groupPtrs = rawGroups.map((v) => (v === -1 ? null : base + v));
  const distinct = [...new Set(groupPtrs.filter((p) => p !== null))].sort((a, b) => a - b);
  const slotTables = new Map();
  const streamStarts = new Set();
  for (const gp of distinct) {
    const slots = [];
    for (let i = 0; i < 0x40; i++) {
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

// ---------- stream decoding (1:1 port of gen-melee-anim-kinds.mjs:188-298) ----------
const OP_SIZE8 = new Set([0x01, 0x02, 0x03, 0x0d]);

function decodeStream(addr, streamStarts) {
  const events = [];
  let p = addr;
  let frame = 0;
  let frameKind = "start";
  let lastAnim = null;
  let sawWait = false;
  // `otherRecognizedOps` lists ops 0x04-0x08, 0x0b, 0x0c, 0x0e-0x11 — VALID ops the
  // op-length table decodes cleanly but which carry no spawn-timing payload. These are
  // NOT decode failures. A genuine decode failure (op byte > 0x11, hitting non-stream
  // data) ends the walk with end="truncated" and is recorded in the summary.
  const otherRecognizedOps = [];
  let decodeFailure = null;
  for (let n = 0; n < 400; n++) {
    if (n > 0 && sawWait && streamStarts.has(p) && p !== addr)
      return { events, end: "fallsThrough", fallsThroughTo: hex(p), otherRecognizedOps, decodeFailure };
    const op = readU8(p);
    if (op === null || op > 0x11) {
      decodeFailure = { addr: hex(p), opByte: op, reason: op === null ? "read_out_of_section" : "op > 0x11 (non-stream data / table end)" };
      let lastWait = -1;
      for (let i = events.length - 1; i >= 0; i--)
        if (events[i].op === "wait") { lastWait = i; break; }
      return { events: events.slice(0, lastWait + 1), end: "truncated", otherRecognizedOps, decodeFailure };
    }
    if (op === 0x00) {
      const mode = readU8(p + 1);
      const val = readS16(p + 2);
      events.push({ op: "wait", mode, val });
      sawWait = true;
      if (mode & 1) return { events, end: "terminated", otherRecognizedOps, decodeFailure };
      if (mode & 8) { frame = (frameKind === "abs" ? frame : 0) + val; frameKind = "timer"; }
      else if (mode & 2) { frame = val; frameKind = "relEnd"; }
      else if (mode & 4) { frame = val; frameKind = "pct"; }
      else if (val >= 0) { frame = val; frameKind = "abs"; }
      else { frame = null; frameKind = "animEnd"; }
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
    } else if (op === 0x02) {
      events.push({ op: "partState", part: 0, state: (b[2] << 24) >> 24, aux: (b[3] << 24) >> 24, frame, frameKind });
    } else if (op === 0x03) {
      events.push({ op: "partState", part: 1, state: (b[1] << 24) >> 24, aux: (b[2] << 24) >> 24, frame, frameKind });
    } else if (op === 0x0a) {
      events.push({ op: "armHit", kind: (b[1] << 24) >> 24, frame, frameKind, statusId: b[2], statusArg: b[3], anim: lastAnim });
    } else if (op === 0x09) {
      // fireChild: byte3 sign-extended = child variant (stream-vm.ts:319-322;
      // gen-melee-anim-kinds.mjs:274-275). Frame context recorded here (the
      // gen-melee walker omitted it for fireChild; this generator adds it).
      events.push({ op: "fireChild", variant: (b[3] << 24) >> 24, frame, frameKind, anim: lastAnim, addr: hex(p) });
    } else {
      // 0x04..0x08, 0x0b, 0x0c, 0x0e..0x11 — recognized ops (op-length table decodes
      // them) that carry no spawn-timing payload. Listed for completeness; NOT a
      // decode failure.
      otherRecognizedOps.push({ op, addr: hex(p) });
    }
    p += len;
  }
  return { events, end: "iterationLimit", otherRecognizedOps, decodeFailure };
}

// ---------- enumerate charge borgs ----------
// Collect all (borgId, action 3, variant) entries and the universe of bank bases.
const chargeBorgs = [];
for (const [id, b] of Object.entries(tables.borgs)) {
  const a3 = b.actions?.["3"];
  if (!a3) continue;
  const variants = [];
  for (const [vi, v] of Object.entries(a3.variants || {})) {
    variants.push({ vi, ...v });
    if (v.bank) allBankBases.add(parseInt(v.bank, 16));
  }
  chargeBorgs.push({ id, name: b.name, borgNumber: b.borgNumber, familyBank: b.familyBank, sharedBank: b.sharedBank, actionHandler: a3.handler, variants });
}
for (const base of allBankBases) {
  // ensure parseBank neighbor-bounds see every charge bank base
}

// ---------- walk ----------
const borgs = {};
const failures = [];
const bankCache = new Map();
function decodeBankRef(baseAddr) {
  if (bankCache.has(baseAddr)) return bankCache.get(baseAddr);
  const decoded = parseBank(baseAddr);
  const out = {};
  for (const g of decoded.groups) {
    if (!g) continue;
    for (let s = 0; s < g.slots.length; s++) {
      const addr = g.slots[s];
      if (addr === null) continue;
      const res = decodeStream(addr, decoded.streamStarts);
      out[`g${g.group}s${s}`] = { streamAddress: hex(addr), ...res };
    }
  }
  const result = { groups: out, groupPtrs: decoded.groups };
  bankCache.set(baseAddr, result);
  return result;
}

function variantStreamKey(v) {
  return `${v.bank}|g${v.group}|s${v.seedSlot}|air${v.airSeedSlot}`;
}

for (const cb of chargeBorgs) {
  const entry = { borgId: cb.id, name: cb.name, borgNumber: cb.borgNumber, actionHandler: cb.actionHandler, streams: {} };
  // Group variants by their resolved stream key (most charge variants share one stream).
  const byStream = new Map();
  for (const v of cb.variants) {
    const key = variantStreamKey(v);
    if (!byStream.has(key)) byStream.set(key, { variants: [], v });
    byStream.get(key).variants.push(v.vi);
  }
  for (const [, { variants: vis, v }] of byStream) {
    const bankAddr = v.bank ? parseInt(v.bank, 16) : null;
    const group = v.group;
    const slot = v.seedSlot;
    const airSlot = v.airSeedSlot;
    const streamRef = {
      variants: vis,
      bank: v.bank,
      group,
      seedSlot: slot,
      airSeedSlot: airSlot,
      seedSource: v.seedSource,
      engine: v.engine,
      phaseTable: v.phaseTable,
      configAddress: v.config?.address ?? null,
    };
    if (bankAddr === null || group === null) {
      streamRef.status = "unresolved_static";
      streamRef.reason = "no stream call reached for this variant (bank/group null in actionStreamTables — variant is dead data or the startStream path was not captured by the concrete emulator; borg familyBank=" + cb.familyBank + ")";
      entry.streams[vis.join(",")] = streamRef;
      continue;
    }
    let decoded;
    try {
      decoded = decodeBankRef(bankAddr);
    } catch (e) {
      streamRef.status = "bank_decode_failed";
      streamRef.reason = String(e && e.message ? e.message : e);
      failures.push({ borgId: cb.id, variants: vis, bank: v.bank, reason: streamRef.reason });
      entry.streams[vis.join(",")] = streamRef;
      continue;
    }
    if (slot === null) {
      // bank+group known but slot is a runtime cursor. If slotCandidates are enumerated,
      // scan every candidate so we can still report fireChild presence exhaustively.
      if (Array.isArray(v.slotCandidates) && v.slotCandidates.length) {
        streamRef.scannedAllCandidates = true;
        streamRef.candidates = [];
        let anyFc = 0;
        for (const candSlot of v.slotCandidates) {
          const candKey = `g${group}s${candSlot}`;
          const candEntry = decoded.groups[candKey];
          if (!candEntry) {
            streamRef.candidates.push({ slot: candSlot, status: "slot_not_found" });
            continue;
          }
          const fc = candEntry.events.filter((e) => e.op === "fireChild");
          anyFc += fc.length;
          streamRef.candidates.push({
            slot: candSlot,
            streamAddress: candEntry.streamAddress,
            end: candEntry.end,
            eventCount: candEntry.events.length,
            decodeFailure: candEntry.decodeFailure ?? null,
            fireChildEvents: fc.map((e) => ({ frame: e.frame, frameKind: e.frameKind, variant: e.variant, addr: e.addr })),
            fireChildCount: fc.length,
          });
        }
        streamRef.fireChildCount = anyFc;
        streamRef.status = anyFc ? "fireChild_present" : "no_fireChild_in_stream";
        if (anyFc === 0) streamRef.reason = "all candidate slots decoded cleanly; none contains op 0x09 fireChild";
      } else {
        streamRef.status = "unresolved_static";
        streamRef.reason = "slot is a runtime cursor and no slotCandidates enumerated (seedSource=" + (v.seedSource ?? "null") + ")";
      }
      entry.streams[vis.join(",")] = streamRef;
      continue;
    }
    const slotKey = `g${group}s${slot}`;
    const slotEntry = decoded.groups[slotKey];
    if (!slotEntry) {
      // group present but slot out of range, or group absent
      streamRef.status = "slot_not_found";
      streamRef.reason = `bank ${v.bank} has groups ${Object.keys(decoded.groups).filter((k) => k.startsWith(`g${group}s`)).length ? `g${group}` : `g${group} (absent)`}; slot ${slot} missing`;
      failures.push({ borgId: cb.id, variants: vis, bank: v.bank, group, slot, reason: "slot_not_found" });
      entry.streams[vis.join(",")] = streamRef;
      continue;
    }
    const fireChildEvents = slotEntry.events.filter((e) => e.op === "fireChild");
    streamRef.streamAddress = slotEntry.streamAddress;
    streamRef.end = slotEntry.end;
    streamRef.eventCount = slotEntry.events.length;
    streamRef.otherRecognizedOps = slotEntry.otherRecognizedOps ?? [];
    streamRef.decodeFailure = slotEntry.decodeFailure ?? null;
    streamRef.fireChildEvents = fireChildEvents.map((e) => ({
      frame: e.frame,
      frameKind: e.frameKind,
      variant: e.variant,
      addr: e.addr,
    }));
    streamRef.fireChildCount = fireChildEvents.length;
    streamRef.status = fireChildEvents.length ? "fireChild_present" : "no_fireChild_in_stream";
    if (fireChildEvents.length === 0) {
      streamRef.reason =
        "stream decoded cleanly but contains no op 0x09 fireChild — beam (if any) spawns via the engine's cfg+0x14 release callback or cfg+0x10 setup callback, NOT the stream";
    }
    // Also scan additionalStreams (secondary per-part streams, e.g. mask 0x2 weapon anim)
    // for fireChild — recorded separately so the primary charge stream result is unambiguous.
    const extraSpawns = [];
    for (const add of v.additionalStreams || []) {
      if (!add.bank || add.slot === null || add.slot === undefined) continue;
      const addBank = parseInt(add.bank, 16);
      const useShared = (add.group & 0x80) !== 0;
      // additionalStreams group is already the resolved group number (no 0x80 flag in the
      // captured table); bank field tells which bank. Pick the decoded bank accordingly.
      let addDecoded;
      try { addDecoded = decodeBankRef(addBank); } catch { continue; }
      const addKey = `g${add.group}s${add.slot}`;
      const addEntry = addDecoded.groups[addKey];
      if (!addEntry) continue;
      const fc = addEntry.events.filter((e) => e.op === "fireChild");
      if (fc.length) {
        for (const e of fc) extraSpawns.push({
          additionalStream: { bank: add.bank, group: add.group, slot: add.slot, mask: add.mask },
          streamAddress: addEntry.streamAddress,
          frame: e.frame, frameKind: e.frameKind, variant: e.variant, addr: e.addr,
        });
      }
    }
    streamRef.additionalStreamFireChild = extraSpawns;
    entry.streams[vis.join(",")] = streamRef;
  }
  borgs[cb.id] = entry;
}

// ---------- summary ----------
let presentCount = 0;
let absentCount = 0;
let unresolvedCount = 0;
let totalFireChild = 0;
let totalAddlFireChild = 0;
const cleanDecodes = [];
const decodeFailures = [];
for (const e of Object.values(borgs)) {
  for (const s of Object.values(e.streams)) {
    if (s.status === "fireChild_present") { presentCount++; totalFireChild += s.fireChildCount; if (s.end) cleanDecodes.push(s.end); }
    else if (s.status === "no_fireChild_in_stream") { absentCount++; if (s.end) cleanDecodes.push(s.end); if (Array.isArray(s.candidates)) for (const c of s.candidates) if (c.end) cleanDecodes.push(c.end); }
    else unresolvedCount++;
    if (s.decodeFailure) decodeFailures.push({ borgId: e.borgId, stream: s.streamAddress, ...s.decodeFailure });
    if (s.candidates) for (const c of s.candidates) if (c.decodeFailure) decodeFailures.push({ borgId: e.borgId, stream: c.streamAddress, ...c.decodeFailure });
    if (s.additionalStreamFireChild) totalAddlFireChild += s.additionalStreamFireChild.length;
  }
}
const decodeEnds = [...new Set(cleanDecodes)];

const out = {
  _meta: {
    generatedBy: "scripts/gen-charge-firechild-frames.mjs",
    source: "user-data/GG4E/disc/sys/boot.dol (raw action-script stream banks)",
    inputTables: "packages/combat/src/data/actionStreamTables.json",
    method:
      "Walk raw bank bytes at each B-charge borg's (bank, group, slot) using the op-length table DERIVED from each DOL handler's `*streamPtr += N` (8B for {0x01,0x02,0x03,0x0d}, 4B otherwise; stream-vm.ts:22-41 / gen-melee-anim-kinds.mjs:184). Wait-frame context tracked as in gen-melee-anim-kinds.mjs:191-230 (bit0 terminator, bit1 relEnd, bit2 pct, bit3 timer, mode 0 & val>=0 abs, mode 0 & val<0 animEnd). fireChild.frame = live wait-context frame at op 0x09.",
    opcodeFireChild: "op 0x09 fireChild (4B): byte3 sign-extended = child variant; handler FUN_8004c67c -> zz_0099e70_ (stream-vm.ts:319-322, gen-melee-anim-kinds.mjs:30,274-275)",
    important:
      "Most charge streams (incl. G RED pl0615 g4s2 @0x80367144) contain NO op 0x09 fireChild. The beam spawns via the shared-charge engine's cfg+0x14 release callback (FUN_801799bc chunk_0044.c:3985-3987; G RED's cb FUN_8018edc4 chunk_0047.c:1003-1013 -> zz_00e19a8_(actor, 0xf, &+0x6f7)), NOT via stream op. Entries with status 'no_fireChild_in_stream' decode cleanly — they are not failures; the spawn simply is not stream-driven.",
    provenance: {
      bankLayout: "zz_004beb8_ chunk_0006.c:1431-1492 (s16 group-offset array -> s16 slot-offset array -> byte stream)",
      streamWalker: "zz_004cd24_ chunk_0006.c:1996 (per-tick interpreter; op 0x09 dispatch FUN_8004c67c)",
      opSizeTable: "PTR_FUN_802d0da0 @0x802d0da0 (18 handlers 0x00-0x11); record sizes verified per-handler in DOL",
      action3Resolution: "actionStreamTables.json _meta.evidence (concrete PPC emulation per (borg, actionIndex 3, variantIndex))",
      gredChargeStream: "pl0615 family bank 0x80366220 group 4 slot 2 -> stream @0x80367144 (20 events, end=terminated, 0 fireChild)",
      gredActualBeamSpawn: "cfg+0x14 cb 0x8018edc4 (chunk_0047.c:1003) fired by FUN_801799bc at phase 1->2 transition (chunk_0044.c:3985-3987)",
    },
    summary: {
      chargeBorgs: chargeBorgs.length,
      streamsWithFireChild: presentCount,
      streamsWithoutFireChild: absentCount,
      streamsWithUnresolvedStaticSlot: unresolvedCount,
      totalFireChildEventsInChargeStreams: totalFireChild,
      totalFireChildEventsInAdditionalStreams: totalAddlFireChild,
      observedDecodeEndStates: decodeEnds,
      decodeFailures,
      cleanDecode: decodeFailures.length === 0 && decodeEnds.every((e) => e === "terminated" || e === "fallsThrough"),
      opLengthTable: "8B for {0x01,0x02,0x03,0x0d}; 4B for all others (0x00,0x04-0x0b,0x0c,0x0e-0x11) — every handler's record size verified against DOL `*streamPtr += N`; stream-vm.ts:22-41 OP_SIZE",
    },
  },
  borgs,
};

fs.writeFileSync(OUT_PATH, JSON.stringify(out, null, 1) + "\n");
console.error(`wrote ${OUT_PATH}`);
console.error(
  `charge borgs=${chargeBorgs.length} streams_with_fireChild=${presentCount} without=${absentCount} unresolved=${unresolvedCount} total_fireChild_events=${totalFireChild}`,
);
if (failures.length) {
  console.error("failures:");
  for (const f of failures) console.error("  " + JSON.stringify(f));
}
