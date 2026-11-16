#!/usr/bin/env python3
"""Three frozen JObj class-initialization bodies232 bytes/58 instructions and five cells20 bytes.

Read-only stdlib, existing authenticated snapshots only. No arbitrary selections,
unlisted data cells, pointer following, transitive helper reads, or raw/operand-list output.
Shared archive authentication, mappings, decoders and allowlists are unchanged.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_second_contact_evidence as base
import read_archived_projectile_resource_evidence as resource
import read_archived_target_selector_evidence as target
import read_archived_mass_preparation_evidence as mass
import read_archived_control_effect_evidence as effect
import read_archived_actor_ceiling_evidence as ceiling
import read_archived_frame_continuation_evidence as continuation
c, command, normal = base.c, base.command, base.normal

TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2149952696, 68, '03ddd15e57721d3bb773846d2b89dc325d99ebd68ba2146e61e22bb1859423fe'), (2149961708, 156, '1588411707b88419db9c408e79e945c4a2bd19052cf560df1fea5a79d1a3dc59'), (2149961544, 8, 'd4e9e7520ef19698837e384bfe1708ac4b91fcf26b16ec098ec21c1e344ad3db'))
OPERAND_DIGESTS = {2149952696: 'bec396506bc9a03f59b366c61dbd0bec05e925b8b10c6c83a360d499152c865a', 2149961708: 'f98853d65c6a1236bcefde26360a13272b7df7872411f74a3084faa4574c6ef7', 2149961544: 'c067af06462ef417ca6969443dd290f93ce9b142a25a140fdc397ccf6b0485ff'}
FLOW_DIGESTS = {2149952696: (2, 'bd09db79a8cebbc8b9baac7571d459f4f8bf12258ea570427785a3c684b1a800'), 2149961708: (1, '40c65fb34288f0f3ecfd24aca6e5fed8863c53a98fd84e0e8e7113aeb0809155'), 2149961544: (1, '89d0517db4d44695dc989913c18ef0af4dfc3057ed1d2cf0bfd9b6410831781f')}
CALLS = {2149952696: (('8025ace8', '8025c984'),), 2149961708: (), 2149961544: ()}
INDIRECT_CALLS = {2149952696: (), 2149961708: (), 2149961544: ()}
REUSED_EVIDENCE = ()
CELLS = ((2151336976, 4, 'd94cc33eb46a3acaa9e27f11cd085a72ae594cfbb4e08409986fc4ec5d7bf4e3'), (2151339336, 4, '4294dac7a46e36c7a4dd890bf760d681bbf6dee05aa5e65841a42721efefd692'), (2151339340, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'), (2151339696, 4, '7932fa2549e5bd8557feeb27b0538e8f3c536d7816c6073ebb9bd79b0e8c7434'), (2151339700, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'))

def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Compose existing exact decoders only; shared allowlists unchanged."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op = word >> 26
    if op == 25: return target.decode_selected(word, pc)
    if op == 28: return mass.decode_selected(word, pc)
    if op == 31 and ((word >> 1) & 1023) == 26: return effect.decode_selected(word, pc)
    return resource.decode_selected(word, pc)


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


def cell_evidence(db, mapping, address, width):
    c.require(type(address) is type(width) is int, 'cell integer fields')
    selected=[s for s in CELLS if s[:2]==(address,width)]
    c.require(len(selected)==1,'cell not allowlisted')
    expected=normal.DATA3_MAPPING if address<0x80400000 else ceiling.DATA5_MAPPING
    normal.require_mapping(mapping,expected)
    raw,spans=db.chain(mapping[-1],address-mapping[0],width,mapping[-2])
    digest=hashlib.sha256(raw).hexdigest()
    c.require(len(raw)==width and digest==selected[0][2],'cell digest/width mismatch')
    return dict(address=f'{address:08x}',width=width,sha256=digest,value=int.from_bytes(raw,'big'),spans=spans)


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, text_fact = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    cells=[];mapping_facts=[text_fact]
    for address,width,_ in CELLS:
        expected=normal.DATA3_MAPPING if address<0x80400000 else ceiling.DATA5_MAPPING
        mapping,fact=normal.mapping_evidence(blocks,subs,image,expected)
        if fact not in mapping_facts: mapping_facts.append(fact)
        cells.append(cell_evidence(db,mapping,address,width))
    values={int(cell['address'],16):cell['value'] for cell in cells}
    c.require(values[0x803acc10]==0x802524e8 and values[0x803ad548]==0x8025acb8 and values[0x803ad6b0]==0x8025cfec,'initializer targets differ')
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=mapping_facts, ranges=ranges,cells=cells,
                selection_basis=dict(reads=8, bytes=252, selected_data_cells=5, uninitialized_metadata_cells=0,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. All three complete bodies '
                    'represented. Unlisted allocator bodies and runtime bank pointer '
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
