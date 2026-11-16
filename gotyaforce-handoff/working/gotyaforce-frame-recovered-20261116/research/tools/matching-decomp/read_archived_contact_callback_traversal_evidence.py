#!/usr/bin/env python3
"""Exactly276 bytes of89aec traversal; no callback bodies or source data selected.

Unchanged existing authentication/decoder. Never outputs bytes or a full listing.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_object_scheduler_evidence as base
c, command, normal = base.c, base.command, base.normal
TEXT_MAPPING = base.TEXT_MAPPING
RANGE=(0x80089aec,276,'03e4a562cd8742937f8f85f602f0f3a3a682457f8f5887accc0b15cbf24f4802')
OPERAND_SHA256='c0f0a39c2f531c9e6674dc7141dc7f3db75b73f69bf6be6ac8bf71c77611f4b0'
FLOW=(15,'b258d92e616402a97bfba8c360951c6b3bff27e732ffb3ed3415d52b028e70d3')
CALL_SITES=('80089b30','80089b84','80089bd0')


def semantic_digest(rows):return hashlib.sha256(json.dumps(rows,sort_keys=True,separators=(',',':')).encode()).hexdigest()


def summarize(rows):
    c.require(len(rows)==69,'instruction count')
    c.require([r['address']for r in rows if r['mnemonic']=='bctrl']==list(CALL_SITES),'indirect call schedule')
    c.require(not any(r['mnemonic']=='bl'for r in rows),'unexpected direct helper')
    c.require(rows[-1]==dict(address='80089bfc',mnemonic='blr',BO=20,BI=0,BH=0,LK=0),'terminal return')
    # Independent linear constant propagation identifies global base loads; no
    # runtime pointer follows or hypothetical original memory values are used.
    known={};loads={};by_pc={r['address']:r for r in rows}
    for r in rows:
        n=r['mnemonic']
        if n in ('addi','addis'):
            base_value=0 if r['rA']==0 else known.get(r['rA'])
            if base_value is None:known.pop(r['rD'],None)
            else:known[r['rD']]=(base_value+(r['immediate']<<(16 if n=='addis'else 0)))&0xffffffff
        elif n in ('lwz','lbz'):
            if r['rA']in known:loads[r['address']]=(known[r['rA']]+r['displacement'])&0xffffffff
            known.pop(r['rD'],None)
    expected={'80089b10':0x803c712c,'80089b54':0x803c4e84,'80089b64':0x803c7130,'80089bb0':0x803c7148}
    c.require(loads==expected,'global head/slot base addresses')
    cmp=by_pc['80089b9c'];c.require(cmp['mnemonic']=='cmpi'and cmp['rA']==28 and cmp['immediate']==6,'six actor loop bound')
    # There is no callback==0 branch: each active arm loads+c, moves the same
    # current node to r3, mtctr, then bctrl. The next8 load follows that call.
    for active,callback,site,next_pc in [('80089b18','80089b24','80089b30','80089b34'),('80089b6c','80089b78','80089b84','80089b88'),('80089bb8','80089bc4','80089bd0','80089bd4')]:
        a,b,n=by_pc[active],by_pc[callback],by_pc[next_pc]
        c.require(a['mnemonic']=='lbz'and a['displacement']==0,'active byte load')
        c.require(b['mnemonic']=='lwz'and b['displacement']==12 and b['rA']==a['rA'],'same-node callback load')
        c.require(n['mnemonic']=='lwz'and n['displacement']==8 and n['rA']==a['rA'],'same-node next load after call')
        middle=[r['mnemonic']for r in rows if int(callback,16)<int(r['address'],16)<int(site,16)]
        c.require(middle==['or','mtctr'],'no null callback shortcut')
    return dict(first_group=48,slot_groups=list(range(49,55)),last_group=55,
                actor_slots=6,callback_sites=list(CALL_SITES),active_callback_unconditional=True,
                node_active_offset=0,node_callback_offset=12,next_offset=8,
                pause_mask_read=False,source_snapshot_stores=False,
                callback_bodies_selected=False)


def range_evidence(db,mapping,address,width):
    c.require(type(address)is type(width)is int,'range integer fields')
    c.require((address,width)==RANGE[:2],'range not allowlisted')
    normal.require_mapping(mapping,TEXT_MAPPING)
    raw,spans=db.chain(mapping[-1],address-mapping[0],width,mapping[-2])
    c.require(len(raw)==width and hashlib.sha256(raw).hexdigest()==RANGE[2],'range digest/width mismatch')
    rows=[]
    for offset in range(0,width,4):
        pc=address+offset;r=base.decode_selected(c.integer(raw,offset,'I'),pc)
        c.require(r is not None,'unrepresented instruction');rows.append(dict(address=f'{pc:08x}',**r))
    c.require(semantic_digest(rows)==OPERAND_SHA256,'operand digest mismatch')
    flow=[r for r in rows if r['mnemonic']in('b','bc','bl','blr','bctrl')]
    c.require((len(flow),semantic_digest(flow))==FLOW,'control flow mismatch')
    c.require(all(address<=int(r['target'],16)<address+width for r in flow if r['mnemonic']in('b','bc')),'branch outside routine')
    return dict(address=f'{address:08x}',width=width,sha256=RANGE[2],operand_sha256=OPERAND_SHA256,
                represented_instructions=len(rows),unrepresented_instructions=0,semantics=summarize(rows),spans=spans)


def inspect(data,digest):
    auth=c.inspect(data,digest);db=c.GBF(data);tables=db.tables()
    blocks,subs=db.rows(tables['Memory Blocks']),db.rows(tables['Sub Memory Blocks']);image=int(auth['image_offset'],16)
    command.mappings(blocks,subs,image);mapping,fact=normal.mapping_evidence(blocks,subs,image,TEXT_MAPPING)
    return dict(snapshot=auth['snapshot'],snapshot_sha256=auth['snapshot_sha256'],mappings=[fact],
                ranges=[range_evidence(db,mapping,*RANGE[:2])],
                selection=dict(reads=1,bytes=276,data_cells=0,helpers_read=False,pointer_following=False,raw_or_operand_listing_output=False),
                caveat='Archived static evidence only. No original execution, callback body verification, live lists or completed normal battle frame.')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('snapshot',type=Path);args=parser.parse_args()
    try:
        c.require(args.snapshot.is_file()and 32<=args.snapshot.stat().st_size<=c.MAX_FILE,'snapshot bounds')
        with args.snapshot.open('rb')as stream:data=stream.read(c.MAX_FILE+1)
        c.require(len(data)<=c.MAX_FILE,'snapshot exceeds bounds')
        print(json.dumps(inspect(data,hashlib.sha256(data).hexdigest()),indent=2,allow_nan=False))
    except(OSError,c.FormatError)as error:
        print(json.dumps({'error':str(error)}),file=sys.stderr);return 1
    return 0
if __name__=='__main__':sys.exit(main())
