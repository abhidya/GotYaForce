#!/usr/bin/env python3
"""Fixed actor-tier lifecycle evidence from authenticated local GBF snapshots.

Read-only stdlib. Complete 8006817c/8006826c spans, two fixed pointer cells,
and six independently fixed rows. No arbitrary addresses, pointer following,
raw executable output, instruction execution, or shared allowlist expansion.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_actor_status_evidence as status
import read_archived_command_evidence as command
import read_archived_constants as c
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH


RANGES = (
    (0x8006817c, 0x68, 'cc7a1791c3441a7767e2999ffe19791d625384942e34ec13b0ff5d0639063f2d'),
    (0x8006826c, 0x8c, 'b5984640399d2952aedfaa554a6459035788415792189757db695fe6c0b4a7bf'),
)
# selector, pointer-cell address, expected target. Unexpected values are refused,
# never followed. These two cells do not prove the pointer table's extent.
POINTER_CELLS = (
    (0, 0x804339e0, 0x802dd5a0),
    (1, 0x804339e4, 0x802dd720),
)
# selector, signed tier, independently fixed row address, exact float32 bits.
# No allocation size, family selector, or live descriptor provenance is inferred.
ROWS = (
    (0, 15, 0x802dd654, ('3f4f5c29', '3f800000', '3f4f5c29')),
    (0, 16, 0x802dd660, ('3f800000', '3f800000', '3f800000')),
    (0, 17, 0x802dd66c, ('3fb33333', '3f7ae148', '3fb33333')),
    (1, 15, 0x802dd7d4, ('3f4f5c29', '3f800000', '3f4f5c29')),
    (1, 16, 0x802dd7e0, ('3f800000', '3f800000', '3f800000')),
    (1, 17, 0x802dd7ec, ('3f99999a', '3f7ae148', '3f99999a')),
)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 0xf42c0, 199)
DATA4_MAPPING = (0x804335a0, 0x804360c0, 6, 'MAIN_.data4', 6, 11040, 262)


def decode_selected(word, pc):
    """Decode only observed integer, branch and float-copy fields, not execution."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 19 and xo == 16 and word != 0x4e800020:
        c.require(b == 0 and rc == 0, 'unsupported conditional LR fields')
        return dict(mnemonic='bclr', BO=d, BI=a, BH=0, LK=0)
    if op == 31 and xo == 23:
        c.require(rc == 0, 'reserved indexed memory bit')
        return dict(mnemonic='lwzx', rD=d, rA=a, rB=b)
    if op == 31 and xo in (339, 467):
        c.require(d == 0 and ((b << 5) | a) == 8 and rc == 0,
                  'unsupported link-register form')
    if not (word == 0x4e800020 or
            op in (7, 10, 11, 14, 15, 16, 18, 21, 32, 34, 36, 37, 38, 48, 52) or
            (op == 31 and xo in (0, 266, 339, 467, 954))):
        return None
    return status.decode_selected(word, pc)


def mappings(blocks, subs, image):
    # Includes every-block overlap checks and exact text1/data3/data5 mappings.
    command.mappings(blocks, subs, image)
    selected = [(key, row) for key, row in blocks.items() if row[0] == 'MAIN_.data4']
    c.require(len(selected) == 1 and selected[0][0] == 6 and
              selected[0][1][4:] == [0x20000000004335a0, 11040, 0], 'data4 mapping mismatch')
    c.require([(key, row) for key, row in subs.items() if row[0] == 6] ==
              [(6, [6, 2, 11040, 0, 262, 0])], 'data4 subblock mapping mismatch')


def range_evidence(db, root, address, width):
    c.require(all(type(value) is int for value in (root, address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    c.require(root == 21 and address % 4 == width % 4 == 0 and
              TEXT_START <= address < address + width <= TEXT_START + TEXT_LENGTH,
              'range root/alignment/bounds')
    raw, spans = db.chain(root, address - TEXT_START, width, TEXT_LENGTH)
    c.require(len(raw) == width, 'range byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'range digest mismatch')
    instructions = []
    for offset in range(0, width, 4):
        decoded = decode_selected(c.integer(raw, offset, 'I'), address + offset)
        c.require(decoded is not None, 'unselected instruction in fixed span')
        instructions.append(dict(address=f'{address + offset:08x}', **decoded))
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, spans=spans, instructions=instructions)


def exact_mapping(mapping, expected):
    return (type(mapping) is tuple and mapping == expected and
            tuple(type(x) for x in mapping) == tuple(type(x) for x in expected))


def pointer_cell_evidence(db, mapping, selector):
    c.require(type(selector) is int, 'pointer selector integer')
    selected = [item for item in POINTER_CELLS if item[0] == selector]
    c.require(len(selected) == 1, 'pointer cell not allowlisted')
    c.require(exact_mapping(mapping, DATA4_MAPPING), 'data4 mapping mismatch')
    _, address, target = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(selector in (0, 1) and address == 0x804339e0 + selector * 4 and
              address % 4 == 0 and start <= address < address + 4 <= end,
              'pointer cell alignment/index/bounds')
    raw, spans = db.chain(root, address - start, 4, length)
    c.require(len(raw) == 4, 'pointer cell byte width')
    c.require(c.integer(raw, 0, 'I') == target, 'pointer cell value mismatch')
    return dict(selector=selector, address=f'{address:08x}', width=4, type='u32-pointer',
                target=f'{target:08x}', sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def row_evidence(db, mapping, selector, tier):
    c.require(all(type(value) is int for value in (selector, tier)), 'row integer fields')
    selected = [item for item in ROWS if item[:2] == (selector, tier)]
    c.require(len(selected) == 1, 'row not allowlisted')
    c.require(exact_mapping(mapping, DATA3_MAPPING), 'data3 mapping mismatch')
    pointers = [item for item in POINTER_CELLS if item[0] == selector]
    c.require(len(pointers) == 1, 'row pointer identity not allowlisted')
    _, _, address, bits = selected[0]
    base = pointers[0][2]  # Expected metadata only; no dynamic pointer following.
    start, end, _, _, _, length, root = mapping
    c.require(selector in (0, 1) and tier in (15, 16, 17) and
              address == base + tier * 12 and address % 4 == 0 and
              start <= address < address + 12 <= end, 'row alignment/index/bounds')
    c.require(type(bits) is tuple and len(bits) == 3 and
              all(type(x) is str and len(x) == 8 for x in bits), 'row bits schema')
    raw, spans = db.chain(root, address - start, 12, length)
    c.require(len(raw) == 12, 'row byte width')
    c.require(raw.hex() == ''.join(bits), 'row bits mismatch')
    cells = [dict(offset=offset, address=f'{address + offset:08x}', type='f32', bits=value,
                  value=struct.unpack('>f', raw[offset:offset + 4])[0])
             for offset, value in zip((0, 4, 8), bits)]
    return dict(selector=selector, tier=tier, base=f'{base:08x}', address=f'{address:08x}',
                width=12, sha256=hashlib.sha256(raw).hexdigest(), spans=spans, cells=cells)


def inspect(data, digest):
    # Actual full-snapshot digest, exact schemas, metadata, empty File Bytes,
    # complete data5 hash and controls are checked before all new selections.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    mappings(blocks, subs, int(auth['image_offset'], 16))
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=21,
                r13_basis=dict(recorded_value='8043b5a0',
                               displacements={'80433934': -31852},
                               caveat='Previously recorded SDA basis; not a live capture. '
                                      'This global pointer and its pointee are not read.'),
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                pointer_cells=[pointer_cell_evidence(db, DATA4_MAPPING, selector)
                               for selector, _, _ in POINTER_CELLS],
                rows=[row_evidence(db, DATA3_MAPPING, selector, tier)
                      for selector, tier, _, _ in ROWS],
                data_mappings=[dict(block_name=m[3], block_key=m[2], subblock_key=m[4],
                                    block_start=f'{m[0]:08x}', block_length=m[5], chain_root=m[6],
                                    subblock_type=2, starting_offset=0, source_offset=0)
                               for m in (DATA3_MAPPING, DATA4_MAPPING)],
                table_scope=dict(authenticated_selectors=[0, 1], authenticated_tiers=[15, 16, 17],
                                 extent_proven=False, descriptor_provenance_proven=False,
                                 runtime_pointer_ownership_proven=False),
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address+width:08x}',
                                        map_width=width, represented_instructions=width//4,
                                        unrepresented_instructions=0, unrepresented_ranges=[])
                                   for address, width, _ in RANGES],
                caveat='Archived ProgramDB evidence only, not original-DOL identity or live parity. '
                       'All 26 delta and 35 refresh instructions are represented. Only two fixed '
                       'pointer cells and six independently fixed rows are selected; unexpected '
                       'pointer values are refused, never followed. No table extent, real family '
                       'selector, descriptor default, actor ownership, live FPSCR or NaN behavior '
                       'is proved. Row transfers are lfs/stfs, not integer word copies. '
                       'Constructor 80056180 is C-level ownership context only, not selected code.')


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
