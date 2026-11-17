#!/usr/bin/env python3
"""Fixed actor-input prefix evidence from authenticated local GBF snapshots.

Read-only stdlib. Complete 800685c0/80068980/8006de44/8008b73c operands. No raw ranges,
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


RANGES = (
    (0x800685c0, 0x130, 'ce30ce82c8a3802573cd9741dba970d10c207e00cb2307bc77d7031c1aae4758'),
    (0x80068980, 0x20c, '87ed4f07dd32d732c316aa47e87f7a9bab648605637c5bf7ec1299c742bb43ce'),
    (0x8006de44, 0xa4, 'fd334ecbc181f71a71d64530d934c38e93884362c413354a07cb8a03e4a788f4'),
    (0x8008b73c, 0x74, '2bd123ab703e075e515d9b70d0029723e523eb86d60ca2cd3553796b59296908'),
)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)


def decode_selected(word, pc):
    """Only observed forms, no execution or generic disassembler fallback.

    Preserve exact unsigned compares, rotations, signed-byte record forms,
    register source/destination direction, paired-load GQR index and branches.
    Every instruction in each fixed span must decode; none are omitted.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 31 and xo == 32:
        c.require(rc == 0 and d & 3 == 0, 'reserved/non-32-bit comparison fields')
        return status.traversal.decode_selected(word, pc)
    if op == 31 and xo == 235:
        return dict(mnemonic='mullw', rD=d, rA=a, rB=b, Rc=rc)
    if op in (24, 40, 56):
        return status.traversal.decode_selected(word, pc)
    if not (word == 0x4e800020 or op in (10, 14, 15, 16, 18, 21, 32, 34, 36, 37, 38, 44) or
            (op == 31 and xo in (28, 87, 266, 339, 444, 467, 824, 954))):
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
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address+width:08x}',
                                        selected_width=width, represented_instructions=width//4,
                                        unrepresented_instructions=0, unrepresented_ranges=[])
                                   for address, width, _ in RANGES],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 76, 131, 41 and 29 instructions are represented, including the full '
                       'direction zero return and first angular call at 8008b780. No constants '
                       'or direction-table data are read. The first three extents match symbol-map '
                       'entries; 8008b73c is a C-export entry in the map gap ending at 8008b7b0. '
                       'GQR4 state, angular behavior, retail actors and runtime ownership are not '
                       'established. Runtime scope can stop before angular 800452a0 and caller '
                       '80068b8c; authenticated downstream call operands are not implementations.')



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
