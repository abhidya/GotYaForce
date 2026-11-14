#!/usr/bin/env python3
"""Authenticate six fixed control40 helpers, derived operands only.

Read-only stdlib. One snapshot-path argument; no address/width/dump options,
new scalar/table selection, pointer following, or archived code execution.
See research/decomp/control40-helper-evidence-2026-11-14.md for provenance.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_actor_status_evidence as status

c, command = status.c, status.command
TEXT_START, TEXT_LENGTH = status.TEXT_START, status.TEXT_LENGTH
RANGES = (
    (0x80069210, 172, '3e71a3acd38a50573c3a0b2ab3958a687210a5971ffa61cc351e677f28560d9e'),
    (0x800693fc, 196, '92cbdc2d4b6e5efc0927794ce9d7bf6c2aff94e90daa83d0fd05079622688eb9'),
    (0x8006965c, 152, '57bad1581c5e8afffe9468b6b01632e9b2a95f39a98fc2437241ff0250c7c045'),
    (0x800695c4, 96, 'f6c8236fa71531c633a42b35c6c72a55f765de4e0445343fdd73f0e68f81819f'),
    (0x8006952c, 96, '9cfabeeb65dcf3d78e5577d90e69a90a5fe5a44760fc5fe9b1ac6bb589f1c32a'),
    (0x800691d8, 56, '56208a03f0b329ba5e1d4e531dd7b1f71d9b4e2822a5445f5245d0f611f13fed'),
)
MAP_SIZES = {0x80069210: 172}
CALLS = {
    0x80069210: ((0x800692a8, 0x8006a750),),
    0x800693fc: ((0x80069438, 0x800694c0), (0x8006947c, 0x8006a750)),
    0x8006965c: ((0x800696b0, 0x8006a750),),
    0x800695c4: ((0x80069608, 0x8006a750),),
    0x8006952c: ((0x80069570, 0x8006a750),),
    0x800691d8: ((0x800691f8, 0x800677b0),),
}


def decode_selected(word, pc):
    """Decode the selected scalar forms without executing any instruction."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if word == 0x4e800020:
        return dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0)
    if op == 40:  # Existing cue0-tail lhz form, not a new ISA form.
        return dict(mnemonic='lhz', rD=d, rA=a,
                    displacement=status.traversal.signed(word & 65535, 16))
    if op == 31 and xo in (339, 467):
        c.require(d == 0 and ((b << 5) | a) == 8 and rc == 0, 'unsupported LR form')
    if not (op in (11, 14, 16, 18, 21, 32, 34, 36, 37, 38, 42, 44) or
            (op == 31 and xo in (0, 339, 444, 467, 954))):
        return None
    result = status.decode_selected(word, pc)
    if result is not None and result['mnemonic'] in ('b', 'bl'):
        result['LK'] = rc
    return result


def control_flow(instructions, address, width):
    """Account for all instructions and direct edges, assuming calls return.

    This is static reachability, not a proof of callee behavior or execution.
    Fixed-span digests and independent operand tests pin every branch field.
    """
    c.require(len(instructions) == width // 4 and
              [item['address'] for item in instructions] ==
              [f'{pc:08x}' for pc in range(address, address + width, 4)],
              'complete instruction coverage')
    c.require(instructions[-1] == dict(address=f'{address + width - 4:08x}',
                                      mnemonic='blr', BO=20, BI=0, BH=0, LK=0),
              'terminal return')
    c.require(sum(item['mnemonic'] == 'blr' for item in instructions) == 1,
              'unexpected interior return')
    calls, branches, edges = [], [], {}
    for item in instructions:
        pc, name = int(item['address'], 16), item['mnemonic']
        if name in ('b', 'bc', 'bl'):
            target = int(item['target'], 16)
            c.require(item['AA'] == 0 and item['LK'] == int(name == 'bl'), 'branch AA/LK')
            if name == 'bl':
                calls.append((pc, target))
                edges[pc] = [pc + 4]
            else:
                c.require(address <= target < address + width and target % 4 == 0,
                          'internal branch bounds')
                c.require(target > pc, 'unexpected backward branch')
                if name == 'bc':
                    c.require(item['BO'] in (4, 12) and item['BI'] in (0, 1, 2),
                              'unexpected branch predicate')
                branches.append(dict(item))
                edges[pc] = [target, pc + 4] if name == 'bc' else [target]
        else:
            edges[pc] = [] if name == 'blr' else [pc + 4]
    c.require(tuple(calls) == CALLS[address], 'direct calls mismatch')
    seen, pending = set(), [address]
    while pending:
        pc = pending.pop()
        if pc not in seen:
            c.require(pc in edges, 'fallthrough outside extent')
            seen.add(pc)
            pending.extend(edges[pc])
    c.require(seen == set(edges), 'unreachable instruction within selected extent')
    return dict(terminal_return=f'{address + width - 4:08x}', interior_returns=[],
                internal_branches=branches,
                direct_calls=[dict(site=f'{pc:08x}', target=f'{target:08x}', AA=0, LK=1)
                              for pc, target in calls],
                represented_instructions=len(instructions), cfg_reachable_instructions=len(seen),
                all_internal_edges_forward=True, unrepresented_instructions=0,
                unrepresented_ranges=[])


def range_evidence(db, root, address, width):
    c.require(all(type(value) is int for value in (root, address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    c.require(root == 21 and address % 4 == width % 4 == 0 and
              TEXT_START <= address < address + width <= TEXT_START + TEXT_LENGTH,
              'range root/alignment/bounds')
    raw, spans = db.chain(root, address - TEXT_START, width, TEXT_LENGTH)
    c.require(len(raw) == width, 'range byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'range digest mismatch')
    instructions = []
    for offset in range(0, width, 4):
        decoded = decode_selected(c.integer(raw, offset, 'I'), address + offset)
        c.require(decoded is not None, 'unselected instruction in fixed span')
        instructions.append(dict(address=f'{address + offset:08x}', **decoded))
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions,
                control_flow=control_flow(instructions, address, width),
                map_size=MAP_SIZES.get(address),
                extent_basis='Independent C/index markers and authenticated terminal return' +
                ('; symbol map size172 also agrees' if address in MAP_SIZES
                 else '; no symbol-map row claimed'))


def inspect(data, digest):
    # Unchanged whole-snapshot/schema/metadata/File Bytes/map/data5/control path.
    # c.inspect reads its existing authentication controls; no new scalar windows.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    c.require(c.data5_mapping(blocks, subs, image) == status.DATA5_MAPPING,
              'data5 mapping mismatch')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                authentication='Existing unchanged whole hash, exact schemas, metadata, empty '
                               'File Bytes, address map, complete data5 digest and existing controls',
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH, chain_root=21,
                subblock_type=2, starting_offset=0, source_offset=0,
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                total_new_selected_bytes=768, total_instructions=192,
                caveat='Archived ProgramDB operand authentication only. No original-DOL '
                       'equivalence, original execution, live parity, runtime implementation, '
                       'ownership, or playability established. No new scalar/table/descriptor '
                       'reads or pointer following. Existing 694c0/696f4/69814/699d8 evidence '
                       'is not reselected. Direct callees remain outside these six windows.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('snapshot', type=Path)
    args = parser.parse_args()
    try:
        c.require(args.snapshot.is_file(), 'snapshot is not a regular file')
        c.require(32 <= args.snapshot.stat().st_size <= c.MAX_FILE, 'snapshot size bounds')
        with args.snapshot.open('rb') as stream:
            data = stream.read(c.MAX_FILE + 1)
        c.require(len(data) <= c.MAX_FILE, 'snapshot exceeds size bound')
        print(json.dumps(inspect(data, hashlib.sha256(data).hexdigest()), indent=2, allow_nan=False))
    except (OSError, c.FormatError) as exc:
        print(json.dumps(dict(error=str(exc))), file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
