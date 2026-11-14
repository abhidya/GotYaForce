#!/usr/bin/env python3
"""Three fixed typed cells for the already-authenticated projectile flight prefix.

Read-only stdlib. Whole-snapshot/schema/data5 authentication precedes exactly
three literal cell reads, 16 bytes total. No initializer/body reread, later row
cells, pointer following, arbitrary address CLI, original execution or imports
of runtime/trigonometric/estimator implementations. Existing readers unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_actor_normal_evidence as normal

DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)
RECORDED_R2 = 0x8043ea20
# Literal source-load order, independently selected from C and existing machine
# evidence before reading. A returned value never selects another address.
# label, address, width, floating type, decoded unsigned IEEE bits, payload SHA
CELLS = (
    ('signed-heading-bias', 0x804379d8, 8, 'f64', 0x4330000080000000,
     '07af8387624cf8f36152797d2f561246f21237d1d22b5c13006eacfa6f475e43'),
    ('heading-radian-scale', 0x804379ac, 4, 'f32', 0x38c90fdb,
     '3d1f500414368d9a27d7a22e23b59438cfba511d69d7b36d8913389df11fddb1'),
    ('initial-positive-zero-pitch', 0x804379a8, 4, 'f32', 0x00000000,
     'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'),
)
INITIALIZER = (0x8007dd84, 1148,
               'e8732a065c806b75274606baf717082e907c68db87400e1a4299b77820148ec2')
# Reused decoded instructions, NOT fresh instruction selection or execution.
# The existing initializer reader independently authenticates this complete body.
SOURCE_ORDER = (
    dict(address='8007de58', mnemonic='lha', rD=4, rA=31, displacement=0x72),
    dict(address='8007de5c', mnemonic='addis', rD=3, rA=0, immediate=0x4330),
    dict(address='8007de60', mnemonic='lwz', rD=0, rA=31, displacement=0xc8),
    dict(address='8007de64', mnemonic='xoris', rS=4, rA=4, immediate=0x8000),
    dict(address='8007de68', mnemonic='stw', rS=3, rA=1, displacement=0xc8),
    dict(address='8007de6c', mnemonic='lfd', fD=1, rA=2, displacement=-28744),
    dict(address='8007de70', mnemonic='cmpli', BF=0, L=0, rA=0, immediate=0),
    dict(address='8007de74', mnemonic='stw', rS=4, rA=1, displacement=0xcc),
    dict(address='8007de78', mnemonic='lfs', fD=2, rA=2, displacement=-28788),
    dict(address='8007de7c', mnemonic='lfd', fD=0, rA=1, displacement=0xc8),
    dict(address='8007de80', mnemonic='lfs', fD=31, rA=2, displacement=-28792),
    dict(address='8007de84', mnemonic='fsubs', fD=0, fA=0, fB=1),
    dict(address='8007de88', mnemonic='fmuls', fD=30, fA=2, fC=0),
    dict(address='8007de8c', mnemonic='bc', BO=12, BI=2, LK=0, target='8007e024', AA=0),
    dict(address='8007e024', mnemonic='fneg', fD=1, fB=31),
    dict(address='8007e028', mnemonic='addi', rD=3, rA=1, immediate=0x94),
    dict(address='8007e02c', mnemonic='addi', rD=4, rA=0, immediate=0x78),
    dict(address='8007e030', mnemonic='bl', target='8020b238', AA=0, LK=1),
)


def cell_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'cell integer fields')
    selected = [item for item in CELLS if item[1:3] == (address, width)]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    label, _, _, kind, expected_bits, expected_sha = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require((width, kind) in ((4, 'f32'), (8, 'f64')) and address % width == 0 and
              start <= address < address + width <= end, 'cell type/alignment/width/bounds')
    c.require(type(expected_bits) is int and 0 <= expected_bits < 1 << (width * 8),
              'cell expected bits bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'cell byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected_sha, 'cell digest mismatch')
    bits = int.from_bytes(raw, 'big')
    c.require(bits == expected_bits, 'cell bits mismatch')
    return dict(label=label, address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, type=kind, bits=f'{bits:0{width * 2}x}',
                value=struct.unpack('>f' if kind == 'f32' else '>d', raw)[0],
                sha256=digest, spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    data5, mapping = normal.mapping_evidence(blocks, subs, image, DATA5_MAPPING)
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping],
        cells=[cell_evidence(db, data5, address, width) for _, address, width, _, _, _ in CELLS],
        reused_initializer=dict(address=f'{INITIALIZER[0]:08x}', width=INITIALIZER[1],
            sha256=INITIALIZER[2], read_here=False,
            source='projectile-initialization-evidence-2026-11-14.md',
            source_order=list(SOURCE_ORDER)),
        r2_basis=dict(recorded_value=f'{RECORDED_R2:08x}',
            displacements={f'{address:08x}': address - RECORDED_R2 for _, address, _, _, _, _ in CELLS},
            source='docs/static-recompilation-spike.md:178',
            caveat='Previously recorded SDA2 basis, not new startup or live register evidence.'),
        selection_scope=dict(reads=3, bytes=16, bodies_read=False, row_cells_read=False,
            pointer_following=False, output_bits='decoded typed IEEE scalar bits only'),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. Existing initializer evidence is reused, '
            'not reread. Fresh signed owner72 precedes ownerc8, then bias/scale/+zero loads, fsubs '
            'and fmuls. A genuinely null ownerc8 branches to7e024; fneg changes +zero pitch to -zero '
            'before actual8020b238. This does not supply a trig/normalization/estimator backend. '
            'Non-null ballistic code and later launch/model row cells remain unselected.')


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
