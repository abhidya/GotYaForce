#!/usr/bin/env python3
"""Fixed axis-only angular evidence from two authenticated local GBF snapshots.

Read-only stdlib: 364 selected text bytes, five numeric constants and one
8-entry byte table. No raw executable output, arbitrary-address CLI, execution,
acquisition or changes to any shared reader's allowlist.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_actor_status_evidence as status
import read_archived_constants as c
import read_archived_wait_evidence as wait


RANGES = (
    (0x800452a0, 0x44, 'cda6ef97281052cb1f03422007ce4b07056ec9232342bd6e0c2fd6c07fdd38b8'),
    (0x8023cb78, 0x20, 'cf8c2fc8d1d538e2582ef7c59421fab6a440e19e32eed3354320b6bd5da843dd'),
    (0x80239984, 0xf4, 'a7d7c189206c510355f928043bc10a7d103275746bec7bc3125ce08f352abc2e'),
    (0x80239c00, 0x14, '632aad066b44b80b2d4062eea6c08624bbb761e3dc516c09c839ff0258eb5fe3'),
)
TARGETS = (
    (0x8043707c, 4, '4622f983'),
    (0x8043cd78, 8, '400921fb54442d18'),
    (0x8043cd80, 8, 'c00921fb54442d18'),
    (0x8043cd88, 8, 'bff921fb54442d18'),
    (0x8043cd90, 8, '3ff921fb54442d18'),
)
DATA4_MAPPING = (0x804335a0, 0x804360c0, 6, 'MAIN_.data4', 6, 11040, 262)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)
TABLE_ADDRESS = 0x80433928
TABLE_WIDTH = 8
TABLE_SHA256 = '6f804bbb73c4b8d418ef3ae69153dc5cde7bf4eb989b44c6ae082a5122108fec'
TABLE_VALUES = (2, 10, 8, 9, 1, 5, 4, 6)


def decode_selected(word, pc):
    """Only selected operand forms; not an interpreter or generic disassembler."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op in (56, 60):
        return dict(mnemonic='psq_l' if op == 56 else 'psq_st',
                    **({'fD': d} if op == 56 else {'fS': d}), rA=a,
                    displacement=status.traversal.signed(word & 0xfff, 12),
                    W=(word >> 15) & 1, I=(word >> 12) & 7)
    if op == 20:
        return dict(mnemonic='rlwimi', rS=d, rA=a, SH=b,
                    MB=(word >> 6) & 31, ME=(word >> 1) & 31, Rc=rc)
    if op == 31 and xo == 104:
        c.require(b == 0, 'reserved neg fields')
        return dict(mnemonic='neg', rD=d, rA=a, Rc=rc)
    if op == 31 and xo == 32:
        c.require(rc == 0 and d & 3 == 0, 'reserved/non-32-bit comparison fields')
        return status.traversal.decode_selected(word, pc)
    if op == 63 and xo == 12:
        c.require(a == 0 and rc == 0, 'reserved frsp fields')
        return dict(mnemonic='frsp', fD=d, fB=b)
    if op == 63 and (xo & 31) == 21:
        c.require(fc == 0 and rc == 0, 'reserved fadd fields')
        return dict(mnemonic='fadd', fD=d, fA=a, fB=b)
    if not (word == 0x4e800020 or op in (11, 14, 15, 16, 18, 21, 32, 36, 37, 42, 48, 50, 54) or
            (op == 59 and (xo & 31) == 25) or
            (op == 31 and xo in (339, 444, 467))):
        return None
    return status.decode_selected(word, pc)


def mappings(blocks, subs, image):
    # text_mapping also rejects every overlapping block, invalid address or segment.
    wait.text_mapping(blocks, subs, image)
    c.require(c.data5_mapping(blocks, subs, image) == DATA5_MAPPING, 'data5 mapping mismatch')
    selected = [(key, row) for key, row in blocks.items() if row[0] == 'MAIN_.data4']
    c.require(len(selected) == 1 and selected[0][0] == 6 and
              selected[0][1][4:] == [0x20000000004335a0, 11040, 0], 'data4 mapping mismatch')
    c.require([(key, row) for key, row in subs.items() if row[0] == 6] ==
              [(6, [6, 2, 11040, 0, 262, 0])], 'data4 subblock mapping mismatch')


def range_evidence(db, root, address, width):
    c.require(all(type(value) is int for value in (root, address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    c.require(root == 21 and address % 4 == width % 4 == 0 and
              wait.TEXT_START <= address < address + width <= wait.TEXT_START + wait.TEXT_LENGTH,
              'range root/alignment/bounds')
    raw, spans = db.chain(root, address - wait.TEXT_START, width, wait.TEXT_LENGTH)
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
    c.require(type(mapping) is tuple and mapping == DATA5_MAPPING, 'data5 mapping mismatch')
    start, end, _, _, _, length, root = mapping
    c.require(width in (4, 8) and address % width == 0 and start <= address < address + width <= end,
              'constant alignment/width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == selected[0][2], 'constant bits mismatch')
    return dict(address=f'{address:08x}', width=width, type='f32' if width == 4 else 'f64',
                bits=raw.hex(), value=struct.unpack('>f' if width == 4 else '>d', raw)[0],
                sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def table_evidence(db, mapping):
    c.require(type(mapping) is tuple and mapping == DATA4_MAPPING, 'data4 mapping mismatch')
    start, end, key, name, subkey, length, root = mapping
    c.require(start <= TABLE_ADDRESS < TABLE_ADDRESS + TABLE_WIDTH <= end, 'table bounds')
    raw, spans = db.chain(root, TABLE_ADDRESS - start, TABLE_WIDTH, length)
    c.require(len(raw) == TABLE_WIDTH, 'table byte width')
    c.require(hashlib.sha256(raw).hexdigest() == TABLE_SHA256, 'table digest mismatch')
    c.require(tuple(raw) == TABLE_VALUES, 'table values mismatch')
    return dict(address=f'{TABLE_ADDRESS:08x}', width=TABLE_WIDTH, sha256=TABLE_SHA256,
                block_name=name, block_key=key, subblock_key=subkey, block_start=f'{start:08x}',
                block_length=length, chain_root=root, spans=spans,
                entries=[dict(index=index, address=f'{TABLE_ADDRESS + index:08x}',
                              type='u8', value=value) for index, value in enumerate(raw)])


def inspect(data, digest):
    # Complete existing snapshot/schema/metadata/empty File Bytes/data5/control
    # authentication and all selected mappings precede any new selected read.
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
                block_start=f'{wait.TEXT_START:08x}', block_length=wait.TEXT_LENGTH, chain_root=21,
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                constants=[constant_evidence(db, DATA5_MAPPING, address, width)
                           for address, width, _ in TARGETS],
                direction_table=table_evidence(db, DATA4_MAPPING),
                function_coverage=[
                    dict(entry='800452a0', end_exclusive='800452e4', width=68,
                         selected_width=68, represented_instructions=17, unrepresented_ranges=[]),
                    dict(entry='8023cb78', end_exclusive='8023cb98', width=32,
                         selected_width=32, represented_instructions=8, unrepresented_ranges=[]),
                    dict(entry='80239984', end_exclusive='80239c14', width=656,
                         selected_width=264, represented_instructions=66,
                         unrepresented_ranges=[dict(start='80239a78', end_exclusive='80239c00', width=392)]),
                ],
                caveat='Archived ProgramDB evidence only; not original-DOL matching or live parity. '
                       'All 91 selected instructions are represented. General atan2 and its atan '
                       'callee are not covered. x==1 reaches unsupported call80239a04; ordinary '
                       'non-axis inputs leave this slice at80239a78. Constants and table do not '
                       'establish live r2/r13, GQR0/GQR5, FPSCR, HID2/MSR, actor ownership or gameplay.')


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
