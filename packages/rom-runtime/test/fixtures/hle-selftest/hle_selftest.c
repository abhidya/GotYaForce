/* hle_selftest.c -- HAND-WRITTEN ROM-shaped call sequences for the audio/DVD
 * HLE host's browser proof, leg one.
 *
 * WHAT THIS IS, and how it differs from ../hle-rom-unit/rom.c. That file is
 * the ROM's own decompiled code. THIS file is not: a human wrote it, choosing
 * call sequences that match what the ROM's file driver does, so that parts of
 * the surface the ROM unit does not reach can still be driven across the real
 * bridge. It proves the SEAM, never the game.
 *
 * The sequences below are modelled on:
 *   * `zz_0274dd4_` @0x80274dd4 (gcCiRead) -- the game's own read driver:
 *     DVDReadAsyncPrio/DVDReadPrio into a 32-byte-rounded buffer, then poll
 *     DVDGetCommandBlockStatus until it reads 0.
 *   * `zz_0274c34_` @0x80274c34 -- the same driver's cancel/close path.
 * Neither is transcribed; both are 200-line functions with a 40-slot handle
 * table, and reproducing them by hand would be a copy with a human in the
 * middle, which is exactly the thing the ROM unit exists to avoid claiming.
 */

typedef unsigned int uint;

#define GHOST8                                                                        \
  unsigned int f1, unsigned int f2, unsigned int f3, unsigned int f4, unsigned int f5, \
      unsigned int f6, unsigned int f7, unsigned int f8

/* [CORPUS] prototypes, argument for argument, from the decompiled bodies.
 * The eight leading ghosts are the PowerPC float-register slots Ghidra
 * surfaces; see ../hle-rom-unit/gnt4_decls.h for why they are kept. */
extern int gnt4_DVDOpen_bl(GHOST8, char *path, int fileInfo, uint p11, uint p12, uint p13, uint p14,
                           uint p15, uint p16);
extern int gnt4_DVDClose_bl(int *fileInfo);
extern int gnt4_DVDReadPrio_bl(GHOST8, int *fileInfo, int addr, int length, uint offset, int prio,
                               uint p14, uint p15, uint p16);
extern int gnt4_DVDReadAbsAsyncPrio_bl(int *block, int addr, int length, uint offset, int callback,
                                       int prio);
extern int gnt4_DVDGetCommandBlockStatus_bl(int block);
extern int gnt4_DVDGetDriveStatus_bl(void);
extern int gnt4_DVDCheckDisk_bl(void);
extern int gnt4_DVDInquiryAsync_bl(int *block, int addr, int callback);
extern int gnt4_OSGetSoundMode_bl(void);
extern void gnt4_OSSetSoundMode_bl(int mode);
extern void gnt4___OSInitAudioSystem_bl(void);
extern void gnt4___OSStopAudioSystem_bl(void);

/* The AI/DSP register lowering; see ../hle-rom-unit/gf_hw_mmio.h. */
extern unsigned int __gf_mmio_load_u16(unsigned int addr);
extern unsigned int __gf_mmio_load_u32(unsigned int addr);
extern void __gf_mmio_store_u16(unsigned int addr, unsigned int value);
extern void __gf_mmio_store_u32(unsigned int addr, unsigned int value);

/* ------------------------------------------------------------------------- */

static int g_callback_hits = 0;
static int g_callback_result = -1;
static int g_callback_block = 0;

/* The completion callback the ROM would register. Its ADDRESS is what goes
 * into the command block's +0x28 word, and the host queues it there. */
static void read_done(int result, int block) {
  g_callback_hits += 1;
  g_callback_result = result;
  g_callback_block = block;
}

/* The address of that callback, as a value the host can put in a block. In
 * wasm a function pointer is a table index, which is exactly the shape a
 * dispatch-companion thunk expects. */
int hle_callback_ptr(void) { return (int)(unsigned int)(void *)&read_done; }

int hle_callback_hits(void) { return g_callback_hits; }
int hle_callback_result(void) { return g_callback_result; }
int hle_callback_block(void) { return g_callback_block; }

/* The dispatch thunk the HOST invokes at a park point to deliver a queued
 * completion. This is the invoke-request half of design R3: the host never
 * calls a ROM function pointer itself, it asks the parked worker to, so the
 * callback runs on the module's own stack. */
void hle_deliver_callback(int callback, int result, int block) {
  ((void (*)(int, int))(unsigned int)callback)(result, block);
}

/* ------------------------------------------------------------------------- */

/* Open, read, close -- the shape `zz_0274dd4_` uses, minus its handle table.
 * `fileInfo` and `dest` are GC addresses the caller supplies. Returns the byte
 * count DVDReadPrio reported, or a negative error. */
int hle_dvd_open_read_close(int path, int fileInfo, int dest, int length) {
  int opened;
  int got;
  opened = gnt4_DVDOpen_bl(0, 0, 0, 0, 0, 0, 0, 0, (char *)(unsigned int)path, fileInfo, 0, 0, 0, 0, 0, 0);
  if (opened == 0) {
    return -1;
  }
  got = gnt4_DVDReadPrio_bl(0, 0, 0, 0, 0, 0, 0, 0, (int *)(unsigned int)fileInfo, dest, length, 0, 2, 0, 0, 0);
  /* [CORPUS] the driver polls until the block reports 0. */
  while (gnt4_DVDGetCommandBlockStatus_bl(fileInfo) != 0) {
    if (gnt4_DVDCheckDisk_bl() == 0) {
      return -2;
    }
  }
  gnt4_DVDClose_bl((int *)(unsigned int)fileInfo);
  return got;
}

/* The absolute async read, with a real completion callback. */
int hle_dvd_abs_read(int block, int dest, int length, uint offset, int callback) {
  int queued = gnt4_DVDReadAbsAsyncPrio_bl((int *)(unsigned int)block, dest, length, offset, callback, 0);
  if (queued == 0) {
    return -1;
  }
  while (gnt4_DVDGetCommandBlockStatus_bl(block) != 0) {
    if (gnt4_DVDGetDriveStatus_bl() < 0) {
      return -2;
    }
  }
  return *(int *)(unsigned int)(block + 0x20); /* [CORPUS] cb+0x20 = transferred */
}

/* Deliberately reach an entry point the host does NOT implement, so the loud
 * failure can be asserted rather than assumed. [CORPUS] `gnt4_DVDInquiryAsync_bl`
 * has one static game call site and no adapter. */
int hle_dvd_call_unimplemented(int block, int dest) {
  return gnt4_DVDInquiryAsync_bl((int *)(unsigned int)block, dest, 0);
}

/* ------------------------------------------------------------------------- */

/* The audio bring-up sequence, in the register order the ROM's own AIInit
 * performs: select the 32 kHz DSP rate (AICR bit 6 clear), zero both volume
 * fields, zero the interrupt-timing register. */
void hle_audio_init(void) {
  unsigned int cr;
  gnt4___OSInitAudioSystem_bl();
  cr = __gf_mmio_load_u32(0xcc006c00);
  __gf_mmio_store_u32(0xcc006c00, (cr & 0xffffffdf) | 0x20);
  __gf_mmio_store_u32(0xcc006c04, 0);
  __gf_mmio_store_u32(0xcc006c0c, 0);
  cr = __gf_mmio_load_u32(0xcc006c00);
  __gf_mmio_store_u32(0xcc006c00, cr & ~0x40u); /* DSPFR = 0 -> 32 kHz */
}

/* Set both volume fields. [CORPUS] AIVR bits 0-7 left, bits 8-15 right. */
void hle_audio_set_volume(uint left, uint right) {
  unsigned int v = __gf_mmio_load_u32(0xcc006c04);
  v = (v & 0xffffff00u) | (left & 0xff);
  v = (v & 0xffff00ffu) | ((right & 0xff) << 8);
  __gf_mmio_store_u32(0xcc006c04, v);
}

int hle_audio_play_state(void) { return (int)(__gf_mmio_load_u32(0xcc006c00) & 1); }

int hle_audio_sample_counter(void) { return (int)__gf_mmio_load_u32(0xcc006c08); }

/* Post one MusyX-shaped command word to the DSP mailbox and spin until the
 * (absent) DSP reports it consumed -- the exact loop `zz_0217dd8_` runs before
 * every audio frame. If the host modelled the mailbox wrongly this hangs, so
 * the assertion is that it returns at all. */
int hle_dsp_post(unsigned int word) {
  int spins = 0;
  __gf_mmio_store_u16(0xcc005000, word >> 16);
  __gf_mmio_store_u16(0xcc005002, word & 0xffff);
  while ((__gf_mmio_load_u16(0xcc005000) >> 15) != 0) {
    spins += 1;
    if (spins > 1000) {
      return -1;
    }
  }
  return spins;
}

void hle_audio_stop(void) { gnt4___OSStopAudioSystem_bl(); }

int hle_sound_mode(void) {
  int mode = gnt4_OSGetSoundMode_bl();
  gnt4_OSSetSoundMode_bl(mode);
  return mode;
}
