"""Synthetic-only GBF fixtures. No archived game bytes or Ghidra runtime needed."""
import hashlib
import struct
import unittest
import read_archived_constants as m

B = 256
N = B - 5

def pack(fmt,*values):
    return struct.pack('>'+fmt,*values)

def string(value):
    raw = value.encode()
    return pack('i',len(raw))+raw

def gbf(nodes,free=-1):
    header = pack('QQiiii',0x2f30312c34292c2a,7,1,B,free,0)
    return header.ljust(B,b'\0')+b''.join((pack('Bi',0,i)+bytes(n).ljust(N,b'\0')) for i,n in enumerate(nodes))

def leaf(rows,variable=False):
    out = bytearray(N)
    header = 14 if variable else 13
    out[:header] = pack('BBiii',4,4,len(rows),-1,-1) if variable else pack('Biii',1,len(rows),-1,-1)
    end = N
    for j,(key,record) in enumerate(rows):
        raw = string(key)+record if variable else record
        end -= len(raw)
        out[end:end+len(raw)] = raw
        entry = pack('iB',end,0) if variable else pack('qiB',key,end,0)
        offset = header+j*len(entry)
        out[offset:offset+len(entry)] = entry
    return out

def fixed(rows):
    return pack('Biii',2,len(rows),-1,-1)+b''.join(pack('qqbqqiq',*row) for row in rows)

def chain_nodes(payload,obfuscated=True,indexed=True):
    size = len(payload)|(0x80000000 if obfuscated else 0)
    if not indexed:
        raw = bytes(v^m.XOR_MASK[i%128] for i,v in enumerate(payload)) if obfuscated else payload
        return [pack('BI',9,size)+raw]
    chunks = [payload[i:i+N-1] for i in range(0,len(payload),N-1)]
    root = pack('BIi',8,size,-1)+b''.join(pack('i',i+1) for i in range(len(chunks)))
    children = []
    for chunk in chunks:
        # Explicitly restart the mask at EACH child, not at logical stream offset.
        children.append(b'\x09'+(bytes(v^m.XOR_MASK[i%128] for i,v in enumerate(chunk)) if obfuscated else chunk))
    return [root]+children

class ReaderTests(unittest.TestCase):
    def test_big_endian_and_cursor_bounds(self):
        self.assertEqual(m.integer(bytes.fromhex('01020304'),0),0x01020304)
        for raw in (b'',b'\x00\x00\x00\x03ab',pack('i',-2)):
            with self.assertRaises(m.FormatError):
                m.Cursor(raw).string()
        with self.assertRaises(m.FormatError):
            m.Cursor(pack('i',1)+b'\xff').string()
        self.assertEqual(m.fields(m.Cursor(pack('i',-1)),[4]),[None])
        with self.assertRaises(m.FormatError):
            m.fields(m.Cursor(b'\2'),[6])

    def test_header_guards(self):
        valid = gbf([b'\0'])
        for offset,fmt,value in [(0,'Q',0),(16,'i',2),(20,'i',0),(28,'i',-1),(B+1,'i',2),(B,'B',1)]:
            data = bytearray(valid)
            struct.pack_into('>'+fmt,data,offset,value)
            with self.subTest(offset=offset),self.assertRaises(m.FormatError):
                m.GBF(data)
        with self.assertRaises(m.FormatError):
            m.GBF(valid[:-1])

    def test_free_buffers_and_cycle(self):
        data = bytearray(gbf([b''],free=0))
        data[B:B+5] = pack('Bi',1,-1)
        db = m.GBF(data)
        with self.assertRaises(m.FormatError):
            db.buffer(0)
        data[B:B+5] = pack('Bi',1,0)
        with self.assertRaises(m.FormatError):
            m.GBF(data)

    def test_inline_long_and_variable_keys(self):
        db = m.GBF(gbf([leaf([(1,string('first')),(2,string('second'))]),
                           leaf([('Image Offset',string('80000000'))],True)]))
        self.assertEqual(db.rows(dict(root=0,keytype=3,types=[4],count=2)),{1:['first'],2:['second']})
        self.assertEqual(db.rows(dict(root=1,keytype=4,types=[4],count=1)),{'Image Offset':['80000000']})

    def test_leaf_guards(self):
        base = leaf([(1,string('x')),(2,string('y'))])
        for pos,fmt,value in [(0,'B',0),(1,'i',10000),(5,'i',0),(21,'i',1),(25,'B',1),(26,'q',1)]:
            node = bytearray(base)
            struct.pack_into('>'+fmt,node,pos,value)
            with self.subTest(pos=pos),self.assertRaises(m.FormatError):
                m.GBF(gbf([node])).leaf(0)

    def test_fixed_subblock_record(self):
        row = (7,7,2,300,0,4,0)
        db = m.GBF(gbf([fixed([row])]))
        self.assertEqual(db.rows(dict(root=0,keytype=3,types=[3,0,3,3,2,3],count=1)),{7:list(row[1:])})

    def test_master_schema_and_parms(self):
        record = (string('Program')+pack('iiB',0,2,4)+pack('i',1)+b'\4'+
                  string('Key;Value;')+pack('iqi',-1,-(1<<63),1))
        parms = pack('BIBi',9,5,1,1)
        db = m.GBF(gbf([parms,leaf([(0,record)]),leaf([('Image Offset',string('80000000'))],True)]))
        tables = db.tables()
        t = m.schema(tables,'Program',0,4,[4],'Key;Value;')
        self.assertEqual(db.rows(t),{'Image Offset':['80000000']})
        with self.assertRaises(m.FormatError):
            m.schema(tables,'Program',1,4,[4],'Key;Value;')
        for bad in (pack('BIBi',8,5,1,1),pack('BIBi',9,6,1,1),pack('BIBi',9,5,2,1)):
            with self.assertRaises(m.FormatError):
                m.GBF(gbf([bad,leaf([(0,record)])])).tables()

    def test_indexed_xor_restarts_and_physical_offsets(self):
        payload = bytes(i%251 for i in range(400))
        for obfuscated in (False,True):
            db = m.GBF(gbf(chain_nodes(payload,obfuscated)))
            raw,spans = db.chain(0,245,20,400)
            self.assertEqual(raw,payload[245:265])
            self.assertEqual([s['length'] for s in spans],[5,15])
            self.assertEqual([s['physical_offset'] for s in spans],[2*B+6+245,3*B+6])
            self.assertEqual(db.chain(0,0,400,400)[0],payload)

    def test_nonindexed_xor(self):
        payload = pack('fd',5.0,-1.0)
        for obfuscated in (False,True):
            db = m.GBF(gbf(chain_nodes(payload,obfuscated,False)))
            self.assertEqual(db.chain(0,0,len(payload),len(payload))[0],payload)
            self.assertEqual(struct.unpack('>f',db.chain(0,0,4,12)[0])[0],5.0)

    def test_chain_guards(self):
        nodes = chain_nodes(bytes(400))
        for pos,value in [(5,0),(9,-1),(9,0),(13,1),(13,999)]:
            modified = list(nodes)
            root = bytearray(modified[0])
            struct.pack_into('>i',root,pos,value)
            modified[0] = root
            with self.subTest(pos=pos,value=value),self.assertRaises(m.FormatError):
                m.GBF(gbf(modified)).chain(0,0,4,400)
        db = m.GBF(gbf(nodes))
        for offset,length,expected in [(-1,4,400),(399,2,400),(0,0,400),(0,4,401)]:
            with self.assertRaises(m.FormatError):
                db.chain(0,offset,length,expected)
        with self.assertRaises(m.FormatError):
            m.GBF(gbf([pack('BI',9,400)])).chain(0,0,4,400)

    def test_address_mapping(self):
        self.assertEqual(m.address_start(0x2000000000436a20,0x80000000),0x80436a20)
        self.assertEqual(m.address_start(0x1000000080436a20,0x80000000),0x80436a20)
        for encoded in (-1,0,0x2000000100000000,0x3000000000000000):
            with self.assertRaises(m.FormatError):
                m.address_start(encoded,0x80000000)

    def test_data5_mapping_rejects_holes_aliases_and_wrong_types(self):
        block = ['MAIN_.data5',None,None,0,0x2000000000436a20,27360,0]
        sub = [7,2,27360,0,263,0]
        self.assertEqual(m.data5_mapping({7:block},{7:sub},0x80000000)[-1],263)
        bad_subs = [dict(),{7:sub,8:sub}]
        for index,value in [(0,9),(1,1),(2,27359),(3,1),(5,1)]:
            changed = list(sub)
            changed[index] = value
            bad_subs.append({7:changed})
        for subs in bad_subs:
            with self.subTest(subs=subs),self.assertRaises(m.FormatError):
                m.data5_mapping({7:block},subs,0x80000000)
        with self.assertRaises(m.FormatError):
            m.data5_mapping({7:block,8:list(block)},{7:sub},0x80000000)
        changed = list(block)
        changed[6] = 1
        with self.assertRaises(m.FormatError):
            m.data5_mapping({7:changed},{7:sub},0x80000000)

    def test_synthetic_signed16_concat44_conversion(self):
        # Exhaustive synthetic arithmetic regression, not execution of the game
        # or independent proof of original bytes. The CLI recovers the constant.
        constant = struct.unpack('>d',bytes.fromhex('4330000080000000'))[0]
        for n in range(-32768,32768):
            low = (n & 0xffffffff) ^ 0x80000000
            concatenated = struct.unpack('>d',pack('II',0x43300000,low))[0]
            converted = concatenated - constant
            self.assertEqual(converted,n)
            narrowed = struct.unpack('>f',pack('f',converted))[0]
            self.assertEqual(narrowed,n)

    def test_unsigned_byte_concat44_conversion(self):
        # Exhaustive arithmetic check, not execution or independent DOL proof.
        constant = struct.unpack('>d',bytes.fromhex('4330000000000000'))[0]
        self.assertEqual(constant,2**52)
        for n in range(256):
            concatenated = struct.unpack('>d',pack('II',0x43300000,n))[0]
            converted = concatenated - constant
            self.assertEqual(converted,n)
            self.assertEqual(struct.unpack('>f',pack('f',converted))[0],n)

    def test_unsigned_bias_is_separate_from_independent_controls(self):
        self.assertEqual(len(m.TARGETS),12)
        self.assertIn((0x80437140,8),m.TARGETS)
        self.assertEqual(m.EXPECTED_TARGETS[0x80437140],'4330000000000000')
        self.assertNotIn(0x80437140,m.CONTROLS)
        self.assertEqual(m.CONTROLS,{0x8043d1f8:'00000000',0x804374e4:'40000000',
                                     0x804374b0:'40a00000',0x80437464:'bf800000'})

    def test_snapshot_authentication_before_parsing(self):
        data = gbf([b''])
        with self.assertRaisesRegex(m.FormatError,'not allowlisted'):
            m.inspect(data,hashlib.sha256(data).hexdigest())
        with self.assertRaisesRegex(m.FormatError,'not allowlisted'):
            m.inspect(data,next(iter(m.SNAPSHOTS)))

if __name__ == '__main__':
    unittest.main()
