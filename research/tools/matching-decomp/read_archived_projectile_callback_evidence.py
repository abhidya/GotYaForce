#!/usr/bin/env python3
"""Fixed projectile callback, guard helper and one initial-state dispatch cell.

Read-only stdlib. Whole-snapshot authentication precedes three fixed reads.
No arbitrary address CLI, raw payload output, pointer following, other state
cells or handlers, original execution, model import or authenticator changes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_actor_normal_evidence as normal

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
# The callback has adjacent C/index bounds, not a named map extent.
RANGES = (
    (0x8007dcec, 152, 'ee9edd0cdc0d53686a872a42378eb638ee4b44fdf26e25f7259f6198f71b815a'),
    (0x8008aff0, 32, '8ea8cac06c446278fad05cfae1dbe3ee6b3a321f4bfd1168269ce88283bef951'),
)
# label, fixed cell, expected target identity, SHA-256. Never a read selector.
CELLS = (
    ('initial-state0', 0x802d6f98, 0x8007dd84,
     '82ff512b4b2bdffddacade1b434ca6436328ae1014d77deb3f0db087032876cd'),
)
CALLS = {0x8007dcec: ('8008aff0',), 0x8008aff0: ()}
RETURNS = {0x8007dcec: (('8007dd80', 'blr'),),
           0x8008aff0: (('8008b000', 'bclr'), ('8008b00c', 'blr'))}
INDIRECT_CALLS = {0x8007dcec: ('8007dd6c',), 0x8008aff0: ()}


def decode_selected(word, pc):
    """Selected forms only; all admitted instruction bits have operands."""
    decoded = normal.decode_selected(word, pc)
    allowed = {'stwu', 'mflr', 'stw', 'or', 'lbz', 'lwz', 'extsb', 'cmpi',
               'bc', 'lha', 'cmp', 'addi', 'stb', 'bl', 'addis', 'rlwinm',
               'lwzx', 'mtctr', 'bctrl', 'mtlr', 'blr', 'bclr'}
    if not decoded or decoded['mnemonic'] not in allowed:
        return None
    # The shared decoder names bl but omits its fixed link bit.
    if decoded['mnemonic'] == 'bl':
        decoded = dict(decoded, LK=1)
    return decoded


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
    c.require(tuple((item['address'], item['mnemonic']) for item in instructions
                    if item['mnemonic'] in ('blr', 'bclr')) == RETURNS[address],
              'span return-site mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] == 'bc'), 'branch outside fixed span')
    c.require(tuple(item['target'] for item in instructions if item['mnemonic'] == 'bl') ==
              CALLS[address], 'span direct-call mismatch')
    c.require(tuple(item['address'] for item in instructions if item['mnemonic'] == 'bctrl') ==
              INDIRECT_CALLS[address], 'span indirect-call mismatch')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def cell_evidence(db, mapping, address):
    c.require(type(address) is int, 'cell integer fields')
    selected = [item for item in CELLS if item[1] == address]
    c.require(len(selected) == 1, 'cell not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    label, _, target, expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == 0 and start <= address < address + 4 <= end, 'cell alignment/bounds')
    raw, spans = db.chain(root, address - start, 4, length)
    c.require(len(raw) == 4, 'cell byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected, 'cell digest mismatch')
    actual = c.integer(raw, 0, 'I')
    c.require(actual == target, 'cell target mismatch')
    return dict(label=label, address=f'{address:08x}', end_exclusive=f'{address + 4:08x}',
                width=4, target=f'{actual:08x}', sha256=digest, spans=spans)


def inspect(data, digest):
    # Preserve complete SHA/schema/language/File Bytes/maps/data5 authentication.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    maps = [normal.mapping_evidence(blocks, subs, image, m) for m in (TEXT_MAPPING, DATA3_MAPPING)]
    text, data3 = [item[0] for item in maps]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[item[1] for item in maps],
        ranges=[range_evidence(db, text, pc, width) for pc, width, _ in RANGES],
        cells=[cell_evidence(db, data3, pc) for _, pc, _, _ in CELLS],
        function_coverage=[dict(entry=f'{pc:08x}', end_exclusive=f'{pc + width:08x}',
            selected_width=width, represented_instructions=width // 4,
            unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis=('stored callback identity; preceding map end and adjacent C/index entries; '
                'authenticated terminal return; no named callback map row' if pc == 0x8007dcec else
                'adjacent named C/index entries, map size and authenticated conditional/terminal returns'),
            map_size=None if pc == 0x8007dcec else width) for pc, width, _ in RANGES],
        selection_basis=dict(callback_slot='child+0x0c', callback='8007dcec', table='802d6f98',
            index_field='signed child+0x18', selected_initial_index=0, entry_width=4,
            initial_zero_source='already-authenticated allocator memset boundary; not reread here',
            guard_must_leave_initial_state_unchanged=True, handler_read_here=False,
            unsupported_guard_state=2, guard_state_cell_read_here=False),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
            'live dispatch, runtime integration or playability. All46 instruction operands and three '
            'return sites are represented. Child90 loads before the signed state comparison. Invalid '
            'owner guard stores18=2, calls8aff0, stores82=0, then reloads signed18. Guard helper returns '
            'its input pointer unchanged, optionally setting1d8=1 for type0/3. Initial-state cell0 holds '
            '8007dd84 only when the guard leaves18 at zero. That handler, other state cells, child10c '
            'callback and assets remain unselected. No pointer value determines any read.')


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
