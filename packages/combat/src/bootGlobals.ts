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
