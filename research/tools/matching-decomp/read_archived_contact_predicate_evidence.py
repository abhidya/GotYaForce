#!/usr/bin/env python3
"""Fixed240-byte39f6c index extent only. No callees/listing output; exactly three authorized constant cells."""
import read_archived_terrain_orientation_evidence as terrain
import read_archived_angular_finite_evidence as angular
import struct
import hashlib
import json
import read_archived_target_action_frame_evidence as base
c=base.c
RANGE=(0x80039f6c,240)
SHA='ea15e86d0428a669821b13e9d6131da6e5c4947d84970604cea6527186912e23'
OPERAND='718c4ff5ee30c90fc83e2adf53170525265212badbbd7844a0c0d56812ee4cbc'
FLOW=(9,'6f9a3f299632b57de188bac26a70209896f7989d759d9948a0e116773888a67f')
def decode_selected(w,pc):
    r=base.decode_selected(w,pc)
    if r is None:r=terrain.decode_selected(w,pc)
    if r is None:r=angular.decode_selected(w,pc)
    return r
def summarize(rows):
    by={int(r['address'],16):r for r in rows}
    def check(pc,name,**fields):
        r=by[pc];c.require(r['mnemonic']==name and all(r.get(k)==v for k,v in fields.items()),'predicate source order')
    for pc,name,reg,owner,off in ((0x80039f74,'lfs',1,2,-31260),(0x80039f8c,'lfs',0,3,36),
        (0x80039fa4,'lfs',0,31,36),(0x80039fc8,'lfs',0,2,-31416),
        (0x80039fd8,'lfd',4,2,-31312),(0x80039fdc,'lfd',3,2,-31304),
        (0x8003a020,'lfs',2,30,36),(0x8003a024,'lfs',0,31,36)):
        check(pc,name,fD=reg,rA=owner,displacement=off)
    for pc,target in ((0x80039f90,'80039fa4'),(0x80039fa8,'80039fbc'),(0x8003a02c,'8003a040')):
        check(pc,'fcmpo',BF=0,fA=1 if pc==0x8003a02c else 0,fB=0 if pc==0x8003a02c else 1)
        check(pc+4,'cror',BT=2,BA=0,BB=2)
        check(pc+8,'bc',BO=4,BI=2,target=target)
    check(0x80039fbc,'addi',rD=3,rA=30,immediate=12)
    check(0x80039fc0,'addi',rD=4,rA=31,immediate=12)
    check(0x80039fc4,'bl',target='8020bc88')
    check(0x80039fd0,'bc',BO=4,BI=1,target='8003a020')
    check(0x80039fd4,'frsqrte',fD=2,fB=1)
    for pc in (0x80039fe8,0x80039ff8,0x8003a008):check(pc,'fnmsub',fD=0,fA=1,fC=0,fB=3)
    for start,last in ((0x80039fe0,2),(0x80039ff0,2),(0x8003a000,0)):
        check(start,'fmul',fD=0,fA=2,fC=2)
        check(start+4,'fmul',fD=2,fA=4,fC=2)
        check(start+12,'fmul',fD=last,fA=2,fC=0)
    check(0x8003a010,'fmul',fD=0,fA=1,fC=0)
    check(0x8003a014,'frsp',fD=0,fB=0)
    check(0x8003a028,'fadds',fD=0,fA=2,fB=0)
    for pc,v in ((0x80039f9c,0),(0x80039fb4,0),(0x8003a038,1),(0x8003a040,0)):
        check(pc,'addi',rD=3,rA=0,immediate=v)
    check(0x8003a058,'blr',BO=20,BI=0,BH=0,LK=0)
    return dict(radius_offset=36,vector_offset=12,early_zero_order=['first','second'],
        constant_r2_offsets=[-31260,-31416,-31312,-31304],constant_values_selected=True,
        refinement_steps=3,reload_radii=True,final_inclusive_compare=True)
def range_evidence(db,mapping,address,width):
    c.require(type(address)is type(width)is int and(address,width)==RANGE,'unselected range')
    base.normal.require_mapping(mapping,base.TEXT_MAPPING)
    raw,spans=db.chain(mapping[-1],address-mapping[0],width,mapping[-2])
    c.require(len(raw)==width and hashlib.sha256(raw).hexdigest()==SHA,'code width/digest mismatch')
    rows=[]
    for i in range(0,width,4):
        r=decode_selected(c.integer(raw,i,'I'),address+i)
        c.require(r is not None,'decoder gap');rows.append(dict(address=f'{address+i:08x}',**r))
    c.require(base.semantic_digest(rows)==OPERAND,'operand mismatch')
    flow=[r for r in rows if r['mnemonic']in('b','bc','bl','blr','bctrl')]
    c.require((len(flow),base.semantic_digest(flow))==FLOW,'flow mismatch')
    c.require(tuple((r['address'],r['target'])for r in rows if r['mnemonic']=='bl')==
        (('80039fc4','8020bc88'),),'call schedule')
    return dict(address=f'{address:08x}',width=width,sha256=SHA,operand_sha256=OPERAND,
        flow_sha256=FLOW[1],represented_instructions=len(rows),unrepresented_instructions=0,
        semantics=summarize(rows),spans=spans)
CELLS=((0x80437004,4,'3dcccccd'),(0x80436fd0,8,'3fe0000000000000'),(0x80436fd8,8,'4008000000000000'))
def cell_evidence(db,address,width):
    c.require(type(address)is type(width)is int,'cell integer fields')
    selected=[x for x in CELLS if x[:2]==(address,width)]
    c.require(len(selected)==1,'unselected cell')
    raw,spans=db.chain(263,address-0x80436a20,width,27360)
    c.require(len(raw)==width and raw.hex()==selected[0][2],'cell bits mismatch')
    return dict(address=f'{address:08x}',width=width,bits=raw.hex(),value=struct.unpack('>f'if width==4 else '>d',raw)[0],spans=spans)
def inspect(data,digest):
    auth=c.inspect(data,digest);db=c.GBF(data);t=db.tables()
    b,s=db.rows(t['Memory Blocks']),db.rows(t['Sub Memory Blocks']);im=int(auth['image_offset'],16)
    base.command.mappings(b,s,im);m,_=base.normal.mapping_evidence(b,s,im,base.TEXT_MAPPING)
    c.require(c.data5_mapping(b,s,im)==(0x80436a20,0x8043d500,7,'MAIN_.data5',7,27360,263),'data mapping mismatch')
    return dict(snapshot_sha256=auth['snapshot_sha256'],ranges=[range_evidence(db,m,*RANGE)],
        cells=[cell_evidence(db,pc,width)for pc,width,_ in CELLS],
        reused_evidence=[dict(address='80436f68',read_here=False),dict(address='8020bc88',read_here=False)],
        selection=dict(code_bytes=240,data_bytes=20,transitive=False),original_execution=False)
if __name__=='__main__':
    import argparse
    from pathlib import Path
    p=argparse.ArgumentParser();p.add_argument('snapshot',type=Path);args=p.parse_args()
    c.require(args.snapshot.is_file()and args.snapshot.stat().st_size<=c.MAX_FILE,'snapshot bounds')
    with args.snapshot.open('rb')as f:data=f.read(c.MAX_FILE+1)
    c.require(len(data)<=c.MAX_FILE,'snapshot bounds')
    print(json.dumps(inspect(data,hashlib.sha256(data).hexdigest()),indent=2))
