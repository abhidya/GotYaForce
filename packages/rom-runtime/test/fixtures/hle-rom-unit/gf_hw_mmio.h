/* gf_hw_mmio.h -- GameCube AI/DSP memory-mapped register lowering, ABI v1.
 *
 * !! THIS FILE IS HAND-WRITTEN. It is NOT assembly-gate output, and that is
 * !! the single most important thing to know about this directory.
 *
 * The GX half's equivalent, ../gx-rom-unit/gf_gx_wgpipe.h, IS gate output:
 * OGhidra's src/port_wgpipe_lowering.py generates it and rewrites the ROM's
 * 0xCC008000 stores to match. That lowering handles the write-gather-pipe
 * window AND ONLY THAT WINDOW. Nothing in the gate lowers 0xCC006C00 (the AI
 * block) or 0xCC005000 (the DSP block), so a composed module built by the gate
 * today would compile `AIInitDMA` into the window and TRAP on its first store.
 *
 * Extending the gate to these windows is the top item of the remainder list in
 * docs/audio-dvd-hle-host.md. Until it exists, this header applies the SAME
 * CLASS of rewrite by hand so that the host side of the seam can be built and
 * proved against real ROM code; the host announces the situation at runtime as
 * the AI_MMIO_NOT_GATE_LOWERED diagnostic. Nothing here may be read as if the
 * gate did it.
 *
 * WHY A LOWERING IS NEEDED AT ALL. The AI and DSP libraries are compiled into
 * the ROM window -- they are not gnt4_*-prefixed, so design V2 F2 does not
 * exclude them from porting -- and they reach the hardware by loading and
 * storing memory-mapped registers, which the decompiler renders as
 * `DAT_cc006c00`. The measured audio inventory counts 18 such registers and
 * 745 static accesses. The composed module's linear memory is 0x807A0000
 * bytes, so a literal access at 0xCC006C00 is out of bounds and traps.
 *
 * THE CONTRACT. Unlike the write-gather pipe -- which is a single FIFO address
 * and therefore needs only a value -- a register access is ADDRESSED, so both
 * imports carry the register address. Values are host-order integers, NOT a
 * byte stream: a register is a number, and the wire carries the number. (The
 * pipe is the opposite case and is big-endian for exactly that reason; see
 * gf_gx_wgpipe.h. Getting these two backwards is the mistake this paragraph
 * exists to prevent.)
 *
 *   __gf_mmio_load_u16(addr)         -> the 16-bit register value, zero-extended
 *   __gf_mmio_load_u32(addr)         -> the 32-bit register value
 *   __gf_mmio_store_u16(addr, value) -> void, low 16 bits stored
 *   __gf_mmio_store_u32(addr, value) -> void
 *
 * WIDTH comes from the Ghidra field spelling, the decompiler's record of the
 * access instruction's width -- the same source the pipe lowering uses. The
 * AI block is documented as 32-bit registers and the DSP block as 16-bit, and
 * the ROM's own bodies agree: `AIInitDMA` declares `ushort uVar1` for the DSP
 * registers while `AIInit` declares `uint` for the AI ones.
 *
 * THE STATEMENT, NOT THE TOKEN, IS REWRITTEN. C has no way to make a plain
 * identifier route an assignment through a function, so -- exactly as
 * GF_WGPIPE_W16 does -- the lowering replaces the whole load or store
 * statement. A surviving `DAT_cc0050` / `DAT_cc006c` mention in a lowered
 * source is a lowering failure, and the build refuses it (see build.sh).
 */
#ifndef GF_HW_MMIO_H
#define GF_HW_MMIO_H

#define GF_HW_MMIO_ABI_VERSION 1

extern unsigned int __gf_mmio_load_u16(unsigned int addr);
extern unsigned int __gf_mmio_load_u32(unsigned int addr);
extern void __gf_mmio_store_u16(unsigned int addr, unsigned int value);
extern void __gf_mmio_store_u32(unsigned int addr, unsigned int value);

#define GF_MMIO_R16(addr) ((unsigned short)__gf_mmio_load_u16((unsigned int)(addr)))
#define GF_MMIO_R32(addr) ((unsigned int)__gf_mmio_load_u32((unsigned int)(addr)))
#define GF_MMIO_W16(addr, value) __gf_mmio_store_u16((unsigned int)(addr), (unsigned int)(value))
#define GF_MMIO_W32(addr, value) __gf_mmio_store_u32((unsigned int)(addr), (unsigned int)(value))

#endif /* GF_HW_MMIO_H */
