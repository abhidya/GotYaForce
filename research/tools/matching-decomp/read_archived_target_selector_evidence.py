#!/usr/bin/env python3
"""Fixed target selector evidence: 8006b450/932 and 80010514/160 bytes.

Read-only stdlib. Unchanged archive/schema/mapping authentication precedes two
independently fixed complete bodies and one separately frozen ten-cell switch
table. No globals, constants, pointer-followed code, arbitrary-address CLI, raw
output or original execution.
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
DATA3_MAPPING = normal.DATA3_MAPPING
TABLE = (0x802c3938, 40, '7464e12255e4f6c2c50b0cd2d2545500fe0a00ac82237ee4343c83dcb572ba11')
TABLE_TARGETS = (0x800105ac, 0x800105ac, 0x80010570, 0x80010578, 0x80010580,
                 0x80010588, 0x80010590, 0x80010598, 0x800105a0, 0x800105a8)
RANGES = (
    (0x8006b450, 932, 'cfc8c375b1bce3d53cbfe9f1d3283341bc7c8ca09ff463b1afaed3a838eca0a7'),
    (0x80010514, 160, '0064cd5dc8e78221bbe059631e699e5d62ce30994743b870fbf0f4ade60803da'),
)
# Explicit complete control inventory. Table targets remain a separate fixed selection.
FLOW = {
    0x8006b450: (
        (0x8006b474, 'bl', '80010514', None, None),
        (0x8006b47c, 'bc', '8006b7d8', 4, 2),
        (0x8006b488, 'bc', '8006b7d8', 4, 2),
        (0x8006b498, 'bc', '8006b7d8', 4, 1),
        (0x8006b4a0, 'bc', '8006b4f4', 12, 2),
        (0x8006b4a4, 'bc', '8006b4b8', 4, 0),
        (0x8006b4ac, 'bc', '8006b4dc', 12, 2),
        (0x8006b4b0, 'bc', '8006b4e8', 4, 0),
        (0x8006b4b4, 'b', '8006b544', None, None),
        (0x8006b4bc, 'bc', '8006b544', 4, 0),
        (0x8006b4d8, 'b', '8006b544', None, None),
        (0x8006b4e4, 'b', '8006b544', None, None),
        (0x8006b4f0, 'b', '8006b544', None, None),
        (0x8006b504, 'bc', '8006b544', 12, 2),
        (0x8006b510, 'bc', '8006b544', 12, 2),
        (0x8006b51c, 'bc', '8006b544', 4, 2),
        (0x8006b528, 'bc', '8006b544', 4, 2),
        (0x8006b540, 'b', '8006b7d8', None, None),
        (0x8006b56c, 'bc', '8006b650', 4, 1),
        (0x8006b578, 'bc', '8006b648', 12, 2),
        (0x8006b588, 'bc', '8006b648', 12, 2),
        (0x8006b594, 'bc', '8006b648', 12, 2),
        (0x8006b5a0, 'bc', '8006b648', 12, 2),
        (0x8006b5a8, 'bc', '8006b648', 12, 2),
        (0x8006b5b0, 'bc', '8006b5d0', 12, 2),
        (0x8006b5c8, 'bc', '8006b648', 12, 2),
        (0x8006b5cc, 'b', '8006b600', None, None),
        (0x8006b5e4, 'bc', '8006b648', 4, 2),
        (0x8006b5f0, 'bc', '8006b600', 12, 2),
        (0x8006b5fc, 'bc', '8006b648', 12, 2),
        (0x8006b608, 'bc', '8006b648', 12, 2),
        (0x8006b618, 'bc', '8006b648', 4, 0),
        (0x8006b624, 'bc', '8006b62c', 4, 2),
        (0x8006b64c, 'bc', '8006b570', 16, 0),
        (0x8006b658, 'bc', '8006b7d8', 12, 2),
        (0x8006b664, 'bc', '8006b6dc', 12, 2),
        (0x8006b66c, 'bc', '8006b68c', 12, 2),
        (0x8006b670, 'bc', '8006b690', 4, 0),
        (0x8006b678, 'bc', '8006b684', 4, 0),
        (0x8006b67c, 'b', '8006b690', None, None),
        (0x8006b680, 'b', '8006b690', None, None),
        (0x8006b688, 'b', '8006b690', None, None),
        (0x8006b694, 'bc', '8006b6a4', 4, 0),
        (0x8006b6a0, 'b', '8006b6b8', None, None),
        (0x8006b6b0, 'bc', '8006b6b8', 4, 1),
        (0x8006b6d4, 'bc', '8006b770', 4, 2),
        (0x8006b6d8, 'b', '8006b7d8', None, None),
        (0x8006b720, 'bl', '8020bc88', None, None),
        (0x8006b738, 'b', '8006b764', None, None),
        (0x8006b748, 'bl', '8020bc88', None, None),
        (0x8006b750, 'bc', '8006b75c', 12, 1),
        (0x8006b76c, 'bc', '8006b73c', 12, 0),
        (0x8006b7f0, 'blr', None, 20, 0),
    ),
    0x80010514: (
        (0x80010530, 'bc', '80010538', 4, 2),
        (0x80010554, 'bc', '800105ac', 12, 1),
        (0x8001056c, 'bctr', None, 20, 0),
        (0x80010574, 'b', '800105ac', None, None),
        (0x8001057c, 'b', '800105ac', None, None),
        (0x80010584, 'b', '800105ac', None, None),
        (0x8001058c, 'b', '800105ac', None, None),
        (0x80010594, 'b', '800105ac', None, None),
        (0x8001059c, 'b', '800105ac', None, None),
        (0x800105a4, 'b', '800105ac', None, None),
        (0x800105b0, 'blr', None, 20, 0),
    ),
}
FLOW_NAMES = ('bc', 'b', 'bl', 'blr', 'bclr', 'bctr', 'bctrl')


def expected_flow(entry):
    rows = []
    for pc, name, target, bo, bi in FLOW[entry]:
        row = dict(address=f'{pc:08x}', mnemonic=name)
        if target is not None: row.update(target=target, AA=0, LK=int(name == 'bl'))
        if bo is not None: row.update(BO=bo, BI=bi, LK=0)
        if name in ('blr', 'bctr'): row['BH'] = 0
        rows.append(row)
    return rows


def decode_selected(word, pc):
    """Local forms only; all admitted bits represented or fixed."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 0), (4, 1), (4, 2), (12, 0),
                  (12, 1), (12, 2), (16, 0)), 'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op == 19 and xo == 528:
        c.require(word == 0x4e800420, 'unselected branch-register form')
        return dict(mnemonic='bctr', BO=20, BI=0, BH=0, LK=0)
    if op in (40, 46, 47, 52):
        name, reg = {40: ('lhz', 'rD'), 46: ('lmw', 'rD'), 47: ('stmw', 'rS'), 52: ('stfs', 'fS')}[op]
        return dict(mnemonic=name, **{reg: d}, rA=a, displacement=normal.signed(word & 65535, 16))
    if op in (56, 60):
        return dict(mnemonic='psq_l' if op == 56 else 'psq_st',
                    **{'fD' if op == 56 else 'fS': d}, rA=a,
                    displacement=normal.signed(word & 4095, 12), W=(word >> 15) & 1, I=(word >> 12) & 7)
    if op in (24, 25):
        return dict(mnemonic='ori' if op == 24 else 'oris', rS=d, rA=a, immediate=word & 65535)
    if op == 31 and xo == 32:
        c.require(d == rc == 0, 'unselected logical comparison fields')
        return dict(mnemonic='cmpl', BF=0, L=0, rA=a, rB=b)
    if op == 31 and xo == 151:
        c.require(rc == 0, 'reserved indexed-store bit')
        return dict(mnemonic='stwx', rS=d, rA=a, rB=b)
    if op == 63 and xo == 72:
        c.require(a == rc == 0, 'reserved fmr fields')
        return dict(mnemonic='fmr', fD=d, fB=b)
    if op == 63 and xo == 32:
        c.require(d == rc == 0, 'unselected fcmpo fields')
        return dict(mnemonic='fcmpo', BF=0, fA=a, fB=b)
    decoded = normal.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'addis', 'stw', 'addi', 'lwz', 'lbz', 'extsb', 'stb',
               'cmpi', 'or', 'bl', 'b', 'cmpli', 'lfs', 'lfd', 'stfd', 'cmp',
               'rlwinm', 'mulli', 'mtctr', 'mtlr', 'blr', 'add', 'lwzx'}
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
    c.require([item for item in instructions if item['mnemonic'] in FLOW_NAMES] == expected_flow(address),
              'complete control-flow mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('bc', 'b')), 'branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def table_evidence(db, mapping, address, width):
    """Only the separately frozen 40-byte range; targets never select reads."""
    c.require(all(type(value) is int for value in (address, width)), 'table integer fields')
    c.require((address, width) == TABLE[:2], 'table range not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == width % 4 == 0 and start <= address < address+width <= end,
              'table alignment/bounds')
    raw, spans = db.chain(root, address-start, width, length)
    c.require(len(raw) == width, 'table byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == TABLE[2], 'table digest mismatch')
    targets = tuple(c.integer(raw, offset, 'I') for offset in range(0, width, 4))
    c.require(targets == TABLE_TARGETS, 'table targets mismatch')
    return dict(address=f'{address:08x}', end_exclusive=f'{address+width:08x}', width=width,
                sha256=digest, spans=spans, extent_basis='authenticated instruction reachability, not map extent',
                entries=[dict(index=index, address=f'{address+4*index:08x}', target=f'{target:08x}')
                         for index, target in enumerate(targets)])


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data); tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    mapping, mapping_facts = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data3, data3_facts = normal.mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    ranges = [range_evidence(db, mapping, pc, width) for pc, width, _ in RANGES]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping_facts, data3_facts], ranges=ranges,
        switch_table=table_evidence(db, data3, TABLE[0], TABLE[1]),
        function_coverage=[dict(entry=f'{pc:08x}', end_exclusive=f'{pc+width:08x}', selected_width=width,
            represented_instructions=width//4, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='independent C/index identity and exact named map size', map_size=width)
            for pc, width, _ in RANGES],
        selection_basis=dict(reads=3, bytes=1132, selected_code_bytes=1092, selected_data_cells=10, pointer_following=False,
            global_payloads_read=False, unlisted_callee_bodies_read=False, original_execution=False,
            globals_runtime_values_established=False, constants_selected=False, estimator_imported=False,
            switch_table_selected=True, switch_targets_established=True,
            indirect_site='8001056c', switch_table_base='802c3938',
            original_scope_sha256='152fee332f08583bdbd92a4d2456d16f22996328edcd258dade1f571c16c8fb7',
            follow_on_scope_sha256='e440af460a35669d9b0b34308a99eb2e7d8b3d7e4fa7d4d1c1c7d8a05a946db8',
            unselected_direct_call_sites=['8006b720', '8006b748'], unselected_direct_target='8020bc88'),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All 273 selected instructions represented. '
            '80010514 reads a pointer switch table, not embedded branch instructions; '
            'exactly ten targets are authenticated by a separate instruction-bounded scope. '
            'Targets never select code reads. Global/actor payloads, GQR/FPSCR state, '
            'and 8020bc88 remain unselected. Existing authentication reads are unchanged; '
            'added selections total two complete bodies and one ten-cell table, 1132 bytes.')


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
