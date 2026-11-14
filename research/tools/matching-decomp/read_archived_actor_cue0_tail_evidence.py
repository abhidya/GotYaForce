#!/usr/bin/env python3
"""Fixed cue0 tail helpers and direct predicate in archived ProgramDB.

Read-only stdlib, six fixed text spans, derived operands only. No arbitrary
address/width, raw executable output, archive execution or shared allowlist edits.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_actor_status_evidence as status

c, command = status.c, status.command
TEXT_START, TEXT_LENGTH = status.TEXT_START, status.TEXT_LENGTH
RANGES = (
    (0x80069814, 76, '6478aa8c8825200e8c8f76a5acf49557a4b072133aff0a5e3c92c420e64aba43'),
    (0x800696f4, 148, '463b8c6883bc8126accbd12fb96d2e5a4315091838f60eea1ff534186ebe061b'),
    (0x80069038, 104, 'ae221bab2b247c6b93b71e3d53262eca37909b891ea1706369f34c43b30348b4'),
    (0x80069354, 168, '85e858e503b2379916a3acf16d04d426d3bdd35ddc46c1e52bb9e945a88414d8'),
    (0x80068f9c, 100, 'bb4d4cc7160149270e06ced78a6b825a09a354b65b189a9076c8c980f6664f2d'),
    (0x800694c0, 40, 'e980d963242e2be1f9873a510c776a99d7a4848dbf56f6541653328f0c7a1194'),
)
MAP_SIZES = {0x80069038: 104, 0x800694c0: 40}


def decode_selected(word, pc):
    """Only observed scalar forms, preserving all operand/condition fields."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 40:
        return dict(mnemonic='lhz', rD=d, rA=a,
                    displacement=status.traversal.signed(word & 65535, 16))
    if op == 31 and xo == 104:
        c.require(b == 0, 'reserved neg field')
        return dict(mnemonic='neg', rD=d, rA=a, Rc=rc)
    if op == 31 and xo in (339, 467):
        c.require(d == 0 and ((b << 5) | a) == 8 and rc == 0,
                  'unsupported link-register form')
    if not (word == 0x4e800020 or op in (7, 11, 14, 16, 18, 21, 32, 34, 36, 37, 38, 42, 44) or
            (op == 31 and xo in (60, 266, 339, 444, 467, 954))):
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


def inspect(data, digest):
    # Whole-snapshot/schema/metadata/File Bytes/maps/data5/control authentication
    # precedes every new fixed read. Shared readers and their allowlists are unchanged.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    c.require(c.data5_mapping(blocks, subs, image) == status.DATA5_MAPPING, 'data5 mapping mismatch')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=21,
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                                        selected_width=width, represented_instructions=width // 4,
                                        unrepresented_instructions=0, unrepresented_ranges=[],
                                        extent_basis='symbol map, C markers and authenticated return'
                                        if address in MAP_SIZES else 'C markers and authenticated return',
                                        map_size=MAP_SIZES.get(address))
                                   for address, width, _ in RANGES],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 159 instructions in six fixed spans are represented. Only 80069038 and '
                       '800694c0 have symbol-map rows; the four other extents use C markers and '
                       'authenticated returns. The first five ranges are cue0 tail helpers, not '
                       'an authenticated caller sequence within this reader. The sixth predicate '
                       'is directly called by 800696f4. Active callee 8006a750 remains a boundary. '
                       'The C export names the 80069818 r13-relative pointer as 80433934; live r13, '
                       'table contents, pointer/actor ownership and production integration are not '
                       'established. No global pointer or actor descriptor is followed.')


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
