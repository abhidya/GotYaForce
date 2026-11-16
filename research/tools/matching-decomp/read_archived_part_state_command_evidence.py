#!/usr/bin/env python3
"""Fixed opcode02/03 bodies and ordinary ground/air command-prefix evidence.

Read-only stdlib. Authenticate the complete archived snapshot before six
literal selections. No command-table read, pointer following, arbitrary-address
CLI, original-code execution, bank-header hydration, or opcode08 admission.
The four data windows cover exactly ground28/air32 through their first wait;
their decoded fields are static evidence, not an executed parser result.
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
# Independently documented adjacent handler entries, not followed table values.
RANGES = (
    (0x8004c424, 100, 'be8ac95c75902d94a0afcbb214ac797ca8f501e0676336d015a424da509cc839'),
    (0x8004c488, 84, 'f0408efcd1b500c334e09862a1a4f0209c4aab0205b2184750565a043cbe6eb3'),
)
# Keep the separately justified continuations distinct from the initial20 bytes.
DATA_WINDOWS = (
    ('ground-initial20', 0x802be5ee, 20, '14f850a2bf4697c92ac063e5b35fe68f5b54892c8653dd313e53fe3903ebdff6'),
    ('ground-continuation8', 0x802be602, 8, '8666d68f6b5964c5f8b774f3c4d2046a920342700c737366062abbd4c7841918'),
    ('air-initial20', 0x802be656, 20, '6186d688a629f42df51983a88011287bc65c8e74133aa53f5f7f67d32adeadfa'),
    ('air-continuation12', 0x802be66a, 12, '5053f080e446d14bbd04be06873b151c6dea341ac08b390863cf98ea957bdfad'),
)
CONDITIONAL_RETURNS = (0x8004c434, 0x8004c47c, 0x8004c498, 0x8004c4b4)
RETURNS = {0x8004c424: (0x8004c434, 0x8004c474, 0x8004c47c, 0x8004c484),
           0x8004c488: (0x8004c498, 0x8004c4b4, 0x8004c4d8)}


def decode_selected(word, pc):
    """Only the selected integer PPC forms, with every encoded operand retained."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, rc = (word >> 1) & 1023, word & 1
    if op == 19:
        c.require(word == 0x4e800020 or (word == 0x4d820020 and pc in CONDITIONAL_RETURNS),
                  'unselected branch-register form')
        return dict(mnemonic='blr' if word == 0x4e800020 else 'bclr', BO=d, BI=a, BH=0, LK=0)
    if op == 16:
        c.require(word & 3 == 0 and (d, a) == (4, 2), 'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op in (10, 11):
        c.require(d == 0, 'unselected comparison fields')
        return dict(mnemonic='cmpli' if op == 10 else 'cmpi', BF=0, L=0, rA=a,
                    immediate=word & 65535 if op == 10 else normal.signed(word & 65535, 16))
    if op == 14:
        return dict(mnemonic='addi', rD=d, rA=a, immediate=normal.signed(word & 65535, 16))
    if op == 21:
        return dict(mnemonic='rlwinm', rS=d, rA=a, SH=b, MB=(word >> 6) & 31,
                    ME=(word >> 1) & 31, Rc=rc)
    if op == 26:
        return dict(mnemonic='xori', rS=d, rA=a, immediate=word & 65535)
    if op in (32, 34, 36, 38, 40):
        name, reg = {32: ('lwz', 'rD'), 34: ('lbz', 'rD'), 36: ('stw', 'rS'),
                     38: ('stb', 'rS'), 40: ('lhz', 'rD')}[op]
        return dict(mnemonic=name, **{reg: d}, rA=a, displacement=normal.signed(word & 65535, 16))
    if op == 31 and xo == 954:
        c.require(b == 0, 'reserved sign-extension fields')
        return dict(mnemonic='extsb', rS=d, rA=a, Rc=rc)
    if op == 31 and xo == 444:
        return dict(mnemonic='or', rS=d, rA=a, rB=b, Rc=rc)
    return None


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
    c.require(tuple(int(item['address'], 16) for item in instructions
                    if item['mnemonic'] in ('blr', 'bclr')) == RETURNS[address], 'return-site mismatch')
    c.require(all(address <= int(item['target'], 16) < address + width
                  for item in instructions if item['mnemonic'] == 'bc'), 'branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def data_window(db, mapping, address, width):
    """Private selected bytes plus provenance, never an arbitrary range reader."""
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


def prefix_fields(address, initial, continuation):
    """Decode only two literal prefix pairs; this function cannot access an archive."""
    c.require(type(address) is int and address in (0x802be5ee, 0x802be656), 'prefix identity')
    air = address == 0x802be656
    c.require(type(initial) is bytes and len(initial) == 20 and type(continuation) is bytes and
              len(continuation) == (12 if air else 8), 'prefix byte widths')
    for pc, raw in ((address, initial), (address + 20, continuation)):
        selected = [item for item in DATA_WINDOWS if item[1:3] == (pc, len(raw))]
        c.require(len(selected) == 1 and hashlib.sha256(raw).hexdigest() == selected[0][3],
                  'prefix digest mismatch')
    raw = initial + continuation
    schedule = ((0, 8, 1), (8, 8, 2), (16, 8, 3)) + (
        ((24, 4, 8), (28, 4, 0)) if air else ((24, 4, 0),))
    records = []
    for offset, width, opcode in schedule:
        row = raw[offset:offset + width]
        c.require(len(row) == width and row[0] == opcode, 'fixed record boundary/opcode')
        if opcode == 1:
            fields = dict(group=row[1], slot=row[2], mode=row[3], transition=row[4],
                          reserved05=row[5], start_signed=c.integer(row, 6, 'h'))
        elif opcode == 2:
            fields = dict(selector582=row[1], selector582_signed=normal.signed(row[1], 8),
                          part0_state1b=row[2], part0_auxiliary1c=row[3], byte6e8=row[4],
                          byte6e9=row[5], reserved06=row[6], reserved07=row[7])
        elif opcode == 3:
            fields = dict(part1_state1b=row[1], part1_auxiliary1c=row[2], reserved03=row[3],
                          reserved04=row[4], reserved05=row[5], control_unsigned=c.integer(row, 6, 'H'))
        elif opcode == 8:
            fields = dict(reserved01=row[1], reserved02=row[2], operand_signed=normal.signed(row[3], 8))
        else:
            fields = dict(mode=row[1], wait_signed=c.integer(row, 2, 'h'))
        records.append(dict(address=f'{address + offset:08x}', width=width, opcode=opcode,
                            sha256=hashlib.sha256(row).hexdigest(), **fields))
    return dict(label='air' if air else 'ground', address=f'{address:08x}',
        end_exclusive=f'{address + len(raw):08x}', width=len(raw), records=records,
        boundary='First wait is the end of this selected prefix, not an end-of-stream claim.',
        handler08_selected=False, bank_headers_selected=False)


def inspect(data, digest):
    # Existing whole SHA/schema/language/File Bytes/data5 controls come first.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    # Mapping validation only: do not call command.inspect/read_range.
    command.mappings(blocks, subs, image)
    maps = [normal.mapping_evidence(blocks, subs, image, m) for m in (TEXT_MAPPING, DATA3_MAPPING)]
    text, data3 = [item[0] for item in maps]
    ranges = [range_evidence(db, text, pc, width) for pc, width, _ in RANGES]
    selections = [(pc, *data_window(db, data3, pc, width)) for _, pc, width, _ in DATA_WINDOWS]
    payloads = {pc: raw for pc, raw, _ in selections}
    prefixes = [prefix_fields(0x802be5ee, payloads[0x802be5ee], payloads[0x802be602]),
                prefix_fields(0x802be656, payloads[0x802be656], payloads[0x802be66a])]
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type', 'executable_metadata_caveat',
            'file_bytes_table', 'block_size', 'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[item[1] for item in maps], ranges=ranges,
        windows=[report for _, _, report in selections], prefixes=prefixes,
        function_coverage=[dict(entry=f'{pc:08x}', end_exclusive=f'{pc + width:08x}', selected_width=width,
            represented_instructions=width // 4, unrepresented_instructions=0, unrepresented_ranges=[],
            extent_basis='independently documented adjacent command handlers; authenticated return sites',
            map_size=None) for pc, width, _ in RANGES],
        reused_table_witness=dict(address='802d0da0', width=72,
            sha256='fdf7c34d3ce203b91e168f8ea7ce7873e7140b5dbf1a6d5cb1710cbe868d260e',
            slots={'02': '8004c424', '03': '8004c488'}, read_here=False),
        caveat='Archived ProgramDB static evidence only, not unchanged original-DOL identity or execution. '
            'Both state commands occupy8 bytes. Opcode03 has two ordered controlWord stores with fresh '
            'operand/owner loads between them. No bank headers, phase1 selections or opcode08 body read. '
            'Air cannot skip08. Ground sets control bit40; in the current cue44 composition, when699d8 and69814 '
            'return0, next full-frame progress stops at59d18->69210 before phase1. '
            'No runtime integration, collision, clone, numerical parity, audio or playability claim.')


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
