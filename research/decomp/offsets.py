#!/usr/bin/env python3
"""Harvest base-relative struct accesses. We track which GPR holds the borg
base (commonly r30/r31 = saved r3) and record every load/store offset + width
+ whether float."""
import struct, sys, re
import os; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dol import data, addr_to_off

# load/store opcodes -> (mnemonic, width, is_float, is_store)
LS = {
 32:('lwz',4,0,0),33:('lwzu',4,0,0),34:('lbz',1,0,0),35:('lbzu',1,0,0),
 36:('stw',4,0,1),37:('stwu',4,0,1),38:('stb',1,0,1),39:('stbu',1,0,1),
 40:('lhz',2,0,0),41:('lhzu',2,0,0),42:('lha',2,0,0),43:('lhau',2,0,0),
 44:('sth',2,0,1),45:('sthu',2,0,1),
 48:('lfs',4,1,0),49:('lfsu',4,1,0),50:('lfd',8,1,0),
 52:('stfs',4,1,1),53:('stfsu',4,1,1),54:('stfd',8,1,1),
}

def harvest(start, end, base_regs=(30,31,3)):
    o=addr_to_off(start)
    n=(end-start)//4
    acc={}  # off -> dict(reads,writes,float,width,regs)
    for i in range(n):
        w=struct.unpack(">I",data[o+i*4:o+i*4+4])[0]
        op=(w>>26)&0x3f
        if op in LS:
            mn,width,isf,isst=LS[op]
            A=(w>>16)&31
            if A in base_regs:
                d=w&0xffff; sd=d-0x10000 if d&0x8000 else d
                if 0<=sd<0x4000:
                    e=acc.setdefault(sd,{'r':0,'w':0,'f':0,'i':0,'width':width})
                    if isst: e['w']+=1
                    else: e['r']+=1
                    if isf: e['f']+=1
                    else: e['i']+=1
                    e['width']=max(e['width'],width)
    return acc

if __name__=="__main__":
    start=int(sys.argv[1],16); end=int(sys.argv[2],16)
    acc=harvest(start,end)
    print(f"struct offsets accessed via base reg in [{start:08x},{end:08x}):")
    print(f"{'off':>6} {'wid':>3} {'r':>4} {'w':>4} {'kind'}")
    for off in sorted(acc):
        e=acc[off]
        kind='float' if e['f']>e['i'] else ('int' if e['i'] else '?')
        print(f"0x{off:04x} {e['width']:>3} {e['r']:>4} {e['w']:>4} {kind}")
