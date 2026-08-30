#include "gnt4_shim.h"

// ==== 800527d8  zz_00527d8_ ====

/* CORPUS CORRECTION 2026-08-30: Ghidra invented a 16-parameter signature here.
 * ROM evidence: boot.dol from the retail ISO, capstone PPC32-BE, symbol map
 * research/symbols/GG4E-CSM-20220412.map.  0x800527d8 is 0x60 bytes / 24
 * instructions -- stwu r1,-0x10(r1); mflr r0; stw r0,0x14(r1); 19 bl (8002a3e4,
 * 8002a638, then the 17-call body from 800527ec); one store, stw r3,-0x5410(r13)
 * at 80052804 (r13=0x8043b5a0 -> DAT_80436190); back edge b 800527ec at 80052834.
 * No mr, no fmr, no load, and no store into the outgoing parameter area at r1+8
 * (the 0x10 frame leaves 8 bytes there and never writes them).  Nothing reads
 * r3-r10 or f1-f13 before defining it, so the ROM function takes no arguments.
 * Every callee Ghidra fed param_N is itself void(void) by its own disassembly:
 * 8002a3e4 / 8002a638 define r3-r6 via li/lis/lwz before each use; 800e9994 and
 * 8002a4d4 read only r13-relative state; 80018b10 the same (its int result comes
 * back in r3 from r31); 800efda8 is a single bl and reads nothing.  On console
 * those callees observe residue left in the volatile PPC EABI registers by the
 * previous callee, which the decompiler mistook for dataflow.  Measured in
 * research/decomp/data/oracle-results/spine-run-main-game-loop.boundary.json:
 * 274/274 calls and the owned write matched, 783/920 arg slots diverged. */
void zz_00527d8_(void)

{
  zz_002a3e4_();
  zz_002a638_();
  do {
    zz_010d450_();
    zz_008c088_();
    zz_0080278_();
    zz_0052838_();
    zz_00e9994_();
    DAT_80436190 = zz_008dbe0_();
    zz_000a004_();
    zz_0018b10_();
    zz_00efda8_();
    zz_002a4b0_();
    dispatch_global_menu_mode();
    zz_00528b4_();
    zz_00802a8_();
    zz_008c2dc_();
    zz_008c344_();
    zz_0027c34_();
    zz_002a4d4_();
  } while( true );
}
