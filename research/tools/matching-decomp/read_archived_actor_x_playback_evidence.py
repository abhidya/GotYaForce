#!/usr/bin/env python3
"""Fixed cue44 dispatch cell, X playback handler and one ground helper.

Read-only stdlib. Authenticate both known complete snapshots before two fixed
pointer cells, one two-byte row and two independently source-bounded text spans. No arbitrary selection,
pointer following, raw-range output, execution or shared allowlist changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_actor_normal_evidence as normal
import read_archived_command_evidence as command
import read_archived_constants as c

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
# Neither pointer cell determines a code or data selection.
CELLS = (
    ('signed-cue44', 0x802d33b0, 0x80059cd0,
     '3444a28cf2b80ab10b57c6aa3d926c09984284298a8ba75776022e6ef19058ff'),
    ('double-constructor-4f0-source', 0x802d3b50, 0x802d3ff8,
     '27b683898f029efc9c3c6c9e780fbb1e9cfd13387ebdba9e0443e733c076a0d5'),
)
# Independent recorded family cue table/row, never selected by a returned pointer.
ROWS = (
    (0x802d4050, 2, 61, 0, 'e7dac261e841e53eb65ac8c2a0e56544df49c46d71e8002d7764f92c66c4c868'),
)
# Independent named C markers precede all payload selections. Neither has a
# symbol-map row. Returns and internal branches authenticate these exact spans.
RANGES = (
    (0x80059cd0, 352, '52f4647dff3c3fd9cf6f26f6d9934465f5caad5a1a4487f6add64c6bbce14fea'),
    (0x800690a0, 160, '1a318a9de9150de8569ecb76c144241d23a41c69a7fcd668f4752ff51657587b'),
)


def decode_selected(word, pc):
    """Observed scalar forms only; preserve every operand and condition field."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 19 and xo == 16:
        c.require(word == 0x4e800020, 'unselected branch-register form')
        return dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0)
    if op == 18:
        c.require(word & 2 == 0, 'unselected absolute branch')
        return dict(mnemonic='bl' if rc else 'b',
                    target=f'{(pc + normal.signed(word & 0x3fffffc, 26)) & 0xffffffff:08x}',
                    AA=0, LK=rc)
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 2), (12, 2)),
                  'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op == 11:
        c.require(d == 0, 'unselected comparison fields')
        return dict(mnemonic='cmpi', BF=0, L=0, rA=a,
                    immediate=normal.signed(word & 65535, 16))
    if op == 14:
        return dict(mnemonic='addi', rD=d, rA=a, immediate=normal.signed(word & 65535, 16))
    if op == 21:
        return dict(mnemonic='rlwinm', rS=d, rA=a, SH=b,
                    MB=(word >> 6) & 31, ME=(word >> 1) & 31, Rc=rc)
    if op == 24:
        return dict(mnemonic='ori', rS=d, rA=a, immediate=word & 65535)
    if op in (32, 34, 36, 37, 38):
        name, reg = {32: ('lwz', 'rD'), 34: ('lbz', 'rD'), 36: ('stw', 'rS'),
                     37: ('stwu', 'rS'), 38: ('stb', 'rS')}[op]
        c.require(op != 37 or a != 0, 'reserved store-update base')
        return dict(mnemonic=name, **{reg: d}, rA=a,
                    displacement=normal.signed(word & 65535, 16))
    if op == 31:
        if xo in (339, 467):
            c.require(d == 0 and ((b << 5) | a) == 8 and rc == 0,
                      'unselected link-register form')
            return dict(mnemonic='mflr', rD=0) if xo == 339 else dict(mnemonic='mtlr', rS=0)
        if xo == 444:
            return dict(mnemonic='or', rS=d, rA=a, rB=b, Rc=rc)
    return None


def cell_evidence(db, mapping, address):
    c.require(type(address) is int, 'cell integer fields')
    selected = [item for item in CELLS if item[1] == address]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    label, _, target, expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == 0 and start <= address < address + 4 <= end, 'cell alignment/bounds')
    raw, spans = db.chain(root, address - start, 4, length)
    c.require(len(raw) == 4, 'cell byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected, 'cell digest mismatch')
    actual = c.integer(raw, 0, 'I')
    c.require(actual == target, 'cell target mismatch')
    return dict(label=label, address=f'{address:08x}', width=4,
                target=f'{actual:08x}', sha256=digest, spans=spans)


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
        c.require(decoded is not None, 'unselected instruction in fixed span')
        instructions.append(dict(address=f'{pc:08x}', **decoded))
    c.require(instructions[-1]['mnemonic'] == 'blr', 'span terminal return mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('b', 'bc')),
              'non-call branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, spans=spans, instructions=instructions)


def row_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'row integer fields')
    selected = [item for item in ROWS if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'row not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    _, _, full, upper, expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(width == 2 and address % 2 == 0 and start <= address < address + width <= end,
              'row alignment/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'row byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected, 'row digest mismatch')
    c.require((raw[0], raw[1]) == (full, upper), 'row values mismatch')
    return dict(address=f'{address:08x}', width=width, full_body_state=raw[0],
                upper_body_state=raw[1], sha256=digest, spans=spans)


def inspect(data, digest):
    # Actual whole SHA/schema/language/metadata/File Bytes/maps/data5 controls
    # precede every new selection, including both cells and the fixed cue row.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, text_fact = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data3, data3_fact = normal.mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[text_fact, data3_fact],
                cells=[cell_evidence(db, data3, address) for _, address, _, _ in CELLS],
                rows=[row_evidence(db, data3, address, width) for address, width, _, _, _ in ROWS],
                ranges=[range_evidence(db, text, address, width) for address, width, _ in RANGES],
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                                        selected_width=width, represented_instructions=width // 4,
                                        unrepresented_instructions=0, unrepresented_ranges=[],
                                        extent_basis='named C markers and authenticated return', map_size=None)
                                   for address, width, _ in RANGES],
                caveat='Archived ProgramDB static evidence only, not unchanged original-DOL, '
                       'live dispatch, actor ownership, runtime integration or behavioral parity. '
                       'All 128 instructions in the two fixed spans are represented. Neither '
                       'function has a symbol-map row. The separately fixed Double 4f0 producer '
                       'cell points to the independently recorded cue table 802d3ff8; exactly '
                       'its independently fixed cue44 row 802d4050 is selected as states 61/0. '
                       'No other table cell or row is read. The constructor schedule remains '
                       'separate existing evidence, not newly selected code. Callee bodies '
                       'other than the independently selected 800690a0 '
                       'are outside this reader, including cue setter 8006a750 and reset '
                       '8005c080. Bit40-set air helpers are ordered call boundaries, not no-ops. '
                       'No values returned from the cell or a decoded call select any read.')


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
