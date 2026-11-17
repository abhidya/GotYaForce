#!/usr/bin/env python3
"""Fixed charge helper and two tables from authenticated archived ProgramDB.

Read-only stdlib. The complete 164-instruction helper, four f32 constants and
six u32 masks only. Derived fields, no arbitrary reads, raw output, archive
execution, or shared-reader allowlist changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_input_machine_evidence as machine

c, command, status = machine.c, machine.command, machine.status
TEXT_START, TEXT_LENGTH = machine.TEXT_START, machine.TEXT_LENGTH
DATA3_MAPPING, DATA5_MAPPING = machine.DATA3_MAPPING, machine.DATA5_MAPPING
RANGES = (
    (0x800686f0, 0x290, '55523dd4f938a0f11bb9f7a26ae31de5d5eb3647354af3315ba37979340f3817'),
)
DATA_RANGES = (
    (0x802d3970, 24, '57b950110534ba512d9dc0bc63a304c0c8b37bff19ae889779618d3109cd2ae0'),
    (0x80437628, 16, '339a9072dd04453256cb6f8826245e04de4e202128dc8a7cc54cf4654b06e03c'),
)


def decode_selected(word, pc):
    """Only observed forms; complete coverage includes paired stack save/restore.

    fnmsubs means single-round fA*fC-fB, then negate. GQR/FPSCR runtime state is
    not established by decoding. Derived fields do not execute instructions.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op in (46, 47):
        return dict(mnemonic='lmw' if op == 46 else 'stmw',
                    **({'rD': d} if op == 46 else {'rS': d}), rA=a,
                    displacement=status.traversal.signed(word & 65535, 16))
    if op in (56, 60):
        c.require(((word >> 15) & 1) == 0 and ((word >> 12) & 7) == 0,
                  'unselected paired stack quantization form')
        return dict(mnemonic='psq_l' if op == 56 else 'psq_st',
                    **({'fD': d} if op == 56 else {'fS': d}), rA=a,
                    displacement=status.traversal.signed(word & 4095, 12), W=0, I=0)
    if op == 31 and xo == 535:
        c.require(rc == 0, 'reserved indexed float memory bit')
        return dict(mnemonic='lfsx', fD=d, rA=a, rB=b)
    if op == 59 and (xo & 31) == 30:
        c.require(rc == 0, 'unsupported fnmsubs record form')
        return dict(mnemonic='fnmsubs', fD=d, fA=a, fC=fc, fB=b)
    if op == 31 and xo in (339, 467):
        c.require(d == 0 and ((b << 5) | a) == 8 and rc == 0,
                  'unsupported link-register form')
    if not (word == 0x4e800020 or
            op in (11, 14, 15, 16, 18, 21, 32, 34, 36, 37, 38, 48, 50, 52, 54) or
            (op == 19 and xo == 449) or
            (op == 31 and xo in (0, 24, 28, 60, 87, 339, 444, 467, 954)) or
            (op == 59 and (xo & 31) in (20, 21, 25)) or
            (op == 63 and xo == 32)):
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
    expected = DATA3_MAPPING if address == 0x802d3970 else DATA5_MAPPING
    c.require(type(mapping) is tuple and mapping == expected and
              all(type(mapping[index]) is int for index in (0, 1, 2, 4, 5, 6)),
              'data mapping mismatch')
    start, end, key, name, subkey, length, root = mapping
    c.require(address % 4 == width % 4 == 0 and start <= address < address + width <= end,
              'data alignment/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'data byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'data digest mismatch')
    values = [c.integer(raw, offset, 'I') for offset in range(0, width, 4)]
    if address == 0x802d3970:
        c.require(values == [0x200, 0x200, 0x400, 0x400, 0x800, 0x1000], 'mask values mismatch')
        fields = [dict(offset=offset, width=4, type='u32', value=value,
                       role='held input mask' if offset < 12 else 'release result mask',
                       slot=(offset // 4) % 3)
                  for offset, value in zip(range(0, width, 4), values)]
    else:
        c.require(values == [0x41200000, 0, 0x3f800000, 0x40000000], 'constant values mismatch')
        fields = [dict(offset=offset, width=4, type='f32', value=struct.unpack_from('>f', raw, offset)[0])
                  for offset in range(0, width, 4)]
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, block_name=name, block_key=key,
                subblock_key=subkey, block_start=f'{start:08x}', block_length=length,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=root, spans=spans,
                fields=fields)


def inspect(data, digest):
    # Full snapshot/schema/metadata/empty File Bytes/maps/data5/control checks
    # precede every new fixed read; no parent reader allowlist is modified.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    mapping5 = c.data5_mapping(blocks, subs, image)
    c.require(mapping5 == DATA5_MAPPING, 'data5 mapping mismatch')
    name, key, encoded, length, root = command.MAPPINGS[1]
    start = c.address_start(encoded, image)
    mapping3 = (start, start + length, key, name, key, length, root)
    c.require(mapping3 == DATA3_MAPPING, 'data3 mapping mismatch')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=21,
                r2_basis=dict(recorded_value='8043ea20',
                              displacements={f'{address:08x}': address - 0x8043ea20
                                             for address in range(0x80437628, 0x80437638, 4)},
                              caveat='Previously recorded SDA2 basis; not a live r2 capture.'),
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                data_ranges=[data_evidence(db, mapping3 if address == 0x802d3970 else mapping5,
                                          address, width) for address, width, _ in DATA_RANGES],
                function_coverage=dict(entry='800686f0', end_exclusive='80068980',
                                       selected_width=656, represented_instructions=164,
                                       unrepresented_instructions=0, unrepresented_ranges=[]),
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 164 instructions are represented, including paired stack save/restore '
                       '80068700/80068964 omitted by the C export. No instruction is assumed unreachable. '
                       'The fixed six masks and four constants are authenticated; no arbitrary table '
                       'index or adjacent data is admitted. Callee bodies 800f0104 and 800061cc are not '
                       'authenticated here. Live FPSCR/GQR/r2 state, actor ownership, actor values '
                       'and production integration are not established.')


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
