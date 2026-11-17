#!/usr/bin/env python3
"""Missing voice interior, complete selector and exactly four event-two bytes.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
arbitrary data cells, pointer following, transitive helper reads or raw output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_later_outer_evidence as base
import read_archived_input_prefix_evidence as prefix
c, command, normal = base.c, base.command, base.normal

TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2148442916, 264, 'e0dcebeeca660396390676cdf27488c21ba21c0f000cdf937ebecbb17f8efb83'), (2148442480, 344, 'be2656ce193e3315726de4cacf3c04e2df1debc2712d0e160e477cde17f5798d'))
OPERAND_DIGESTS = {2148442916: '71673cbcbf8538c5ec6b85860984bdc42c7ec8c5e9b716ee7e4c346c0b9cab59', 2148442480: '8354b834911c339627f2208016dc1590737613f23bca084e4d0b1b0f7befa3cd'}
FLOW_DIGESTS = {2148442916: (16, '72f84b4bae075888b755858941788030833f5b570832e3f2541d5bcc3822ff7d'), 2148442480: (14, '58386f28121efc407df1a05fcfc0262d249febcfb4c392bd06bd6319db01da49')}
CALLS = {2148442916: (('800ea324', '800055fc'), ('800ea3e4', '800ea170'), ('800ea424', '800dbf04')), 2148442480: (('800ea190', '800055fc'), ('800ea1ac', '800e9f0c'), ('800ea1f8', '800e9e68'), ('800ea250', '800055fc'), ('800ea278', '800e9f0c'))}
INDIRECT_CALLS = {pc: () for pc, _, _ in RANGES}
DATA3_MAPPING = normal.DATA3_MAPPING
CELLS = ((2150735264, 64, 'c3641f8544d7c02f3580b07c0f9887f0c6a27ff5ab1d4a3e29caf197cfc299ae'), (2150735265, 128, '76be8b528d0075f7aae98d6fa57a6d3c83ae480a8469e668d7b0af968995ac71'), (2150735266, 127, '620bfdaa346b088fb49998d92f19a7eaf6bfc2fb0aee015753966da1028cb731'), (2150735267, 0, '6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d'))
REUSED_EVIDENCE = (
    dict(address='800055fc', width=52, source='read_archived_rng_evidence.py', read_here=False),
    dict(address='800ea2ec', width=56, source='read_archived_actor_command_admission_evidence.py', read_here=False),
    dict(address='800ea42c', width=20, source='read_archived_actor_command_admission_evidence.py', read_here=False),
)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    if word >> 26 == 31 and (word >> 1) & 1023 == 235:
        return prefix.decode_selected(word,pc)
    return base.decode_selected(word,pc)


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
    c.require(all((address <= int(row['target'], 16) < address + width or (address == 0x800ea324 and row['target'] == '800ea42c'))
                  for row in flow if row['mnemonic'] in ('b', 'bc')), 'branch outside fixed span')
    calls = tuple((row['address'], row['target']) for row in flow if row['mnemonic'] == 'bl')
    c.require(calls == CALLS[address], 'call schedule mismatch')
    indirect = tuple(row['address'] for row in flow if row['mnemonic'] == 'bctrl')
    c.require(indirect == INDIRECT_CALLS[address], 'indirect call schedule mismatch')
    if address == 0x800ea324:
        c.require(instructions[-1] == dict(address='800ea428',mnemonic='or',rS=29,rA=3,rB=29,Rc=0),
                  'gap must fall through to existing authenticated return at800ea42c')
    else:
        c.require(instructions[-1] == dict(address=f'{address + width - 4:08x}',mnemonic='blr',BO=20,BI=0,BH=0,LK=0),
                  'complete terminal return')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, represented_instructions=len(instructions),
                unrepresented_instructions=0, operand_sha256=OPERAND_DIGESTS[address],
                control_flow_count=len(flow), control_flow_sha256=FLOW_DIGESTS[address][1],
                calls=[dict(site=site, target=target) for site, target in calls],
                indirect_call_sites=list(indirect))


def cell_evidence(db, mapping, address):
    c.require(type(address) is int, 'cell address integer')
    selected = [row for row in CELLS if row[0] == address]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    raw, spans = db.chain(mapping[-1], address - mapping[0], 1, mapping[-2])
    c.require(len(raw) == 1, 'cell byte width')
    c.require(hashlib.sha256(raw).hexdigest() == selected[0][2], 'cell digest mismatch')
    c.require(raw[0] == selected[0][1], 'cell target mismatch')
    return dict(address=f'{address:08x}', width=1, value=selected[0][1],
                sha256=selected[0][2], spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, mapping = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    data3, data3_fact = normal.mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    cells = [cell_evidence(db, data3, pc) for pc, _, _ in CELLS]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping, data3_fact], ranges=ranges, event2_cells=cells,
                selection_basis=dict(reads=6, bytes=612, selected_data_cells=4,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. The264-byte voice interior and '
                    'complete344-byte selector are represented. Reuse existing ea2ec entry/return and055fc RNG '
                    'evidence without new reads. Initial RNG state, voice pools, audio payloads and other '
                    'event rows remain unselected.')


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
