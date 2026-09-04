/* RETAIL, extracted from the DOL by dolsym.py. Authoritative. */
zz_008bbc0_:                    /* 0x8008bbc0, 4 instructions */
        lis   r3, 0xff          /* 3c6000ff */
        addi  r0, r3, 0x1f7f    /* 38031f7f  -> r0 = 0x00FF1F7F          */
        and   r3, r4, r0        /* 7c830038  -> return arg2 & 0x00FF1F7F */
        blr                     /* 4e800020                              */

/* Note: the 32-bit constant is built with lis+ADDI, not lis+ori. That is an
   MWCC habit; GCC emits lis+ori for the same constant. It is one of the
   idioms that says this DOL was not built with GCC. */
