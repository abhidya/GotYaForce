#!/usr/bin/env python3
"""Fixed ordinary-X command admission evidence from archived ProgramDB.

Read-only stdlib. Four primary spans, bounded trig/voice support, six literal
constants, one fixed mask window and unchanged zero-kernel evidence reuse.
No arbitrary addresses, pointer following, raw executable output, archive
execution or changes to shared allowlists.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import read_archived_actor_normal_evidence as normal
import read_archived_actor_status_evidence as status
import read_archived_actor_traversal_evidence as traversal

c, command = status.c, status.command
TEXT_MAPPING, DATA3_MAPPING = normal.TEXT_MAPPING, normal.DATA3_MAPPING
DATA5_MAPPING = status.DATA5_MAPPING
RANGES = (
    (0x80069ea4, 316, '8b0efdb5a565ee7ef2266109d0ee51d37118bcebb03821f06b9418cadaeac9d7'),
    (0x8006c674, 180, '4381614f1242f91931948f08fe8952e48ab1ac34b5e9561a2e20f4150fd08110'),
    (0x8006a104, 716, '476ca1cbad57dc6ad22dbe4c919646740f7d517f813bcc9f7da70ccb7474253f'),
    (0x8006bda8, 472, '175c8cf36b7dc4bb7bc5c76ce86651b067ff08ff5cfdc0eb0c394411acb28dc9'),
)
SUPPORT_RANGES = (
    (0x80045204, 52, 'cd6a74d4ec3ade0be57d6c57a0a2e558dee77ab24ebd545f89543a74d162a1a5'),
    (0x80045238, 52, 'c882d317771586afa562e3243e557411e54441b86fdcd9966e2b39af9b7d120f'),
    (0x800ea2c8, 36, 'd32cb5a6a7828518b31b184cab5db4840a2a8c7e55c86a953d1317941bdf9966'),
    # Reached entry/gate and return only; NOT the complete 340-byte function.
    (0x800ea2ec, 56, 'aee7a9b97ff23e93962d200216fefd082fd8d3f6b20404535842c312fcb38662'),
    (0x800ea42c, 20, '972973be8074e92b0f10fc5fbbaaef6c28e2905f99007654cd735a5fd69933fc'),
)
# Reuse existing fixed selections unchanged. This reader does not duplicate or
# expand libm selection/decoding. Their omitted instructions remain explicit.
REUSED_ZERO_RANGES = ((0x8023c9e8, 216), (0x8023c480, 212),
                      (0x8023bf8c, 160), (0x8023b044, 244))
REUSED_ZERO_CONSTANTS = (0x80437078, 0x8043d198, 0x8043d150, 0x8043d030)
CONSTANTS = (
    (0x8043762c, 4, '00000000'),
    (0x8043764c, 4, 'bf800000'),
    (0x80437658, 4, '00000000'),
    (0x80437660, 8, '3fe0000000000000'),
    (0x80437668, 8, '4008000000000000'),
    (0x80437678, 4, '469c4000'),
)
# Six admitted input slots, selected independently of any runtime index.
# Neither a full-table extent nor authorization to read negative/larger indices.
MASK_WINDOW = (0x802d3994, 12)
MASK_PAIRS = ((58, 4), (56, 4), (56, 0), (56, 0), (56, 0), (56, 0))
MASK_SHA = '94929509e3228a6f14382e3c05d7cd38c28d1af7ee09e0ec5f36c23ca79460fc'
RECORDED_R2 = 0x8043ea20


def decode_selected(word, pc):
    """Explicit observed PPC forms, all operand/condition fields, no execution."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo, fc, rc = (word >> 1) & 1023, (word >> 6) & 31, word & 1
    if word == 0x4e800020:
        return dict(mnemonic='blr')
    if op == 18:
        c.require(word & 2 == 0, 'unselected absolute branch')
        return dict(mnemonic='bl' if rc else 'b', AA=0,
                    target=f'{(pc + normal.signed(word & 0x3fffffc, 26)) & 0xffffffff:08x}')
    if op == 16:
        c.require(word & 3 == 0 and (d, a) in ((4, 1), (4, 2), (12, 0), (12, 2)),
                  'unselected conditional branch')
        return dict(mnemonic='bc', BO=d, BI=a, AA=0, LK=0,
                    target=f'{(pc + normal.signed(word & 0xfffc, 16)) & 0xffffffff:08x}')
    if op in (10, 11):
        c.require(d == 0, 'unselected comparison fields')
        return dict(mnemonic='cmpli' if op == 10 else 'cmpi', BF=0, L=0, rA=a,
                    immediate=word & 65535 if op == 10 else normal.signed(word & 65535, 16))
    if op in (7, 14, 15):
        return dict(mnemonic={7: 'mulli', 14: 'addi', 15: 'addis'}[op],
                    rD=d, rA=a, immediate=normal.signed(word & 65535, 16))
    if op == 21:
        return dict(mnemonic='rlwinm', rS=d, rA=a, SH=b, MB=fc, ME=(word >> 1) & 31, Rc=rc)
    if op in (32, 34, 36, 37, 38, 42, 44, 46, 47, 48, 50, 52):
        name, reg = {32: ('lwz', 'rD'), 34: ('lbz', 'rD'), 36: ('stw', 'rS'),
                     37: ('stwu', 'rS'), 38: ('stb', 'rS'), 42: ('lha', 'rD'),
                     44: ('sth', 'rS'), 46: ('lmw', 'rD'), 47: ('stmw', 'rS'),
                     48: ('lfs', 'fD'), 50: ('lfd', 'fD'), 52: ('stfs', 'fS')}[op]
        c.require(op != 37 or a != 0, 'reserved store-update base')
        return dict(mnemonic=name, **{reg: d}, rA=a, displacement=normal.signed(word & 65535, 16))
    if op == 56:
        w, i = (word >> 15) & 1, (word >> 12) & 7
        c.require(w == 1 and i == 5 and d == a == 1 and word & 4095 == 8,
                  'unselected quantized short fields')
        return dict(mnemonic='psq_l', fD=d, rA=a, displacement=8, W=w, I=i)
    if op == 31:
        if xo in (339, 467):
            c.require(d == rc == 0 and ((b << 5) | a) == 8, 'unselected link-register form')
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
        if xo in (60, 444):
            return dict(mnemonic='andc' if xo == 60 else 'or', rS=d, rA=a, rB=b, Rc=rc)
        if xo == 266:
            return dict(mnemonic='add', rD=d, rA=a, rB=b, Rc=rc)
    if op == 59 and (xo & 31) in (20, 21, 25):
        form = xo & 31
        c.require(rc == 0 and (b == 0 if form == 25 else fc == 0),
                  'reserved single arithmetic fields')
        if form == 25:
            return dict(mnemonic='fmuls', fD=d, fA=a, fC=fc)
        return dict(mnemonic='fsubs' if form == 20 else 'fadds', fD=d, fA=a, fB=b)
    if op == 63:
        if xo == 32:
            c.require(rc == d == 0, 'unselected fcmpo fields')
            return dict(mnemonic='fcmpo', crD=0, fA=a, fB=b)
        if xo in (12, 26):
            c.require(a == rc == 0, 'reserved floating unary fields')
            return dict(mnemonic='frsp' if xo == 12 else 'frsqrte', fD=d, fB=b)
        if (xo & 31) in (25, 30):
            form = xo & 31
            c.require(rc == 0 and (b == 0 if form == 25 else True),
                      'reserved double arithmetic fields')
            if form == 25:
                return dict(mnemonic='fmul', fD=d, fA=a, fC=fc)
            return dict(mnemonic='fnmsub', fD=d, fA=a, fC=fc, fB=b)
    return None


def range_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'range integer fields')
    selected = [item for item in RANGES + SUPPORT_RANGES if item[:2] == (address, width)]
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
        decoded = decode_selected(c.integer(raw, offset, 'I'), address + offset)
        c.require(decoded is not None, 'unselected instruction in fixed span')
        instructions.append(dict(address=f'{address + offset:08x}', **decoded))
    return dict(address=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                width=width, sha256=digest, spans=spans, instructions=instructions)


def constant_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'constant integer fields')
    selected = [item for item in CONSTANTS if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'constant not allowlisted')
    normal.require_mapping(mapping, DATA5_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(width in (4, 8) and address % width == 0 and start <= address < address + width <= end,
              'constant alignment/width/bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'constant byte width')
    c.require(raw.hex() == selected[0][2], 'constant bits mismatch')
    return dict(address=f'{address:08x}', width=width, type='f32' if width == 4 else 'f64',
                bits=raw.hex(), value=struct.unpack('>f' if width == 4 else '>d', raw)[0],
                sha256=hashlib.sha256(raw).hexdigest(), spans=spans)


def mask_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'mask integer fields')
    c.require((address, width) == MASK_WINDOW, 'mask window not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(start <= address < address + width <= end, 'mask bounds')
    raw, spans = db.chain(root, address - start, width, length)
    c.require(len(raw) == width, 'mask byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == MASK_SHA, 'mask digest mismatch')
    pairs = tuple(tuple(raw[i:i + 2]) for i in range(0, width, 2))
    c.require(pairs == MASK_PAIRS, 'mask values mismatch')
    return dict(address=f'{address:08x}', width=width, sha256=digest, spans=spans,
                slots=[dict(index=i, mask57a=first, mask57b=second)
                       for i, (first, second) in enumerate(pairs)], extent_proven=False,
                caveat='Independent fixed 12-byte window for slots 0..5 only. Source uses signed '
                       '584 and reloads it between cells. No runtime index, full-table extent '
                       'or adjacent byte is authenticated.')


def inspect(data, digest):
    # Whole-file SHA, schemas, metadata, empty File Bytes, address maps, data5
    # digest and existing controls all precede the independently fixed reads.
    auth = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks, subs = db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'], 16)
    command.mappings(blocks, subs, image)
    text, text_fact = normal.mapping_evidence(blocks, subs, image, TEXT_MAPPING)
    data3, data3_fact = normal.mapping_evidence(blocks, subs, image, DATA3_MAPPING)
    data5, data5_fact = normal.mapping_evidence(blocks, subs, image, DATA5_MAPPING)
    keys = ('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
            'executable_sha256_metadata', 'executable_sha256_property_type',
            'executable_metadata_caveat', 'file_bytes_table', 'block_size',
            'master_root', 'table_roots', 'image_offset', 'data5_sha256')
    reused = []
    for address, width in REUSED_ZERO_RANGES:
        result = traversal.range_evidence(db, text[-1], address, width)
        # The older reader labels store registers like loads. Normalize only
        # this returned evidence; do not change that shared reader or its scope.
        for item in result['instructions']:
            if item['mnemonic'] in ('stw', 'stwu'): item['rS'] = item.pop('rD')
            if item['mnemonic'] == 'stfd': item['fS'] = item.pop('fD')
        represented = {int(item['address'], 16) for item in result['instructions']}
        result['unrepresented_addresses'] = [f'{pc:08x}' for pc in range(address, address + width, 4)
                                             if pc not in represented]
        result['represented_instructions'] = len(represented)
        result['unrepresented_instructions'] = width // 4 - len(represented)
        reused.append(result)
    return dict({key: auth[key] for key in keys}, mappings=[text_fact, data3_fact, data5_fact],
                ranges=[range_evidence(db, text, address, width) for address, width, _ in RANGES],
                support_ranges=[range_evidence(db, text, address, width)
                                for address, width, _ in SUPPORT_RANGES],
                constants=[constant_evidence(db, data5, address, width)
                           for address, width, _ in CONSTANTS],
                mask_window=mask_evidence(db, data3, *MASK_WINDOW),
                reused_zero_trig=dict(source_reader='read_archived_actor_traversal_evidence.py',
                                      ranges=reused,
                                      constants=[traversal.constant_evidence(db, address)
                                                 for address in REUSED_ZERO_CONSTANTS],
                                      caveat='Existing fixed selections and selected-field decoder '
                                             'reused unchanged, not fully represented libm functions. '
                                             'Every omitted instruction address is reported. Only '
                                             'the established positive-zero arithmetic path is used; '
                                             'nonzero paths and general libm parity are not claimed.'),
                r2_basis=dict(recorded_value=f'{RECORDED_R2:08x}',
                              displacements={f'{address:08x}': address - RECORDED_R2
                                             for address, _, _ in CONSTANTS},
                              source='docs/static-recompilation-spike.md:178',
                              caveat='Previously recorded SDA2 basis, not a newly authenticated '
                                     'startup span or live r2 capture.'),
                r13_basis=dict(recorded_value='8043b5a0', displacement=-31852,
                               derived_cell_address='80433934',
                               source='docs/static-recompilation-spike.md:179-180',
                               caveat='Recorded SDA basis, not live r13 or global pointer contents. '
                                      'No global cell or pointee is read by this tool.'),
                function_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                                        selected_width=width, represented_instructions=width // 4,
                                        unrepresented_instructions=0, unrepresented_ranges=[],
                                        extent_basis='symbol map, C markers and authenticated return',
                                        map_size=width)
                                   for address, width, _ in RANGES],
                support_coverage=[dict(entry=f'{address:08x}', end_exclusive=f'{address + width:08x}',
                                       selected_width=width, represented_instructions=width // 4,
                                       unrepresented_instructions=0, unrepresented_ranges=[],
                                       extent_basis='symbol map, C markers and authenticated return', map_size=width)
                                  for address, width, _ in SUPPORT_RANGES[:3]] + [
                    dict(entry='800ea2ec', end_exclusive='800ea440', map_size=340,
                         selected_width=76, represented_instructions=19, unrepresented_instructions=66,
                         unrepresented_ranges=[dict(address='800ea324', end_exclusive='800ea42c', width=264)],
                         extent_basis='full map/C extent; only fixed entry gate and epilogue selected')],
                caveat='Archived ProgramDB static evidence only, not unchanged original-DOL '
                       'identity, live input, runtime ownership or behavioral parity. All 421 '
                       'primary instructions and all 54 additional selected support instructions '
                       'are represented. ea2ec normal-match body remains unselected. Runtime '
                       'descriptors, actor globals, nonzero trig, angle/vector helpers, cue reset, launch, ammo and sound remain '
                       'callee or ownership boundaries. frsqrte and fused fnmsub must not be '
                       'replaced with host sqrt or split arithmetic under an exactness claim. '
                       'Zero-yaw proof assumes GQR5 signed16/load-scale0 and FPSCR RN=00/NI=0; '
                       'these are execution-domain conditions, not observed live state. '
                       'No runtime pointer determines any reader address.')


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
