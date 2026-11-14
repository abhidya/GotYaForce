#!/usr/bin/env python3
"""Fixed projectile state3 cleanup: nine selections /1100 bytes.

Read-only stdlib. Complete unchanged snapshot/schema/maps authentication
precedes two scalar cells and seven independently bounded bodies. No returned
pointer selects a read. No unref body, other table entry, raw
payload, arbitrary-address CLI, original execution, runtime/estimator import,
external fetch or shared-reader/authenticator modification.
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
TABLE_ROOT, SIGNED_STATE, ENTRY_WIDTH = 0x802d6f98, 3, 4
DESCRIPTOR_ROOT, DESCRIPTOR_ROW, DESCRIPTOR_STRIDE = 0x8036f644, 0, 0x1c
RELEASE_OFFSET = 0x18
RANGES = (
    (0x8007e678, 32, '3e7f2e5665b4173038c13f23df183d62e6483e1258dff141a07504568b6ef994'),
    (0x80088e50, 328, 'c747b919f60eaad0d8b255db2b1fdc9ecb0bd22cea33c4930d1085dcdf34d3f4'),
    (0x80089444, 272, '662fe9d92fabf618cf21cc81fdcc266d090bda7b674bc9ad28266a89be6e2bf2'),
    (0x80006d80, 72, 'af3ef03d2ff4dfbd26b5e33794ffac72543f7b6b70aaa2a0c7f7af14cdf13768'),
    (0x80197ad8, 188, 'e3650544ce98694f5c3a5ca208c4dfe1479fbc02f46712a3a8a75d8d210c9082'),
    (0x80089814, 132, '1bb689f99364d17b27d89cf9d15ceb89ffde7be29dc90d4bba30b495975710dd'),
    # Second-stage selection: independent C/index/map extent, after scalar report.
    (0x80006ed8, 68, 'cedb8b8e89d09bc76af3e72117c07093a720afee20d40d3d397737a9353c2492'),
)
CELLS = (
    ('cleanup-state3', 0x802d6fa4, 4, 0x8007e678,
     'a6c03f0cd98471891b5199d09bdedc269455f2281a76e92818c15baaef0ed389'),
    ('descriptor0-release-callback', 0x8036f65c, 4, 0x80006ed8,
     '6146361b1fa0fc8c864ab07ecfd5700f34b9dee55187fc418c57c1403c63a484'),
)
REUSED_EVIDENCE = (
    dict(address='8008aff0', width=32,
         sha256='8ea8cac06c446278fad05cfae1dbe3ee6b3a321f4bfd1168269ce88283bef951',
         source='projectile-callback-evidence-2026-11-14.md', read_here=False,
         purpose='upstream retirement marker helper, not a call in cleanup'),
    dict(address='80197bec', width=20,
         sha256='cdcbfde48212824dc444a6b18aab2c256ffdcb4fec35ad9a18b332b9529c0995',
         source='object-allocator-evidence-2026-11-14.md', read_here=False,
         purpose='signed16 descriptor free-count load, row stride1c'),
    dict(address='80197bd8', width=20,
         sha256='8a8dd5a501652fd1370ed64d05ed17044aada0fa4bf21eecf6b6f13f0809eaea',
         source='object-allocator-evidence-2026-11-14.md', read_here=False,
         purpose='low16 descriptor free-count store, r3 returns low32(type*28)'),
)

# Complete control-flow inventory, independent of decoded payloads. Branch rows
# carry pc, mnemonic, target, BO, BI. Calls/returns include all fixed flags below.
FLOW = {
    0x80006ed8: (
        (0x80006ef4, 'bc', '80006f04', 12, 2),
        (0x80006ef8, 'bl', '8024fd74', None, None),
        (0x80006f18, 'blr', None, 20, 0)),
    0x8007e678: (
        (0x8007e684, 'bl', '80088e50', None, None),
        (0x8007e694, 'blr', None, 20, 0)),
    0x80088e50: (
        (0x80088e78, 'bc', '80088f74', 12, 2),
        (0x80088e88, 'bc', '80088ec4', 4, 2),
        (0x80088e90, 'bc', '80088ec4', 4, 2),
        (0x80088ec0, 'b', '80088f2c', None, None),
        (0x80088ec8, 'bc', '80088ef4', 4, 2),
        (0x80088ed0, 'bc', '80088ef4', 12, 2),
        (0x80088ef0, 'b', '80088f2c', None, None),
        (0x80088ef8, 'bc', '80088f24', 12, 2),
        (0x80088f00, 'bc', '80088f24', 4, 2),
        (0x80088f20, 'b', '80088f2c', None, None),
        (0x80088f34, 'bc', '80088f74', 12, 2),
        (0x80088f3c, 'bl', '80089444', None, None),
        (0x80088f48, 'b', '80088f64', None, None),
        (0x80088f54, 'bc', '80088f5c', 12, 2),
        (0x80088f58, 'bl', '80006d80', None, None),
        (0x80088f70, 'bc', '80088f4c', 12, 0),
        (0x80088f78, 'bl', '80089814', None, None),
        (0x80088f94, 'blr', None, 20, 0)),
    0x80089444: (
        (0x80089450, 'bclr', None, 12, 2),
        (0x80089460, 'bc', '8008947c', 12, 2),
        (0x80089478, 'b', '800894d8', None, None),
        (0x80089480, 'bc', '8008949c', 12, 2),
        (0x80089498, 'b', '800894d8', None, None),
        (0x800894a0, 'bc', '800894c4', 12, 2),
        (0x800894c0, 'b', '800894d8', None, None),
        (0x800894dc, 'bc', '800894f8', 4, 2),
        (0x800894e4, 'bc', '800894f8', 4, 2),
        (0x800894f4, 'b', '80089540', None, None),
        (0x800894fc, 'bc', '80089518', 4, 2),
        (0x80089504, 'bc', '80089518', 12, 2),
        (0x80089514, 'b', '80089540', None, None),
        (0x8008951c, 'bc', '80089538', 12, 2),
        (0x80089524, 'bc', '80089538', 4, 2),
        (0x80089534, 'b', '80089540', None, None),
        (0x80089550, 'blr', None, 20, 0)),
    0x80006d80: (
        (0x80006d9c, 'bc', '80006dac', 12, 2),
        (0x80006da0, 'bl', '8024fd74', None, None),
        (0x80006db0, 'bl', '80197ad8', None, None),
        (0x80006dc4, 'blr', None, 20, 0)),
    0x80197ad8: (
        (0x80197af4, 'bc', '80197b78', 12, 2),
        (0x80197b18, 'bc', '80197b24', 12, 2),
        (0x80197b20, 'bctrl', None, 20, 0),
        (0x80197b30, 'bc', '80197b3c', 12, 2),
        (0x80197b38, 'b', '80197b40', None, None),
        (0x80197b44, 'bc', '80197b4c', 12, 2),
        (0x80197b64, 'bl', '80197bec', None, None),
        (0x80197b74, 'bl', '80197bd8', None, None),
        (0x80197b90, 'blr', None, 20, 0)),
    0x80089814: (
        (0x80089830, 'bc', '80089854', 4, 2),
        (0x80089850, 'b', '80089868', None, None),
        (0x80089894, 'blr', None, 20, 0)),
}


def expected_flow(address):
    rows = []
    for pc, name, target, bo, bi in FLOW[address]:
        row = dict(address=f'{pc:08x}', mnemonic=name)
        if target is not None:
            row.update(target=target, AA=0, LK=int(name == 'bl'))
        if bo is not None:
            row.update(BO=bo, BI=bi, LK=int(name == 'bctrl'))
        if name in ('blr', 'bclr', 'bctrl'):
            row['BH'] = 0
        rows.append(row)
    return rows


def decode_selected(word, pc):
    """All admitted bits exposed or fixed, without changing shared decoders."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 31 and xo in (151, 279, 407):
        c.require(rc == 0, 'reserved indexed Rc')
        name, reg = {151: ('stwx', 'rS'), 279: ('lhzx', 'rD'), 407: ('sthx', 'rS')}[xo]
        return dict(mnemonic=name, **{reg: d}, rA=a, rB=b)
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 2), (12, 0), (12, 2)),
                  'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op == 19 and xo == 16:
        c.require(b == 0 and rc == 0 and (d, a) in ((20, 0), (12, 2)),
                  'unselected return form')
        return dict(mnemonic='blr' if (d, a) == (20, 0) else 'bclr', BO=d, BI=a, BH=0, LK=0)
    decoded = normal.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'stw', 'lwz', 'lbz', 'stb', 'or', 'extsb', 'cmpi',
               'cmpli', 'cmp', 'addis', 'addi', 'mulli', 'rlwinm', 'add', 'lwzx',
               'b', 'bl', 'mtlr', 'mtctr', 'bctrl'}
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
               ('bc', 'b', 'bl', 'blr', 'bclr', 'bctrl')] == expected_flow(address),
              'complete control-flow mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('bc', 'b')),
              'branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def cell_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'cell integer fields')
    selected = [item for item in CELLS if item[1:3] == (address, width)]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    label, _, _, target, expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(width == 4 and address % 4 == 0 and start <= address < address + width <= end,
              'cell alignment/width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'cell byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected, 'cell digest mismatch')
    actual = c.integer(raw, 0, 'I')
    c.require(actual == target, 'cell target mismatch')
    return dict(label=label, address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, target=f'{actual:08x}', sha256=digest, spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    maps = [normal.mapping_evidence(blocks, subs, image, m) for m in (TEXT_MAPPING, DATA3_MAPPING)]
    text, data3 = [item[0] for item in maps]
    c.require(TABLE_ROOT + SIGNED_STATE * ENTRY_WIDTH == 0x802d6fa4, 'fixed state3 derivation')
    c.require(DESCRIPTOR_ROOT + DESCRIPTOR_ROW * DESCRIPTOR_STRIDE + RELEASE_OFFSET == 0x8036f65c,
              'fixed descriptor0 callback derivation')
    cells = [cell_evidence(db, data3, pc, width) for _, pc, width, _, _ in CELLS]
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    c.require(cells[0]['target'] == ranges[0]['address'],
              'cell target differs from independently selected candidate')
    c.require(cells[1]['target'] == ranges[6]['address'],
              'callback target differs from independently selected body')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[item[1] for item in maps],
        cells=cells, ranges=ranges,
        function_coverage=[dict(entry=f'{pc:08x}', end_exclusive=f'{pc + width:08x}', selected_width=width,
            represented_instructions=width // 4, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis=('independent adjacent C/index entries; no named map extent' if pc == 0x8007e678
                          else 'named C/index identity and exact map size'),
            map_size=None if pc == 0x8007e678 else width) for pc, width, _ in RANGES],
        selection_basis=dict(table='802d6f98', index_field='signed child+0x18', selected_state=3,
            cell='802d6fa4', entry_width=4, independent_candidate='8007e678',
            candidate_end_exclusive='8007e698', target_equals_independent_candidate=True,
            descriptor_row='8036f644', descriptor_type=0, descriptor_stride=28, release_offset=24,
            release_cell='8036f65c', release_callback='80006ed8', release_callback_body_read=True, callback_extent_independently_selected=True,
            unref_body_read=False, pointer_following=False, reads=9, bytes=1100,
            reused_helpers_read=False, other_state_cells_read=False),
        reused_evidence=list(REUSED_EVIDENCE),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All273 selected instructions represented. '
            'Cleanup performs group unlink, optional draw unlink and descriptor teardown, then object '
            'pool return in source order. Descriptor0 callback18 is NONNULL80006ed8; its authenticated body '
            'rereads descriptor0c, conditionally calls unselected JObjUnref8024fd74, clears0c after '
            'that call returns, and returns0. Effects after unresolved Unref require its successful '
            'return; do not claim complete teardown across that boundary. Group=-1 or '
            'type4 can skip descriptor work. Pool return preserves child r3, clears active0/next4 only '
            'after unsigned16 count update; it does not clear state18 or child descriptor slots.')


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
