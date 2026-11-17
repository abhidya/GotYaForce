#!/usr/bin/env python3
"""Read two fixed selector/metadata spans from authenticated archived ProgramDB.

Read-only stdlib; no arbitrary-address CLI, raw-range output or new constants.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_constants as c
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH, text_mapping

RANGES = (
    (0x8004d1f4, 80, '9e0f6e4ba064be40990771590bfc7bd13f3fa71b4299825c03df53932bf73bd2'),
    (0x8004d244, 772, 'f2464189801b361f9fdadecff1325e0f69c9cb2c4b1c2101f64fabc1fc1e5128'),
)
WORDS = {
    0x8004d218: (0x88030582, 'lbz r0,0x582(r3): default-group byte before family pointer'),
    0x8004d21c: (0x7c000774, 'extsb r0,r0: signed default group'),
    0x8004d224: (0x80631d88, 'lwz r3,0x1d88(r3): family pointer'),
    0x8004d1fc: (0x80631d8c, 'lwz r3,0x1d8c(r3): shared pointer'),
    0x8004d200: (0x54800e3c, 'rlwinm r0,r4,1,24,30: masked shared group times two'),
    0x8004d228: (0x5480083c, 'slwi r0,r4,1: group displacement modulo32'),
    0x8004d204: (0x7c0302ae, 'lhax r0,r3,r0: signed group displacement'),
    0x8004d22c: (0x7c0302ae, 'lhax r0,r3,r0: signed group displacement'),
    0x8004d234: (0x54a0083c, 'slwi r0,r5,1: action displacement modulo32'),
    0x8004d238: (0x7c0302ae, 'lhax r0,r3,r0: signed action displacement'),
    0x8004d240: (0x4e800020, 'blr: selector endpoint'),
    0x8004d244: (0x88060000, 'lbz r0,0(r6): scale byte first'),
    0x8004d24c: (0x98050032, 'stb r0,0x32(r5): precedes channel dispatch'),
    0x8004d250: (0x418201e8, 'beq 8004d438: channel2'),
    0x8004d25c: (0x41820018, 'beq 8004d274: channel0'),
    0x8004d260: (0x40800138, 'bge 8004d398: channel1'),
    0x8004d264: (0x4e800020, 'blr: negative channel after scale write'),
    0x8004d270: (0x48000250, 'b 8004d4c0: channel3'),
    0x8004d294: (0x88860006, 'lbz r4,6(r6): mirror flags snapshot'),
    0x8004d2a4: (0x88050030, 'lbz r0,0x30(r5): old mirror only for toggle'),
    0x8004d2a8: (0x68000001, 'xori r0,r0,1'),
    0x8004d2ac: (0x98050030, 'stb r0,0x30(r5): mirror toggle'),
    0x8004d2d8: (0x88060006, 'lbz r0,6(r6): reload flags after mirror update'),
    0x8004d3fc: (0x8806000e, 'lbz r0,14(r6): channel1 flags reload'),
    0x8004d49c: (0x88060016, 'lbz r0,22(r6): channel2 flags reload'),
    0x8004d524: (0x8806001e, 'lbz r0,30(r6): channel3 flags reload'),
    0x8004d2f8: (0x88e60009, 'lbz r7,9(r6): first fallback selector'),
    0x8004d2fc: (0x7ce00775, 'extsb. r0,r7: signed selector test'),
    0x8004d304: (0x88050033, 'lbz r0,0x33(r5): bank before descriptor lookup'),
    0x8004d308: (0x808304b0, 'lwz r4,0x4b0(r3): fallback descriptor'),
    0x8004d30c: (0x7c000774, 'extsb r0,r0: signed bank'),
    0x8004d310: (0x5400083c, 'slwi r0,r0,1: bank displacement modulo32'),
    0x8004d314: (0x88e400be, 'lbz r7,0xbe(r4): fallback value before target add'),
    0x8004d318: (0x7c830214, 'add r4,r3,r0: target base'),
    0x8004d31c: (0x98e41d74, 'stb r7,0x1d74(r4): first fallback target'),
    0x8004d324: (0x88050033, 'lbz r0,0x33(r5): direct first target bank; r7 retained'),
    0x8004d334: (0x98e41d74, 'stb r7,0x1d74(r4): retained metadata9, no reread'),
    0x8004d364: (0x88050033, 'lbz r0,0x33(r5): direct second target bank; r6 retained'),
    0x8004d374: (0x98c41d75, 'stb r6,0x1d75(r4): retained metadata10, no reread'),
    0x8004d338: (0x88c6000a, 'lbz r6,10(r6): second selector after first store'),
    0x8004d344: (0x88050033, 'lbz r0,0x33(r5): second independent bank load'),
    0x8004d348: (0x808304b0, 'lwz r4,0x4b0(r3): second descriptor reload'),
    0x8004d354: (0x88c400bf, 'lbz r6,0xbf(r4): second fallback byte'),
    0x8004d35c: (0x98c41d75, 'stb r6,0x1d75(r4): second target'),
    0x8004d378: (0x88050033, 'lbz r0,0x33(r5): final bank reload'),
    0x8004d384: (0x88031d74, 'lbz r0,0x1d74(r3): first copy source'),
    0x8004d388: (0x98031d94, 'stb r0,0x1d94(r3): first copy destination'),
    0x8004d38c: (0x88031d75, 'lbz r0,0x1d75(r3): second copy source after first store'),
    0x8004d390: (0x98031d95, 'stb r0,0x1d95(r3): second copy destination'),
    0x8004d544: (0x4e800020, 'blr: metadata endpoint'),
}

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
    for pc, (expected, annotation) in WORDS.items():
        if address <= pc < address+width:
            word = c.integer(raw, pc-address, 'I')
            c.require(word == expected, 'instruction word mismatch')
            facts.append(dict(address=f'{pc:08x}', word=f'{word:08x}', annotation=annotation))
    return dict(address=f'{address:08x}', width=width, sha256=digest,
                spans=spans, instructions=facts)


def inspect(data, digest):
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
                constant_scope='Existing twelve targets unchanged; no new table or constant targets.',
                provenance_caveat='Archived ProgramDB agreement is not original-DOL or live-runtime proof.')


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
