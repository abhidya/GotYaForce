/* BLOCKED  zz_00d1cbc_ @ 0x800d1cbc  (11 instructions)  -- NOT MATCHED
 *
 *   800d1cbc  38a00000  li   r5, 0
 *   800d1cc0  4800000c  b    0x800d1ccc
 *   800d1cc4  80a30004  lwz  r5, 4(r3)
 *   800d1cc8  38630008  addi r3, r3, 8
 *   800d1ccc  80030000  lwz  r0, 0(r3)
 *   800d1cd0  7c002000  cmpw r0, r4
 *   800d1cd4  4181000c  bgt  0x800d1ce0
 *   800d1cd8  2c00ffff  cmpwi r0, -1
 *   800d1cdc  4082ffe8  bne  0x800d1cc4
 *   800d1ce0  7ca32b78  mr   r3, r5
 *   800d1ce4  4e800020  blr
 *
 * mwcc-rs refuses:
 *
 *   mwcc: loop codegen is not implemented yet (roadmap) (in function 'f')
 *
 * The diagnostic understates its own capability: COUNTED `for` loops DO lower
 * correctly to mtctr/bdnz (verified separately).  What is missing is the
 * uncounted form -- a `while` whose continuation test is a conjunction over
 * loaded values, which is what a table walk is.  The census counts 15.5 % of
 * functions as containing a loop, so this is a large blocked class.
 *
 * The C below is a plausible first candidate.  It has never compiled.
 */

typedef struct Entry { int key; int value; } Entry;

int f(Entry *entry, int key)
{
    int value = 0;
    while (entry->key <= key && entry->key != -1) {
        value = entry->value;
        entry++;
    }
    return value;
}
