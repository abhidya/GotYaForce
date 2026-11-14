#!/usr/bin/env python3
"""Fixed actor-tick entry and support-contact gates from local GBF snapshots.

Read-only stdlib. Complete 80059068 plus only the entry/no-support-return spans
of 80067a70. Derived operand fields only; no arbitrary-address CLI, raw ranges,
archived-code execution, or changes to shared archive-reader allowlists.
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
    (0x80059068, 0xd0, 'ea22383e1d48094534b9c882b22400b794423bdea5657be04bcfab050da3716c'),
    (0x80067a70, 0x50, '9129c95f317a2e7bdabee44f8501fdfcc548e377cfbe72136241d49f0586974c'),
    (0x80067d58, 0x18, 'a0c187512d546cf9453e4196cd6494239a580f0fa7262d0c48ec3eceac34c994'),
)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)


def decode_selected(word, pc):
    """Only scalar forms observed in the three digest-pinned spans.

    Every selected instruction must decode. The gap inside 80067a70 is explicit
    coverage metadata, not instructions silently skipped by this decoder.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if word == 0x4e800421:
        return dict(mnemonic='bctrl', BO=20, BI=0, BH=0, LK=1)
    if op == 31 and xo == 23:
        c.require(rc == 0, 'reserved indexed-load bit')
        return dict(mnemonic='lwzx', rD=d, rA=a, rB=b)
    if op == 31 and xo in (339, 467):
        spr = (b << 5) | a
        c.require(rc == 0 and ((spr == 8 and d == 0) or
                              (spr == 9 and xo == 467 and d == 12)),
                  'unsupported SPR form')
    if not (word == 0x4e800020 or
            op in (10, 11, 14, 15, 16, 18, 21, 32, 34, 36, 37, 38, 48, 52) or
            (op == 31 and xo in (339, 444, 467, 954)) or
            (op == 59 and (xo & 31) == 18)):
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
                function_coverage=[
                    dict(entry='80059068', end_exclusive='80059138', map_width=208,
                         represented_instructions=52, unrepresented_instructions=0,
                         unrepresented_ranges=[]),
                    dict(entry='80067a70', end_exclusive='80067d70', map_width=768,
                         represented_instructions=26, unrepresented_instructions=166,
                         unrepresented_ranges=[dict(address='80067ac0', end_exclusive='80067d58',
                                                    width=664)])],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 52 tick-function instructions and all 20+6 instructions in the selected '
                       'support-contact entry/return spans are represented. The remaining 166 '
                       'support-contact instructions are NOT decoded or separately span-checked by '
                       'this fixed reader. 8005bab8 body evidence belongs to the separate gauge/scale '
                       'reader. Live FPSCR state, retail actor values and runtime ownership are '
                       'not established; downstream calls are not implementations.')


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
