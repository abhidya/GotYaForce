#!/usr/bin/env python3
"""Fixed actor-control and bounded charge-effect evidence from archived ProgramDB.

Read-only stdlib. Six complete fixed functions, +0f, two color pointers, cue1
pointer and its first signed16 only. No pointer-following API, raw output,
arbitrary-address CLI, original/archived execution or shared allowlist changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_charge_helper_evidence as charge

c, command, status = charge.c, charge.command, charge.status
TEXT_START, TEXT_LENGTH = charge.TEXT_START, charge.TEXT_LENGTH
DATA3_MAPPING, DATA5_MAPPING = charge.DATA3_MAPPING, charge.DATA5_MAPPING
RANGES = (
    (0x8005a190, 0x108, '38c79e7746c5dd77629b3c47c8548fb6f8e9cdb6bd1a071374eeed808095ca66'),
    (0x8006ab9c, 0x1c, '84dc19c6d1c42e0aebd50aefb26c7094fdf09c8ee54db60004bf6d9ec4a79e35'),
    (0x8006abb8, 0x1c, '1fcb5229a65674e661e975d13a6c7de2dfcd6272455f5cd12e7a1aef7d1c5583'),
    (0x800061cc, 0x24, '89494a4a32bc20ce7acf322deb4d5857318ab1708d18d530c8982d920dedc74b'),
    (0x800061f0, 0x48, '8abedf63ca8b25b1c456bb4ecffa2f79e8ddd0fe0cfbaf81be0f464f80f63b6d'),
    (0x800f0104, 0x110, '5d114b7dd7dc8252d474b0681d7b6fa1db756427eb0d67c68db3e00a318ec5b4'),
)
DATA_RANGES = (
    (0x80436a20, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'),
    (0x802c37bc, 8, 'fade6764faf5058f95209d0725c28d0899d47529cb5881eadefa4cb828a8dcb6'),
    (0x8031b698, 4, '283ff16b0fc15610bcb5c698fd5235ab535c956de7a340c946de14e6840be646'),
    (0x8031b454, 2, '0d1abbe3b9da7a48d463edb0a844f3a102dcf7fdea35f9c771d885027b31b322'),
)


def decode_selected(word, pc):
    """Only observed scalar forms, including C-unreachable 800f01c8.

    Decode every instruction, preserving operand direction and signedness.
    This is evidence interpretation, never instruction execution.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 40:
        return dict(mnemonic='lhz', rD=d, rA=a,
                    displacement=status.traversal.signed(word & 65535, 16))
    if op == 31 and xo == 23:
        c.require(rc == 0, 'reserved indexed-load bit')
        return dict(mnemonic='lwzx', rD=d, rA=a, rB=b)
    if op == 31 and xo == 26:
        c.require(b == 0, 'reserved cntlzw fields')
        return dict(mnemonic='cntlzw', rS=d, rA=a, Rc=rc)
    if op == 31 and xo in (339, 467):
        c.require(d == 0 and ((b << 5) | a) == 8 and rc == 0,
                  'unsupported link-register form')
    if not (word == 0x4e800020 or
            op in (10, 11, 14, 15, 16, 18, 21, 32, 34, 36, 37, 38, 42, 44, 48, 52) or
            (op == 31 and xo in (0, 28, 266, 339, 444, 467, 922, 954))):
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
    expected = DATA5_MAPPING if address == 0x80436a20 else DATA3_MAPPING
    c.require(type(mapping) is tuple and mapping == expected and
              all(type(mapping[index]) is int for index in (0, 1, 2, 4, 5, 6)),
              'data mapping mismatch')
    start, end, key, name, subkey, length, root = mapping
    alignment = 2 if address == 0x8031b454 else 4
    c.require(address % alignment == width % alignment == 0 and
              start <= address < address + width <= end, 'data alignment/bounds')
    if address == 0x8031b454:
        # Always authenticate the one fixed pointer before its one fixed head.
        # Neither the address nor width of the head is computed from that pointer.
        anchor = data_evidence(db, mapping, 0x8031b698, 4)
        c.require(anchor['fields'][0]['value'] == '8031b454', 'cue1 pointer anchor mismatch')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'data byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'data digest mismatch')
    if address == 0x80436a20:
        c.require(c.integer(raw, 0, 'I') == 0, 'positive zero mismatch')
        fields = [dict(offset=0, width=4, type='f32', value=struct.unpack('>f', raw)[0])]
    elif address == 0x802c37bc:
        values = [c.integer(raw, offset, 'I') for offset in (0, 4)]
        c.require(values == [0x802c36b0, 0x802c36e0], 'color pointer mismatch')
        fields = [dict(offset=offset, width=4, type='pointer32', value=f'{value:08x}',
                       table_base='802c3770', table_index=0x13 + offset // 4)
                  for offset, value in zip((0, 4), values)]
    elif address == 0x8031b698:
        value = c.integer(raw, 0, 'I')
        c.require(value == 0x8031b454, 'cue1 pointer mismatch')
        fields = [dict(offset=0, width=4, type='pointer32', value=f'{value:08x}',
                       table_base='8031b694', table_index=1)]
    else:
        value = c.integer(raw, 0, 'h')
        c.require(value == 126, 'cue1 signed16 head mismatch')
        fields = [dict(offset=0, width=2, type='s16', value=value,
                       pointer_cell='8031b698', role='cue1 record first signed16 only')]
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, block_name=name, block_key=key,
                subblock_key=subkey, block_start=f'{start:08x}', block_length=length,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=root,
                spans=spans, fields=fields)


def inspect(data, digest):
    # Snapshot/schema/metadata/empty File Bytes/maps/data5/control checks precede
    # every new fixed read. No shared reader or shared allowlist is modified.
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
                r2_basis=dict(recorded_value='8043ea20', displacements={'80436a20': -32768},
                              caveat='Previously recorded SDA2 basis; not a live r2 capture.'),
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                data_ranges=[data_evidence(db, mapping5 if address == 0x80436a20 else mapping3,
                                          address, width) for address, width, _ in DATA_RANGES],
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                                        selected_width=width, represented_instructions=width // 4,
                                        unrepresented_instructions=0, unrepresented_ranges=[])
                                   for address, width, _ in RANGES],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 175 selected instructions are represented, including C-unreachable '
                       '800f01c8 and every stack instruction. Control callees 8006aab0/80176ec0/8006a980 '
                       'are not authenticated. Color script bodies are not read. Only cue1 pointer '
                       'and first signed16 are authenticated; matching heads do not establish matching '
                       'records or no writes: owner/countdown are still stored. Sound activation and '
                       'replacement callees, timestamp, mode record fields, audio constant80439050, '
                       'live actor/slot ownership and production integration remain unestablished. '
                       'The full 80059068 tick is covered by the separate tick-prefix reader; its '
                       'conditional indirect call800590e8 has no resolved table target here.')


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
