#!/usr/bin/env python3
"""Only536-byte2cf80 and4-byte80436f6c; no transitive selections or listings."""
import hashlib
import json
import struct
import read_archived_initial_contact_evidence as prior
c=prior.c
RANGE=(0x8002cf80,536)
CONSTANT=0x80436f6c
DATA_MAPPING=(0x80436a20,0x8043d500,7,'MAIN_.data5',7,27360,263)
def summarize_prefix(rows):
    by={int(r['address'],16):r for r in rows}
    def check(pc,name,**fields):
        r=by[pc]
        c.require(r['mnemonic']==name and all(r.get(k)==v for k,v in fields.items()),'contact prefix order')
    for pc,base,offset,reg in ((0x8002cfac,30,0,28),(0x8002cfb0,28,0x20,26),
        (0x8002cff0,29,0,27),(0x8002cff4,28,0x20,0),(0x8002cff8,27,0x20,3)):
        check(pc,'lwz',rA=base,displacement=offset,rD=reg)
    check(0x8002cfb4,'lbz',rA=26,displacement=0x83,rD=0)
    check(0x8002cfb8,'extsb',rS=0,rA=0,Rc=1)
    check(0x8002cfbc,'bc',BO=4,BI=2,target='8002cfe4')
    check(0x8002cfc0,'lfs',rA=28,displacement=0x68,fD=1)
    check(0x8002cfc8,'lfs',rA=28,displacement=0x88,fD=0)
    check(0x8002cfd0,'lbz',rA=26,displacement=0x3e4,rD=0)
    check(0x8002cfd4,'fsubs',fD=0,fA=1,fB=0,Rc=0)
    check(0x8002cfd8,'extsb',rS=0,rA=0,Rc=0)
    check(0x8002cfdc,'rlwinm',rS=0,rA=0,SH=2,MB=0,ME=29,Rc=0)
    check(0x8002cfe0,'stfsx',fS=0,rA=3,rB=0)
    check(0x8002cffc,'cmpl',rA=0,rB=3)
    check(0x8002d000,'bc',BO=12,BI=2,target='8002d15c')
    check(0x8002d004,'cmpl',rA=26,rB=3)
    check(0x8002d00c,'bc',BO=12,BI=2,target='8002d15c')
    for start,source,destination in ((0x8002d014,28,0x4d0),(0x8002d040,27,0x368)):
        check(start,'addi',rD=0,rA=0,immediate=45)
        check(start+4,'addi',rD=3,rA=3,immediate=destination)
        check(start+8,'addi',rD=4,rA=source,immediate=0x54)
        check(start+12,'addi',rD=5,rA=3,immediate=-4)
        check(start+16,'mtctr',rS=0)
        check(start+20,'lwz',rD=3,rA=4,displacement=4)
        check(start+24,'lwzu',rD=0,rA=4,displacement=8)
        check(start+28,'stw',rS=3,rA=5,displacement=4)
        check(start+32,'stwu',rS=0,rA=5,displacement=8)
        check(start+36,'bc',BO=16,BI=0,target=f'{start+20:08x}')
    for pc,offset,index,target in ((0x8002d164,-21340,23,'8002cff0'),(0x8002d178,-21338,24,'8002cfac')):
        check(pc,'lhz',rD=0,rA=13,displacement=offset)
        check(pc+4,'cmp',rA=index,rB=0)
        check(pc+8,'bc',BO=12,BI=0,target=target)
    check(0x8002d080,'bl',target='8003a05c')
    return dict(count_sites=['8002d178','8002d164'],height_order=['HIT68','HIT88','owner3e4','fsubs68minus88','store'],
                pair_pointer_order=['inner HIT','fresh outer owner20','inner owner20'],
                copy_pairs=45,copy_order=['lwz','lwzu','stw','stwu'],first_helper_site='8002d080')
def range_evidence(db,mapping,address,width):
    c.require(type(address)is type(width)is int and(address,width)==RANGE,'unselected range')
    prior.normal.require_mapping(mapping,prior.TEXT_MAPPING)
    raw,spans=db.chain(mapping[-1],address-mapping[0],width,mapping[-2])
    c.require(len(raw)==width and hashlib.sha256(raw).hexdigest()==prior.RANGES[0][2],'code width/digest mismatch')
    rows=[]
    for i in range(0,width,4):
        r=prior.decode_selected(c.integer(raw,i,'I'),address+i)
        c.require(r is not None,'decoder gap');rows.append(dict(address=f'{address+i:08x}',**r))
    c.require(prior.semantic_digest(rows)==prior.OPERAND_DIGESTS[address],'operand mismatch')
    flow=[r for r in rows if r['mnemonic']in('b','bc','bl','blr','bctrl')]
    c.require((len(flow),prior.semantic_digest(flow))==prior.FLOW_DIGESTS[address],'flow mismatch')
    c.require(tuple((r['address'],r['target'])for r in rows if r['mnemonic']=='bl')==prior.CALLS[address],'calls mismatch')
    return dict(address=f'{address:08x}',width=width,sha256=prior.RANGES[0][2],
        represented_instructions=len(rows),unrepresented_instructions=0,
        operand_sha256=prior.OPERAND_DIGESTS[address],flow_sha256=prior.FLOW_DIGESTS[address][1],
        semantics=summarize_prefix(rows),spans=spans)
def constant_evidence(db,address,width=4):
    c.require(type(address)is type(width)is int and(address,width)==(CONSTANT,4),'unselected constant')
    raw,spans=db.chain(263,CONSTANT-DATA_MAPPING[0],4,27360)
    c.require(len(raw)==4 and raw.hex()=='c61c4000','constant width/bits mismatch')
    return dict(address='80436f6c',width=4,bits='c61c4000',value=struct.unpack('>f',raw)[0],spans=spans)
def inspect(data,digest):
    auth=c.inspect(data,digest)
    db=c.GBF(data);tables=db.tables()
    blocks,subs=db.rows(tables['Memory Blocks']),db.rows(tables['Sub Memory Blocks'])
    image=int(auth['image_offset'],16);prior.command.mappings(blocks,subs,image)
    text,_=prior.normal.mapping_evidence(blocks,subs,image,prior.TEXT_MAPPING)
    c.require(c.data5_mapping(blocks,subs,image)==DATA_MAPPING,'data mapping mismatch')
    return dict(snapshot_sha256=auth['snapshot_sha256'],
        ranges=[range_evidence(db,text,*RANGE)],constants=[constant_evidence(db,CONSTANT)],
        selection=dict(code_bytes=536,data_bytes=4,transitive=False),original_execution=False)
if __name__=='__main__':
    import argparse
    from pathlib import Path
    p=argparse.ArgumentParser();p.add_argument('snapshot',type=Path);args=p.parse_args()
    c.require(args.snapshot.is_file()and args.snapshot.stat().st_size<=c.MAX_FILE,'snapshot bounds')
    with args.snapshot.open('rb')as f:data=f.read(c.MAX_FILE+1)
    c.require(len(data)<=c.MAX_FILE,'snapshot bounds')
    print(json.dumps(inspect(data,hashlib.sha256(data).hexdigest()),indent=2))
