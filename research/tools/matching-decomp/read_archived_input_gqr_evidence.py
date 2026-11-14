#!/usr/bin/env python3
"""Fixed 24-byte GQR4/GQR5 initializer evidence from two authenticated GBFs.

Read-only stdlib. Only six decoded operands and derived initializer settings;
no raw range, arbitrary-address option, execution or shared allowlist changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_constants as c
import read_archived_wait_evidence as wait


RANGES = ((0x8002a408, 24,
           '9b36820166852b72b71cd34c91a379644b1b9dc97aca1e7e6c078cc74933efce'),)
WORDS = {
    0x8002a408: 0x38600006,
    0x8002a40c: 0x64630006,
    0x8002a410: 0x7c74e3a6,
    0x8002a414: 0x38600007,
    0x8002a418: 0x64630007,
    0x8002a41c: 0x7c75e3a6,
}


def decode_selected(word):
    """Only li, oris and non-record mtspr; never execute an instruction."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    op, a, xo = word >> 26, (word >> 16) & 31, (word >> 1) & 1023
    c.require((op == 14 and a == 0) or op == 25 or
              (op == 31 and xo == 467 and word & 1 == 0),
              'unselected initializer instruction')
    return wait.decode_word(word)


def range_evidence(db, root, address, width):
    c.require(all(type(value) is int for value in (root, address, width)),
              'range integer fields')
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
        pc = address + offset
        word = c.integer(raw, offset, 'I')
        c.require(pc in WORDS and word == WORDS[pc], 'initializer word mismatch')
        instructions.append(dict(address=f'{pc:08x}', **decode_selected(word)))
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, spans=spans, instructions=instructions)


def initializer_settings(instructions):
    """Recognize only these two li/oris/mtspr triplets, not a PPC interpreter."""
    c.require(len(instructions) == 6, 'initializer instruction count')
    result = []
    for index, (pc, immediate, spr) in enumerate(((0x8002a408, 6, 916), (0x8002a414, 7, 917))):
        expected = [
            dict(address=f'{pc:08x}', mnemonic='li', rD=3, immediate=immediate),
            dict(address=f'{pc + 4:08x}', mnemonic='oris', rA=3, rS=3, immediate=immediate),
            dict(address=f'{pc + 8:08x}', mnemonic='mtspr', spr=spr, rS=3),
        ]
        c.require(instructions[index * 3:index * 3 + 3] == expected, 'initializer operand mismatch')
        value = expected[0]['immediate'] | (expected[1]['immediate'] << 16)
        result.append(dict(register=f'GQR{spr - 912}', spr=spr,
                           write_address=f'{pc + 8:08x}', value=f'{value:08x}',
                           load_type=(value >> 16) & 7, load_scale=(value >> 24) & 63,
                           store_type=value & 7, store_scale=(value >> 8) & 63))
    return result


def inspect(data, digest):
    # Existing full snapshot/schema/metadata/empty File Bytes/data5/control
    # authentication must complete before this reader's single fixed read.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    root = wait.text_mapping(blocks, subs, int(auth['image_offset'], 16))
    ranges = [range_evidence(db, root, address, width) for address, width, _ in RANGES]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{wait.TEXT_START:08x}', block_length=wait.TEXT_LENGTH,
                chain_root=root, ranges=ranges,
                initializer_settings=initializer_settings(ranges[0]['instructions']),
                selected_coverage=dict(start='8002a408', end_exclusive='8002a420',
                                       represented_instructions=6, unrepresented_instructions=0),
                owner_function=dict(entry='8002a3e4', width=204,
                                    source='research/symbols/GG4E-CSM-20220412.map:380',
                                    whole_function_covered=False),
                caveat='Archived initializer instruction evidence only. Not original-DOL matching, '
                       'an executed startup, live GQR contents or invariance, HID2/MSR state, '
                       'retail inputs, angular behavior, direction-table data or gameplay parity.')


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
