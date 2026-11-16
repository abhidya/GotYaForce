#!/usr/bin/env python3
"""Two fixed callback/ammo bodies and four constants from archived ProgramDBs.

Read-only stdlib. Authenticate the whole snapshot before six literal reads.
C/index/map independently fix both complete extents; named C scalar references
fix four constants. No pointer following, arbitrary address CLI, raw payload
output, original execution, model import, or shared allowlist changes.
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
# Literal selections independently justified in the accompanying evidence note.
RANGES = (
    (0x800715f8, 224, '7735b73fbd6b3149290d56bad8eed6be6202d6afbcb315708646b0717bbda4a8'),
    (0x8006dbe0, 224, '0b2e322f452d317b5f515e0ebd95f821a10cdbee5db9cdbd07678c8d251eed31'),
)
CONSTANTS = (
    (0x80437748, '41200000', 'hSpeed44', 'b9e69238a01189ddad0c70c62fc04d362b55ee6eefaa558dd13fc45ac1d665be'),
    (0x804376e4, '00000000', 'hDecel4c', 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'),
    (0x80437768, '41700000', 'yVel48', '6684130864793326a78b61833fd87b8235a4a62157e3d50ac29ed8a2abaf83c1'),
    (0x804376e0, 'bf800000', 'gravityCoeff50', 'b705efea49cb3296c6f0417c21fe14f10adb140333fd79d7cfc3318904f887ea'),
)


def decode_selected(word, pc):
    """Selected PPC forms only, retaining every admitted variable operand."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 19:
        c.require(word == 0x4e800020, 'unselected branch-register form')
        return dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0)
    if op == 18:
        c.require(word & 2 == 0, 'unselected absolute branch')
        return dict(mnemonic='bl' if rc else 'b',
                    target=f'{(pc + normal.signed(word & 0x3fffffc, 26)) & 0xffffffff:08x}', AA=0, LK=rc)
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 0), (4, 2), (12, 2)),
                  'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op == 11:
        c.require(d == 0, 'unselected comparison fields')
        return dict(mnemonic='cmpi', BF=0, L=0, rA=a, immediate=normal.signed(word & 65535, 16))
    if op in (14, 15):
        return dict(mnemonic='addi' if op == 14 else 'addis', rD=d, rA=a,
                    immediate=normal.signed(word & 65535, 16))
    if op == 21:
        return dict(mnemonic='rlwinm', rS=d, rA=a, SH=b, MB=fc, ME=(word >> 1) & 31, Rc=rc)
    if op == 27:
        return dict(mnemonic='xoris', rS=d, rA=a, immediate=word & 65535)
    if op in (32, 34, 36, 37, 42, 44, 48, 50, 52):
        name, reg = {32: ('lwz', 'rD'), 34: ('lbz', 'rD'), 36: ('stw', 'rS'),
                     37: ('stwu', 'rS'), 42: ('lha', 'rD'), 44: ('sth', 'rS'),
                     48: ('lfs', 'fD'), 50: ('lfd', 'fD'), 52: ('stfs', 'fS')}[op]
        c.require(op != 37 or a != 0, 'reserved store-update base')
        return dict(mnemonic=name, **{reg: d}, rA=a, displacement=normal.signed(word & 65535, 16))
    if op == 31:
        if xo in (339, 467):
            spr = (b << 5) | a
            c.require(rc == 0 and spr == 8 and d == 0, 'unselected SPR form')
            return dict(mnemonic='mflr', rD=0) if xo == 339 else dict(mnemonic='mtlr', rS=0)
        if xo == 0:
            c.require(d == rc == 0, 'unselected register comparison fields')
            return dict(mnemonic='cmp', BF=0, L=0, rA=a, rB=b)
        if xo in (922, 954):
            c.require(b == 0, 'reserved sign-extension fields')
            return dict(mnemonic='extsh' if xo == 922 else 'extsb', rS=d, rA=a, Rc=rc)
        if xo == 444:
            return dict(mnemonic='or', rS=d, rA=a, rB=b, Rc=rc)
        if xo in (40, 266):
            return dict(mnemonic='subf' if xo == 40 else 'add', rD=d, rA=a, rB=b, OE=0, Rc=rc)
    if op == 59 and (xo & 31) in (20, 21):
        c.require(fc == rc == 0, 'reserved single-arithmetic fields')
        return dict(mnemonic='fsubs' if (xo & 31) == 20 else 'fadds', fD=d, fA=a, fB=b)
    return None


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
    calls = [item['target'] for item in instructions if item['mnemonic'] == 'bl']
    c.require(calls == (['8006dbe0'] + ['8007db5c'] * 4 if address == 0x800715f8 else []),
              'span direct-call mismatch')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def constant_evidence(db, mapping, address):
    c.require(type(address) is int, 'constant integer fields')
    selected = [item for item in CONSTANTS if item[0] == address]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    _, bits, label, expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == 0 and start <= address < address + 4 <= end, 'constant alignment/bounds')
    raw, spans = db.chain(root, address - start, 4, length)
    c.require(len(raw) == 4, 'constant byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected, 'constant digest mismatch')
    c.require(raw.hex() == bits, 'constant bits mismatch')
    return dict(label=label, address=f'{address:08x}', end_exclusive=f'{address + 4:08x}', width=4,
                bits=bits, value=struct.unpack('>f', raw)[0], sha256=digest, spans=spans)


def inspect(data, digest):
    # Keep complete SHA/schema/language/File Bytes/maps/data5 authentication intact.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    maps = [normal.mapping_evidence(blocks, subs, image, m) for m in (TEXT_MAPPING, DATA5_MAPPING)]
    text, data5 = [item[0] for item in maps]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[item[1] for item in maps],
        ranges=[range_evidence(db, text, pc, width) for pc, width, _ in RANGES],
        constants=[constant_evidence(db, data5, pc) for pc, _, _, _ in CONSTANTS],
        function_coverage=[dict(entry=f'{pc:08x}', end_exclusive=f'{pc + width:08x}', selected_width=width,
            represented_instructions=width // 4, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='adjacent named C/index entries, map size and authenticated terminal return',
            map_size=width) for pc, width, _ in RANGES],
        recorded_bases=dict(r2='8043ea20',
            caveat='Previously recorded basis, not freshly authenticated startup or live processor state.'),
        reused_evidence=dict(
            timer_zero=dict(address='80437658', bits='00000000', read_here=False,
                source='actor-status-timers-evidence-2026-11-13.md'),
            signed_conversion=dict(address='804376a0', bits='4330000080000000', read_here=False,
                source='actor-status-timers-evidence-2026-11-13.md')),
        caveat='Archived ProgramDB static evidence only, not unchanged original-DOL identity, execution, '
            'MATCH, live dispatch, runtime integration or playability. Both complete 56-instruction bodies '
            'include all operands and returns. Callback tests signed part1 state before yaw/physics writes, '
            'then consumes real slot2 ammo before inspecting signed borg type. Ammo has no capacity or '
            'default-success shortcut. Successful selected projectile calls remain explicit boundaries; '
            'no 8007db5c body, projectile assets, magnitude/model code, tables or pointer-following reads.')


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
