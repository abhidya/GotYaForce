// afs.ts — AFS top-level CRI archive parser.
// Status: SOLVED upstream (NeoGF afstool / RenolY2 / AFSPacker). Magic `AFS\0`.
// NOTE: the AFS TOC is commonly LITTLE-endian — verify per file (members may be BE).
// TODO: implement unpack(buf) -> members[]; repack(members) -> buf.
export {};
