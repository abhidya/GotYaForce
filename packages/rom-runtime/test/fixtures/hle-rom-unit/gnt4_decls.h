/* gnt4_decls.h -- prototypes for the out-of-window SDK callees this unit
 * calls, plus the two libc entry points emcc supplies.
 *
 * This is the counterpart of ../gx-rom-unit/gnt4_gx_decls.h and exists for the
 * same reason: the gate's merged shim carries DATA symbols and leaves function
 * callees implicitly declared, which C99 rejects -- and an implicit
 * declaration would also link every SDK import as `(params) -> i32` while the
 * host's adapters declare their real return classes. The bridge builds
 * signature-accurate per-import trampolines, so a return-class disagreement is
 * a real ABI bug, not a cosmetic one.
 *
 * THE EIGHT GHOST PARAMETERS. Ghidra renders the DVD entry points with eight
 * leading `undefined8` parameters before the real ones. Those are not
 * arguments: they are the decompiler's record of the PowerPC EABI's f1..f8
 * float-register slots, made visible by a varargs-shaped prototype. They carry
 * no data -- every call site in the corpus passes whatever happened to be in
 * those registers -- but they DO occupy dispatch-frame argument slots, so the
 * host's adapters read the path at slot 8 and the DVDFileInfo at slot 9.
 * Keeping them here, as `unsigned int`, is what makes the fixture's frame
 * layout the same one a gate-built module would produce. Declaring them
 * `unsigned int` rather than `unsigned long long` narrows each slot to i32,
 * which the bridge trampolines handle without an i64 marshalling path; the
 * slot INDEX -- which is what the adapters key off -- is unchanged.
 */
#ifndef GNT4_DECLS_H
#define GNT4_DECLS_H

#define GHOST8                                                                                  \
  unsigned int f1, unsigned int f2, unsigned int f3, unsigned int f4, unsigned int f5,           \
      unsigned int f6, unsigned int f7, unsigned int f8

/* [CORPUS] gnt4_DVDOpen_bl @0x8020d1ec: (ghosts..., char *path, int fileInfo, ...) -> int */
extern int gnt4_DVDOpen_bl(GHOST8, char *path, int fileInfo, unsigned int p11, unsigned int p12,
                           unsigned int p13, unsigned int p14, unsigned int p15, unsigned int p16);
/* [CORPUS] gnt4_DVDClose_bl @0x8020d2b4: narrow, one argument. */
extern int gnt4_DVDClose_bl(int *fileInfo);
/* [CORPUS] gnt4_OSDisableInterrupts_bl / gnt4_OSRestoreInterrupts_bl -- the OS
 * family, which is outside this work's surface. The selftest registers
 * explicitly-labelled scaffold adapters for them; they are NOT counted in any
 * audio or DVD coverage figure. */
extern int gnt4_OSDisableInterrupts_bl(void);
extern void gnt4_OSRestoreInterrupts_bl(int level);

/* libc, supplied by emcc. [CORPUS] the ROM calls its own copies; behaviourally
 * identical and not part of any seam. */
#include <string.h>

#endif /* GNT4_DECLS_H */
