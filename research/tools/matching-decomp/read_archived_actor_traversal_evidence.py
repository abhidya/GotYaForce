#!/usr/bin/env python3
"""Fixed actor traversal/matrix and zero-trig evidence from authenticated GBF.

Read-only stdlib; no arbitrary-address CLI or instruction execution. Only the
listed spans and constants are read. Derived instruction fields are emitted,
not raw ranges. Unselected instructions are omitted, not inferred.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys
import read_archived_constants as c
import read_archived_world_matrix_evidence as w
from read_archived_wait_evidence import text_mapping, TEXT_START, TEXT_LENGTH

RANGES = (
    (0x800457d4, 100, '5834ba9c6bf11389b74fe25a13eaaf04a90d4aa5e6ba376d7a0ea3004613a2e5'),
    (0x80045838, 224, '90bfcf864297a8889d20a2489af7de1e3441f2b62db6983b4bc0d1f6c904c595'),
    (0x80046698, 68, '61b77c5623de2cd35042a7082b2d50a43304dc672bd99fa2006f59ea41d37a27'),
    (0x80046754, 72, 'dab21dfac6dedaabc6b1c10ef17f7adb824ffe7e5742e8161fbb1db015a4fdde'),
    (0x8004679c, 376, '4618782341d1ab5d9a186147c16d4ad9a7a1cdddc894d3a78719e58f34d15b57'),
    (0x80046bd0, 304, '8eb7629551da53d25aedebd78bd1a11804468247065eb4685b79f68cfa013cbd'),
    (0x8020aefc, 44, '72cc63551ec26fadb4106dfa694a34efe3be38fa7fa97f802d306453f072dfba'),
    (0x8020b4ac, 76, '282352ff267e0d5e83043d89188bc46363fe127380a6eb5414487ff0da6072f7'),
    (0x8020ba54, 36, 'c7b35d4075874e063982faa1d7d086e5d5ec4d70aed2b56c619b5e440e18e1ab'),
    (0x8020b238, 112, 'e655ac2abaa9fab3af19ebc0df03b7ec62c2f35b640cfeeff6f6941b6db7d178'),
    (0x8020b2a8, 176, '832e4fbd68ca5d25b4345248b3eadb3421dcade987a190829e0617a61b19a8d7'),
    (0x8023cc44, 72, 'f6fb91c05f7548feeb7ab6910eddf99de5616a2f69ffb302668e9051badb44b2'),
    (0x8023c480, 212, '7191f0b4d2e319d285c8db0eb3c663aaef119792a2e0a66390ed24c441f18e0f'),
    (0x8023c9e8, 216, 'f5cca675e2bbd4c6f03e357e1551f901741db5fa9354b1a9d3e86b62fb65f2d7'),
    (0x8023b044, 244, 'e291a438fc827ef22d258b8b22405923970c977efcbfcad6171577ab95b2e6cd'),
    (0x8023bf8c, 160, '74d1575c2f44b98288faef0858309e3e440520c568d670b0ad1b946df7454f44'),
)
TARGETS = {
    0x80437078: '38c90fdb',  # short-to-radian factor
    0x80437098: '41a00000',  # alternate joint-1 translation Y
    0x8043ca68: '3f800000', 0x8043ca6c: '00000000',
    0x8043d030: '3ff0000000000000',  # kernel cos early return
    0x8043d150: '0000000000000000',  # cos tail argument
    0x8043d198: '0000000000000000',  # sin tail argument
}


def signed(value, bits):
    return value - (1 << bits) if value & (1 << (bits-1)) else value


def decode_selected(word, pc):
    """Selected PPC/Gekko fields; no execution or generic disassembler fallback."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    op, d, a, b = word >> 26, (word >> 21)&31, (word >> 16)&31, (word >> 11)&31
    fc, xo, xx = (word >> 6)&31, (word >> 1)&31, (word >> 1)&1023
    if word == 0x4e800020:
        return dict(mnemonic='blr')
    if op == 18:
        n = signed(word & 0x3fffffc, 26)
        return dict(mnemonic='bl' if word&1 else 'b',
                    target=f'{(n if word&2 else pc+n)&0xffffffff:08x}',AA=(word>>1)&1)
    if op == 16:
        n = signed(word & 0xfffc, 16)
        return dict(mnemonic='bc',BO=d,BI=a,LK=word&1,
                    target=f'{(n if word&2 else pc+n)&0xffffffff:08x}',AA=(word>>1)&1)
    if op in (10,11):
        return dict(mnemonic='cmpli' if op==10 else 'cmpi',BF=(word>>23)&7,L=(word>>21)&1,
                    rA=a,immediate=word&65535 if op==10 else signed(word&65535,16))
    if op in (7,14,15):
        return dict(mnemonic={7:'mulli',14:'addi',15:'addis'}[op],rD=d,rA=a,immediate=signed(word&65535,16))
    if op in (24,28):
        return dict(mnemonic='ori' if op==24 else 'andi.',rS=d,rA=a,immediate=word&65535)
    if op==21:
        return dict(mnemonic='rlwinm',rS=d,rA=a,SH=b,MB=(word>>6)&31,ME=(word>>1)&31,Rc=word&1)
    if op in (32,34,36,37,40,42,44):
        return dict(mnemonic={32:'lwz',34:'lbz',36:'stw',37:'stwu',40:'lhz',42:'lha',44:'sth'}[op],
                    rD=d,rA=a,displacement=signed(word&65535,16))
    if op in (50,54):
        return dict(mnemonic='lfd' if op==50 else 'stfd',fD=d,rA=a,displacement=signed(word&65535,16))
    if op == 31:
        if xx in (0,32) and word&1==0:
            return dict(mnemonic='cmp' if xx==0 else 'cmpl',BF=(word>>23)&7,L=(word>>21)&1,rA=a,rB=b)
        if xx in (954,922) and b==0:
            return dict(mnemonic='extsb' if xx==954 else 'extsh',rS=d,rA=a,Rc=word&1)
        if xx in (24,28,444):
            return dict(mnemonic={24:'slw',28:'and',444:'or'}[xx],rS=d,rA=a,rB=b,Rc=word&1)
        if xx in (235,266):
            return dict(mnemonic='mullw' if xx==235 else 'add',rD=d,rA=a,rB=b,Rc=word&1)
    if op==4 and word&1==0:
        if xx==40 and a==0:
            return dict(mnemonic='ps_neg',fD=d,fB=b)
        if xo==21 and fc==0:
            return dict(mnemonic='ps_add',fD=d,fA=a,fB=b)
    if op==63 and word&1==0:
        if xx in (12,15,40,72) and a==0:
            return dict(mnemonic={12:'frsp',15:'fctiwz',40:'fneg',72:'fmr'}[xx],fD=d,fB=b)
    if op in (4,48,52,56,59,60):
        return w.decode_float(word)
    return None


def range_evidence(db, root, address, width):
    matches=[r for r in RANGES if r[:2]==(address,width)]
    c.require(len(matches)==1, 'range not allowlisted')
    c.require(address%4==width%4==0 and TEXT_START<=address<address+width<=TEXT_START+TEXT_LENGTH,
              'range alignment/bounds')
    raw,spans=db.chain(root,address-TEXT_START,width,TEXT_LENGTH)
    digest=hashlib.sha256(raw).hexdigest()
    c.require(len(raw)==width and digest==matches[0][2], 'range digest/width mismatch')
    facts=[]
    for off in range(0,width,4):
        decoded=decode_selected(c.integer(raw,off,'I'),address+off)
        if decoded is not None:
            facts.append(dict(address=f'{address+off:08x}',**decoded))
    return dict(address=f'{address:08x}',width=width,sha256=digest,spans=spans,instructions=facts)


def constant_evidence(db,address):
    c.require(address in TARGETS, 'constant not allowlisted')
    width=len(TARGETS[address])//2
    raw,spans=db.chain(263,address-0x80436a20,width,27360)
    c.require(raw.hex()==TARGETS[address], 'constant bits mismatch')
    return dict(address=f'{address:08x}',bits=raw.hex(),
                value=struct.unpack('>f' if width==4 else '>d',raw)[0],spans=spans)


def inspect(data,digest):
    auth=c.inspect(data,digest)
    db=c.GBF(data); tables=db.tables()
    blocks,subs=db.rows(tables['Memory Blocks']),db.rows(tables['Sub Memory Blocks'])
    image=int(auth['image_offset'],16)
    root=text_mapping(blocks,subs,image)
    c.require(c.data5_mapping(blocks,subs,image)==(0x80436a20,0x8043d500,7,'MAIN_.data5',7,27360,263),
              'data5 mapping mismatch')
    return dict(snapshot=auth['snapshot'],snapshot_sha256=auth['snapshot_sha256'],
                executable_sha256_metadata=auth['executable_sha256_metadata'],
                ranges=[range_evidence(db,root,a,n) for a,n,_ in RANGES],
                constants=[constant_evidence(db,a) for a in TARGETS],
                caveat='Archived ProgramDB only, not original-DOL/live parity. GQR0 float, GQR5 signed16/scale0 and RN=00/NI=0 are execution-domain preconditions, not live-state evidence. Unselected instructions are omitted.')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('snapshot',type=Path);args=parser.parse_args()
    try:
        c.require(args.snapshot.is_file() and 32<=args.snapshot.stat().st_size<=c.MAX_FILE,'snapshot size/type')
        with args.snapshot.open('rb') as stream: data=stream.read(c.MAX_FILE+1)
        c.require(len(data)<=c.MAX_FILE,'snapshot size')
        print(json.dumps(inspect(data,hashlib.sha256(data).hexdigest()),indent=2,allow_nan=False))
    except (OSError,c.FormatError) as exc:
        print(json.dumps({'error':str(exc)}),file=sys.stderr);return 1
    return 0


if __name__=='__main__': sys.exit(main())
