"""Independently transcribed expected operands in exact address order.

This is explicit test data, not computed from the decoder or a saved report.
Branch fields AA=0/LK follow mnemonic; explicit blr is BO20 BI0 BH0 LK0.
"""
FIELDS = {
 'stwu':'rS rA displacement','stw':'rS rA displacement','stb':'rS rA displacement','sth':'rS rA displacement',
 'lwz':'rD rA displacement','lbz':'rD rA displacement','lhz':'rD rA displacement','lha':'rD rA displacement',
 'addi':'rD rA immediate','mflr':'rD','mtlr':'rS','or':'rS rA rB Rc',
 'rlwinm':'rS rA SH MB ME Rc','extsb':'rS rA Rc',
 'cmpi':'BF L rA immediate','cmp':'BF L rA rB',
 'b':'target','bl':'target','bc':'BO BI target','blr':''}
def ops(text):
 result=[]
 for line in text.strip().splitlines():
  name,*values=line.split(); keys=FIELDS[name].split(); assert len(keys)==len(values)
  row=dict(mnemonic=name,**{k:v if k=='target' else int(v,0) for k,v in zip(keys,values)})
  if name in ('b','bl','bc'): row.update(AA=0,LK=int(name=='bl'))
  if name=='blr': row.update(BO=20,BI=0,BH=0,LK=0)
  result.append(row)
 return result
EXPECTED={
0x80069210:ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
lwz 0 3 0x5e0
rlwinm 0 0 0 30 30 1
bc 12 2 80069230
addi 3 0 0
b 800692ac
lwz 0 3 0x5d4
rlwinm 0 0 0 30 30 1
bc 4 2 80069244
addi 3 0 0
b 800692ac
lbz 0 3 0x588
extsb 0 0 1
bc 4 2 80069258
addi 3 0 0
b 800692ac
lbz 4 3 0x7cd
extsb 4 0 1
bc 4 2 80069284
lwz 4 3 0x4ac
lbz 5 3 0x747
lbz 0 4 0x9f
extsb 5 4 0
cmp 0 0 4 0
bc 12 0 800692a4
addi 3 0 0
b 800692ac
extsb 4 0 0
cmpi 0 0 0 1
bc 4 2 800692a4
lha 0 3 0x736
cmpi 0 0 0 0
bc 12 1 800692a4
addi 3 0 0
b 800692ac
addi 4 0 8
bl 8006a750
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
0x800693fc:ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lbz 0 3 0x661
extsb 0 0 0
cmpi 0 0 0 2
bc 4 2 80069428
addi 3 0 0
b 800694ac
cmpi 0 0 0 5
bc 4 2 80069438
addi 3 0 0
b 800694ac
bl 800694c0
cmpi 0 0 3 0
bc 4 2 8006944c
addi 3 0 0
b 800694ac
lwz 0 31 0x5e0
rlwinm 0 0 0 31 31 1
bc 12 2 80069460
addi 3 0 0
b 800694ac
lhz 0 31 0x5d8
rlwinm 0 0 0 24 27 1
bc 4 2 80069474
addi 3 0 0
b 800694ac
or 31 3 31 0
addi 4 0 15
bl 8006a750
cmpi 0 0 3 0
bc 4 2 80069490
addi 3 0 0
b 800694ac
lhz 0 31 0x5d8
addi 3 0 1
rlwinm 0 0 28 28 31 0
stb 0 31 0x58f
lhz 0 31 0x5d8
rlwinm 0 0 0 28 23 0
sth 0 31 0x5d8
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
0x8006965c:ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lbz 0 3 0x661
cmpi 0 0 0 2
bc 12 2 80069684
addi 3 0 0
b 800696e0
lwz 0 31 0x5e0
rlwinm 0 0 0 30 30 1
bc 12 2 80069698
addi 3 0 0
b 800696e0
lhz 0 31 0x5d8
rlwinm 0 0 0 24 27 1
bc 4 2 800696ac
addi 3 0 0
b 800696e0
addi 4 0 22
bl 8006a750
cmpi 0 0 3 0
bc 4 2 800696c4
addi 3 0 0
b 800696e0
lhz 0 31 0x5d8
addi 3 0 1
rlwinm 0 0 28 28 31 0
stb 0 31 0x58f
lhz 0 31 0x5d8
rlwinm 0 0 0 28 23 0
sth 0 31 0x5d8
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
0x800695c4:ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
lbz 0 3 0x661
cmpi 0 0 0 2
bc 12 2 800695e4
addi 3 0 0
b 80069614
lwz 0 3 0x5e0
rlwinm 0 0 0 30 30 1
bc 12 2 800695f8
addi 3 0 0
b 80069614
lwz 0 3 0x5b4
rlwinm 0 0 0 12 15 1
bc 12 2 80069610
addi 4 0 19
bl 8006a750
b 80069614
addi 3 0 0
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
0x8006952c:ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
lbz 0 3 0x661
cmpi 0 0 0 2
bc 12 2 8006954c
addi 3 0 0
b 8006957c
lwz 0 3 0x5e0
rlwinm 0 0 0 30 30 1
bc 12 2 80069560
addi 3 0 0
b 8006957c
lwz 0 3 0x5b4
rlwinm 0 0 0 23 23 1
bc 12 2 80069578
addi 4 0 18
bl 8006a750
b 8006957c
addi 3 0 0
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
0x800691d8:ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
lbz 0 3 0x4a0
cmpi 0 0 0 2
bc 4 2 800691f8
addi 3 0 0
b 80069200
bl 800677b0
addi 3 0 0
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
}

def encode(i, pc):
    """Independent inverse PPC field encoder, no production decoder dependency."""
    name=i['mnemonic']
    memory={'lwz':32,'lbz':34,'stw':36,'stwu':37,'stb':38,'lhz':40,'lha':42,'sth':44}
    if name in memory:
        reg=i['rD'] if name in ('lwz','lbz','lhz','lha') else i['rS']
        return memory[name]<<26 | reg<<21 | i['rA']<<16 | (i['displacement']&65535)
    if name=='addi': return 14<<26 | i['rD']<<21 | i['rA']<<16 | (i['immediate']&65535)
    if name in ('mflr','mtlr'):
        reg=i['rD'] if name=='mflr' else i['rS']
        return 31<<26 | reg<<21 | 8<<16 | (339 if name=='mflr' else 467)<<1
    if name=='or': return 31<<26 | i['rS']<<21 | i['rA']<<16 | i['rB']<<11 | 444<<1 | i['Rc']
    if name=='extsb': return 31<<26 | i['rS']<<21 | i['rA']<<16 | 954<<1 | i['Rc']
    if name=='rlwinm': return 21<<26 | i['rS']<<21 | i['rA']<<16 | i['SH']<<11 | i['MB']<<6 | i['ME']<<1 | i['Rc']
    if name=='cmpi': return 11<<26 | i['BF']<<23 | i['L']<<21 | i['rA']<<16 | (i['immediate']&65535)
    if name=='cmp': return 31<<26 | i['BF']<<23 | i['L']<<21 | i['rA']<<16 | i['rB']<<11
    if name in ('b','bl','bc'):
        target=int(i['target'],16); delta=target if i['AA'] else target-pc
        if name=='bc': return 16<<26 | i['BO']<<21 | i['BI']<<16 | (delta&0xfffc) | i['AA']<<1 | i['LK']
        return 18<<26 | (delta&0x3fffffc) | i['AA']<<1 | i['LK']
    if name=='blr': return 19<<26 | i['BO']<<21 | i['BI']<<16 | i['BH']<<11 | 16<<1 | i['LK']
    raise ValueError(name)
