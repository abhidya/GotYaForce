// pzz.ts — PZZ archive parser (GF archive of members; member `000` mirrors borg data).
// Status: SOLVED upstream (NeoGF pzztool). Big-endian; size table header. Central entry
// point for borg data + models. Port pzztool's unpack/repack (incl. per-member ARZ).
// TODO: implement unpack(buf) -> members[]; repack(members) -> buf.
export {};
