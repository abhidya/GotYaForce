#!/usr/bin/env python3
"""Read two fixed wait-instruction ranges from SHA-allowlisted GBF snapshots.

Stdlib only, read-only, no disassembler or vendor-code execution. Only the eight
listed instruction forms are decoded; this is not a general PPC disassembler.
Output contains hashes, lineage and selected instruction facts, never raw ranges.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_constants as c

TEXT_START = 0x800055e0
TEXT_LENGTH = 2796416
RANGES = (
    (0x8004cd24, 0x2d0, '0d8fdecb40f550e2003f0a28a40d4399178851ca4f1901ba73d9039701267c80'),
    (0x8002a414, 12, '47700afbd889ec8e727fc3506213596b94b94cebedaeeb6413728aca6557ee1b'),
)
WORDS = {
    0x8004ce34: 0xe03bd024, 0x8004ce38: 0xec21102a,
    0x8004ce68: 0xe05bd024, 0x8004ce74: 0xec001024,
    0x8004ce7c: 0xec010032, 0x8002a414: 0x38600007,
    0x8002a418: 0x64630007, 0x8002a41c: 0x7c75e3a6,
}


def text_mapping(blocks, subs, image):
    """Validate every block for overlap, then require the exact text source."""
    ranges = []
    for key, row in blocks.items():
        name, _, _, _, encoded, length, segment = row
        start = c.address_start(encoded, image)
        c.require(segment == 0 and 0 < length <= 0x100000000-start,
                  'block bounds/segment')
        ranges.append((start, start+length, key, name, encoded))
    ranges.sort()
    c.require(all(a[1] <= b[0] for a, b in zip(ranges, ranges[1:])),
              'overlapping memory blocks')
    selected = [r for r in ranges if r[3] == 'MAIN_.text1']
    c.require(selected == [(TEXT_START, TEXT_START+TEXT_LENGTH, 1,
                            'MAIN_.text1', 0x20000000000055e0)],
              'text block mapping mismatch')
    selected_subs = [(k, r) for k, r in subs.items() if r[0] == 1]
    c.require(selected_subs == [(1, [1, 2, TEXT_LENGTH, 0, 21, 0])],
              'text subblock mapping mismatch')
    return 21


def decode_word(word):
    """Minimal bit-field decoder for synthetic testing of the selected forms."""
    c.require(isinstance(word, int) and 0 <= word <= 0xffffffff, 'word bounds')
    op, d, a, b = word >> 26, (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    if op == 56:  # Gekko DQ form, signed 12-bit displacement.
        displacement = word & 0xfff
        if displacement & 0x800:
            displacement -= 0x1000
        return dict(mnemonic='psq_l',fD=d,rA=a,displacement=displacement,
                    W=(word >> 15) & 1,I=(word >> 12) & 7)
    if op == 59 and word & 1 == 0:
        xo, fc = (word >> 1) & 31, (word >> 6) & 31
        if xo in (18, 21) and fc == 0:
            return dict(mnemonic={18:'fdivs',21:'fadds'}[xo],fD=d,fA=a,fB=b)
        if xo == 25 and b == 0:
            return dict(mnemonic='fmuls',fD=d,fA=a,fC=fc)
    if op == 14 and a == 0:
        immediate = word & 0xffff
        if immediate & 0x8000:
            immediate -= 0x10000
        return dict(mnemonic='li',rD=d,immediate=immediate)
    if op == 25:
        return dict(mnemonic='oris',rA=a,rS=d,immediate=word & 0xffff)
    if op == 31 and ((word >> 1) & 0x3ff) == 467 and word & 1 == 0:
        return dict(mnemonic='mtspr',spr=(b << 5) | a,rS=d)
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
            facts.append(dict(address=f'{pc:08x}',word=f'{word:08x}',**decode_word(word)))
    return dict(address=f'{address:08x}',width=width,sha256=digest,
                spans=spans,instructions=facts)


def inspect(data, digest):
    # Reuse ALL existing authentication, exact schemas, metadata, address-map,
    # full data5 digest and control checks, rather than trusting a new parser.
    constants = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    blocks = db.rows(tables['Memory Blocks'])
    subs = db.rows(tables['Sub Memory Blocks'])
    root = text_mapping(blocks, subs, int(constants['image_offset'], 16))
    ranges = [range_evidence(db, root, address, width) for address, width, _ in RANGES]
    keys = ('snapshot','snapshot_sha256','program_name','created_with_ghidra_version',
            'executable_sha256_metadata','executable_sha256_property_type',
            'executable_metadata_caveat','file_bytes_table','block_size',
            'master_root','table_roots','image_offset')
    return dict({k:constants[k] for k in keys}, block_name='MAIN_.text1',
                block_key=1,subblock_key=1,block_start=f'{TEXT_START:08x}',
                block_length=TEXT_LENGTH,chain_root=root,ranges=ranges,
                constant_100=next(r for r in constants['results'] if r['address']=='80437148'),
                gqr5_startup=dict(spr=917,value='00070007',load_type=7,load_scale=0,
                                  store_type=7,store_scale=0,
                                  caveat='Startup code configuration only; not a captured live register or invariant.'))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('snapshot',type=Path)
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
