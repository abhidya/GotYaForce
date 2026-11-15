#!/usr/bin/env python3
"""Six frozen initial contact passes, 2684 bytes / 671 instructions.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
new data cells, pointer following, transitive helper reads, or raw/operand-list output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_target_action_frame_evidence as base
import read_archived_mass_preparation_evidence as mass
c, command, normal = base.c, base.command, base.normal

TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2147667840, 536, 'e983f60ae94672202ce930e0db112632eb3ed9b4f6e6a1624e61191e4f760668'), (2147668828, 560, '00140178bfbc1b8045e667ea10990ca28bee61ff1f64a27caac64fd0960242c0'), (2147669388, 568, 'c5a46197dc87a2081493726da867c1d7a8260d19ce89024f62f8c21607243bb6'), (2147668376, 452, 'cd48388d7fc68721c23ec91604ee5e90d8235b6a638f5c830f2a32859212349a'), (2147672520, 224, '470b12b4ca9eb8185cec3058d100094f89086e056a23748770ba2a97923e829b'), (2147666720, 344, 'c8809b685fad83bde8b7379680d8c9809b605c66f65bc2a882718f440d913b09'))
OPERAND_DIGESTS = {2147667840: '35d9f2097b88e448f23458d69d9dfa148bcd0bdc750cddb6136cc4467a9b1f22', 2147668828: '3ca63702b068d79ac1e3d562472742fa605d674a6bf60ec61a3173b4677e577e', 2147669388: '0d609d24b1b807ea41a44587bfb0e79d263dfaa65d840e101280a819935233a3', 2147668376: '05e8e7aba71b6d4e6d96795145c401c1e3d998a515bb24eca96143b23b0aa7fa', 2147672520: 'b60ff989e3c798711f76aa041f98de4c557cefd85b36b221418f1ccdb0fc555f', 2147666720: '0ee0304067c4394ede033f4b26727d17a12a2e71d64f9bdd12963be338a3bb29'}
FLOW_DIGESTS = {2147667840: (20, '208a12d8ce2409e7024c9b85cab68c12698be42005ca951d95c115302b46081e'), 2147668828: (27, 'f7d4cc9ba0416a433fe2d96b2952a9d5a4fc66449ce5c1c0d2f109844e575a9d'), 2147669388: (28, 'f1dd764fd46717046d3c92cf8fed545f026e522926b2ebf12c359c8eb900cba5'), 2147668376: (20, 'ea2a549a326bcf6fefa5b68305bca24ad306e1f96ea988b3c792699853b88d44'), 2147672520: (8, '19299e86a20193930cb027697503be78726d4d587cf23a4206fdf8024edc9f11'), 2147666720: (19, 'f52cb9ffa191c3fd14f6c5c3de1d4e8737d35e8379645f7117afb7041887a2ff')}
CALLS = {2147667840: (('8002d080', '8003a05c'), ('8002d0cc', '80039f6c'), ('8002d134', '80030348'), ('8002d158', '800303b0')), 2147668828: (('8002d4b4', '8003a05c'), ('8002d4c8', '80039f6c'), ('8002d4ec', '80030348'), ('8002d510', '80030420')), 2147669388: (('8002d6d4', '8003a05c'), ('8002d728', '80039f6c'), ('8002d74c', '80030348'), ('8002d770', '80030420')), 2147668376: (('8002d27c', '8003a05c'), ('8002d290', '80039f6c'), ('8002d2f8', '80030348'), ('8002d31c', '800303b0')), 2147672520: (('8002e278', '80035e58'),), 2147666720: (('8002cc08', '80035ca4'), ('8002cc34', '80035ca4'))}
INDIRECT_CALLS = {pc: () for pc, _, _ in RANGES}
REUSED_EVIDENCE = (
    dict(address="80029380", source="outer-frame-evidence-2026-11-14.md", read_here=False),
    dict(address="80053b30", source="mass-preparation-evidence-2026-11-14.md", read_here=False),
)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Reuse proven decoders, adding only existing lwzu representation."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    if word >> 26 == 33: return mass.decode_selected(word, pc)
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
                selection_basis=dict(reads=6, bytes=2684, selected_data_cells=0,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. All six complete bodies '
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
