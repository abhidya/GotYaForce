#!/usr/bin/env python3
"""Exactly996 bytes of8a65c contact callback; no callees or source data selected.

Unchanged existing authentication/decoder. Never outputs bytes or a full listing.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import read_archived_target_action_frame_evidence as base
import read_archived_double_action_evidence as double
import read_archived_frame_continuation_evidence as continuation
c, command, normal = base.c, base.command, base.normal
TEXT_MAPPING = base.TEXT_MAPPING
RANGE=(0x8008a65c,996,'92fa6953e7aea5fe06460450ea539bf738406dc0632251b89ccba4c973b3adf4')
OPERAND_SHA256='243ca13099eae02b8b7c3b3a64fe8f2a674fdae6292d0e61810f24a1746ce438'
FLOW=(68,'5a30f1b32e1c73bb64d4fa21565813e099059a2cf7cf106c70eacb7510526ecc')
CALLS=(('8008a69c', '80088e50'), ('8008a6e0', '80088e50'), ('8008a728', '8020b7a8'), ('8008a81c', '8008a5d0'), ('8008a830', '8008a5d0'), ('8008a84c', '8008aa40'), ('8008a85c', '8008a2bc'), ('8008a888', '8020b7a8'), ('8008a8c4', '80088e50'), ('8008a8e4', '80088e50'), ('8008a954', '8008b480'), ('8008a960', '8008b480'), ('8008a974', '8008b290'), ('8008a9ac', '8008a5d0'), ('8008a9dc', '8008aa40'), ('8008a9ec', '8008a2bc'), ('8008aa0c', '8008aa40'), ('8008aa1c', '8008a2bc'))
INDIRECT_CALLS=('8008a7b8','8008a908')


def semantic_digest(rows):return hashlib.sha256(json.dumps(rows,sort_keys=True,separators=(',',':')).encode()).hexdigest()


def decode_selected(word,pc):
    c.require(type(word)is int and 0<=word<=0xffffffff,'word bounds')
    c.require(type(pc)is int and 0<=pc<=0xfffffffc and pc%4==0,'PC bounds')
    if word>>26==63 and (word>>1)&1023==15:return double.decode_selected(word,pc)
    if word==0x4e800421:return continuation.decode_selected(word,pc)
    return base.decode_selected(word,pc)


def summarize(rows):
    c.require(len(rows)==249,'instruction count')
    c.require(tuple((r['address'],r['target'])for r in rows if r['mnemonic']=='bl')==CALLS,'direct call schedule')
    c.require(tuple(r['address']for r in rows if r['mnemonic']=='bctrl')==INDIRECT_CALLS,'indirect call schedule')
    c.require(rows[-1]==dict(address='8008aa3c',mnemonic='blr',BO=20,BI=0,BH=0,LK=0),'terminal return')
    by_pc={int(r['address'],16):r for r in rows}
    def memory(pc,name,base,offset,reg):
        r=by_pc[pc];register='rS'if name in('stw','stb','sth')else'rD'
        c.require(r['mnemonic']==name and r['rA']==base and r['displacement']==offset and r[register]==reg,'prefix memory schedule')
    # A narrow derived load/store schedule, not a full original instruction fixture.
    for args in ((0x8008a67c,'lwz',3,0x20,30),(0x8008a680,'lbz',30,0x1d8,0),
                 (0x8008a68c,'lbz',30,0,0),(0x8008a6a4,'lbz',30,0x83,0),
                 (0x8008a6b0,'lha',29,0x4a,0),(0x8008a6bc,'lbz',30,0x1cec,0),
                 (0x8008a6c0,'lbz',30,0x1ced,4),(0x8008a6c8,'lha',29,0x4c,5),
                 (0x8008a6ec,'stb',29,0x13,0),(0x8008a6f0,'lbz',29,0x10,0),
                 (0x8008a6f4,'lwz',29,0x28,31),(0x8008a71c,'lwz',29,0x60,3),
                 (0x8008a72c,'lwz',29,0x30,3),(0x8008a730,'lwz',29,0x34,0),
                 (0x8008a734,'stw',29,0x3c,3),(0x8008a738,'stw',29,0x40,0),
                 (0x8008a73c,'lwz',29,0x38,0),(0x8008a740,'stw',29,0x44,0),
                 (0x8008a744,'lha',29,0x48,3),(0x8008a88c,'lha',29,0x4a,3),
                 (0x8008a864,'lwz',29,0x30,3),(0x8008a86c,'lwz',29,0x34,0),
                 (0x8008a874,'stw',29,0x3c,3),(0x8008a878,'stw',29,0x40,0),
                 (0x8008a87c,'lwz',29,0x38,0),(0x8008a880,'stw',29,0x44,0),
                 (0x8008a884,'lwz',29,0x60,3),(0x8008a9f4,'lbz',30,0x281,0),
                 (0x8008aa04,'stb',29,0x10,0)):
        memory(*args)
    # Both calls consume the descriptor retained in r31, not a fresh HIT28 load.
    # These address computations do not dereference or select any descriptor data.
    for pc,destination,base_register,offset in ((0x8008a720,4,31,0x0c),
                                               (0x8008a724,5,29,0x30),
                                               (0x8008a868,4,31,0x0c),
                                               (0x8008a870,5,29,0x30)):
        r=by_pc[pc]
        c.require(r['mnemonic']=='addi'and (r['rD'],r['rA'],r['immediate'])==
                  (destination,base_register,offset),'transform argument provenance')
    state=by_pc[0x8008a6f0];c.require(state['mnemonic']=='lbz','unsigned state byte')
    cmp=by_pc[0x8008a710];branch=by_pc[0x8008a714]
    c.require(cmp['mnemonic']=='cmpi'and cmp['rA']==0 and cmp['immediate']==3,'state upper branch')
    c.require(branch['mnemonic']=='bc'and branch['BO']==4 and branch['BI']==0 and branch['target']=='8008aa20','state>=3 real return')
    c.require(by_pc[0x8008a6e8]['mnemonic']=='addi'and by_pc[0x8008a6e8]['immediate']==0,'literal zero before13 store')
    c.require(by_pc[0x8008aa00]['mnemonic']=='addi'and by_pc[0x8008aa00]['immediate']==1,'literal one before state2 store')
    for pc,reg in ((0x8008a6c4,0),(0x8008a6cc,4)):
        r=by_pc[pc];c.require(r['mnemonic']=='extsb'and r['rS']==reg and r['rA']==reg and r['Rc']==0,'signed group/action bytes')
    shift=by_pc[0x8008a6d0];add=by_pc[0x8008a6d4];compare=by_pc[0x8008a6d8]
    c.require(shift['mnemonic']=='rlwinm'and (shift['rS'],shift['rA'],shift['SH'],shift['MB'],shift['ME'])==(0,0,12,0,19),'group shift twelve')
    c.require(add['mnemonic']=='add'and (add['rD'],add['rA'],add['rB'])==(0,4,0),'group plus action')
    c.require(compare['mnemonic']=='cmp'and (compare['rA'],compare['rB'])==(5,0),'signed saved action compare')
    flag=by_pc[0x8008a9f8];skip=by_pc[0x8008a9fc]
    c.require(flag['mnemonic']=='extsb'and flag['Rc']==1,'mode2 owner flag zero test')
    c.require(skip['mnemonic']=='bc'and (skip['BO'],skip['BI'],skip['target'])==(4,2,'8008aa08'),'mode2 nonzero skips state store')
    return dict(owner_pointer_offset=32,owner_checks=[472,0,131],
                timer_compare=dict(hit_signed_half=74,owner_signed_bytes=[7404,7405],saved_hit_signed_half=76),
                common_prefix=['clear hit13','load unsigned hit10','load hit28'],
                state_ge3_returns=True,state0_transform_site='8008a728',
                transform_arguments=dict(matrix_hit_offset=0x60,captured_descriptor_hit_offset=0x28,
                                         input_descriptor_offset=0x0c,output_hit_offset=0x30),
                state0_copy_order=['load30','load34','store3c','store40','load38','store44'],
                next_loads={'8008a744':dict(signed_half_hit_offset=0x48),
                            '8008a88c':dict(signed_half_hit_offset=0x4a)},
                state1_copy_order=['load30','load34','store3c','store40','load38','store44','load60'],
                state1_transform_site='8008a888',state2_owner_byte=641,
                state2_zero_store=1,state2_matrix_validity_site='8008aa0c',
                callee_bodies_selected=False,original_execution=False)


def range_evidence(db,mapping,address,width):
    c.require(type(address)is type(width)is int,'range integer fields')
    c.require((address,width)==RANGE[:2],'range not allowlisted')
    normal.require_mapping(mapping,TEXT_MAPPING)
    raw,spans=db.chain(mapping[-1],address-mapping[0],width,mapping[-2])
    c.require(len(raw)==width and hashlib.sha256(raw).hexdigest()==RANGE[2],'range digest/width mismatch')
    rows=[]
    for offset in range(0,width,4):
        pc=address+offset;r=decode_selected(c.integer(raw,offset,'I'),pc)
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
                selection=dict(reads=1,bytes=996,data_cells=0,helpers_read=False,pointer_following=False,raw_or_operand_listing_output=False),
                caveat='Archived static evidence only. No original execution, callee body verification, live inputs or completed normal battle frame.')


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
