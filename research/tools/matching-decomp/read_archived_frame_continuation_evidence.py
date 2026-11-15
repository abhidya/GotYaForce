#!/usr/bin/env python3
"""Three frozen frame-continuation bodies, 424 bytes / 106 instructions.

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

outer = prior.outer

c, command, normal = outer.c, outer.command, outer.normal
TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = (
    (0x80053a2c, 104, '1a8719769697cc0f7a8a1a711983175c6b9823e6c5e080885fa83dd1430cb177'),
    (0x80087cf0, 60, '0a36f0211bae8654c9502654856eef93e12a2084ccdbe2ad79665ce4c6c21e72'),
    (0x80089554, 260, '14d54d2183c44456974e44418019670cfd857a373e5baced583924c4c74280df'),
)
OPERAND_DIGESTS = {
    0x80053a2c: 'f084a8593bf144dcf9843df184b74cbb6eb4739a4f9a74467b17c612b29b0cc7',
    0x80087cf0: 'd69d131f83c63dc3cd2ce81c0f47fcccde9e1a7ad23ff025dba119196c6ddabe',
    0x80089554: 'a856fe5847582ce64dafa79c9930981af86823336ed44ee01d2e3d8de56c8bfa',
}
FLOW_DIGESTS = {
    0x80053a2c: (7, '5ceb4f48056fcdd5fdf34c2b08119a10785c1e99198de8f5372c698de76c9d8b'),
    0x80087cf0: (2, 'a83000c1730350c0639eb7f7c65307d3004e2ba4606dc374eb5cd92ca5b425fe'),
    0x80089554: (16, '131d38022218146185aaae755a0494dae24dc36ec0a6f57e1eedc7bd20092780'),
}
CALLS = {
    0x80053a2c: (('80053a40', '8005ace8'), ('80053a58', '80054070'), ('80053a74', '8005b140'), ('80053a78', '8005b2b8')),
    0x80087cf0: (),
    0x80089554: (),
}
INDIRECT_CALLS = {0x80053a2c: (), 0x80087cf0: ('80087d18',), 0x80089554: ('80089590', '800895d4', '8008961c')}
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
                selection_basis=dict(reads=3, bytes=424, selected_data_cells=0,
                    pointer_following=False, helpers_read=False, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. All three complete bodies '
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
