#!/usr/bin/env python3
"""Five allocator helpers, one callback and eight fixed typed metadata selections.

Read-only stdlib. Whole-snapshot authentication precedes literal selections.
No arbitrary address CLI, raw payload output, pointer walking, lifecycle reads,
original execution, estimator import or shared authenticator/allowlist changes.
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

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
RANGES = (
    (0x80088d98, 184, 'a134e40d302eb33d6ebc1c3dd371228809562bdc533d833bebf095b19180ab44'),
    (0x80197bec, 20, 'cdcbfde48212824dc444a6b18aab2c256ffdcb4fec35ad9a18b332b9529c0995'),
    (0x80197bd8, 20, '8a8dd5a501652fd1370ed64d05ed17044aada0fa4bf21eecf6b6f13f0809eaea'),
    (0x80197a0c, 204, '96222c5bda44dae9f8bb740618f6f8c5d08d455044410156499752c80db51a82'),
    (0x80006d4c, 52, 'ac9afd93b2bee5eca79b75684fcff6a276cadb29e4509e2d0db46a38c42dc3e2'),
    # Independently bounded gap, selected callback; no map-named extent.
    (0x80006f60, 24, '0070931fd4199aa0583862fedea3296041d962fd44af91ecdc761c907a85f6a0'),
)
# label, literal address, width, type, expected typed values, fixed SHA-256.
# Second-stage fields were separately justified after the first three cells.
# Returned pointer/type values are checks, never dynamic read selections.
CELLS = (
    ('battle-descriptor-root', 0x8036fa1c, 4, '>I', (0x8036f644,), '9013485b6a5daf0c7505ce80059edadf81f64480ebe7c725e1e71ec34f576aa6'),
    ('pool3-type', 0x802da673, 1, '>b', (3,), '084fed08b978af4d7d196a7446a86b58009e636b611db16211b65a9aadff29c5'),
    ('pool3-capacity', 0x802da67e, 2, '>H', (512,), '99be5efb88ca2013bd8e4eb035fd42d5245468fe9afa70d8ba9c1c419a48c4e8'),
    ('descriptor0-stride', 0x8036f654, 2, '>h', (44,), '59b94638773b642b87af5d2478ec16fbeb99d878d318561ce058787ce46bb46e'),
    ('descriptor0-init-callback', 0x8036f658, 4, '>I', (0x80006f60,), '7c9a350375faea6aeb1a90130cee6f8b49293167cabd747aa6d5520705b85a3f'),
    ('object-type3-size', 0x802da666, 2, '>H', (740,), '12edb515547ea77eb8d10532d4901e878a52732d60408d9960513e6946c5e3d5'),
    ('group8-classification', 0x802da708, 1, '>b', (16,), 'c555eab45d08845ae9f10d452a99bfcb06f74a50b988fe7e48dd323789b88ee3'),
    ('groups9-through14-classification', 0x802da709, 6, '>6b', (16, 16, 16, 16, 16, 16), '39dda76eea065c7cb80b4b9b82c279acd5e5aa5f145114a96dddf5e00c4fc46b'),
)
CALLS = {0x80088d98: ('8000540c',), 0x80197bec: (), 0x80197bd8: (),
         0x80197a0c: ('80197bec', '80197bd8', '80197ad8'), 0x80006d4c: ('80197a0c',),
         0x80006f60: ()}


def decode_selected(word, pc):
    """Selected forms, with every admitted variable bit represented."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 31 and xo in (151, 279, 343, 407):
        c.require(rc == 0, 'reserved indexed Rc')
        name, reg = {151: ('stwx', 'rS'), 279: ('lhzx', 'rD'),
                     343: ('lhax', 'rD'), 407: ('sthx', 'rS')}[xo]
        return dict(mnemonic=name, **{reg: d}, rA=a, rB=b)
    decoded = normal.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'stw', 'or', 'addis', 'rlwinm', 'addi', 'lwzx',
               'cmpli', 'bc', 'lwz', 'lbz', 'extsb', 'bl', 'b', 'stb', 'mtlr',
               'blr', 'mulli', 'add', 'mtctr', 'bctrl', 'cmpi'}
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
              [f'{address + width - 4:08x}'], 'span return-site mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('bc', 'b')), 'branch outside fixed span')
    c.require(tuple(item['target'] for item in instructions if item['mnemonic'] == 'bl') ==
              CALLS[address], 'span direct-call mismatch')
    c.require([item['address'] for item in instructions if item['mnemonic'] == 'bctrl'] ==
              (['80197aa0'] if address == 0x80197a0c else []), 'span indirect-call mismatch')
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
        function_coverage=[dict(entry=f'{pc:08x}', end_exclusive=f'{pc + width:08x}', selected_width=width,
            represented_instructions=width // 4, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis=('constructor-selected callback; preceding mapped function end and next named '
                'C/index/map start; complete straight-line terminal return' if pc == 0x80006f60 else
                'adjacent named C/index entries, map size and authenticated terminal return'),
            map_size=None if pc == 0x80006f60 else width) for pc, width, _ in RANGES],
        selection_basis=dict(descriptor_mode=1, descriptor_pool=0, descriptor_row='8036f644',
            selected_descriptor_offsets=[16, 20], object_mode=0, object_pool=3,
            object_type=3, groups=[8, 9, 10, 11, 12, 13, 14],
            remapped_actor_slot_domain=[0, 1, 2, 3, 4, 5], constructors_instruction_authenticated_here=False),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. Object count is unsigned16; descriptor '
            'count is signed16. 06d4c preserves r3 returned by197a0c despite its decompiled void type. '
            'Descriptor callback14 is NONNULL80006f60: it zeroes words20/24/28 then returns zero. '
            'Release callback18 and cleanup197ad8 are not read. '
            'Synthetic initial pool state is not source battle initialization or proof of successful '
            'allocation. Memset is a call boundary, not authenticated libc instruction/fault order.')


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
