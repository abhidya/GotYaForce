#!/usr/bin/env python3
"""Fixed finite signed-byte angular continuation from authenticated local GBF.

Read-only stdlib: 928 selected text bytes, six f64 constants and nineteen f64
table entries. Derived operands only. No raw executable output, arbitrary-read
CLI, archived execution, acquisition, or shared-reader allowlist changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_angular_axis_evidence as axis
import read_archived_constants as c


RANGES = (
    (0x80239a78, 392, '01d37196d53d58f2abc0f975bf9e03ea5aa908352367d23ffbd5eaf8cb58579d'),
    (0x8023c240, 536, '7d416d0cdc348e762435349f3617d5704066d9bad625163c07fede64447521c8'),
)
TARGETS = (
    (0x8043cdc8, 8, '3ca1a62633145c07'),
    (0x8043d128, 8, '7e37e43c8800759c'),
    (0x8043d130, 8, '3ff0000000000000'),
    (0x8043d138, 8, '4000000000000000'),
    (0x8043d140, 8, '3ff8000000000000'),
    (0x8043d148, 8, 'bff0000000000000'),
)
DATA2_MAPPING = (0x802b01a0, 0x802bae60, 4, 'MAIN_.data2', 4, 44224, 195)
TABLE_ADDRESS = 0x802b5168
TABLE_WIDTH = 152
TABLE_SHA256 = 'd2300c1fe150ba73b6aed6f9d794851581a2851f55926bb7c6a87593a0f9681e'
TABLE_BITS = (
    '3fddac670561bb4f', '3fe921fb54442d18', '3fef730bd281f69b', '3ff921fb54442d18',
    '3c7a2b7f222f65e2', '3c81a62633145c07', '3c7007887af0cbbd', '3c91a62633145c07',
    '3fd555555555550d', 'bfc999999998ebc4', '3fc24924920083ff', 'bfbc71c6fe231671',
    '3fb745cdc54c206e', 'bfb3b0f2af749a6d', '3fb10d66a0d03d51', 'bfadde2d52defd9a',
    '3fa97b4b24760deb', 'bfa2b4442c6a6c2f', '3f90ad3ae322da11',
)


def decode_selected(word, pc):
    """Selected scalar fields, never a generic disassembler or interpreter."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 63:
        if xo in (40, 264):
            c.require(a == 0 and rc == 0, 'reserved unary float fields')
            return dict(mnemonic='fneg' if xo == 40 else 'fabs', fD=d, fB=b)
        if xo == 32:
            c.require(rc == 0 and d & 3 == 0, 'reserved fcmpo fields')
            return dict(mnemonic='fcmpo', crD=d >> 2, fA=a, fB=b)
        form = xo & 31
        if form in (18, 20, 21, 25, 28, 29, 30):
            c.require(rc == 0, 'reserved double arithmetic record bit')
            if form in (18, 20, 21):
                c.require(fc == 0, 'reserved double binary fields')
                return dict(mnemonic={18: 'fdiv', 20: 'fsub', 21: 'fadd'}[form], fD=d, fA=a, fB=b)
            if form == 25:
                c.require(b == 0, 'reserved double multiply fields')
                return dict(mnemonic='fmul', fD=d, fA=a, fC=fc)
            return dict(mnemonic={28: 'fmsub', 29: 'fmadd', 30: 'fnmsub'}[form],
                        fD=d, fA=a, fC=fc, fB=b)
    if op == 31 and xo == 599:
        c.require(rc == 0, 'reserved lfdx record bit')
        return dict(mnemonic='lfdx', fD=d, rA=a, rB=b)
    if op in (10, 27) or (op == 31 and xo in (0, 40, 824)):
        return axis.status.decode_selected(word, pc)
    return axis.decode_selected(word, pc)


def mappings(blocks, subs, image):
    # Existing text mapping rejects all overlapping blocks before any new read.
    axis.mappings(blocks, subs, image)
    selected = [(key, row) for key, row in blocks.items() if row[0] == 'MAIN_.data2']
    c.require(len(selected) == 1 and selected[0][0] == 4 and
              selected[0][1][4:] == [0x20000000002b01a0, 44224, 0], 'data2 mapping mismatch')
    c.require([(key, row) for key, row in subs.items() if row[0] == 4] ==
              [(4, [4, 2, 44224, 0, 195, 0])], 'data2 subblock mapping mismatch')


def range_evidence(db, root, address, width):
    c.require(all(type(value) is int for value in (root, address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    c.require(root == 21 and address % 4 == width % 4 == 0 and
              axis.wait.TEXT_START <= address < address + width <= axis.wait.TEXT_START + axis.wait.TEXT_LENGTH,
              'range root/alignment/bounds')
    raw, spans = db.chain(root, address - axis.wait.TEXT_START, width, axis.wait.TEXT_LENGTH)
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


def constant_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'constant integer fields')
    selected = [item for item in TARGETS if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'constant not allowlisted')
    c.require(type(mapping) is tuple and mapping == axis.DATA5_MAPPING and
              all(type(mapping[index]) is int for index in (0, 1, 2, 4, 5, 6)), 'data5 mapping mismatch')
    start, end, _, _, _, length, root = mapping
    c.require(width == 8 and address % 8 == 0 and start <= address < address + width <= end,
              'constant alignment/width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == selected[0][2], 'constant bits mismatch')
    return dict(address=f'{address:08x}', width=width, type='f64', bits=raw.hex(),
                value=struct.unpack('>d', raw)[0], sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def table_evidence(db, mapping):
    c.require(type(mapping) is tuple and mapping == DATA2_MAPPING and
              all(type(mapping[index]) is int for index in (0, 1, 2, 4, 5, 6)), 'data2 mapping mismatch')
    start, end, key, name, subkey, length, root = mapping
    c.require(start <= TABLE_ADDRESS < TABLE_ADDRESS + TABLE_WIDTH <= end, 'table bounds')
    raw, spans = db.chain(root, TABLE_ADDRESS - start, TABLE_WIDTH, length)
    c.require(len(raw) == TABLE_WIDTH, 'table byte width')
    c.require(hashlib.sha256(raw).hexdigest() == TABLE_SHA256, 'table digest mismatch')
    c.require(tuple(raw[i:i+8].hex() for i in range(0, TABLE_WIDTH, 8)) == TABLE_BITS, 'table values mismatch')
    return dict(address=f'{TABLE_ADDRESS:08x}', width=TABLE_WIDTH, sha256=TABLE_SHA256,
                block_name=name, block_key=key, subblock_key=subkey, block_start=f'{start:08x}',
                block_length=length, chain_root=root, spans=spans,
                entries=[dict(index=index, address=f'{TABLE_ADDRESS + index*8:08x}', type='f64',
                              bits=value, value=struct.unpack('>d', bytes.fromhex(value))[0])
                         for index, value in enumerate(TABLE_BITS)])


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    mappings(blocks, subs, int(auth['image_offset'], 16))
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{axis.wait.TEXT_START:08x}', block_length=axis.wait.TEXT_LENGTH, chain_root=21,
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                constants=[constant_evidence(db, axis.DATA5_MAPPING, address, width)
                           for address, width, _ in TARGETS],
                atan_table=table_evidence(db, DATA2_MAPPING),
                function_coverage=[
                    dict(entry='80239984', end_exclusive='80239c14', width=656,
                         selected_width=392, represented_instructions=98,
                         prior_axis_reader_width=264, combined_unrepresented_ranges=[]),
                    dict(entry='8023c240', end_exclusive='8023c458', width=536,
                         selected_width=536, represented_instructions=134, unrepresented_ranges=[]),
                ],
                caveat='Archived ProgramDB evidence only, not original-DOL matching, execution or live parity. '
                       'All 232 newly selected instructions are represented. With prior axis evidence, '
                       'both complete atan/atan2 text functions are covered. Data selection closes only '
                       'finite signed8/scale0 operands (canonical +0), not general NaN/Inf/libm behavior. '
                       'Full source semantics require separately verified f64 fused rounding and explicit '
                       'processor/data owners; no live r2, FPSCR, GQR, HID2/MSR or gameplay is established.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('snapshot', type=Path)
    args = parser.parse_args()
    try:
        c.require(args.snapshot.is_file(), 'snapshot is not a regular file')
        c.require(32 <= args.snapshot.stat().st_size <= c.MAX_FILE, 'snapshot size bounds')
        with args.snapshot.open('rb') as stream:
            data = stream.read(c.MAX_FILE + 1)
        c.require(len(data) <= c.MAX_FILE, 'snapshot exceeds size bound')
        print(json.dumps(inspect(data, hashlib.sha256(data).hexdigest()), indent=2, allow_nan=False))
    except (OSError, c.FormatError) as exc:
        print(json.dumps({'error': str(exc)}), file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
