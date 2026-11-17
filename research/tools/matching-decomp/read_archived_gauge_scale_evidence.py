#!/usr/bin/env python3
"""Fixed gauge-reset and scale/tier evidence from authenticated local GBF snapshots.

Read-only stdlib. Complete 8003d3e8/8003d444/8005bab8 spans and four named constants;
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
    (0x8003d3e8, 0x5c, '029c02b480e2afb11381d7ff2f595f03c46dabff6c4a410a249d2b4eb53ef1af'),
    (0x8003d444, 0x5c, '38e165f8b714575694c3f29ce4efea45dd1b1f16c3b10e3900e39fe2fb2b8902'),
    (0x8005bab8, 0x108, 'd857580767ae7b19893084b31d12b3a0c9a606a7891ae5e4f3cbaa7672c0ee46'),
)
TARGETS = (
    (0x80436f88, 8, '4330000080000000'),
    (0x80436f7c, 4, '3f000000'),
    (0x80436f78, 4, '3f800000'),
    (0x80437420, 4, '3d4ccccd'),
)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)


def decode_selected(word, pc):
    """Decode only observed scalar forms; preserve signedness and operand order.

    Shared authentication, mappings and field decoders are unchanged. Every
    instruction in each digest-pinned span must decode, or the read fails.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 31 and xo in (339, 467):
        c.require(d == 0 and ((b << 5) | a) == 8 and rc == 0, 'unsupported link-register form')
    if op == 31 and xo == 104:
        c.require(b == 0 and rc == 0, 'reserved/unsupported neg fields')
        return dict(mnemonic='neg', rD=d, rA=a, Rc=rc)
    if op == 63 and xo == 0:
        c.require(rc == 0 and d & 3 == 0, 'reserved fcmpu fields')
        return dict(mnemonic='fcmpu', crD=d >> 2, fA=a, fB=b)
    if not (word == 0x4e800020 or
            op in (11, 14, 15, 16, 18, 27, 32, 34, 36, 37, 38, 42, 44, 48, 50, 52, 54) or
            (op == 19 and xo == 449) or
            (op == 31 and xo in (266, 339, 444, 467, 922, 954)) or
            (op == 59 and (xo & 31) in (20, 21, 25)) or
            (op == 63 and xo in (15, 32))):
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
    c.require(width in (4, 8) and address % width == 0 and start <= address < address + width <= end,
              'constant alignment/width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == selected[0][2], 'constant bits mismatch')
    return dict(address=f'{address:08x}', width=width, type='f32' if width == 4 else 'f64',
                bits=raw.hex(), value=struct.unpack('>f' if width == 4 else '>d', raw)[0],
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
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 23+23 gauge-reset and 66 scale/tier instructions are represented. '
                       'Constants authenticate 0.5f, 1f, the scale step and signed conversion bias. '
                       'Live FPSCR state, retail actor values and runtime ownership are not established.')


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
