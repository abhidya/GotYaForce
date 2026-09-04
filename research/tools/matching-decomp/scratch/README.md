# Matching-decompilation scratches

One directory per target function, in the shape `decomp.me` and every GameCube
decomp project uses: the retail disassembly, and a candidate C file that is
supposed to compile to it.

**Every candidate here is UNVERIFIED.** `mwcceppc.exe` is not on this machine
(see [`docs/matching-decompilation-spike.md`](../../../../docs/matching-decompilation-spike.md) §1),
so none of these has been through the oracle. They exist to show exactly what
the loop submits and what a first iteration looks like — they are not results.

To verify one, once a licensed CodeWarrior for GameCube is installed:

```
python research/tools/matching-decomp/match.py \
    --function zz_008bbc0_ \
    --src research/tools/matching-decomp/scratch/zz_008bbc0_/cand.c \
    --json verdict.json
```

Exit 0 = MATCH, 1 = MISMATCH, 2 = build failed, 3 = no compiler.
