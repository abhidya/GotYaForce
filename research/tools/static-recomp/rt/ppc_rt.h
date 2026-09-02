/* ppc_rt.h -- the whole machine model a statically recompiled PowerPC function
 * needs.  Feasibility-spike scope; see docs/static-recompilation-spike.md.
 *
 * THE POINT OF THIS FILE.  The existing pipeline's C is Ghidra's INFERENCE
 * about the machine code: types, parameter lists, the width of a store, whether
 * a value is a float.  A recompiler has no inferences to make, because it emits
 * one C statement per PowerPC instruction against an explicit register file and
 * explicit memory accessors.  Everything the translated code can possibly need
 * is here, and there is nothing else.
 *
 * MEMORY MODEL.  MEM1 is 24 MiB of GameCube RAM at 0x80000000 (cached alias)
 * / 0xC0000000 (uncached alias), held BIG-ENDIAN -- a literal image of console
 * memory.  Every access goes through an accessor, which is why:
 *   - byte order is settled once, here, instead of per-store in the source;
 *   - MMIO (0xCC______) is a range test in the accessor rather than a static
 *     source rewrite by an "assembly gate";
 *   - the arena does NOT have to be the wasm module's linear memory, so the
 *     2,155,479,040-byte fixed shared memory the Ghidra-C route requires
 *     (because its shim casts GameCube addresses straight to C pointers) is
 *     not a requirement here.  24 MiB is enough.
 */
#ifndef PPC_RT_H
#define PPC_RT_H

#include <stdint.h>
#include <string.h>

/* ---------------------------------------------------------------- state --*/

typedef struct ppc_ctx {
    uint32_t r[32];        /* GPRs */
    double   f[32];        /* FPRs, double view (ps0) */
    double   ps1[32];      /* paired-single second slot -- see ppc_ps_unsupported */
    uint32_t cr;           /* 8 x 4-bit fields, CR0 in the HIGH nibble */
    uint32_t xer;          /* bit 31-.. : SO=0x80000000 OV=0x40000000 CA=0x20000000 */
    uint32_t lr;
    uint32_t ctr;
    uint32_t fpscr;
    uint32_t gqr[8];       /* SPR 912..919: paired-single quantisation regs */
    uint32_t cia;          /* address of the instruction being executed */
} ppc_ctx;

/* SPRs the register file does not model are an explicit, NAMED seam call --
 * never a guess.  HID0/HID2/L2CR/DEC and friends land here. */
uint32_t gf_host_mfspr(struct ppc_ctx *c, int n);
void     gf_host_mtspr(struct ppc_ctx *c, int n, uint32_t v);
uint32_t gf_host_timebase(struct ppc_ctx *c, int n);

#define PPC_XER_SO 0x80000000u
#define PPC_XER_OV 0x40000000u
#define PPC_XER_CA 0x20000000u

/* ------------------------------------------------------------- memory ----*/

#define PPC_MEM1_BASE 0x80000000u
#define PPC_MEM1_SIZE 0x01800000u      /* 24 MiB */

extern uint8_t *ppc_mem1;

/* Hard error hooks.  A recompiler must fail loudly, never guess. */
void ppc_fault(const char *what, uint32_t a, uint32_t b);

/* MMIO.  A store whose RESOLVED effective address lands in a hardware window
 * is dispatched here.  The GameCube's write-gather pipe is 0xCC008000..20; the
 * host decides what to do with it.  Note that this is a RUNTIME test on the
 * computed EA -- the Ghidra-C route cannot do this, which is why it needs a
 * static "write-gather-pipe lowering" pass that fails closed on any store it
 * cannot constant-fold. */
int  ppc_is_mmio(uint32_t ea);
void ppc_mmio_store(ppc_ctx *c, uint32_t ea, uint32_t value, int width, int is_float);
uint32_t ppc_mmio_load(ppc_ctx *c, uint32_t ea, int width);

static inline uint32_t ppc_xlat(uint32_t ea)
{
    /* 0x8xxxxxxx cached, 0xCxxxxxxx uncached, both alias physical MEM1. */
    uint32_t off = ea & 0x03FFFFFFu;
    if (off >= PPC_MEM1_SIZE) ppc_fault("address out of MEM1", ea, 0);
    return off;
}

static inline uint8_t ppc_r8(ppc_ctx *c, uint32_t ea)
{
    if (ppc_is_mmio(ea)) return (uint8_t)ppc_mmio_load(c, ea, 1);
    return ppc_mem1[ppc_xlat(ea)];
}
static inline uint16_t ppc_r16(ppc_ctx *c, uint32_t ea)
{
    if (ppc_is_mmio(ea)) return (uint16_t)ppc_mmio_load(c, ea, 2);
    uint32_t o = ppc_xlat(ea);
    return (uint16_t)((ppc_mem1[o] << 8) | ppc_mem1[o + 1]);
}
static inline uint32_t ppc_r32(ppc_ctx *c, uint32_t ea)
{
    if (ppc_is_mmio(ea)) return ppc_mmio_load(c, ea, 4);
    uint32_t o = ppc_xlat(ea);
    return ((uint32_t)ppc_mem1[o] << 24) | ((uint32_t)ppc_mem1[o + 1] << 16)
         | ((uint32_t)ppc_mem1[o + 2] << 8) | (uint32_t)ppc_mem1[o + 3];
}
static inline uint64_t ppc_r64(ppc_ctx *c, uint32_t ea)
{
    return ((uint64_t)ppc_r32(c, ea) << 32) | ppc_r32(c, ea + 4);
}

static inline void ppc_w8(ppc_ctx *c, uint32_t ea, uint8_t v)
{
    if (ppc_is_mmio(ea)) { ppc_mmio_store(c, ea, v, 1, 0); return; }
    ppc_mem1[ppc_xlat(ea)] = v;
}
static inline void ppc_w16(ppc_ctx *c, uint32_t ea, uint16_t v)
{
    if (ppc_is_mmio(ea)) { ppc_mmio_store(c, ea, v, 2, 0); return; }
    uint32_t o = ppc_xlat(ea);
    ppc_mem1[o] = (uint8_t)(v >> 8); ppc_mem1[o + 1] = (uint8_t)v;
}
static inline void ppc_w32(ppc_ctx *c, uint32_t ea, uint32_t v)
{
    if (ppc_is_mmio(ea)) { ppc_mmio_store(c, ea, v, 4, 0); return; }
    uint32_t o = ppc_xlat(ea);
    ppc_mem1[o] = (uint8_t)(v >> 24); ppc_mem1[o + 1] = (uint8_t)(v >> 16);
    ppc_mem1[o + 2] = (uint8_t)(v >> 8); ppc_mem1[o + 3] = (uint8_t)v;
}
static inline void ppc_w64(ppc_ctx *c, uint32_t ea, uint64_t v)
{
    ppc_w32(c, ea, (uint32_t)(v >> 32)); ppc_w32(c, ea + 4, (uint32_t)v);
}

/* float <-> raw bits.  `stfs` stores the SINGLE bit pattern of the FPR's
 * double value; `lfs` widens.  The instruction says which, so there is nothing
 * to infer -- contrast gf_gx_wgpipe.h, which has to recover "floatness" from
 * the C type Ghidra guessed for the stored expression. */
static inline uint32_t ppc_f2u32(double d) { float f = (float)d; uint32_t u; memcpy(&u, &f, 4); return u; }
static inline double   ppc_u322f(uint32_t u) { float f; memcpy(&f, &u, 4); return (double)f; }
static inline uint64_t ppc_d2u64(double d) { uint64_t u; memcpy(&u, &d, 8); return u; }
static inline double   ppc_u642d(uint64_t u) { double d; memcpy(&d, &u, 8); return d; }

static inline void ppc_stfs(ppc_ctx *c, uint32_t ea, double v)
{
    if (ppc_is_mmio(ea)) { ppc_mmio_store(c, ea, ppc_f2u32(v), 4, 1); return; }
    ppc_w32(c, ea, ppc_f2u32(v));
}

/* ---------------------------------------------------------------- CR -----*/

static inline void ppc_setcrf(ppc_ctx *c, int f, uint32_t v)
{
    int sh = 28 - 4 * f;
    c->cr = (c->cr & ~(0xFu << sh)) | ((v & 0xFu) << sh);
}
static inline uint32_t ppc_getcrf(ppc_ctx *c, int f)
{
    return (c->cr >> (28 - 4 * f)) & 0xFu;
}
static inline int ppc_crbit(ppc_ctx *c, int bi) { return (c->cr >> (31 - bi)) & 1; }
static inline void ppc_setcrbit(ppc_ctx *c, int bi, int v)
{
    uint32_t m = 1u << (31 - bi);
    c->cr = v ? (c->cr | m) : (c->cr & ~m);
}

static inline void ppc_cmp(ppc_ctx *c, int f, int32_t a, int32_t b)
{
    uint32_t v = (a < b) ? 8u : (a > b) ? 4u : 2u;
    if (c->xer & PPC_XER_SO) v |= 1u;
    ppc_setcrf(c, f, v);
}
static inline void ppc_cmpl(ppc_ctx *c, int f, uint32_t a, uint32_t b)
{
    uint32_t v = (a < b) ? 8u : (a > b) ? 4u : 2u;
    if (c->xer & PPC_XER_SO) v |= 1u;
    ppc_setcrf(c, f, v);
}
/* Rc=1 forms: compare the result against zero into CR0. */
static inline void ppc_rc(ppc_ctx *c, uint32_t res) { ppc_cmp(c, 0, (int32_t)res, 0); }
static inline void ppc_fcmpu(ppc_ctx *c, int f, double a, double b)
{
    uint32_t v;
    if (a != a || b != b) v = 1u;            /* unordered */
    else if (a < b) v = 8u;
    else if (a > b) v = 4u;
    else v = 2u;
    ppc_setcrf(c, f, v);
}

static inline void ppc_setca(ppc_ctx *c, int ca)
{
    c->xer = ca ? (c->xer | PPC_XER_CA) : (c->xer & ~PPC_XER_CA);
}

/* --------------------------------------------------------- bit shuffles --*/

static inline uint32_t ppc_rotl32(uint32_t v, int n)
{
    n &= 31; return n ? ((v << n) | (v >> (32 - n))) : v;
}
static inline uint32_t ppc_mask(int mb, int me)
{
    /* PowerPC MASK(mb,me), inclusive, wrapping when mb > me. */
    uint32_t m;
    if (mb <= me) m = (me == 31 ? 0xFFFFFFFFu : ((1u << (31 - me)) - 1) ^ 0xFFFFFFFFu)
                       & (mb == 0 ? 0xFFFFFFFFu : (0xFFFFFFFFu >> mb));
    else m = ~(((mb == 0 ? 0xFFFFFFFFu : (0xFFFFFFFFu >> mb)))
               & ((me == 31 ? 0xFFFFFFFFu : ((1u << (31 - me)) - 1) ^ 0xFFFFFFFFu)));
    return m;
}
static inline uint32_t ppc_cntlzw(uint32_t v)
{
    uint32_t n = 0; if (!v) return 32;
    while (!(v & 0x80000000u)) { v <<= 1; n++; }
    return n;
}

/* --------------------------------------------------------------- calls ---*/

typedef void (*ppc_fn)(ppc_ctx *);

/* The whole-program entry-point table.  A `bl` is a lookup by constant; a
 * `bctrl` is the SAME lookup with a runtime value.  N64Recomp's jump table
 * over all known function entries is exactly this, and it is what makes the
 * 1,602 functions the existing pipeline calls "unverifiable -- ROM
 * function-pointer dispatch" ordinary code here. */
ppc_fn ppc_lookup(uint32_t addr);
void   ppc_bl(ppc_ctx *c, uint32_t target);
void   ppc_bctrl(ppc_ctx *c);

/* Instructions this spike's translator refuses to guess at.  Reaching one is a
 * loud abort, never a silently wrong value. */
void ppc_ps_unsupported(ppc_ctx *c, const char *mnemonic);
void ppc_supervisor(ppc_ctx *c, const char *mnemonic);

#endif /* PPC_RT_H */
