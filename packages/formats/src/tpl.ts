// tpl.ts — TPL standard GameCube texture-palette parser.
// Status: standard GC format; should yield to generic tooling. Big-endian, TPL header,
// None/CMPR compression. Decode to RGBA, then convert PNG -> KTX2 offline for KTX2Loader.
// TODO: implement decode(buf) -> { width, height, rgba }[].
export {};
