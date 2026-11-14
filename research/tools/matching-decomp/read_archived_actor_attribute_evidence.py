#!/usr/bin/env python3
"""Fixed actor-attribute refresh evidence from authenticated local GBF snapshots.

Read-only stdlib. The complete 80055dcc function only, with derived instruction
fields, hashes and physical traces. No raw executable output, arbitrary-address
CLI, archived instruction execution or function-specific constant acquisition.
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
    (0x80055dcc, 0x118, '7f60ab140ba8c7261c2ad34d87e1f41962e0c870e435a5c0efc12f216e6fb4a2'),
)


def decode_selected(word, pc):
    """Observed scalar forms, with only the r0/LR save and restore SPR forms.

    Reuse the existing field decoder without expanding shared modules. Store
    operands are named rS/fS to distinguish them from load destinations.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo = (word >> 1) & 1023
    if op == 31 and xo in (339, 467):
        # SPR halves are encoded in the opposite order from an ordinary D form.
        spr = (b << 5) | a
        c.require(d == 0 and spr == 8 and word & 1 == 0, 'unsupported link-register form')
        return dict(mnemonic='mflr', rD=0) if xo == 339 else dict(mnemonic='mtlr', rS=0)
    if op == 38:
        return dict(mnemonic='stb', rS=d, rA=a,
                    displacement=traversal.signed(word & 65535, 16))
    if not (word == 0x4e800020 or op in (11, 14, 16, 18, 21, 32, 36, 37, 48, 52) or
            (op == 59 and ((word >> 1) & 31) == 25)):
        return None
    decoded = traversal.decode_selected(word, pc)
    if decoded is not None and decoded['mnemonic'] in ('stw', 'stwu'):
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
        c.require(decoded is not None, 'unselected instruction in fixed span')
        instructions.append(dict(address=f'{address + offset:08x}', **decoded))
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, spans=spans, instructions=instructions)


def inspect(data, digest):
    # Whole-snapshot authentication, exact schemas, executable metadata, empty
    # File Bytes, address maps, full data5 hash and controls precede text reads.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)  # Exact identities and all-block overlap guard.
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
                       'All 70 instructions in the fixed function are represented. '
                       'Five scalar products use fmuls; all limits and row copies use lfs/stfs. '
                       'There is one final call to 8004d08c and no function-specific constant loads. '
                       'Live FPSCR state, arbitrary NaN payloads and retail actor data are not established.')


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
