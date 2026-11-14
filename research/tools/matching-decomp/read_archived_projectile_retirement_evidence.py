#!/usr/bin/env python3
"""Fixed state2 dispatch cell and independently selected retirement handler.

Read-only stdlib. Full snapshot/schema/maps authentication precedes exactly
2 selections /64 bytes. No pointer following, neighboring state cell/handler,
helper reread, raw output, arbitrary-address CLI, original execution, runtime
or estimator import, external fetch or shared authenticator changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_actor_normal_evidence as normal

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
TABLE_ROOT = 0x802d6f98
SIGNED_STATE = 2
ENTRY_WIDTH = 4
# Independent C/index bounds, not a named map extent or returned-pointer read.
RANGES = (
    (0x8007e63c, 0x3c, '955fe1fa85b6c60a40c7e078f9787575519bb7a4455394bc523ae78ec5c932ad'),
)
# label, literal cell, width, independently selected candidate, payload SHA.
CELLS = (
    ('retirement-state2', 0x802d6fa0, 4, 0x8007e63c,
     '7cc80c32e114c358aba4f4c0ff53230ae0c47acdf8bd9051d0fa1cd6cbc3b830'),
)
REUSED_EVIDENCE = (
    dict(address='8007dcec', width=152,
         sha256='ee9edd0cdc0d53686a872a42378eb638ee4b44fdf26e25f7259f6198f71b815a',
         purpose='signed state18 dispatch through table802d6f98; guard can select state2',
         read_here=False, source='projectile-callback-evidence-2026-11-14.md'),
    dict(address='8008aff0', width=32,
         sha256='8ea8cac06c446278fad05cfae1dbe3ee6b3a321f4bfd1168269ce88283bef951',
         purpose='type0/3 stores1d8=1; all paths preserve incoming r3',
         read_here=False, source='projectile-callback-evidence-2026-11-14.md'),
)


def decode_selected(word, pc):
    """Only selected forms; all admitted instruction bits fixed or exposed."""
    decoded = normal.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'stw', 'addi', 'or', 'stb', 'bl', 'lwz', 'mtlr', 'blr'}
    if not decoded or decoded['mnemonic'] not in allowed:
        return None
    if decoded['mnemonic'] == 'bl':
        decoded = dict(decoded, LK=1)
    return decoded


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
    c.require([item for item in instructions if item['mnemonic'] == 'blr'] ==
              [dict(address='8007e674', mnemonic='blr', BO=20, BI=0, BH=0, LK=0)],
              'span terminal return mismatch')
    c.require([item for item in instructions if item['mnemonic'] == 'bl'] ==
              [dict(address='8007e658', mnemonic='bl', target='8008aff0', AA=0, LK=1)],
              'span direct-call mismatch')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def cell_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'cell integer fields')
    selected = [item for item in CELLS if item[1:3] == (address, width)]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    label, _, _, target, expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(width == 4 and address % 4 == 0 and start <= address < address + width <= end,
              'cell alignment/width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'cell byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected, 'cell digest mismatch')
    actual = c.integer(raw, 0, 'I')
    c.require(actual == target, 'cell target mismatch')
    return dict(label=label, address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, target=f'{actual:08x}', sha256=digest, spans=spans)


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
    c.require(TABLE_ROOT + SIGNED_STATE * ENTRY_WIDTH == 0x802d6fa0, 'fixed state2 derivation')
    # These literal selections are independent. Neither read consumes the other's output.
    cells = [cell_evidence(db, data3, pc, width) for _, pc, width, _, _ in CELLS]
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    c.require(len(cells) == len(ranges) == 1 and cells[0]['target'] == ranges[0]['address'],
              'cell target differs from independently selected candidate')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[item[1] for item in maps],
        cells=cells, ranges=ranges,
        function_coverage=[dict(entry='8007e63c', end_exclusive='8007e678', selected_width=60,
            represented_instructions=15, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='independent adjacent C/index entries and authenticated terminal return; '
                'no named candidate map extent', map_size=None)],
        selection_basis=dict(table='802d6f98', index_field='signed child+0x18', selected_state=2,
            entry_width=4, cell='802d6fa0', independent_candidate='8007e63c',
            candidate_end_exclusive='8007e678', target_equals_independent_candidate=True,
            reads=2, bytes=64, pointer_following=False, helper_read_here=False,
            other_state_cells_read_here=False, state3_handler_read_here=False),
        reused_evidence=list(REUSED_EVIDENCE),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All15 instructions are represented. '
            'Store child18=3, call8008aff0(child), then store child82=0 through saved child identity. '
            'The epilogue preserves r3; reused helper evidence returns the original child pointer. '
            'A guard-selected state2 can call the helper a second time in one root callback. '
            'State3 is stored, not dispatched recursively here. No free/unlink or live scheduling '
            'claim follows. State3 cell/handler and all neighboring selections remain unselected.')


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
