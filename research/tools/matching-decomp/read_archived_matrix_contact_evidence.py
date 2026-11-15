#!/usr/bin/env python3
"""Bounded normal matrix handler46f08, 604 bytes /151 instructions and six constants.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
pointer following, transitive helper reads, or raw/operand-list output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import struct

import read_archived_later_outer_evidence as base
import read_archived_actor_mode1_evidence as mode1
c, command, normal = base.c, base.command, base.normal

TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2147774216, 604, '7fc36ec2addbca5604997cf3b8977c264e6dce3ba94fd21e305850ea7843db24'),)
OPERAND_DIGESTS = {0x80046f08: '94147c93b33cdd4d813cd321148aeee3ca7e535eeb4eb6f043cdeba939abbdee'}
FLOW_DIGESTS = {0x80046f08: (12, 'b04a32df8b4c330dfbf7fd82bc17646a74c456a9986cc0aebd71ecbc16260595')}
CALLS = {0x80046f08: (('80047000', '8003d6e4'),)}
INDIRECT_CALLS = {0x80046f08: ()}
DATA_MAPPING = (0x80436a20,0x8043d500,7,"MAIN_.data5",7,27360,263)
CONSTANTS = ((2151903392, 4, '00000000'), (2151903396, 4, '40000000'), (2151903400, 4, '3e000000'), (2151903404, 4, '40400000'), (2151903408, 4, '3e800000'), (2151903416, 8, '4330000080000000'))
REUSED_EVIDENCE = (dict(address="80046e7c", source="normal-actor-matrix-evidence-2026-11-13.md", read_here=False),)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Compose unchanged selected decoders; no new instruction forms."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    if word >> 26 == 27 or (word >> 26 == 63 and (word >> 1) & 1023 == 40):
        return mode1.decode_selected(word, pc)
    return base.decode_selected(word, pc)


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


def constant_evidence(db, mapping, address, width):
    c.require(type(address) is type(width) is int, 'constant integer fields')
    selected = [row for row in CONSTANTS if row[:2] == (address, width)]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA_MAPPING)
    raw, spans = db.chain(mapping[-1], address - mapping[0], width, mapping[-2])
    c.require(len(raw) == width and raw.hex() == selected[0][2], 'constant bits mismatch')
    return dict(address=f'{address:08x}', width=width, bits=raw.hex(),
                value=struct.unpack('>f' if width == 4 else '>d', raw)[0], spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, mapping = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data, data_mapping = normal.mapping_evidence(blocks, subs, image, DATA_MAPPING)
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    constants = [constant_evidence(db, data, pc, width) for pc, width, _ in CONSTANTS]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping, data_mapping], ranges=ranges, constants=constants,
                selection_basis=dict(reads=7, bytes=632, selected_data_cells=6,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. Complete46f08 body '
                    'represented. Direct callee bodies, indirect callback targets, global pointer '
                    'values, descriptors and actor runtime fields remain unselected by this reader.')


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
