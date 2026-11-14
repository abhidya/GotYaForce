#!/usr/bin/env python3
"""Fixed target preparation evidence: complete 8006ae60, 1520 bytes / 380 instructions.

Read-only stdlib. Unchanged archive/schema/mapping authentication precedes one
fixed selection. No constants, global payloads, pointer following, arbitrary-address CLI, raw
payload output, original execution, estimator imports or shared reader changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_actor_normal_evidence as normal

TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((0x8006ae60, 1520, '6b725b93ac0755d146b4a67fe61ec81127d98afccc77ca5c3fcd990fa199b50a'),)


# Filled from the independently inspected complete body; not inferred from callees.
FLOW = (
    (0x8006ae84, 'bc', '8006aea0', 12, 2),
    (0x8006aea8, 'bc', '8006aec4', 12, 2),
    (0x8006aecc, 'bc', '8006aee8', 12, 2),
    (0x8006aef0, 'bc', '8006af0c', 12, 2),
    (0x8006af14, 'bc', '8006af30', 12, 2),
    (0x8006af38, 'bc', '8006af54', 12, 2),
    (0x8006af68, 'bc', '8006b33c', 12, 2),
    (0x8006af78, 'bc', '8006b33c', 12, 0),
    (0x8006af80, 'bl', '8006b450', None, None),
    (0x8006af88, 'bl', '8006b7f4', None, None),
    (0x8006af94, 'bc', '8006b180', 12, 2),
    (0x8006afac, 'bl', '8020bc88', None, None),
    (0x8006afb8, 'bc', '8006b008', 4, 1),
    (0x8006b038, 'bc', '8006b088', 4, 1),
    (0x8006b098, 'bl', '8006d228', None, None),
    (0x8006b0bc, 'bc', '8006b0d4', 12, 2),
    (0x8006b0d0, 'b', '8006b0d8', None, None),
    (0x8006b0f0, 'bc', '8006b100', 4, 2),
    (0x8006b108, 'bc', '8006b114', 12, 2),
    (0x8006b110, 'b', '8006b128', None, None),
    (0x8006b118, 'bc', '8006b124', 12, 2),
    (0x8006b120, 'b', '8006b128', None, None),
    (0x8006b140, 'bc', '8006b14c', 4, 0),
    (0x8006b148, 'b', '8006b160', None, None),
    (0x8006b14c, 'bc', '8006b160', 4, 1),
    (0x8006b16c, 'bc', '8006b1d0', 4, 2),
    (0x8006b17c, 'b', '8006b1d0', None, None),
    (0x8006b190, 'bl', '80045204', None, None),
    (0x8006b1c0, 'bl', '80045238', None, None),
    (0x8006b1d8, 'bc', '8006b2ec', 12, 2),
    (0x8006b208, 'bl', '8020bc88', None, None),
    (0x8006b214, 'bc', '8006b264', 4, 1),
    (0x8006b294, 'bc', '8006b2e4', 4, 1),
    (0x8006b2e8, 'b', '8006b33c', None, None),
    (0x8006b2fc, 'bl', '80045204', None, None),
    (0x8006b32c, 'bl', '80045238', None, None),
    (0x8006b348, 'bc', '8006af60', 12, 0),
    (0x8006b368, 'bc', '8006b42c', 12, 2),
    (0x8006b370, 'bc', '8006b42c', 12, 2),
    (0x8006b37c, 'bc', '8006b42c', 4, 2),
    (0x8006b388, 'bc', '8006b42c', 4, 2),
    (0x8006b3a0, 'bc', '8006b42c', 12, 2),
    (0x8006b3b0, 'bc', '8006b42c', 12, 1),
    (0x8006b3d0, 'bc', '8006b420', 12, 2),
    (0x8006b3e4, 'bc', '8006b420', 12, 2),
    (0x8006b3f4, 'bc', '8006b420', 4, 2),
    (0x8006b41c, 'b', '8006b42c', None, None),
    (0x8006b428, 'bc', '8006b3cc', 16, 0),
    (0x8006b438, 'bc', '8006b35c', 12, 0),
    (0x8006b44c, 'blr', None, 20, 0),
)


def expected_flow():
    rows = []
    for pc, name, target, bo, bi in FLOW:
        row = dict(address=f'{pc:08x}', mnemonic=name)
        if target is not None: row.update(target=target, AA=0, LK=int(name == 'bl'))
        if bo is not None: row.update(BO=bo, BI=bi, LK=0)
        if name == 'blr': row['BH'] = 0
        rows.append(row)
    return rows


def decode_selected(word, pc):
    """Only this body's forms; every admitted bit represented or fixed."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 0), (4, 1), (4, 2), (12, 0),
                  (12, 1), (12, 2), (16, 0)), 'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op in (35, 46, 47, 52):
        if op == 35: c.require(a != 0 and a != d, 'reserved load-update fields')
        name, reg = {35: ('lbzu', 'rD'), 46: ('lmw', 'rD'),
                     47: ('stmw', 'rS'), 52: ('stfs', 'fS')}[op]
        return dict(mnemonic=name, **{reg: d}, rA=a,
                    displacement=normal.signed(word & 65535, 16))
    if op == 24:
        return dict(mnemonic='ori', rS=d, rA=a, immediate=word & 65535)
    if op == 31 and xo == 535:
        c.require(rc == 0, 'reserved indexed-float-load bit')
        return dict(mnemonic='lfsx', fD=d, rA=a, rB=b)
    if op == 31 and xo == 24:
        return dict(mnemonic='slw', rS=d, rA=a, rB=b, Rc=rc)
    if op == 19 and xo == 449:
        c.require(rc == 0, 'reserved CR logical bit')
        return dict(mnemonic='cror', crD=d, crA=a, crB=b)
    if op == 59 and (xo & 31) == 21:
        c.require(fc == rc == 0, 'reserved fadds fields')
        return dict(mnemonic='fadds', fD=d, fA=a, fB=b)
    if op == 63:
        if xo == 32:
            c.require(d == rc == 0, 'unselected fcmpo fields')
            return dict(mnemonic='fcmpo', BF=0, fA=a, fB=b)
        if xo in (12, 26):
            c.require(a == rc == 0, 'reserved unary float fields')
            return dict(mnemonic='frsp' if xo == 12 else 'frsqrte', fD=d, fB=b)
        if (xo & 31) in (25, 30):
            c.require(rc == 0, 'reserved double float record bit')
            if (xo & 31) == 25:
                c.require(b == 0, 'reserved fmul fields')
                return dict(mnemonic='fmul', fD=d, fA=a, fC=fc)
            return dict(mnemonic='fnmsub', fD=d, fA=a, fC=fc, fB=b)
    decoded = normal.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'addis', 'stw', 'addi', 'lwz', 'lbz', 'extsb', 'stb',
               'cmpi', 'or', 'bl', 'b', 'cmpli', 'lfs', 'lfd', 'fsubs', 'fmuls', 'cmp',
               'rlwinm', 'fmadds', 'lha', 'mulli', 'mtctr', 'and', 'mtlr', 'blr'}
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
               ('bc', 'b', 'bl', 'blr', 'bclr', 'bctrl')] == expected_flow(),
              'complete control-flow mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('bc', 'b')), 'branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data); tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    mapping, mapping_facts = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    ranges = [range_evidence(db, mapping, pc, width) for pc, width, _ in RANGES]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping_facts], ranges=ranges,
        function_coverage=[dict(entry='8006ae60', end_exclusive='8006b450', selected_width=1520,
            represented_instructions=380, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='independent C/index identity and exact named map size', map_size=1520)],
        selection_basis=dict(reads=1, bytes=1520, selected_data_cells=0, pointer_following=False,
            global_payloads_read=False, callee_bodies_read=False, original_execution=False,
            globals_runtime_values_established=False, constants_selected=False, estimator_imported=False,
            first_unresolved_call='8006b450', first_unresolved_call_site='8006af80'),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All 380 selected instructions represented. '
            'Constants, callee bodies, actor/global payloads and pointer targets remain unselected. '
            'frsqrte operands are represented, not its estimator implementation or live FPSCR behavior. '
            'Existing authentication reads are unchanged; only added selection is this 1520-byte body.')



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
