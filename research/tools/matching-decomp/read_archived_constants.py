#!/usr/bin/env python3
"""Bounded read-only reader for twelve constants in two authenticated GBF snapshots.

Python stdlib only; no Ghidra, network, writes, or vendor-code execution. Supports
only inline single-leaf tables, ram map zero and one-level buffer indexes. This
is deliberately not a general GBF reader. Unknown layouts fail closed.

Format reference: NSA Ghidra commit 42db038f3c88c6bd7e9bedbb919138111f8b77fd:
LocalBufferFile, DBParms, TableRecord, VarRecNode, FixedRecNode,
VarKeyRecordNode, AddressMapDBAdapterV1 and MemoryMapDBAdapterV3.
XOR_MASK copied from ChainedBuffer.java, Copyright National Security Agency,
Apache-2.0 licensed:
https://github.com/NationalSecurityAgency/ghidra/blob/42db038f3c88c6bd7e9bedbb919138111f8b77fd/Ghidra/Framework/DB/src/main/java/db/ChainedBuffer.java
https://github.com/NationalSecurityAgency/ghidra/blob/42db038f3c88c6bd7e9bedbb919138111f8b77fd/LICENSE
"""
import argparse
import hashlib
import json
import math
from pathlib import Path
import re
import struct
import sys

SNAPSHOTS = {
 '7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0': 'db.3.gbf',
 '1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8': 'db.4.gbf'}
EXECUTABLE_SHA = '21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836'
DATA5_SHA = '989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4'
MAX_FILE = 512 * 1024 * 1024
MAX_CHAIN = 4 * 1024 * 1024  # Bounded to include the authenticated MAIN_.text1 chain.
XOR_MASK = bytes.fromhex(
 '59ea6723dab800b8c348dd8b21d6947835ab2b7eb24f824e0e16c457128e7ee6'
 'b6bd56915772e691dc522ef21ab7d66fdadee848b1bb506ff4dd11eef267fe48'
 '8dae691ae0268c248e177651e260d7e68365d5f07ff2a0d64bbd24d8abea9ea6'
 '48943e7b2cf4cedc6911f83ca73f5d77943fe48e4820db5632c187012ee37f40')
TARGETS = [(0x804370f0,4),(0x804370f4,4),(0x804370f8,8),
 (0x80437128,4),(0x8043d1fc,4),(0x8043d310,8),(0x8043d1f8,4),
 (0x804374e4,4),(0x804374b0,4),(0x80437464,4),(0x80437148,4),(0x80437140,8)]
CONTROLS = {0x8043d1f8:'00000000',0x804374e4:'40000000',
            0x804374b0:'40a00000',0x80437464:'bf800000'}
# Newly recovered archive target, not an independently recorded DOL control.
EXPECTED_TARGETS = {0x80437148:'42c80000',0x80437140:'4330000000000000'}

class FormatError(ValueError):
    """Unsupported, corrupt, or unauthenticated evidence."""

def require(ok, message):
    if not ok:
        raise FormatError(message)

class Cursor:
    def __init__(self, data):
        self.data, self.pos = data, 0

    def take(self, n):
        require(0 <= n <= len(self.data)-self.pos, 'record bounds')
        result = self.data[self.pos:self.pos+n]
        self.pos += n
        return result

    def num(self, fmt):
        return struct.unpack('>'+fmt, self.take(struct.calcsize('>'+fmt)))[0]

    def binary(self, nullable=False):
        n = self.num('i')
        return None if nullable and n == -1 else self.take(n)

    def string(self, nullable=False):
        raw = self.binary(nullable)
        try:
            return None if raw is None else raw.decode('utf-8')
        except UnicodeError as exc:
            raise FormatError('invalid UTF-8') from exc

    def done(self):
        require(self.pos == len(self.data), 'record trailing bytes')

def integer(data, pos, fmt='i'):
    size = struct.calcsize('>'+fmt)
    require(0 <= pos <= len(data)-size, 'integer bounds')
    return struct.unpack_from('>'+fmt,data,pos)[0]

def fields(c, types):
    out = []
    for t in types:
        if t == 4:
            value = c.string(True)
        else:
            require(t in (0,2,3,6), 'unsupported field type')
            value = c.num({0:'b',2:'i',3:'q',6:'B'}[t])
            if t == 6:
                require(value in (0,1), 'invalid boolean')
                value = bool(value)
        out.append(value)
    return out

class GBF:
    """Direct construction permits synthetic fixtures; CLI authenticates first."""
    def __init__(self, data):
        require(32 <= len(data) <= MAX_FILE, 'file size bounds')
        self.data = data
        h = Cursor(data[:32])
        require(h.num('Q') == 0x2f30312c34292c2a, 'GBF magic')
        self.file_id = h.num('Q')
        require(h.num('i') == 1, 'GBF version')
        self.block = h.num('i')
        require(64 <= self.block <= 1024*1024, 'block size bounds')
        require(len(data) % self.block == 0, 'truncated file')
        self.count = len(data)//self.block-1
        free, count = h.num('i'), h.num('i')
        require(0 <= count <= (self.block-32)//8, 'parameter count')
        p, names = Cursor(data[32:self.block]), set()
        for _ in range(count):
            name = p.string()
            require(name not in names, 'duplicate header parameter')
            names.add(name)
            p.num('i')
        self.free = set()
        while free != -1:
            require(0 <= free < self.count and free not in self.free, 'free list cycle/bounds')
            self.free.add(free)
            pos = (free+1)*self.block
            require(data[pos] == 1, 'free list flags')
            free = integer(data,pos+1)
        # Observed snapshots use physical index == logical ID; no remapping.
        for i in range(self.count):
            pos = (i+1)*self.block
            if i not in self.free:
                require(data[pos] == 0 and integer(data,pos+1) == i,
                        'missing, orphan-free, or aliased buffer')

    def buffer(self, ident):
        require(0 <= ident < self.count and ident not in self.free, 'missing/free buffer')
        p = (ident+1)*self.block
        return self.data[p+5:p+self.block]

    def leaf(self, root, keytype=3, types=None):
        a = self.buffer(root)
        variable = keytype == 4
        require(keytype in (3,4), 'unsupported key type')
        node = a[0]
        require(node in ((4,) if variable else (1,2)), 'unsupported tree layout')
        if variable:
            require(a[1] == 4, 'variable key field type')
        cp, header = (2,14) if variable else (1,13)
        count = integer(a,cp)
        require(integer(a,cp+4) == integer(a,cp+8) == -1, 'multiple leaves unsupported')
        stride = 5 if variable else 13
        if node == 2:
            require(types is not None and all(t in (0,2,3,6) for t in types), 'fixed schema')
            stride = 8 + sum({0:1,2:4,3:8,6:1}[t] for t in types)
        require(0 <= count <= (len(a)-header)//stride, 'leaf count')
        out, previous, last = [], len(a), None
        for j in range(count):
            pos = header+j*stride
            if node == 2:
                key, raw = integer(a,pos,'q'), a[pos+8:pos+stride]
            else:
                key = None if variable else integer(a,pos,'q')
                op = pos if variable else pos+8
                offset = integer(a,op)
                require(a[op+4] == 0, 'indirect record unsupported')
                require(header+count*stride <= offset < previous, 'record overlap/bounds')
                raw, previous = a[offset:previous], offset
                if variable:
                    c = Cursor(raw)
                    key = c.string()
                    raw = raw[c.pos:]
            require(last is None or last < key, 'duplicate or unsorted keys')
            last = key
            out.append((key,raw))
        return out

    def tables(self):
        p = self.buffer(0)
        require(p[0] == 9 and p[5] == 1, 'DBParms format')
        n = integer(p,1)
        require(5 <= n <= len(p)-5 and (n-1)%4 == 0, 'DBParms length')
        self.master_root = integer(p,6)
        out = {}
        for key,raw in self.leaf(self.master_root):
            c = Cursor(raw)
            name = c.string()
            t = dict(key=key,version=c.num('i'),root=c.num('i'),keytype=c.num('B'),
                     types=list(c.binary()),fields=c.string(),indexed=c.num('i'),
                     maxkey=c.num('q'),count=c.num('i'))
            c.done()
            if t['indexed'] == -1:
                require(name not in out, 'duplicate master table')
                out[name] = t
        return out

    def rows(self, t):
        records = self.leaf(t['root'],t['keytype'],t['types'])
        require(len(records) == t['count'], 'table record count')
        out = {}
        for key,raw in records:
            c = Cursor(raw)
            out[key] = fields(c,t['types'])
            c.done()
        return out

    def chain(self, root, offset, length, expected):
        a = self.buffer(root)
        size = integer(a,1,'I')
        obfuscated, size = bool(size & 0x80000000), size & 0x7fffffff
        require(size == expected and 0 < size <= MAX_CHAIN, 'chain size')
        require(0 <= offset < size and 0 < length <= size-offset, 'chain read bounds')
        if a[0] == 9:
            require(size <= len(a)-5, 'nonindexed chain overflow')
            children,base,space = [root],5,len(a)-5
        else:
            require(a[0] == 8 and integer(a,5) == -1, 'unsupported/cyclic index chain')
            base,space = 1,len(a)-1
            count = (size+space-1)//space
            require(count <= (len(a)-9)//4, 'index capacity')
            children = [integer(a,9+i*4) for i in range(count)]
            require(root not in children and len(set(children)) == count, 'chain alias/cycle')
            for child in children:
                require(self.buffer(child)[0] == 9, 'invalid/missing chain child')
        out,spans = bytearray(),[]
        remaining = length
        while remaining:
            index,relative = divmod(offset,space)
            child = children[index]
            take = min(remaining,space-relative)
            raw = self.buffer(child)[base+relative:base+relative+take]
            if obfuscated:
                raw = bytes(v ^ XOR_MASK[(relative+i)%128] for i,v in enumerate(raw))
            out.extend(raw)
            spans.append(dict(root_buffer=root,data_buffer=child,chain_offset=offset,
                              data_offset=relative,length=take,obfuscated=obfuscated,
                              physical_offset=(child+1)*self.block+5+base+relative))
            offset += take
            remaining -= take
        return bytes(out),spans

def schema(tables,name,version,keytype,types,names):
    require(name in tables, 'missing table: '+name)
    t = tables[name]
    require((t['version'],t['keytype'],t['types'],t['fields']) ==
            (version,keytype,types,names), 'unsupported schema: '+name)
    return t

def address_start(encoded,image):
    require(0 <= encoded < 1 << 63, 'invalid address encoding')
    kind,space,offset = encoded>>60,(encoded>>32)&0xfffffff,encoded&0xffffffff
    require(kind in (1,2) and space == 0, 'unsupported address space/type')
    return (offset+(image if kind == 2 else 0))&0xffffffff

def data5_mapping(blocks,subs,image):
    """Reject ambiguous, overlapping, partial, or unsupported source mappings."""
    ranges = []
    for key,row in blocks.items():
        name,_,_,_,encoded,length,segment = row
        start = address_start(encoded,image)
        require(segment == 0 and 0 < length <= 0x100000000-start, 'block bounds/segment')
        ranges.append((start,start+length,key,name))
    ranges.sort()
    require(all(a[1] <= b[0] for a,b in zip(ranges,ranges[1:])), 'overlapping memory blocks')
    candidates = [r for r in ranges if r[3] == 'MAIN_.data5']
    require(len(candidates) == 1, 'missing/aliased data5')
    start,end,block_key,name = candidates[0]
    require(start == 0x80436a20 and end-start == 27360, 'data5 bounds mismatch')
    selected = [(k,r) for k,r in subs.items() if r[0] == block_key]
    require(len(selected) == 1, 'subblock overlap/hole or unsupported segmentation')
    subkey,(parent,kind,length,offset,root,source_offset) = selected[0]
    require(kind == 2 and length == end-start and offset == source_offset == 0, 'unsupported subblock mapping')
    return start,end,block_key,name,subkey,length,root

def inspect(data,digest):
    require(digest in SNAPSHOTS and hashlib.sha256(data).hexdigest() == digest,
            'snapshot SHA256 not allowlisted')
    db = GBF(data)
    tables = db.tables()
    program = db.rows(schema(tables,'Program',0,4,[4],'Key;Value;'))
    require(program.get('Program Name') == ['boot.dol'], 'program name mismatch')
    require(program.get('Language ID') == ['PowerPC:BE:32:Gekko_Broadway'], 'language mismatch')
    image_text = program.get('Image Offset',[None])[0]
    require(isinstance(image_text,str) and re.fullmatch(r'(?:0x)?[0-9a-fA-F]{1,8}',image_text), 'image offset')
    image = int(image_text,16)
    props = db.rows(schema(tables,'Property Table',0,4,[4,0],'Property Name;Value;Type;'))
    metadata = props.get('Program Information.Executable SHA256')
    require(metadata == [EXECUTABLE_SHA,2], 'executable metadata SHA/type mismatch')
    created = props.get('Program Information.Created With Ghidra Version')
    require(created == ['12.1.2',2], 'creation version/type mismatch')
    file_bytes = schema(tables,'File Bytes',0,3,[4,3,3,5,5],
                        'Key;Filename;Offset;Size;Chain Buffer IDs;Layered Chain Buffer IDs;')
    require(file_bytes['root'] == -1 and file_bytes['count'] == 0 and
            file_bytes['maxkey'] == -(1 << 63), 'File Bytes table is not empty')
    amap = db.rows(schema(tables,'ADDRESS MAP',1,3,[4,2,6],'Key;Space Name;Segment;Deleted;'))
    require(amap == {0:['ram',0,False]}, 'unsupported address map')
    blocks = db.rows(schema(tables,'Memory Blocks',3,3,[4,4,4,0,3,3,2],
                            'Key;Name;Comments;Source Name;Flags;Start Address;Length;Segment;'))
    subs = db.rows(schema(tables,'Sub Memory Blocks',3,3,[3,0,3,3,2,3],
                         'Key;Parent ID;Type;Length;Starting Offset;Source ID;Source Address/Offset;'))
    start,end,block_key,name,subkey,length,root = data5_mapping(blocks,subs,image)
    contents,spans = db.chain(root,0,length,length)
    data_hash = hashlib.sha256(contents).hexdigest()
    require(data_hash == DATA5_SHA, 'data5 digest mismatch')
    results = []
    for address,width in TARGETS:
        require(width in (4,8) and start <= address and address+width <= end, 'target width/bounds')
        raw,trace = db.chain(root,address-start,width,length)
        value = struct.unpack('>f' if width == 4 else '>d',raw)[0]
        require(math.isfinite(value), 'nonfinite target')
        if address in CONTROLS:
            require(raw.hex() == CONTROLS[address], 'known control mismatch')
        if address in EXPECTED_TARGETS:
            require(raw.hex() == EXPECTED_TARGETS[address], 'expected target mismatch')
        results.append(dict(address=f'{address:08x}',type='f32' if width == 4 else 'f64',
                            bytes=raw.hex(),number=value,control=address in CONTROLS,spans=trace))
    return dict(snapshot=SNAPSHOTS[digest],snapshot_sha256=digest,
                program_name=program['Program Name'][0],
                created_with_ghidra_version=created[0],
                executable_sha256_metadata=metadata[0],
                executable_sha256_property_type=metadata[1],
                file_bytes_table={k:file_bytes[k] for k in ('version','root','count')},
                executable_metadata_caveat='Import metadata is not proof of unchanged original executable bytes.',
                block_size=db.block,master_root=db.master_root,
                table_roots={n:tables[n]['root'] for n in ('Program','Property Table','ADDRESS MAP','Memory Blocks','Sub Memory Blocks','File Bytes')},
                image_offset=f'{image:08x}',block_name=name,block_key=block_key,
                block_start=f'{start:08x}',block_length=length,subblock_key=subkey,
                data5_sha256=data_hash,data5_spans=spans,results=results)

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('snapshot',type=Path)
    args = parser.parse_args()
    try:
        require(args.snapshot.is_file(), 'snapshot is not a regular file')
        with args.snapshot.open('rb') as stream:
            require(32 <= args.snapshot.stat().st_size <= MAX_FILE, 'file size bounds')
            data = stream.read(MAX_FILE+1)
        require(len(data) <= MAX_FILE, 'file exceeds bound')
        digest = hashlib.sha256(data).hexdigest()
        print(json.dumps(inspect(data,digest),indent=2,allow_nan=False))
    except (OSError,FormatError) as exc:
        print(json.dumps({'error':str(exc)}),file=sys.stderr)
        return 1
    return 0

if __name__ == '__main__':
    sys.exit(main())
