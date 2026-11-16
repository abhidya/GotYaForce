#!/usr/bin/env python3
"""Five frozen actor-dispatch bodies, 3000 bytes / 750 instructions.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
arbitrary data cells, pointer following, or raw/operand-list output.
Shared archive authentication, mappings and decoders are unchanged.
This reader adds only the five fixed bodies and three fixed cells listed below.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_frame_blocker_evidence as prior
import read_archived_actor_normal_evidence as actor_normal
import read_archived_transform_history_evidence as history
import read_archived_normal_matrix_evidence as matrix
import read_archived_terrain_orientation_evidence as terrain
import read_archived_frame_suffix_evidence as suffix
import struct

outer = prior.outer

c, command, normal = outer.c, outer.command, outer.normal
TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((0x80054070, 316, '349fd1d6d1088a9ba19eb03192f38515faa2652943f8d2edce8d84ead782be90'),
 (0x8005475c, 128, '1123e2ac001c1e70649a8db6558d85a462c2837f16c81a8c65bc00c567156b5e'),
 (0x80054c78, 68, '81f97bf335f352727071f136d31de22a856e4d80a09d600ec17e9a8c0f4a8c45'),
 (0x8005a580, 1896, '061ebcdfdafeca5f6a522c2dc2a792f7247ac7e6747f6413d1d862a5efad71cf'),
 (0x80006284, 592, '0a500f1d0852bb5e754b1f1f742e1e4db3fba8d7162831e4c45d11882b52d429'))
OPERAND_DIGESTS = {0x80054070: '55b68e98757c5eb52116cc5a6aa74806d0f1f0b32c89a15066b92dce5fbb1690',
 0x8005475c: '75c0b94eb27e621ecf8b3b3a7cd2bc4521a755e2231f9394adc3369d518b8d19',
 0x80054c78: 'f0e81f351b1956551ce4b0be4fa73ee34317e44bedd6c2ba86586566a52df6de',
 0x8005a580: '662e45d9ae7e070a012c421b4927353e59f98a319ef5a8d9546591d009ede789',
 0x80006284: '276b8c1c2d293ae9cc3058dbad9793ff6fc731dbfe573ae7d9e60f5ec1bfc348'}
FLOW_DIGESTS = {0x80054070: (16, '1ece826173f57c0cd9a09761636f32588b3fabf92f6d15c71a289f6845999419'),
 0x8005475c: (5, '679bd3fedbba176deed933c3e4271ed2752c3a08793245f3d242d274cc64f129'),
 0x80054c78: (3, 'e422a9b96b694a3af2d31b5f867587a88563dd33aba27dc4424d0ca2693cbd01'),
 0x8005a580: (107, '41301979cac85b255a7bc0e915921c83fe9451b113898c66f53779b50a8b0acf'),
 0x80006284: (16, '07a09ff4a1d53bccde2cadbec4e50cb24d40842df214bc14f314017ae76b0ecb')}
CALLS = {0x80054070: (('8005408c', '8005685c'),
              ('800540dc', '8008b480'),
              ('8005410c', '8003d6e4'),
              ('80054120', '8020ba54'),
              ('80054140', '8005a580'),
              ('80054160', '800465fc'),
              ('8005418c', '80006284')),
 0x8005475c: (),
 0x80054c78: (('80054ca8', '80055568'),),
 0x8005a580: (('8005a664', '80092ecc'),
              ('8005a680', '80092ecc'),
              ('8005a6c4', '800f036c'),
              ('8005a6d4', '800f036c'),
              ('8005a788', '80092ecc'),
              ('8005a7a4', '80092ecc'),
              ('8005a7e8', '800f036c'),
              ('8005a7f8', '800f036c'),
              ('8005a8c4', '80092ecc'),
              ('8005a8e0', '80092ecc'),
              ('8005a924', '800f036c'),
              ('8005a934', '800f036c'),
              ('8005a9f8', '80092ecc'),
              ('8005aa10', '80092ecc'),
              ('8005aa54', '800f036c'),
              ('8005aa64', '800f036c'),
              ('8005ab28', '80092ecc'),
              ('8005ab44', '80092ecc'),
              ('8005ab88', '800f036c'),
              ('8005ab98', '800f036c'),
              ('8005ac48', '80092ecc'),
              ('8005ac64', '80092ecc'),
              ('8005aca8', '800f036c'),
              ('8005acb8', '800f036c'),
              ('8005acc8', '800677b0')),
 0x80006284: (('800064a8', '80006f98'),)}
INDIRECT_CALLS = {0x80054070: ('800540c8',), 0x8005475c: ('800547c8',), 0x80054c78: (), 0x8005a580: (), 0x80006284: ()}
DATA3_MAPPING = normal.DATA3_MAPPING
DATA5_MAPPING = suffix.DATA5_MAPPING
CELLS = (
 ('lifecycle_index_1', 0x802d3268, 0x8005475c, '483c6b14cec525b355a48863696e6fd290242ba29c99b42690a156540ba721ab'),
 ('substate_index_1', 0x802d3278, 0x80054c78, 'e02d167abc140e9aba5a214d3e46f9491fe27b2b2dc54dcfac1e8809128c7fc3'),
)
CONSTANTS = ((0x804373e0, '41a00000', 'stage_boundary_margin'),)
REUSED_EVIDENCE = (
 dict(address='8005685c', source='read_archived_transform_history_evidence.py', read_here=False),
 dict(address='80437250', source='read_archived_actor_status_evidence.py', read_here=False),
)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Compose unchanged, already validated decoders; add no instruction forms."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    for module in (prior, actor_normal, history, matrix, terrain):
        try:
            result = module.decode_selected(word, pc)
        except c.FormatError:
            continue
        if result is not None:
            return result
    return None


def range_evidence(db, mapping, address, width):
    c.require(type(address) is type(width) is int, 'range integer fields')
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
    flow = [row for row in instructions if row['mnemonic'] in ('b', 'bc', 'bl', 'blr', 'bctrl')]
    c.require((len(flow), semantic_digest(flow)) == FLOW_DIGESTS[address], 'complete control-flow mismatch')
    c.require(semantic_digest(instructions) == OPERAND_DIGESTS[address], 'complete operand mismatch')
    c.require(all(address <= int(row['target'], 16) < address + width
                  for row in flow if row['mnemonic'] in ('b', 'bc')), 'branch outside fixed span')
    calls = tuple((row['address'], row['target']) for row in flow if row['mnemonic'] == 'bl')
    c.require(calls == CALLS[address], 'call schedule mismatch')
    indirect = tuple(row['address'] for row in flow if row['mnemonic'] == 'bctrl')
    c.require(indirect == INDIRECT_CALLS[address], 'indirect call schedule mismatch')
    c.require(instructions[-1] == dict(address=f'{address + width - 4:08x}', mnemonic='blr',
                                      BO=20, BI=0, BH=0, LK=0), 'complete terminal return')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, represented_instructions=len(instructions),
                unrepresented_instructions=0, operand_sha256=OPERAND_DIGESTS[address],
                control_flow_count=len(flow), control_flow_sha256=FLOW_DIGESTS[address][1],
                calls=[dict(site=site, target=target) for site, target in calls],
                indirect_call_sites=list(indirect))


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
    text, mapping = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data3, map3 = normal.mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    data5, map5 = normal.mapping_evidence(blocks, subs, image, DATA5_MAPPING)
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping, map3, map5], ranges=ranges,
                cells=[cell_evidence(db, data3, pc) for _, pc, _, _ in CELLS],
                constants=[constant_evidence(db, data5, pc) for pc, _, _ in CONSTANTS],
                selection_basis=dict(reads=8, bytes=3012, selected_data_cells=3,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. All five complete bodies '
                    'represented. Only lifecycle/substate index 1 cells are selected, not whole tables. '
                    'No actual actor initialization, raw-input values, host epoch, scheduler membership, '
                    'other indirect targets, list records or live global pointers are established.')


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
