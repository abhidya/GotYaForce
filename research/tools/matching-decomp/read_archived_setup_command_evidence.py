#!/usr/bin/env python3
"""Read fixed parser/opcode01/setup-gate evidence from authenticated GBF snapshots.

Stdlib only and read-only. Emits lineage, hashes and selected instruction facts,
not raw ranges. No arbitrary-address interface or vendor-code execution.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_constants as c
import read_archived_command_evidence as command
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH, text_mapping

RANGES = (
    (0x8004c050, 584, '1161d002aab162ea3506cd8a088d941fb362861f51cfae3f35ac6b57547d3ab0'),
    (0x8004c298, 396, '42c560d248bf6cdff40bb3e0f93a73b6ce65af55eaef0fd4874a521daa6a2188'),
    (0x80048648, 212, '0eb26bc9a603d933ffcaf3e9065583d3127cb603be56c29d887566f9211a2ad9'),
)
# Exact checked words and narrow manual annotations, not a general decoder.
# Opcode01 ends at its c420 return; neighboring handlers are excluded.
WORDS = {
    0x8004c070: (0xffe00890, 'fmr f31,f1: preserve original parser float'),
    0x8004c080: (0x7cd93378, 'mr r25,r6: preserve transition override'),
    0x8004c084: (0x7cfa3b78, 'mr r26,r7: preserve mode override'),
    0x8004c098: (0xfc20f890, 'fmr f1,f31: restore original float for every dispatch'),
    0x8004c0a8: (0x7f26cb78, 'mr r6,r25: restore transition override'),
    0x8004c0ac: (0x7f47d378, 'mr r7,r26: restore mode override'),
    0x8004c0b0: (0x38a10008, 'addi r5,r1,8: address of local cursor'),
    0x8004c0b8: (0x4e800421, 'bctrl: indirect handler call'),
    0x8004c0c0: (0x28000001, 'cmplwi r0,1: completed opcode comparison'),
    0x8004c0c4: (0x40820008, 'bne 8004c0cc'),
    0x8004c0c8: (0x3b600000, 'li r27,0: suppress terminal fallback'),
    0x8004c0d8: (0x4082ffbc, 'bne 8004c094: next nonzero opcode'),
    0x8004c0dc: (0x2c1b0000, 'cmpwi r27,0'),
    0x8004c0e0: (0x41820090, 'beq 8004c170: bypass fallback'),
    0x8004c2b0: (0xffe00890, 'fmr f31,f1: handler-local float'),
    0x8004c2b4: (0x83e50000, 'lwz r31,0(r5): old cursor'),
    0x8004c2c0: (0x381f0008, 'addi r0,r31,8'),
    0x8004c2c8: (0xfc1f0040, 'fcmpo cr0,f31,f0'),
    0x8004c2cc: (0x90050000, 'stw r0,0(r5): advance before operands'),
    0x8004c2d0: (0x7cdd3378, 'mr r29,r6: transition override'),
    0x8004c2d4: (0x7cfe3b78, 'mr r30,r7: mode override'),
    0x8004c2d8: (0x40800024, 'bge 8004c2fc'),
    0x8004c2dc: (0xa87f0006, 'lha r3,6(r31): signed frame default'),
    0x8004c2f8: (0xefe00828, 'fsubs f31,f0,f1: signed conversion'),
    0x8004c2fc: (0x2c1e0000, 'cmpwi r30,0: mode first'),
    0x8004c300: (0x40800008, 'bge 8004c308'),
    0x8004c304: (0x8bdf0003, 'lbz r30,3(r31): mode default'),
    0x8004c308: (0x2c1d0000, 'cmpwi r29,0: transition second'),
    0x8004c30c: (0x40800008, 'bge 8004c314'),
    0x8004c310: (0x8bbf0004, 'lbz r29,4(r31): transition default'),
    0x8004c330: (0xc0180008, 'lfs f0,8(r24): prior target'),
    0x8004c334: (0xd018000c, 'stfs f0,12(r24): save prior target'),
    0x8004c338: (0x8818001d, 'lbz r0,29(r24): prior status'),
    0x8004c340: (0x41820030, 'beq 8004c370: skip accumulation'),
    0x8004c344: (0xa87a1af8, 'lha r3,6904(r26): signed prior duration'),
    0x8004c35c: (0xc0580010, 'lfs f2,16(r24): accumulator'),
    0x8004c368: (0xec02002a, 'fadds f0,f2,f0'),
    0x8004c36c: (0xd0180010, 'stfs f0,16(r24): update accumulator before setup'),
    0x8004c374: (0xfc1f0040, 'fcmpo cr0,f31,f0'),
    0x8004c378: (0x40800010, 'bge 8004c388'),
    0x8004c37c: (0xc03a1ae0, 'lfs f1,6880(r26): channel frame'),
    0x8004c380: (0xc01b1dc8, 'lfs f0,7624(r27): frame offset'),
    0x8004c384: (0xefe1002a, 'fadds f31,f1,f0: persists across selected channels'),
    0x8004c388: (0xfc20f890, 'fmr f1,f31: setup float'),
    0x8004c38c: (0x88bf0001, 'lbz r5,1(r31): animation operand'),
    0x8004c390: (0x88df0002, 'lbz r6,2(r31): secondary operand'),
    0x8004c39c: (0x7fa7eb78, 'mr r7,r29: transition argument'),
    0x8004c3a0: (0x7fc8f378, 'mr r8,r30: mode argument'),
    0x8004c3a4: (0x4bffc2a5, 'bl 80048648: setup gate'),
    0x8004c3ac: (0x9818001d, 'stb r0,29(r24): set status after setup returns'),
    0x8004c3b0: (0xc0380010, 'lfs f1,16(r24): accumulator after setup'),
    0x8004c3b4: (0xc01a1ae0, 'lfs f0,6880(r26): frame after setup'),
    0x8004c3b8: (0xec01002a, 'fadds f0,f1,f0'),
    0x8004c3bc: (0xd0180008, 'stfs f0,8(r24): target after setup'),
    0x8004c3d0: (0x4180ff50, 'blt 8004c320: next channel'),
    0x8004c3e0: (0x981b071d, 'stb r0,1821(r27): clear channel-one marker'),
    0x8004c3e4: (0x881f0005, 'lbz r0,5(r31): unsupported nonzero tail'),
    0x8004c3ec: (0x4182001c, 'beq 8004c408: zero tail skips conversion'),
    0x8004c3f8: (0xc022870c, 'lfs f1,-30964(r2): recorded-r2 address 8043712c, not authenticated constant'),
    0x8004c420: (0x4e800020, 'blr: opcode01 return'),
    0x80048664: (0x80031d88, 'lwz r0,7560(r3): readiness pointer one'),
    0x8004866c: (0x41820098, 'beq 80048704: return if missing'),
    0x80048670: (0x801e1d8c, 'lwz r0,7564(r30): readiness pointer two'),
    0x80048678: (0x40820008, 'bne 80048680'),
    0x8004867c: (0x48000088, 'b 80048704: return if missing'),
    0x80048680: (0x2c1f0001, 'cmpwi r31,1: channel-one gate'),
    0x80048688: (0x881e0578, 'lbz r0,1400(r30): marker one'),
    0x80048694: (0x881e1db3, 'lbz r0,7603(r30): marker two'),
    0x8004869c: (0x41820068, 'beq 80048704: both markers one suppress setup'),
    0x800486a0: (0x887e1d9a, 'lbz r3,7578(r30): blocked mask'),
    0x800486a8: (0x7c00f830, 'slw r0,r0,r31'),
    0x800486ac: (0x7c630774, 'extsb r3,r3'),
    0x800486b0: (0x7c600039, 'and. r0,r3,r0'),
    0x800486b4: (0x41820018, 'beq 800486cc: unblocked dispatch'),
    0x800486c0: (0x38800000, 'li r4,0: blocked-path argument'),
    0x800486c4: (0x48001d59, 'bl 8004a41c: blocked path'),
    0x800486c8: (0x4800003c, 'b 80048704: blocked path skips follow-up'),
    0x800486d0: (0x5500103a, 'rlwinm r0,r8,2,0,29: mode-indexed dispatch'),
    0x800486e8: (0x4e800421, 'bctrl: unblocked setup dispatch'),
    0x800486ec: (0x2c1f0001, 'cmpwi r31,1'),
    0x800486f0: (0x40820014, 'bne 80048704'),
    0x800486fc: (0xd01e06d8, 'stfs f0,1752(r30): channel-one reset'),
    0x80048700: (0x4800498d, 'bl 8004d08c: channel-one follow-up'),
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


def verify_entry1(table):
    c.require(len(table) == 72, 'dispatch table width')
    c.require(c.integer(table, 4, 'I') == 0x8004c298, 'entry1 mismatch')


def inspect(data, digest):
    # Retain existing snapshot authentication, exact schemas, metadata, address
    # mapping, full data5 digest and controls. Do not add new constant targets.
    constants = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    root = text_mapping(db.rows(tables['Memory Blocks']),
                        db.rows(tables['Sub Memory Blocks']), int(constants['image_offset'],16))
    command.mappings(db.rows(tables['Memory Blocks']),
                     db.rows(tables['Sub Memory Blocks']), int(constants['image_offset'],16))
    table, table_fact = command.read_range(db, command.TABLE_ADDRESS, 72,
                                            int(constants['image_offset'],16))
    verify_entry1(table)
    table_fact['entry1'] = dict(address='802d0da4', target='8004c298')
    ranges = [range_evidence(db,root,address,width) for address,width,_ in RANGES]
    keys = ('snapshot','snapshot_sha256','program_name','created_with_ghidra_version',
            'executable_sha256_metadata','executable_sha256_property_type',
            'executable_metadata_caveat','file_bytes_table','block_size',
            'master_root','table_roots','image_offset')
    return dict({k:constants[k] for k in keys}, block_name='MAIN_.text1', block_key=1,
                subblock_key=1, block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                chain_root=root, ranges=ranges, dispatch_table=table_fact,
                constant_scope='Existing twelve targets unchanged; 8043712c remains unsupported.',
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
