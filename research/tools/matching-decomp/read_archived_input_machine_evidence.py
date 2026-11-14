#!/usr/bin/env python3
"""Fixed first input-machine evidence from authenticated local GBF snapshots.

Read-only stdlib: complete wrapper and three handlers, first 12-byte descriptor,
and three dispatch targets. Derived fields only, no raw or arbitrary reads,
original/archive execution, or shared-reader allowlist changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_actor_status_evidence as status
import read_archived_command_evidence as command
import read_archived_constants as c
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH


RANGES = (
    (0x80068b8c, 0x88, '47cba4509016e06f1bd98132a48e436013e6ff74ff62478a8efc1060eede27a2'),
    (0x80068c14, 0x70, '230e4f4b80234a1ff978cda142ff079bd9c11cfa0b271b7c1b3208a7339ff314'),
    (0x80068c84, 0x80, '178de0acf5085e37b37b6581715136703b885a808261e30c7de13395067c7ab6'),
    (0x80068d04, 0xf4, 'f077c452065b1619363a0b2190a4c35aa0b018223f9ad9c9fa144cbffe8bb923'),
)
DATA_RANGES = (
    (0x802d38f8, 12, '9de63b2eeedf5a02dd167702d515058ad54ea92b8095283a3038d240bfd764ca'),
    (0x802d3988, 12, '89ef779dd3c9f8f9603d38286c5124e32d7dbde2bdf60ac109e671e5a7a241ad'),
)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 0xf42c0, 199)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)


def decode_selected(word, pc):
    """Decode only observed forms; reserved encodings and omissions fail closed."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if word == 0x4e800421:
        return dict(mnemonic='bctrl', BO=20, BI=0, BH=0, LK=1)
    if op == 31 and xo == 23:
        c.require(rc == 0, 'reserved indexed memory bit')
        return dict(mnemonic='lwzx', rD=d, rA=a, rB=b)
    if op == 31 and xo in (26, 104):
        c.require(b == 0, 'reserved unary fields')
        if xo == 26:
            return dict(mnemonic='cntlzw', rS=d, rA=a, Rc=rc)
        return dict(mnemonic='neg', rD=d, rA=a, Rc=rc)
    if op == 40:
        return status.traversal.decode_selected(word, pc)
    if not (word == 0x4e800020 or op in (10, 11, 14, 15, 16, 18, 21, 32, 34, 36, 37, 38) or
            (op == 31 and xo in (0, 28, 40, 266, 339, 444, 467, 954))):
        return None
    return status.decode_selected(word, pc)


def range_evidence(db, root, address, width):
    c.require(all(type(value) is int for value in (root, address, width)), 'range integer fields')
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
        c.require(decoded is not None, 'unselected instruction in fixed span')
        instructions.append(dict(address=f'{address + offset:08x}', **decoded))
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, spans=spans, instructions=instructions)


def data_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'data integer fields')
    selected = [item for item in DATA_RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'data range not allowlisted')
    c.require(type(mapping) is tuple and mapping == DATA3_MAPPING and
              all(type(mapping[index]) is int for index in (0, 1, 2, 4, 5, 6)),
              'data3 mapping mismatch')
    start, end, key, name, subkey, length, root = mapping
    c.require(address % 4 == width % 4 == 0 and start <= address < address + width <= end,
              'data alignment/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'data byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'data digest mismatch')
    result = dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                  width=width, sha256=digest, block_name=name, block_key=key,
                  subblock_key=subkey, block_start=f'{start:08x}', block_length=length,
                  subblock_type=2, starting_offset=0, source_offset=0, chain_root=root, spans=spans)
    if address == 0x802d38f8:
        values = [c.integer(raw, offset, 'H') for offset in range(0, 12, 2)]
        c.require(values == [1, 0, 0, 1, 0x200, 0], 'descriptor values mismatch')
        result['fields'] = [dict(offset=offset, width=2, type='u16', value=value)
                            for offset, value in zip(range(0, 12, 2), values)]
    else:
        targets = [c.integer(raw, offset, 'I') for offset in range(0, 12, 4)]
        c.require(targets == [0x80068c14, 0x80068c84, 0x80068d04], 'dispatch targets mismatch')
        result['entries'] = [dict(index=index, address=f'{address + index * 4:08x}',
                                  width=4, target=f'{target:08x}')
                             for index, target in enumerate(targets)]
    return result


def inspect(data, digest):
    # Snapshot identity, schemas, executable metadata, empty File Bytes, maps,
    # full data5 digest and controls are checked before new fixed-range reads.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    c.require(c.data5_mapping(blocks, subs, image) == DATA5_MAPPING, 'data5 mapping mismatch')
    name, key, encoded, length, root = command.MAPPINGS[1]
    start = c.address_start(encoded, image)
    mapping = (start, start + length, key, name, key, length, root)
    c.require(mapping == DATA3_MAPPING, 'data3 mapping mismatch')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=21,
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                data_ranges=[data_evidence(db, mapping, address, width)
                             for address, width, _ in DATA_RANGES],
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                                        selected_width=width, represented_instructions=width // 4,
                                        unrepresented_instructions=0, unrepresented_ranges=[])
                                   for address, width, _ in RANGES],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 155 instructions are represented. The 68c84 entry is a separate leaf '
                       'after the 68c14 epilogue and return, absent from the C export and symbol map. '
                       'The authenticated dispatch table independently identifies that entry; '
                       'the adjacent 68d04 entry bounds its selected extent. Only the first '
                       '12-byte descriptor and three dispatch entries are authenticated here. '
                       'Out-of-range state/index values do not authorize adjacent reads. '
                       'Actor ownership and input capture are not established.')


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
