#!/usr/bin/env python3
"""Fixed normal actor-matrix evidence from two authenticated local GBF snapshots.

Read-only stdlib. Six text spans, one indexed dispatch window and one constant
only. Emits hashes, selected instruction fields and table targets, not raw
ranges. No arbitrary-address CLI, instruction execution or original-DOL claim.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_actor_traversal_evidence as traversal
import read_archived_command_evidence as command
import read_archived_constants as c
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH


RANGES = (
    (0x800465fc, 156, '7ed4ac7350606317cb9c955ccda304c0989e84dfa9b16052184c41b33a5be24f'),
    (0x80046914, 700, 'f794718b565c7444fe476be643a4197ee99f44ff47f5d775696a176f10249ebc'),
    (0x80046e7c, 120, '0d3af7347d1335ae1992342a6a7b467fcb746d25c904521df36b9e89fd4d6d0f'),
    (0x80046ef4, 20, '75237b79ca27cfc01aa947b9665ecc81cbbc352c54deb64ae070a80599518717'),
    (0x80047904, 296, '79704ea5e729833d36b5d4bb4164d21d3711b0db9e51b63a6bbef9da0ffda41e'),
    (0x80047a2c, 120, 'f8d3960587cdf2e650b9b3f0fa621b411eba9611eb2acc0a6ceb2ba22c73dd1c'),
)
TABLE_ADDRESS = 0x802d0d60
TABLE_WIDTH = 64
TABLE_SHA = '381cc4c2e0589ece921995f02d74259465998b059357aacb1774266d9437e19c'
# The masked selector can address these 16 consecutive words. This does not
# assert a separately allocated 16-element C table: later words overlap the
# address region named as setup-handler tables elsewhere in the export.
TABLE_TARGETS = (
    0x80046f08, 0x80046ef4, 0x80047164, 0x80047344,
    0x8004871c, 0x800487ec, 0x8004892c, 0x80048a6c,
    0x80048be0, 0x80049f10, 0x8004a00c, 0x8004a0e0,
    0x8004a1cc, 0x8004a2ec, 0x8004a41c, 0x8004a60c,
)
TARGETS = {0x8043709c: '3f4ccccd'}


def decode_selected(word, pc):
    """Extend the existing selected-field decoder; unselected forms stay absent."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    if op == 38:
        return dict(mnemonic='stb', rS=d, rA=a,
                    displacement=traversal.signed(word & 65535, 16))
    if op == 31 and word & 1 == 0:
        xo = (word >> 1) & 1023
        if xo == 23:
            return dict(mnemonic='lwzx', rD=d, rA=a, rB=b)
        if xo == 467 and ((b << 5) | a) == 9:
            return dict(mnemonic='mtctr', rS=d)
    if word == 0x4e800421:
        return dict(mnemonic='bctrl')
    return traversal.decode_selected(word, pc)


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


def dispatch_evidence(db):
    raw, spans = db.chain(199, TABLE_ADDRESS - 0x802bae60, TABLE_WIDTH, 0xf42c0)
    c.require(len(raw) == TABLE_WIDTH, 'selector window byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == TABLE_SHA, 'selector window digest mismatch')
    targets = tuple(c.integer(raw, offset, 'I') for offset in range(0, TABLE_WIDTH, 4))
    c.require(targets == TABLE_TARGETS, 'selector targets mismatch')
    return dict(address=f'{TABLE_ADDRESS:08x}', width=TABLE_WIDTH, sha256=digest,
                spans=spans, entries=[dict(selector=i, address=f'{TABLE_ADDRESS + 4*i:08x}',
                                          target=f'{target:08x}')
                                      for i, target in enumerate(targets)],
                damping_selectors=[i for i, target in enumerate(targets) if target == 0x80046ef4],
                scope='16 indexed words reachable by the low-nibble mask, not a proven allocation extent.')


def constant_evidence(db, address):
    c.require(address in TARGETS, 'constant not allowlisted')
    raw, spans = db.chain(263, address - 0x80436a20, 4, 27360)
    c.require(raw.hex() == TARGETS[address], 'constant width/bits mismatch')
    return dict(address=f'{address:08x}', bits=raw.hex(), value=struct.unpack('>f', raw)[0], spans=spans)


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
                dispatch_window=dispatch_evidence(db),
                constants=[constant_evidence(db, address) for address in TARGETS],
                r2_basis=dict(recorded_value='8043ea20', displacement=-31108,
                              derived_address='8043709c', source='docs/static-recompilation-spike.md:178'),
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
