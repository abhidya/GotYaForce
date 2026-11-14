#!/usr/bin/env python3
"""Fixed projectile HIT registration and four independently typed allocator cells.

Read-only stdlib. Whole-snapshot authentication precedes exactly five literal
reads. No arbitrary addresses, pointer following, HIT payload hydration, raw
output, original execution, model imports or shared authenticator changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_actor_normal_evidence as normal
import read_archived_projectile_spawn_evidence as spawn

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
RANGES = (
    (0x8008ac80, 400, '88d16df3bda187ed3cb011269a356a7d0646ca1c946dcd194664a5abf4a317d0'),
)
# Labels, literal addresses, widths, types, values, hashes. No read selector is
# derived from a returned value. Pool4 type and groups49..54 were separate probes.
CELLS = (
    ('object-type4-size', 0x802da668, 2, '>H', (448,),
     '32444d1ca2314b6449d98ed53575e1d1dca3e826e1d622fee4502e355a21dd85'),
    ('group48-classification', 0x802da730, 1, '>b', (26,),
     '58f7b0780592032e4d8602a3e8690fb2c701b2e1dd546e703445aabd6469734d'),
    ('pool4-type', 0x802da674, 1, '>b', (4,),
     'e52d9c508c502347344d8c07ad91cbd6068afc75ff6292f062a09ca381c89e71'),
    ('groups49-through54-classification', 0x802da731, 6, '>6b', (26, 26, 26, 26, 26, 26),
     'e605937264e19250f2777c6c637c32f173428ed770f4f9a2134eb52ef2c21e24'),
)
CALLS = {0x8008ac80: ('80088aa0',)}


def decode_selected(word, pc):
    """Only selected forms; every admitted instruction bit is fixed or exposed."""
    decoded = spawn.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'stw', 'stmw', 'or', 'addi', 'lwz', 'cmpli',
               'bc', 'b', 'rlwinm', 'add', 'bl', 'addis', 'stb', 'lbz',
               'extsb', 'mulli', 'sth', 'lhz', 'lha', 'cmpi', 'lmw', 'mtlr', 'blr'}
    return decoded if decoded and decoded['mnemonic'] in allowed else None


def range_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    normal.require_mapping(mapping, TEXT_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == width % 4 == 0 and start <= address < address + width <= end,
              'range alignment/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'range byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'range digest mismatch')
    instructions = []
    for offset in range(0, width, 4):
        pc = address + offset
        decoded = decode_selected(c.integer(raw, offset, 'I'), pc)
        c.require(decoded is not None, f'unselected instruction at {pc:08x}')
        instructions.append(dict(address=f'{pc:08x}', **decoded))
    c.require([item['address'] for item in instructions if item['mnemonic'] == 'blr'] ==
              ['8008ae0c'], 'span return-site mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('bc', 'b')), 'branch outside fixed span')
    c.require(tuple(item['target'] for item in instructions if item['mnemonic'] == 'bl') ==
              CALLS[address], 'span direct-call mismatch')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def cell_evidence(db, mapping, address):
    c.require(type(address) is int, 'cell integer fields')
    selected = [item for item in CELLS if item[1] == address]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    label, _, width, fmt, expected, digest_expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(start <= address < address + width <= end and struct.calcsize(fmt) == width,
              'cell width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'cell byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == digest_expected, 'cell digest mismatch')
    values = struct.unpack(fmt, raw)
    c.require(values == expected, 'cell value mismatch')
    return dict(label=label, address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, values=list(values), sha256=digest, spans=spans)


def inspect(data, digest):
    # Preserve complete SHA/schema/language/File Bytes/maps/data5 authentication.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    maps = [normal.mapping_evidence(blocks, subs, image, m) for m in (TEXT_MAPPING, DATA3_MAPPING)]
    text, data3 = [item[0] for item in maps]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[item[1] for item in maps],
        ranges=[range_evidence(db, text, pc, width) for pc, width, _ in RANGES],
        cells=[cell_evidence(db, data3, pc) for _, pc, _, _, _, _ in CELLS],
        function_coverage=[dict(entry='8008ac80', end_exclusive='8008ae10', selected_width=400,
            represented_instructions=100, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='adjacent named C/index entries, map size and authenticated terminal return',
            map_size=400)],
        selection_basis=dict(object_mode=0, object_pool=4, object_type=4, requested_group=48,
            remapped_groups=[49, 50, 51, 52, 53, 54], remapped_actor_slot_domain=[0, 1, 2, 3, 4, 5],
            constructor_instructions_authenticated_here=False, pool_capacity_read_here=False,
            hit_payloads_read_here=False, callback_target='8008a65c', callback_body_read_here=False),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All100 instructions represented. '
            'Loop reads and sign-tests remap before count<4, including a fifth condition byte after '
            'four attempts. Successful allocation reloads remap for row selection and again for HIT12. '
            'Initial owner and asset bases are retained; child90 and27c reload after allocation. '
            'Type4 size448 and classification26 do not authenticate initial pool lists or HIT assets. '
            'No pointer determines any read. Callback8008a65c, HIT tables and collision remain unselected.')


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
