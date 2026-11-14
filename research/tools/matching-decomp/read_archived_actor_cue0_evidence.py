#!/usr/bin/env python3
"""Fixed cue0 and terrain schedules from two existing authenticated GBF files.

Read-only stdlib. Authenticate whole snapshots before one previously selected
cue cell, two independent code spans, and four literal constants. No pointer
following, arbitrary-address CLI, raw output, or instruction execution. Decode
all selected instructions, including the paired-single ABI save/restore omitted
by decompiled C. Active math and unselected callees remain explicit boundaries.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_actor_normal_evidence as normal
import read_archived_command_evidence as command
import read_archived_constants as c

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)
CUE_CELL = 0x802d3300
# Independent literals, never selected from the contents of CUE_CELL.
RANGES = (
    (0x8005913c, 180, 'ae9d04496b94a8823bda233ea5be5e51b2a7855fe462b83ba29c251cc4e3188b'),
    (0x80068df8, 420, '975733da691528eb19e1ddc92bef341167d1a60154dad7d79836d26f967267c9'),
)
CONSTANTS = (
    (0x8043762c, 4, '00000000'),
    (0x80437638, 8, '3fe0000000000000'),
    (0x80437640, 8, '4008000000000000'),
    (0x80437648, 4, '41f00000'),
)
RECORDED_R2 = 0x8043ea20


def decode_selected(word, pc):
    """Explicit observed operand forms; return None for unsupported opcodes."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 16 and (d, a) == (12, 0):
        c.require(word & 3 == 0, 'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op == 52:
        return dict(mnemonic='stfs', fS=d, rA=a, displacement=normal.signed(word & 65535, 16))
    if op in (56, 60):
        w, i = (word >> 15) & 1, (word >> 12) & 7
        c.require(w == i == 0 and d == 31 and a == 1 and word & 4095 == 40,
                  'unselected paired-single ABI fields')
        return dict(mnemonic='psq_l' if op == 56 else 'psq_st',
                    **{'fD' if op == 56 else 'fS': d}, rA=a, W=w, I=i, displacement=40)
    if op == 59 and (xo & 31) == 18:
        c.require(fc == rc == 0, 'reserved single-division fields')
        return dict(mnemonic='fdivs', fD=d, fA=a, fB=b)
    if op == 63:
        if xo in (0, 32):
            c.require(d == rc == 0, 'unselected floating comparison fields')
            return dict(mnemonic='fcmpu' if xo == 0 else 'fcmpo', BF=0, fA=a, fB=b)
        if xo in (12, 26, 40):
            c.require(a == rc == 0, 'reserved floating unary fields')
            return dict(mnemonic={12: 'frsp', 26: 'frsqrte', 40: 'fneg'}[xo], fD=d, fB=b)
        if (xo & 31) == 25:
            c.require(b == rc == 0, 'reserved double-multiply fields')
            return dict(mnemonic='fmul', fD=d, fA=a, fC=fc)
        if (xo & 31) == 30:
            c.require(rc == 0, 'unselected double-fused fields')
            return dict(mnemonic='fnmsub', fD=d, fA=a, fC=fc, fB=b)
    return normal.decode_selected(word, pc)


def cell_evidence(db, mapping, address):
    c.require(type(address) is int, 'cell integer fields')
    c.require(address == CUE_CELL, 'cell not allowlisted')
    return normal.cell_evidence(db, mapping, address)


def range_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    normal.require_mapping(mapping, TEXT_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == width % 4 == 0 and start <= address < address + width <= end,
              'range alignment/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'range byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'range digest mismatch')
    instructions = []
    for offset in range(0, width, 4):
        pc = address + offset
        decoded = decode_selected(c.integer(raw, offset, 'I'), pc)
        c.require(decoded is not None, 'unselected instruction in fixed span')
        instructions.append(dict(address=f'{pc:08x}', **decoded))
    c.require(instructions[-1]['mnemonic'] == 'blr', 'span terminal return mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('b', 'bc')),
              'non-call branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, spans=spans, instructions=instructions)


def constant_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'constant integer fields')
    selected = [item for item in CONSTANTS if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(width in (4, 8) and address % width == 0 and
              start <= address < address + width <= end, 'constant alignment/width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == selected[0][2], 'constant bits mismatch')
    return dict(address=f'{address:08x}', width=width, type='f32' if width == 4 else 'f64',
                bits=raw.hex(), value=struct.unpack('>f' if width == 4 else '>d', raw)[0],
                sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def inspect(data, digest):
    # Whole-file SHA, exact schema/metadata, empty File Bytes, address maps,
    # complete data5 hash and established controls precede every selection.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, text_fact = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data3, data3_fact = normal.mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    data5, data5_fact = normal.mapping_evidence(blocks, subs, image, DATA5_MAPPING)
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[text_fact, data3_fact, data5_fact],
                cells=[cell_evidence(db, data3, CUE_CELL)],
                ranges=[range_evidence(db, text, address, width) for address, width, _ in RANGES],
                constants=[constant_evidence(db, data5, address, width)
                           for address, width, _ in CONSTANTS],
                r2_basis=dict(recorded_value=f'{RECORDED_R2:08x}',
                              displacements={f'{address:08x}': address - RECORDED_R2
                                             for address, _, _ in CONSTANTS},
                              source='docs/static-recompilation-spike.md:178',
                              caveat='Recorded SDA2 basis, not newly authenticated startup '
                                     'instructions or a live r2 capture.'),
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                                        selected_width=width, represented_instructions=width // 4,
                                        unrepresented_instructions=0, unrepresented_ranges=[])
                                   for address, width, _ in RANGES],
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, '
                       'live dispatch, runtime state or retail parity. All 150 selected '
                       'instructions decode, including paired-single ABI save/restore; '
                       'no live GQR0/FPSCR state is established. No callee body is selected. '
                       'The genuine 8003d6e4 terrain call must not become a fabricated sample. '
                       'Positive squared distance reaches frsqrte, not host sqrt; later '
                       '800452a0 and 8006a5a4 remain ordered boundaries unless separately '
                       'implemented. Return-zero terrain still reaches cue0 helper 800699d8. '
                       'No pointer chooses a read and no live-global value is inferred.')


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
