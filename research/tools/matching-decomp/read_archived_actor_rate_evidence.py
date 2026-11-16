#!/usr/bin/env python3
"""Fixed actor-rate lifecycle evidence from authenticated local GBF snapshots.

Read-only stdlib. Complete 8005a378 span, three constants and four selected table cells;
derived operand fields only. No arbitrary-address CLI, raw executable output,
vendor-code execution, or changes to the shared archive reader's allowlist.
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
    (0x8005a378, 0x208, 'b6a3dfe9d8bf1b34fb4d470444385f1bbdafe4ba0596786d67699ca9e92ecd2f'),
)
TARGETS = (
    (0x804373c8, 4, '3f800000'),
    (0x804373d8, 4, '3fc00000'),
    (0x804373dc, 4, '3cf5c28f'),
)
# Explicit positive indices, NOT a declaration of either table's extent.
# No index-zero cell is required: the source skips its table read for zero.
TABLE_CELLS = (
    (0x802dd57c, 1, 0x802dd580, '3f333333'),
    (0x802dd57c, 2, 0x802dd584, '3ecccccd'),
    (0x802dd58c, 1, 0x802dd590, '3fa00000'),
    (0x802dd58c, 2, 0x802dd594, '3fc00000'),
)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 0xf42c0, 199)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)


def decode_selected(word, pc):
    """Only observed scalar forms; preserve every operand and instruction.

    This decodes fields, never executes instructions. Shared field decoding,
    archive authentication, mappings and allowlists remain unchanged.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, xo = word >> 26, (word >> 1) & 1023
    if not (word == 0x4e800020 or
            op in (10, 11, 14, 15, 16, 21, 32, 34, 38, 42, 44, 48, 52) or
            (op == 31 and xo in (266, 922, 954)) or
            (op == 59 and (xo & 31) == 25)):
        return None
    return status.decode_selected(word, pc)


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


def constant_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'constant integer fields')
    selected = [item for item in TARGETS if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'constant not allowlisted')
    c.require(mapping == DATA5_MAPPING, 'data5 mapping mismatch')
    start, end, _, _, _, length, root = mapping
    c.require(width == 4 and address % width == 0 and start <= address < address + width <= end,
              'constant alignment/width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == selected[0][2], 'constant bits mismatch')
    return dict(address=f'{address:08x}', width=width, type='f32',
                bits=raw.hex(), value=struct.unpack('>f', raw)[0],
                sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def table_cell_evidence(db, mapping, base, index):
    c.require(all(type(value) is int for value in (base, index)), 'table integer fields')
    selected = [item for item in TABLE_CELLS if item[:2] == (base, index)]
    c.require(len(selected) == 1, 'table cell not allowlisted')
    c.require(mapping == DATA3_MAPPING, 'data3 mapping mismatch')
    _, _, address, bits = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(index in (1, 2) and address == base + index * 4 and address % 4 == 0 and
              start <= address < address + 4 <= end, 'table cell alignment/index/bounds')
    raw, spans = db.chain(root, address - start, 4, length)
    c.require(len(raw) == 4, 'table cell byte width')
    c.require(raw.hex() == bits, 'table cell bits mismatch')
    return dict(base=f'{base:08x}', index=index, address=f'{address:08x}', width=4,
                type='f32', bits=bits, value=struct.unpack('>f', raw)[0],
                sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def inspect(data, digest):
    # Whole-snapshot authentication, exact schemas, executable metadata, empty
    # File Bytes, address maps, full data5 hash and controls precede new reads.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    mapping = c.data5_mapping(blocks, subs, image)
    c.require(mapping == DATA5_MAPPING, 'data5 mapping mismatch')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=21,
                r2_basis=dict(recorded_value='8043ea20',
                              displacements={f'{a:08x}': a - 0x8043ea20 for a, _, _ in TARGETS},
                              caveat='Previously recorded SDA2 basis; not a live r2 capture.'),
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                constants=[constant_evidence(db, mapping, address, width) for address, width, _ in TARGETS],
                table_cells=[table_cell_evidence(db, DATA3_MAPPING, base, index)
                             for base, index, _, _ in TABLE_CELLS],
                table_mapping=dict(block_name='MAIN_.data3', block_key=5, subblock_key=5,
                                   block_start='802bae60', block_length=0xf42c0,
                                   subblock_type=2, starting_offset=0, source_offset=0, chain_root=199),
                table_scope=dict(authenticated_indices=[1, 2], zero_skips_read=True,
                                 unsupported_signed_indices=[[-128, -1], [3, 127]],
                                 extent_proven=False),
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address+width:08x}',
                                        selected_width=width, represented_instructions=width//4,
                                        unrepresented_instructions=0, unrepresented_ranges=[])
                                   for address, width, _ in RANGES],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 130 actor-rate instructions are represented; no calls or stack frame. '
                       'Extent uses C next entry and final decoded blr, not a symbol-map size. '
                       'Only three fixed constants and index 1/2 cells of each table are selected. '
                       'All other nonzero signed table indices, live actor values, pointer ownership '
                       'and live FPSCR state are unsupported. The selected table cells do not prove '
                       'table extents or runtime index provenance.')


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
