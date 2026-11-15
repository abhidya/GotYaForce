#!/usr/bin/env python3
"""Five frozen later frame bodies, 720 bytes / 180 instructions.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
new data cells, pointer following, helper reads, or raw/operand-list output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_frame_blocker_evidence as prior
import read_archived_actor_status_evidence as status

outer = prior.outer

c, command, normal = outer.c, outer.command, outer.normal
TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2148049548, 48, '94cb040d0d0bd380e6ab2d81aec5d82583aaf212f52408a7050212f7e39acc08'), (2148047596, 276, '03e4a562cd8742937f8f85f602f0f3a3a682457f8f5887accc0b15cbf24f4802'), (2148046636, 120, '5f226c16b749f7e78e5d3a72f60c8235d9eeee3cb1dadcdf8ed6f9a4a027c78d'), (2148046424, 120, 'eec105ac979d991b2c30e5d6b4533a282be84e87c764fac7e8d9b684c77719f5'), (2147826324, 156, '908608c3724b5803beb7be025c6aa067b9b4e9158317ca1e33a986865fcb5840'))
OPERAND_DIGESTS = {2148049548: '74610b50d0d0d77b8f5906823cecc306f02500938980c06f57f017f1c6e93cdc', 2148047596: 'c0f0a39c2f531c9e6674dc7141dc7f3db75b73f69bf6be6ac8bf71c77611f4b0', 2148046636: '41ab02e33163e5948d8b557f19df711a88c7d3e26c7c2e986ce6e2d1a94163f2', 2148046424: 'cb99caf71b6eb45ac7b9fc685b4d613380a4dc6e222715f9bf80347d66381d58', 2147826324: '992996cd339f07c9f89e143fe8ef4d26279f2041e78edec532f20aa996ff7dfa'}
FLOW_DIGESTS = {2148049548: (1, 'b5275368dcd4238265d1f7a1b021eefbc237f61bb2fb34d68d4c20707e0b7580'), 2148047596: (15, 'b258d92e616402a97bfba8c360951c6b3bff27e732ffb3ed3415d52b028e70d3'), 2148046636: (6, '6d67907982a1f8bb78e68501ca93100232cefe73215b407eeeede4e571e20f9c'), 2148046424: (6, '4e4b35cd40b55b3a330a2d3c3900c2606e608a397b23ee0174069dbb8afddf63'), 2147826324: (8, '5840fc9401737f35752d48801e29b44371e501559b2c31882d265a9a5debbb61')}
CALLS = {pc: () for pc, _, _ in RANGES}
INDIRECT_CALLS = {2148049548: (), 2148047596: ('80089b30', '80089b84', '80089bd0'), 2148046636: ('80089768',), 2148046424: ('80089694',), 2147826324: ('80053afc',)}
REUSED_EVIDENCE = (
    dict(address="80029380", source="outer-frame-evidence-2026-11-14.md", read_here=False),
    dict(address="80053b30", source="mass-preparation-evidence-2026-11-14.md", read_here=False),
)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Reuse frozen integer decoder; admit only the already-proven bctrl form."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    if word >> 26 == 44:
        return status.decode_selected(word, pc)
    if word == 0x4e800421:
        return normal.decode_selected(word, pc)
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
                selection_basis=dict(reads=5, bytes=720, selected_data_cells=0,
                    pointer_following=False, helpers_read=False, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. All five complete bodies '
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
