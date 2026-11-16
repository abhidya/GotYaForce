#!/usr/bin/env python3
"""Fixed Double prehook, action-two dispatch and phase-zero archived evidence.

Read-only stdlib. Whole-file/schema/language/File Bytes/mapping authentication
precedes literal selections. No arbitrary addresses, pointer following, raw
payload output, execution, or modification of any shared reader allowlist.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys
import read_archived_actor_normal_evidence as normal
import read_archived_actor_mode1_evidence as mode1
import read_archived_command_evidence as command
import read_archived_constants as c

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
DATA4_MAPPING = (0x804335a0, 0x804360c0, 6, 'MAIN_.data4', 6, 11040, 262)
DATA5_MAPPING = mode1.DATA5_MAPPING
# Independent named selections; prehook excludes the omitted-C posthook.
RANGES = (
    (0x8006f7c0, 204, 'e4b751102a00fb7b424274976e8bb1f140fe0807706cd1517078b40dbe3de8dd'),
    (0x8005f238, 4, 'f332ea5b5437103cbb6f1508679da89eec9288ad775c96c439a17fccabe3de8e'),
    (0x80065dfc, 40, 'c594bd68034bba3cc31848d5a87038e876cdfc890c341310c2294b17e0bf21a5'),
    (0x8006facc, 60, '5deeacdae63ecf201429acfbceebbb51b8ef807c1e450b943eec9a6141a564f0'),
    (0x80071598, 60, '4ac9a8f7c2f0b6fbac5305b3c0db122125ccfe4e454ffe8e0924314cd3a7daf9'),
    (0x800715d4, 36, '3cdd2ad074ad5dfab5f9e5817c06a9188420d3d4a0b70c9ce3ce7a8ab0da67ee'),
    (0x800ff2bc, 80, '6fd537f5d08e83e327f7cf326132bcc5a8e832b48badf8fd0959ceb48ccdea48'),
    (0x800ff30c, 268, '72404d4312c0508eb0b293dcfc9a338bbdbad9f719b1a4fedc7cf217c2904f97'),
    (0x8006d144, 100, '9192553250e34d5b4747df230f7eea747fbdeaa373bdf5436c086e45021c8707'),
    (0x800669d0, 96, '69f451585b1f653484e6dc9b7daa50eac754d1b0af9c07fb7bbd3e46cb3d63f1'),
    (0x8020ba78, 36, '5997a5a32c7df8eb2a03901039345f35a84f00b017545800218ef21bdbfaf81a'),
    (0x8020ba9c, 28, 'e0fbf8bbb6f184d7b21d322b68975adca6dc652510963c83c95b9ceb63e0671d'),
    (0x8020ba54, 36, 'c7b35d4075874e063982faa1d7d086e5d5ec4d70aed2b56c619b5e440e18e1ab'),
    (0x80066a30, 144, '04067a35ffbcd87ad1127ca2d980b63d26e9c05ffb80941604d1a31ddb44a68f'),
)
CELLS = (
    ('constructor-prehook', 0x802d3b1c, 0x8006f7c0, '154203d03076144a9c4fe908daee41ac69e0c36249556a66cf47e8003ed7801b'),
    ('upper0', 0x802d37a8, 0x8005f238, '8868a8515e4b649802f66057c61600c1899cea349f7d393786d886caaff607a4'),
    ('full61', 0x802d379c, 0x80065dfc, 'e6955d35c5cea55d3ab618c25eaaa6ecb58c408b0e21b2f29101334fb56b6201'),
    ('constructor-root', 0x802d3b14, 0x8006facc, 'b9aebbd587956abb6bd0bb4e5c2099f98afed6fce826f48d5c5a627c966bd045'),
    ('action2', 0x802d3b70, 0x80071598, '749496dd63f8f9fbe6d9574d4cc5109fb6d3d1a2fdd04e42a2f67a1a4f761e55'),
    ('variant0', 0x802d3c48, 0x800715d4, '745d9df22815e0d2ebf0504740b71d230a0bc7f2b73fe3261e01502d8c360dcd'),
    ('phase0', 0x8031f000, 0x800ff30c, '9461c792d0b20cf5b639ffc16b4fab5c53178e78c1ca538faea2a30286033974'),
)
# Required instruction-named scalar addresses only, never a returned pointer.
CONSTANTS = (
    (0x804376f8, '43160000', 'prehook-scale'),
    (0x804375c8, '4330000080000000', 'signed-integer-conversion-double'),
    (0x804392b4, '00000000', 'phase0-zero'),
    (0x804392b8, 'bf800000', 'phase0-stream-rate'),
    (0x804392d0, '3f733333', 'phase0-carry'),
)
CONFIG_SCALARS = ((0x80433868, 0, 'ground-slot'), (0x8043386a, 1, 'air-slot'))
MAP_SIZES = {0x80071598:60, 0x800715d4:36, 0x800ff2bc:80, 0x800ff30c:268, 0x8006d144:100,0x8020ba78:36,0x8020ba9c:28,0x8020ba54:36}


def decode_selected(word, pc):
    """Explicit PPC forms; every operand including implicit condition fields."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 4 and (xo & 31) in (20,21):
        c.require(((word >> 6) & 31) == rc == 0, 'reserved paired-arithmetic fields')
        return dict(mnemonic='ps_sub' if (xo & 31) == 20 else 'ps_add', fD=d, fA=a, fB=b, Rc=0)
    if op == 10:
        c.require(d == 0, 'unselected comparison fields')
        return dict(mnemonic='cmpli', BF=0, L=0, rA=a, immediate=word & 65535)
    if op in (24, 28):
        return dict(mnemonic='ori' if op == 24 else 'andi.', rS=d, rA=a, immediate=word & 65535)
    if op in (40, 42, 44):
        return dict(mnemonic={40:'lhz',42:'lha',44:'sth'}[op],
                    **{'rS' if op == 44 else 'rD':d}, rA=a,
                    displacement=normal.signed(word & 65535,16))
    if op == 31 and xo == 922:
        c.require(b == 0, 'reserved sign-extension fields')
        return dict(mnemonic='extsh', rS=d, rA=a, Rc=rc)
    if op == 31 and xo == 104:
        c.require(b == 0, 'reserved negate fields')
        return dict(mnemonic='neg', rD=d, rA=a, OE=0, Rc=rc)
    if op == 31 and xo == 40:
        return dict(mnemonic='subf', rD=d, rA=a, rB=b, OE=0, Rc=rc)
    if op == 63 and xo == 15:
        c.require(a == rc == 0, 'reserved conversion fields')
        return dict(mnemonic='fctiwz', fD=d, fB=b, Rc=0)
    return mode1.decode_selected(word, pc)


def range_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    normal.require_mapping(mapping, TEXT_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == width % 4 == 0 and start <= address < address + width <= end, 'range alignment/bounds')
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
                  for item in instructions if item['mnemonic'] in ('b', 'bc')), 'non-call branch outside fixed span')
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
    return dict(label=label, address=f'{address:08x}', width=4, target=f'{actual:08x}', sha256=digest, spans=spans)


def constant_evidence(db, mapping, address):
    c.require(type(address) is int, 'constant integer fields')
    selected = [item for item in CONSTANTS if item[0] == address]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    _, bits, label = selected[0]
    width = len(bits) // 2
    start, end, _, _, _, length, root = mapping
    c.require(width in (4,8) and address % width == 0 and start <= address < address+width <= end, 'constant alignment/bounds')
    raw, spans = db.chain(root, address-start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == bits, 'constant bits mismatch')
    return dict(address=f'{address:08x}', label=label, width=width, bits=raw.hex(),
                value=struct.unpack('>f' if width == 4 else '>d',raw)[0], sha256=hashlib.sha256(raw).hexdigest(),spans=spans)


def config_evidence(db, mapping, address):
    c.require(type(address) is int, 'config integer fields')
    selected = [item for item in CONFIG_SCALARS if item[0] == address]
    c.require(len(selected) == 1, 'config not allowlisted')
    normal.require_mapping(mapping, DATA4_MAPPING)
    _, expected, label = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(address % 2 == 0 and start <= address < address+2 <= end, 'config alignment/bounds')
    raw, spans = db.chain(root, address-start, 2, length)
    c.require(len(raw) == 2, 'config byte width')
    value = c.integer(raw,0,'H')
    c.require(value == expected, 'config value mismatch')
    return dict(address=f'{address:08x}', label=label,width=2,value=value,sha256=hashlib.sha256(raw).hexdigest(),spans=spans)


def inspect(data,digest):
    auth = c.inspect(data,digest)
    db = c.GBF(data); tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'],16)
    command.mappings(blocks,subs,image)
    # data4 has the same strict single initialized mapping controls as shared maps.
    c.require([(key,row) for key,row in blocks.items() if row[0] == 'MAIN_.data4'] ==
              [(6, blocks[6])], 'data4 block identity mismatch')
    c.require((blocks[6][4],blocks[6][5],blocks[6][6]) ==
              (0x20000000004335a0,11040,0), 'data4 block mapping mismatch')
    c.require([(key,row) for key,row in subs.items() if row[0] == 6] ==
              [(6,[6,2,11040,0,262,0])], 'data4 subblock mapping mismatch')
    maps = [normal.mapping_evidence(blocks,subs,image,m) for m in
            (TEXT_MAPPING,DATA3_MAPPING,DATA4_MAPPING,DATA5_MAPPING)]
    text,data3,data4,data5 = [item[0] for item in maps]
    keys = ('snapshot','snapshot_sha256','program_name','created_with_ghidra_version',
            'executable_sha256_metadata','executable_sha256_property_type','executable_metadata_caveat',
            'file_bytes_table','block_size','master_root','table_roots','image_offset','data5_sha256')
    return dict({key:auth[key] for key in keys},mappings=[item[1] for item in maps],
        ranges=[range_evidence(db,text,pc,width) for pc,width,_ in RANGES],
        cells=[cell_evidence(db,data3,pc) for _,pc,_,_ in CELLS],
        constants=[constant_evidence(db,data5,pc) for pc,_,_ in CONSTANTS],
        config_scalars=[config_evidence(db,data4,pc) for pc,_,_ in CONFIG_SCALARS],
        function_coverage=[dict(entry=f'{pc:08x}',end_exclusive=f'{pc+width:08x}',selected_width=width,
            represented_instructions=width//4,unrepresented_instructions=0,unrepresented_ranges=[],
            extent_basis=('prior identified return stub; prior5f188 map ends at entry; next C marker5f23c; authenticated return'
                if pc == 0x8005f238 else 'named entry plus prior independently identified posthook6f88c; authenticated return'
                if pc == 0x8006f7c0 else 'adjacent named C markers, map size and authenticated return'
                if pc in MAP_SIZES else 'adjacent named C markers and authenticated return'),map_size=MAP_SIZES.get(pc))
            for pc,width,_ in RANGES],
        float_preconditions=dict(FPSCR_RN=0,FPSCR_NI=0,GQR0_load_type=0,GQR0_store_type=0,
            GQR0_load_scale=0,GQR0_store_scale=0,finite_inputs_and_results_required=True,
            caveat='Bounded host implementation preconditions, not authenticated live register state.'),
        recorded_bases=dict(r2='8043ea20',r13='8043b5a0',
            caveat='Previously recorded bases, not freshly authenticated startup or live register state.'),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, live dispatch, '
               'numerical parity, full action playback, integration or playable-game proof. Every selected instruction '
               'and operand is represented; external callees remain explicit boundaries. Literal selections are '
               'independent of decoded pointers. Prehook ends before omitted-C posthook6f88c. Config scalars are not '
               'function pointers. Float execution needs separately stated FPSCR/GQR assumptions.')


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
