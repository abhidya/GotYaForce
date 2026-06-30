#!/usr/bin/env python3
"""Robust-ish PPC disassembler: capstone for most, manual fallback for FP/PS ops
capstone skips (Gekko paired-single + some FP-compare forms)."""
import struct, sys, re
from capstone import *
import os; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dol import data, addr_to_off, read_u32, read_f32
import disasm as D  # for SYMS

md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)

def manual(w, addr):
    op = (w>>26)&0x3f
    D_ = (w>>21)&31; A=(w>>16)&31; B=(w>>11)&31; C=(w>>6)&31
    xo10=(w>>1)&0x3ff; xo5=(w>>1)&0x1f
    d = w & 0xffff
    sd = d-0x10000 if d&0x8000 else d
    rc='.' if w&1 else ''
    # opcode 48/50 lfs/lfd, 52/54 stfs/stfd
    if op==48: return f"lfs      f{D_}, {sd:#x}(r{A})"
    if op==49: return f"lfsu     f{D_}, {sd:#x}(r{A})"
    if op==50: return f"lfd      f{D_}, {sd:#x}(r{A})"
    if op==52: return f"stfs     f{D_}, {sd:#x}(r{A})"
    if op==53: return f"stfsu    f{D_}, {sd:#x}(r{A})"
    if op==54: return f"stfd     f{D_}, {sd:#x}(r{A})"
    if op==56: return f"psq_l    f{D_}, ...(r{A})"
    if op==60: return f"psq_st   f{D_}, ...(r{A})"
    if op==59: # single-precision FP
        m={18:'fdivs',20:'fsubs',21:'fadds',25:'fmuls',24:'fres',
           28:'fmsubs',29:'fmadds',30:'fnmsubs',31:'fnmadds'}
        n=m.get(xo5,m.get(xo10,f'fp59_{xo10}'))
        if xo5 in (25,28,29,30,31): return f"{n}{rc}    f{D_}, f{A}, f{C}, f{B}"
        return f"{n}{rc}    f{D_}, f{A}, f{B}"
    if op==63: # double + compares
        if xo10==0: return f"fcmpu    cr{(w>>23)&7}, f{A}, f{B}"
        if xo10==32: return f"fcmpu    cr{(w>>23)&7}, f{A}, f{B}"
        if xo10==64: return f"fcmpo    cr{(w>>23)&7}, f{A}, f{B}"
        m={12:'frsp',15:'fctiwz',72:'fmr',136:'fnabs',40:'fneg',264:'fabs',
           18:'fdiv',20:'fsub',21:'fadd',25:'fmul',23:'fsel'}
        n=m.get(xo10,m.get(xo5,f'fp63_{xo10}'))
        if xo5 in (25,):  return f"fmul{rc}     f{D_}, f{A}, f{C}"
        if xo10 in (72,264,136,40,12): return f"{n}{rc}    f{D_}, f{B}"
        return f"{n}{rc}    f{D_}, f{A}, f{B}"
    if op==4:  # paired single
        return f"ps_op    f{D_}, f{A}, f{B} (xo={xo10})"
    return None

def one(w, addr):
    code=struct.pack(">I",w)
    for ins in md.disasm(code, addr):
        s=f"{ins.mnemonic:<8} {ins.op_str}"
        for tok in re.findall(r"0x[0-9a-fA-F]+", ins.op_str):
            t=int(tok,16)
            if t in D.SYMS: s+=f"   <{D.SYMS[t]}>"
        return s
    m=manual(w,addr)
    return m if m else f".word    0x{w:08x}"

def disasm(start, length):
    o=addr_to_off(start)
    out=[]
    for i in range(length//4):
        a=start+i*4
        w=struct.unpack(">I",data[o+i*4:o+i*4+4])[0]
        out.append(f"  {a:08x}:  {w:08x}  {one(w,a)}")
    return "\n".join(out)

if __name__=="__main__":
    print(disasm(int(sys.argv[1],16), int(sys.argv[2],16)))
