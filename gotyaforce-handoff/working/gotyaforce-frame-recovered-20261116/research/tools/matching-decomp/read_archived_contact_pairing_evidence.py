#!/usr/bin/env python3
"""Exactly existing560-byte2d35c selection, no data or transitive selection."""
import hashlib
import json
import read_archived_initial_contact_evidence as prior
c=prior.c
RANGE=(0x8002d35c,560)
SHA=next(x[2]for x in prior.RANGES if x[:2]==RANGE)
def summarize(rows):
    by={int(r['address'],16):r for r in rows}
    def check(pc,name,**fields):
        r=by[pc];c.require(r['mnemonic']==name and all(r.get(k)==v for k,v in fields.items()),'pairing source order')
    check(0x8002d364,'addis',rD=3,rA=0,immediate=-32708)
    check(0x8002d36c,'addi',rD=0,rA=3,immediate=0x3b7c)
    for pc,reg in ((0x8002d554,0),(0x8002d568,3)):
        check(pc,'lhz',rD=reg,rA=13,displacement=-21332)
    check(0x8002d56c,'addi',rD=0,rA=3,immediate=-1)
    check(0x8002d570,'cmp',rA=25,rB=0)
    check(0x8002d574,'bc',BO=12,BI=0,target='8002d380')
    check(0x8002d3b0,'addi',rD=5,rA=25,immediate=1)
    check(0x8002d3b8,'rlwinm',rS=5,rA=4,SH=2,MB=0,ME=29)
    check(0x8002d3c0,'or',rS=5,rA=24,rB=5)
    check(0x8002d558,'cmp',rA=24,rB=0)
    check(0x8002d55c,'bc',BO=12,BI=0,target='8002d3cc')
    for pc,name,d,owner,off in ((0x8002d380,'lwz',29,31,0),(0x8002d384,'lwz',3,29,0x28),
        (0x8002d388,'lhz',0,3,2),(0x8002d394,'lwz',27,29,0x20),
        (0x8002d398,'lbz',0,27,0x281),(0x8002d3a4,'lbz',0,27,0x83),
        (0x8002d3cc,'lwz',28,30,0),(0x8002d3d0,'lwz',0,29,0x20),
        (0x8002d3d4,'lwz',4,28,0x20),(0x8002d3e0,'lwz',3,28,0x28),
        (0x8002d3e4,'lhz',0,3,2),(0x8002d3f0,'lbz',0,4,0x281),
        (0x8002d400,'lbz',0,4,0x83)):
        check(pc,name,rD=d,rA=owner,displacement=off)
    for pc,target in ((0x8002d38c,'8002d560'),(0x8002d3e8,'8002d54c')):
        check(pc,'rlwinm',rS=0,rA=0,SH=0,MB=20,ME=20,Rc=1)
        check(pc+4,'bc',BO=4,BI=2,target=target)
    for pc,target in ((0x8002d39c,'8002d560'),(0x8002d3f8,'8002d54c')):
        check(pc,'extsb',rS=0,rA=0,Rc=1);check(pc+4,'bc',BO=4,BI=2,target=target)
    for pc,target in ((0x8002d3a8,'8002d560'),(0x8002d404,'8002d54c')):
        check(pc,'cmpi',rA=0,immediate=23);check(pc+4,'bc',BO=12,BI=2,target=target)
    for pc,first in ((0x8002d3d8,0),(0x8002d40c,27)):
        check(pc,'cmpl',rA=first,rB=4);check(pc+4,'bc',BO=12,BI=2,target='8002d54c')
    for pc,owner,hit,skip in ((0x8002d414,27,28,'8002d42c'),(0x8002d42c,26,29,'8002d444')):
        check(pc,'lbz',rD=0,rA=owner,displacement=0x1db)
        check(pc+4,'extsb',rS=0,rA=0,Rc=1)
        check(pc+8,'bc',BO=12,BI=2,target=skip)
        check(pc+12,'lwz',rD=0,rA=owner,displacement=0x1e0)
        check(pc+16,'cmpl',rA=0,rB=hit)
        check(pc+20,'bc',BO=12,BI=2,target='8002d54c')
    for pc,source,dst in ((0x8002d448,29,0x4d0),(0x8002d474,28,0x368)):
        check(pc,'addi',rD=0,rA=0,immediate=45)
        check(pc+4,'addi',rD=3,rA=3,immediate=dst)
        check(pc+8,'addi',rD=4,rA=source,immediate=0x54)
        check(pc+12,'addi',rD=5,rA=3,immediate=-4)
        check(pc+16,'mtctr',rS=0)
        for off,name,reg,base,disp in ((20,'lwz',3,4,4),(24,'lwzu',0,4,8),(28,'stw',3,5,4),(32,'stwu',0,5,8)):
            check(pc+off,name,**{'rD'if name.startswith('l')else'rS':reg},rA=base,displacement=disp)
        check(pc+36,'bc',BO=16,BI=0,target=f'{pc+20:08x}')
    for pc,target in ((0x8002d4b4,'8003a05c'),(0x8002d4c8,'80039f6c'),(0x8002d4ec,'80030348')):
        check(pc,'bl',target=target)
    check(0x8002d4cc,'cmpi',rA=3,immediate=0)
    check(0x8002d4d0,'bc',BO=12,BI=2,target='8002d54c')
    check(0x8002d4dc,'lwz',rD=5,rA=29,displacement=0x58)
    check(0x8002d4e4,'lwz',rD=6,rA=28,displacement=0x58)
    return dict(table='803c3b7c',counter='8043624c',fresh_counter=True,outer='i<count-1',inner='j=i+1;j<count',
        descriptor_skip_mask=0x800,owner281_signed=True,owner83_unsigned_equal=23,
        support_pointer_compares_hit=True,copy_pairs=45,positive_boundary='8002d4ec')
def range_evidence(db,mapping,address,width):
    c.require(type(address)is type(width)is int and(address,width)==RANGE,'unselected range')
    prior.normal.require_mapping(mapping,prior.TEXT_MAPPING)
    raw,spans=db.chain(mapping[-1],address-mapping[0],width,mapping[-2])
    c.require(len(raw)==width and hashlib.sha256(raw).hexdigest()==SHA,'code digest mismatch')
    rows=[]
    for i in range(0,width,4):
        r=prior.decode_selected(c.integer(raw,i,'I'),address+i)
        c.require(r is not None,'decoder gap');rows.append(dict(address=f'{address+i:08x}',**r))
    c.require(prior.semantic_digest(rows)==prior.OPERAND_DIGESTS[address],'operand mismatch')
    flow=[r for r in rows if r['mnemonic']in('b','bc','bl','blr','bctrl')]
    c.require((len(flow),prior.semantic_digest(flow))==prior.FLOW_DIGESTS[address],'flow mismatch')
    return dict(address=f'{address:08x}',width=width,sha256=SHA,operand_sha256=prior.OPERAND_DIGESTS[address],
        represented_instructions=len(rows),semantics=summarize(rows),spans=spans)
def inspect(data,digest):
    auth=c.inspect(data,digest);db=c.GBF(data);t=db.tables()
    b,s=db.rows(t['Memory Blocks']),db.rows(t['Sub Memory Blocks']);im=int(auth['image_offset'],16)
    prior.command.mappings(b,s,im);m,_=prior.normal.mapping_evidence(b,s,im,prior.TEXT_MAPPING)
    return dict(snapshot_sha256=auth['snapshot_sha256'],ranges=[range_evidence(db,m,*RANGE)],
        selection=dict(code_bytes=560,data_bytes=0,transitive=False),original_execution=False,
        caller_order=dict(address='8002bb14',calls=['8002cf80','8002d35c','8002d58c'],read_here=False))
