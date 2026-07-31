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
 * Set the boot configuration byte (DAT_80436498).
 * Called once at application bootstrap; the battle system reads it via getBootConfigByte().
 */
export function setBootConfigByte(value: number): void {
  _bootConfigByte = value & 0xff;
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
export function getBootConfigByte(): number {
  return _bootConfigByte;
}

/**
 * Check whether MetroTRK debugger initialization should be triggered.
 * Mirrors the caller's gate: `if (zz_000314c_() == 1) InitMetroTRK_BBA();`
 */
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
function zz_0003424_(dest: Uint8Array | null, size: number): void {
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
 * gnt4_memset @0x8000540c — Portable memset implementation.
 *
 * Original decomp:
 *   void *gnt4_memset(void *__s, int __c, size_t __n) {
 *     gnt4___fill_mem_bl();
 *     return __s;
 *   }
 *
 * In the browser port, we use the native fill method.
 */
function gnt4_memset(dest: Uint8Array, value: number, n: number): void {
  if (n <= 0) return;
  dest.fill(value, 0, n);
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
    if (dest !== src && dest !== null && src !== null) {
      gnt4_memcpy(dest, src, size);
      zz_0003424_(dest, size);
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

