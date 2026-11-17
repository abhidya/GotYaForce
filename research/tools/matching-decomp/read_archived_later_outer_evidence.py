#!/usr/bin/env python3
"""Four later outer bodies and source tick body, 2492 bytes / 623 instructions.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
new data cells, pointer following, transitive helper reads, or raw/operand-list output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_initial_contact_evidence as base
import read_archived_target_preparation_evidence as target
import read_archived_actor_mode1_evidence as mode1
import read_archived_mass_preparation_evidence as mass
c, command, normal = base.c, base.command, base.normal

TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2147708452, 1216, '1e95c5b5b01321a06768d975a6776e8d00821b1cb0b8100003d4e9f13cf20d77'), (2147532196, 336, '4a1f60baa37fd87e9b9bd776d5fcb4eb01e684984ee553bcbf5ce87b451ff701'), (2147748756, 464, 'd86872d1ddde0d509084f7daad8fed3d8e8e8d2758584cd8cd8c04579478968e'), (2148466480, 468, '795964d3f0af7aad82b5209636797f8b0dd96b739eb564853ba7063e7ab2541d'), (2149609560, 8, '7836ce7cf2facfcda9d887183c84a835cd71b6de5b52dede3efb27d086a23294'))
OPERAND_DIGESTS = {2147708452: 'dd8b9bdf1731d2852f1eb57c4d2babb07597466a2f631dcb54066ee7e82120ce', 2147532196: '477ace7187dd4dd653e14912e961ad4b2f875d22886c11fa285f7f79a33f6f8e', 2147748756: 'b391f9ba3ca4eafc12d848f49674db796c43cd245ab3196c793f31565e3faaad', 2148466480: 'b404a58deab11817386a24b33bcbefbb3e9ef65557b2cdc7d334e4e72243a7c1', 2149609560: '7b1e95251f6982db8280f52c333c9ec1736bd50358be8974baf51873905ca1d6'}
FLOW_DIGESTS = {2147708452: (43, 'e200c85496651f5fdf6d0b833c2d9a5166f12373fcae906c921237777668f68e'), 2147532196: (13, '8e5d81c09e022b4f0d3e52bacbffb869923722aa6a174e50bb74882847976a5b'), 2147748756: (28, '307ca4a3056ede274a28698c144a0c87b72d28cc37a19dc30c6392627e6a5d3a'), 2148466480: (30, 'f84aa18c9243671d06105ca7779811b0026ff2020186ee6cff324b57281d3ff2'), 2149609560: (1, 'c555ae2346b3b8287d386cea1e5944e971ab5808fdb55a45456a51da088c42df')}
CALLS = {2147708452: (('80036f00', '8020bc88'), ('80036f20', '8020ba54'), ('80036f30', '8020ba9c'), ('80036fc4', '8020bc88'), ('8003714c', '8020bc88'), ('8003716c', '8020ba54'), ('8003717c', '8020ba9c'), ('800371f4', '8020bc88')), 2147532196: (('8000be64', '8008ae10'), ('8000be90', '8000c5f8'), ('8000bea0', '8000d46c'), ('8000bed0', '80010b64')), 2147748756: (('80040c64', '80040a00'), ('80040d2c', '80245a74')), 2148466480: (('800eff48', '80207058'), ('800eff9c', '800f036c'), ('800f0060', '800f0414'), ('800f0074', '800f06f0'), ('800f00a4', '800f0414'), ('800f00b8', '800f06f0')), 2149609560: ()}
INDIRECT_CALLS = {2147708452: ('8003705c', '8003728c'), 2147532196: (), 2147748756: (), 2148466480: (), 2149609560: ()}
REUSED_EVIDENCE = (
    dict(address="80029380", source="outer-frame-evidence-2026-11-14.md", read_here=False),
    dict(address="80053b30", source="mass-preparation-evidence-2026-11-14.md", read_here=False),
)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Existing float forms plus primary-ISA addic., divwu and TBL read."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op,xo = word >> 26,(word >> 1) & 1023
    if op == 13:
        # https://www.ibm.com/docs/en/aix/7.1.0?topic=set-addic-ai-add-immediate-carrying-record-instruction
        return dict(mnemonic='addic.',rD=(word >> 21)&31,rA=(word >> 16)&31,
                    immediate=((word & 65535)^32768)-32768)
    if op == 31 and xo == 459:
        # https://www.ibm.com/docs/en/aix/7.1.0?topic=set-divwu-divide-word-unsigned-instruction
        return dict(mnemonic='divwu',rD=(word >> 21)&31,rA=(word >> 16)&31,
                    rB=(word >> 11)&31,OE=0,Rc=word&1)
    if op == 31 and xo == 371:
        # NXP MPC82XINSET.pdf: reversed five-bit TBR fields;268 selects lower timebase.
        tbr = ((word >> 16)&31) | (((word >> 11)&31) << 5)
        c.require(word & 1 == 0 and tbr == 268, 'unselected timebase form')
        return dict(mnemonic='mftb',rD=(word >> 21)&31,TBR=tbr)
    if op == 31 and xo == 11: return mass.decode_selected(word,pc)
    if op == 63 and (xo in (26,12) or xo&31 in (25,30)):
        return target.decode_selected(word,pc)
    if word == 0x4e800421: return mode1.decode_selected(word,pc)
    return base.decode_selected(word,pc)


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
                selection_basis=dict(reads=5, bytes=2492, selected_data_cells=0,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
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
