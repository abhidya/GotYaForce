#!/usr/bin/env python3
"""Exactly full36a8[0], four bytes; existing dispatch and return-stub evidence reused.

Read-only authenticated local snapshots. No target following, arbitrary addresses,
whole tables, original instruction output, runtime state or default handlers.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_double_action_evidence as prior
c, command, normal = prior.c, prior.command, prior.normal
DATA3_MAPPING = prior.DATA3_MAPPING
CELL = ('full0', 0x802d36a8, 0x8005f238,
        '8868a8515e4b649802f66057c61600c1899cea349f7d393786d886caaff607a4')
REUSED_EVIDENCE = (
    dict(address='80055568', width=292, source='read_archived_actor_mode1_evidence.py',
         sha256='4ef4d2db70068dec76e280773b3d58c546452599966914bffd4f8cbaf56472c7', read_here=False),
    dict(address='8005f238', width=4, source='read_archived_double_action_evidence.py',
         sha256='f332ea5b5437103cbb6f1508679da89eec9288ad775c96c439a17fccabe3de8e', read_here=False),
)


def cell_evidence(db, mapping, address):
    c.require(type(address) is int and address == CELL[1], 'cell not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    label, _, target, expected = CELL
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == 0 and start <= address < address + 4 <= end, 'cell bounds')
    raw, spans = db.chain(root, address - start, 4, length)
    c.require(len(raw) == 4, 'cell byte width')
    c.require(hashlib.sha256(raw).hexdigest() == expected, 'cell digest mismatch')
    c.require(c.integer(raw, 0, 'I') == target, 'cell target mismatch')
    return dict(label=label, address=f'{address:08x}', width=4, target=f'{target:08x}',
                sha256=expected, spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    mapping, fact = normal.mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    cell = cell_evidence(db, mapping, CELL[1])
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[fact], cells=[cell],
                selection_basis=dict(reads=1, bytes=4, selected_data_cells=1,
                    pointer_following=False, helpers_read=False, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live selector value, hydration or full frame. Only full index0 is selected; '
                    'existing55568 table-base derivation and5f238 bare-return proof are reused. '
                    'No other table cells, target bodies, current actor state or defaults are read.')


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
