#!/usr/bin/env python3
"""Fixed mass preparation evidence: one complete body /1344 bytes, three floats.

Read-only stdlib. Unchanged full archive/schema/mapping authentication precedes
four fixed selections. No pointer following, arbitrary-address CLI, raw payload
output, original execution, runtime imports or shared decoder/allowlist changes.
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
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)
RANGES = ((0x80053b30, 1344, '8c5a0b248d9fa0b131b7ff20346ee5af01ea3453ae1c8c9a18012ff8839a6890'),)
CONSTANTS = (
    (0x80437250, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119', 0.0),
    (0x80437254, 4, '2b6153d08dad36fbfbc33c125e7c858acc13a4a989168279c710896032141f98', 50000.0),
    (0x80437258, 4, 'de620abd6d3615746360c1d15ce3a56291236d37424124054a49d25e947ffc4d', 1.0),
)
# Independent complete source control-flow inventory; every target fixed.
FLOW = {
    0x80053b30: (
        (0x80053bdc, 'bc', '80053c78', 12, 2),
        (0x80053bfc, 'bc', '80053c08', 12, 2),
        (0x80053c04, 'bc', '80053c34', 4, 2),
        (0x80053c18, 'bc', '80053c2c', 4, 0),
        (0x80053c28, 'b', '80053c38', None, None),
        (0x80053c30, 'b', '80053c38', None, None),
        (0x80053c40, 'bc', '80053c78', 4, 2),
        (0x80053c80, 'bc', '80053bd4', 16, 0),
        (0x80053cb4, 'b', '80053cec', None, None),
        (0x80053cc4, 'bc', '80053cf8', 4, 2),
        (0x80053cf4, 'bc', '80053cb8', 4, 2),
        (0x80053d10, 'b', '80053d48', None, None),
        (0x80053d20, 'bc', '80053d54', 4, 2),
        (0x80053d50, 'bc', '80053d14', 4, 2),
        (0x80053d5c, 'bc', '80053c9c', 16, 0),
        (0x80053d60, 'bl', '800055fc', None, None),
        (0x80053d80, 'bl', '800055fc', None, None),
        (0x80053d8c, 'bc', '80053d94', 12, 2),
        (0x80053db8, 'bc', '80053dc4', 4, 0),
        (0x80053dc0, 'b', '80053de0', None, None),
        (0x80053de8, 'bc', '80053f30', 12, 2),
        (0x80053df4, 'bc', '80053f30', 12, 2),
        (0x80053e18, 'bc', '80053f30', 12, 0),
        (0x80053e20, 'bc', '80053e48', 4, 2),
        (0x80053e44, 'b', '80053f30', None, None),
        (0x80053e70, 'bc', '80053f24', 4, 0),
        (0x80053e90, 'bc', '80053f04', 4, 1),
        (0x80053e9c, 'bc', '80053ef0', 12, 2),
        (0x80053ee4, 'bc', '80053ea0', 16, 0),
        (0x80053eec, 'bc', '80053f04', 12, 2),
        (0x80053f00, 'bc', '80053ef4', 16, 0),
        (0x80053f20, 'b', '80053f30', None, None),
        (0x80053f2c, 'bc', '80053e1c', 16, 0),
        (0x80053f38, 'bc', '80053da8', 12, 0),
        (0x80053f50, 'bc', '8005404c', 12, 2),
        (0x80053f5c, 'bc', '8005404c', 4, 2),
        (0x80053f7c, 'bc', '8005404c', 12, 0),
        (0x80053f8c, 'bc', '80054040', 4, 2),
        (0x80053fac, 'bc', '80054020', 4, 1),
        (0x80053fb8, 'bc', '8005400c', 12, 2),
        (0x80054000, 'bc', '80053fbc', 16, 0),
        (0x80054008, 'bc', '80054020', 12, 2),
        (0x8005401c, 'bc', '80054010', 16, 0),
        (0x8005403c, 'b', '8005404c', None, None),
        (0x80054048, 'bc', '80053f80', 16, 0),
        (0x80054058, 'bc', '80053f48', 12, 0),
        (0x8005406c, 'blr', None, 20, 0)),
}


def expected_flow(address):
    rows = []
    for pc, name, target, bo, bi in FLOW[address]:
        row = dict(address=f'{pc:08x}', mnemonic=name)
        if target is not None:
            row.update(target=target, AA=0, LK=int(name == 'bl'))
        if bo is not None:
            row.update(BO=bo, BI=bi, LK=0)
        if name == 'blr': row['BH'] = 0
        rows.append(row)
    return rows


def decode_selected(word, pc):
    """Every admitted bit represented or fixed; shared decoders unchanged."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 0), (4, 1), (4, 2), (12, 0), (12, 2), (16, 0)),
                  'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op in (33, 52):
        if op == 33: c.require(a != 0 and a != d, 'reserved load-update fields')
        return dict(mnemonic='lwzu' if op == 33 else 'stfs',
                    **({'rD': d} if op == 33 else {'fS': d}), rA=a,
                    displacement=normal.signed(word & 65535, 16))
    if op == 28:
        return dict(mnemonic='andi.', rS=d, rA=a, immediate=word & 65535)
    if op == 31 and xo in (11, 40, 75, 151, 215):
        if xo in (151, 215):
            c.require(rc == 0, 'reserved indexed-store bit')
            return dict(mnemonic='stwx' if xo == 151 else 'stbx', rS=d, rA=a, rB=b)
        return dict(mnemonic={11: 'mulhwu', 40: 'subf', 75: 'mulhw'}[xo], rD=d, rA=a, rB=b, Rc=rc)
    if op == 31 and xo == 32:
        c.require(d == rc == 0, 'unselected unsigned comparison fields')
        return dict(mnemonic='cmpl', BF=0, L=0, rA=a, rB=b)
    if op == 59 and (xo & 31) == 21:
        c.require(fc == rc == 0, 'reserved fadds fields')
        return dict(mnemonic='fadds', fD=d, fA=a, fB=b)
    if op == 63 and xo == 32:
        c.require(d == rc == 0, 'unselected fcmpo fields')
        return dict(mnemonic='fcmpo', BF=0, fA=a, fB=b)
    decoded = normal.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'stw', 'lwz', 'lbz', 'stb', 'or', 'extsb', 'cmpi', 'cmp',
               'addis', 'addi', 'rlwinm', 'add', 'lbzx', 'lwzx', 'b', 'bl', 'mtlr',
               'mtctr', 'blr', 'lfs', 'fmuls', 'mulli'}
    if not decoded or decoded['mnemonic'] not in allowed: return None
    return dict(decoded, LK=rc) if decoded['mnemonic'] in ('bl', 'b') else decoded


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
    c.require([item for item in instructions if item['mnemonic'] in
               ('bc', 'b', 'bl', 'blr')] == expected_flow(address), 'complete control-flow mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('bc', 'b')), 'branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def constant_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'constant integer fields')
    selected = [item for item in CONSTANTS if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(width == 4 and address % 4 == 0 and start <= address < address + width <= end,
              'constant alignment/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'constant digest mismatch')
    value = struct.unpack('>f', raw)[0]
    c.require(value == selected[0][3], 'constant value mismatch')
    return dict(address=f'{address:08x}', width=width, sha256=digest, value=value, spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data); tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, tf = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data5, df = normal.mapping_evidence(blocks, subs, image, DATA5_MAPPING)
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    constants = [constant_evidence(db, data5, pc, width) for pc, width, _, _ in CONSTANTS]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[tf, df], ranges=ranges, constants=constants,
        function_coverage=[dict(entry='80053b30', end_exclusive='80054070', selected_width=1344,
            represented_instructions=336, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='independent C/index identity and exact named map size', map_size=1344)],
        selection_basis=dict(reads=4, bytes=1356, selected_data_cells=3, pointer_following=False,
            global_payloads_read=False, callee_bodies_read=False, original_execution=False,
            globals_runtime_values_established=False, first_unresolved_call='800055fc',
            first_unresolved_call_site='80053d60',
            constants_basis='explicit named FLOAT uses in chunk_0006.c:6774,6777,6780,6830'),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All336 selected instructions represented. '
            'Contiguous actor pass starts from pointer loaded at803c4e84; propagation loads six '
            'live pointer-table entries. First mandatory unresolved call800055fc at80053d60. '
            'Global payloads, pointer targets and both RNG callee invocations remain unselected.')


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


if __name__ == '__main__': sys.exit(main())
