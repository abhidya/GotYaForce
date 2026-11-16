#!/usr/bin/env python3
"""Fixed object scheduler evidence: three independent bodies /596 bytes.

Read-only stdlib. Unchanged complete archive/schema/mapping authentication
precedes exactly three fixed code selections. No selected data cells, returned
pointer following, arbitrary-address CLI, raw payload output, original execution,
shared-authenticator changes or runtime/estimator imports.
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
RANGES = (
    (0x80089898, 228, '126a25b8262b9ec16da7e6121fd72318cce3c39faab481f718d2a559307c1299'),
    (0x8008997c, 280, '3d628d2b7b32b3cd2c7e0816370547898bb863673bd68351246c797720e57eab'),
    (0x80089a94, 88, 'dcb8bf7edce7313e0e258ee526af82153e5e35eac0987938a42cccc6a270dde4'),
)
REUSED_EVIDENCE = (
    dict(address='80088e50', width=328,
         sha256='c747b919f60eaad0d8b255db2b1fdc9ecb0bd22cea33c4930d1085dcdf34d3f4',
         source='projectile-cleanup-evidence-2026-11-14.md', read_here=False,
         purpose='callback cleanup may unlink object without clearing its own next8'),
    dict(address='80089814', width=132,
         sha256='1bb689f99364d17b27d89cf9d15ceb89ffde7be29dc90d4bba30b495975710dd',
         source='projectile-cleanup-evidence-2026-11-14.md', read_here=False,
         purpose='pool return clears active0 and next4, not next8'),
)
# Independent complete control-flow inventory; every flag is fixed explicitly.
FLOW = {
    0x80089898: (
        (0x800898b0, 'bc', '800898ec', 4, 0),
        (0x800898bc, 'bc', '800898ec', 12, 2),
        (0x800898c4, 'bc', '800898dc', 4, 0),
        (0x800898d4, 'bc', '800898ec', 12, 2),
        (0x800898d8, 'b', '80089964', None, None),
        (0x800898e8, 'bc', '80089964', 4, 2),
        (0x80089900, 'b', '8008995c', None, None),
        (0x8008990c, 'bc', '80089958', 12, 2),
        (0x80089944, 'bctrl', None, 20, 0),
        (0x80089950, 'bc', '80089958', 12, 2),
        (0x80089960, 'bc', '80089904', 4, 2),
        (0x80089978, 'blr', None, 20, 0)),
    0x8008997c: (
        (0x80089994, 'bc', '80089a80', 4, 0),
        (0x800899b0, 'bc', '80089a70', 12, 2),
        (0x800899b8, 'bc', '800899d8', 4, 0),
        (0x800899d0, 'bc', '80089a70', 4, 2),
        (0x800899d4, 'b', '800899f0', None, None),
        (0x800899ec, 'bc', '80089a70', 4, 2),
        (0x80089a0c, 'b', '80089a68', None, None),
        (0x80089a18, 'bc', '80089a64', 12, 2),
        (0x80089a50, 'bctrl', None, 20, 0),
        (0x80089a5c, 'bc', '80089a64', 12, 2),
        (0x80089a6c, 'bc', '80089a10', 4, 2),
        (0x80089a7c, 'bc', '800899a4', 12, 0),
        (0x80089a90, 'blr', None, 20, 0)),
    0x80089a94: (
        (0x80089aac, 'bc', '80089ab8', 4, 0),
        (0x80089ab4, 'bc', '80089ac4', 12, 2),
        (0x80089abc, 'bl', '80089898', None, None),
        (0x80089ac0, 'b', '80089ad8', None, None),
        (0x80089ac4, 'bl', '8008997c', None, None),
        (0x80089acc, 'bl', '80089898', None, None),
        (0x80089ad4, 'bl', '80089898', None, None),
        (0x80089ae8, 'blr', None, 20, 0)),
}


def expected_flow(address):
    rows = []
    for pc, name, target, bo, bi in FLOW[address]:
        row = dict(address=f'{pc:08x}', mnemonic=name)
        if target is not None:
            row.update(target=target, AA=0, LK=int(name == 'bl'))
        if bo is not None:
            row.update(BO=bo, BI=bi, LK=int(name == 'bctrl'))
        if name in ('blr', 'bctrl'):
            row['BH'] = 0
        rows.append(row)
    return rows


def decode_selected(word, pc):
    """Every admitted bit is represented or fixed; shared decoder unchanged."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op in (40, 46, 47):
        name, reg = {40: ('lhz', 'rD'), 46: ('lmw', 'rD'), 47: ('stmw', 'rS')}[op]
        if op == 46:
            c.require(a == 0 or a < d, 'reserved load-multiple base overlap')
        return dict(mnemonic=name, **{reg: d}, rA=a, displacement=normal.signed(word & 65535, 16))
    if op == 31 and xo == 24:
        return dict(mnemonic='slw', rS=d, rA=a, rB=b, Rc=rc)
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 0), (4, 2), (12, 0), (12, 2)),
                  'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    decoded = normal.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'stw', 'lwz', 'lbz', 'stb', 'sth', 'or', 'and',
               'extsb', 'cmpi', 'cmpli', 'addis', 'addi', 'rlwinm', 'add',
               'lwzx', 'b', 'bl', 'mtlr', 'mtctr', 'bctrl', 'blr'}
    if not decoded or decoded['mnemonic'] not in allowed:
        return None
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
               ('bc', 'b', 'bl', 'blr', 'bctrl')] == expected_flow(address),
              'complete control-flow mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('bc', 'b')),
              'branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, mapping = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping], ranges=ranges,
        function_coverage=[dict(entry=f'{pc:08x}', end_exclusive=f'{pc + width:08x}', selected_width=width,
            represented_instructions=width // 4, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='independent C/index identity and exact named map size', map_size=width)
            for pc, width, _ in RANGES],
        selection_basis=dict(reads=3, bytes=596, selected_data_cells=0, pointer_following=False,
            reused_helpers_read=False, global_payloads_read=False, callback_bodies_read=False,
            group_heads='803c706c', eligibility_pointer_table='803c4e84',
            pause_owner_pointer='r13-31852', pause_owner_C_name='PTR_DAT_80433934',
            pause_owner_runtime_value_established=False),
        reused_evidence=list(REUSED_EVIDENCE),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All149 selected instructions represented. '
            'Global pause-owner contents, eligibility objects, group heads and callback targets are not read. '
            'Both walkers copy fields before calling stored object0c with object r3; after normal return '
            'they inspect live86, conditionally clear1ca, then reload live next8, without rechecking active0. '
            'No null callback/eligibility pointer guard, group-range clamp or cycle guard is added. '
            'Wrapper order on signed base<56 and low3==0 is six eligibility groups, base, base+7.')


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
