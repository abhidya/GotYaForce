#!/usr/bin/env python3
"""One fixed transform-history span from two authenticated local GBF snapshots.

Read-only stdlib. Emits derived fields, hashes and physical traces, never raw
executable ranges. No arbitrary-address CLI or instruction execution. There
are no function-specific constant reads; existing archive controls are reused.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_actor_traversal_evidence as traversal
import read_archived_command_evidence as command
import read_archived_constants as c
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH


RANGES = (
    (0x8005685c, 0xa4, '9ad43b6e8ed1d405fa3c2e0fc0803871f93353c6ebf6f7ae7585d07211bf41a6'),
)


def decode_selected(word, pc):
    """Only the observed load/store, compare, mask and return instruction forms."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo = (word >> 1) & 1023
    if op == 19 and xo == 16 and d == 12 and a == 2 and b == 0 and word & 1 == 0:
        # Exact conditional return form: CR0.EQ true, no CTR test or LR update.
        return dict(mnemonic='bclr', BO=d, BI=a, BH=0, LK=0)
    if not (word == 0x4e800020 or op in (10, 16, 32, 34, 36, 40, 44, 48, 52) or
            (op == 31 and xo in (28, 954))):
        return None
    decoded = traversal.decode_selected(word, pc)
    if decoded is not None and decoded['mnemonic'] in ('stw', 'sth'):
        decoded['rS'] = decoded.pop('rD')
    if decoded is not None and decoded['mnemonic'] == 'stfs':
        decoded['fS'] = decoded.pop('fD')
    return decoded


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
        # This complete 41-instruction function needs no omitted-form caveat.
        # Refuse a future unsupported form rather than implying complete coverage.
        c.require(decoded is not None, 'unselected instruction in fixed span')
        instructions.append(dict(address=f'{address + offset:08x}', **decoded))
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, spans=spans, instructions=instructions)


def inspect(data, digest):
    # Full snapshot authentication, schemas, executable metadata, empty File
    # Bytes, address maps, full data5 hash and known controls all run first.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    # Reuse exact text1/data3/data5 identity, overlap and subblock guards.
    command.mappings(blocks, subs, image)
    c.require(c.data5_mapping(blocks, subs, image) ==
              (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263),
              'data5 mapping mismatch')
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
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All instructions in this one fixed span are represented. '
                       'This fixed function has no constant loads or calls; live FPSCR state is not established. '
                       'The scalar 6d0-to-6d4 copy uses lfs/stfs, not a raw integer copy.')


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
