#!/usr/bin/env python3
"""Three frozen physical actor helper bodies, 2448 bytes / 612 instructions.

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
import read_archived_actor_mode1_evidence as mode1
import read_archived_target_preparation_evidence as target
import read_archived_actor_status_evidence as status
import read_archived_terrain_orientation_evidence as terrain

outer = prior.outer

c, command, normal = outer.c, outer.command, outer.normal
TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2147855592, 1112, '898fe12bdf49c8fc785958cf940ae1d6eca74d58e23214f32d652a4ea2e6e2eb'), (2147856704, 376, '522ef5010bfd4aed533b4d5d8213cead2c3e322bae7320095566c2c80a8cf90d'), (2147857080, 960, '0fe8b247c7947c3e9fa6f65e91f1f30d2f132e374a91e86d612e7cb8cdb20968'))
OPERAND_DIGESTS = {2147855592: '4854b74cb7267ffcf526fd200cff0472fed05c5107520b29140973dfa5564d88', 2147856704: '1f61d07db65cc4dc3c7cb36b879baf3f87bbdf45b7d489089fca910f2950c760', 2147857080: 'f8229b6528ed49b101d3cab1b201fca506704bb67811279e05988f612aa5c75c'}
FLOW_DIGESTS = {2147855592: (50, '32d3ee505ba38ae443a8b83ba6399541b66def8362969f9a5c7f43d18c3d3d43'), 2147856704: (14, '77277cd92ab3880d47fe840c80a770d0eddf9ad888289736713725bb1047abe7'), 2147857080: (45, '6793d788fdc7b65da0ebdc44f80258dc7ff6b93361c109b99b6ada82494ff05a')}
CALLS = {2147855592: (('8005ad88', '8006abb8'), ('8005ad98', '8006abb8'), ('8005adb8', '800f6654'), ('8005adc4', '800f036c'), ('8005adcc', '8006a980'), ('8005af2c', '8003d964'), ('8005afdc', '800452a0'), ('8005b048', '80045204'), ('8005b05c', '80045238'), ('8005b070', '80068138'), ('8005b078', '80068138'), ('8005b0d4', '8006a868'), ('8005b0fc', '8006a868')), 2147856704: (('8005b214', '8006826c'),), 2147857080: (('8005b440', '8008b480'), ('8005b4c0', '8005b678'), ('8005b4d0', '8005c15c'), ('8005b4d8', '8005c15c'), ('8005b520', '80067f54'), ('8005b52c', '8006a750'), ('8005b538', '8006a750'), ('8005b594', '800061a8'), ('8005b5c0', '80067f54'))}
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
                selection_basis=dict(reads=3, bytes=2448, selected_data_cells=0,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
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
