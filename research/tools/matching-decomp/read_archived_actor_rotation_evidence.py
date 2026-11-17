#!/usr/bin/env python3
"""Fixed rotation damping inputs from the two existing authenticated GBF files.

Read-only stdlib. Reuse two already-authenticated normal-reader code spans;
select four literal constants and one independent eight-byte descriptor window.
No pointer following, arbitrary-address CLI, raw binary output or execution.
The descriptor window is not a claim about the containing object's extent.
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
DATA3_MAPPING = normal.DATA3_MAPPING
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)
# Independent literals, already authenticated by the unchanged normal reader.
RANGES = ((0x80059f5c, 488), (0x8006f60c, 252))
CONSTANTS = (
    (0x804373c0, 4, '3f666666'),
    (0x804373c4, 4, '3dccccd0'),
    (0x804373c8, 4, '3f800000'),
    (0x804373d0, 8, '4330000080000000'),
)
# Fixed address is independently selected; the constructor value never chooses a read.
DESCRIPTOR_WINDOW = (0x8033b028, 8)
DESCRIPTOR_VALUES = (12, 2, 7, 11, -1, -1, -1, -1)
DESCRIPTOR_SHA = '65fc8a2905ebfd7f8fbe4a7f74fed48be279cecf265ffba74f2414edd840e538'
RECORDED_R2 = 0x8043ea20


def range_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'range integer fields')
    c.require(sum(item == (address, width) for item in RANGES) == 1, 'range not allowlisted')
    # Preserves full span digest checks and strict decoding of every instruction.
    return normal.range_evidence(db, mapping, address, width)


def constant_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'constant integer fields')
    selected = [item for item in CONSTANTS if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(width in (4, 8) and address % width == 0 and
              start <= address < address + width <= end, 'constant alignment/width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == selected[0][2], 'constant bits mismatch')
    return dict(address=f'{address:08x}', width=width, type='f32' if width == 4 else 'f64',
                bits=raw.hex(), value=struct.unpack('>f' if width == 4 else '>d', raw)[0],
                sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def descriptor_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'descriptor integer fields')
    c.require((address, width) == DESCRIPTOR_WINDOW, 'descriptor window not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(start <= address < address + width <= end, 'descriptor bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'descriptor byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == DESCRIPTOR_SHA, 'descriptor digest mismatch')
    values = struct.unpack('>8b', raw)
    c.require(values == DESCRIPTOR_VALUES, 'descriptor signed values mismatch')
    return dict(address=f'{address:08x}', width=width, type='signed8',
                values=list(values), sha256=digest, spans=spans,
                constructor_source='8006f60c', descriptor_base='8033af78',
                descriptor_offset=0xb0, source_loop_limit=8, first_sentinel_position=4,
                traversed_indices=list(values[:4]), extent_proven=False,
                caveat='Fixed eight-byte window only; first -1 stops source list reads. '
                       'No live descriptor ownership or containing-object extent is established.')


def inspect(data, digest):
    # Authenticate actual whole-file SHA, exact schemas/metadata, empty File
    # Bytes, address maps, complete data5 hash and controls before any new read.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, text_fact = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data3, data3_fact = normal.mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    data5, data5_fact = normal.mapping_evidence(blocks, subs, image, DATA5_MAPPING)
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                mappings=[text_fact, data3_fact, data5_fact],
                ranges=[range_evidence(db, text, address, width) for address, width in RANGES],
                constants=[constant_evidence(db, data5, address, width)
                           for address, width, _ in CONSTANTS],
                descriptor_window=descriptor_evidence(db, data3, *DESCRIPTOR_WINDOW),
                r2_basis=dict(recorded_value=f'{RECORDED_R2:08x}',
                              displacements={f'{address:08x}': address - RECORDED_R2
                                             for address, _, _ in CONSTANTS},
                              source='docs/static-recompilation-spike.md:178',
                              caveat='Previously recorded SDA2 basis, not a freshly authenticated '
                                     'startup instruction span or live r2 capture.'),
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                                        selected_width=width, represented_instructions=width // 4,
                                        unrepresented_instructions=0, unrepresented_ranges=[])
                                   for address, width in RANGES],
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, '
                       'live dispatch, runtime state or retail parity. The unchanged normal '
                       'reader authenticates and strictly decodes all 185 selected instructions. '
                       'Four constants and one independent descriptor window are selected. '
                       'The constructor does not prove a fully initialized live actor. '
                       'No arbitrary descriptor, list extent, FPSCR state or other data is inferred. '
                       'Single fused fmadds must not become separate multiply/add operations. '
                       'Signed list entries, ordered repeated indices, sentinel exit to trailing '
                       '18da/18dc/18de stores, and conversion order remain significant.')


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
