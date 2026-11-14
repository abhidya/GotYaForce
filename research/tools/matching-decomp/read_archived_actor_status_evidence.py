#!/usr/bin/env python3
"""Fixed actor-status and ammo evidence from authenticated local GBF snapshots.

Read-only stdlib. Complete 8005568c/8006dcc0 spans and four named constants;
derived operand fields only. No arbitrary-address CLI, raw executable output,
vendor-code execution, or changes to the shared archive reader's allowlist.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_actor_traversal_evidence as traversal
import read_archived_command_evidence as command
import read_archived_constants as c
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH


RANGES = (
    (0x8005568c, 1856, '0f964164be0f7581e45a26f8acd1113b414d13ecdbefeb94be72acde53c156ac'),
    (0x8006dcc0, 336, '2d58ff4852a700a526d906055a7d70dcee182783f6f0a3b0d83d3be2fd20de8f'),
)
TARGETS = (
    (0x80437250, 4, '00000000'),
    (0x80437658, 4, '00000000'),
    (0x804376c8, 4, '41200000'),
    (0x804376a0, 8, '4330000080000000'),
)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)


def decode_selected(word, pc):
    """Only the scalar forms observed in these two fixed functions.

    Keep operand direction, signedness, CR conditions and record bits explicit.
    Reject reserved encodings and unselected forms; never omit an instruction.
    This decodes fields, and does not execute the archived instructions.
    """
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if op == 31 and xo in (339, 467):
        spr = (b << 5) | a
        c.require(rc == 0 and ((spr == 8 and d == 0) or (spr == 9 and xo == 467)),
                  'unsupported SPR form')
        if spr == 9:
            return dict(mnemonic='mtctr', rS=d)
        return dict(mnemonic='mflr', rD=0) if xo == 339 else dict(mnemonic='mtlr', rS=0)
    if op == 19 and xo == 449:
        c.require(rc == 0, 'reserved cror bit')
        return dict(mnemonic='cror', crD=d, crA=a, crB=b)
    if op == 63 and xo == 32:
        c.require(rc == 0 and d & 3 == 0, 'reserved fcmpo fields')
        return dict(mnemonic='fcmpo', crD=d >> 2, fA=a, fB=b)
    if op == 59 and (xo & 31) in (18, 20, 21, 25):
        form = xo & 31
        c.require(rc == 0 and (b == 0 if form == 25 else fc == 0),
                  'reserved single arithmetic fields')
        if form == 25:
            return dict(mnemonic='fmuls', fD=d, fA=a, fC=fc)
        return dict(mnemonic={18: 'fdivs', 20: 'fsubs', 21: 'fadds'}[form], fD=d, fA=a, fB=b)
    if op in (8, 27, 38):
        if op == 27:
            return dict(mnemonic='xoris', rS=d, rA=a, immediate=word & 65535)
        if op == 38:
            return dict(mnemonic='stb', rS=d, rA=a, displacement=traversal.signed(word & 65535, 16))
        return dict(mnemonic='subfic', rD=d, rA=a, immediate=traversal.signed(word & 65535, 16))
    if op == 31:
        if xo in (40, 75):
            return dict(mnemonic='subf' if xo == 40 else 'mulhw', rD=d, rA=a, rB=b, Rc=rc)
        if xo == 60:
            return dict(mnemonic='andc', rS=d, rA=a, rB=b, Rc=rc)
        if xo == 824:
            return dict(mnemonic='srawi', rS=d, rA=a, SH=b, Rc=rc)
        if xo in (87, 151, 215):
            c.require(rc == 0, 'reserved indexed memory bit')
            return dict(mnemonic={87: 'lbzx', 151: 'stwx', 215: 'stbx'}[xo],
                        **({'rD': d} if xo == 87 else {'rS': d}), rA=a, rB=b)
        if xo in (0, 32):
            c.require(rc == 0 and d & 3 == 0, 'reserved/non-32-bit comparison fields')
        if xo in (954, 922):
            c.require(b == 0, 'reserved sign-extension fields')
    if op in (10, 11):
        c.require(d & 3 == 0, 'reserved/non-32-bit comparison fields')
    if not (word == 0x4e800020 or op in (7, 10, 11, 14, 15, 16, 18, 21, 28,
                                       32, 34, 36, 37, 42, 44, 48, 50, 52, 54) or
            (op == 31 and xo in (0, 24, 28, 266, 444, 922, 954)) or
            (op == 63 and xo == 15)):
        return None
    decoded = traversal.decode_selected(word, pc)
    if decoded is not None and decoded['mnemonic'] in ('stw', 'stwu', 'sth'):
        decoded['rS'] = decoded.pop('rD')
    if decoded is not None and decoded['mnemonic'] in ('stfs', 'stfd'):
        decoded['fS'] = decoded.pop('fD')
    return decoded


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
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, spans=spans, instructions=instructions)


def constant_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'constant integer fields')
    selected = [item for item in TARGETS if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'constant not allowlisted')
    c.require(mapping == DATA5_MAPPING, 'data5 mapping mismatch')
    start, end, _, _, _, length, root = mapping
    c.require(width in (4, 8) and address % width == 0 and start <= address < address + width <= end,
              'constant alignment/width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == selected[0][2], 'constant bits mismatch')
    return dict(address=f'{address:08x}', width=width, type='f32' if width == 4 else 'f64',
                bits=raw.hex(), value=struct.unpack('>f' if width == 4 else '>d', raw)[0],
                sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def inspect(data, digest):
    # Whole-snapshot authentication, exact schemas, executable metadata, empty
    # File Bytes, address maps, full data5 hash and controls precede new reads.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    mapping = c.data5_mapping(blocks, subs, image)
    c.require(mapping == DATA5_MAPPING, 'data5 mapping mismatch')
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    return dict({key: auth[key] for key in keys},
                block_name='MAIN_.text1', block_key=1, subblock_key=1,
                block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                subblock_type=2, starting_offset=0, source_offset=0, chain_root=21,
                ranges=[range_evidence(db, 21, address, width) for address, width, _ in RANGES],
                constants=[constant_evidence(db, mapping, address, width) for address, width, _ in TARGETS],
                caveat='Archived ProgramDB evidence only, not unchanged original-DOL or live parity. '
                       'All 464 status and 84 ammo instructions are represented. '
                       'Constants authenticate two positive zeros, 10f and a signed conversion bias. '
                       'Live FPSCR state, retail actor values and runtime ownership are not established.')


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
