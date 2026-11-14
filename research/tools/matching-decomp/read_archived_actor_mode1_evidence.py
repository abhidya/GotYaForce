#!/usr/bin/env python3
"""Fixed ordinary actor envelope and mode-one setup/playback archived evidence.

Read-only stdlib. Complete independent named spans and fixed instruction-named
scalars only, after full snapshot/schema/mapping authentication. No arbitrary
selection, pointer following, raw ranges, execution or shared allowlist edits.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_actor_normal_evidence as normal
import read_archived_command_evidence as command
import read_archived_constants as c

TEXT_MAPPING = normal.TEXT_MAPPING
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)
# Each selection has independent named C bounds, never a returned pointer.
RANGES = (
    (0x80055568, 292, '4ef4d2db70068dec76e280773b3d58c546452599966914bffd4f8cbaf56472c7'),
    (0x800487ec, 320, '89ff3f5e42d9fb00cbb2b9cd09864c30a2de70f0539ca93245827a290548571d'),
    (0x8004a00c, 212, '943a91557593db9ea74d25db6555ccde8ada24fa808aa1dbb944ec4522be2f3f'),
    (0x8004b94c, 456, 'eb174f015991c8786bb609ba168c208ad41e6213bb209a9eb37e4d35512e19b3'),
    (0x8004a8cc, 532, '2da4f533bb5e7cb3ee7f530dae5f56ab60027846174ddd4824c05e5cb6077321'),
    (0x8020ba9c, 28, 'e0fbf8bbb6f184d7b21d322b68975adca6dc652510963c83c95b9ceb63e0671d'),
    (0x8020bf08, 372, '30cb73d805f9a7ac73924e6898d2c8a98a36fff0a5a1a517168e9884c22af4e7'),
)
CONSTANTS = (
    (0x804370f0, '3f800000', 'one'),
    (0x804370f4, '00000000', 'zero'),
    (0x804370f8, '4330000080000000', 'signed-integer-conversion-double'),
    (0x80437104, '3f000000', 'half'),
    (0x8043cab8, '3f800000', 'quaternion-one'),
    (0x8043caa0, '00000000', 'quaternion-zero'),
    (0x8043cac0, '3f7fff58', 'quaternion-linear-threshold'),
)


def decode_selected(word, pc):
    """Observed PPC forms only, with every operand and condition field explicit."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 19 and xo == 449:
        c.require(rc == 0, 'reserved condition-register bit')
        return dict(mnemonic='cror', BT=d, BA=a, BB=b)
    if op == 19 and xo in (16, 528):
        c.require(word in (0x4e800020, 0x4e800421), 'unselected branch-register form')
        return dict(mnemonic='blr' if xo == 16 else 'bctrl', BO=d, BI=a, BH=0, LK=rc)
    if op == 18:
        c.require(word & 2 == 0, 'unselected absolute branch')
        return dict(mnemonic='bl' if rc else 'b',
                    target=f'{(pc + normal.signed(word & 0x3fffffc, 26)) & 0xffffffff:08x}', AA=0, LK=rc)
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 0), (4, 1), (4, 2), (12, 0), (12, 1), (12, 2), (16, 0)),
                  'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op == 11:
        c.require(d == 0, 'unselected comparison fields')
        return dict(mnemonic='cmpi', BF=0, L=0, rA=a, immediate=normal.signed(word & 65535, 16))
    if op in (7, 14, 15):
        return dict(mnemonic={7: 'mulli', 14: 'addi', 15: 'addis'}[op], rD=d, rA=a,
                    immediate=normal.signed(word & 65535, 16))
    if op in (26, 27):
        return dict(mnemonic='xori' if op == 26 else 'xoris', rS=d, rA=a, immediate=word & 65535)
    if op == 21:
        return dict(mnemonic='rlwinm', rS=d, rA=a, SH=b, MB=fc, ME=(word >> 1) & 31, Rc=rc)
    if op in (32, 34, 36, 37, 38, 46, 47, 48, 50, 52, 54):
        name, reg = {32: ('lwz', 'rD'), 34: ('lbz', 'rD'), 36: ('stw', 'rS'),
                     37: ('stwu', 'rS'), 38: ('stb', 'rS'), 46: ('lmw', 'rD'),
                     47: ('stmw', 'rS'), 48: ('lfs', 'fD'), 50: ('lfd', 'fD'),
                     52: ('stfs', 'fS'), 54: ('stfd', 'fS')}[op]
        c.require(op != 37 or a != 0, 'reserved store-update base')
        c.require(op != 46 or a < d, 'overlapping load-multiple base')
        return dict(mnemonic=name, **{reg: d}, rA=a, displacement=normal.signed(word & 65535, 16))
    if op in (56, 60):
        return dict(mnemonic='psq_l' if op == 56 else 'psq_st', **{'fD' if op == 56 else 'fS': d},
                    rA=a, displacement=normal.signed(word & 4095, 12), W=(word >> 15) & 1, I=(word >> 12) & 7)
    if op == 31:
        if xo in (339, 467):
            spr = (b << 5) | a
            c.require(rc == 0 and ((spr == 8 and d == 0) or (spr == 9 and xo == 467)), 'unselected SPR form')
            if spr == 9:
                return dict(mnemonic='mtctr', rS=d)
            return dict(mnemonic='mflr', rD=0) if xo == 339 else dict(mnemonic='mtlr', rS=0)
        if xo == 0:
            c.require(d == rc == 0, 'unselected register comparison fields')
            return dict(mnemonic='cmp', BF=0, L=0, rA=a, rB=b)
        if xo in (23, 87):
            c.require(rc == 0, 'reserved indexed-load bit')
            return dict(mnemonic='lwzx' if xo == 23 else 'lbzx', rD=d, rA=a, rB=b)
        if xo == 954:
            c.require(b == 0, 'reserved sign-extension fields')
            return dict(mnemonic='extsb', rS=d, rA=a, Rc=rc)
        if xo == 444:
            return dict(mnemonic='or', rS=d, rA=a, rB=b, Rc=rc)
        if xo == 266:
            return dict(mnemonic='add', rD=d, rA=a, rB=b, OE=0, Rc=rc)
    if op == 4 and (xo & 31) == 12:
        c.require(b == rc == 0, 'reserved paired-multiply fields')
        return dict(mnemonic='ps_muls0', fD=d, fA=a, fC=fc, Rc=0)
    if op == 59 and (xo & 31) in (18, 20, 21, 25):
        form = xo & 31
        c.require(rc == 0 and (b == 0 if form == 25 else fc == 0),
                  'unselected single-arithmetic fields')
        if form == 25:
            return dict(mnemonic='fmuls', fD=d, fA=a, fC=fc, Rc=0)
        return dict(mnemonic={18: 'fdivs', 20: 'fsubs', 21: 'fadds'}[form], fD=d, fA=a, fB=b, Rc=0)
    if op == 63:
        if xo == 32:
            c.require(d == rc == 0, 'unselected floating-comparison fields')
            return dict(mnemonic='fcmpo', BF=0, fA=a, fB=b)
        if xo in (40, 72):
            c.require(a == rc == 0, 'reserved floating-unary fields')
            return dict(mnemonic='fneg' if xo == 40 else 'fmr', fD=d, fB=b, Rc=0)
    return None


def range_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    normal.require_mapping(mapping, TEXT_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == width % 4 == 0 and start <= address < address + width <= end, 'range alignment/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'range byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'range digest mismatch')
    instructions = []
    for offset in range(0, width, 4):
        pc = address + offset
        decoded = decode_selected(c.integer(raw, offset, 'I'), pc)
        c.require(decoded is not None, 'unselected instruction in fixed span')
        instructions.append(dict(address=f'{pc:08x}', **decoded))
    c.require(instructions[-1]['mnemonic'] == 'blr', 'span terminal return mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('b', 'bc')), 'non-call branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def constant_evidence(db, mapping, address):
    c.require(type(address) is int, 'constant integer fields')
    selected = [item for item in CONSTANTS if item[0] == address]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    _, bits, label = selected[0]
    width = len(bits) // 2
    start, end, _, _, _, length, root = mapping
    c.require(width in (4, 8) and address % width == 0 and start <= address < address + width <= end, 'constant alignment/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == bits, 'constant bits mismatch')
    return dict(address=f'{address:08x}', label=label, width=width, bits=bits,
                value=struct.unpack('>f' if width == 4 else '>d', raw)[0], sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def inspect(data, digest):
    # Existing actual whole-file SHA/schema/language/metadata/File Bytes/maps,
    # full data5 hash and controls precede every new payload selection.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, text_fact = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data5, data5_fact = normal.mapping_evidence(blocks, subs, image, DATA5_MAPPING)
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[text_fact, data5_fact],
                ranges=[range_evidence(db, text, address, width) for address, width, _ in RANGES],
                constants=[constant_evidence(db, data5, address) for address, _, _ in CONSTANTS],
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                                        selected_width=width, represented_instructions=width // 4,
                                        unrepresented_instructions=0, unrepresented_ranges=[],
                                        extent_basis='named C markers, map size and authenticated return'
                                        if address in (0x8020ba9c, 0x8020bf08) else 'named C markers and authenticated return',
                                        map_size={0x8020ba9c: 28, 0x8020bf08: 372}.get(address))
                                   for address, width, _ in RANGES],
                dispatch_basis='Existing normal-matrix evidence: setup slot1 cell 802d0d74 -> 800487ec; '
                               'playback slot1 cell 802d0d88 -> 8004a00c. No pointer cells selected here.',
                caveat='Archived ProgramDB static evidence only, not unchanged original-DOL identity, '
                       'live dispatch, actor ownership, runtime integration, numerical parity or playable-game proof. '
                       'Every instruction in each fixed span is represented. External callees remain explicit '
                       'call boundaries. No pointer or decoded call determines a read. Scalar and paired-single '
                       'execution requires separately stated FPSCR/GQR assumptions, not established live state.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('snapshot', type=Path)
    args = parser.parse_args()
    try:
        c.require(args.snapshot.is_file(), 'snapshot is not a regular file')
        with args.snapshot.open('rb') as stream:
            c.require(32 <= args.snapshot.stat().st_size <= c.MAX_FILE, 'snapshot size bounds')
            data = stream.read(c.MAX_FILE + 1)
        c.require(len(data) <= c.MAX_FILE, 'snapshot exceeds size bound')
        print(json.dumps(inspect(data, hashlib.sha256(data).hexdigest()), indent=2, allow_nan=False))
    except (OSError, c.FormatError) as exc:
        print(json.dumps({'error': str(exc)}), file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
