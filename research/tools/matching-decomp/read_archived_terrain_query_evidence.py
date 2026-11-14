#!/usr/bin/env python3
"""Fixed terrain-query evidence from two authenticated local GBF snapshots.

Read-only stdlib. Four fixed text spans and six fixed constants only, following
existing whole-snapshot authentication and mapping guards. Emits derived
instruction fields, hashes, constants and physical traces, not raw ranges.
No arbitrary-address CLI, archived instruction execution or original-DOL claim.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_terrain_matrix_evidence as terrain
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH


RANGES = (
    (0x8003d6e4, 640, '3788a13d2282f6b5ae753eb0d7f29c13289f305f35665a0122ce54e8e1fca7b3'),
    (0x8003f320, 872, '559b34375add13a9156ac4437abc9633cb1f52dcb53817a21c5b95ca3ee4cb1a'),
    (0x8003fa68, 152, 'a8447bcc787bb143584b40bf66dde650f1d635c841eb1948b95fb421f8a57c8a'),
    (0x8003fb00, 88, '333885e9781b90d779a3a3056c414854cac154f64352ef15cf25aa8fec76b908'),
)
TARGETS = {
    0x80436f68: '00000000',
    0x80436f88: '4330000080000000',
    0x80436ffc: '43fa0000',
    0x80437034: 'c5ea6000',
    0x80437038: '45ea6000',
    # Authenticated solely to describe the excluded nonempty +20 ceiling path.
    0x80436f70: 'bf000000',
}


def decode_selected(word, pc):
    """Add only fdivs, fcmpu and cror to existing selected-field decoding.

    cror copies (CR[BA] | CR[BB]) into CR[BT]. BI 0/1/2/3 in CR0 are
    LT/GT/EQ/UN. Keeping these operands is necessary to distinguish >=, <=
    and ordered equality; collapsing these branches into C loses evidence.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    fc, xo, xx = (word >> 6) & 31, (word >> 1) & 31, (word >> 1) & 1023
    if op == 59 and xo == 18:
        c.require(fc == 0 and word & 1 == 0, 'unsupported fdivs form')
        return dict(mnemonic='fdivs', fD=d, fA=a, fB=b)
    if op == 63 and xx == 0:
        c.require(word & 0x00600001 == 0, 'unsupported fcmpu form')
        return dict(mnemonic='fcmpu', BF=(word >> 23) & 7, fA=a, fB=b)
    if op == 19 and xx == 449:
        c.require(word & 1 == 0, 'unsupported cror form')
        return dict(mnemonic='cror', BT=d, BA=a, BB=b)
    return terrain.decode_selected(word, pc)


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
    return dict(address=f'{address:08x}', bits=raw.hex(),
                value=struct.unpack('>f' if width == 4 else '>d', raw)[0], spans=spans)


def inspect(data, digest):
    # Authentication precedes all query-span reads; validates the supplied digest
    # against data as well as both known full-snapshot hashes, schemas, metadata,
    # empty File Bytes, address maps, all data5 bytes and independent controls.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
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
                              displacements={f'{a:08x}': a - 0x8043ea20 for a in TARGETS},
                              source='docs/static-recompilation-spike.md:178'),
                r13_basis=dict(recorded_value='8043b5a0', displacement=-21316,
                               derived_address='8043625c',
                               source='docs/static-recompilation-spike.md:179'),
                caveat='Archived ProgramDB evidence only. Unselected instructions are omitted. '
                       'No live FPSCR/GQR, original-DOL, full terrain/IK or gameplay parity is established. '
                       '80436f70 describes only the excluded nonempty +20 ceiling branch.')


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
