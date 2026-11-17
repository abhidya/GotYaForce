#!/usr/bin/env python3
"""Fixed actor-ceiling lifecycle evidence from authenticated local GBF snapshots.

Read-only stdlib. Complete 80068030 and 8008b290 spans, one float32 constant;
derived operands only. No arbitrary-address CLI, raw executable output,
instruction execution, pointer following, or shared-reader allowlist changes.
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
    (0x80068030, 0xa4, '62727691b8e6edb70b8260d660b2d3587900c5309c58a924ab411265b1b797e6'),
    (0x8008b290, 0xc, 'bed0f0166ee2d2521bf4778199e5f52e29e6c02e88cb20f8e9ad9c4faed7c25e'),
)
TARGETS = (
    (0x804375d0, 4, '00000000'),
)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)


def decode_selected(word, pc):
    """Only observed scalar forms; preserve every operand and instruction.

    Shared decoding and archive authentication stay unchanged. This decodes
    instruction fields, never executes instructions or reads pointer targets.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 31 and xo in (339, 467):
        c.require(d == 0 and ((b << 5) | a) == 8 and rc == 0,
                  'unsupported link-register form')
    if not (word == 0x4e800020 or
            op in (11, 14, 16, 18, 32, 34, 36, 37, 48, 52) or
            (op == 31 and xo in (339, 444, 467, 954)) or
            (op == 59 and (xo & 31) in (20, 21)) or
            (op == 63 and xo == 32)):
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
                              displacements={'804375d0': -29776},
                              caveat='Previously recorded SDA2 basis; not a live r2 capture.'),
                r13_basis=dict(recorded_value='8043b5a0',
                               displacements={'80433934': -31852, '8043625c': -21316},
                               caveat='Previously recorded SDA basis; not a live r13 capture. '
                                      'Pointer globals and pointees are not read.'),
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                constants=[constant_evidence(db, mapping, address, width) for address, width, _ in TARGETS],
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address+width:08x}',
                                        map_width=width, represented_instructions=width//4,
                                        unrepresented_instructions=0, unrepresented_ranges=[])
                                   for address, width, _ in RANGES],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 41 ceiling and 3 leaf instructions are represented. Both extents agree '
                       'with symbol-map sizes, C next entries and final decoded blr instructions. '
                       'The leaf returns an unsigned byte; only actor+1db is sign-extended. '
                       'Constant 804375d0 is positive zero. Global/pointee values, actor ownership, '
                       'live FPSCR state and floating exception or NaN behavior are not established. '
                       'The existing tick-prefix reader owns caller 80059068..80059138 evidence; '
                       'this reader neither expands nor re-reads that span.')


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
