#!/usr/bin/env python3
"""decode-tdc-archives.py — decode the GG4E desk-intro anim/pose banks (tdc00..09.arc).

These 10 bare HSD DATs (root name `scene_data`, 1.3-1.8 KB each) are preloaded with
tl00_mdl.arc by zz_0042a58_ and hold the title-desk actor animation/pose data. pl000amot.bin
(Sasuke's battle motion bank) is absent from AFS, so the tdc banks are likely the canonical
source for the desk-intro anims across both actor slots.

Uses the validated DAT loader from research/prototypes/hsd_walker.py. Goal: identify the
root object graph (HSD JObj/AObj/FObj), extract the transform keyframes (tx,ty,tz /
rx,ry,rz / sx,sy,sz per frame), and report what each tdc bank contains.
"""
import os
import struct
import sys

PROTO = os.path.join(os.path.dirname(__file__), "..", "research", "prototypes")
sys.path.insert(0, PROTO)
import hsd_walker  # noqa: E402  (validated DAT loader + helpers)

ROOT = r"D:\GotYaForce\user-data\GG4E\afs_data\root"

# HSD object signatures (class id at struct +0x00 in the reloc-resolved object graph).
# AObj (animation) = {u32 type, f32 frame_count, u32 next_ptr, u32 fobj_ptr}.
# FObj (animation track) = {u32 next_ptr, u32 type, u32 keyframe_ptr, ...}.
# JObjDesc (joint descriptor) = {ptr child, ptr next, f32 scaleX, f32 scaleY, f32 scaleZ,
#   f32 rotX, f32 rotY, f32 rotZ, f32 trX, f32 trY, f32 trZ, ...}.


def walk_pointers(dat, rel, depth=0, seen=None):
    """Recursively dump reloc-marked pointers from a struct, depth-limited."""
    if seen is None:
        seen = set()
    if rel in seen or depth > 4:
        return
    seen.add(rel)


def dump_struct(dat, rel, label, n_words=8):
    a = dat.abs(rel)
    words = [dat.ru32(rel + i * 4) for i in range(n_words)]
    floats = []
    for i in range(n_words):
        v = struct.unpack(">f", struct.pack(">I", words[i]))[0]
        floats.append(v)
    is_ptr = [dat.isp(rel + i * 4) for i in range(n_words)]
    print(f"    {label}@rel=0x{rel:x} (file 0x{a:x}):")
    for i in range(n_words):
        pmark = "ptr->0x{:x}".format(words[i]) if is_ptr[i] else ""
        print(f"      +0x{i*2:02x}: u32=0x{words[i]:08x}  f32={floats[i]:>12.4f}  {pmark}")


def decode_bank(name):
    path = os.path.join(ROOT, name)
    dat, n = hsd_walker.load(path)
    droot, rname = dat.roots[0]
    print("=" * 72)
    print(f"{name}: size={n} dsize=0x{dat.data_size:x} relocs={dat.reloc_count} root={rname}@rel=0x{droot:x}")
    # Root scene_data struct.
    dump_struct(dat, droot, "root scene_data", n_words=12)
    # Walk the 4 leading pointers (hypothesis: sub-trees / descriptor tables).
    leading = [dat.ru32(droot + i * 4) for i in range(4)]
    leading_relocs = [dat.isp(droot + i * 4) for i in range(4)]
    print(f"    leading ptrs: {['0x%x' % p if r else '-' for p, r in zip(leading, leading_relocs)]}")
    # Enumerate ALL reloc targets (every pointer in the object graph).
    targets = sorted(dat.relocs)
    ptr_uses = {}
    for loc in targets:
        tgt = dat.ru32(loc)
        ptr_uses.setdefault(tgt, []).append(loc)
    print(f"    distinct reloc targets: {len(ptr_uses)} (reloc sites: {len(targets)})")
    # Sample the first few distinct targets (the object graph nodes).
    nodes = sorted(ptr_uses.keys())
    for t in nodes[:6]:
        refs = ptr_uses[t]
        dump_struct(dat, t, f"node (refs from {len(refs)} site{'s' if len(refs)!=1 else ''})", n_words=10)
    # Hunt for AObj (animation object): a struct whose +0x04 reads as a sane float frame
    # count (>0, <10000) and whose +0x00 is a small type int and +0x08/+0x0c are pointers.
    print(f"    -- scanning {len(nodes)} reloc targets for AObj/FObj signatures --")
    aobj_candidates = []
    fobj_candidates = []
    for t in nodes:
        if t + 0x14 > dat.data_size:
            continue
        w = [dat.ru32(t + i * 4) for i in range(5)]
        f1 = struct.unpack(">f", struct.pack(">I", w[1]))[0]
        # AObj: type small int at +0x00, f32 frame_count at +0x04, ptrs at +0x08/+0x0c
        if 0 < w[0] < 16 and 0.0 < f1 < 10000.0 and (dat.isp(t + 8) or dat.isp(t + 0xc)):
            aobj_candidates.append((t, w, f1))
        # FObj: +0x00 next ptr, +0x04 track type (small int 0..20), +0x08 keyframe ptr
        if dat.isp(t) and 0 < w[1] < 32 and dat.isp(t + 8):
            fobj_candidates.append((t, w))
    print(f"    AObj candidates (type,frameCount,ptrs): {len(aobj_candidates)}")
    for t, w, f1 in aobj_candidates[:4]:
        print(f"      rel=0x{t:x} type={w[0]} frames={f1:.1f} +0x08={'ptr' if dat.isp(t+8) else '-'} +0x0c={'ptr' if dat.isp(t+0xc) else '-'}")
    print(f"    FObj candidates (next,trackType,keyframePtr): {len(fobj_candidates)}")
    for t, w in fobj_candidates[:6]:
        tt = w[1]
        kind = {0:"TX",1:"TY",2:"TZ",3:"RX",4:"RY",5:"RZ",6:"SX",7:"SY",8:"SZ",11:"AA",12:"AB"}.get(tt, f"?{tt}")
        print(f"      rel=0x{t:x} trackType={tt}({kind}) next=0x{w[0]:x} kfptr=0x{w[2]:x}")
    # Float census (how much of the payload is plausible f32 transform values).
    plausible = 0
    total = dat.data_size // 4
    for i in range(total):
        v = struct.unpack(">f", dat.raw[dat.ds + i * 4: dat.ds + i * 4 + 4])[0]
        if -100000.0 < v < 100000.0 and v != 0.0 and (abs(v) > 1e-6 or v == 0.0):
            plausible += 1
    print(f"    float census: {plausible}/{total} words are plausible f32 ({100*plausible//max(1,total)}%)")


if __name__ == "__main__":
    for nm in ["tdc00.arc", "tdc03.arc", "tdc06.arc", "tdc09.arc"]:
        try:
            decode_bank(nm)
        except Exception as e:
            import traceback
            print(f"ERROR {nm}: {e}")
            traceback.print_exc()
