#!/usr/bin/env python3
"""Five fixed nonnull-JObj leaf helper bodies,1912 bytes. Original data stays local.
No arbitrary selection, payload reads, pointer following or raw instruction output.
"""
import argparse,hashlib,json,sys
from pathlib import Path
import read_archived_loadjoint_foundation_evidence as f
c=f.c
TEXT_MAPPING=f.TEXT_MAPPING
RANGES = ((2149833444, 152, '475bac2ae34eaa5ede6911882d00f547ecad9e2279484ef69c2097b0fe8826af'), (2149943436, 1140, '6604fea69c349a70f0d77f4b8c5f03d344f12fe5460039490668fd22e519f0c9'), (2149947044, 236, '9f75beffa64470d01074a0e5ea8df4c65f352857791e4dca41ce7b565b80dba2'), (2149943160, 276, '7120c565d10c34b9e22c4d1879c96d4981fa6185384c7f2aad4d6c9c64db530e'), (2149833804, 108, 'd66ec94a1738b0f4851123362f10910365967aea99bd68692c4c4995a5303520'))
OPERAND_DIGESTS = {2149833444: '40ab9e92f48f03c4c03aacb99cd0e06a2f91a59b220e47529f1dd4b14dd07cea', 2149943436: '1ff9d28700a0958b1a39573fda49a6d289ed1a98350cf34f7a4ff0ce035b596a', 2149947044: 'd7d447898fd665df4c77f085bbbef37328460f7cfd40eb4efd7cafb71812799e', 2149943160: '3a22d25c30652e42e861ebd5cc3bc130590675e6c0877174ea970dc0327f8674', 2149833804: 'c18433f23c9e29ce02e35ca87b26c09e3a5397140edbac728d8a1eef18c31046'}
FLOW_DIGESTS = {2149833444: (12, '0ec5fcbeba31308065448770259b0494659bde9bef822868c3f5e5a0d1a15dcb'), 2149943436: (100, '4b15a71f1f57c2310ae763b92e39a82284b46897da6ab63a2d21bef8a6d6568d'), 2149947044: (13, 'caf771fb4a825cc6f31c3b4c42ad940055eebe7bdc2f053022a910234cd6689e'), 2149943160: (19, 'ae62b9def0f0605cd08d66092a0c3ef94df70af18d9a4cfa8fa985aa0a9c2c7f'), 2149833804: (7, 'b96ed5a4ca8508734fb51844e3f13c0e8ef8e7a04c3be35bb4d18884524f8fea')}
CALLS = {2149833444: (('8023db14', '8025d4e8'), ('8023db20', '8023dbf0'), ('8023db2c', '8025d088'), ('8023db44', '80264290')), 2149943436: (('8025889c', '80232a9c'), ('802588a8', '80258d9c'), ('802588bc', '80258d9c'), ('802588d0', '80258d9c'), ('802588e4', '80258d9c'), ('802588f0', '8025888c'), ('80258994', '80259338'), ('802589a4', '8025942c'), ('802589e4', '802642ec'), ('80258a90', '80259338'), ('80258aa0', '8025942c'), ('80258ae0', '802642ec'), ('80258b8c', '80259338'), ('80258b9c', '8025942c'), ('80258bdc', '802642ec'), ('80258c88', '80259338'), ('80258c98', '8025942c'), ('80258cd8', '802642ec'), ('80258cec', '80232ae8')), 2149947044: (('802596b4', '80232aa8'), ('80259738', '802572f0'), ('80259750', '80264290'), ('80259760', '8000540c'), ('8025977c', '80232af4')), 2149943160: (('802587dc', '8024febc'), ('802587ec', '8025983c'), ('8025880c', '80264290'), ('80258840', '80264290'), ('80258854', '80259524')), 2149833804: (('8023dc84', '8024aaac'),)}
INDIRECT = {2149833444: ('8023db5c',), 2149943436: (), 2149947044: (), 2149943160: (), 2149833804: ()}

def decode_selected(word,pc):
 c.require(type(word)is int and 0<=word<=0xffffffff,'word bounds')
 c.require(type(pc)is int and 0<=pc<=0xfffffffc and pc%4==0,'PC bounds')
 if word>>26==31 and ((word>>1)&1023)==11:return f.mass.decode_selected(word,pc)
 return f.decode_selected(word,pc)
def range_evidence(db,mapping,pc,size):
 c.require(type(pc)is int and type(size)is int,'range integers')
 selected=[r for r in RANGES if r[:2]==(pc,size)];c.require(len(selected)==1,'range not allowlisted')
 f.normal.require_mapping(mapping,TEXT_MAPPING)
 c.require(pc%4==size%4==0 and mapping[0]<=pc<pc+size<=mapping[1],'range bounds')
 raw,spans=db.chain(mapping[-1],pc-mapping[0],size,mapping[-2]);c.require(len(raw)==size,'range byte width')
 digest=hashlib.sha256(raw).hexdigest();c.require(digest==selected[0][2],'range digest mismatch')
 rows=[]
 for off in range(0,size,4):
  at=pc+off;decoded=decode_selected(c.integer(raw,off,'I'),at);c.require(decoded is not None,'unselected instruction');rows.append(dict(address=f'{at:08x}',**decoded))
 flow=[r for r in rows if r['mnemonic']in('b','bc','bl','blr','bctrl')]
 c.require(f.semantic_digest(rows)==OPERAND_DIGESTS[pc],'operand mismatch')
 c.require((len(flow),f.semantic_digest(flow))==FLOW_DIGESTS[pc],'flow mismatch')
 calls=tuple((r['address'],r['target'])for r in flow if r['mnemonic']=='bl');c.require(calls==CALLS[pc],'call schedule mismatch')
 indirect=tuple(r['address']for r in flow if r['mnemonic']=='bctrl');c.require(indirect==INDIRECT[pc],'indirect mismatch')
 c.require(all(pc<=int(r['target'],16)<pc+size for r in flow if r['mnemonic']in('b','bc')),'branch outside body')
 c.require(rows[-1]==dict(address=f'{pc+size-4:08x}',mnemonic='blr',BO=20,BI=0,BH=0,LK=0),'terminal return mismatch')
 return dict(address=f'{pc:08x}',width=size,sha256=digest,represented_instructions=len(rows),unrepresented_instructions=0,operand_sha256=OPERAND_DIGESTS[pc],control_flow_sha256=FLOW_DIGESTS[pc][1],calls=[dict(site=s,target=t)for s,t in calls],indirect_calls=list(indirect),spans=spans)
def inspect(data,digest):
 auth=c.inspect(data,digest);db=c.GBF(data);tables=db.tables();blocks=db.rows(tables['Memory Blocks']);subs=db.rows(tables['Sub Memory Blocks']);image=int(auth['image_offset'],16)
 f.command.mappings(blocks,subs,image);mapping,fact=f.normal.mapping_evidence(blocks,subs,image,TEXT_MAPPING)
 return dict(snapshot_sha256=digest,mapping=fact,ranges=[range_evidence(db,mapping,pc,n)for pc,n,_ in RANGES],selection_basis=dict(reads=5,bytes=1912,data_cells=0,pointer_following=False,global_payloads_read=False,raw_output=False),caveat='Authenticated static body evidence only, not execution, live owner provenance or complete LoadJoint/frame.')
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('snapshot',type=Path);a=p.parse_args()
 try:
  c.require(a.snapshot.is_file()and 32<=a.snapshot.stat().st_size<=c.MAX_FILE,'snapshot file bounds')
  with a.snapshot.open('rb')as stream:data=stream.read(c.MAX_FILE+1)
  c.require(len(data)<=c.MAX_FILE,'snapshot size');print(json.dumps(inspect(data,hashlib.sha256(data).hexdigest()),indent=2))
 except(OSError,c.FormatError)as e:print(json.dumps(dict(error=str(e))),file=sys.stderr);return 1
 return 0
if __name__=='__main__':sys.exit(main())
