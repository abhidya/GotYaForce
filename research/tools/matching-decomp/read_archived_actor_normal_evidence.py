#!/usr/bin/env python3
"""Fixed normal-actor dispatch and bounded lifecycle evidence from archived GBF.

Read-only stdlib. Authenticate the complete existing snapshot before exactly
four fixed pointer cells and seven independent code spans. No table dumps,
pointer following, arbitrary-address CLI, raw output or instruction execution.
The constructor span proves a producer, not full constructor implementation or
which live actor owns it. Every selected instruction must decode explicitly.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_command_evidence as command
import read_archived_constants as c


TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 1000128, 199)
# label, address, expected target, SHA-256. Targets never select code reads.
CELLS = (
    ('signed-cue9', 0x802d3324, 0x80059138,
     '2546ad0258f9f41c33b44ebd186e8486d9f61b7315e8494aa23a48df4777fb43'),
    ('signed-cue0', 0x802d3300, 0x8005913c,
     '9580f1cc45ceb6223ad8f8413118771eee94978d6f6c1c752bab7d772c40c400'),
    ('constructor-4c8-source', 0x8036554c, 0x8018cfe4,
     '35f8fb00f9e6b005eabae38a3b327c8a5cfa27ce70355b05cc4041e757fbcc2e'),
    ('double-constructor-4c8-source', 0x802d3b28, 0x8006f950,
     'c8e68f4fca4b823b7a7ffbe6210ccdc0041a26eed3c415fc65b553558a889157'),
)
# Independent address, width and digest allowlist, never derived from CELLS.
RANGES = (
    (0x80059138, 4, 'f332ea5b5437103cbb6f1508679da89eec9288ad775c96c439a17fccabe3de8e'),
    (0x8018ccfc, 288, 'dda3561372b459527f131057a11caf6f4645b8bb0c80ac17372cb2e42ff6a58f'),
    (0x8018cfe4, 4, 'f332ea5b5437103cbb6f1508679da89eec9288ad775c96c439a17fccabe3de8e'),
    (0x80059f5c, 488, '68a4b07dfea21671d8a803518f84c3a9935569931681b6116d827d7078ec3f59'),
    (0x8005a144, 76, 'fd9836eda5033e276bba22bf9d42f357c4ba31c68a3ed461a9d0def0a0975a53'),
    (0x8006f60c, 252, '201ead69a9e7e0cb04851db5f7498352ebdf5cbecc88be4486e68e2122e3e962'),
    # Three adjacent returns, NOT a claimed 12-byte function extent.
    (0x8006f950, 12, '26344477d6cb9e47db67286493a89c8016eaa46f7fcd67da87ddca2ec859f47a'),
)


def signed(value, bits):
    return value - (1 << bits) if value & (1 << (bits - 1)) else value


def decode_selected(word, pc):
    """Decode only observed forms, preserving source/destination and CR fields."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 19 and xo in (16, 528):
        c.require(word in (0x4e800020, 0x4c820020, 0x4e800421), 'unselected branch-register form')
        return dict(mnemonic={0x4e800020: 'blr', 0x4c820020: 'bclr',
                              0x4e800421: 'bctrl'}[word], BO=d, BI=a, BH=0, LK=rc)
    if op == 18:
        c.require(word & 2 == 0, 'unselected absolute branch')
        return dict(mnemonic='bl' if rc else 'b',
                    target=f'{(pc + signed(word & 0x3fffffc, 26)) & 0xffffffff:08x}', AA=0)
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 0), (4, 1), (4, 2),
                                              (12, 1), (12, 2), (16, 0)),
                  'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, LK=0,
                    target=f'{(pc + signed(word & 0xfffc, 16)) & 0xffffffff:08x}', AA=0)
    if op in (10, 11):
        c.require(d == 0, 'unselected comparison fields')
        return dict(mnemonic='cmpli' if op == 10 else 'cmpi', BF=0, L=0, rA=a,
                    immediate=word & 65535 if op == 10 else signed(word & 65535, 16))
    if op in (7, 14, 15):
        return dict(mnemonic={7: 'mulli', 14: 'addi', 15: 'addis'}[op],
                    rD=d, rA=a, immediate=signed(word & 65535, 16))
    if op == 27:
        return dict(mnemonic='xoris', rS=d, rA=a, immediate=word & 65535)
    if op == 21:
        return dict(mnemonic='rlwinm', rS=d, rA=a, SH=b, MB=fc, ME=(word >> 1) & 31, Rc=rc)
    if op in (32, 34, 36, 37, 38, 42, 44, 48, 50, 54):
        name, reg = {32: ('lwz', 'rD'), 34: ('lbz', 'rD'), 36: ('stw', 'rS'),
                     37: ('stwu', 'rS'), 38: ('stb', 'rS'), 42: ('lha', 'rD'),
                     44: ('sth', 'rS'), 48: ('lfs', 'fD'), 50: ('lfd', 'fD'),
                     54: ('stfd', 'fS')}[op]
        if op == 37:
            c.require(a != 0, 'reserved store-update base')
        return dict(mnemonic=name, **{reg: d}, rA=a, displacement=signed(word & 65535, 16))
    if op == 31:
        if xo in (339, 467):
            spr = (b << 5) | a
            c.require(rc == 0 and ((spr == 8 and d == 0) or (spr == 9 and xo == 467)),
                      'unselected SPR form')
            if spr == 9:
                return dict(mnemonic='mtctr', rS=d)
            return dict(mnemonic='mflr', rD=0) if xo == 339 else dict(mnemonic='mtlr', rS=0)
        if xo == 0:
            c.require(d == rc == 0, 'unselected register comparison fields')
            return dict(mnemonic='cmp', BF=0, L=0, rA=a, rB=b)
        if xo in (23, 87):
            c.require(rc == 0, 'reserved indexed-load bit')
            return dict(mnemonic='lwzx' if xo == 23 else 'lbzx', rD=d, rA=a, rB=b)
        if xo in (922, 954):
            c.require(b == 0, 'reserved sign-extension fields')
            return dict(mnemonic='extsh' if xo == 922 else 'extsb', rS=d, rA=a, Rc=rc)
        if xo in (28, 444):
            return dict(mnemonic='and' if xo == 28 else 'or', rS=d, rA=a, rB=b, Rc=rc)
        if xo == 266:
            return dict(mnemonic='add', rD=d, rA=a, rB=b, Rc=rc)
    if op == 59 and (xo & 31) in (20, 25, 29):
        form = xo & 31
        c.require(rc == 0 and (fc == 0 if form == 20 else b == 0 if form == 25 else True),
                  'unselected single-arithmetic fields')
        if form == 20:
            return dict(mnemonic='fsubs', fD=d, fA=a, fB=b)
        if form == 25:
            return dict(mnemonic='fmuls', fD=d, fA=a, fC=fc)
        return dict(mnemonic='fmadds', fD=d, fA=a, fC=fc, fB=b)
    if op == 63 and xo == 15:
        c.require(a == rc == 0, 'reserved conversion fields')
        return dict(mnemonic='fctiwz', fD=d, fB=b)
    return None


def require_mapping(mapping, expected):
    c.require(type(mapping) is tuple and mapping == expected and
              tuple(map(type, mapping)) == tuple(map(type, expected)), 'exact mapping mismatch')


def mapping_evidence(blocks, subs, image, expected):
    key = expected[2]
    row, sub = blocks[key], subs[key]
    start = c.address_start(row[4], image)
    actual = (start, start + row[5], key, row[0], key, sub[2], sub[4])
    require_mapping(actual, expected)
    return actual, dict(block_name=row[0], block_key=key, subblock_key=key,
                        block_start=f'{start:08x}', end_exclusive=f'{start + row[5]:08x}',
                        block_length=row[5], chain_root=sub[4], subblock_type=sub[1],
                        starting_offset=sub[3], source_offset=sub[5])


def cell_evidence(db, mapping, address):
    c.require(type(address) is int, 'cell integer fields')
    selected = [item for item in CELLS if item[1] == address]
    c.require(len(selected) == 1, 'cell not allowlisted')
    require_mapping(mapping, DATA3_MAPPING)
    label, _, target, expected = selected[0]
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == 0 and start <= address < address + 4 <= end, 'cell alignment/bounds')
    raw, spans = db.chain(root, address - start, 4, length)
    c.require(len(raw) == 4, 'cell byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected, 'cell digest mismatch')
    actual = c.integer(raw, 0, 'I')
    c.require(actual == target, 'cell target mismatch')
    return dict(label=label, address=f'{address:08x}', width=4, target=f'{actual:08x}',
                sha256=digest, spans=spans)


def range_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    require_mapping(mapping, TEXT_MAPPING)
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
        c.require(decoded is not None, 'unselected instruction in fixed span')
        instructions.append(dict(address=f'{pc:08x}', **decoded))
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, spans=spans, instructions=instructions)


def inspect(data, digest):
    # Exact full SHA, schemas, language/metadata, File Bytes, address maps,
    # full data5 hash and established controls precede all selected payloads.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, text_fact = mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data3, data3_fact = mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys}, mappings=[text_fact, data3_fact],
                cells=[cell_evidence(db, data3, address) for _, address, _, _ in CELLS],
                ranges=[range_evidence(db, text, address, width) for address, width, _ in RANGES],
                caveat='Archived ProgramDB static evidence only, not original-DOL identity, '
                       'live dispatch or behavioral parity. Constructor source identity is '
                       'not full constructor implementation or live actor ownership. Cue0 '
                       'body, 8006a6fc, rotation constants/list payloads and 4dc targets are '
                       'unselected. The 8006f60c source cell 802d3b28 holds 8006f950, '
                       'an immediate return; adjacent returns 8006f954/8006f958 have '
                       'no established owner. No pointer determines a read; all 281 '
                       'instructions decode.')


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
