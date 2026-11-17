#!/usr/bin/env python3
"""Fixed112-byte3a05c index extent only. No callees/data/listing output."""
import hashlib
import json
import read_archived_target_action_frame_evidence as base
c=base.c
RANGE=(0x8003a05c,112)
SHA='d578f446b921fc1cdcbc86d06d110733fa73ebcd78a9c60938a31aa9179631d2'
OPERAND='3d2d8aeb29c0b8efa52d5982a6475c97f389c61e1418f1d9ef7837a5bfa346d9'
FLOW=(6,'8408e74cd0b2e933d2aea415dad4f4886ae13893d4ac967f48f0fbe83b1335a9')
def summarize_vector_add(rows):
    """Derived existing8020ba54 schedule; not read by this reader's inspect."""
    c.require(len(rows)==9,'vector instruction count')
    for i,name,reg,base_register,offset,w in ((0,'psq_l',2,3,0,0),(1,'psq_l',4,4,0,0),
        (3,'psq_st',6,5,0,0),(4,'psq_l',3,3,8,1),(5,'psq_l',5,4,8,1),(7,'psq_st',7,5,8,1)):
        r=rows[i];key='fD'if name=='psq_l'else'fS'
        c.require(r['mnemonic']==name and r[key]==reg and(r['rA'],r['displacement'],r['W'],r['I'])==
                  (base_register,offset,w,0),'vector paired access schedule')
    for i,d,a,b in ((2,6,2,4),(6,7,3,5)):
        r=rows[i];c.require(r['mnemonic']=='ps_add'and(r['fD'],r['fA'],r['fB'],r['Rc'])==(d,a,b,0),'vector add schedule')
    c.require(rows[8]['mnemonic']=='blr','vector return')
    return dict(pair_store_before_z_loads=True,gqr=0,xy_width=2,z_width=1)
def summarize_post_adjust(rows):
    by={int(r['address'],16):r for r in rows}
    def check(pc,name,**fields):
        r=by[pc];c.require(r['mnemonic']==name and all(r.get(k)==v for k,v in fields.items()),'post adjust order')
    check(0x8002d084,'lbz',rA=26,displacement=0x83,rD=0)
    check(0x8002d088,'extsb',rS=0,rA=0,Rc=1)
    check(0x8002d08c,'bc',BO=4,BI=2,target='8002d0bc')
    check(0x8002d094,'lbz',rA=26,displacement=0x3e4,rD=0)
    check(0x8002d0a0,'lfs',rA=4,displacement=0x10,fD=1)
    check(0x8002d0a4,'extsb',rS=0,rA=0,Rc=0)
    check(0x8002d0a8,'lfs',rA=4,displacement=0x30,fD=0)
    check(0x8002d0ac,'rlwinm',rS=0,rA=0,SH=2,MB=0,ME=29)
    check(0x8002d0b4,'fsubs',fD=0,fA=1,fB=0)
    check(0x8002d0b8,'stfsx',fS=0,rA=3,rB=0)
    check(0x8002d0cc,'bl',target='80039f6c')
    return dict(order=['fresh owner83','owner3e4','scratch10','scratch30','subtract','store'],next_helper='80039f6c')
def summarize(rows):
    by={int(r['address'],16):r for r in rows}
    def check(pc,name,**fields):
        r=by[pc];c.require(r['mnemonic']==name and all(r.get(k)==v for k,v in fields.items()),'adjust source order')
    check(0x8003a06c,'or',rS=6,rA=31,rB=6,Rc=0)
    check(0x8003a074,'or',rS=4,rA=30,rB=4,Rc=0)
    for pc,owner,scratch,target in ((0x8003a078,5,3,'8003a094'),(0x8003a094,31,30,'8003a0b0')):
        check(pc,'lbz',rD=0,rA=owner,displacement=0x1dd)
        check(pc+4,'extsb',rS=0,rA=0,Rc=1)
        check(pc+8,'bc',BO=12,BI=2,target=target)
        check(pc+12,'addi',rD=4,rA=scratch,immediate=12)
        check(pc+16,'addi',rD=3,rA=owner,immediate=0x1cc)
        check(pc+20,'or',rS=4,rA=5,rB=4,Rc=0)
        check(pc+24,'bl',target='8020ba54')
    check(0x8003a0c4,'blr',BO=20,BI=0,BH=0,LK=0)
    check(0x8003a0c8,'blr',BO=20,BI=0,BH=0,LK=0)
    return dict(flag_offset=0x1dd,signed=True,owner_order=['entry_r5','entry_r6'],
        call_sites=['8003a090','8003a0ac'],callee='8020ba54',
        call_arguments=['owner+1cc','scratch+0c','scratch+0c'],
        zero_flags_return=True,reachable_return='8003a0c4',trailing_return='8003a0c8')
def range_evidence(db,mapping,address,width):
    c.require(type(address)is type(width)is int and(address,width)==RANGE,'unselected range')
    base.normal.require_mapping(mapping,base.TEXT_MAPPING)
    raw,spans=db.chain(mapping[-1],address-mapping[0],width,mapping[-2])
    c.require(len(raw)==width and hashlib.sha256(raw).hexdigest()==SHA,'code width/digest mismatch')
    rows=[]
    for i in range(0,width,4):
        r=base.decode_selected(c.integer(raw,i,'I'),address+i)
        c.require(r is not None,'decoder gap');rows.append(dict(address=f'{address+i:08x}',**r))
    c.require(base.semantic_digest(rows)==OPERAND,'operand mismatch')
    flow=[r for r in rows if r['mnemonic']in('b','bc','bl','blr','bctrl')]
    c.require((len(flow),base.semantic_digest(flow))==FLOW,'flow mismatch')
    c.require(tuple((r['address'],r['target'])for r in rows if r['mnemonic']=='bl')==
        (('8003a090','8020ba54'),('8003a0ac','8020ba54')),'call schedule')
    return dict(address=f'{address:08x}',width=width,sha256=SHA,operand_sha256=OPERAND,
        flow_sha256=FLOW[1],represented_instructions=len(rows),unrepresented_instructions=0,
        semantics=summarize(rows),spans=spans)
def inspect(data,digest):
    auth=c.inspect(data,digest);db=c.GBF(data);t=db.tables()
    b,s=db.rows(t['Memory Blocks']),db.rows(t['Sub Memory Blocks']);im=int(auth['image_offset'],16)
    base.command.mappings(b,s,im);m,_=base.normal.mapping_evidence(b,s,im,base.TEXT_MAPPING)
    return dict(snapshot_sha256=auth['snapshot_sha256'],ranges=[range_evidence(db,m,*RANGE)],
        selection=dict(code_bytes=112,data_bytes=0,transitive=False),original_execution=False,
        reused_evidence=[dict(address='8020ba54',width=36,source='read_archived_double_action_evidence.py',read_here=False),
                         dict(address='8002cf80',width=536,source='read_archived_initial_contact_evidence.py',read_here=False)])
if __name__=='__main__':
    import argparse
    from pathlib import Path
    p=argparse.ArgumentParser();p.add_argument('snapshot',type=Path);args=p.parse_args()
    c.require(args.snapshot.is_file()and args.snapshot.stat().st_size<=c.MAX_FILE,'snapshot bounds')
    with args.snapshot.open('rb')as f:data=f.read(c.MAX_FILE+1)
    c.require(len(data)<=c.MAX_FILE,'snapshot bounds')
    print(json.dumps(inspect(data,hashlib.sha256(data).hexdigest()),indent=2))
