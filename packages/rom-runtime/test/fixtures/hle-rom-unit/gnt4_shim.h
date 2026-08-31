/* gnt4_shim.h -- the data symbols this window touches, in the assembly gate's
 * own shape (src/port_assembly_gate.py merges one of these per window).
 *
 * HAND-WRITTEN, like everything else in this directory that is not a ROM body:
 * the gate has never run over these particular windows, because it cannot
 * lower their MMIO yet (see gf_hw_mmio.h). The FORM is copied exactly from
 * ../gx-rom-unit/gnt4_shim.h, which IS gate output, so that when the gate does
 * cover these windows its merged header drops in unchanged.
 *
 * Every macro maps a GameCube address STRAIGHT to a linear-memory offset,
 * which is why the module's memory has to be the gate's production arena size
 * (0x807A0000). See build.sh.
 */
#ifndef GNT4_ASSEMBLY_MERGE_H
#define GNT4_ASSEMBLY_MERGE_H

typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned int uint;
typedef unsigned short ushort;
/* size_t comes from <string.h>, which gnt4_decls.h includes. */

#define GC_IPTR(a) (*(int *)(unsigned int)(a))
#define GC_CPTR(a) ((char *)(unsigned int)(a))

/* [CORPUS] FUN_802756fc (gcCiGetFileSize) reads these four:
 *   DAT_8040b1d0  the error-reporting callback pointer (may be null)
 *   DAT_8040b1cc  the first argument that callback is handed
 *   DAT_8040c178  the base directory string every path is built onto
 *   the s_E00929xx_* strings are its message constants
 */
#define DAT_8040b1d0 (*(void (**)(int, const char *, int))(unsigned int)0x8040b1d0u)
#define DAT_8040b1cc GC_IPTR(0x8040b1cc)
#define DAT_8040c178 (*GC_CPTR(0x8040c178))

#define s_E0092901_fname_is_null__gcCiGetF_802b77ec GC_CPTR(0x802b77ecu)
#define s_E0040201_can_t_open_a_file__gcCi_802b7818 GC_CPTR(0x802b7818u)
#define s_E0040202_can_t_close_a_file__gcC_802b7848 GC_CPTR(0x802b7848u)

#endif /* GNT4_ASSEMBLY_MERGE_H */
