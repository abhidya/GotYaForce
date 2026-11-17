#!/usr/bin/env python3
"""Five frozen second-contact bodies, 2880 bytes / 720 instructions.

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
import read_archived_frame_continuation_evidence as continuation
c, command, normal = base.c, base.command, base.normal

TEXT_MAPPING = normal.TEXT_MAPPING
RANGES = ((2147667524, 76, '18b249a49dc819bc3e9d29548241e69cba1aa2a3eced9dc011c807dac7a325bd'), (2147667600, 240, '59dfbede2aa96fbce042cfd535cc233fb16df309ad4c7d5f30f8ac50afcb567e'), (2147669956, 916, 'de5a3ee6973ac13185bfa04dd4bb22e51d838140d0c0c6ca54a4d879faeccc92'), (2147671816, 704, '63d85aedf020cb22b956652399476a95e802f67787b1d813ca9f2aa30f2e8de4'), (2147670872, 944, '4aa097fc70080cd5b6c849d879cd20b39efebb359b80fb70b6a02c486ba38238'))
OPERAND_DIGESTS = {2147667524: 'd7c67292166ed8bc0ae258316d63420aaa99b6ac9eda43699dd533ca8f8db4b8', 2147667600: '8b04d56a189b3937f35cb20b8606ffcc580bce9309534ca6f74dab5fce171ce2', 2147669956: '441121704991c6463c37d730028fac7f907385431fba54162efdb8687c769a38', 2147671816: '05ccc6d482cd30bf97642b357fff67f8c596dfb0e5d54ff0e3a9a669ace1d763', 2147670872: '7a1bd4f1a2806480ff282c92436de4acaf0f85e27201ee7532e7592d49257b92'}
FLOW_DIGESTS = {2147667524: (5, 'e1dabdac97678c4a0b8febf755422de3b30f0e947a750e5264fbe375b8c24d41'), 2147667600: (11, 'acfd75d87a9abeab59dad891b4a57b66f46cf7c1352a2dd61f2695e4dda29fdb'), 2147669956: (48, '3a560b50dd66ebfc8a0f57d1f2f88d96ecbc8c383259085204a85d9478c4e0de'), 2147671816: (34, 'd71cfc6919d311bdcc2f37ba4d261f202ca81815f5afa4334fe10fd79ad33b54'), 2147670872: (51, '16789bd9b3ca8716ac91e67193a22efa4cb15059877281826bec875f34bcae19')}
CALLS = {2147667524: (('8002ce58', '8002ce90'), ('8002ce60', '8002ce90'), ('8002ce6c', '8002ce90')), 2147667600: (('8002cf14', '8020ba54'),), 2147669956: (('8002d89c', '8002fd7c'), ('8002d930', '80039f6c'), ('8002d9d4', '80030348'), ('8002d9f8', '80030490'), ('8002da14', '8002e2a8'), ('8002da24', '8020bc88'), ('8002daa8', '8020ba78'), ('8002dab0', '8020bafc'), ('8002dad0', '8020ba54'), ('8002dae0', '8020ba54'), ('8002daf0', '8020ba9c'), ('8002db00', '8020ba54'), ('8002db24', '8002e2a8')), 2147671816: (('8002dfb4', '8002fd7c'), ('8002dfc8', '80039f6c'), ('8002e044', '80030348'), ('8002e068', '80030490'), ('8002e084', '8002e2a8'), ('8002e094', '8020bc88'), ('8002e118', '8020ba78'), ('8002e120', '8020bafc'), ('8002e140', '8020ba54'), ('8002e150', '8020ba54'), ('8002e160', '8020ba9c'), ('8002e170', '8020ba54'), ('8002e194', '8002e2a8')), 2147670872: (('8002dc58', '8002fd7c'), ('8002dcec', '80039f6c'), ('8002dd68', '80030348'), ('8002dd8c', '80030490'), ('8002dda8', '8002e2a8'), ('8002ddb8', '8020bc88'), ('8002de58', '8020ba78'), ('8002de60', '8020bafc'), ('8002de80', '8020ba54'), ('8002de90', '8020ba54'), ('8002dea0', '8020ba9c'), ('8002deb0', '8020ba54'), ('8002ded4', '8002e2a8'))}
INDIRECT_CALLS = {2147667524: (), 2147667600: ('8002cef4',), 2147669956: ('8002db18',), 2147671816: ('8002e188',), 2147670872: ('8002dec8',)}
REUSED_EVIDENCE = (
    dict(address="80029380", source="outer-frame-evidence-2026-11-14.md", read_here=False),
    dict(address="80053b30", source="mass-preparation-evidence-2026-11-14.md", read_here=False),
)


def semantic_digest(rows):
    return hashlib.sha256(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def decode_selected(word, pc):
    """Compose unchanged initial-contact and proven bctrl decoders."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    if word == 0x4e800421: return continuation.decode_selected(word, pc)
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
                selection_basis=dict(reads=5, bytes=2880, selected_data_cells=0,
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
