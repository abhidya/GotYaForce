#!/usr/bin/env python3
"""Read fixed opcode-0x10 evidence from the two SHA-allowlisted GBF snapshots.

Stdlib only, read-only. No arbitrary-address CLI, disassembler, or raw-range
output. Instruction annotations are fixed facts checked against exact words,
not a general decoder. All archive authentication and data5 controls are reused.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_constants as c
import read_archived_wait_evidence as w

TABLE_ADDRESS = 0x802d0da0
HANDLER_ADDRESS = 0x8004caa4
# name, block key, encoded start, length, chain root
MAPPINGS = (
    ('MAIN_.text1', 1, 0x20000000000055e0, 2796416, 21),
    ('MAIN_.data3', 5, 0x20000000002bae60, 0xf42c0, 199),
    ('MAIN_.data5', 7, 0x2000000000436a20, 27360, 263),
)
# address, width, digest, mapping index
RANGES = (
    (TABLE_ADDRESS, 72, 'fdf7c34d3ce203b91e168f8ea7ce7873e7140b5dbf1a6d5cb1710cbe868d260e', 1),
    (HANDLER_ADDRESS, 552, '3f978a468ff1f6ff295694c851e4858ca611b1d4877b0bb17962cf03f7273254', 0),
    (0x80437140, 8, '2b2979f362d94c89fe17a6e01637f14332de063fe7a544bdc5facfc046f4169f', 2),
)
WORDS = {
    0x8004caa8: (0x80e50000, 'lwz 7, 0(5)'),
    0x8004caac: (0x38070004, 'addi 0, 7, 4'),
    0x8004cab0: (0x90050000, 'stw 0, 0(5)'),
    0x8004cab4: (0x88070002, 'lbz 0, 2(7)'),
    0x8004cab8: (0x2c000002, 'cmpwi\t0, 2'),
    0x8004cabc: (0x418200f4, 'bt\t2, .+244'),
    0x8004cacc: (0x40800034, 'bf\t0, .+52'),
    0x8004cb00: (0x38a00000, 'li 5, 0'),
    0x8004cb04: (0x38c00001, 'li 6, 1'),
    0x8004cb08: (0x7cc52830, 'slw 5, 6, 5'),
    0x8004cb0c: (0xc8228720, 'lfd 1, -30944(2)'),
    0x8004cb10: (0x7c852839, 'and. 5, 4, 5'),
    0x8004cb14: (0x3c004330, 'lis 0, 17200'),
    0x8004cb18: (0x4182001c, 'bt\t2, .+28'),
    0x8004cb1c: (0x88a70003, 'lbz 5, 3(7)'),
    0x8004cb20: (0x90010008, 'stw 0, 8(1)'),
    0x8004cb24: (0x90a1000c, 'stw 5, 12(1)'),
    0x8004cb28: (0xc8010008, 'lfd 0, 8(1)'),
    0x8004cb2c: (0xec000828, 'fsubs 0, 0, 1'),
    0x8004cb30: (0xd0031ce4, 'stfs 0, 7396(3)'),
    0x8004cb34: (0x38a00001, 'li 5, 1'),
    0x8004cb58: (0xd0031d04, 'stfs 0, 7428(3)'),
    0x8004cb5c: (0x38a00002, 'li 5, 2'),
    0x8004cb80: (0xd0031d24, 'stfs 0, 7460(3)'),
    0x8004cb84: (0x38a00003, 'li 5, 3'),
    0x8004cba8: (0xd0031d44, 'stfs 0, 7492(3)'),
    0x8004cbb0: (0x38000002, 'li 0, 2'),
    0x8004cbb4: (0x38c00000, 'li 6, 0'),
    0x8004cbb8: (0x7c0903a6, 'mtctr 0'),
    0x8004cbbc: (0x38a00001, 'li 5, 1'),
    0x8004cbc0: (0x7ca03030, 'slw 0, 5, 6'),
    0x8004cbc4: (0x7c800039, 'and. 0, 4, 0'),
    0x8004cbc8: (0x4182004c, 'bt\t2, .+76'),
    0x8004cbcc: (0x88070003, 'lbz 0, 3(7)'),
    0x8004cbd0: (0x2c000002, 'cmpwi\t0, 2'),
    0x8004cbd4: (0x4182002c, 'bt\t2, .+44'),
    0x8004cbd8: (0x40800010, 'bf\t0, .+16'),
    0x8004cbdc: (0x2c000001, 'cmpwi\t0, 1'),
    0x8004cbe0: (0x40800014, 'bf\t0, .+20'),
    0x8004cbe4: (0x48000030, 'b .+48'),
    0x8004cbe8: (0x2c000004, 'cmpwi\t0, 4'),
    0x8004cbec: (0x40800028, 'bf\t0, .+40'),
    0x8004cbf0: (0x48000018, 'b .+24'),
    0x8004cbf4: (0x38000000, 'li 0, 0'),
    0x8004cbf8: (0x98031b04, 'stb 0, 6916(3)'),
    0x8004cc00: (0x98a31b04, 'stb 5, 6916(3)'),
    0x8004cc08: (0x88031b04, 'lbz 0, 6916(3)'),
    0x8004cc0c: (0x68000001, 'xori 0, 0, 1'),
    0x8004cc10: (0x98031b04, 'stb 0, 6916(3)'),
    0x8004cc18: (0x38c60001, 'addi 6, 6, 1'),
    0x8004cc54: (0x98031b44, 'stb 0, 6980(3)'),
    0x8004cc5c: (0x98a31b44, 'stb 5, 6980(3)'),
    0x8004cc64: (0x88031b44, 'lbz 0, 6980(3)'),
    0x8004cc68: (0x68000001, 'xori 0, 0, 1'),
    0x8004cc6c: (0x98031b44, 'stb 0, 6980(3)'),
    0x8004cc70: (0x38630080, 'addi 3, 3, 128'),
    0x8004cc74: (0x38c60001, 'addi 6, 6, 1'),
    0x8004cc78: (0x4200ff44, 'bdnz .-188'),
}


def mappings(blocks, subs, image):
    # Also checks every block for overlap, address encoding and segment bounds.
    w.text_mapping(blocks, subs, image)
    for name, key, encoded, length, root in MAPPINGS:
        selected = [(k, r) for k, r in blocks.items() if r[0] == name]
        c.require(len(selected) == 1 and selected[0][0] == key,
                  'command block identity mismatch')
        row = selected[0][1]
        c.require((row[4], row[5], row[6]) == (encoded, length, 0),
                  'command block mapping mismatch')
        selected_subs = [(k, r) for k, r in subs.items() if r[0] == key]
        c.require(selected_subs == [(key, [key, 2, length, 0, root, 0])],
                  'command subblock mapping mismatch')


def read_range(db, address, width, image):
    selected = [r for r in RANGES if r[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    _, _, expected, index = selected[0]
    name, key, encoded, length, root = MAPPINGS[index]
    start = c.address_start(encoded, image)
    c.require(address % 4 == width % 4 == 0 and
              start <= address < address+width <= start+length, 'range alignment/bounds')
    raw, spans = db.chain(root, address-start, width, length)
    c.require(len(raw) == width, 'range byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == expected, 'range digest mismatch')
    return raw, dict(address=f'{address:08x}', width=width, sha256=digest,
                     block_name=name, block_key=key, subblock_key=key,
                     block_start=f'{start:08x}', block_length=length,
                     subblock_type=2, starting_offset=0, source_offset=0,
                     chain_root=root, spans=spans)


def instruction_facts(raw):
    c.require(len(raw) == 552, 'handler byte width')
    facts = []
    for pc, (expected, annotation) in WORDS.items():
        word = c.integer(raw, pc-HANDLER_ADDRESS, 'I')
        c.require(word == expected, 'instruction word mismatch')
        facts.append(dict(address=f'{pc:08x}', word=f'{word:08x}', annotation=annotation))
    return facts


def inspect(data, digest):
    constants = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    image = int(constants['image_offset'], 16)
    mappings(db.rows(tables['Memory Blocks']), db.rows(tables['Sub Memory Blocks']), image)
    table, table_fact = read_range(db, TABLE_ADDRESS, 72, image)
    handler, handler_fact = read_range(db, HANDLER_ADDRESS, 552, image)
    bias, bias_fact = read_range(db, 0x80437140, 8, image)
    c.require(c.integer(table, 16*4, 'I') == HANDLER_ADDRESS, 'entry16 mismatch')
    entry, trace = db.chain(199, 0x802d0de0-0x802bae60, 4, 0xf42c0)
    c.require(entry == table[64:68], 'entry16 source mismatch')
    table_fact['entry16'] = dict(address='802d0de0', target='8004caa4', spans=trace)
    handler_fact['instructions'] = instruction_facts(handler)
    c.require(bias.hex() == '4330000000000000', 'unsigned byte bias mismatch')
    bias_fact['constant'] = next(r for r in constants['results'] if r['address']=='80437140')
    keys = ('snapshot','snapshot_sha256','program_name','created_with_ghidra_version',
            'executable_sha256_metadata','executable_sha256_property_type',
            'executable_metadata_caveat','file_bytes_table','block_size',
            'master_root','table_roots','image_offset','data5_sha256')
    return dict({k: constants[k] for k in keys}, ranges=[table_fact,handler_fact,bias_fact],
                r2_basis=dict(recorded_value='8043ea20', displacement=-30944,
                              derived_address='80437140',
                              source='docs/static-recompilation-spike.md:178',
                              caveat='Recorded documentation only; startup r2 was not freshly verified.'),
                scope='Archive evidence for modes 1 and 2; not original-DOL or runtime proof.')


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
        print(json.dumps(inspect(data, hashlib.sha256(data).hexdigest()), indent=2, allow_nan=False))
    except (OSError, c.FormatError) as exc:
        print(json.dumps({'error': str(exc)}), file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
