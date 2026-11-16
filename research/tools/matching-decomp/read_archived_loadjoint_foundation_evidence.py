#!/usr/bin/env python3
"""Eight frozen LoadJoint foundation bodies, 2212 bytes / 553 instructions.

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
RANGES = ((2149906484, 168, '7097dc1adb66cd754ffdd1fbed2a646eba164a78107a66d948b3470048211569'), (2149905976, 508, '7febacaa8abb14c4ce6f5df392610ab659c2df57373a51f117a27373f5222a59'), (2149910984, 92, 'd5ae463f8ecf70194016e8e41560e6a71738e8ef6c6a7e7fe44a4316aa9836f5'), (2149961864, 200, '91908a91d5ce77429c23d432b62a92afaba86113d25c3c674f9456aa383570a2'), (2149906900, 724, 'dc50fd1932a723b4ec1fed80eebbff8da4d29e9786266d9f3814c5ca22933ecc'), (2149916340, 100, '1aec072d380ef7245c478e5c20eceb57178ddc0ad3a37a68ad85961874549bb7'), (2149917928, 188, 'abc19685bbafdcac5bca360958af62cf052ad680e57cec077dc2f63360657b7e'), (2149960068, 232, 'ffc4f94444b3b48c302cf315a4492fb2f86c7656790ef223b66c0ca00031a34d'))
OPERAND_DIGESTS = {2149906484: '1d24f3a6a817577dbff4f2e095888cdf5914d3f3d8612f694fd35898a9b328ff', 2149905976: 'd939b5e50bf4d5ced02a51a389288a9e2ddf6e919ab73f010ac9553d54fa7d7f', 2149910984: 'e69451de39dd1e8bb35368b8cd9022fd08d37fd65b088de7f1ec6dd39b2ac951', 2149961864: 'ce38060b18cd4a8b09ac7eddc530c3d4de69de5eb93f339331846a3832fe6bf7', 2149906900: 'cae26fb009843d76cde4373bb45ce8713692cb1af20378ca788d56487acecc81', 2149916340: '21deaa56f2dffdaadb9b57ab4edce5337fb6f5cbda16d4a16a7b03208cf4351b', 2149917928: '7055159f04ccfdca18fcc8851f70597d46fff93bd6797be2fe99c797b8d41f40', 2149960068: '48b91183401972b29ea2cef946aaba8cf0b3c9d9d63a99f5a04eab9ab2ba795a'}
FLOW_DIGESTS = {2149906484: (13, '58153181574d2e2db85ab53aeb5be43d04fbe3574b9793029181ea408c54d619'), 2149905976: (31, '281d605edb9592c6972b2879e1f19b9aa67f0cdc2e1119fa047a687ec5429daf'), 2149910984: (6, '800e35e3eb6d00537e7fd8a9088551ad5a98373734af5568715116aa36055f69'), 2149961864: (13, '9d942b9a2177981223945c05664e5d1178f0607dfc3c1602b7612a7e232b58b0'), 2149906900: (57, '29302ba7106b9d3bcc58771f44f03593ba2e4f1fc0963c1e98f709a4e9df0b85'), 2149916340: (3, '40f54323c64e28f818afd25ec1831bb4597dda4d398d21cce4dc82d6d1f6ca7c'), 2149917928: (2, '1341a6b9b3e282a7830dd55f4f6800736a9ecb0394fb08926d5c988876c4dc93'), 2149960068: (9, '29783ee91838c7429f7345b7ecb6147a3a4d55fa19be552983b2d331f6868ef4')}
CALLS = {2149906484: (('8024f864', '8025d4e8'), ('8024f870', '802509c8'), ('8024f87c', '8025d088'), ('8024f894', '80264290'), ('8024f8bc', '8024f9d4')), 2149905976: (('8024f6c8', '8023dae4'), ('8024f6d4', '8025888c'), ('8024f728', '8020aefc'), ('8024f740', '80256dd8'), ('8024f754', '800054f4'), ('8024f764', '802596a4'), ('8024f79c', '8025d4e8'), ('8024f7a8', '802509c8'), ('8024f7b4', '8025d088'), ('8024f7cc', '80264290'), ('8024f804', '8024ff64')), 2149910984: (('802509f0', '8025d088'), ('80250a08', '80264290')), 2149961864: (('8025d0fc', '8000540c'),), 2149906900: (('8024f9e4', '80232a98'), ('8024fa14', '80258778'), ('8024fa28', '8024fd74'), ('8024fa38', '8025983c'), ('8024fa58', '80264290'), ('8024fa8c', '80264290'), ('8024faac', '8023dc4c'), ('8024fae0', '80258778'), ('8024faf4', '8024fd74'), ('8024fb04', '8025983c'), ('8024fb24', '80264290'), ('8024fb34', '8024fd28'), ('8024fb54', '8023dc4c'), ('8024fb88', '80258778'), ('8024fb9c', '8024fd74'), ('8024fba8', '8024fcfc'), ('8024fbc8', '80264290'), ('8024fbd0', '8024fca8'), ('8024fbf0', '8023dc4c'), ('8024fc14', '8024f8dc'), ('8024fc2c', '8024f9d4'), ('8024fc94', '80232ae4')), 2149916340: (), 2149917928: (('8025251c', '8025c984'),), 2149960068: (('8025ca0c', '80264290'), ('8025ca30', '80264290'), ('8025ca44', '800054f4'))}
INDIRECT_CALLS = {2149906484: ('8024f8b0',), 2149905976: ('8024f7e8',), 2149910984: (), 2149961864: ('8025d0b4', '8025d0c4', '8025d0ec', '8025d110', '8025d128'), 2149906900: (), 2149916340: ('80251edc',), 2149917928: (), 2149960068: ('8025c9e8',)}
REUSED_EVIDENCE = ()
CELLS = ((2151336980, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'), (2151336992, 2, '96a296d224f285c67bee93c30f8a309157f0daa35dc5b87e410b78630a09cfc7'), (2151336996, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'), (2151337016, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'), (2151337020, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'), (2151337036, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'), (2151339380, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'), (2151928584, 4, 'de620abd6d3615746360c1d15ce3a56291236d37424124054a49d25e947ffc4d'))


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


def uninitialized_override(blocks,subs,image):
    c.require(blocks.get(9)==['MAIN_uninitialized1','',None,6,0x2000000000000000+0x804360c0-image,2400,0], 'override uninitialized block mismatch')
    c.require(subs.get(9)==[9,3,2400,0,0,0], 'override uninitialized subblock mismatch')
    return dict(address='80436980',width=4,status='uninitialized-no-stored-value')


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, text_fact = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    cells=[];mapping_facts=[text_fact]
    for address,width,_ in CELLS:
        expected=normal.DATA3_MAPPING if address<0x80400000 else ceiling.DATA5_MAPPING
        mapping,fact=normal.mapping_evidence(blocks,subs,image,expected)
        if fact not in mapping_facts: mapping_facts.append(fact)
        cells.append(cell_evidence(db,mapping,address,width))
    override=uninitialized_override(blocks,subs,image)
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=mapping_facts, ranges=ranges,cells=cells,override=override,
                selection_basis=dict(reads=16, bytes=2242, selected_data_cells=8, uninitialized_metadata_cells=1,
                    pointer_following=False, helpers_read=True, global_payloads_read=False,
                    original_execution=False, operand_listing_output=False),
                reused_evidence=list(REUSED_EVIDENCE),
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, '
                    'MATCH, live dispatch, runtime integration or playability. All eight complete bodies '
                    'represented. Unlisted callee bodies and initialized runtime class targets, bank pointer '
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
