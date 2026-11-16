#!/usr/bin/env python3
"""One complete populated-root draw callback, 404 bytes / 101 instructions.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
arbitrary data cells, pointer following, helper reads, or raw/operand-list output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import struct
import read_archived_actor_frame_dispatch_evidence as owners

import read_archived_frame_blocker_evidence as prior
import read_archived_later_outer_evidence as selected

outer = prior.outer

c, command, normal = outer.c, outer.command, outer.normal
TEXT_MAPPING = normal.TEXT_MAPPING
DATA5_MAPPING = owners.DATA5_MAPPING
CONSTANTS = ((0x804370e0,"38c90fdb","signed-angle-to-radians"),)
RANGES = ((2147777188, 404, 'd1034c09b0f68dabce25aa8dc2fd55eb99b31ee2e017cf379fad8fa7c23eb779'),)
OPERAND_DIGESTS = {2147777188: '518f2820422a9163f2a2d78a190783f46962ceb117535357bce7f7143fd67153'}
FLOW_DIGESTS = {2147777188: (24, 'b657ba7bcffbecfdee218f793b6f57a2d37f57c19e2700c879c23a159e164fae')}
CALLS = {2147777188: (('80047ae4', '8020af28'), ('80047b00', '8020af28'), ('80047b0c', '8020aefc'), ('80047b24', '8020b7a8'), ('80047b80', '8020b238'), ('80047b90', '8020af5c'), ('80047bb0', '8020b238'), ('80047bc0', '8020af5c'), ('80047be0', '8020b238'), ('80047bf0', '8020af5c'), ('80047c0c', '8020b4f8'), ('80047c1c', '8020af5c'))}
INDIRECT_CALLS = {0x80047aa4: ()}
REUSED_EVIDENCE = (dict(address="80089554", source="read_archived_frame_continuation_evidence.py", read_here=False),)

def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    return selected.decode_selected(word, pc)


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
    data5, map5 = normal.mapping_evidence(blocks, subs, image, DATA5_MAPPING)
    constants = [constant_evidence(db,data5,0x804370e0)]
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping,map5], ranges=ranges, constants=constants,
                selection_basis=dict(reads=2, bytes=408, selected_data_cells=1,
                    pointer_following=False, helpers_read=False, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived static body evidence only, not live flags, original-DOL identity or full frame. '
                    'Helpers reuse prior evidence; only one required angle constant; no helper, root or actor payload is selected here.')



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
