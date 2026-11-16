#!/usr/bin/env python3
"""Fixed actor-frame suffix evidence from two existing archived ProgramDBs.

Read-only stdlib. Whole-file/schema/language/File Bytes/map authentication
precedes three complete literal instruction spans, two constructor cells and
one scalar. No arbitrary addresses, payload following, raw output, execution,
or changes to another reader's allowlists. A nonnull sound pointer is not a
hydrated sound table.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_double_action_evidence as double
import read_archived_actor_normal_evidence as normal
import read_archived_command_evidence as command
import read_archived_constants as c

TEXT_MAPPING = double.TEXT_MAPPING
DATA3_MAPPING = double.DATA3_MAPPING
DATA5_MAPPING = double.DATA5_MAPPING
RANGES = (
    (0x8006f88c, 72, '680c0ec8c71efb08c8f58d754022ce70e08256402c7a34562baa55330e614ab1'),
    (0x80055ee4, 172, 'f9d106d64326e759fd9b72a619c6bde22a12cc53c0c1a7da4ae9e8f1d40c0ca2'),
    (0x8005b880, 268, '4a8f527b8d258953b38ad46c1e5681e3ce20354bc56c7540349d7d2e91660832'),
)
CELLS = (
    ('constructor-posthook4c0', 0x802d3b20, 0x8006f88c,
     'db31181abe0ba833169a9c38254008f88804c913fb1a6376e648cea6661e1229'),
    ('constructor-soundEventTable4e8', 0x802d3b48, 0x802d3ca0,
     '35a3a289b82d0f1c8bec13375bc8f3374fe8355be59fc72bef4277dd84a81e8d'),
)
CONSTANTS = ((0x80437298, '40000000', 'size-product-threshold'),)
MAP_SIZES = {0x80055ee4: 172, 0x8005b880: 268}
# References to independent prior fixed selections, not new reads or pointers
# used to select reads. The ordinary frame is reused from its existing reader.
REUSED_RANGES = (
    ('double_action', 0x8006f7c0, 204, 'e4b751102a00fb7b424274976e8bb1f140fe0807706cd1517078b40dbe3de8dd'),
    ('actor_normal', 0x8006f60c, 252, '201ead69a9e7e0cb04851db5f7498352ebdf5cbecc88be4486e68e2122e3e962'),
    ('actor_mode1', 0x80055568, 292, '4ef4d2db70068dec76e280773b3d58c546452599966914bffd4f8cbaf56472c7'),
)
REUSED_CONSTANTS = (('actor_rotation', 0x804373d0, 8, '4330000080000000'),)


def decode_selected(word, pc):
    """Every observed operand, including conditional LR-return fields."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    if word >> 26 == 19 and (word >> 1) & 1023 == 16 and word != 0x4e800020:
        c.require(word in (0x4c820020, 0x4c810020, 0x4d820020),
                  'unselected conditional LR-return fields')
        return dict(mnemonic='bclr', BO=(word >> 21) & 31, BI=(word >> 16) & 31, BH=0, LK=0)
    return double.decode_selected(word, pc)


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
    c.require(instructions[-1]['mnemonic'] == 'blr', 'span terminal return mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('b', 'bc')),
              'non-call branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


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
    return dict(label=label, address=f'{address:08x}', width=4, target=f'{actual:08x}',
                sha256=digest, spans=spans)


def constant_evidence(db, mapping, address):
    c.require(type(address) is int, 'constant integer fields')
    selected = [item for item in CONSTANTS if item[0] == address]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    _, bits, label = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == 0 and start <= address < address + 4 <= end, 'constant alignment/bounds')
    raw, spans = db.chain(root, address - start, 4, length)
    c.require(len(raw) == 4, 'constant byte width')
    c.require(raw.hex() == bits, 'constant bits mismatch')
    return dict(address=f'{address:08x}', label=label, width=4, bits=raw.hex(),
                value=struct.unpack('>f', raw)[0], sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    maps = [normal.mapping_evidence(blocks, subs, image, m)
            for m in (TEXT_MAPPING, DATA3_MAPPING, DATA5_MAPPING)]
    text, data3, data5 = [item[0] for item in maps]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[item[1] for item in maps],
        ranges=[range_evidence(db, text, pc, width) for pc, width, _ in RANGES],
        cells=[cell_evidence(db, data3, pc) for _, pc, _, _ in CELLS],
        constants=[constant_evidence(db, data5, pc) for pc, _, _ in CONSTANTS],
        function_coverage=[dict(entry=f'{pc:08x}', end_exclusive=f'{pc+width:08x}', selected_width=width,
            represented_instructions=width//4, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='adjacent named C markers, map size and authenticated return' if pc in MAP_SIZES
                else 'prior independently named posthook, authenticated prehook end, next named C marker and terminal return; no C body or map row',
            map_size=MAP_SIZES.get(pc)) for pc, width, _ in RANGES],
        reused_evidence=dict(
            ranges=[dict(reader=f'read_archived_{reader}_evidence.py', address=f'{pc:08x}', width=width,
                sha256=sha) for reader, pc, width, sha in REUSED_RANGES],
            constants=[dict(reader=f'read_archived_{reader}_evidence.py', address=f'{pc:08x}', width=width,
                bits=bits) for reader, pc, width, bits in REUSED_CONSTANTS],
            caveat='Prior independently fixed witnesses; not selected again by this reader.'),
        float_preconditions=dict(FPSCR_RN=0, FPSCR_NI=0, finite_inputs_and_results_required=True,
            caveat='Bounded host preconditions, not authenticated live register state.'),
        recorded_bases=dict(r2='8043ea20', r13='8043b5a0',
            caveat='Previously recorded bases, not freshly authenticated startup or live register state.'),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, live dispatch, '
            'numerical parity, complete frames/actions, integration or playable-game proof. Every selected '
            'instruction and operand is represented. Sound table cell is nonnull; its payload is not read. '
            'No synthetic null or all-minus-one row indices establish retail sound hydration. '
            'External 8005b98c remains a boundary. New literal selections are independent of pointer values.')


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
