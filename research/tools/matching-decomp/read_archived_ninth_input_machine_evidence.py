#!/usr/bin/env python3
"""Fixed ninth input-machine descriptor and ninth-to-tenth caller evidence.

Read-only stdlib. Only 800686a4..800686d4 and 802d3958..802d3964 are added.
Derived operands/fields only; no arbitrary reads, raw output, archive execution,
or shared-reader allowlist changes. Existing wrapper/handler evidence is reused.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_input_machine_evidence as machine

c, command = machine.c, machine.command
TEXT_START, TEXT_LENGTH = machine.TEXT_START, machine.TEXT_LENGTH
DATA3_MAPPING, DATA5_MAPPING = machine.DATA3_MAPPING, machine.DATA5_MAPPING
RANGES = (
    (0x800686a4, 0x30, '46cda4dacae8063b1b784e11500b4d733b5d0db253610752afc232b9baf80ad8'),
)
DATA_RANGES = (
    (0x802d3958, 12, '521152c5a5eb1552b6b6296d55c24ad00596a2bc0e6729e56e1a4cedfc99cb4a'),
)


def decode_selected(word, pc):
    """Only the four forms reached in this fixed caller span."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, xo = word >> 26, (word >> 1) & 1023
    if not (op in (14, 15) or (op == 18 and word & 3 == 1) or
            (op == 31 and xo == 444 and word & 1 == 0)):
        return None
    return machine.decode_selected(word, pc)


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
    values = [c.integer(raw, offset, 'H') for offset in range(0, 12, 2)]
    c.require(values == [1, 0, 0, 1, 0x10, 0], 'descriptor values mismatch')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, block_name=name, block_key=key,
                subblock_key=subkey, block_start=f'{start:08x}', block_length=length,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=root, spans=spans,
                fields=[dict(offset=offset, width=2, type='u16', value=value)
                        for offset, value in zip(range(0, 12, 2), values)])


def inspect(data, digest):
    # Full snapshot/schema/metadata/empty File Bytes/maps/data5/control checks
    # precede every new fixed read; no parent reader allowlist is modified.
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
                selected_coverage=dict(address='800686a4', end_exclusive='800686d4',
                                       selected_width=48, represented_instructions=12,
                                       unrepresented_instructions=0, unrepresented_ranges=[]),
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 12 instructions in the selected caller span are represented; '
                       'this is not a complete-function coverage claim. Ninth descriptor storage '
                       'is bounded to 12 bytes by the next caller descriptor address. Tenth '
                       'descriptor bytes are not read. The ninth return is discarded without '
                       'caller stores or branches before the tenth call. Existing wrapper and '
                       'handler evidence is separate. Actor ownership and input capture are '
                       'not established. Indexed reads beyond these 12 bytes remain unsupported.')


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
