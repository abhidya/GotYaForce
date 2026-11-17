#!/usr/bin/env python3
"""Fixed complete 8005b98c sound-event helper and five named scalar witnesses.

Read-only stdlib. Snapshot/schema/language/File Bytes/maps and source-extent
identity precede independent literal selections. No sound-table payload,
pointer following, phase-one evidence, raw export, execution or shared edits.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import struct
import sys

import read_archived_double_action_evidence as double
import read_archived_actor_normal_evidence as normal
import read_archived_command_evidence as command
import read_archived_constants as c

TEXT_MAPPING = double.TEXT_MAPPING
DATA5_MAPPING = double.DATA5_MAPPING
RANGES = ((0x8005b98c, 300, 'e2da8d687aa2b5cadc9c8159e24ec46a1bd81ad0b331d575715a359780f0ddb7'),)
CONSTANTS = (
    (0x804373e4, '00000000', 'frame-zero'),
    (0x80437418, '4330000000000000', 'unsigned-integer-conversion-double'),
    (0x8043740c, '3f333333', 'scale-lower-threshold'),
    (0x80437410, '40000000', 'scale-upper-threshold'),
    (0x80437404, '3e4ccccd', 'kind2-kind3-call-f1'),
)
SOURCE_FILES = (
    ('research/symbols/GG4E-CSM-20220412.map',
     '7dadd7e766ca73bc0db66a9920f22e349d1c91a3d6525de3f791404f275f237d'),
    ('research/decomp/ghidra-export/chunk_0007.c',
     '083e4282487e48708b0387ee4bb4c9cc7371546c2c3d4f9ad98d57316eccc3f4'),
)


def source_extent_evidence():
    """Only named markers and map row establish extent; C body is not an oracle."""
    root = Path(__file__).resolve().parents[3]
    contents = []
    for relative, digest in SOURCE_FILES:
        raw = (root / relative).read_bytes()
        c.require(hashlib.sha256(raw).hexdigest() == digest, 'source extent file digest mismatch')
        contents.append(raw.decode('utf-8'))
    rows = contents[0].splitlines()
    expected = '8005b98c 0000012c 8005b98c 0 zz_005b98c_'
    c.require(len(rows) >= 718 and rows[717] == expected and rows.count(expected) == 1,
              'source extent map row mismatch')
    markers = [(i, int(pc, 16)) for i, line in enumerate(contents[1].splitlines(), 1)
               if (match := re.fullmatch(r'// ==== ([0-9a-f]{8})  .* ====', line))
               for pc in [match.group(1)]]
    hits = [i for i, (_, pc) in enumerate(markers) if pc == 0x8005b98c]
    c.require(len(hits) == 1 and hits[0] + 1 < len(markers), 'source entry marker mismatch')
    entry, following = markers[hits[0]], markers[hits[0] + 1]
    c.require(following[1] == 0x8005bab8, 'source next marker mismatch')
    return dict(map_file=SOURCE_FILES[0][0], map_sha256=SOURCE_FILES[0][1], map_row=718,
                map_size=300, chunk_file=SOURCE_FILES[1][0], chunk_sha256=SOURCE_FILES[1][1],
                entry_marker_line=entry[0], next_marker_line=following[0],
                entry='8005b98c', end_exclusive='8005bab8',
                caveat='Source files establish named extent only; all instruction facts come from archive bytes.')


def decode_selected(word, pc):
    """Observed PPC forms, including the initial unordered equality compare."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    if word >> 26 == 63 and (word >> 1) & 1023 == 0:
        c.require((word >> 21) & 31 == 0 and word & 1 == 0,
                  'unselected unordered floating-comparison fields')
        return dict(mnemonic='fcmpu', BF=0, fA=(word >> 16) & 31, fB=(word >> 11) & 31)
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


def constant_evidence(db, mapping, address):
    c.require(type(address) is int, 'constant integer fields')
    selected = [item for item in CONSTANTS if item[0] == address]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    _, bits, label = selected[0]
    width = len(bits) // 2
    start, end, _, _, _, length, root = mapping
    c.require(width in (4, 8) and address % width == 0 and start <= address < address + width <= end,
              'constant alignment/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == bits, 'constant bits mismatch')
    return dict(address=f'{address:08x}', label=label, width=width, bits=raw.hex(),
                value=struct.unpack('>f' if width == 4 else '>d', raw)[0],
                sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    source_extent = source_extent_evidence()
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
        source_extent=source_extent,
        ranges=[range_evidence(db, text, pc, width) for pc, width, _ in RANGES],
        constants=[constant_evidence(db, data5, pc) for pc, _, _ in CONSTANTS],
        function_coverage=[dict(entry='8005b98c', end_exclusive='8005bab8', selected_width=300,
            represented_instructions=75, unrepresented_instructions=0, unrepresented_ranges=[], map_size=300,
            extent_basis='authenticated map row718, adjacent named C markers and terminal return')],
        conditional_calls=[dict(site=site, target=target, condition=condition) for site, target, condition in (
            ('8005ba54', '800f036c', 'frame gate passes and unsigned kind byte is zero'),
            ('8005ba94', '800f036c', 'frame gate passes and unsigned kind byte is one'),
            ('8005baa4', '800f061c', 'frame gate passes and unsigned kind byte is two or three'))],
        float_preconditions=dict(FPSCR_RN=0, FPSCR_NI=0, finite_inputs_and_results_required=True,
            caveat='Bounded host preconditions, not authenticated live register state.'),
        recorded_bases=dict(r2='8043ea20',
            caveat='Previously recorded base, not freshly authenticated startup or live register state.'),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, live dispatch, '
            'numerical parity, integration or playable-game proof. All 75 instructions and operands are '
            'represented, including the unreachable 8005ba3c branch. No sound-table payload or phase-one '
            'selection. All new addresses are independent literals; external callees remain boundaries.')


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
