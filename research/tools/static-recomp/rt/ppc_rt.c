/* ppc_rt.c -- the runtime half of the machine model.  Spike scope.
 *
 * Everything here is WHOLE-PROGRAM, not per-function: one arena, one MMIO
 * router, one entry-point table.  Adding a function to the port adds a row to
 * the table; it does not add a spec, a capture plan, a shim, or a review.
 */
#include "ppc_rt.h"

#include <stdio.h>
#include <stdlib.h>

uint8_t *ppc_mem1 = 0;

void ppc_fault(const char *what, uint32_t a, uint32_t b)
{
    fprintf(stderr, "{\"k\":\"fault\",\"what\":\"%s\",\"a\":\"0x%08x\",\"b\":\"0x%08x\"}\n",
            what, a, b);
    exit(2);
}

/* The GameCube's hardware register block is 0xCC000000..0xCD000000.  A store
 * whose RESOLVED address lands there is hardware, whatever the source looked
 * like.  This is one range test in one place; the Ghidra-C route needs a
 * static source-rewriting pass (port_wgpipe_lowering.py) that can only see
 * stores whose address it can constant-fold, and fails the whole window closed
 * when it cannot. */
int ppc_is_mmio(uint32_t ea)
{
    return (ea >> 24) == 0xCCu || (ea >> 24) == 0xCDu;
}

/* Host hooks -- provided by the embedder (spike_host.c here, the browser HLE
 * host in a real port). */
extern void gf_host_wgpipe(ppc_ctx *c, uint32_t value, int width, int is_float);
extern uint32_t gf_host_mmio_load(ppc_ctx *c, uint32_t ea, int width);

void ppc_mmio_store(ppc_ctx *c, uint32_t ea, uint32_t value, int width, int is_float)
{
    if (ea >= 0xCC008000u && ea < 0xCC008020u) {
        gf_host_wgpipe(c, value, width, is_float);
        return;
    }
    ppc_fault("unmodelled MMIO store", ea, value);
}

uint32_t ppc_mmio_load(ppc_ctx *c, uint32_t ea, int width)
{
    return gf_host_mmio_load(c, ea, width);
}

/* ---------------------------------------------------------------- calls --*/

void ppc_bl(ppc_ctx *c, uint32_t target)
{
    ppc_fn f = ppc_lookup(target);
    if (!f) ppc_fault("call to an address with no entry in the function table",
                      target, c->cia);
    f(c);
}

void ppc_bctrl(ppc_ctx *c)
{
    /* The indirect call.  It is the SAME table lookup as a direct call, with a
     * runtime address instead of a constant.  This is why the 1,602 functions
     * the existing pipeline classifies "unverifiable -- ROM function-pointer
     * dispatch" are not a special case for a recompiler. */
    ppc_fn f = ppc_lookup(c->ctr);
    if (!f) ppc_fault("indirect call to an address with no entry in the function table",
                      c->ctr, c->cia);
    f(c);
}

void ppc_ps_unsupported(ppc_ctx *c, const char *mnemonic)
{
    ppc_fault("paired-single instruction not implemented", c->cia, 0);
    (void)mnemonic;
}

void ppc_supervisor(ppc_ctx *c, const char *mnemonic)
{
    ppc_fault("supervisor instruction not implemented", c->cia, 0);
    (void)mnemonic;
}
