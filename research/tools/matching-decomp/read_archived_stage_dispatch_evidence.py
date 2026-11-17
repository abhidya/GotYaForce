#!/usr/bin/env python3
"""Stage owner initializer, state-zero body and exactly two dispatch cells.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
arbitrary data cells, pointer following, transitive helper reads or raw output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_frame_blocker_evidence as prior
import read_archived_actor_mode1_evidence as mode1
import read_archived_target_preparation_evidence as target
import read_archived_actor_status_evidence as status
import read_archived_terrain_orientation_evidence as terrain

outer = prior.outer

c, command, normal = outer.c, outer.command, outer.normal
TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2148038424, 252, '1562f9b6cce8ef72042409a77b9bcd96bab9667c7f1eff383c5bfac56496dc43'), (2148039980, 504, '4af69623be006a38ea38c9184995f6cc3301b09806cd833357466dc3e8331658'))
OPERAND_DIGESTS = {2148038424: '20c78fdeab3437d90c95b726d86710937682caaf72202edc120f38f03cac888c', 2148039980: '47936a1929405484bc5e3c807bcf74575e618449f96c24f28caf42d07e68a185'}
FLOW_DIGESTS = {2148038424: (2, '81c004a737d2332be2b389c88fd376d69de6533b261f58f6132753f455766984'), 2148039980: (29, '1c25aa95ea147812e3d4c3853a94ed4c8d554dec98f80e354546963737327957')}
CALLS = {2148038424: (('80087730', '8000540c'),), 2148039980: (('80087d7c', '800818d0'), ('80087d80', '80087924'), ('80087d84', '80006d4c'), ('80087da8', '80006fb4'), ('80087dac', '80006d4c'), ('80087dd0', '80006fb4'), ('80087e0c', '8024fd74'), ('80087e24', '80007c54'), ('80087e3c', '80007cd0'), ('80087e4c', '80007cac'), ('80087e58', '80007f38'), ('80087e68', '80007d68'), ('80087e78', '80007908'), ('80087e98', '80007834'), ('80087e9c', '80006d4c'), ('80087ec0', '800070e4'), ('80087ed0', '80009c28'), ('80087ee0', '80009c30'), ('80087ee4', '80006d4c'), ('80087f08', '80006fb4'))}
INDIRECT_CALLS = {pc: () for pc, _, _ in RANGES}
DATA4_MAPPING = (0x804335a0, 0x804360c0, 6, "MAIN_.data4", 6, 11040, 262)
CELLS = ((2151889176, 2148039980, '095420b255262dcf65d40f5358807b9f38328787e5131c1911ac5c881210283a'), (2151889180, 2148040480, '31c457b8b303558c3ea6ddf252b3969a407774c2d2f275c2ef028028ea60a7b0'))
REUSED_EVIDENCE = (
    dict(address="80029380", source="outer-frame-evidence-2026-11-14.md", read_here=False),
    dict(address="80053b30", source="mass-preparation-evidence-2026-11-14.md", read_here=False),
)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Compose unchanged proven decoders for only the required instruction forms."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, xo = word >> 26, (word >> 1) & 1023
    if op in (48, 50, 52, 54, 56, 60):
        return mode1.decode_selected(word, pc)
    if op == 31 and xo == 535:
        return target.decode_selected(word, pc)
    if op == 42 or (op == 59 and xo & 31 == 29):
        return target.decode_selected(word, pc)
    if op == 44 or (op == 31 and xo in (40, 824)):
        return status.decode_selected(word, pc)
    if op == 40:
        return terrain.decode_selected(word, pc)
    if op == 59 and xo & 31 in (18, 20, 21, 25):
        return mode1.decode_selected(word, pc)
    return prior.decode_selected(word, pc)


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
    c.require(type(address) is int, 'cell address integer')
    selected = [row for row in CELLS if row[0] == address]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA4_MAPPING)
    raw, spans = db.chain(mapping[-1], address - mapping[0], 4, mapping[-2])
    c.require(len(raw) == 4, 'cell byte width')
    c.require(hashlib.sha256(raw).hexdigest() == selected[0][2], 'cell digest mismatch')
    c.require(c.integer(raw, 0, 'I') == selected[0][1], 'cell target mismatch')
    return dict(address=f'{address:08x}', width=4, target=f'{selected[0][1]:08x}',
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
    data4, data4_fact = normal.mapping_evidence(blocks, subs, image, DATA4_MAPPING)
    cells = [cell_evidence(db, data4, pc) for pc, _, _ in CELLS]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping, data4_fact], ranges=ranges, dispatch_cells=cells,
                selection_basis=dict(reads=4, bytes=764, selected_data_cells=2,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. Both complete bodies '
                    'represented. Only state-zero and state-one targets evidenced; transitive callees, global pointer '
                    'values, list records and mode data remain unselected by this reader.')


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
