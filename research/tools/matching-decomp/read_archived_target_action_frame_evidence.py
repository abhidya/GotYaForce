#!/usr/bin/env python3
"""One frozen target/action frame body, 3712 bytes / 928 instructions.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
new data cells, pointer following, transitive helper reads, or raw/operand-list output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_stage_dispatch_evidence as base
import read_archived_actor_mode1_evidence as mode1
import read_archived_target_preparation_evidence as target
import read_archived_target_selector_evidence as selector
import read_archived_object_allocator_evidence as allocator
import read_archived_actor_normal_evidence as normal
import read_archived_double_action_evidence as double
c, command = base.c, base.command

TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2147662612, 3712, '9aa80c3f876242ebee4cbf8afd5ede6938e90b767f8da7f4f8d9ab6d4fad1911'),)
OPERAND_DIGESTS = {0x8002bb14: 'de94f84feeb065eb4739bb7f542796a567e5707f01aec7cabccd3ee47147336a'}
FLOW_DIGESTS = {0x8002bb14: (191, 'cea4cb7dea86366a9de010d2e424d84cb1a1a6ee2772f31e1bc933ae32428325')}
CALLS = {0x8002bb14: (('8002bbe4', '8002cda4'), ('8002bd44', '8002cc78'), ('8002bd4c', '8002cc78'), ('8002bd54', '8002cc78'), ('8002bd5c', '8002cc78'), ('8002bd64', '8002cc78'), ('8002bd6c', '8002cc78'), ('8002bd84', '8002cda4'), ('8002bd98', '8002cf80'), ('8002bd9c', '8002d35c'), ('8002bda0', '8002d58c'), ('8002bda4', '8002d198'), ('8002bda8', '8002e1c8'), ('8002bdac', '8002cb20'), ('8002be14', '8003d6e4'), ('8002be84', '8020bafc'), ('8002be9c', '8020bab8'), ('8002bf44', '8003f320'), ('8002bf7c', '8003f320'), ('8002bf9c', '8002caa8'), ('8002bff0', '8003f320'), ('8002c058', '8002caa8'), ('8002c0a4', '8002caa8'), ('8002c0e4', '8002caa8'), ('8002c0f0', '8002caa8'), ('8002c13c', '8003f320'), ('8002c1c0', '8002caa8'), ('8002c218', '8002caa8'), ('8002c270', '8002caa8'), ('8002c2dc', '8002caa8'), ('8002c2e8', '8002caa8'), ('8002c354', '8002caa8'), ('8002c360', '8002caa8'), ('8002c3d0', '8002caa8'), ('8002c3dc', '8002caa8'), ('8002c428', '8002caa8'), ('8002c434', '8002caa8'), ('8002c440', '8002caa8'), ('8002c460', '8003f320'), ('8002c488', '8020b7a8'), ('8002c49c', '8002caa8'), ('8002c4c0', '8002ce44'), ('8002c4c4', '8002d7c4'), ('8002c4c8', '8002df08'), ('8002c4cc', '8002db58'), ('8002c534', '8002f8dc'), ('8002c584', '8003d444'), ('8002c5a0', '8005c290'), ('8002c5d0', '800681e4'), ('8002c5f4', '8006ace8'), ('8002c600', '800680d4'), ('8002c620', '8006ace8'), ('8002c62c', '800680d4'), ('8002c65c', '8006ab04'), ('8002c668', '800680d4'), ('8002c680', '8005c290'), ('8002c6b8', '8003d3e8'), ('8002c6c0', '8005c290'), ('8002c6d0', '800680d4'), ('8002c6dc', '8005bbc0'), ('8002c720', '80159168'), ('8002c768', '8006abd4'), ('8002c798', '8006ab04'), ('8002c7e4', '8020bafc'), ('8002c7fc', '8020bab8'), ('8002c86c', '8005a580'), ('8002c888', '800466dc'), ('8002c91c', '8002c994'))}
INDIRECT_CALLS = {0x8002bb14: ()}
REUSED_EVIDENCE = (
    dict(address="80029380", source="outer-frame-evidence-2026-11-14.md", read_here=False),
    dict(address="80053b30", source="mass-preparation-evidence-2026-11-14.md", read_here=False),
)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Only required forms; unchanged prior decoders plus documented stfsx."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, xo = word >> 26, (word >> 1) & 1023
    if op == 31 and xo == 663:
        # IBM ISA: X-form op31, FRS, RA, RB, XO663, unused final bit.
        # https://www.ibm.com/docs/en/aix/7.1.0?topic=set-stfsx-store-floating-point-single-indexed-instruction
        c.require(word & 1 == 0, 'reserved stfsx bit')
        return dict(mnemonic='stfsx', fS=(word >> 21) & 31,
                    rA=(word >> 16) & 31, rB=(word >> 11) & 31)
    if op == 31 and xo == 32: return selector.decode_selected(word, pc)
    if op == 31 and xo in (343, 407): return allocator.decode_selected(word, pc)
    if (op == 63 and xo in (32, 72)) or (op == 19 and xo == 449):
        return mode1.decode_selected(word, pc)
    if op == 24: return target.decode_selected(word, pc)
    if op == 31 and xo == 922: return normal.decode_selected(word, pc)
    if op == 31 and xo == 104: return double.decode_selected(word, pc)
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
                selection_basis=dict(reads=1, bytes=3712, selected_data_cells=0,
                    pointer_following=False, helpers_read=False, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. The complete body '
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
