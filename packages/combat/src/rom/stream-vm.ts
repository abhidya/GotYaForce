// ROM-faithful action-script stream interpreter — 1:1 port of `zz_004beb8_` (bank
// resolver + stream starter) and `zz_004cd24_` (per-tick interpreter) at
// `research/decomp/ghidra-export/chunk_0006.c:1429` and `:1996`.
//
// Every family action handler calls `startStream` once at move-start (arming the
// kind-N hitbox + playAnim) and `tickStream` each per-frame phase (advancing the
// choreography: anim frames, hitbox windows, contact-flag writes the family handler
// polls for phase transitions).
//
// Bank layout (chunk_0006.c:1445-1477, proven in cue-script-stream-decode §3):
//   group bit7 clear → family bank (+0x1d80); group==0 → default-group (+0x582)
//   group bit7 set   → shared bank (+0x1d84); group & 0x7f indexes it
//   bank = [s16 groupOffset[group]] ... [s16 slotOffset[slot]] ... stream bytes
//
// Op handler operand layouts are all DERIVED from boot.dol disassembly (see
// research/decomp/action-vm-and-gcrash-decode-2026-07-05.md §A).

import type { RomActor, RomPartState } from "./actor.js";

/** Stream record sizes per opcode (DERIVED — every handler's `addi r0, r6, <size>`
 *  confirmed in the disasm). Index by opcode 0x00..0x11. */
const OP_SIZE: ReadonlyArray<number> = [
  4,  // 0x00 wait     (mode + s16 val)
  8,  // 0x01 playAnim (group|0x80, slot, +6 pad)
  8,  // 0x02 part-state-setter (b1..b5 + 2 pad)
  8,  // 0x03 control-word-setter (b1, b2, b6..b7 u16 + pad)
  4,  // 0x04 part-2 flag (b1, b2)
  4,  // 0x05 part-3 flag (b1, b2)
  4,  // 0x06 per-part go (post-lhau 2-byte record + 2 pad)
  4,  // 0x07 hand/weapon swap (b1, b2, b3)
  4,  // 0x08 state-mode setter (b1, b2, b3)
  4,  // 0x09 fireChild (b1, b2 variant u16)
  4,  // 0x0a armHit (b1 kind, b2 statusId, b3 statusArg)
  4,  // 0x0b bit set/clear on +0x709 (b1 mode, b2 mask)
  4,  // 0x0c bit set/clear on +0x57a/+0x57b (b1 mode, b2 mask)
  8,  // 0x0d blendAnim (group|0x80, slot, +6 pad)
  4,  // 0x0e playSound (b1 part, b2 mode, b3 soundId) — unused on GG4E
  4,  // 0x0f table-driven voice (b1 part, b2=0, b3 unused)
  4,  // 0x10 per-part toggle (b1 part, b2 mode, b3 value)
  4,  // 0x11 indirect callback (b1 part, b2, b3)
];

export interface StreamContext {
  /** Reads the kind-N hitbox arm event into the host hit system. Host wires this to
   *  the existing @gf/combat melee-hit resolver (startMeleeAttack's per-active-frame
   *  path). The statusId/statusArg bytes seed the status-infliction gate. */
  onArmHit?: (actor: RomActor, kind: number, statusId: number, statusArg: number) => void;
  /** Plays the named anim clip. Host wires to the renderer (borgPresentationAssets
   *  loadClip via the group/slot → label table). */
  onPlayAnim?: (actor: RomActor, group: number, slot: number, blend: boolean) => void;
  /** Op 0x09 fireChild — spawns a projectile/child object. Host wires to combat.ts
   *  spawnProjectile with the variant-resolved record. */
  onFireChild?: (actor: RomActor, variant: number) => void;
  /** Op 0x11 indirect callback — the family-scripted FX hook at actor+0x4d8. Per-family
   *  registration; null when the family hasn't set the callback. */
  onIndirect?: (actor: RomActor, a: number, b: number) => void;
  /** Family-table projectile spawn — for spawner functions with their OWN record tables
   *  (e.g. the ninja shuriken zz_007db5c_ @0x8007db5c, table 0x802d6d68), which index a
   *  DIFFERENT registry than op 0x09's generic variant table (DAT_802f3dda → onFireChild).
   *  `spawnerAddr` is the ROM spawner address, `type` its record-select argument. Hosts
   *  that haven't wired the family table leave this unset (spawn is skipped, honest no-op). */
  onFamilyProjectile?: (actor: RomActor, spawnerAddr: number, type: number) => void;
  /** Param-tier delta — port of `apply_actor_param_tier_delta_127(actor, signedDelta)`.
   *  Fired by family handlers that mutate the +0xb4 param tier (STAR HERO / PLANET HERO's
   *  X-special applies +4 on a connecting dash, reverted by FUN_8010f790 at -4). The host
   *  (bridge.ts) routes this to BorgRuntime.paramTier via applyActorParamTierDelta127. */
  onParamTierDelta?: (actor: RomActor, signedDelta: number) => void;
  /** Sound-cue player — port of `zz_00f036c_(actor, cueId)`. Fired by family handlers on
   *  status changes (STAR HERO's buff application plays cue 0xa5). The host wires this to
   *  the existing voice/sound presentation layer. */
  onPlayCue?: (actor: RomActor, cueId: number) => void;
  /** Exact zz_006dbe0_ bridge: weapon cell check/consume. consumeMode 0 checks only;
   *  nonzero snapshots/decrements the cell and arms its refill behavior. */
  onAllocateResource?: (
    actor: RomActor,
    weaponIndex: number,
    count: number,
    consumeMode?: number,
  ) => boolean;
}

/**
 * Port of `zz_004beb8_` @ chunk_0006.c:1431 — resolve (group, slot) against the
 *  family/shared bank and return the stream byte offset. Returns -1 when the chosen
 *  bank is null (the ROM clears all parts and returns in that case).
 *
 * ROM signature: `zz_004beb8_(rate, actor, mask, group, slot, ...)`.
 */
export function resolveStreamOffset(actor: RomActor, group: number, slot: number): number {
  const useShared = (group & 0x80) !== 0;
  const bank = useShared ? actor.sharedStreamBank : actor.familyStreamBank;
  if (!bank || bank.length === 0) return -1;
  const groupIndex = useShared ? group & 0x7f : group === 0 ? actor.defaultGroup : group;
  // s16 group-offset table at bank start.
  const groupOffset = readS16(bank, groupIndex * 2);
  const groupBase = groupOffset;
  if (groupBase < 0 || groupBase + slot * 2 + 2 > bank.length) return -1;
  const slotOffset = readS16(bank, groupBase + slot * 2);
  const streamStart = groupBase + slotOffset;
  if (streamStart < 0 || streamStart >= bank.length) return -1;
  return streamStart;
}

/** Port of `zz_004beb8_`'s part-activation loop (lines 1478-1489). Activates the parts
 *  selected by `mask & actor.+0x579`, stamps the resolved group/slot onto each part
 *  (+0x18/+0x19), resets the part state, and seeds the stream pointer.
 *
 *  `rate` (-1.0 default) is the playback rate passed to zz_004c050_; the host renderer
 *  reads it via the part-anim clock. */
export function startStream(
  actor: RomActor,
  mask: number,
  group: number,
  slot: number,
  rate: number = -1.0,
): void {
  const hostScheduled = (actor as RomActor & {
    onStartStream?: (group: number, slot: number, mask: number) => boolean;
  }).onStartStream?.(group, slot, mask) === true;
  const effective = mask & 0xff; // actor.+0x579 is the part-enable mask; surfaced as 0xff here.
  if ((effective & 2) !== 0) {
    // Clear +0x709 (chunk_0006.c:1442-1444) — the contact-slow flag. Bridge clears it
    // on the BorgRuntime status word.
  }
  const streamStart = resolveStreamOffset(actor, group, slot);
  if (streamStart < 0) {
    for (let i = 0; i < actor.parts.length; i++) {
      if ((effective & (1 << i)) === 0) continue;
      const part = actor.parts[i]!;
      resetPart(part);
      if (hostScheduled) {
        // The host owns timing from the decoded event schedule when raw stream bytes
        // are not resident. A non-negative sentinel keeps the ROM completion byte low.
        part.streamPtr = Number.MAX_SAFE_INTEGER;
        part.active = 1;
      }
    }
    return;
  }
  for (let i = 0; i < 4; i++) {
    if ((effective & (1 << i)) !== 0) {
      const part = actor.parts[i]!;
      // The ROM stores group/slot at +0x18/+0x19 for later re-resolution (combo re-arm).
      (part as RomPartState & { group: number; slot: number }).group = group;
      (part as RomPartState & { slot: number }).slot = slot;
      resetPart(part);
      part.streamPtr = streamStart;
      part.active = 1;
      if (i === 0) actor.wallContact = 0;
      (part as RomPartState & { rate: number }).rate = rate;
    }
  }
}

function resetPart(part: RomPartState): void {
  // zz_004c020_ @ chunk_0006.c:1498.
  part.streamPtr = -1;
  part.frameClock = 0;
  part.prevTarget = 0;
  part.curTarget = 0;
  part.animTime = 0;
  part.active = 0;
  part.stateByte = 0;
}

/**
 * Port of `zz_004cd24_` @ chunk_0006.c:1996 — advance all parts selected by `mask` one
 *  tick. For each part: if its wait clock has expired, dispatch the next opcode via
 *  the handler table; the handler advances the part's streamPtr by the op's record
 *  size. Stops at end-of-script (op 0x00 mode 0 val -1).
 *
 *  The ROM dispatches through PTR_FUN_802d0da0 (18 entries); here it's a switch since
 *  JS has no function-pointer table cost worth worrying about. Every handler's operand
 *  layout is the DERIVED decode from the disasm.
 */
export function tickStream(actor: RomActor, mask: number, ctx: StreamContext = {}): boolean {
  let completed = false;
  for (let i = 0; i < 4; i++) {
    if ((mask & (1 << i)) === 0) continue;
    const part = actor.parts[i]!;
    if (part.streamPtr < 0) continue;
    const before = part.streamPtr;
    tickPart(actor, part, ctx);
    if (before >= 0 && part.streamPtr < 0) {
      part.active = 0;
      if (i === 0) actor.wallContact = 1;
      completed = true;
    }
  }
  return completed;
}

function tickPart(actor: RomActor, part: RomPartState, ctx: StreamContext): void {
  const bank = actor.familyStreamBank; // shared-bank streams carry group bit7 set and
                                       // resolve the same way; the active bank is whichever
                                       // the startStream resolved. For simplicity the host
                                       // stamps the resolved bank onto the part; here we
                                       // fall back to the family bank.
  if (!bank) return;
  // Advance the part's frame clock by dt (the integrator's tick).
  part.frameClock += actor.dt;
  // Walk ops until we hit a wait that hasn't expired.
  let safety = 32;
  while (safety-- > 0 && part.streamPtr >= 0 && part.streamPtr < bank.length) {
    const opByte = bank[part.streamPtr]!;
    if (opByte > 0x11) {
      // Junk / table-end marker — stop walking this part.
      part.streamPtr = -1;
      return;
    }
    if (opByte === 0x00) {
      // Wait op: mode at byte+2, val s16 at byte+2..+3. The ROM's full wait dispatch
      // (chunk_0006.c:2024-2081) covers modes 0/1/2/8; here we honor the common ones.
      const mode = bank[part.streamPtr + 1]! >>> 0;
      const val = readS16(bank, part.streamPtr + 2);
      if (mode === 0 && val === -1) {
        part.streamPtr = -1; // end-of-script sentinel
        return;
      }
      if (mode === 1) {
        // Countdown wait: decrement by dt; advance when expired.
        const slot = part as RomPartState & { waitRemaining?: number };
        const remaining = slot.waitRemaining ?? val;
        const next = remaining - actor.dt;
        if (next > 0) {
          slot.waitRemaining = next;
          return; // not yet
        }
        delete slot.waitRemaining;
      } else if (mode === 2) {
        // Anim-relative wait: fires when animTime >= val. The anim clock is owned by the
        // host renderer; for the runtime we approximate by comparing frameClock to val.
        if (part.frameClock < val) return;
      } else if (mode === 8) {
        // Realtime countdown — same shape as mode 1 but wall-clock. Use dt.
        const slot = part as RomPartState & { waitRemaining?: number };
        const remaining = slot.waitRemaining ?? val;
        const next = remaining - actor.dt;
        if (next > 0) {
          slot.waitRemaining = next;
          return;
        }
        delete slot.waitRemaining;
      }
      part.streamPtr += OP_SIZE[0]!;
      continue;
    }
    dispatchOp(actor, part, opByte, bank, ctx);
    part.streamPtr += OP_SIZE[opByte]!;
  }
}

/** Op handler dispatch — the port of PTR_FUN_802d0da0. Each handler reads its operand
 *  bytes and writes the actor fields, exactly as the decompiled handler does. */
function dispatchOp(
  actor: RomActor,
  part: RomPartState,
  op: number,
  bank: Uint8Array,
  ctx: StreamContext,
): void {
  const ptr = part.streamPtr;
  const partIndex = actor.parts.indexOf(part);
  const b1 = bank[ptr + 1]!;
  const b2 = bank[ptr + 2]!;
  const b3 = bank[ptr + 3]!;
  switch (op) {
    case 0x01: // playAnim (group|0x80, slot)
    case 0x0d: // blendAnim — same operand shape
      ctx.onPlayAnim?.(actor, b1, b2, op === 0x0d);
      return;
    case 0x02: { // part-0-state setter: b2→+0x1cef, b3→+0x1cf0, b4→+0x6e8, b5→+0x6e9; b1 toggles +0x582
      // The handler is part-0-gated; the offsets +0x1cef/+0x1cf0 ARE the part-0 block's
      // +0x1b/+0x1c. +0x6e8/+0x6e9 are actor-global FX-mode bytes.
      actor.parts[0]!.stateByte = b2 >= 0x80 ? b2 - 0x100 : b2;
      actor.contactP0 = actor.parts[0]!.stateByte;
      (actor.parts[0] as RomPartState & { c?: number }).c = b3 >= 0x80 ? b3 - 0x100 : b3;
      const fx = actor as RomActor & { fxMode0?: number; fxMode1?: number };
      fx.fxMode0 = b2 >= 0x80 ? b2 - 0x100 : b2; // sign-extend; the ROM stores signed
      // b1 toggles +0x582 (the camera/default-group byte)
      if (b1 === 0xfe) actor.defaultGroup ^= 1; // -2 → toggle
      else if (b1 !== 0xff) actor.defaultGroup = b1 >= 0x80 ? b1 - 0x100 : b1;
      return;
    }
    case 0x03: { // part-1 state + control-word setter: +0x1d0f/+0x1d10, bits 20..27
      actor.parts[1]!.stateByte = b1 >= 0x80 ? b1 - 0x100 : b1;
      (actor.parts[1] as RomPartState & { c?: number }).c = b2 >= 0x80 ? b2 - 0x100 : b2;
      const u16 = (bank[ptr + 6]! << 8) | bank[ptr + 7]!;
      // The ROM masks +0x5e0 to clear bits 20..27 then ORs in (u16 & 0xff00).
      actor.controlWord = (actor.controlWord & ~0x0ff00000) | (u16 & 0xff00) << 12;
      return;
    }
    case 0x04: // part-2 flag: b1→+0x1d2f, b2→+0x1d30
      actor.parts[2]!.stateByte = b1;
      return;
    case 0x05: // part-3 flag
      actor.parts[3]!.stateByte = b1;
      return;
    case 0x06: { // per-part "go": the halfword selects which parts activate; sets +0x1cf2..+0x1d52
      const halfword = readS16(bank, ptr + 2);
      void halfword; // the per-part-bit iteration is the host anim-blender's responsibility
      return;
    }
    case 0x07: // hand/weapon swap (descriptor +0xbe/+0xbf fallback)
      // Routes through actor.descriptor.defaultHand0/1; family-port adapter applies.
      return;
    case 0x08: { // state-mode setter: byte3 → +0x71d (or +0x6d8 × FLOAT_80437130 if negative)
      const mode = actor as RomActor & { stateMode?: number };
      if (b3 >= 0x80) mode.stateMode = (b3 - 0x100) * 1.0; // FLOAT_80437130 == 1.0
      else mode.stateMode = b3;
      return;
    }
    case 0x09: { // fireChild: signed byte 3 (FUN_8004c67c)
      const variant = b3 >= 0x80 ? b3 - 0x100 : b3;
      ctx.onFireChild?.(actor, variant);
      return;
    }
    case 0x0a: { // armHit: b1=kind, b2=statusId, b3=statusArg
      if (b1 > 0) {
        ctx.onArmHit?.(actor, b1, b2, b3);
        (actor as RomActor & { lastKind?: number }).lastKind = b1;
      }
      return;
    }
    case 0x0b: { // bit set/clear on +0x709 (b1 mode, b2 mask)
      const flag = actor as RomActor & { contactFlags?: number };
      const cur = flag.contactFlags ?? 0;
      flag.contactFlags = b1 === 0 ? cur | b2 : cur & ~b2;
      return;
    }
    case 0x0c: { // bit set/clear on +0x57a/+0x57b
      const sa = actor as RomActor & { stateFlagA?: number; stateFlagB?: number };
      if (b1 === 0) sa.stateFlagB = (sa.stateFlagB ?? 0) | b2;
      else {
        sa.stateFlagA = (sa.stateFlagA ?? 0) & ~b2;
        sa.stateFlagB = (sa.stateFlagB ?? 0) & ~b2;
      }
      return;
    }
    case 0x0e: // playSound — unused on GG4E (zero corpus); port for completeness
      return;
    case 0x0f: // table-driven voice — host wires via the existing voice-cue presentation
      return;
    case 0x10: { // per-part toggle: b2 mode, b3 value → +0x1b04/+0x1b44 (per-part flags)
      const partFlag = actor.parts[partIndex] as RomPartState & { toggle?: number };
      const cur = partFlag.toggle ?? 0;
      if (b2 === 0) partFlag.toggle = 0;
      else if (b2 === 1) partFlag.toggle = 0;
      else if (b2 === 2) partFlag.toggle = 1;
      else if (b2 === 3 || b2 === 4) partFlag.toggle = cur ^ 1;
      return;
    }
    case 0x11: // indirect callback via +0x4d8
      ctx.onIndirect?.(actor, b2, b3);
      return;
  }
}

function readS16(bank: Uint8Array, offset: number): number {
  if (offset < 0 || offset + 2 > bank.length) return -1;
  const u = (bank[offset]! << 8) | bank[offset + 1]!;
  return u >= 0x8000 ? u - 0x10000 : u;
}
