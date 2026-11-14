#!/usr/bin/env python3
"""Fixed initial projectile handler, draw-list insertion and one row1 HIT kind.

Read-only stdlib. Whole-snapshot authentication precedes exactly three fixed
reads. No arbitrary address CLI, raw payload output, pointer following, other
row fields, HIT assets/body, original execution or shared authenticator changes.
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
    (0x8007dd84, 1148, 'e8732a065c806b75274606baf717082e907c68db87400e1a4299b77820148ec2'),
    (0x80089100, 568, 'aa8525094a1010f6a9580f8d8d8413754b0204b809fb9f18536f97a640d650e5'),
)
CELLS = (
    ('variant1-hit-kind', 0x802d6da3, 1, '>b', (1,),
     '4bf5122f344554c53bde2ebb8cd2b7e3d1600ad631c385a5d7cce23c7785459a'),
)
CALLS = {0x8007dd84: (
    '80089100', '8008ac80', '8020b7a8', '8020ba54', '8020ba78', '8023c240',
    '8020ba78', '8023cb78', '8020b238', '8020b238', '8020af5c', '8020bab8',
    '8020ba9c', '80006fb4', '800086b8', '80007c30', '80007d40', '80006fb4',
    '80006f78', '80006fb4', '80045ef4', '800aedc0', '80047aa4', '8007e200'),
    0x80089100: ()}
RETURNS = {0x8007dd84: (('8007e1fc', 'blr'),), 0x80089100: (
    ('80089108', 'bclr'), ('8008914c', 'blr'), ('80089158', 'blr'),
    ('80089188', 'blr'), ('80089194', 'blr'), ('800891d4', 'blr'),
    ('800891e0', 'blr'), ('80089210', 'blr'), ('8008921c', 'blr'),
    ('80089264', 'blr'), ('80089270', 'blr'), ('800892a8', 'blr'),
    ('800892b4', 'blr'), ('800892ec', 'blr'), ('800892f8', 'blr'),
    ('80089328', 'blr'), ('80089334', 'blr'))}


def decode_selected(word, pc):
    """Selected PPC forms only; every admitted bit is represented or fixed."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 19 and xo == 16:
        c.require(word in (0x4e800020, 0x4d820020), 'unselected branch-register form')
        return dict(mnemonic='blr' if d == 20 else 'bclr', BO=d, BI=a, BH=0, LK=0)
    if op == 19 and xo == 449:
        c.require(rc == 0, 'reserved CR logical bit')
        return dict(mnemonic='cror', BT=d, BA=a, BB=b)
    if op == 54:
        return dict(mnemonic='stfd', fS=d, rA=a, displacement=normal.signed(word & 65535, 16))
    if op in (56, 60):
        name, field = ('psq_l', 'fD') if op == 56 else ('psq_st', 'fS')
        return dict(mnemonic=name, **{field: d}, rA=a,
                    displacement=normal.signed(word & 4095, 12), W=(word >> 15) & 1, I=(word >> 12) & 7)
    if op == 63 and xo in (12, 26, 40, 72):
        c.require(a == rc == 0, 'reserved FP unary fields')
        return dict(mnemonic={12: 'frsp', 26: 'frsqrte', 40: 'fneg', 72: 'fmr'}[xo], fD=d, fB=b)
    if op == 63 and xo == 32:
        c.require(d == rc == 0, 'unselected FP comparison fields')
        return dict(mnemonic='fcmpo', BF=0, fA=a, fB=b)
    if op in (59, 63) and (xo & 31) in (18, 25, 30):
        form = xo & 31
        c.require(rc == 0, 'unselected FP record bit')
        if form == 18:
            c.require(op == 59 and fc == 0, 'unselected FP division fields')
            return dict(mnemonic='fdivs', fD=d, fA=a, fB=b)
        if form == 25:
            c.require(b == 0, 'reserved FP multiply fields')
            return dict(mnemonic='fmuls' if op == 59 else 'fmul', fD=d, fA=a, fC=fc)
        c.require(op == 63, 'unselected FP negative multiply-subtract precision')
        return dict(mnemonic='fnmsub', fD=d, fA=a, fC=fc, fB=b)
    decoded = spawn.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'stw', 'stmw', 'or', 'addis', 'lbz', 'lwz', 'addi',
               'extsb', 'rlwinm', 'stb', 'mulli', 'add', 'bl', 'lha', 'sth', 'cmpi',
               'bc', 'b', 'xoris', 'lfd', 'cmpli', 'lfs', 'fsubs', 'fadds', 'stfs',
               'lmw', 'mtlr', 'lwzx', 'stwx'}
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
    c.require(tuple((item['address'], item['mnemonic']) for item in instructions
                    if item['mnemonic'] in ('blr', 'bclr')) == RETURNS[address], 'span return-site mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('bc', 'b')), 'branch outside fixed span')
    c.require(tuple(item['target'] for item in instructions if item['mnemonic'] == 'bl') == CALLS[address],
              'span direct-call mismatch')
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
            extent_basis=('authenticated state0 identity; adjacent C/index entries and terminal return; '
                'no named map row' if pc == 0x8007dd84 else
                'adjacent named C/index entries, map size and all authenticated return sites'),
            map_size=None if pc == 0x8007dd84 else width) for pc, width, _ in RANGES],
        row_selection=dict(base='802d6d68', stride=56, variant=1, row='802d6da0',
            field_offset=3, address='802d6da3', width=1, signed=True,
            consumer_call='8008ac80', consumer_body_read_here=False),
        reused_evidence=dict(initial_state_cell=dict(address='802d6f98', width=4, target='8007dd84',
            sha256='82ff512b4b2bdffddacade1b434ca6436328ae1014d77deb3f0db087032876cd', read_here=False),
            variant1_source=dict(source='projectile-spawn-evidence-2026-11-14.md', read_here=False)),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All429 instruction operands and18 return '
            'sites are represented. Child11 loads before owner90 and the state18 store. The prefix '
            'registers separate104/108 draw-list links before84 and72 stores, then calls8ac80 with '
            'signed row1 HIT kind1. HIT assets/body, pointer referents, other row fields and helper bodies '
            'are unselected. Reading the whole initializer does not implement its later dependencies. '
            'No pointer value determines any read.')


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
