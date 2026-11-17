#!/usr/bin/env python3
"""Read fixed stream bootstrap/reset evidence from authenticated GBF snapshots.

Stdlib only and read-only. Emits lineage, hashes and selected instruction facts,
not raw ranges. No arbitrary-address interface or vendor-code execution.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_constants as c
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH, text_mapping

RANGES = (
    (0x8004beb8, 360, 'af8c9bb8f3fa6387ee864411f266f0757d936550f2ac0cfa50bfc3b2e35390a2'),
    (0x8004c020, 48, '06c4624d1c2173dc6d487e2f4bec33c32b892011cddc144b09542c4a7e470629'),
)
WORDS = {
    0x8004bee4: 0x88030579, 0x8004bee8: 0x7c000774, 0x8004beec: 0x7c9b0038,
    0x8004bf40: 0x57800e3c, 0x8004bf44: 0x7c0302ae, 0x8004bf48: 0x7c630214,
    0x8004bf90: 0x881a0582, 0x8004bf94: 0x7c000774, 0x8004bf98: 0x7f9c0214,
    0x8004bf9c: 0x5780083c, 0x8004bfa0: 0x7c0302ae, 0x8004bfa4: 0x7c630214,
    0x8004bfa8: 0x57a0083c, 0x8004bfb0: 0x7c0302ae, 0x8004bfbc: 0x7ec30214,
    0x8004bfcc: 0x9b980018, 0x8004bfd4: 0x9bb80019,
    0x8004c020: 0xc00286d4, 0x8004c024: 0x38000000,
    0x8004c028: 0xd003000c, 0x8004c02c: 0xd0030010, 0x8004c030: 0xd0030008,
    0x8004c034: 0x9803001d, 0x8004c038: 0x9803001e, 0x8004c03c: 0x90030004,
    0x8004c040: 0x90030000, 0x8004c044: 0xd0030014, 0x8004c048: 0x9803001a,
}


def decode_word(word):
    """Decode only the integer/memory forms needed by these word facts."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    immediate = word & 0xffff
    if immediate & 0x8000:
        immediate -= 0x10000
    if op in (34, 36, 38, 48, 52):
        mnemonic, field = {34:('lbz','rD'),36:('stw','rS'),38:('stb','rS'),
                           48:('lfs','fD'),52:('stfs','fS')}[op]
        return dict(mnemonic=mnemonic, **{field:d}, rA=a, displacement=immediate)
    if op == 14 and a == 0:
        return dict(mnemonic='li', rD=d, immediate=immediate)
    if op == 21 and word & 1 == 0:
        return dict(mnemonic='rlwinm', rA=a, rS=d, shift=b,
                    mask_begin=(word >> 6) & 31, mask_end=(word >> 1) & 31)
    if op == 31 and word & 1 == 0:
        xo = (word >> 1) & 0x3ff
        if xo == 954 and b == 0:
            return dict(mnemonic='extsb', rA=a, rS=d)
        if xo == 28:
            return dict(mnemonic='and', rA=a, rS=d, rB=b)
        if xo in (343, 266):
            return dict(mnemonic={343:'lhax',266:'add'}[xo], rD=d, rA=a, rB=b)
    raise c.FormatError('unsupported instruction form')


def range_evidence(db, root, address, width):
    matches = [r for r in RANGES if r[:2] == (address, width)]
    c.require(len(matches) == 1, 'range not allowlisted')
    c.require(address % 4 == width % 4 == 0 and
              TEXT_START <= address < address+width <= TEXT_START+TEXT_LENGTH,
              'range alignment/bounds')
    raw, spans = db.chain(root, address-TEXT_START, width, TEXT_LENGTH)
    c.require(len(raw) == width, 'range byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == matches[0][2], 'range digest mismatch')
    facts = []
    for pc, expected in WORDS.items():
        if address <= pc < address+width:
            word = c.integer(raw, pc-address, 'I')
            c.require(word == expected, 'instruction word mismatch')
            facts.append(dict(address=f'{pc:08x}', word=f'{word:08x}', **decode_word(word)))
    return dict(address=f'{address:08x}', width=width, sha256=digest,
                spans=spans, instructions=facts)


def inspect(data, digest):
    # Retain existing snapshot authentication, exact schemas, metadata, address
    # mapping, full data5 digest and controls. Do not add new constant targets.
    constants = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    root = text_mapping(db.rows(tables['Memory Blocks']),
                        db.rows(tables['Sub Memory Blocks']), int(constants['image_offset'],16))
    ranges = [range_evidence(db,root,address,width) for address,width,_ in RANGES]
    keys = ('snapshot','snapshot_sha256','program_name','created_with_ghidra_version',
            'executable_sha256_metadata','executable_sha256_property_type',
            'executable_metadata_caveat','file_bytes_table','block_size',
            'master_root','table_roots','image_offset')
    return dict({k:constants[k] for k in keys}, block_name='MAIN_.text1', block_key=1,
                subblock_key=1, block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                chain_root=root, ranges=ranges,
                reset_zero=next(r for r in constants['results'] if r['address']=='804370f4'),
                provenance_caveat='Matching archived ProgramDB bytes are not fresh original DOL or live-runtime parity proof.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('snapshot', type=Path)
    args = parser.parse_args()
    try:
        c.require(args.snapshot.is_file(), 'snapshot is not a regular file')
        with args.snapshot.open('rb') as stream:
            c.require(32 <= args.snapshot.stat().st_size <= c.MAX_FILE, 'file size bounds')
            data = stream.read(c.MAX_FILE+1)
        c.require(len(data) <= c.MAX_FILE, 'file exceeds bound')
        print(json.dumps(inspect(data,hashlib.sha256(data).hexdigest()),indent=2,allow_nan=False))
    except (OSError,c.FormatError) as exc:
        print(json.dumps({'error':str(exc)}),file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
