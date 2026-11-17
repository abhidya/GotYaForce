#!/usr/bin/env python3
"""Fixed ready-lifecycle evidence from authenticated local GBF snapshots.

Read-only stdlib. Complete 8006a980/8006aab0/8005a298; derived operands only.
No new fixed data reads, raw ranges, arbitrary-address CLI, execution, or
shared-reader allowlist changes.
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
    (0x8006a980, 0x130, '7fb393271bfa4e07dadb938b1fcdfa07432417321d93822c1ebc7b9926272f06'),
    (0x8006aab0, 0x54, 'c8116ab45414d5501def81eef2c485644619d856449687742002d359ed6b7662'),
    (0x8005a298, 0xe0, 'c9bf8af26f845365fb063252eba311929b38338f9bcf5a36421d632be6989efd'),
)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)


def decode_selected(word, pc):
    """Only observed forms; all operands, including the unsupported float path.

    Decode fields, never execute instructions or supply missing constant values.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 24:
        return dict(mnemonic='ori', rS=d, rA=a, immediate=word & 65535)
    if op == 40:
        return dict(mnemonic='lhz', rD=d, rA=a,
                    displacement=status.traversal.signed(word & 65535, 16))
    if op == 31 and xo == 32:
        c.require(rc == 0 and d & 3 == 0, 'reserved/non-32-bit comparison fields')
        return dict(mnemonic='cmpl', BF=d >> 2, L=0, rA=a, rB=b)
    if op == 31 and xo in (339, 467):
        c.require(d == 0 and ((b << 5) | a) == 8 and rc == 0,
                  'unsupported link-register form')
    if op == 63 and xo == 15:
        c.require(a == 0 and rc == 0, 'reserved fctiwz fields')
    if not (word == 0x4e800020 or
            op in (11, 14, 15, 16, 18, 21, 27, 32, 34, 36, 37, 38, 42, 44, 50, 54) or
            (op == 31 and xo in (339, 444, 467, 922, 954)) or
            (op == 59 and (xo & 31) in (18, 20, 25)) or
            (op == 63 and xo == 15)):
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


def inspect(data, digest):
    # Full snapshot authentication, schemas, executable metadata, empty File
    # Bytes, maps, full data5 hash and existing controls all precede fixed reads.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    c.require(c.data5_mapping(blocks, subs, image) == DATA5_MAPPING, 'data5 mapping mismatch')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=21,
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                constants=[],
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address+width:08x}',
                                        selected_width=width, represented_instructions=width//4,
                                        unrepresented_instructions=0, unrepresented_ranges=[])
                                   for address, width, _ in RANGES],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'Extents use C export next entries and final decoded blr instructions; '
                       'none of the three entries has a symbol-map size. '
                       'All 76, 21 and 56 instructions are represented, including floating-point '
                       'and stack instructions. No new fixed data is read. '
                       'The 8006a980 nonzero-4a0 call to 80066198 and its floating path remain unsupported; '
                       'the r2-relative load at 8006aa28 is decoded without authenticating its value. '
                       'Caller 8005a190 still reaches unsupported 80176ec0 after 8006aab0. '
                       'The 8005a298 call to 80010514 remains an external boundary. '
                       'Live actor values, pointer validity, ownership and retail parity are not established.')



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
