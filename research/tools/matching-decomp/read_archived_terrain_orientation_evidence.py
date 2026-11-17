#!/usr/bin/env python3
"""Fixed secondary terrain-orientation evidence from authenticated local GBF.

Read-only stdlib. Nine fixed text spans, one positive-axis lookup window, one
selected dispatch cell and four constants. No arbitrary-address CLI, raw text
output or archived instruction execution. Code evidence does not establish the
Gekko reciprocal-square-root estimate or live FPSCR/GQR state.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_terrain_query_evidence as query
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH


RANGES = (
    (0x8004784c, 184, 'fb82e0b8d8e11f40b382a11097e861b4e3256a0a64406b1af1001f80fb77e0c2'),
    (0x8003de80, 552, '23cb1653c3d6d0dadb77a3e877433ec7a52365e3175e487699c8db5d3dc29faf'),
    (0x80045918, 688, 'bfee155c1b91677ec7193fe0c0304ef01fe5a12dd1613b71c6262c5e74f757d1'),
    (0x80045ef4, 212, '9078a77f10df335efefbc86ef7a833d76170b0f604c29d3b7bbc4c5616c565be'),
    (0x80046158, 200, '5a3a6bcc3270be7e7cea64413ca39b1647de0da204100a4473baa7db28799201'),
    (0x8020b7a8, 84, '0e86b49668bd9172bfd1256aa2842a4326032efab48cb6b8df58523a63992e78'),
    (0x8020bab8, 68, '0bedb847db29f7910fad9eb0124a664fee124a375a096925888092f01a159310'),
    (0x8020bb14, 68, '492e3d053ee6336c226ad94d8947492f358b1941ca2292029efea8a6d4d382bb'),
    (0x8020bb78, 60, '5628e2b0f92b5abb682884c6b2ca18d2286f3036053e283dbc44550998ee11a4'),
)
# Positive axes a,b in1..3 address base802d0d34 + (3*a+b), exactly indices4..12.
# This is a reachable window, not a claimed allocation extent. Only pair(2,1)
# and its first successful constructor are selected for the bounded closure.
TABLES = (
    (0x802d0d38, 9, '93dc572c2e7e9d5b9c7d93c548da5a04d8206f9ce4ea8de59bfab767d11009ee'),
    (0x802d0d4c, 4, '33e98d407c753368a5388cc2e512531ff0a8559fde6bd62a40757cc45fd45ada'),
)
AXIS_SELECTORS = (0, 0, 1, 2, 0, 3, 4, 5, 0)
TARGETS = {
    0x80436f78: '3f800000',
    0x80437080: '2edbe6fe',
    0x8043ca90: '3f000000',
    0x8043ca94: '40400000',
}


def decode_selected(word, pc):
    """Selected fields only. fnmsubs has fA*fC-fB, fused, then negated."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    fc, xo, xx = (word >> 6) & 31, (word >> 1) & 31, (word >> 1) & 1023
    if op == 63 and xo == 26:
        c.require(a == fc == 0 and word & 1 == 0, 'unsupported frsqrte form')
        return dict(mnemonic='frsqrte', fD=d, fB=b)
    if op == 59 and xo == 30:
        c.require(word & 1 == 0, 'unsupported fnmsubs form')
        return dict(mnemonic='fnmsubs', fD=d, fA=a, fC=fc, fB=b)
    if op == 31:
        if xx in (339, 467) and ((b << 5) | a) == 8:
            c.require(word & 1 == 0, 'unsupported link-register form')
            return dict(mnemonic='mflr' if xx == 339 else 'mtlr', **({'rD': d} if xx == 339 else {'rS': d}))
        if xx == 824:
            c.require(word & 1 == 0, 'unsupported srawi form')
            return dict(mnemonic='srawi', rS=d, rA=a, SH=b)
        if xx == 316:
            c.require(word & 1 == 0, 'unsupported xor form')
            return dict(mnemonic='xor', rS=d, rA=a, rB=b)
        if xx == 40:
            c.require(word & 1 == 0, 'unsupported subf form')
            return dict(mnemonic='subf', rD=d, rA=a, rB=b)
        if xx == 104:
            c.require(b == 0 and word & 1 == 0, 'unsupported neg form')
            return dict(mnemonic='neg', rD=d, rA=a)
        if xx == 87:
            c.require(word & 1 == 0, 'unsupported lbzx form')
            return dict(mnemonic='lbzx', rD=d, rA=a, rB=b)
    return query.decode_selected(word, pc)


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


def table_evidence(db, address, width):
    selected = [item for item in TABLES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'table not allowlisted')
    c.require(0x802bae60 <= address < address + width <= 0x802bae60 + 0xf42c0,
              'table bounds')
    raw, spans = db.chain(199, address - 0x802bae60, width, 0xf42c0)
    c.require(len(raw) == width, 'table byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'table digest mismatch')
    result = dict(address=f'{address:08x}', width=width, sha256=digest, spans=spans)
    if address == 0x802d0d38:
        selectors = tuple(c.integer(raw, i, 'b') for i in range(9))
        c.require(selectors == AXIS_SELECTORS, 'axis selectors mismatch')
        result['lookup_base'] = '802d0d34'
        result['entries'] = [dict(normal_axis=a, reference_axis=b, index=3*a+b,
                                  selector=selectors[3*a+b-4])
                             for a in range(1, 4) for b in range(1, 4)]
    else:
        target = c.integer(raw, 0, 'I')
        c.require(target == 0x80046158, 'selected constructor mismatch')
        result.update(dispatch_base='802d0d44', selector=2, target=f'{target:08x}')
    return result


def constant_evidence(db, address):
    c.require(address in TARGETS, 'constant not allowlisted')
    raw, spans = db.chain(263, address - 0x80436a20, 4, 27360)
    c.require(len(raw) == 4 and raw.hex() == TARGETS[address], 'constant width/bits mismatch')
    return dict(address=f'{address:08x}', bits=raw.hex(), value=struct.unpack('>f', raw)[0], spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    c.require(c.data5_mapping(blocks, subs, image) ==
              (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263),
              'data5 mapping mismatch')
    # Authenticate selector/dispatch facts before reading their chosen constructor.
    selected_tables = [table_evidence(db, address, width) for address, width, _ in TABLES]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_metadata_caveat', 'file_bytes_table',
            'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                tables=selected_tables,
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                constants=[constant_evidence(db, address) for address in TARGETS],
                selected_domain=dict(normal_axis=2, reference_axis=1, constructor='80046158',
                                     first_constructor_must_succeed=True),
                r2_basis=dict(recorded_value='8043ea20',
                              displacements={f'{a:08x}': a - 0x8043ea20 for a in TARGETS},
                              source='docs/static-recompilation-spike.md:178'),
                caveat='Archived ProgramDB code/data evidence only, not estimate hardware semantics, '
                       'live FPSCR/GQR, unchanged original-DOL bytes or gameplay parity. '
                       'Negative axes, fallback constructors and 47368 remain outside the selected domain.')


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
