#!/usr/bin/env python3
"""Fixed height-plus-normal query and actor-ground archived evidence.

Read-only stdlib. Two independently named complete instruction spans and five
instruction-named scalars, after whole-source/schema/language/File Bytes/map
authentication. No arbitrary addresses, broad payloads, pointer following,
instruction execution, or modifications to a shared reader's allowlists.
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
DATA5_MAPPING = double.DATA5_MAPPING
RANGES = (
    (0x8003e0a8, 844, '4310809c29ad48750521ad16c4e2f47192b2c69b1d3dc357d613870af21d1708'),
    (0x800677b0, 544, '09ab80886742547a9862056d729a3b23984007549f8cd636ea2d5cf3e63bf246'),
)
CONSTANTS = (
    (0x8043702c, 'c59c4000', 'outside-height'),
    (0x804375f8, '2edbe6fe', 'displacement-squared-threshold'),
    (0x804375d4, '3f666666', 'steep-slope-damping'),
    (0x80437600, '3fe0000000000000', 'sqrt-refinement-half'),
    (0x80437608, '4008000000000000', 'sqrt-refinement-three'),
)
MAP_SIZES = {0x800677b0: 544}
# Existing independently authenticated evidence, not new reads and never
# selected from a decoded branch/pointer. The focused tests check the references.
REUSED_RANGES = (
    ('terrain_query', 0x8003f320, 872, '559b34375add13a9156ac4437abc9633cb1f52dcb53817a21c5b95ca3ee4cb1a'),
    ('terrain_query', 0x8003fa68, 152, 'a8447bcc787bb143584b40bf66dde650f1d635c841eb1948b95fb421f8a57c8a'),
    ('terrain_query', 0x8003fb00, 88, '333885e9781b90d779a3a3056c414854cac154f64352ef15cf25aa8fec76b908'),
    ('double_action', 0x8020ba78, 36, '5997a5a32c7df8eb2a03901039345f35a84f00b017545800218ef21bdbfaf81a'),
    ('double_action', 0x8020ba9c, 28, 'e0fbf8bbb6f184d7b21d322b68975adca6dc652510963c83c95b9ceb63e0671d'),
    ('double_action', 0x8020ba54, 36, 'c7b35d4075874e063982faa1d7d086e5d5ec4d70aed2b56c619b5e440e18e1ab'),
    ('double_action', 0x800ff30c, 268, '72404d4312c0508eb0b293dcfc9a338bbdbad9f719b1a4fedc7cf217c2904f97'),
)
REUSED_CONSTANTS = (
    ('terrain_query', 0x80436f68, '00000000'),
    ('terrain_query', 0x80436f88, '4330000080000000'),
    ('terrain_query', 0x80436ffc, '43fa0000'),
    ('terrain_query', 0x80437034, 'c5ea6000'),
    ('terrain_query', 0x80437038, '45ea6000'),
    ('terrain_query', 0x80436f70, 'bf000000'),
    ('terrain_orientation', 0x80436f78, '3f800000'),
    ('actor_ceiling', 0x804375d0, '00000000'),
)


def decode_selected(word, pc):
    """Every operand of observed forms, including record and condition fields."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 63:
        if xo == 0:
            c.require(d == rc == 0, 'unselected floating-comparison fields')
            return dict(mnemonic='fcmpu', BF=0, fA=a, fB=b)
        if xo in (12, 26):
            c.require(a == rc == 0, 'reserved floating-unary fields')
            return dict(mnemonic='frsp' if xo == 12 else 'frsqrte', fD=d, fB=b, Rc=0)
        if (xo & 31) == 25:
            c.require(b == rc == 0, 'reserved double-multiply fields')
            return dict(mnemonic='fmul', fD=d, fA=a, fC=fc, Rc=0)
        if (xo & 31) == 30:
            c.require(rc == 0, 'reserved fused-negative-multiply-subtract fields')
            return dict(mnemonic='fnmsub', fD=d, fA=a, fC=fc, fB=b, Rc=0)
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
        constants=[constant_evidence(db, data5, pc) for pc, _, _ in CONSTANTS],
        function_coverage=[dict(entry=f'{pc:08x}', end_exclusive=f'{pc+width:08x}', selected_width=width,
            represented_instructions=width//4, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='adjacent named C markers, map size and authenticated return' if pc in MAP_SIZES
                else 'adjacent named C markers and authenticated return', map_size=MAP_SIZES.get(pc))
            for pc, width, _ in RANGES],
        reused_evidence=dict(
            ranges=[dict(reader=f'read_archived_{reader}_evidence.py', address=f'{pc:08x}', width=width,
                sha256=sha) for reader, pc, width, sha in REUSED_RANGES],
            constants=[dict(reader=f'read_archived_{reader}_evidence.py', address=f'{pc:08x}', bits=bits)
                for reader, pc, bits in REUSED_CONSTANTS],
            caveat='Prior exact fixed witnesses; not selected or decoded again by this reader. '
                'The prior terrain-query reader omits only its link-register save/restore instructions.'),
        float_preconditions=dict(FPSCR_RN=0, FPSCR_NI=0, GQR0_load_type=0, GQR0_store_type=0,
            GQR0_load_scale=0, GQR0_store_scale=0, finite_inputs_and_results_required=True,
            caveat='Bounded host preconditions, not authenticated live register state. '
                'Decoding frsqrte/refinement does not supply numerical emulation.'),
        recorded_bases=dict(r2='8043ea20', r13='8043b5a0',
            caveat='Previously recorded bases, not freshly authenticated startup or live register state.'),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, live dispatch, '
            'numerical parity, full contact/action playback, integration or playable-game proof. Every selected '
            'instruction and operand is represented. External callees remain boundaries. New literal selections '
            'are independent of decoded pointers. No terrain/actor/pointer-global payloads are selected.')


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
