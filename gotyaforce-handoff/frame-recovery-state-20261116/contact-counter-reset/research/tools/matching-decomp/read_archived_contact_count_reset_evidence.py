#!/usr/bin/env python3
"""One fixed 48-byte contact-count reset body; no data cells or helper reads.

Original bytes and complete instruction listings remain local and are not output.
Uses unchanged existing archive authentication, mappings, and instruction decoder.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_object_scheduler_evidence as base
c, command, normal = base.c, base.command, base.normal
TEXT_MAPPING = base.TEXT_MAPPING
RANGE = (0x8008a28c, 48, '94cb040d0d0bd380e6ab2d81aec5d82583aaf212f52408a7050212f7e39acc08')
OPERAND_SHA256 = '74610b50d0d0d77b8f5906823cecc306f02500938980c06f57f017f1c6e93cdc'
STORE_ADDRESSES = tuple(range(0x80436250, 0x8043623c, -2))


def summarize(rows):
    c.require(len(rows) == 12, 'instruction count')
    first, last = rows[0], rows[-1]
    c.require(first['mnemonic'] == 'addi' and first['rA'] == 0 and first['immediate'] == 0, 'literal zero')
    stores = rows[1:-1]
    c.require(all(r['mnemonic'] == 'sth' and r['rS'] == first['rD'] and r['rA'] == 13 for r in stores), 'halfword store form')
    addresses = tuple(0x8043b5a0 + r['displacement'] for r in stores)
    c.require(addresses == STORE_ADDRESSES, 'ordered counter addresses')
    c.require(last == dict(address='8008a2b8', mnemonic='blr', BO=20, BI=0, BH=0, LK=0), 'terminal return')
    return dict(stores=[f'{p:08x}' for p in addresses], width=2, value=0, calls=[],
                prior_values_read=False, lists_read=False,
                r13_basis='Previously recorded8043b5a0, not a live register capture')


def range_evidence(db, mapping, address, width):
    c.require(type(address) is type(width) is int, 'range integer fields')
    c.require((address, width) == RANGE[:2], 'range not allowlisted')
    normal.require_mapping(mapping, TEXT_MAPPING)
    raw, spans = db.chain(mapping[-1], address - mapping[0], width, mapping[-2])
    c.require(len(raw) == width and hashlib.sha256(raw).hexdigest() == RANGE[2], 'range digest/width mismatch')
    rows = []
    for offset in range(0, width, 4):
        pc = address + offset
        decoded = base.decode_selected(c.integer(raw, offset, 'I'), pc)
        c.require(decoded is not None, 'unrepresented instruction')
        rows.append(dict(address=f'{pc:08x}', **decoded))
    digest = hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()
    c.require(digest == OPERAND_SHA256, 'operand digest mismatch')
    return dict(address=f'{address:08x}', width=width, sha256=RANGE[2],
                operand_sha256=digest, represented_instructions=len(rows), unrepresented_instructions=0,
                semantics=summarize(rows), spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    mapping, fact = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    selected = range_evidence(db, mapping, *RANGE[:2])
    return dict(snapshot=auth['snapshot'], snapshot_sha256=auth['snapshot_sha256'],
                mappings=[fact], ranges=[selected],
                selection=dict(reads=1, bytes=48, data_cells=0, helpers_read=False,
                               pointer_following=False, raw_or_operand_listing_output=False),
                caveat='Archived static evidence only. No original execution, normal-frame completion or live global values.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('snapshot', type=Path)
    args = parser.parse_args()
    try:
        c.require(args.snapshot.is_file() and 32 <= args.snapshot.stat().st_size <= c.MAX_FILE, 'snapshot bounds')
        with args.snapshot.open('rb') as stream:
            data = stream.read(c.MAX_FILE + 1)
        c.require(len(data) <= c.MAX_FILE, 'snapshot exceeds bounds')
        print(json.dumps(inspect(data, hashlib.sha256(data).hexdigest()), indent=2, allow_nan=False))
    except (OSError, c.FormatError) as error:
        print(json.dumps({'error': str(error)}), file=sys.stderr)
        return 1
    return 0

if __name__ == '__main__':
    sys.exit(main())
