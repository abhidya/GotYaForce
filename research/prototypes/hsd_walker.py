#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
hsd_walker.py -- hand-written HSD DAT (HAL Sysdolphin) parser for Gotcha Force (GG4E) .arc models.

VALIDATED on real GG4E disc bytes (arrow_mdl.arc, deck00_mdl.arc, pl0f06k_mdl.arc).
Walks scene_data -> node array -> MOBJ -> POBJ -> VtxDescList + GX display list,
extracts POSITION vertices, triangulates GX primitives, writes .obj.

IMPORTANT GF-vs-Melee divergences discovered (see report at bottom of run):
  * scene_data root is a SCENE struct (3 cross-linked pointer tables), NOT a JOBJ.
  * The model graph node array entries are MOBJ-style (material+geometry refs),
    not the textbook Melee JOBJ(0x40)/DOBJ(0x10) chain. Field offsets differ.
  * POBJ: vtxDescList ptr @+0x08, display-list ptr @+0x0C.
  * VtxDescList entry = 0x18 bytes: u32 attr, u32 attrType, u32 compCnt, u32 compType,
    u8 frac, u8 pad, u16 stride, u32 arrayPtr.  Terminator attr == 0xFF.
  * Display list = GX primitive stream; for arrow, per-vertex index is 1 byte (INDEX8),
    POS attr only. TRISTRIP (0x98) primitives.

All values BIG-ENDIAN.
"""
import struct, os, sys

ROOT    = r"D:\GotYaForce\user-data\GG4E\afs_data\root"
OUT_DIR = r"D:\GotYaForce\user-data\GG4E\hsd-test-python"

def u8(b,o):  return b[o]
def u16(b,o): return struct.unpack_from(">H",b,o)[0]
def s16(b,o): return struct.unpack_from(">h",b,o)[0]
def u32(b,o): return struct.unpack_from(">I",b,o)[0]
def f32(b,o): return struct.unpack_from(">f",b,o)[0]

GXVA = {0:"PNMTXIDX",1:"TEX0MTXIDX",9:"POS",10:"NRM",11:"CLR0",12:"CLR1",
        13:"TEX0",14:"TEX1",0xFF:"NULL"}
GX_PRIM = {0x80:"QUADS",0x90:"TRIANGLES",0x98:"TRISTRIP",0xA0:"TRIFAN",
           0xA8:"LINES",0xB0:"LINESTRIP",0xB8:"POINTS"}

class DAT:
    def __init__(self, raw, base):
        self.raw=raw; self.base=base; self.ds=base+0x20
        self.file_size=u32(raw,base); self.data_size=u32(raw,base+4)
        self.reloc_count=u32(raw,base+8); self.root_count=u32(raw,base+0xC)
        self.extref_count=u32(raw,base+0x10)
        self.reloc_off=self.ds+self.data_size
        self.root_off=self.reloc_off+self.reloc_count*4
        self.extref_off=self.root_off+self.root_count*8
        self.symbol_off=self.extref_off+self.extref_count*8
        self.relocs=set(u32(raw,self.reloc_off+i*4) for i in range(self.reloc_count))
        self.roots=[]
        for i in range(self.root_count):
            do=u32(raw,self.root_off+i*8); so=u32(raw,self.root_off+i*8+4)
            p=self.symbol_off+so; e=raw.find(b"\x00",p)
            self.roots.append((do, raw[p:e].decode("ascii","replace")))
    # data-block-relative accessors
    def abs(self,rel): return self.ds+rel
    def ru32(self,rel): return u32(self.raw,self.ds+rel)
    def rf32(self,rel): return f32(self.raw,self.ds+rel)
    def ru16(self,rel): return u16(self.raw,self.ds+rel)
    def ru8(self,rel):  return self.raw[self.ds+rel]
    def ptr(self,rel):
        v=self.ru32(rel); return None if v==0 else v
    def isp(self,rel): return rel in self.relocs

def load(path):
    raw=open(path,"rb").read(); n=len(raw); base=0
    if n>0x104 and u32(raw,0)==0x100 and u32(raw,0x100)==n-0x100: base=0x100
    return DAT(raw,base), n

# ---------------------------------------------------------------------------
# VtxDescList (0x18-byte entries, terminated by attr==0xFF)
# ---------------------------------------------------------------------------
def parse_vtxdesc(dat, rel):
    out=[]
    for k in range(32):
        b=rel+k*0x18
        if dat.abs(b)+0x18 > len(dat.raw): break
        attr=dat.ru32(b)
        if attr==0xFF: break
        # NOTE: array offset 0x0 is a VALID data-block-relative target (arrow POS array
        # lives at rel 0x0). Treat the field as a pointer iff the reloc table marks it.
        arr_loc=b+0x14
        arr = dat.ru32(arr_loc) if dat.isp(arr_loc) else None
        out.append(dict(rel=b, attr=attr, attr_type=dat.ru32(b+4),
            comp_cnt=dat.ru32(b+8), comp_type=dat.ru32(b+0xC),
            frac=dat.ru8(b+0x10), stride=dat.ru16(b+0x12),
            array=arr))
    return out

# ---------------------------------------------------------------------------
# Find POBJs by signature: a struct with reloc ptr @+0x08 -> a valid VtxDescList
# containing a POS(9) attr, and reloc ptr @+0x0C -> a display-list region.
# This is robust against the exact JOBJ/MOBJ wrapper layout.
# ---------------------------------------------------------------------------
def looks_like_vtxdesc(dat, rel):
    """Return descs if rel points at a VtxDescList containing a POS attr whose
    array pointer is reloc-marked (i.e. a real geometry stream)."""
    if rel is None or rel>=dat.data_size: return None
    descs=parse_vtxdesc(dat, rel)
    if not descs: return None
    pos=next((d for d in descs if d["attr"]==9), None)
    if pos is None or pos["array"] is None: return None
    return descs

def dl_start(dat, rel):
    """Given a display-list ptr, skip leading 0x00 padding and return the abs offset
    of the first GX primitive opcode, or None if none found within 0x20 bytes."""
    if rel is None or rel>=dat.data_size: return None
    a=dat.abs(rel)
    for k in range(0x20):
        if a+k>=len(dat.raw): return None
        op=dat.raw[a+k]
        if op==0x00: continue
        if op in GX_PRIM: return a+k
        return None
    return None

def find_pobjs(dat):
    """Standard HSD_POBJ layout (CONFIRMED on arrow):
        +0x00 u32 class_name_ptr (0 in GF)
        +0x04 u32 next_ptr
        +0x08 u32 vertex_attr_list_ptr  -> VtxDescList (POS entry)
        +0x0C u16 flags, u16 n_display
        +0x10 u32 display_list_ptr      -> GX primitive stream
    A POBJ candidate: reloc @+0x08 -> VtxDescList(POS+array) AND reloc @+0x10 -> displist
    beginning (after optional padding) with a GX primitive opcode."""
    pobjs=[]
    for loc in sorted(dat.relocs):
        tgt=dat.ru32(loc)
        descs=looks_like_vtxdesc(dat,tgt)
        if descs is None: continue
        pobj_rel=loc-0x08
        if pobj_rel<0: continue
        dl_loc=pobj_rel+0x10
        if not dat.isp(dl_loc): continue
        dl=dat.ru32(dl_loc)
        dls=dl_start(dat,dl)
        if dls is None: continue
        flags=dat.ru16(pobj_rel+0x0C); ndisp=dat.ru16(pobj_rel+0x0E)
        pobjs.append(dict(rel=pobj_rel, vtxdesc=tgt, descs=descs,
                          displist=dl, dl_abs=dls, flags=flags, ndisp=ndisp))
    return pobjs

# ---------------------------------------------------------------------------
# GX display list decode. POS attr decides index size and array read.
# ---------------------------------------------------------------------------
def comp_type_size(ct): return {0:1,1:1,2:2,3:2,4:4}.get(ct,4)
def pos_ncomp(d): return 3 if d["comp_cnt"]==1 else 2  # POS: cnt1=XYZ, cnt0=XY

def read_pos(dat, posd, idx):
    arr=posd["array"]; stride=posd["stride"]; ct=posd["comp_type"]; fr=posd["frac"]
    off=arr+idx*stride; n=pos_ncomp(posd); raw=dat.raw; a=dat.abs(off); v=[]
    for c in range(n):
        if ct==4:   x=f32(raw,a+c*4)
        elif ct==3: x=s16(raw,a+c*2)/float(1<<fr)
        elif ct==2: x=u16(raw,a+c*2)/float(1<<fr)
        elif ct==1: r=raw[a+c]; x=((r-256) if r>127 else r)/float(1<<fr)
        else:       x=raw[a+c]/float(1<<fr)
        v.append(x)
    while len(v)<3: v.append(0.0)
    return tuple(v)

def attr_dl_size(d):
    """Bytes consumed per vertex in the display list for this attribute."""
    at=d["attr_type"]
    if at==2: return 1          # INDEX8
    if at==3: return 2          # INDEX16
    if at==1:                   # DIRECT inline
        n = pos_ncomp(d) if d["attr"]==9 else (3 if d["attr"]==10 else 1)
        return comp_type_size(d["comp_type"])*n
    return 0                    # NONE

def decode_displist(dat, pobj):
    """Walk the GX primitive stream starting at the display-list ptr; return (verts,tris)."""
    descs=pobj["descs"]; dl=pobj["displist"]
    posd=next((d for d in descs if d["attr"]==9), None)
    if posd is None or posd["array"] is None or dl is None:
        return [],[],"no POS/displist"
    # per-vertex layout
    per=0; pos_off=0
    for d in descs:
        if d["attr"]==9: pos_off=per
        per+=attr_dl_size(d)
    if per==0: return [],[],"zero stride"
    pos_at=posd["attr_type"]
    raw=dat.raw; p=pobj.get("dl_abs") or dat.abs(dl); end=dat.abs(dat.data_size)
    verts=[]; tris=[]
    guard=0
    while p<end and guard<100000:
        guard+=1
        op=raw[p]
        if op==0x00: p+=1; continue
        if op not in GX_PRIM: break
        cnt=u16(raw,p+1)
        if cnt==0 or cnt>4096: break
        p+=3
        base_v=len(verts)
        prim=[]
        ok=True
        for vi in range(cnt):
            ve=p+vi*per
            if ve+per>end: ok=False; break
            fo=ve+pos_off
            if pos_at==3:   idx=u16(raw,fo)
            elif pos_at==2: idx=raw[fo]
            else:           idx=None
            if idx is None:
                xyz=_inline_pos(dat,fo,posd)
            else:
                # bounds check on POS array
                if dat.abs(posd["array"]+idx*posd["stride"])+12>len(raw): ok=False;break
                xyz=read_pos(dat,posd,idx)
            # sanity: reject non-finite / implausible coords (catches mis-sized strides)
            if any((v!=v) or abs(v)>1e6 for v in xyz): ok=False; break
            prim.append(xyz)
        if not ok: break
        verts.extend(prim); p+=cnt*per
        m=len(prim)
        if op==0x90:
            for t in range(0,m-2,3): tris.append((base_v+t,base_v+t+1,base_v+t+2))
        elif op==0x98:
            for t in range(m-2):
                if t%2==0: tris.append((base_v+t,base_v+t+1,base_v+t+2))
                else:      tris.append((base_v+t+1,base_v+t,base_v+t+2))
        elif op==0xA0:
            for t in range(1,m-1): tris.append((base_v,base_v+t,base_v+t+1))
        elif op==0x80:
            for t in range(0,m-3,4):
                tris.append((base_v+t,base_v+t+1,base_v+t+2))
                tris.append((base_v+t,base_v+t+2,base_v+t+3))
    return verts,tris,None

def _inline_pos(dat,off,d):
    ct=d["comp_type"]; fr=d["frac"]; n=pos_ncomp(d); raw=dat.raw; v=[]
    for c in range(n):
        if ct==4: x=f32(raw,off+c*4)
        elif ct==3: x=s16(raw,off+c*2)/float(1<<fr)
        else: x=0.0
        v.append(x)
    while len(v)<3: v.append(0.0)
    return tuple(v)

def write_obj(path, verts, tris):
    with open(path,"w") as f:
        f.write("# GG4E HSD walker export\n")
        for x,y,z in verts: f.write("v %.6f %.6f %.6f\n"%(x,y,z))
        for a,b,c in tris: f.write("f %d %d %d\n"%(a+1,b+1,c+1))
    return len(verts),len(tris)

# ---------------------------------------------------------------------------
def fmt_descs(descs):
    return ", ".join("%s[type=%d cnt=%d ct=%d fr=%d stride=%d arr=%s]"%(
        GXVA.get(d["attr"],"?%d"%d["attr"]),d["attr_type"],d["comp_cnt"],
        d["comp_type"],d["frac"],d["stride"],
        ("0x%X"%d["array"]) if d["array"] else "null") for d in descs)

def process(name, export=True):
    dat,n = load(os.path.join(ROOT,name))
    print("="*72)
    print("FILE %s  size=%d base=0x%X (%s)"%(name,n,dat.base,"wrapped" if dat.base else "bare"))
    print("  fileSize=%d dataBlockSize=0x%X relocCount=%d rootCount=%d extRef=%d  layout_ok=%s"%(
        dat.file_size,dat.data_size,dat.reloc_count,dat.root_count,dat.extref_count,
        (dat.base+dat.file_size==n)))
    droot,rname=dat.roots[0]
    print("  root[0] dataOffset=0x%X name=%r"%(droot,rname))
    # scene_data top struct: 3 leading pointers
    sp=[dat.ru32(droot+i*4) for i in range(3)]
    print("  scene_data ptrs: [0]=0x%X [1]=0x%X [2]=0x%X (cross-linked scene tables)"%tuple(sp))

    pobjs=find_pobjs(dat)
    print("  POBJs found (via VtxDescList+POS signature): %d"%len(pobjs))
    if pobjs:
        # distinct attr layouts
        layouts={}
        for po in pobjs:
            k=tuple((d["attr"],d["attr_type"],d["comp_type"],d["stride"]) for d in po["descs"])
            layouts.setdefault(k,0); layouts[k]+=1
        print("  distinct vertex-attribute layouts: %d"%len(layouts))
        for po in pobjs[:1]:
            print("    sample POBJ@0x%X displist=%s attrs: %s"%(
                po["rel"], ("0x%X"%po["displist"]) if po["displist"] else "none",
                fmt_descs(po["descs"])))

    if export and pobjs:
        allv=[]; allt=[]; used=0; skipped=0
        for po in pobjs:
            v,t,err=decode_displist(dat,po)
            if err or not v:
                skipped+=1; continue
            # per-POBJ plausibility: reject if bbox is implausibly large (mis-decode)
            xs=[p[0] for p in v]; ys=[p[1] for p in v]; zs=[p[2] for p in v]
            span=max(max(xs)-min(xs),max(ys)-min(ys),max(zs)-min(zs))
            if span>1e5:
                skipped+=1; continue
            off=len(allv); allv.extend(v); allt.extend([(a+off,b+off,c+off) for a,b,c in t]); used+=1
        if allv:
            outp=os.path.join(OUT_DIR,name.replace(".arc","")+".obj")
            nv,nt=write_obj(outp,allv,allt)
            xs=[v[0] for v in allv]; ys=[v[1] for v in allv]; zs=[v[2] for v in allv]
            print("  EXPORTED %s  verts=%d tris=%d  (%d/%d POBJs, %d skipped)"%(
                outp,nv,nt,used,len(pobjs),skipped))
            print("    bbox x[%.3f,%.3f] y[%.3f,%.3f] z[%.3f,%.3f]"%(
                min(xs),max(xs),min(ys),max(ys),min(zs),max(zs)))
        else:
            print("  EXPORT: no geometry decoded")
    print()

if __name__=="__main__":
    os.makedirs(OUT_DIR,exist_ok=True)
    for nm in ("arrow_mdl.arc","deck00_mdl.arc","pl0f06k_mdl.arc"):
        try: process(nm)
        except Exception as e:
            import traceback; print("ERROR",nm,e); traceback.print_exc()
