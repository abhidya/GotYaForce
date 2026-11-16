#!/usr/bin/env python3
"""Fixed actor input-test chain and sentinel dispatch in archived ProgramDB.

Read-only stdlib, eight fixed text spans, derived operands only. No arbitrary
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
    (0x800699d8, 176, 'c809fe8851e308079759e95d7cb982414ac6399dae30d964ee36ee00f0ba07fd'),
    (0x80069a88, 136, 'c7859e78b66a2dc8fae3d67fa0fe35809f941b7da353bb344b4d60173beb8c0d'),
    (0x80069b10, 136, 'd314cddf30ff9cec52d98556ec16a0051b206c441c685e0e3db0eace3e1e113f'),
    (0x80069b98, 88, 'b1b819b1e9ff72f8e8154ac586bd3b362690f2fd099e3eb2ae73f0cc40e025cc'),
    (0x80069bf0, 96, '672733b12993bfdaf4141580b1c35f8914c4fb7f3e6139f877228278dba385fe'),
    (0x80069c50, 96, '64085e89f7385ffc9e08355146fe8c2ce9b61634ccca8bc8ea652174a28b37b2'),
    (0x80069cb0, 288, '948dca24959a3810bd95deeddc2109e709a342b405a633f060df63e5746299ab'),
    (0x80069dd0, 212, 'd47e5fab253284676c8062bab436402e6ba6e75cfcc3e3df2c8b86b1ead76830'),
)


def decode_selected(word, pc):
    """Only observed scalar forms, preserving all operand/condition fields."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 24:
        return dict(mnemonic='ori', rS=d, rA=a, immediate=word & 65535)
    if op == 31 and xo == 104:
        c.require(b == 0, 'reserved neg field')
        return dict(mnemonic='neg', rD=d, rA=a, Rc=rc)
    if op == 31 and xo in (339, 467):
        c.require(d == 0 and ((b << 5) | a) == 8 and rc == 0,
                  'unsupported link-register form')
    if not (word == 0x4e800020 or op in (11, 14, 16, 18, 21, 32, 34, 36, 37, 38) or
            (op == 31 and xo in (24, 28, 266, 339, 444, 467, 954))):
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
                                        extent_basis='C markers and authenticated return' if index == 0 else
                                        'symbol map, C markers and authenticated return',
                                        map_size=None if index == 0 else width)
                                   for index, (address, width, _) in enumerate(RANGES)],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 307 instructions in the eight fixed spans are represented. The symbol '
                       'map has no 800699d8 entry; its extent uses C markers and the authenticated '
                       '80069a84 return, not an invented map row. Active callees 8005c080, 80069ea4 '
                       'and 80069fe0 remain boundaries. No runtime 4a4/4b0 pointer, actor ownership, '
                       'descriptor contents, live input or production integration is established.')


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
