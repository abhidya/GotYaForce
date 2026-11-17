#!/usr/bin/env python3
"""Read fixed actor movement-followup evidence from authenticated ProgramDB.

Read-only stdlib; two fixed instruction spans and three fixed scalar targets.
No arbitrary-address CLI, raw-range output, disassembler or vendor execution.
Existing constants/parser are reused without expanding their public allowlist.
"""
import argparse
import hashlib
import json
import math
from pathlib import Path
import struct
import sys
import read_archived_constants as c
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH, text_mapping

RANGES = (
    (0x80048648, 212, '0eb26bc9a603d933ffcaf3e9065583d3127cb603be56c29d887566f9211a2ad9'),
    (0x8004d08c, 360, 'ba2fb11f03cbfae5126e2f32f33bae5fe2b01840191bd77d8e7348a507ae97e7'),
)
MOVEMENT_TARGETS = (
    (0x80437104, 4, '3f000000'),
    (0x80437134, 4, '3f333333'),
    (0x8043714c, 4, '40a00000'),
)
# Selected exact instruction facts. This is not a general disassembler.
WORDS = {
    0x80048664: (0x80031d88, 'lwz r0,0x1d88(r3): first outer gate'),
    0x8004866c: (0x41820098, 'beq 80048704: skip all later actor reads'),
    0x80048670: (0x801e1d8c, 'lwz r0,0x1d8c(r30): second gate'),
    0x80048678: (0x40820008, 'bne 80048680: both banks nonnull'),
    0x8004867c: (0x48000088, 'b 80048704'),
    0x80048680: (0x2c1f0001, 'cmpwi r31,1: channel'),
    0x80048684: (0x4082001c, 'bne 800486a0: non-part1 skips suppression bytes'),
    0x80048688: (0x881e0578, 'lbz r0,0x578(r30)'),
    0x80048690: (0x40820010, 'bne 800486a0: first byte not1 skips second'),
    0x80048694: (0x881e1db3, 'lbz r0,0x1db3(r30)'),
    0x8004869c: (0x41820068, 'beq 80048704: both suppression bytes1'),
    0x800486a0: (0x887e1d9a, 'lbz r3,0x1d9a(r30)'),
    0x800486a8: (0x7c00f830, 'slw r0,r0,r31: PPC 32-bit channel bit'),
    0x800486ac: (0x7c630774, 'extsb r3,r3: signed mask byte'),
    0x800486b0: (0x7c600039, 'and. r0,r3,r0'),
    0x800486b4: (0x41820018, 'beq 800486cc: ordinary setup branch'),
    0x800486c0: (0x38800000, 'li r4,0: alternate branch first argument'),
    0x800486c4: (0x48001d59, 'bl 8004a41c: no movement followup on this path'),
    0x800486c8: (0x4800003c, 'b 80048704'),
    0x800486d0: (0x5500103a, 'slwi r0,r8,2: mode-table index'),
    0x800486dc: (0x7d83002e, 'lwzx r12,r3,r0: table802d0d70'),
    0x800486e8: (0x4e800421, 'bctrl: actual setup before part1 followup'),
    0x800486ec: (0x2c1f0001, 'cmpwi r31,1: retained channel after setup'),
    0x800486f0: (0x40820014, 'bne 80048704'),
    0x800486f4: (0xc00286d0, 'lfs f0,-0x7930(r2): authenticated804370f0=1'),
    0x800486fc: (0xd01e06d8, 'stfs f0,0x6d8(r30): preserve before followup refusal'),
    0x80048700: (0x4800498d, 'bl 8004d08c'),
    0x80048718: (0x4e800020, 'blr'),
    0x8004d090: (0x880303e8, 'lbz r0,0x3e8(r3): first movement gate'),
    0x8004d094: (0x2c000005, 'cmpwi r0,5'),
    0x8004d098: (0x4182014c, 'beq 8004d1e4: zero-store branch'),
    0x8004d09c: (0x88030661, 'lbz r0,0x661(r3): second gate only'),
    0x8004d0a0: (0x7c000775, 'extsb. r0,r0: signed nonzero gate'),
    0x8004d0a4: (0x40820140, 'bne 8004d1e4'),
    0x8004d0a8: (0x800305e0, 'lwz r0,0x5e0(r3): third gate only'),
    0x8004d0ac: (0x54000673, 'rlwinm. r0,r0,0,25,25: test0x40'),
    0x8004d0b0: (0x41820134, 'beq 8004d1e4'),
    0x8004d0b4: (0x8883071d, 'lbz r4,0x71d(r3): exactly one override-byte load'),
    0x8004d0b8: (0x7c800775, 'extsb. r0,r4: signed override test'),
    0x8004d0bc: (0x41820040, 'beq 8004d0fc: normal path'),
    0x8004d0c0: (0x7c840774, 'extsb r4,r4: retain original signed byte'),
    0x8004d0c8: (0x3884ffff, 'addi r4,r4,-1: signed value minus1'),
    0x8004d0d0: (0x6c808000, 'xoris r0,r4,0x8000: integer conversion'),
    0x8004d0d4: (0xc84286d8, 'lfd f2,-0x7928(r2): authenticated804370f8'),
    0x8004d0dc: (0xc062872c, 'lfs f3,-0x78d4(r2): 8043714c=5'),
    0x8004d0e0: (0xc8210008, 'lfd f1,8(r1): integer conversion stack'),
    0x8004d0e4: (0xc00300b4, 'lfs f0,0xb4(r3): scale before arithmetic'),
    0x8004d0e8: (0xec211028, 'fsubs f1,f1,f2: exact small signed integer'),
    0x8004d0ec: (0xec230072, 'fmuls f1,f3,f1:5 times signedByteMinus1'),
    0x8004d0f0: (0xec010032, 'fmuls f0,f1,f0: then actor scale'),
    0x8004d0f4: (0xd00306d0, 'stfs f0,0x6d0(r3): override has no clamp'),
    0x8004d0f8: (0x480000f4, 'b 8004d1ec: override returns'),
    0x8004d0fc: (0x808304b0, 'lwz r4,0x4b0(r3): retain initial descriptor'),
    0x8004d100: (0xc0830670, 'lfs f4,0x670(r3): snapshot once BEFORE920 load'),
    0x8004d104: (0xc0030920, 'lfs f0,0x920(r3)'),
    0x8004d108: (0x38c40022, 'addi r6,r4,0x22: list retained across descriptor reload'),
    0x8004d10c: (0xc04286e4, 'lfs f2,-0x791c(r2):80437104=0.5'),
    0x8004d110: (0xd00306d0, 'stfs f0,0x6d0(r3): first normal-path store'),
    0x8004d114: (0xc023066c, 'lfs f1,0x66c(r3): after first store'),
    0x8004d118: (0xc00306d0, 'lfs f0,0x6d0(r3): reload first store'),
    0x8004d11c: (0xec0100bc, 'fnmsubs f0,f1,f2,f0: negative fused multiply-subtract'),
    0x8004d120: (0xd00306d0, 'stfs f0,0x6d0(r3)'),
    0x8004d124: (0x808304b0, 'lwz r4,0x4b0(r3): descriptor reload'),
    0x8004d128: (0xc0630024, 'lfs f3,0x24(r3): retained first baseY'),
    0x8004d12c: (0x8804000f, 'lbz r0,0xf(r4): joint from reloaded descriptor'),
    0x8004d130: (0xc00306d0, 'lfs f0,0x6d0(r3): before transform read'),
    0x8004d134: (0x7c000774, 'extsb r0,r0: signed joint index'),
    0x8004d138: (0x1c000030, 'mulli r0,r0,0x30'),
    0x8004d13c: (0x7c830214, 'add r4,r3,r0: source modulo32 address'),
    0x8004d140: (0xc02408f0, 'lfs f1,0x8f0(r4): selected transformY'),
    0x8004d144: (0xec211828, 'fsubs f1,f1,f3: rounded delta'),
    0x8004d148: (0xec2118ba, 'fmadds f1,f1,f2,f3: one fused rounding'),
    0x8004d14c: (0xfc010040, 'fcmpo cr0,f1,f0: compare candidate to prior6d0'),
    0x8004d150: (0x40800008, 'bge 8004d158: skip unless strictly less'),
    0x8004d154: (0xd02306d0, 'stfs f1,0x6d0(r3): selected first candidate'),
    0x8004d158: (0x38a00000, 'li r5,0: list count'),
    0x8004d15c: (0x48000030, 'b 8004d18c: count check before list load'),
    0x8004d160: (0x7c800774, 'extsb r0,r4: signed list index'),
    0x8004d164: (0xc00306d0, 'lfs f0,0x6d0(r3): before list transform'),
    0x8004d168: (0x1c800030, 'mulli r4,r0,0x30'),
    0x8004d16c: (0x380408f0, 'addi r0,r4,0x8f0'),
    0x8004d170: (0x7c23042e, 'lfsx f1,r3,r0: indexed transformY'),
    0x8004d174: (0xec212028, 'fsubs f1,f1,f4: ENTRY snapshot670, not live read'),
    0x8004d178: (0xfc010040, 'fcmpo cr0,f1,f0'),
    0x8004d17c: (0x40800008, 'bge 8004d184: skip unless strictly less'),
    0x8004d180: (0xd02306d0, 'stfs f1,0x6d0(r3): selected list candidate'),
    0x8004d184: (0x38a50001, 'addi r5,r5,1'),
    0x8004d188: (0x38c60008, 'addi r6,r6,8: retained list advances'),
    0x8004d18c: (0x2c050004, 'cmpwi r5,4'),
    0x8004d190: (0x40800014, 'bge 8004d1a4: no fifth list-byte read'),
    0x8004d194: (0x88860000, 'lbz r4,0(r6): current retained list byte'),
    0x8004d198: (0x7c800774, 'extsb r0,r4: signed sentinel test'),
    0x8004d19c: (0x2c00ffff, 'cmpwi r0,-1'),
    0x8004d1a0: (0x4082ffc0, 'bne 8004d160: -1 alone ends list'),
    0x8004d1a4: (0xc02306d0, 'lfs f1,0x6d0(r3): tail reload'),
    0x8004d1a8: (0xc0030024, 'lfs f0,0x24(r3): tail baseY reload'),
    0x8004d1ac: (0xc0428714, 'lfs f2,-0x78ec(r2):80437134=0.7f'),
    0x8004d1b0: (0xec210028, 'fsubs f1,f1,f0: rounded displacement'),
    0x8004d1b4: (0xc00286d4, 'lfs f0,-0x792c(r2): authenticated positive zero'),
    0x8004d1b8: (0xd02306d0, 'stfs f1,0x6d0(r3): displacement store'),
    0x8004d1bc: (0xc02306d8, 'lfs f1,0x6d8(r3): scale BEFORE displacement reload'),
    0x8004d1c0: (0xc06306d0, 'lfs f3,0x6d0(r3): displacement reload'),
    0x8004d1c4: (0xec220072, 'fmuls f1,f2,f1: FIRST0.7f times scale'),
    0x8004d1c8: (0xec230072, 'fmuls f1,f3,f1: THEN displacement times product'),
    0x8004d1cc: (0xd02306d0, 'stfs f1,0x6d0(r3): scaled displacement'),
    0x8004d1d0: (0xc02306d0, 'lfs f1,0x6d0(r3): clamp reload'),
    0x8004d1d4: (0xfc010040, 'fcmpo cr0,f1,f0: compare to positive zero'),
    0x8004d1d8: (0x40800014, 'bge 8004d1ec: -0 survives; unordered also skips'),
    0x8004d1dc: (0xd00306d0, 'stfs f0,0x6d0(r3): strictly negative clamps to+0'),
    0x8004d1e0: (0x4800000c, 'b 8004d1ec'),
    0x8004d1e4: (0xc00286d4, 'lfs f0,-0x792c(r2): disabled branch loads only+0'),
    0x8004d1e8: (0xd00306d0, 'stfs f0,0x6d0(r3): disabled branch only actor write'),
    0x8004d1f0: (0x4e800020, 'blr'),
}


def float_instruction(word):
    """Decode only five observed floating forms for operand/rounding checks."""
    c.require(isinstance(word, int) and 0 <= word <= 0xffffffff, 'word bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    fc, xo = (word >> 6) & 31, (word >> 1) & 31
    if op == 59 and word & 1 == 0:
        if xo == 20 and fc == 0:
            return dict(mnemonic='fsubs', fD=d, fA=a, fB=b, rounding='single')
        if xo == 25 and b == 0:
            return dict(mnemonic='fmuls', fD=d, fA=a, fC=fc, rounding='single')
        if xo in (29, 30):
            return dict(mnemonic={29:'fmadds', 30:'fnmsubs'}[xo], fD=d, fA=a,
                        fC=fc, fB=b, rounding='single fused')
    if op == 63 and (word >> 1) & 1023 == 32 and word & 1 == 0 and d & 3 == 0:
        return dict(mnemonic='fcmpo', crD=d >> 2, fA=a, fB=b)
    raise c.FormatError('unsupported floating instruction form')


def range_evidence(db, root, address, width):
    matches = [r for r in RANGES if r[:2] == (address, width)]
    c.require(len(matches) == 1, 'range not allowlisted')
    c.require(address % 4 == width % 4 == 0 and
              TEXT_START <= address < address+width <= TEXT_START+TEXT_LENGTH,
              'range alignment/bounds')
    raw, spans = db.chain(root, address-TEXT_START, width, TEXT_LENGTH)
    c.require(len(raw) == width, 'range byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == matches[0][2], 'range digest mismatch')
    facts = []
    for pc, (expected, annotation) in WORDS.items():
        if address <= pc < address+width:
            word = c.integer(raw, pc-address, 'I')
            c.require(word == expected, 'instruction word mismatch')
            fact = dict(address=f'{pc:08x}', word=f'{word:08x}', annotation=annotation)
            if word >> 26 in (59, 63):
                fact.update(float_instruction(word))
            facts.append(fact)
    return dict(address=f'{address:08x}', width=width, sha256=digest,
                spans=spans, instructions=facts)


def constant_evidence(db, mapping, address, width):
    matches = [r for r in MOVEMENT_TARGETS if r[:2] == (address, width)]
    c.require(len(matches) == 1, 'constant not allowlisted')
    start, end, _, _, _, length, root = mapping
    c.require(width == 4 and start <= address < address+width <= end,
              'constant width/bounds')
    raw, spans = db.chain(root, address-start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == matches[0][2], 'constant bits mismatch')
    value = struct.unpack('>f', raw)[0]
    c.require(math.isfinite(value), 'nonfinite constant')
    return dict(address=f'{address:08x}', type='f32', bytes=raw.hex(), number=value,
                sha256=hashlib.sha256(raw).hexdigest(), spans=spans,
                control=False)


def inspect(data, digest):
    # Authenticate the entire snapshot, exact schemas, metadata, address map,
    # complete data5 digest and existing controls before reading new targets.
    constants = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(constants['image_offset'], 16)
    root = text_mapping(blocks, subs, image)
    mapping = c.data5_mapping(blocks, subs, image)
    c.require(mapping == (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263),
              'data5 mapping mismatch')
    ranges = [range_evidence(db, root, address, width) for address, width, _ in RANGES]
    recovered = [constant_evidence(db, mapping, address, width)
                 for address, width, _ in MOVEMENT_TARGETS]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset')
    return dict({k:constants[k] for k in keys}, block_name='MAIN_.text1', block_key=1,
                subblock_key=1, block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                chain_root=root, ranges=ranges, movement_constants=recovered,
                existing_constants=[r for r in constants['results']
                                    if r['address'] in ('804370f0', '804370f4', '804370f8')],
                data5_mapping=dict(block_name=mapping[3], block_key=mapping[2],
                                   subblock_key=mapping[4], block_start=f'{mapping[0]:08x}',
                                   block_length=mapping[5], chain_root=mapping[6],
                                   sha256=constants['data5_sha256']),
                constant_scope='Three fixed movement constants only; existing twelve-target reader unchanged.',
                floating_caveat='Instruction forms establish fused/single sites, not captured FPSCR modes, exceptions or live parity.',
                provenance_caveat='Archived ProgramDB agreement is not original-DOL or live-runtime proof.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('snapshot', type=Path)
    args = parser.parse_args()
    try:
        c.require(args.snapshot.is_file(), 'snapshot is not a regular file')
        with args.snapshot.open('rb') as stream:
            c.require(32 <= args.snapshot.stat().st_size <= c.MAX_FILE, 'file size bounds')
            data = stream.read(c.MAX_FILE+1)
        c.require(len(data) <= c.MAX_FILE, 'file exceeds bound')
        print(json.dumps(inspect(data, hashlib.sha256(data).hexdigest()), indent=2, allow_nan=False))
    except (OSError, c.FormatError) as exc:
        print(json.dumps({'error':str(exc)}), file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
