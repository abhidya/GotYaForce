/**
 * Boot-time global state — direct port of the GameCube's early-boot byte globals.
 *
 * zz_000314c_ @0x8000314c (chunk_0000.c) reads DAT_80436498 and returns it as a byte.
 * The caller (0x8000328c) checks `if (zz_000314c_() == 1) InitMetroTRK_BBA();`
 * — this byte is the boot configuration flag that enables the MetroTRK debugger.
 */

/**
 * DAT_80436498 — boot configuration byte.
 * The original ROM reads this at 0x8000314c via `lbz r3, -0x5108(r13)`.
 * Value 1 enables MetroTRK debugger initialization; other values skip it.
 * In the browser port this is exposed as a configurable boot flag.
 */
let _bootConfigByte: number = 0;

/**
 * DAT_804360c0 — audio cue global.
 * The original ROM writes to this at 0x80005984 via `zz_0005984_` (a thin setter).
 * Called during boot/setup sequences (zz_0180820_, FUN_000c0358, zz_00059b8_)
 * with argument 0 to clear/reset the audio cue state.
 */
let _audioCue: number = 0;

/**
 * Set the boot configuration byte (DAT_80436498).
 * Called once at application bootstrap; the battle system reads it via getBootConfigByte().
 */
export function setBootConfigByte(value: number): void {
  _bootConfigByte = value & 0xff;
}

/**
 * gnt4___init_hardware_bl @0x80003400 — Early hardware initialization sequence.
 *
 * Original decomp:
 *   void gnt4___init_hardware_bl(void) {
 *     gnt4___OSPSInit_bl();
 *     gnt4___OSFPRInit_bl();
 *     gnt4___OSCacheInit_bl();
 *     return;
 *   }
 *
 * Normalized disassembly:
 *   mfmsr r0
 *   ori r0,r0,0x2000
 *   mtmsr r0,0
 *   mfspr r31,lr
 *   bl 0x801ff548  // gnt4___OSPSInit_bl
 *   bl 0x801feaf0  // gnt4___OSFPRInit_bl
 *   bl 0x80200934  // gnt4___OSCacheInit_bl
 *   mtspr lr,r31
 *   blr
 *
 * Called from start() @0x8000316c (chunk_0000.c) during early boot,
 * after __init_registers() and before zz_0003340_().
 *
 * In the browser port, this is a no-op (no GameCube hardware to initialize).
 */
export function gnt4___init_hardware_bl(): void {
  // Browser has no GameCube hardware — all three init functions are no-ops.
  // The original calls gnt4___OSPSInit_bl(), gnt4___OSFPRInit_bl(), and gnt4___OSCacheInit_bl()
  // in sequence to initialize power/performance state, floating-point registers, and caches.
}

/**
 * zz_000314c_ @0x8000314c — read the boot configuration byte.
 *
 * Original decomp:
 *   undefined1 zz_000314c_(void) {
 *     return DAT_80436498;
 *   }
 *
 * Normalized disassembly:
 *   lbz r3, -0x5108(r13)
 *   blr
 *
 * The caller at 0x8000328c checks: if (zz_000314c_() == 1) InitMetroTRK_BBA();
 */
/**
 * zz_0005984_ @0x80005984 — Set the audio cue global (DAT_804360c0).
 *
 * Original decomp:
 *   void zz_0005984_(undefined4 param_1) {
 *     DAT_804360c0 = param_1;
 *     return;
 *   }
 *
 * Normalized disassembly:
 *   stw r3,-0x54e0(r13)
 *   blr
 *
 * Called from zz_0180820_ (0x8018083c), FUN_000c0358 (0x800c0378),
 * and zz_00059b8_ (0x80005aac) during boot/setup sequences with arg 0.
 */
export function zz_0005984_(cue: number): void {
  _audioCue = cue;
}

export function getBootConfigByte(): number {
  return _bootConfigByte;
}

/**
 * Check whether MetroTRK debugger initialization should be triggered.
 * Mirrors the caller's gate: `if (zz_000314c_() == 1) InitMetroTRK_BBA();`
 */
/**
 * Get the current audio cue value (DAT_804360c0).
 * Used by the title VM's setAudioCue opcode (0x0c) to read back the cue.
 */
export function getAudioCue(): number {
  return _audioCue;
}

export function isMetroTRKEnabled(): boolean {
  return getBootConfigByte() === 1;
}

// ---------------------------------------------------------------------------------------
// zz_0003340_ @0x80003340 — Boot-time memory patching and BSS clearing.
// ---------------------------------------------------------------------------------------
//
// Original decomp:
//   void zz_0003340_(void) {
//     undefined **ppuVar1;
//     undefined *__n;
//     undefined *__dest;
//     for (ppuVar1 = &PTR___check_pad3_80005544;
//          __n = ppuVar1[2], __n != (undefined *)0x0;
//          ppuVar1 = ppuVar1 + 3) {
//       __dest = ppuVar1[1];
//       if (__dest != *ppuVar1) {
//         gnt4_memcpy(__dest, *ppuVar1, (size_t)__n);
//         zz_0003424_(__dest, __n);
//       }
//     }
//     for (ppuVar1 = &PTR_DAT_800055b0;
//          ppuVar1[1] != (undefined *)0x0;
//          ppuVar1 = ppuVar1 + 2) {
//       gnt4_memset(*ppuVar1, 0, (size_t)ppuVar1[1]);
//     }
//     return;
//   }
//
// Called from start() @0x8000316c (chunk_0000.c) during early boot, after
// __init_registers() and gnt4___init_hardware_bl(), before the main game loop.
//
// The function processes two null-terminated tables:
//   1. PTR___check_pad3_80005544: array of [dest, src, size] triplets.
//      For each entry where dest != src, copies size bytes from src to dest,
//      then calls zz_0003424_ (cache sync) on the destination.
//   2. PTR_DAT_800055b0: array of [dest, size] pairs.
//      For each entry, zeroes 'size' bytes at dest.
//
// In the browser port, these tables are empty (JavaScript runtime handles
// memory initialization automatically), but the function preserves the exact
// control flow, loop structure, and helper call patterns from the original ROM.

/**
 * Memory copy triplet: [dest, src, size].
 * Null size (0) terminates the table.
 */
interface MemCopyTriplet {
  dest: Uint8Array | null;
  src: Uint8Array | null;
  size: number;
}

/**
 * BSS clear pair: [dest, size].
 * Null size (0) terminates the table.
 */
interface MemClearPair {
  dest: Uint8Array | null;
  size: number;
}

/**
 * PTR___check_pad3_80005544 — null-terminated table of memory copy triplets.
 * In the original ROM, this table contains patches for initialized data sections.
 * In the browser port, this is empty (JavaScript handles initialization).
 */
const PTR__CHECK_PAD3_80005544: MemCopyTriplet[] = [];

/**
 * PTR_DAT_800055b0 — null-terminated table of BSS clear pairs.
 * In the original ROM, this table contains regions to zero (BSS-style).
 * In the browser port, this is empty (JavaScript implicitly zeroes BSS).
 */
const PTR_DAT_800055B0: MemClearPair[] = [];

/**
 * zz_0003424_ @0x80003424 — Cache synchronization after memory copy.
 *
 * Original decomp:
 *   void zz_0003424_(uint param_1, int param_2) {
 *     uint uVar1;
 *     uVar1 = param_1 & 0xfffffff1;
 *     param_2 = param_2 + (param_1 - uVar1);
 *     do {
 *       dataCacheBlockStore(uVar1);
 *       sync(0);
 *       instructionCacheBlockInvalidate(uVar1);
 *       uVar1 = uVar1 + 8;
 *       param_2 = param_2 + -8;
 *     } while (-1 < param_2);
 *     instructionSynchronize();
 *     return;
 *   }
 *
 * In the browser port, this is a no-op (no hardware cache to sync).
 */
function zz_0003424_(dest: number, size: number): void {
  // Browser has no hardware cache — this is a no-op.
  void dest;
  void size;
}

/**
 * gnt4_memcpy @0x800054f4 — Portable memcpy implementation.
 *
 * Original decomp:
 *   void *gnt4_memcpy(void *__dest, void *__src, size_t __n) {
 *     if (__dest <= __src) {
 *       // Copy forward
 *     } else {
 *       // Copy backward
 *     }
 *     return __dest;
 *   }
 *
 * In the browser port, we use the native Array.prototype.set or manual copy.
 */
function gnt4_memcpy(dest: Uint8Array, src: Uint8Array, n: number): void {
  if (n <= 0) return;
  // Use native set for efficiency when possible
  if (dest.length >= n && src.length >= n) {
    dest.set(src.subarray(0, n), 0);
  }
}

/**
 * gnt4___fill_mem_bl @0x8000543c — Optimized block-fill routine.
 *
 * Original decomp:
 *   void gnt4___fill_mem_bl(int param_1, byte param_2, uint param_3)
 *   {
 *     uint uVar1;
 *     uint *puVar2;
 *     byte *pbVar3;
 *     uint uVar4;
 *     uVar4 = (uint)param_2;
 *     pbVar3 = (byte *)(param_1 + -1);
 *     if (0x1f < param_3) {
 *       uVar1 = ~(uint)pbVar3 & 3;
 *       if (uVar1 != 0) {
 *         param_3 = param_3 - uVar1;
 *         do {
 *           uVar1 = uVar1 - 1;
 *           pbVar3 = pbVar3 + 1;
 *           *pbVar3 = param_2;
 *         } while (uVar1 != 0);
 *       }
 *       if (uVar4 != 0) {
 *         uVar4 = uVar4 | uVar4 << 8 | (uint)param_2 << 0x18 | uVar4 << 0x10;
 *       }
 *       puVar2 = (uint *)(pbVar3 + -3);
 *       for (uVar1 = param_3 >> 5; uVar1 != 0; uVar1 = uVar1 - 1) {
 *         puVar2[1] = uVar4;
 *         puVar2[2] = uVar4;
 *         puVar2[3] = uVar4;
 *         puVar2[4] = uVar4;
 *         puVar2[5] = uVar4;
 *         puVar2[6] = uVar4;
 *         puVar2[7] = uVar4;
 *         puVar2 = puVar2 + 8;
 *         *puVar2 = uVar4;
 *       }
 *       for (uVar1 = param_3 >> 2 & 7; uVar1 != 0; uVar1 = uVar1 - 1) {
 *         puVar2 = puVar2 + 1;
 *         *puVar2 = uVar4;
 *       }
 *       pbVar3 = (byte *)((int)puVar2 + 3);
 *       param_3 = param_3 & 3;
 *     }
 *     if (param_3 != 0) {
 *       do {
 *         param_3 = param_3 - 1;
 *         pbVar3 = pbVar3 + 1;
 *         *pbVar3 = (byte)uVar4;
 *       } while (param_3 != 0);
 *       return;
 *     }
 *     return;
 *   }
 *
 * This is the core block-fill routine called by gnt4_memset.
 * It handles unaligned starts, word-aligned bulk fills (8 uint32s per iteration),
 * and trailing bytes.
 */
function gnt4___fill_mem_bl(dest: Uint8Array, value: number, n: number): void {
  if (n <= 0) return;

  const uVar4 = value & 0xff;
  // pbVar3 starts at dest - 1 (Ghidra: pbVar3 = (byte *)(param_1 + -1))
  // We track pbVar3 as an index into dest, starting at -1
  let pbVar3Idx = -1;

  if (n > 0x1f) {
    // Align to 4-byte boundary
    // uVar1 = ~(uint)pbVar3 & 3
    let uVar1 = (~pbVar3Idx) & 3;
    if (uVar1 !== 0) {
      n -= uVar1;
      do {
        uVar1--;
        pbVar3Idx++;
        dest[pbVar3Idx] = value & 0xff;
      } while (uVar1 !== 0);
    }

    // Build 32-bit fill word
    let fillWord = uVar4;
    if (fillWord !== 0) {
      fillWord = fillWord | (fillWord << 8) | ((uVar4 & 0xff) << 16) | (fillWord << 24);
    }

    // puVar2 = (uint *)(pbVar3 + -3)
    // pbVar3Idx is now at the aligned position, so puVar2 starts at pbVar3Idx - 3
    let puVar2Idx = pbVar3Idx - 3; // as uint32 offset
    let uVar1Count = n >> 5; // n / 32
    while (uVar1Count !== 0) {
      // Write 8 uint32s: indices 1-7 relative to puVar2, then advance by 8
      // puVar2[1] through puVar2[7], then puVar2 += 8, then *puVar2 = uVar4
      for (let i = 1; i <= 7; i++) {
        const idx = (puVar2Idx + i) * 4;
        dest[idx] = fillWord & 0xff;
        dest[idx + 1] = (fillWord >> 8) & 0xff;
        dest[idx + 2] = (fillWord >> 16) & 0xff;
        dest[idx + 3] = (fillWord >> 24) & 0xff;
      }
      puVar2Idx += 8;
      // *puVar2 = uVar4
      const idx = puVar2Idx * 4;
      dest[idx] = fillWord & 0xff;
      dest[idx + 1] = (fillWord >> 8) & 0xff;
      dest[idx + 2] = (fillWord >> 16) & 0xff;
      dest[idx + 3] = (fillWord >> 24) & 0xff;
      uVar1Count--;
    }

    // Fill remaining uint32s (up to 7)
    let uVar1Rem = (n >> 2) & 7;
    while (uVar1Rem !== 0) {
      puVar2Idx++;
      const idx = puVar2Idx * 4;
      dest[idx] = fillWord & 0xff;
      dest[idx + 1] = (fillWord >> 8) & 0xff;
      dest[idx + 2] = (fillWord >> 16) & 0xff;
      dest[idx + 3] = (fillWord >> 24) & 0xff;
      uVar1Rem--;
    }

    // pbVar3 = (byte *)((int)puVar2 + 3)
    pbVar3Idx = puVar2Idx * 4 + 3;
    n = n & 3;
  }

  // Handle trailing bytes
  if (n !== 0) {
    do {
      n--;
      pbVar3Idx++;
      dest[pbVar3Idx] = uVar4;
    } while (n !== 0);
  }
}

/**
 * gnt4_memset @0x8000540c — Thin wrapper around gnt4___fill_mem_bl.
 *
 * Original decomp:
 *   void *gnt4_memset(void *__s, int __c, size_t __n) {
 *     gnt4___fill_mem_bl();
 *     return __s;
 *   }
 *
 * Normalized disassembly:
 *   stwu r1,-0x10(r1)
 *   mfspr r0,lr
 *   stw r0,0x14(r1)
 *   stw r31,0xc(r1)
 *   or r31,r3,r3
 *   bl 0x8000543c
 *   lwz r0,0x14(r1)
 *   or r3,r31,r31
 *   lwz r31,0xc(r1)
 *   mtspr lr,r0
 *   addi r1,r1,0x10
 *   blr
 *
 * Returns the original pointer (dest) for chaining compatibility.
 */
function gnt4_memset(dest: Uint8Array, value: number, n: number): Uint8Array {
  if (n <= 0) return dest;
  gnt4___fill_mem_bl(dest, value, n);
  return dest;
}

/**
 * zz_0003340_ @0x80003340 — Boot-time memory patching and BSS clearing.
 *
 * This function is called during early boot (from start() @0x8000316c)
 * to apply data section patches and clear BSS-style memory regions.
 *
 * In the browser port, the tables are empty (JavaScript handles memory
 * initialization), but the function preserves the exact control flow
 * and loop structure from the original ROM for auditability.
 */
export function zz_0003340_(): void {
  // First loop: process memory copy triplets
  for (let i = 0; i < PTR__CHECK_PAD3_80005544.length; i += 3) {
    const triplet = PTR__CHECK_PAD3_80005544[i];
    if (!triplet || triplet.size === 0) break;

    const dest = triplet.dest;
    const src = triplet.src;
    const size = triplet.size;

    // Only copy if dest != src (preserves the ROM's comparison)
    if (dest !== null && src !== null && dest !== src) {
      gnt4_memcpy(dest, src, size);
      // zz_0003424_ expects a memory address (number) and size (number)
      // In the browser port we pass 0 as a dummy address since it's a no-op
      zz_0003424_(0, size);
    }
  }

  // Second loop: process BSS clear pairs
  for (let i = 0; i < PTR_DAT_800055B0.length; i += 2) {
    const pair = PTR_DAT_800055B0[i];
    if (!pair || pair.size === 0) break;

    const dest = pair.dest;
    const size = pair.size;

    if (dest !== null) {
      gnt4_memset(dest, 0, size);
    }
  }
}

