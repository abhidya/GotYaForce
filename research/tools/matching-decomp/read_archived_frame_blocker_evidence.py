#!/usr/bin/env python3
"""Exactly two frozen frame-predecessor bodies, 1792 bytes / 448 instructions.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
new data cells, pointer following, helper reads, or raw/operand-list output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_outer_frame_evidence as outer

c, command, normal = outer.c, outer.command, outer.normal
TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = (
    (0x80027764, 736, '6ecb2b36a87268ae52b5b4f53649991e70f755c5a4128eaf1575bb90c9668d4f'),
    (0x8000bef4, 1056, 'dc9bdaf0c10968c6eadd7325b99361b7c91d5cddf2a1758edca587cd5b8b82e4'),
)
# Digests pin every derived operand, without publishing reconstructable listings.
OPERAND_DIGESTS = {
    0x80027764: '5bb4489c224c57e491d6433db081023fd6d6b40012bf16124fd9dead26b50e28',
    0x8000bef4: '776e4e7eeade8f56714551fa4ac2c77edb841c9a1a2c128a34a08bc0210b096c',
}
FLOW_DIGESTS = {
    0x80027764: (41, '8025c64b5427c06030dc3c57483e8ed684c4b452a0c711f55f80ba06b4115efe'),
    0x8000bef4: (36, 'f6b8a6566237d3c9a330dbae081f69bae7da0b6bc2656fe0429403b91095d833'),
}
CALLS = {
    0x80027764: (('80027770', '800055fc'),),
    0x8000bef4: (('8000c11c', '80010514'), ('8000c1e4', '80010514'),
                 ('8000c270', '80010514')),
}
REUSED_EVIDENCE = (
    dict(address='800055fc', source='rng-evidence-2026-11-14.md', read_here=False),
    dict(address='80010514', source='target-selector-evidence-2026-11-14.md', read_here=False),
)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Selected integer forms only; every encoded bit is represented or fixed."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op in (35, 46, 47):
        if op == 35:
            c.require(a != 0 and a != d, 'reserved load-update base')
        if op == 46:
            c.require(a == 0 or a < d, 'overlapping load-multiple base')
        return dict(mnemonic={35: 'lbzu', 46: 'lmw', 47: 'stmw'}[op],
                    **{'rS' if op == 47 else 'rD': d}, rA=a,
                    displacement=normal.signed(word & 65535, 16))
    if op == 31 and xo in (23, 151):
        c.require(rc == 0, 'reserved indexed-memory bit')
        return dict(mnemonic='lwzx' if xo == 23 else 'stwx',
                    **{'rD' if xo == 23 else 'rS': d}, rA=a, rB=b)
    if op == 7:
        return dict(mnemonic='mulli', rD=d, rA=a, immediate=normal.signed(word & 65535, 16))
    if op == 16 and (d, a) == (4, 0):
        c.require(word & 3 == 0, 'unselected conditional branch')
        return dict(mnemonic='bc', BO=4, BI=0, LK=0, AA=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}')
    decoded = outer.decode_selected(word, pc)
    allowed = {'addi', 'addis', 'b', 'bc', 'bl', 'blr', 'cmp', 'cmpi', 'cmpli', 'extsb',
               'lbz', 'lwz', 'mflr', 'mtctr', 'mtlr', 'or', 'stb', 'stw', 'stwu',
               'add', 'and', 'lbzx', 'rlwinm', 'slw', 'stbx'}
    return decoded if decoded and decoded['mnemonic'] in allowed else None


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
    flow = [row for row in instructions if row['mnemonic'] in ('b', 'bc', 'bl', 'blr')]
    c.require((len(flow), semantic_digest(flow)) == FLOW_DIGESTS[address], 'complete control-flow mismatch')
    c.require(semantic_digest(instructions) == OPERAND_DIGESTS[address], 'complete operand mismatch')
    c.require(all(address <= int(row['target'], 16) < address + width
                  for row in flow if row['mnemonic'] in ('b', 'bc')), 'branch outside fixed span')
    calls = tuple((row['address'], row['target']) for row in flow if row['mnemonic'] == 'bl')
    c.require(calls == CALLS[address], 'call schedule mismatch')
    c.require(instructions[-1] == dict(address=f'{address + width - 4:08x}', mnemonic='blr',
                                      BO=20, BI=0, BH=0, LK=0), 'complete terminal return')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, represented_instructions=len(instructions),
                unrepresented_instructions=0, operand_sha256=OPERAND_DIGESTS[address],
                control_flow_count=len(flow), control_flow_sha256=FLOW_DIGESTS[address][1],
                calls=[dict(site=site, target=target) for site, target in calls])


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
                selection_basis=dict(reads=2, bytes=1792, selected_data_cells=0,
                    pointer_following=False, helpers_read=False, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. Both complete bodies '
                    'represented. Reuse existing055fc/10514 evidence without new reads. Global pointer '
                    'values, actor/player records, mode byte and view metadata remain unselected.')


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
