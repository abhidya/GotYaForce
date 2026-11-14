#!/usr/bin/env python3
"""Fixed stage-bounds function evidence from authenticated local GBF snapshots.

Read-only stdlib. Complete 80059e58; derived operands only. No raw ranges,
arbitrary-address CLI, execution, or shared-reader allowlist changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_actor_status_evidence as status
import read_archived_command_evidence as command
import read_archived_constants as c
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH


RANGES = ((0x80059e58, 260, '551ac855e1a74b2c56801713d0cf7c3ddf577c11214046365dec304c64206f77'),)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)


def decode_selected(word, pc):
    """Decode only forms present in the fixed function; preserve source operands."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a = word >> 26, (word >> 21) & 31, (word >> 16) & 31
    xo = (word >> 1) & 1023
    if op in (24, 29):
        return dict(mnemonic='ori' if op == 24 else 'andis.', rS=d, rA=a,
                    immediate=word & 65535)
    if not (word == 0x4e800020 or
            op in (11, 14, 16, 18, 21, 32, 34, 36, 37, 38, 42, 44, 48) or
            (op == 31 and xo in (339, 444, 467, 954)) or
            (op == 63 and xo == 32)):
        return None
    if op == 31 and xo in (339, 467):
        b = (word >> 11) & 31
        c.require(((b << 5) | a) == 8 and d == 0, 'unsupported SPR form')
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


def inspect(data, digest):
    # Full snapshot authentication, schemas, executable metadata, empty File
    # Bytes, maps, full data5 hash and existing controls all precede fixed reads.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    c.require(c.data5_mapping(blocks, subs, image) == DATA5_MAPPING, 'data5 mapping mismatch')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=21,
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                constants=[],
                function_coverage=[dict(entry='80059e58', end_exclusive='80059f5c',
                                        selected_width=260, represented_instructions=65,
                                        unrepresented_instructions=0, unrepresented_ranges=[])],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'Extent uses the C export next entry and authenticated epilogue, not a symbol-map entry. '
                       'All 65 selected instructions are represented. No scalar float constants are loaded; '
                       'stage bounds and stage pointer are runtime inputs, not authenticated values. '
                       'Live FPSCR state, retail actor values and runtime ownership are not established. '
                       'Cue calls are call-boundary evidence, not implementations.')



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
