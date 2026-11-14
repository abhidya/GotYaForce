#!/usr/bin/env python3
"""Five fixed matrix instruction spans and four constants from authenticated local GBF.

Read-only stdlib. Emits derived instruction facts, never raw ranges. No arbitrary
address CLI, execution, uploads or original-DOL parity claim.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys
import read_archived_constants as c
from read_archived_wait_evidence import text_mapping, TEXT_START, TEXT_LENGTH

RANGES = (
    (0x8020af28, 52, '16a1071dcfbc5fc2775a7b929ee6903ac5ab4d946af9119d57f5c8b823f41df1'),
    (0x8020b4f8, 40, 'e0973dcf5701b4b975a0a3d358a66e9af66353276f25f530500ab1ca52cd3de6'),
    (0x80046dd4, 168, '9522644852d3cf46ccd31a6489318c9c7378d535ac93922ca9785916d495eca5'),
    (0x8020af5c, 204, '76d05fd3f0428b0ee7d051458a11fcaddd6de21fb68961b8a19990beefa68637'),
    (0x8020b578, 164, '712544e159855114729c096e3d362ac93149ebd2f3776e517395ba37c6d1970a'),
)
CALLER_FACTS = {
    0x80046e00:(0x481c4779, 'bl 8020b578: quaternion matrix'),
    0x80046e28:(0x481c4135, 'bl 8020af5c: parent/local concat'),
    0x80046e2c:(0xa8bd0000, 'lha r5,0(r29): correction X'),
    0x80046e34:(0xa8dd0002, 'lha r6,2(r29): correction Y'),
    0x80046e3c:(0xa8fd0004, 'lha r7,4(r29): correction Z'),
    0x80046e40:(0x4bffe9f9, 'bl 80045838: short correction'),
    0x80046e54:(0x481c46a5, 'bl 8020b4f8: scale matrix'),
    0x80046e64:(0x481c40f9, 'bl 8020af5c: destination/scale concat'),
}
TARGETS = {0x8043ca68:'3f800000', 0x8043ca6c:'00000000',
           0x80435ca0:'00000000', 0x80435ca4:'3f800000'}


def decode_float(word):
    """Only observed matrix arithmetic and paired memory forms; no executor."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    op, d, a, b = word >> 26, (word >> 21)&31, (word >> 16)&31, (word >> 11)&31
    fc, xo, xx = (word >> 6)&31, (word >> 1)&31, (word >> 1)&1023
    if op in (48,52):
        n=word&0xffff
        return dict(mnemonic='lfs' if op==48 else 'stfs', fD=d,rA=a,
                    displacement=n-65536 if n&32768 else n)
    if op in (56,60):
        n=word&0xfff
        return dict(mnemonic='psq_l' if op==56 else 'psq_st', fD=d,rA=a,
                    displacement=n-4096 if n&2048 else n,W=(word>>15)&1,I=(word>>12)&7)
    c.require(word&1 == 0, 'record form unsupported')
    if op==4:
        if xx in (528,560,592,624):
            return dict(mnemonic={528:'ps_merge00',560:'ps_merge01',592:'ps_merge10',624:'ps_merge11'}[xx],fD=d,fA=a,fB=b)
        names={10:'ps_sum0',11:'ps_sum1',12:'ps_muls0',13:'ps_muls1',14:'ps_madds0',15:'ps_madds1',25:'ps_mul',28:'ps_msub',29:'ps_madd',30:'ps_nmsub'}
        if xo in names:
            return dict(mnemonic=names[xo],fD=d,fA=a,fC=fc,fB=b)
    if op==59:
        if xo in (20,21) and fc==0:
            return dict(mnemonic={20:'fsubs',21:'fadds'}[xo],fD=d,fA=a,fB=b)
        if xo==24 and a==fc==0:
            return dict(mnemonic='fres',fD=d,fB=b)
        if xo==25 and b==0:
            return dict(mnemonic='fmuls',fD=d,fA=a,fC=fc)
    raise c.FormatError('unsupported floating instruction')


def range_evidence(db, root, address, width):
    matches=[r for r in RANGES if r[:2]==(address,width)]
    c.require(len(matches)==1, 'range not allowlisted')
    raw,spans=db.chain(root,address-TEXT_START,width,TEXT_LENGTH)
    digest=hashlib.sha256(raw).hexdigest()
    c.require(len(raw)==width and digest==matches[0][2], 'range digest/width mismatch')
    facts=[]
    for off in range(0,width,4):
        word=c.integer(raw,off,'I')
        if address+off in CALLER_FACTS:
            expected,annotation=CALLER_FACTS[address+off]
            c.require(word==expected, 'caller instruction mismatch')
            facts.append(dict(address=f'{address+off:08x}',annotation=annotation))
        if word>>26 in (4,56,60,59,48,52):
            facts.append(dict(address=f'{address+off:08x}',**decode_float(word)))
    return dict(address=f'{address:08x}',width=width,sha256=digest,spans=spans,instructions=facts)


def constant_evidence(db, address):
    c.require(address in TARGETS, 'constant not allowlisted')
    start,length,root=(0x80436a20,27360,263) if address>=0x80436a20 else (0x804335a0,11040,262)
    raw,spans=db.chain(root,address-start,4,length)
    c.require(raw.hex()==TARGETS[address], 'constant bits mismatch')
    return dict(address=f'{address:08x}',bits=raw.hex(),value=struct.unpack('>f',raw)[0],spans=spans)


def inspect(data,digest):
    auth=c.inspect(data,digest)
    db=c.GBF(data); tables=db.tables()
    blocks,subs=db.rows(tables['Memory Blocks']),db.rows(tables['Sub Memory Blocks'])
    image=int(auth['image_offset'],16)
    root=text_mapping(blocks,subs,image)
    c.require(c.data5_mapping(blocks,subs,image)==(0x80436a20,0x8043d500,7,'MAIN_.data5',7,27360,263),'data5 mismatch')
    row=blocks.get(6)
    c.require(row is not None and row[0]=='MAIN_.data4' and row[5:]==[11040,0] and c.address_start(row[4],image)==0x804335a0,'data4 mismatch')
    c.require([(k,r) for k,r in subs.items() if r[0]==6]==[(6,[6,2,11040,0,262,0])],'data4 subblock mismatch')
    return dict(snapshot=auth['snapshot'],snapshot_sha256=auth['snapshot_sha256'],
                executable_sha256_metadata=auth['executable_sha256_metadata'],
                ranges=[range_evidence(db,root,a,n) for a,n,_ in RANGES],
                constants=[constant_evidence(db,a) for a in TARGETS],
                caveat='Archived ProgramDB evidence only, not unchanged original DOL or live parity. Paired-single facts do not establish FPSCR/GQR runtime state.')


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
