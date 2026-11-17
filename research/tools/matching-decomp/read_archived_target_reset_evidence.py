#!/usr/bin/env python3
"""Two frozen target/contact reset helpers, 460 bytes / 115 instructions.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
new data cells, pointer following, transitive helper reads, or raw/operand-list output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_frame_blocker_evidence as prior
import read_archived_projectile_initialization_evidence as projectile
import read_archived_actor_mode1_evidence as mode1
import read_archived_target_preparation_evidence as target
import read_archived_actor_status_evidence as status
import read_archived_terrain_orientation_evidence as terrain

outer = prior.outer

c, command, normal = outer.c, outer.command, outer.normal
TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2147667064, 300, '2234d9aa7af59047260c7d72939f52c5ef9b31f10e9e89864abf2ff281132ecc'), (2147667364, 160, '2dcecd916811217d411f21faca6a1ca97774fa3c65c5f3756bf92d230096a693'))
OPERAND_DIGESTS = {2147667064: '1f85a42b21074708df27c69d0b06d55c28895555d6b26f12418c23d6129ae45b', 2147667364: '3cdbe47e7376e6452a9ccf84c67393f95dc544de6707520911a9d4fc89985f51'}
FLOW_DIGESTS = {2147667064: (20, 'fc41766c584ab74307ed3ebd841412baae015bbc5855f6100830a29a765799b6'), 2147667364: (5, 'a9e96c6c99ebaccf14ca0f5dd78bf2778ff86f9f817a3aa6989c620486245ab9')}
CALLS = {2147667064: (('8002ccbc', '8002cda4'), ('8002cd30', '8002cda4'), ('8002cd80', '8002cda4')), 2147667364: ()}
INDIRECT_CALLS = {pc: () for pc, _, _ in RANGES}
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
    if word == 0x4d820020:
        return projectile.decode_selected(word, pc)
    op, xo = word >> 26, (word >> 1) & 1023
    if op in (48, 50, 52, 54, 56, 60):
        return mode1.decode_selected(word, pc)
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
    flow = [row for row in instructions if row['mnemonic'] in ('b', 'bc', 'bl', 'blr', 'bctrl', 'bclr')]
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


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, mapping = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping], ranges=ranges,
                selection_basis=dict(reads=2, bytes=460, selected_data_cells=0,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. Both complete bodies '
                    'represented. Direct callee bodies, indirect callback targets, global pointer '
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
