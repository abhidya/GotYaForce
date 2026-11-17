#!/usr/bin/env python3
"""Active47904 and null-target helpers:544 selected code bytes/136 instructions and four constants.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
pointer following, transitive helper reads, or raw/operand-list output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import struct

import read_archived_matrix_contact_evidence as base
import read_archived_double_action_evidence as double
import read_archived_actor_mode1_evidence as mode1
c, command, normal = base.c, base.command, base.normal

TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2147776772, 296, '79704ea5e729833d36b5d4bb4164d21d3711b0db9e51b63a6bbef9da0ffda41e'), (2147902848, 76, '586315cc74ccba7aad75f08eea721f7c8a6dec5bd837b630231a83b4251131a1'), (2147927848, 152, 'fe69cec08aad2b5a23ae8fce80d8b0aeb1113b2745e6331d3f9304ebdad30c57'), (2147929212, 20, '3596abe8738d7683464fcc48aa718710633cadcd9a737faa93768214043a5d85'))
OPERAND_DIGESTS = {2147776772: 'aa08568e25ff1e7e5c6c38e26b07f0d120ce22d98db31f97c2a35471af2e2b57', 2147902848: 'fb3316618d2346d0aa6f82f3d216455cb2412049e1077324223372af46969b1a', 2147927848: '41be4917fdb411e171ec0f55d7b8c0125f5b037e5ab08c77716a1592f86f7c4e', 2147929212: '87d8f93c65a3801a25fa2c1f3129d9dc3fc13414bcfd72989ec2c8617d347607'}
FLOW_DIGESTS = {2147776772: (12, '46d88adf8f33eec4b7e1eddefa0f9f7231a5463634fa436960841efc19372575'), 2147902848: (4, '0dbeeeae1c4bca753ba0f5ef07485e803189fd495be8d3edae0727c2e53d6d5e'), 2147927848: (2, 'afcc9d55547d38a2f67a4902c474719d7fed649760832e34acd8b64ad84acfd2'), 2147929212: (1, '6eafa92a7a20798062d2947087fe27a340032dcee9bcf24b8a9b1da8997f40da')}
CALLS = {2147776772: (('80047968', '80066580'), ('800479ac', '8006c728')), 2147902848: (('800665b0', '800452a0'),), 2147927848: (), 2147929212: ()}
INDIRECT_CALLS = {pc: () for pc, _, _ in RANGES}
DATA_MAPPING = base.DATA_MAPPING
CONSTANTS = ((2151903452, 4, '3f75c28f'), (2151903416, 8, '4330000080000000'), (2151904916, 4, '3f75c28f'), (2151904928, 8, '4330000080000000'))
UNSELECTED_BRANCHES = (('8006c74c','8006c7c0'),)
REUSED_EVIDENCE = (dict(address='80047904', source='normal-actor-matrix-evidence-2026-11-13.md', read_here=True,
                       note='same prior296byte scope, now complete operand coverage'),)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    if word >> 26 == 63 and (word >> 1) & 1023 == 15:
        return double.decode_selected(word, pc)
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
    c.require(all(any(pc <= int(row['target'],16) < pc+size for pc,size,_ in RANGES)
                  or (row['address'],row['target']) in UNSELECTED_BRANCHES
                  for row in flow if row['mnemonic'] in ('b','bc')), 'branch outside selected coverage/boundary')
    calls = tuple((row['address'], row['target']) for row in flow if row['mnemonic'] == 'bl')
    c.require(calls == CALLS[address], 'call schedule mismatch')
    indirect = tuple(row['address'] for row in flow if row['mnemonic'] == 'bctrl')
    c.require(indirect == INDIRECT_CALLS[address], 'indirect call schedule mismatch')
    terminal = (dict(address='8006c7bc',mnemonic='b',target='8006cc7c',AA=0,LK=0)
                if address == 0x8006c728 else
                dict(address=f'{address+width-4:08x}',mnemonic='blr',BO=20,BI=0,BH=0,LK=0))
    c.require(instructions[-1] == terminal, 'selected terminal mismatch')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, represented_instructions=len(instructions),
                unrepresented_instructions=0, operand_sha256=OPERAND_DIGESTS[address],
                control_flow_count=len(flow), control_flow_sha256=FLOW_DIGESTS[address][1],
                calls=[dict(site=site, target=target) for site, target in calls],
                indirect_call_sites=list(indirect))


def constant_evidence(db, mapping, address, width):
    c.require(type(address) is type(width) is int, 'constant integer fields')
    selected = [row for row in CONSTANTS if row[:2] == (address, width)]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA_MAPPING)
    raw, spans = db.chain(mapping[-1], address - mapping[0], width, mapping[-2])
    c.require(len(raw) == width and raw.hex() == selected[0][2], 'constant bits mismatch')
    return dict(address=f'{address:08x}', width=width, bits=raw.hex(),
                value=struct.unpack('>f' if width == 4 else '>d', raw)[0], spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, mapping = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data, data_mapping = normal.mapping_evidence(blocks, subs, image, DATA_MAPPING)
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    constants = [constant_evidence(db, data, pc, width) for pc, width, _ in CONSTANTS]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[mapping, data_mapping], ranges=ranges, constants=constants,
                selection_basis=dict(reads=8, bytes=568, selected_data_cells=4,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE), unselected_branch_boundaries=list(UNSELECTED_BRANCHES),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. Complete47904 and66580 bodies, only null508 prefix/epilogue of6c728 '
                    'represented. Direct callee bodies, indirect callback targets, global pointer '
                    'values and actor runtime fields remain unselected. The6c728 nonnull body is deliberately outside this reader.')


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
