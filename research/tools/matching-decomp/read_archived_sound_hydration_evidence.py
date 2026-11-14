#!/usr/bin/env python3
"""Fixed ordinary-Double metadata, initialized-row and reached-sound evidence.

Read-only stdlib. Authenticate full existing snapshots, schemas and mappings
before fixed literal selections. The 296-byte sound INSPECTION window ends at
an independently named adjacent descriptor, not an asserted sound-table end.
Decode only chains selected by the two fixed ordinary descriptors, entirely
inside that already read window. No dynamic archive read, raw whole-window
output, instruction execution, constructor execution, or new assets.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_actor_normal_evidence as normal
import read_archived_double_action_evidence as double

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
RANGES = ((0x8004bb14, 756, '63f0151abf89a6275e77bc14f1b6e842d74cc6b5bc2d7d27430690d5dad89c8a'),)
# label, literal address, width, SHA-256. Slots were separately fixed after the
# group-cell selection; independent descriptor starts predict their offsets.
DATA_WINDOWS = (
    ('double-descriptor-active-mask', 0x8033af7a, 1, '084fed08b978af4d7d196a7446a86b58009e636b611db16211b65a9aadff29c5'),
    ('double-descriptor-fallbacks', 0x8033b036, 2, 'b413f47d13ee2fe6c845b2ee141af81de858df4ec549a58b7970bb96645bc8d2'),
    ('family-group4', 0x802bd788, 2, '3f2d2a889d22530bd1abdc40ff1cbb23ca53ae3f1983e58c70d46a15c120e780'),
    ('group4-slot0', 0x802bd8a4, 2, '1585c80c682bcc8c6d1e1e2436faaf76fa8cd2f447ad91b0be1fcdb59d9cb9d5'),
    ('group4-slot1', 0x802bd8a6, 2, 'b4eb2237d68a6a5c7b9da1353d74d901ea68dcf5727ae97a1554e5aaa0de0531'),
    ('ordinary-ground-descriptor', 0x802bdd60, 20, '2301ecf31b1bfc0d124f0289f501ca6dc321019541be202a693e709c6134cd3a'),
    ('ordinary-air-descriptor', 0x802bdd74, 20, '99ee2f74daaae93c627e24d4955b95ba4c54dcc025a34828b47fa432d2d586c1'),
    ('bounded-sound-inspection', 0x802d3ca0, 296, 'fe09942ed6f070ce7cc9f3534d17a0e2497927e10d18de0a0aa2d2a9cf988a82'),
)
SOUND_BASE = 0x802d3ca0
SOUND_WIDTH = 296


def decode_selected(word, pc):
    """Existing explicit PPC forms represent all 189 initializer instructions."""
    return double.decode_selected(word, pc)


def range_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'range integer fields')
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
    c.require(instructions[-1]['mnemonic'] == 'blr', 'span terminal return mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] in ('b', 'bc')),
              'non-call branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def data_window(db, mapping, address, width):
    """Return private bytes plus provenance; caller never emits the sound window."""
    c.require(all(type(value) is int for value in (address, width)), 'window integer fields')
    selected = [item for item in DATA_WINDOWS if item[1:3] == (address, width)]
    c.require(len(selected) == 1, 'window not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(start <= address < address + width <= end, 'window bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'window byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][3], 'window digest mismatch')
    return raw, dict(label=selected[0][0], address=f'{address:08x}',
                     end_exclusive=f'{address + width:08x}', width=width, sha256=digest, spans=spans)


def descriptor_fields(raw):
    """Every byte of a selected 20-byte descriptor has an explicit numeric field."""
    c.require(type(raw) is bytes and len(raw) == 20, 'descriptor byte width')
    return dict(scaleIndex32=raw[0], reserved01=raw[1], reserved02=raw[2], reserved03=raw[3],
        part0=dict(selector2a=raw[4], selector2b=raw[5], flags=raw[6], rewind26=raw[7],
                   auxiliary37=raw[8], fallbackBE=raw[9], fallbackBF=raw[10], reserved0b=raw[11]),
        part1=dict(selector2a=raw[12], selector2b=raw[13], flags=raw[14], rewind26=raw[15],
                   auxiliary37=raw[16], byte1d98=raw[17], byte1d99=raw[18], byte1d9b=raw[19]))


def reached_chains(window, mask, descriptors):
    """Pure bounded decoding; never receives an archive or reads beyond window."""
    c.require(type(window) is bytes and len(window) == SOUND_WIDTH, 'sound inspection width')
    c.require(type(mask) is int and mask == 3, 'selected active mask mismatch')
    c.require(type(descriptors) is list and len(descriptors) == 2, 'selected descriptors required')
    c.require([row[0] for row in descriptors] == [0x802bdd60, 0x802bdd74], 'descriptor identity mismatch')
    result = []
    for address, raw in descriptors:
        fields = descriptor_fields(raw)
        for part in range(2):
            index = fields[f'part{part}']['auxiliary37']
            chain = dict(descriptor=f'{address:08x}', part=part, selector=index,
                         signed_selector=normal.signed(index, 8), records=[])
            if index == 255:
                chain['closed'] = True
                chain['termination'] = 'source signed-minus-one skip'
                result.append(chain)
                continue
            c.require(index < 128, 'negative non-sentinel sound selector')
            offset = index * 8
            while True:
                c.require(0 <= offset and offset + 8 <= len(window), 'reached chain exceeds fixed inspection window')
                row = window[offset:offset + 8]
                chain['records'].append(dict(address=f'{SOUND_BASE + offset:08x}', table_offset=offset,
                    width=8, index=offset // 8, frame=c.integer(row, 0, 'H'), windowFlag=row[2],
                    mode=row[3], soundId=c.integer(row, 4, 'H'), continuation=row[6], pad=row[7],
                    sha256=hashlib.sha256(row).hexdigest()))
                if row[6] == 255:
                    chain['closed'] = True
                    chain['termination'] = 'current record byte6 is ff'
                    break
                offset += 8
            result.append(chain)
    return result


def inspect(data, digest):
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    maps = [normal.mapping_evidence(blocks, subs, image, m) for m in (TEXT_MAPPING, DATA3_MAPPING)]
    text, data3 = [item[0] for item in maps]
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    # All literal reads finish before any numeric selector is interpreted.
    selections = [(pc, *data_window(db, data3, pc, width)) for _, pc, width, _ in DATA_WINDOWS]
    payloads = {pc: raw for pc, raw, _ in selections}
    mask = payloads[0x8033af7a][0]
    group = c.integer(payloads[0x802bd788], 0, 'h')
    slots = [c.integer(payloads[pc], 0, 'h') for pc in (0x802bd8a4, 0x802bd8a6)]
    c.require(mask == 3 and group == 0x124 and slots == [0x4bc, 0x4d0], 'selector value mismatch')
    c.require(0x802bd780 + group == 0x802bd8a4 and
              [0x802bd8a4 + value for value in slots] == [0x802bdd60, 0x802bdd74], 'fixed lookup relation mismatch')
    descriptors = [(pc, payloads[pc]) for pc in (0x802bdd60, 0x802bdd74)]
    chains = reached_chains(payloads[SOUND_BASE], mask, descriptors)
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[item[1] for item in maps], ranges=ranges,
        windows=[report for _, _, report in selections], activeMask579=mask,
        descriptor_defaults=dict(address='8033b036', bytebe=payloads[0x8033b036][0], bytebf=payloads[0x8033b036][1]),
        lookup=dict(family_base='802bd780', group=4, group_cell='802bd788', group_displacement=group,
                    group_base='802bd8a4', slot_cells=['802bd8a4', '802bd8a6'], slot_displacements=slots,
                    descriptor_addresses=['802bdd60', '802bdd74']),
        descriptors=[dict(address=f'{pc:08x}', width=20, **descriptor_fields(raw)) for pc, raw in descriptors],
        reached_sound_chains=chains,
        initialized_state=dict(banks=2, parts_per_bank=4, row_stride=64, row_base_offset=0x1ad4,
            zeroed_width=64, bank33='bank index', part34='part index', auxiliary37=255,
            boundary='Decoded state after source initializer; this reader does not execute it.'),
        function_coverage=[dict(entry='8004bb14', end_exclusive='8004be08', selected_width=756,
            represented_instructions=189, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='adjacent named C markers chunk_0006.c:1237/1393 and _index.tsv:919/920; authenticated return',
            map_size=None)],
        caveat='Archived ProgramDB static evidence only. No original-DOL identity, executed initializer, '
            'full actor constructor, model topology, playback, audio, hardware, production or playability proof. '
            'The sound inspection window is not a global table-extent claim. Only reached chains are decoded '
            'and emitted; unrelated records are not output. Inactive parts2/3 retain explicit initialized ff '
            'only at that stated boundary. Actual ordinary start uses active mask3; model/DAT inputs remain separate.')


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
