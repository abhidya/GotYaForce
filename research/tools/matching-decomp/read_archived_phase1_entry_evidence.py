#!/usr/bin/env python3
"""Four fixed Double phase-one selections from authenticated archived ProgramDBs.

Read-only stdlib. Whole-snapshot authentication precedes literal selections of
one phase cell, one complete body, one config callback cell and one threshold.
No command-prefix/table reads, pointer following, arbitrary-address CLI, raw
payload output, original execution, or changes to shared reader allowlists.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_actor_normal_evidence as normal
import read_archived_double_action_evidence as double

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
DATA4_MAPPING = double.DATA4_MAPPING
DATA5_MAPPING = double.DATA5_MAPPING
# Adjacent named C/index entries and map size independently fix this extent.
RANGES = ((0x800ff418, 188, '4d7718098a024195217efd94548567af5e30aefaa970b02de985bc2566fd59e8'),)
# Literal selections, never code addresses to follow.
CELLS = (
    ('phase1', 0x8031f004, 0x800ff418, '21ba1af7a6b8585448a533d5cb69f0592dcae0a1c27ec6c49625f39f61f527da'),
    ('config-callback', 0x8043386c, 0x800715f8, '91cbc2b5e1dc50f2d1d25c141235833e121cc9f3139cdc919a5b10fe6155a607'),
)
CONSTANTS = ((0x804392c8, '40400000', 'motion-threshold',
              '638354a0b185ec05318029e52610c8de48d33523e2b4854e71154187583d1037'),)


def decode_selected(word, pc):
    """Only selected PPC forms; every variable operand is preserved explicitly."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 19:
        c.require(word in (0x4e800020, 0x4e800421), 'unselected branch-register form')
        return dict(mnemonic='blr' if word == 0x4e800020 else 'bctrl', BO=d, BI=a, BH=0, LK=rc)
    if op == 18:
        c.require(word & 3 == 1, 'unselected direct-call fields')
        return dict(mnemonic='bl', target=f'{(pc + normal.signed(word & 0x3fffffc, 26)) & 0xffffffff:08x}',
                    AA=0, LK=1)
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 1), (12, 2)), 'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op == 10:
        c.require(d == 0, 'unselected comparison fields')
        return dict(mnemonic='cmpli', BF=0, L=0, rA=a, immediate=word & 65535)
    if op == 14:
        return dict(mnemonic='addi', rD=d, rA=a, immediate=normal.signed(word & 65535, 16))
    if op in (32, 34, 36, 37, 38, 48):
        name, reg = {32: ('lwz', 'rD'), 34: ('lbz', 'rD'), 36: ('stw', 'rS'),
                     37: ('stwu', 'rS'), 38: ('stb', 'rS'), 48: ('lfs', 'fD')}[op]
        c.require(op != 37 or a != 0, 'reserved store-update base')
        return dict(mnemonic=name, **{reg: d}, rA=a, displacement=normal.signed(word & 65535, 16))
    if op == 31:
        if xo in (339, 467):
            spr = (b << 5) | a
            c.require(rc == 0 and ((spr == 8 and d == 0) or (spr == 9 and xo == 467)),
                      'unselected SPR form')
            if spr == 9:
                return dict(mnemonic='mtctr', rS=d)
            return dict(mnemonic='mflr', rD=0) if xo == 339 else dict(mnemonic='mtlr', rS=0)
        if xo == 954:
            c.require(b == 0, 'reserved sign-extension fields')
            return dict(mnemonic='extsb', rS=d, rA=a, Rc=rc)
        if xo == 444:
            return dict(mnemonic='or', rS=d, rA=a, rB=b, Rc=rc)
    if op == 63 and xo == 32:
        c.require(d == rc == 0, 'unselected floating-comparison fields')
        return dict(mnemonic='fcmpo', BF=0, fA=a, fB=b)
    return None


def range_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    normal.require_mapping(mapping, TEXT_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == width % 4 == 0 and start <= address < address + width <= end,
              'range alignment/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'range byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'range digest mismatch')
    instructions = []
    for offset in range(0, width, 4):
        pc = address + offset
        decoded = decode_selected(c.integer(raw, offset, 'I'), pc)
        c.require(decoded is not None, f'unselected instruction at {pc:08x}')
        instructions.append(dict(address=f'{pc:08x}', **decoded))
    c.require([item['address'] for item in instructions if item['mnemonic'] == 'blr'] == ['800ff4d0'],
              'span return-site mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] == 'bc'), 'branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def cell_evidence(db, mapping, address):
    c.require(type(address) is int, 'cell integer fields')
    selected = [item for item in CELLS if item[1] == address]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING if address == 0x8031f004 else DATA4_MAPPING)
    label, _, target, expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == 0 and start <= address < address + 4 <= end, 'cell alignment/bounds')
    raw, spans = db.chain(root, address - start, 4, length)
    c.require(len(raw) == 4, 'cell byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected, 'cell digest mismatch')
    actual = c.integer(raw, 0, 'I')
    c.require(actual == target, 'cell target mismatch')
    return dict(label=label, address=f'{address:08x}', end_exclusive=f'{address + 4:08x}', width=4,
                target=f'{actual:08x}', sha256=digest, spans=spans)


def constant_evidence(db, mapping, address):
    c.require(type(address) is int, 'constant integer fields')
    selected = [item for item in CONSTANTS if item[0] == address]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    _, bits, label, expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == 0 and start <= address < address + 4 <= end, 'constant alignment/bounds')
    raw, spans = db.chain(root, address - start, 4, length)
    c.require(len(raw) == 4, 'constant byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected, 'constant digest mismatch')
    c.require(raw.hex() == bits, 'constant bits mismatch')
    return dict(label=label, address=f'{address:08x}', end_exclusive=f'{address + 4:08x}', width=4,
                bits=bits, value=struct.unpack('>f', raw)[0], sha256=digest, spans=spans)


def inspect(data, digest):
    # Unchanged complete SHA/schema/language/File Bytes/maps/data5 authentication.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    # data4 is not covered by command.mappings; require its exact single mapping.
    c.require(6 in blocks and len(blocks[6]) >= 7, 'missing data4 block')
    c.require([(key, row) for key, row in blocks.items() if row[0] == 'MAIN_.data4'] ==
              [(6, blocks[6])], 'data4 block identity mismatch')
    c.require((blocks[6][4], blocks[6][5], blocks[6][6]) ==
              (0x20000000004335a0, 11040, 0), 'data4 block mapping mismatch')
    c.require([(key, row) for key, row in subs.items() if row[0] == 6] ==
              [(6, [6, 2, 11040, 0, 262, 0])], 'data4 subblock mapping mismatch')
    maps = [normal.mapping_evidence(blocks, subs, image, m) for m in
            (TEXT_MAPPING, DATA3_MAPPING, DATA4_MAPPING, DATA5_MAPPING)]
    text, data3, data4, data5 = [item[0] for item in maps]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[item[1] for item in maps],
        ranges=[range_evidence(db, text, pc, width) for pc, width, _ in RANGES],
        cells=[cell_evidence(db, data3, 0x8031f004), cell_evidence(db, data4, 0x8043386c)],
        constants=[constant_evidence(db, data5, 0x804392c8)],
        function_coverage=[dict(entry='800ff418', end_exclusive='800ff4d4', selected_width=188,
            represented_instructions=47, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='adjacent named C/index entries, map size and authenticated terminal return', map_size=188)],
        recorded_bases=dict(r2='8043ea20',
            caveat='Previously recorded basis, not freshly authenticated startup or live processor state.'),
        reused_evidence=dict(
            scale=dict(address='804392d0', bits='3f733333', read_here=False,
                source='double-action-envelope-evidence-2026-11-14.md'),
            magnitude=dict(address='8020bb14', width=68,
                sha256='492e3d053ee6336c226ad94d8947492f358b1941ca2292029efea8a6d4d382bb',
                read_here=False, source='terrain-orientation-evidence-2026-11-13.md',
                caveat='Static helper evidence and a separately bounded signed-axis implementation do not '
                       'establish a general exact motion-magnitude implementation.')),
        caveat='Archived ProgramDB static evidence only, not unchanged original-DOL identity, execution, '
            'MATCH, live dispatch, runtime integration or playability. The 47 instructions include every '
            'operand and return. No command prefix/table or callee body is selected here. Phase1 scales '
            'existing motion, increments540 before the reached nonnull config callback800715f8, then '
            'unconditionally calls8020bb14 after that optional callback returns. Only magnitude>3 calls '
            '800b22f4. An unimplemented callback or numerical operation remains an explicit boundary; '
            'no null callback, zero motion, subtraction, collision result or SDK approximation is invented.')


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
