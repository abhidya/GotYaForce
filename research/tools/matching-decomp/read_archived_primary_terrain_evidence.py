#!/usr/bin/env python3
"""Fixed primary two-bone terrain evidence from authenticated local GBF.

Read-only stdlib. Three fixed text spans, six typed constants and the three
selected bend-axis bytes only. Reuses existing fixed RotTrig and factor-two
evidence. Emits derived fields, never raw executable ranges. No arbitrary
address CLI, instruction execution, original-DOL or live-state parity claim.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_actor_traversal_evidence as traversal
import read_archived_terrain_matrix_evidence as terrain
import read_archived_terrain_orientation_evidence as orientation
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH


RANGES = (
    (0x80047368, 1252, '64365eb011b470b5c2abddcc606e4fe28fe8ac37b6f9f28be76af21bbde278e2'),
    (0x8020ba78, 36, '5997a5a32c7df8eb2a03901039345f35a84f00b017545800218ef21bdbfaf81a'),
    (0x8020bc88, 40, 'a5dc9dd558d92f78fdebc97036e9c4e9b250a0f57eed1b449a8515f13c029e74'),
)
# Types follow the actual lfs/lfd loads, not the decompiler's expression types.
TARGETS = {
    0x804370a0: ('f32', 4, '00000000'),
    0x804370c0: ('f64', 8, '3fe0000000000000'),
    0x804370c8: ('f64', 8, '4008000000000000'),
    0x804370d0: ('f32', 4, '3f7fbe77'),
    0x804370d4: ('f32', 4, '3f800000'),
    0x804370d8: ('f32', 4, 'bf800000'),
}
TABLE_ADDRESS, TABLE_WIDTH = 0x804336a9, 3
TABLE_SHA = '3608bca1e44ea6c4d268eb6db02260269892c0b42b86bbf1e77a6fa16c3c9282'
BEND_AXES = (120, 121, 122)
DATA4_START, DATA4_LENGTH, DATA4_ROOT = 0x804335a0, 11040, 262


def decode_selected(word, pc):
    """Preserve double refinement, single fused sine and paired subtraction.

    fnmsub/fnmsubs are -(fA*fC-fB), fused before negation. The former
    rounds as binary64, the latter as binary32 under the stated FP domain.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    fc, xo = (word >> 6) & 31, (word >> 1) & 31
    if op == 63 and xo == 25:
        c.require(b == 0 and word & 1 == 0, 'unsupported fmul form')
        return dict(mnemonic='fmul', fD=d, fA=a, fC=fc)
    if op == 63 and xo == 30:
        c.require(word & 1 == 0, 'unsupported fnmsub form')
        return dict(mnemonic='fnmsub', fD=d, fA=a, fC=fc, fB=b)
    if op == 4 and xo == 20:
        c.require(fc == 0 and word & 1 == 0, 'unsupported ps_sub form')
        return dict(mnemonic='ps_sub', fD=d, fA=a, fB=b)
    return orientation.decode_selected(word, pc)


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


def data4_mapping(blocks, subs, image):
    selected = [(key, row) for key, row in blocks.items() if row[0] == 'MAIN_.data4']
    c.require(len(selected) == 1 and selected[0][0] == 6, 'data4 identity mismatch')
    row = selected[0][1]
    c.require(row[4:] == [0x20000000004335a0, DATA4_LENGTH, 0] and
              c.address_start(row[4], image) == DATA4_START, 'data4 mapping mismatch')
    c.require([(key, row) for key, row in subs.items() if row[0] == 6] ==
              [(6, [6, 2, DATA4_LENGTH, 0, DATA4_ROOT, 0])], 'data4 subblock mismatch')


def table_evidence(db, address=TABLE_ADDRESS, width=TABLE_WIDTH):
    c.require((address, width) == (TABLE_ADDRESS, TABLE_WIDTH), 'table not allowlisted')
    c.require(DATA4_START <= address < address + width <= DATA4_START + DATA4_LENGTH,
              'table bounds')
    raw, spans = db.chain(DATA4_ROOT, address - DATA4_START, width, DATA4_LENGTH)
    c.require(len(raw) == width, 'table byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == TABLE_SHA, 'table digest mismatch')
    axes = tuple(c.integer(raw, offset, 'b') for offset in range(width))
    c.require(axes == BEND_AXES, 'bend axes mismatch')
    return dict(address=f'{address:08x}', width=width, sha256=digest, spans=spans,
                lookup_base='804336a8', element_type='signed8',
                entries=[dict(index=i + 1, selector=axis, axis=chr(axis)) for i, axis in enumerate(axes)],
                scope='Only absolute signed bend indices 1..3. Not index zero or a table allocation extent.')


def constant_evidence(db, address):
    c.require(address in TARGETS, 'constant not allowlisted')
    kind, width, expected = TARGETS[address]
    c.require((kind, width) in (('f32', 4), ('f64', 8)), 'constant type/width mismatch')
    c.require(0x80436a20 <= address < address + width <= 0x8043d500, 'constant bounds')
    raw, spans = db.chain(263, address - 0x80436a20, width, 27360)
    c.require(len(raw) == width and raw.hex() == expected, 'constant width/bits mismatch')
    return dict(address=f'{address:08x}', type=kind, width=width, bits=raw.hex(),
                value=struct.unpack('>f' if kind == 'f32' else '>d', raw)[0], spans=spans)


def inspect(data, digest):
    # Admission authenticates supplied bytes and whole-snapshot digest, schemas,
    # address map, executable metadata, empty File Bytes, all data5 and controls.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)  # Includes all-block overlap guard.
    c.require(c.data5_mapping(blocks, subs, image) ==
              (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263),
              'data5 mapping mismatch')
    data4_mapping(blocks, subs, image)
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_metadata_caveat', 'file_bytes_table',
            'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                bend_axes=table_evidence(db),
                constants=[constant_evidence(db, address) for address in TARGETS],
                reused_evidence=dict(
                    rot_trig=traversal.range_evidence(db, 21, 0x8020b2a8, 176),
                    factor_two=terrain.constant_evidence(db, 0x804370a4)),
                r2_basis=dict(recorded_value='8043ea20',
                              displacements={f'{a:08x}': a - 0x8043ea20 for a in TARGETS},
                              source='docs/static-recompilation-spike.md:178'),
                r13_basis=dict(recorded_value='8043b5a0', displacement=-32504,
                               derived_address='804336a8',
                               source='docs/static-recompilation-spike.md:179'),
                caveat='Archived ProgramDB code/data evidence only. No original capture, unchanged '
                       'original-DOL bytes, estimate hardware semantics, live FPSCR/GQR or gameplay '
                       'parity is established. Unselected instructions are omitted. General bending '
                       'and exact target attainment are not proved by the folded candidate.')


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
