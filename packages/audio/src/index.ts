export type AudioCueType = "bgm" | "sfx" | "voice";

export interface AudioManifestEntry {
  key: string;
  type: AudioCueType;
  path: string;
  durationSec?: number;
  loop?: boolean;
  cue?: string;
  cues?: string[];
}

export interface AudioManifest {
  files: AudioManifestEntry[];
}

export interface AudioManagerOptions {
  manifestUrl?: string;
  manifest?: AudioManifest;
  baseUrl?: string;
  muted?: boolean;
  volumes?: Partial<AudioVolumes>;
}

export interface AudioVolumes {
  master: number;
  bgm: number;
  sfx: number;
  voice: number;
}

const DEFAULT_MANIFEST_URL = "/audio/manifest.json";
const DEFAULT_VOLUMES: AudioVolumes = {
  master: 1,
  bgm: 0.8,
  sfx: 1,
  voice: 1,
};

export class GotchaAudioManager {
  readonly manifest: AudioManifest;

  private readonly baseUrl: string;
  private readonly bgm = new Map<string, AudioManifestEntry>();
  private readonly sfx = new Map<string, AudioManifestEntry>();
  private readonly voice = new Map<string, AudioManifestEntry>();
  private readonly activeSfx = new Set<HTMLAudioElement>();
  private currentBgm: HTMLAudioElement | undefined;
  private muted: boolean;
  private volumes: AudioVolumes;

  private constructor(options: Required<Pick<AudioManagerOptions, "manifest" | "baseUrl" | "muted">> & {
    volumes: AudioVolumes;
  }) {
    this.manifest = options.manifest;
    this.baseUrl = options.baseUrl;
    this.muted = options.muted;
    this.volumes = options.volumes;
    this.indexManifest(options.manifest);
  }

  static async create(options: AudioManagerOptions = {}): Promise<GotchaAudioManager> {
    const manifest = options.manifest ?? (await loadAudioManifest(options.manifestUrl ?? DEFAULT_MANIFEST_URL));
    const baseUrl = options.baseUrl ?? getDefaultBaseUrl();
    const muted = options.muted ?? false;
    const volumes = { ...DEFAULT_VOLUMES, ...options.volumes };

    return new GotchaAudioManager({ manifest, baseUrl, muted, volumes });
  }

  async playBgm(key: string): Promise<void> {
    const entry = this.bgm.get(key);
    if (!entry) {
      throw new Error(`Unknown BGM cue: ${key}`);
    }

    this.stopBgm();

    const audio = this.createElement(entry, this.volumes.bgm);
    audio.loop = entry.loop ?? true;
    this.currentBgm = audio;
    try {
      await audio.play();
    } catch (error) {
      if (this.currentBgm === audio) {
        this.stopBgm();
      }
      throw error;
    }
  }

  stopBgm(): void {
    if (!this.currentBgm) {
      return;
    }

    this.currentBgm.pause();
    this.currentBgm.currentTime = 0;
    this.currentBgm.src = "";
    this.currentBgm.load();
    this.currentBgm = undefined;
  }

  async playSfx(key: string): Promise<HTMLAudioElement> {
    const entry = this.sfx.get(key) ?? this.voice.get(key);
    if (!entry) {
      throw new Error(`Unknown SFX cue: ${key}`);
    }

    const typeVolume = entry.type === "voice" ? this.volumes.voice : this.volumes.sfx;
    const audio = this.createElement(entry, typeVolume);
    audio.loop = false;
    this.activeSfx.add(audio);
    audio.addEventListener("ended", () => this.activeSfx.delete(audio), { once: true });
    try {
      await audio.play();
    } catch (error) {
      this.activeSfx.delete(audio);
      audio.src = "";
      audio.load();
      throw error;
    }
    return audio;
  }

  setMuted(muted: boolean): void {
    this.muted = muted;
    if (this.currentBgm) {
      this.currentBgm.muted = muted;
    }
    for (const audio of this.activeSfx) {
      audio.muted = muted;
    }
  }

  setVolumes(volumes: Partial<AudioVolumes>): void {
    this.volumes = { ...this.volumes, ...volumes };
    if (this.currentBgm) {
      this.currentBgm.volume = this.resolveVolume(this.volumes.bgm);
    }
    for (const audio of this.activeSfx) {
      const cueType = audio.dataset["gfAudioType"];
      const typeVolume = cueType === "voice" ? this.volumes.voice : this.volumes.sfx;
      audio.volume = this.resolveVolume(typeVolume);
    }
  }

  dispose(): void {
    this.stopBgm();
    for (const audio of this.activeSfx) {
      audio.pause();
      audio.src = "";
      audio.load();
    }
    this.activeSfx.clear();
  }

  private indexManifest(manifest: AudioManifest): void {
    for (const entry of manifest.files) {
      const map = this.mapForType(entry.type);
      if (!map) {
        continue;
      }

      map.set(entry.key, entry);
      if (entry.cue) {
        map.set(entry.cue, entry);
      }
      for (const cue of entry.cues ?? []) {
        map.set(cue, entry);
      }
    }
  }

  private mapForType(type: AudioCueType): Map<string, AudioManifestEntry> | undefined {
    switch (type) {
      case "bgm":
        return this.bgm;
      case "sfx":
        return this.sfx;
      case "voice":
        return this.voice;
    }
  }

  private createElement(entry: AudioManifestEntry, typeVolume: number): HTMLAudioElement {
    const audio = new Audio(this.resolveUrl(entry.path));
    audio.preload = "auto";
    audio.muted = this.muted;
    audio.volume = this.resolveVolume(typeVolume);
    audio.dataset["gfAudioKey"] = entry.key;
    audio.dataset["gfAudioType"] = entry.type;
    return audio;
  }

  private resolveUrl(path: string): string {
    return new URL(path, this.baseUrl).toString();
  }

  private resolveVolume(typeVolume: number): number {
    return clampVolume(this.volumes.master * typeVolume);
  }
}

export async function createAudioManager(options: AudioManagerOptions = {}): Promise<GotchaAudioManager> {
  return GotchaAudioManager.create(options);
}

export async function loadAudioManifest(url = DEFAULT_MANIFEST_URL): Promise<AudioManifest> {
  const response = await fetch(url);
  if (!response.ok) {
    throw new Error(`Failed to load audio manifest ${url}: ${response.status} ${response.statusText}`);
  }
  return (await response.json()) as AudioManifest;
}

function getDefaultBaseUrl(): string {
  if (typeof document !== "undefined") {
    return document.baseURI;
  }
  if (typeof location !== "undefined") {
    return location.href;
  }
  return "http://localhost/";
}

function clampVolume(value: number): number {
  if (!Number.isFinite(value)) {
    return 1;
  }
  return Math.min(1, Math.max(0, value));
}
