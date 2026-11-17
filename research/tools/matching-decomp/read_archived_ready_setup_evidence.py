#!/usr/bin/env python3
"""Read fixed mode-zero setup spans and slot zero from authenticated ProgramDB.

Read-only stdlib; no arbitrary-address CLI, raw-range output or new constants.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_constants as c
import read_archived_command_evidence as command
from read_archived_wait_evidence import TEXT_START, TEXT_LENGTH, text_mapping

SLOT_ADDRESS = 0x802d0d70
SLOT_SHA256 = 'b69bfd3e17f88dc64ebe0e5d8c02bb836ac61a4e64f32b8e016106d18076f36a'
RANGES = (
    (0x80006f98, 28, 'f60303935eb09bd98a7dc923acee50f14334cc5f73b27ced28c6d436dd00eda1'),
    (0x8004871c, 208, 'ed37e8d151614f6a73f92005849ef40d58ee6dd328e75914c862c4c6c9db29e4'),
    (0x8004a754, 220, '6029f652ed9d3b61961394341db00103e356b05aba56ad30d86c31f014e02fec'),
    (0x8004d548, 244, 'f6d1ded4ca75a50c1df6bb8129391153a259d31bf80816e9c43a97306df249a0'),
    (0x8004adc8, 192, 'feef7d2deb1076d9da60cb2c3a5f129b0fe3016c4f8ffd9d1450c7405b36c919'),
    (0x8004af94, 76, 'd184495d0aa2ea059570c526d67319d358b4d1414c03d81e32b7ce9b553b7bf0'),
)
# Narrow manual instruction annotations, not a general decoder.
WORDS = {
    0x80006f98: (0x88830097, 'lbz r4,0x97(r3): live actor selector'),
    0x80006f9c: (0x3c60803c, 'lis r3,0x803c'),
    0x80006fa0: (0x3803b4c0, 'addi r0,r3,-0x4b40: base 803bb4c0'),
    0x80006fa4: (0x7c830774, 'extsb r3,r4: signed selector'),
    0x80006fa8: (0x1c630c30, 'mulli r3,r3,0xc30'),
    0x80006fac: (0x7c601a14, 'add r3,r0,r3: modulo32 address'),
    0x80006fb0: (0x4e800020, 'blr'),
    0x80048734: (0xffe00890, 'fmr f31,f1: retain incoming frame'),
    0x80048738: (0x7cbd2b78, 'mr r29,r5: group'),
    0x8004873c: (0x7cde3378, 'mr r30,r6: action'),
    0x80048740: (0x7c9c2378, 'mr r28,r4: channel'),
    0x80048750: (0x48004aa5, 'bl 8004d1f4: resolve before stores'),
    0x8004876c: (0x9bbf0028, 'stb r29,0x28(r31): group'),
    0x80048778: (0x9bdf0029, 'stb r30,0x29(r31): action'),
    0x8004877c: (0x48004ac9, 'bl 8004d244: actual metadata'),
    0x80048780: (0x889f002a, 'lbz r4,0x2a(r31): flags after metadata'),
    0x80048788: (0xc00286d4, 'lfs f0,-0x792c(r2): existing authenticated zero'),
    0x80048790: (0x5485cffe, 'srwi r5,r4,7'),
    0x80048798: (0x98bf0031, 'stb r5,0x31(r31): bank'),
    0x8004879c: (0x38800000, 'li r4,0: bank index'),
    0x800487a0: (0x38a00000, 'li r5,0: setup argument'),
    0x800487a4: (0x981f002f, 'stb r0,0x2f(r31)'),
    0x800487a8: (0xd01f0020, 'stfs f0,0x20(r31)'),
    0x800487ac: (0xd01f0018, 'stfs f0,0x18(r31)'),
    0x800487b0: (0xd01f001c, 'stfs f0,0x1c(r31)'),
    0x800487b4: (0x981f0036, 'stb r0,0x36(r31)'),
    0x800487b8: (0xd01f0010, 'stfs f0,0x10(r31)'),
    0x800487bc: (0xd3ff0014, 'stfs f31,0x14(r31)'),
    0x800487c0: (0xd01f0008, 'stfs f0,8(r31)'),
    0x800487c4: (0xd3ff000c, 'stfs f31,12(r31)'),
    0x800487c8: (0xc03f000c, 'lfs f1,12(r31): reload frame'),
    0x800487cc: (0x48001f89, 'bl 8004a754'),
    0x800487e8: (0x4e800020, 'blr'),
    0x8004a788: (0x98bf0035, 'stb r5,0x35(r31): before bank read'),
    0x8004a78c: (0x881f0031, 'lbz r0,0x31(r31)'),
    0x8004a794: (0x41820010, 'beq 8004a7a4: primary bank'),
    0x8004a798: (0x801d1d7c, 'lwz r0,0x1d7c(r29): alternate bank'),
    0x8004a79c: (0x901f0000, 'stw r0,0(r31)'),
    0x8004a7a4: (0x801d1d78, 'lwz r0,0x1d78(r29): primary bank'),
    0x8004a7a8: (0x901f0000, 'stw r0,0(r31)'),
    0x8004a7b4: (0x981f002e, 'stb r0,0x2e(r31): clear before resolution'),
    0x8004a7b8: (0x48002d91, 'bl 8004d548'),
    0x8004a7bc: (0x7c600775, 'extsb. r0,r3: signed return-byte test'),
    0x8004a7c0: (0x987f0038, 'stb r3,0x38(r31): always save return byte'),
    0x8004a7c4: (0x4182000c, 'beq 8004a7d0'),
    0x8004a7cc: (0x981f002e, 'stb r0,0x2e(r31): nonzero result'),
    0x8004a7dc: (0x48001119, 'bl 8004b8f4: range snapshot'),
    0x8004a7e8: (0x80bd04b0, 'lwz r5,0x4b0(r29): each iteration'),
    0x8004a7f8: (0x7ca500ae, 'lbzx r5,r5,r0: live descriptor joint'),
    0x8004a7fc: (0x38c00001, 'li r6,1: setup flag'),
    0x8004a800: (0x480002e1, 'bl 8004aae0'),
    0x8004a82c: (0x4e800020, 'blr'),
    0x8004d568: (0x80630000, 'lwz r3,0(r3): bank'),
    0x8004d570: (0x4082000c, 'bne 8004d57c'),
    0x8004d574: (0x3860ffff, 'li r3,-1: null bank leaves descriptor untouched'),
    0x8004d57c: (0x881e002a, 'lbz r0,0x2a(r30)'),
    0x8004d584: (0x540015fa, 'rlwinm r0,r0,2,23,29: masked group displacement'),
    0x8004d588: (0x7c83002e, 'lwzx r4,r3,r0'),
    0x8004d590: (0x40820018, 'bne 8004d5a8'),
    0x8004d594: (0x83830000, 'lwz r28,0(r3): fallback slot'),
    0x8004d59c: (0x801c0000, 'lwz r0,0(r28)'),
    0x8004d5a0: (0x901e0004, 'stw r0,4(r30)'),
    0x8004d5a8: (0x881e002b, 'lbz r0,0x2b(r30)'),
    0x8004d5ac: (0x7c000774, 'extsb r0,r0: signed action'),
    0x8004d5b4: (0x7f840214, 'add r28,r4,r0: retain selected slot'),
    0x8004d5b8: (0x801c0000, 'lwz r0,0(r28)'),
    0x8004d5bc: (0x901e0004, 'stw r0,4(r30)'),
    0x8004d5c0: (0x801e0004, 'lwz r0,4(r30): reload after store'),
    0x8004d5c8: (0x40820018, 'bne 8004d5e0'),
    0x8004d5cc: (0x807e0000, 'lwz r3,0(r30): reload bank after null descriptor'),
    0x8004d5d4: (0x83830000, 'lwz r28,0(r3): fallback slot'),
    0x8004d5d8: (0x801c0000, 'lwz r0,0(r28)'),
    0x8004d5dc: (0x901e0004, 'stw r0,4(r30)'),
    0x8004d5e0: (0x807e0004, 'lwz r3,4(r30): tag test reload'),
    0x8004d5e8: (0x41820030, 'beq 8004d618: untagged'),
    0x8004d5f4: (0x901e0004, 'stw r0,4(r30): clear tag before allocation'),
    0x8004d5f8: (0x4814a415, 'bl 800197a0c: allocation'),
    0x8004d5fc: (0x809e0004, 'lwz r4,4(r30): after-allocation reload'),
    0x8004d604: (0x8063000c, 'lwz r3,12(r3): allocation archive'),
    0x8004d608: (0x80a40000, 'lwz r5,0(r4): payload size'),
    0x8004d60c: (0x4820da01, 'bl 8025b00c: archive parse'),
    0x8004d610: (0x93bc0000, 'stw r29,0(r28): retained selected slot'),
    0x8004d614: (0x93be0004, 'stw r29,4(r30): descriptor after slot'),
    0x8004d638: (0x4e800020, 'blr'),
    0x8004adec: (0x54e007ff, 'clrlwi. r0,r7,31: setup flag bit1'),
    0x8004ae00: (0x41820910, 'beq 8004b710: non-setup branch'),
    0x8004ae04: (0x4bfbc195, 'bl 80006f98'),
    0x8004ae08: (0x809d0004, 'lwz r4,4(r29): part descriptor'),
    0x8004ae0c: (0x1c1f0030, 'mulli r0,r31,0x30: pose displacement'),
    0x8004ae10: (0x8084000c, 'lwz r4,12(r4): first archive retained'),
    0x8004ae14: (0x7c630214, 'add r3,r3,r0: pose address'),
    0x8004ae18: (0x8004000c, 'lwz r0,12(r4): snapshot count BEFORE pose reads'),
    0x8004ae1c: (0xc043000c, 'lfs f2,12(r3): pose x'),
    0x8004ae20: (0xc023001c, 'lfs f1,28(r3): pose y'),
    0x8004ae24: (0x7c00f840, 'cmplw r0,r31: unsigned count versus index'),
    0x8004ae28: (0xc003002c, 'lfs f0,44(r3): pose z AFTER compare'),
    0x8004ae2c: (0xd0410018, 'stfs f2,24(r1): saved x'),
    0x8004ae30: (0xd021001c, 'stfs f1,28(r1): saved y'),
    0x8004ae34: (0xd0010020, 'stfs f0,32(r1): saved z'),
    0x8004ae38: (0x4181015c, 'bgt 8004af94: in-count skips globals'),
    0x8004ae44: (0x39040bc8, 'addi r8,r4,0xbc8: global block 802b0bc8'),
    0x8004ae4c: (0x80e80000, 'lwz r7,0(r8): OUT-OF-COUNT only'),
    0x8004ae50: (0x80c80004, 'lwz r6,4(r8): OUT-OF-COUNT only'),
    0x8004ae54: (0x80a80008, 'lwz r5,8(r8): OUT-OF-COUNT only'),
    0x8004ae58: (0x8008000c, 'lwz r0,12(r8): OUT-OF-COUNT only'),
    0x8004ae6c: (0x48202689, 'bl 8024d4f4: out-of-count call'),
    0x8004af94: (0x7c832378, 'mr r3,r4: retained first archive'),
    0x8004af98: (0x7fe4fb78, 'mr r4,r31: joint index'),
    0x8004af9c: (0x482101dd, 'bl 8025b178: public name'),
    0x8004afa0: (0x80bd0004, 'lwz r5,4(r29): descriptor reload after name'),
    0x8004afa8: (0x8065000c, 'lwz r3,12(r5): archive reload after name'),
    0x8004afac: (0x48210205, 'bl 8025b1b0: public address'),
    0x8004afbc: (0x38a00000, 'li r5,0'),
    0x8004afc0: (0x38c00000, 'li r6,0'),
    0x8004afc4: (0x48202c41, 'bl 8024dc04: JObjAddAnim'),
    0x8004afc8: (0x807e007c, 'lwz r3,0x7c(r30): actual attached AObj'),
    0x8004afd0: (0x40820320, 'bne 8004b2f0: surviving AObj branch'),
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


def slot_evidence(db, image):
    name, key, encoded, length, root = command.MAPPINGS[1]
    start = c.address_start(encoded, image)
    c.require(start <= SLOT_ADDRESS < SLOT_ADDRESS + 4 <= start + length,
              'slot mapping bounds')
    raw, spans = db.chain(root, SLOT_ADDRESS-start, 4, length)
    c.require(len(raw) == 4, 'slot byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == SLOT_SHA256, 'slot digest mismatch')
    target = c.integer(raw, 0, 'I')
    c.require(target == 0x8004871c, 'slot target mismatch')
    return dict(address=f'{SLOT_ADDRESS:08x}', width=4, sha256=digest,
                target=f'{target:08x}', spans=spans, block_name=name,
                block_key=key, subblock_key=key, chain_root=root)


def inspect(data, digest):
    constants = c.inspect(data, digest)
    db = c.GBF(data)
    tables = db.tables()
    root = text_mapping(db.rows(tables['Memory Blocks']),
                        db.rows(tables['Sub Memory Blocks']), int(constants['image_offset'],16))
    command.mappings(db.rows(tables['Memory Blocks']),
                     db.rows(tables['Sub Memory Blocks']), int(constants['image_offset'],16))
    slot = slot_evidence(db, int(constants['image_offset'],16))
    ranges = [range_evidence(db,root,address,width) for address,width,_ in RANGES]
    keys = ('snapshot','snapshot_sha256','program_name','created_with_ghidra_version',
            'executable_sha256_metadata','executable_sha256_property_type',
            'executable_metadata_caveat','file_bytes_table','block_size',
            'master_root','table_roots','image_offset')
    return dict({k:constants[k] for k in keys}, block_name='MAIN_.text1', block_key=1,
                subblock_key=1, block_start=f'{TEXT_START:08x}', block_length=TEXT_LENGTH,
                chain_root=root, ranges=ranges, mode_table_slot0=slot,
                constant_scope='Existing twelve constants unchanged; only mode-table slot0 added. Out-of-count global values and part1 postamble constants are not read.',
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
