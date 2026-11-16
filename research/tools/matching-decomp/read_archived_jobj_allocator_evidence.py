#!/usr/bin/env python3
"""Three frozen JObj allocator bodies, 1156 bytes / 289 instructions.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
new data cells, pointer following, transitive helper reads, or raw/operand-list output.
Shared archive authentication, mappings and decoder allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_second_contact_evidence as base
import read_archived_loadjoint_foundation_evidence as foundation
import read_archived_later_outer_evidence as later
import read_archived_frame_continuation_evidence as continuation
c, command, normal = base.c, base.command, base.normal

TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2149961456, 88, 'ad26ba87150230c1921905926a0f14da7f0b687ea22d84d9fe78358a21bbb8f3'), (2149960912, 456, '0024cb0989342ab55988c6dd09be1147557eaeaa00b914e37f7ecffb17acd894'), (2149960300, 612, '7c14a119a9cafa07d9496e82cd275bf27b55525d54335a56e9827ec81e7fe029'))
OPERAND_DIGESTS = {2149961456: '6baab5d2806a5bee81dbcb132acaba8ce34cfd4a7be48012741bdcae4f6e1332', 2149960912: 'cef42c9573f49e4c10c9389244408e5b42c996300c472162224e1bfac3ff420c', 2149960300: '35522e98388d01040fc6027cc0870f032a352f02a32d35a35572e5938ea58c11'}
FLOW_DIGESTS = {2149961456: (4, '023916ac3a97ebdae24392824db6120f55a4960745cde44575746d7f90c7e44f'), 2149960912: (21, '6218a31a00ef44d6fcc64722b87b7777c30e7c206f7fc167507f9e7701204df7'), 2149960300: (34, '62f4fbf352fbf1fef58086125cde41dbc06b7ff5d29c0bcee5fdd915a428235a')}
CALLS = {2149961456: (('8025cf08', '8025ccd0'),), 2149960912: (('8025cd00', '8025ca6c'), ('8025cd68', '8025ca6c'), ('8025ce00', '8025ca6c'), ('8025ce24', '8025aeb8')), 2149960300: (('8025caa0', '80264290'), ('8025cadc', '8025aeb8'), ('8025cafc', '8000540c'), ('8025cb28', '8025aeb8'), ('8025cb48', '800054f4'), ('8025cb64', '8000540c'), ('8025cb80', '8025ce98'), ('8025cbc4', '8025aeb8'), ('8025cbe0', '8000540c'))}
INDIRECT_CALLS = {2149961456: (), 2149960912: (), 2149960300: ()}
REUSED_EVIDENCE = ()


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Only addze is new; OE=1 and reserved rB forms refuse explicitly."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, xo = word >> 26, (word >> 1) & 1023
    if op == 13: return later.decode_selected(word, pc)
    if op == 31 and xo in (202, 714):
        c.require(xo == 202 and ((word >> 11) & 31) == 0, 'unsupported addze OE or reserved rB')
        return dict(mnemonic='addze', rD=(word >> 21) & 31, rA=(word >> 16) & 31, OE=0, Rc=word & 1)
    return foundation.decode_selected(word, pc)


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
                selection_basis=dict(reads=3, bytes=1156, selected_data_cells=0,
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
