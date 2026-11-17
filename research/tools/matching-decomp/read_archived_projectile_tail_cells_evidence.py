#!/usr/bin/env python3
"""Five fixed captured projectile-row1 cells, 18 bytes; existing Scale reused.

Authenticated local snapshots only. No whole-row/table, arbitrary selection,
pointer following, helper body reads or original instruction/byte output.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys
import read_archived_projectile_spawn_evidence as prior
c, command, normal = prior.c, prior.command, prior.normal
DATA3_MAPPING = prior.DATA3_MAPPING
CELLS = (('descriptor-selector00', 2150460832, 2, '>h', 14, '9f4917386c45e2c0da0d9b475f1a19cf2db1e929195c6a9f4966ca0d2105b196'), ('speed10', 2150460848, 4, '>f', 40.0, 'e8ed90c1eadc4cdc681ef61f06f767afc7043be08ecd94c5c2990ed7e560c8f8'), ('lifetime-word14', 2150460852, 4, '>I', 4, '1bc5d0e3df0ea12c4d0078668d14924f95106bbe173e196de50fe13a900b0937'), ('motion28', 2150460872, 4, '>f', 0.30000001192092896, '602c0ad4e31620e547048b7233e0666cc3ba1151637458f13c344d0aca90e0f5'), ('scale30', 2150460880, 4, '>f', 2.0, 'c31425b44a7ed682a3356bf6820141e1584a15c43b6d6793f552e5d4621586f7'))
REUSED_EVIDENCE = (
    dict(address='8007dd84', width=1148, source='read_archived_projectile_initialization_evidence.py',
         sha256='e8732a065c806b75274606baf717082e907c68db87400e1a4299b77820148ec2', read_here=False),
    dict(address='8020ba9c', width=28, source='read_archived_actor_mode1_evidence.py',
         sha256='e0fbf8bbb6f184d7b21d322b68975adca6dc652510963c83c95b9ceb63e0671d', read_here=False),
)


def cell_evidence(db, mapping, address, width):
    c.require(type(address) is type(width) is int, 'cell integer fields')
    selected = [row for row in CELLS if row[1:3] == (address, width)]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    label, _, _, fmt, value, expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(address % width == 0 and start <= address < address + width <= end, 'cell bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'cell byte width')
    c.require(hashlib.sha256(raw).hexdigest() == expected, 'cell digest mismatch')
    c.require(struct.unpack(fmt, raw)[0] == value, 'cell semantic value mismatch')
    return dict(label=label, address=f'{address:08x}', offset=address-0x802d6da0,
                width=width, format=fmt, value=value, sha256=expected, spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    mapping, fact = normal.mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    cells = [cell_evidence(db, mapping, row[1], row[2]) for row in CELLS]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[fact], cells=cells,
                selection_basis=dict(reads=5, bytes=18, selected_data_cells=5,
                    pointer_following=False, helpers_read=False, whole_row_read=False,
                    original_execution=False, operand_listing_output=False),
                row_selection=dict(base='802d6d68', stride=56, variant=1, row='802d6da0'),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived static row1 evidence, not live memory ownership, original-DOL identity, '
                    'execution or full frame. Only five requested cells selected; descriptor helper bodies '
                    'and remaining row fields are not selected. Source reloads speed after Scale.')


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
