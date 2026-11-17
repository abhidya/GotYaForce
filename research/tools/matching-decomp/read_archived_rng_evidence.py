#!/usr/bin/env python3
"""Fixed RNG evidence: complete 800055fc body, 52 bytes / 13 instructions.

Read-only stdlib. Unchanged archive/schema/mapping authentication precedes one
fixed selection. No state bytes, pointer following, arbitrary-address CLI, raw
payload output, original execution, runtime imports or shared reader changes.
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
RANGES = ((0x800055fc, 52, '74fb9a01b91b2d60cd400a8a96d2781782ea688ddd992f4e5eb472d4b9426438'),)


def expected_flow():
    return [dict(address='8000562c', mnemonic='blr', BO=20, BI=0, BH=0, LK=0)]


def decode_selected(word, pc):
    """Every admitted bit represented or fixed; only this body's seven forms."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 31 and xo == 824:
        return dict(mnemonic='srawi', rS=d, rA=a, SH=b, Rc=rc)
    if op == 19:
        c.require(word == 0x4e800020, 'unselected branch-register form')
        return dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0)
    decoded = normal.decode_selected(word, pc)
    if not decoded or decoded['mnemonic'] not in {'lbz', 'stb', 'rlwinm', 'add', 'mulli'}:
        return None
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
    c.require([item for item in instructions if item['mnemonic'] in
               ('bc', 'b', 'bl', 'blr', 'bclr', 'bctrl')] == expected_flow(),
              'complete control-flow mismatch')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data); tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    mapping, mapping_facts = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    ranges = [range_evidence(db, mapping, pc, width) for pc, width, _ in RANGES]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping_facts], ranges=ranges,
        function_coverage=[dict(entry='800055fc', end_exclusive='80005630', selected_width=52,
            represented_instructions=13, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='independent C/index identity and exact named map size', map_size=52)],
        selection_basis=dict(reads=1, bytes=52, selected_data_cells=0, pointer_following=False,
            global_payloads_read=False, callee_bodies_read=False, original_execution=False,
            globals_runtime_values_established=False, initial_rng_bytes_read=False),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All 13 selected instructions represented. '
            'Two unsigned byte loads and two byte stores are proven in source order, but initial RNG '
            'state bytes and runtime r13 are not read or established. Existing authentication reads '
            'are unchanged; the only added payload selection is the 52-byte function body.')


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


if __name__ == '__main__': sys.exit(main())
