#!/usr/bin/env python3
"""Two fixed projectile spawn/allocation bodies and four variant1 row fields.

Read-only stdlib. Authenticate the complete archived ProgramDB before exactly
six literal selections. Independent C/index/map bounds; no pointer following,
arbitrary address CLI, raw payload output, instruction execution, model import,
projectile lifecycle bodies, adjacent rows, or shared allowlist changes.
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
import read_archived_callback_ammo_evidence as ammo

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
RANGES = (
    (0x8007db5c, 400, 'd759aaf2c9b38c2924ac451e7b29c4d67ef37c2d01492fc5654f04821eeaa0dc'),
    (0x80088aa0, 416, '800882bf558ba7e7f9e955e1884be71e0c9aad8870807bf7dc0876f56baaeab6'),
)
# label, exact cell, width, format, expected semantic values, fixed hash.
# Row1 base802d6d68+1*38=802d6da0. No complete row/table read.
CELLS = (
    ('variant1-family', 0x802d6dce, 2, '>h', (3,), '583c7dfb7b3055d99465544032a571e10a134b1b6f769422bbb71fd7fa167a5d'),
    ('variant1-joint', 0x802d6da2, 1, '>b', (11,), 'e7cf46a078fed4fafd0b5e3aff144802b853f8ae459a4f0c14add3314b7cc3a6'),
    ('variant1-vector', 0x802d6da4, 12, '>fff', (55.0, 0.0, 0.0), 'f2c4bfd9a4763155499b7a93f506ddae33df56d5c4653e547547bdec2987ea19'),
    ('variant1-offset-flag', 0x802d6dcc, 1, '>b', (0,), '6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d'),
)
CALLS = {0x8007db5c: ('80088aa0', '8020b7a8', '8020ba54'),
         0x80088aa0: ('80197bec', '80088d98', '80006d4c')}


def decode_selected(word, pc):
    """Only selected PPC forms; each variable admitted bit has an output operand."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 7:
        return dict(mnemonic='mulli', rD=d, rA=a, immediate=normal.signed(word & 65535, 16))
    if op == 10:
        c.require(d == 0, 'unselected unsigned comparison fields')
        return dict(mnemonic='cmpli', BF=0, L=0, rA=a, immediate=word & 65535)
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 0), (4, 1), (4, 2), (12, 0), (12, 2)),
                  'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op in (38, 40, 46, 47):
        name, reg = {38: ('stb', 'rS'), 40: ('lhz', 'rD'),
                     46: ('lmw', 'rD'), 47: ('stmw', 'rS')}[op]
        return dict(mnemonic=name, **{reg: d}, rA=a, displacement=normal.signed(word & 65535, 16))
    if op == 31 and xo in (23, 87, 151):
        c.require(rc == 0, 'reserved indexed Rc')
        name, reg = {23: ('lwzx', 'rD'), 87: ('lbzx', 'rD'), 151: ('stwx', 'rS')}[xo]
        return dict(mnemonic=name, **{reg: d}, rA=a, rB=b)
    # Existing decoder retains branch, register, signedness, load/store and FP operands.
    return ammo.decode_selected(word, pc)


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
    c.require([item['address'] for item in instructions if item['mnemonic'] == 'blr'] ==
              [f'{address + width - 4:08x}'], 'span return-site mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('bc', 'b')), 'branch outside fixed span')
    calls = tuple(item['target'] for item in instructions if item['mnemonic'] == 'bl')
    c.require(calls == CALLS[address], 'span direct-call mismatch')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def cell_evidence(db, mapping, address):
    c.require(type(address) is int, 'cell integer fields')
    selected = [item for item in CELLS if item[1] == address]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    label, _, width, fmt, expected, digest_expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(start <= address < address + width <= end and struct.calcsize(fmt) == width,
              'cell width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'cell byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == digest_expected, 'cell digest mismatch')
    values = struct.unpack(fmt, raw)
    c.require(values == expected, 'cell value mismatch')
    return dict(label=label, address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, values=list(values), sha256=digest, spans=spans)


def inspect(data, digest):
    # Preserve complete SHA/schema/language/File Bytes/maps/data5 authentication.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    maps = [normal.mapping_evidence(blocks, subs, image, m) for m in (TEXT_MAPPING, DATA3_MAPPING)]
    text, data3 = [item[0] for item in maps]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[item[1] for item in maps],
        ranges=[range_evidence(db, text, pc, width) for pc, width, _ in RANGES],
        cells=[cell_evidence(db, data3, pc) for _, pc, _, _, _, _ in CELLS],
        function_coverage=[dict(entry=f'{pc:08x}', end_exclusive=f'{pc + width:08x}', selected_width=width,
            represented_instructions=width // 4, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='adjacent named C/index entries, map size and authenticated terminal return',
            map_size=width) for pc, width, _ in RANGES],
        row_selection=dict(base='802d6d68', stride=56, variant=1, row='802d6da0',
            fields=[dict(offset=offset, address=f'{0x802d6da0 + offset:08x}', width=width)
                    for offset, width in ((46, 2), (2, 1), (4, 12), (44, 1))]),
        reused_evidence=dict(
            matrix_vector=dict(address='8020b7a8', width=84, read_here=False,
                sha256='0e86b49668bd9172bfd1256aa2842a4326032efab48cb6b8df58523a63992e78',
                source='terrain-orientation-evidence-2026-11-13.md'),
            vector_add=dict(address='8020ba54', width=36, read_here=False,
                sha256='c7b35d4075874e063982faa1d7d086e5d5ec4d70aed2b56c619b5e440e18e1ab',
                source='double-action-envelope-evidence-2026-11-14.md')),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
            'MATCH, live dispatch, runtime integration or playability. Both complete bodies include all '
            '204 instruction operands and returns. The row1 family gate precedes allocation; nonnull '
            'allocation precedes child metadata, genuine joint transformation and saved aim stores. '
            'Allocator helpers197bec/88d98/06d4c, pool/table contents and lifecycle callbacks remain '
            'explicit boundaries here. No other projectile rows, lifecycle bodies or assets were read.')


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
