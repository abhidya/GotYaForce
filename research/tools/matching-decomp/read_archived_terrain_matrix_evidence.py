#!/usr/bin/env python3
"""Fixed terrain-handler evidence from two authenticated local GBF snapshots.

Read-only stdlib. Two fixed text spans and three constants
only. Emits hashes, selected instruction fields and constants, not raw
ranges. No arbitrary-address CLI, instruction execution or original-DOL claim.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_normal_matrix_evidence as normal
import read_archived_actor_traversal_evidence as traversal
import read_archived_command_evidence as command
import read_archived_constants as c
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH


RANGES = (
    (0x80047164, 480, '4568ff72bcbdb8e255eb225282710693120e868fce1afab45dd4de78f8191563'),
    (0x80047344, 36, '79c608b75e1ef0dbe48958d8d395daccb1b445f8cab487d781e0b3b43a52135e'),
)
TARGETS = {
    0x8043709c: '3f4ccccd',
    0x804370a4: '40000000',
    0x804370b8: '4330000080000000',
}


def decode_selected(word, pc):
    """Selected instruction fields only; fmadds means fA*fC+fB, once rounded."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo = (word >> 1) & 1023
    if op == 27:
        return dict(mnemonic='xoris', rS=d, rA=a, immediate=word & 65535)
    if op == 31 and xo == 535 and word & 1 == 0:
        return dict(mnemonic='lfsx', fD=d, rA=a, rB=b)
    if op == 63 and xo == 32 and word & 1 == 0 and word & 0x00600000 == 0:
        return dict(mnemonic='fcmpo', BF=(word >> 23) & 7, fA=a, fB=b)
    if op == 59 and (word >> 1) & 31 == 29 and word & 1 == 0:
        return dict(mnemonic='fmadds', fD=d, fA=a, fC=(word >> 6) & 31, fB=b)
    return normal.decode_selected(word, pc)


def range_evidence(db, root, address, width):
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
        if decoded is not None:
            instructions.append(dict(address=f'{address + offset:08x}', **decoded))
    return dict(address=f'{address:08x}', width=width, sha256=digest,
                spans=spans, instructions=instructions)


def constant_evidence(db, address):
    c.require(address in TARGETS, 'constant not allowlisted')
    width = len(TARGETS[address]) // 2
    raw, spans = db.chain(263, address - 0x80436a20, width, 27360)
    c.require(raw.hex() == TARGETS[address], 'constant width/bits mismatch')
    return dict(address=f'{address:08x}', bits=raw.hex(), value=struct.unpack('>f' if width == 4 else '>d', raw)[0], spans=spans)


def inspect(data, digest):
    # Existing authentication checks full snapshot hashes, schemas, executable
    # metadata, empty File Bytes, address maps, all data5 bytes and controls.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    # Exact text1/data3/data5 mappings, including subblocks; also rejects overlap.
    command.mappings(blocks, subs, image)
    c.require(c.data5_mapping(blocks, subs, image) ==
              (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263),
              'data5 mapping mismatch')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_metadata_caveat', 'file_bytes_table',
            'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                constants=[constant_evidence(db, address) for address in TARGETS],
                r2_basis=dict(recorded_value='8043ea20',
                              displacements={'8043709c': -31108, '804370a4': -31100, '804370b8': -31080},
                              source='docs/static-recompilation-spike.md:178'),
                caveat='Archived ProgramDB evidence only. Unselected instructions are omitted. '
                       'No live FPSCR/GQR, original-DOL, full terrain/IK or gameplay parity is established.')


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
