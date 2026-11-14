#!/usr/bin/env python3
"""Fixed outer-frame evidence: five complete bodies /1080 bytes.

Read-only stdlib. Unchanged full archive/schema/mapping authentication precedes
exactly five fixed code selections. No selected data cells, pointer following,
arbitrary-address CLI, raw payload output, original execution or runtime imports.
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
    (0x80029434, 320, '6b951fb1955f3acb931beff0831af002d9b6ff9b108a15796a3114b5020b1b6c'),
    (0x8008b048, 68, 'f301aa22755c8f9c590db04552e1461969fbdb7f0df11c62b225eed6b77c264d'),
    (0x8008b010, 40, '979ef724f8f7c5c40352c666b8676668553d3f5333961b61443f2eafbb5b7b8e'),
    (0x80029d48, 336, 'cafbf7ba2143ecf749bfec6a51d4d7525da518e34836b42c07e591009d47feb0'),
    (0x80029e98, 316, 'b6a32d4c3b5911b5974991cf21f060fc128e48d8116cabb0c96f146cdaeae450'),
)
# Independent, complete source control-flow inventory.
FLOW = {
    0x80029434: (
        (0x80029440, 'bl', '8008b048', None, None),
        (0x80029444, 'bl', '80029d48', None, None),
        (0x80029454, 'bc', '80029464', 4, 2),
        (0x80029458, 'bl', '80053b30', None, None),
        (0x8002945c, 'bl', '8006ae60', None, None),
        (0x80029460, 'bl', '80027764', None, None),
        (0x80029464, 'bl', '8000bef4', None, None),
        (0x80029474, 'bc', '800294b8', 4, 2),
        (0x8002947c, 'bl', '80089a94', None, None),
        (0x80029484, 'bl', '80089a94', None, None),
        (0x80029488, 'bl', '80053a2c', None, None),
        (0x8002948c, 'bl', '80087cf0', None, None),
        (0x80029494, 'bl', '80089a94', None, None),
        (0x8002949c, 'bl', '80089a94', None, None),
        (0x800294a4, 'bl', '80089a94', None, None),
        (0x800294ac, 'bl', '80089a94', None, None),
        (0x800294b4, 'bl', '80089898', None, None),
        (0x800294bc, 'bl', '80089898', None, None),
        (0x800294c4, 'bl', '80089898', None, None),
        (0x800294c8, 'bl', '80089554', None, None),
        (0x800294e8, 'bc', '800294f8', 4, 2),
        (0x800294ec, 'bl', '8008a28c', None, None),
        (0x800294f0, 'bl', '80089aec', None, None),
        (0x800294f4, 'bl', '8002bb14', None, None),
        (0x800294f8, 'bl', '80036e24', None, None),
        (0x800294fc, 'bl', '8008972c', None, None),
        (0x80029500, 'bl', '80089658', None, None),
        (0x80029510, 'bc', '80029520', 4, 2),
        (0x80029514, 'bl', '80053a94', None, None),
        (0x8002951c, 'bl', '80089898', None, None),
        (0x8002952c, 'bc', '80029534', 12, 2),
        (0x80029530, 'bl', '8000bda4', None, None),
        (0x80029540, 'bc', '80029548', 12, 2),
        (0x80029544, 'bl', '80040b94', None, None),
        (0x80029548, 'bl', '800eff30', None, None),
        (0x80029570, 'blr', None, 20, 0)),
    0x8008b048: (
        (0x8008b060, 'bc', '8008b070', 12, 2),
        (0x8008b06c, 'bl', '8008b010', None, None),
        (0x8008b088, 'blr', None, 20, 0)),
    0x8008b010: (
        (0x8008b01c, 'bclr', None, 4, 0),
        (0x8008b024, 'bclr', None, 12, 0),
        (0x8008b034, 'blr', None, 20, 0)),
    0x80029d48: (
        (0x80029d6c, 'bl', '80029e98', None, None),
        (0x80029d78, 'bc', '80029e70', 4, 1),
        (0x80029d84, 'bc', '80029e4c', 12, 2),
        (0x80029d90, 'bl', '8008b290', None, None),
        (0x80029d98, 'bc', '80029e70', 4, 2),
        (0x80029d9c, 'bl', '8008b480', None, None),
        (0x80029da4, 'bc', '80029db8', 12, 2),
        (0x80029db4, 'bc', '80029e70', 12, 2),
        (0x80029dc8, 'bc', '80029de0', 12, 1),
        (0x80029ddc, 'b', '80029e70', None, None),
        (0x80029e48, 'b', '80029e70', None, None),
        (0x80029e58, 'bc', '80029e68', 12, 0),
        (0x80029e64, 'b', '80029e70', None, None),
        (0x80029e7c, 'bc', '80029d68', 12, 0),
        (0x80029e94, 'blr', None, 20, 0)),
    0x80029e98: (
        (0x80029ee8, 'bc', '80029f4c', 12, 2),
        (0x80029f04, 'bc', '80029f4c', 4, 2),
        (0x80029f24, 'bc', '80029f34', 12, 2),
        (0x80029f64, 'bc', '80029fc8', 12, 2),
        (0x80029f80, 'bc', '80029fc8', 4, 2),
        (0x80029fa0, 'bc', '80029fb0', 12, 2),
        (0x80029fcc, 'bc', '80029ed4', 16, 0),
        (0x80029fd0, 'blr', None, 20, 0)),
}
REUSED_EVIDENCE = (
    dict(address='80089898', width=228,
         sha256='126a25b8262b9ec16da7e6121fd72318cce3c39faab481f718d2a559307c1299',
         source='object-scheduler-evidence-2026-11-14.md', read_here=False),
    dict(address='80089a94', width=88,
         sha256='dcb8bf7edce7313e0e258ee526af82153e5e35eac0987938a42cccc6a270dde4',
         source='object-scheduler-evidence-2026-11-14.md', read_here=False),
)


def expected_flow(address):
    rows = []
    for pc, name, target, bo, bi in FLOW[address]:
        row = dict(address=f'{pc:08x}', mnemonic=name)
        if target is not None:
            row.update(target=target, AA=0, LK=int(name == 'bl'))
        if bo is not None:
            row.update(BO=bo, BI=bi, LK=0)
        if name in ('blr', 'bclr'):
            row['BH'] = 0
        rows.append(row)
    return rows


def decode_selected(word, pc):
    """Every admitted bit represented or fixed; shared decoders unchanged."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 19 and xo == 16:
        c.require((word >> 13) & 7 == 0 and b == 0 and rc == 0 and
                  (d, a) in ((20, 0), (4, 0), (12, 0)), 'unselected branch-register form')
        return dict(mnemonic='blr' if d == 20 else 'bclr', BO=d, BI=a, BH=0, LK=0)
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 1), (4, 2), (12, 0), (12, 1), (12, 2), (16, 0)),
                  'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op == 40:
        return dict(mnemonic='lhz', rD=d, rA=a, displacement=normal.signed(word & 65535, 16))
    if op == 31 and xo in (24, 215):
        if xo == 215:
            c.require(rc == 0, 'reserved indexed-store bit')
            return dict(mnemonic='stbx', rS=d, rA=a, rB=b)
        return dict(mnemonic='slw', rS=d, rA=a, rB=b, Rc=rc)
    if op == 31 and xo == 32:
        c.require(d == rc == 0, 'unselected unsigned comparison fields')
        return dict(mnemonic='cmpl', BF=0, L=0, rA=a, rB=b)
    if op == 59 and (xo & 31) == 18:
        c.require(fc == rc == 0, 'reserved fdivs fields')
        return dict(mnemonic='fdivs', fD=d, fA=a, fB=b)
    decoded = normal.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'stw', 'lwz', 'lbz', 'stb', 'sth', 'or', 'and',
               'extsb', 'extsh', 'cmpi', 'cmpli', 'cmp', 'addis', 'addi', 'rlwinm', 'add',
               'lbzx', 'b', 'bl', 'bc', 'mtlr', 'mtctr', 'blr', 'xoris',
               'lha', 'lfd', 'fsubs', 'fmuls', 'fctiwz', 'stfd'}
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
               ('bc', 'b', 'bl', 'blr', 'bclr')] == expected_flow(address),
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
        selection_basis=dict(reads=5, bytes=1080, selected_data_cells=0, pointer_following=False,
            reused_helpers_read=False, global_payloads_read=False, callback_bodies_read=False,
            owner_pointer='r13-31852', participant_owner_pointer='r13-31856',
            owner_C_name='PTR_DAT_80433934', owner_runtime_value_established=False,
            unresolved_calls=('8008b290', '8008b480'), floating_constants_read=False),
        reused_evidence=list(REUSED_EVIDENCE),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All270 selected instructions represented. '
            'Outer first calls request consumer8b048 then four-team refresh29d48. '
            'Burst-active populated team clears charged0f before unresolved8b290. '
            'After normal refresh return, mode0 reaches53b30; nonzero mode reachesbef4. '
            'No scheduler call is safely reachable through those unresolved predecessors. '
            'Source later schedules wrappers40,32,0,16,8,24, then singles56,58,57 and conditionally59. '
            'Global owner/participant pointers, table payloads,8b290/8b480 and FP constants are unselected.')

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
