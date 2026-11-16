#!/usr/bin/env python3
"""Observed substate-two dispatch, input sampler and pad mask:492 bytes/123 instructions.

Fixed read-only authenticated local snapshots; one dispatch cell, no runtime/pad
payloads, arbitrary selections, pointer following or raw instruction output.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_later_outer_evidence as base
import read_archived_actor_status_evidence as status
c, command, normal = base.c, base.command, base.normal
TEXT_MAPPING, DATA3_MAPPING = normal.TEXT_MAPPING, normal.DATA3_MAPPING
RANGES = ((2147830972, 52, '5031b1cbdf20bc9464eef663b0778abe4c88b6c39931b9b0be6f0feabc0fdb26'), (2147838208, 424, '52c4c7e19500682352bbf4503d8973d50f69fed24c5525d5b3ab40bba34bbfa2'), (2148056000, 16, '257d48a7d554a62bc9c18c1daf1fa73860c81815999016f64a0a7b01f7cda582'))
OPERAND_DIGESTS = {2147830972: '815e893875bb7654e6fa5032bcd72a6eb730b01ab0d4eba0dda7ed8afb4cccff', 2147838208: '9d14230f9149dc13839a9321ef1614e23900540dd9edc1e36e01dab16d51dbb1', 2148056000: 'caf0eff044eb475aeb4c3dd645a42c69e0bade3c40c48686abe18e10d09cc5cd'}
FLOW_DIGESTS = {2147830972: (3, '217c552b84c2ddb7ab5b9a0de1d3dc4300712570cb60b6f159b7effdfa891a83'), 2147838208: (14, 'c1d795af4d72a4904965c3b3dc768fcc15e5a927f22c8ffa8b49f0d0667beca7'), 2148056000: (1, 'a7e089b5c32bf4754bb4356fcfa048215e9de5685d176250707cf74e2f4c83ee')}
CALLS = {2147830972: (('80054cd0', '80056900'), ('80054cd8', '80055568')), 2147838208: (('800569e4', '8008bbc0'), ('80056a58', '8001c9d0')), 2148056000: ()}
INDIRECT_CALLS = {pc: () for pc, _, _ in RANGES}
CELLS = (('substate_index_2', 2150445692, 2147830972, '2c003f1520860d7999fed1fdbc3ab22879135b1d1b9676583d180e72760579c9'),)
REUSED_EVIDENCE = (
    dict(address='8005475c', source='read_archived_actor_frame_dispatch_evidence.py', read_here=False),
    dict(address='80055568', source='read_archived_frame_suffix_evidence.py', read_here=False),
)


def decode_selected(word, pc):
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    if word >> 26 == 31 and (word >> 1) & 1023 == 60:
        return status.decode_selected(word, pc)
    return base.decode_selected(word, pc)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


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


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, text_fact = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data3, data_fact = normal.mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    cells = [cell_evidence(db, data3, pc) for _, pc, _, _ in CELLS]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[text_fact, data_fact], ranges=ranges, cells=cells,
                selection_basis=dict(reads=4, bytes=496, selected_data_cells=1,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, retail hydration or playability. Exact index2 cell and three '
                    'complete bodies represented. Conditional AI8001c9d0 body, controller records, '
                    'actual runtime inputs and global pointer values remain unselected.')


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
