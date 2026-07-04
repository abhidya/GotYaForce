import { hitBin } from "@gf/formats";
import {
  stageCollisionFromHitGrids,
  type RectStageBounds,
  type StageCollision,
  type StageCollisionLayer,
} from "@gf/physics";

export interface BorgAssetEntry {
  id: string;
  name: string;
  energy: number;
  speed?: number;
  tribe?: string;
  type?: string;
  hp?: string;
  defense?: number;
  shot?: number;
  attack?: number;
  jump?: string;
  hasModel?: boolean;
  model?: string | null;
}

export type BorgRosterData = readonly BorgAssetEntry[] | { borgs: readonly BorgAssetEntry[] };

export interface BorgForceEntry {
  id: string;
  name: string;
  energy: number;
}

export interface BorgRosterQuery {
  ids?: readonly string[];
  tribe?: string;
  type?: string;
  hasModel?: boolean;
}

export interface BorgRoster {
  entries: readonly BorgAssetEntry[];
  ids: readonly string[];
  byId: ReadonlyMap<string, BorgAssetEntry>;
  get(id: string): BorgAssetEntry | null;
  require(id: string): BorgAssetEntry;
  has(id: string): boolean;
  select(query?: BorgRosterQuery): readonly BorgAssetEntry[];
  forceCatalog(query?: BorgRosterQuery): readonly BorgForceEntry[];
  entriesForIds(ids: readonly string[]): readonly BorgAssetEntry[];
  validIds(ids: readonly string[], options?: { fallbackId?: string }): string[];
  energyFor(ids: readonly string[]): number;
}

export interface ModelManifestEntry {
  id: string;
  name: string;
  glb: string;
}

export interface StageManifestModel {
  path: string;
}

export interface StageManifest {
  id?: string;
  models?: StageManifestModel[];
  visual?: {
    glbCount?: number;
    expectedGlbIndices?: number[];
  };
  collision?: Array<{ path: string }>;
}

export interface UiSceneManifestEntry {
  id?: string;
  modelFiles?: Array<{ publicPath?: string }>;
}

export interface UiSceneManifest {
  assets?: UiSceneManifestEntry[];
}

export interface PublicAssetCatalogOptions {
  baseUrl?: string;
  fetchJson?: <T>(url: string) => Promise<T>;
  fetchArrayBuffer?: (url: string) => Promise<ArrayBuffer>;
}

export interface PublicAssetCatalog {
  loadModelManifest(): Promise<ModelManifestEntry[]>;
  loadModelLibraryPaths(): Promise<ReadonlyMap<string, string>>;
  loadStageManifest(stageId: string): Promise<StageManifest>;
  loadStageRenderState<T>(stageId: string): Promise<T>;
  loadStageAssets<T = unknown>(stageId: string): Promise<StageAssets<T>>;
  loadUiSceneManifest(): Promise<UiSceneManifest>;
  loadUiSceneModelPaths(sceneId: string, options?: { maxModels?: number }): Promise<string[]>;
  stageAssetUrl(stageId: string, path: string): string;
  uiAssetUrl(path: string): string;
}

export interface StageAssets<T = unknown> {
  stageId: string;
  manifest: StageManifest;
  renderState: T;
  modelUrls: string[];
  collisionFiles: string[];
  bounds?: RectStageBounds;
  collision?: StageCollision;
}

export function readBorgRoster(data: BorgRosterData): readonly BorgAssetEntry[] {
  return createBorgRoster(data).entries;
}

export function createBorgRoster(data: BorgRosterData): BorgRoster {
  const entries = ("borgs" in data ? data.borgs : data).filter((b) => b.id.trim() !== "" && b.name.trim() !== "");
  const byId = new Map<string, BorgAssetEntry>();
  for (const borg of entries) {
    if (!byId.has(borg.id)) byId.set(borg.id, borg);
  }
  const ids = entries.map((borg) => borg.id);

  const get = (id: string): BorgAssetEntry | null => byId.get(id) ?? null;
  const has = (id: string): boolean => byId.has(id);
  const select = (query: BorgRosterQuery = {}): readonly BorgAssetEntry[] => {
    const source = query.ids === undefined ? entries : query.ids.map((id) => get(id)).filter(isBorgEntry);
    return source.filter((borg) => matchesBorgQuery(borg, query));
  };

  return {
    entries,
    ids,
    byId,
    get,
    require(id: string) {
      const borg = get(id);
      if (!borg) throw new Error(`Unknown borg id: ${id}`);
      return borg;
    },
    has,
    select,
    forceCatalog(query?: BorgRosterQuery) {
      return select(query)
        .map((borg) => ({ id: borg.id, name: borg.name, energy: borg.energy }))
        .sort(
          (a, b) =>
            (get(a.id)?.tribe ?? "").localeCompare(get(b.id)?.tribe ?? "") ||
            a.energy - b.energy ||
            a.name.localeCompare(b.name),
        );
    },
    entriesForIds(inputIds: readonly string[]) {
      return inputIds.map((id) => get(id)).filter(isBorgEntry);
    },
    validIds(inputIds: readonly string[], options: { fallbackId?: string } = {}) {
      const valid = inputIds.filter((id) => has(id));
      if (valid.length > 0) return valid;
      return options.fallbackId && has(options.fallbackId) ? [options.fallbackId] : [];
    },
    energyFor(inputIds: readonly string[]) {
      return inputIds.reduce((total, id) => total + (get(id)?.energy ?? 0), 0);
    },
  };
}

function isBorgEntry(value: BorgAssetEntry | null): value is BorgAssetEntry {
  return value !== null;
}

function matchesBorgQuery(borg: BorgAssetEntry, query: BorgRosterQuery): boolean {
  if (query.tribe !== undefined && borg.tribe !== query.tribe) return false;
  if (query.type !== undefined && borg.type !== query.type) return false;
  if (query.hasModel !== undefined && (borg.hasModel === true || Boolean(borg.model)) !== query.hasModel) return false;
  return true;
}

export function createPublicAssetCatalog(options: PublicAssetCatalogOptions = {}): PublicAssetCatalog {
  const baseUrl = options.baseUrl ?? defaultBaseUrl();
  const fetchJson = options.fetchJson ?? defaultFetchJson;
  const fetchArrayBuffer = options.fetchArrayBuffer ?? defaultFetchArrayBuffer;
  const url = (path: string): string => new URL(path, baseUrl).toString();
  const stageAssetUrl = (stageId: string, assetPath: string): string => url(`/stages/${stageId}/${assetPath}`);

  return {
    loadModelManifest() {
      return fetchJson<ModelManifestEntry[]>(url("/models/library/manifest.json"));
    },
    async loadModelLibraryPaths() {
      const entries = await this.loadModelManifest();
      const byId = new Map<string, string>();
      for (const entry of Array.isArray(entries) ? entries : []) {
        if (!entry.id || !entry.glb) throw new Error(`Model library entry is missing GLB: ${JSON.stringify(entry)}`);
        byId.set(entry.id, url(`/models/library/${entry.id}/${entry.glb}`));
      }
      return byId;
    },
    loadStageManifest(stageId: string) {
      return fetchJson<StageManifest>(url(`/stages/${stageId}/manifest.json`));
    },
    loadStageRenderState<T>(stageId: string) {
      return fetchJson<T>(url(`/stages/${stageId}/render-state.json`));
    },
    async loadStageAssets<T = unknown>(stageId: string) {
      const [manifest, renderState] = await Promise.all([
        this.loadStageManifest(stageId),
        this.loadStageRenderState<T>(stageId),
      ]);
      const modelUrls = stageModelPaths(manifest).map((path) => stageAssetUrl(stageId, path));
      const collision = await loadStageCollision(stageId, manifest, {
        fetchArrayBuffer,
        loadStageManifest: this.loadStageManifest.bind(this),
        stageAssetUrl,
      });
      return {
        stageId,
        manifest,
        renderState,
        modelUrls,
        collisionFiles: [...(manifest.collision ?? [])]
          .map((file) => file.path)
          .sort((a, b) => a.localeCompare(b)),
        ...(collision.bounds ? { bounds: collision.bounds } : {}),
        ...(collision.collision ? { collision: collision.collision } : {}),
      };
    },
    loadUiSceneManifest() {
      return fetchJson<UiSceneManifest>(url("/ui/scenes/manifest.json"));
    },
    async loadUiSceneModelPaths(sceneId: string, options: { maxModels?: number } = {}) {
      const manifest = await this.loadUiSceneManifest();
      const paths =
        manifest.assets
          ?.find((asset) => asset.id === sceneId)
          ?.modelFiles?.map((file) => file.publicPath)
          .filter((path): path is string => Boolean(path)) ?? [];
      const limited = options.maxModels === undefined ? paths : paths.slice(0, options.maxModels);
      if (limited.length === 0) throw new Error(`UI scene manifest has no model files for ${sceneId}`);
      return assertGlbPaths(limited, `UI scene ${sceneId}`).map((path) => url(path));
    },
    stageAssetUrl(stageId: string, path: string) {
      return stageAssetUrl(stageId, path);
    },
    uiAssetUrl(path: string) {
      return url(path.startsWith("/") ? path : `/ui/${path}`);
    },
  };
}

async function defaultFetchJson<T>(url: string): Promise<T> {
  const response = await fetch(url);
  if (!response.ok) throw new Error(`Failed to load asset JSON ${url}: ${response.status} ${response.statusText}`);
  return (await response.json()) as T;
}

async function defaultFetchArrayBuffer(url: string): Promise<ArrayBuffer> {
  const response = await fetch(url);
  if (!response.ok) throw new Error(`Failed to load asset bytes ${url}: ${response.status} ${response.statusText}`);
  return response.arrayBuffer();
}

function defaultBaseUrl(): string {
  if (typeof document !== "undefined") return document.baseURI;
  if (typeof location !== "undefined") return location.href;
  return "http://localhost/";
}

function stageModelPaths(manifest: StageManifest): string[] {
  if (Array.isArray(manifest.models) && manifest.models.length > 0) {
    const paths = manifest.models.map((m) => m.path);
    return assertGlbPaths(paths, `Stage ${manifest.id ?? "unknown"} manifest`);
  }

  const indices = manifest.visual?.expectedGlbIndices;
  if (indices && indices.length > 0) {
    return indices.map((i) => `model/model_${String(i).padStart(2, "0")}.glb`);
  }

  const count = manifest.visual?.glbCount ?? 0;
  if (count > 0) return Array.from({ length: count }, (_, i) => `model/model_${String(i).padStart(2, "0")}.glb`);

  throw new Error(`Stage manifest has no GLB model entries for ${manifest.id ?? "unknown stage"}`);
}

function assertGlbPaths(paths: readonly string[], label: string): string[] {
  const nonGlb = paths.find((modelPath) => !/\.glb(?:[?#].*)?$/i.test(modelPath));
  if (nonGlb) throw new Error(`${label} must use GLB, got ${nonGlb}`);
  return [...paths];
}

interface StageCollisionLoader {
  fetchArrayBuffer(url: string): Promise<ArrayBuffer>;
  loadStageManifest(stageId: string): Promise<StageManifest>;
  stageAssetUrl(stageId: string, path: string): string;
}

async function loadStageCollision(
  stageId: string,
  manifest: StageManifest,
  loader: StageCollisionLoader,
): Promise<Pick<StageAssets, "bounds" | "collision">> {
  const collisionFiles = [...(manifest.collision ?? [])].sort((a, b) => a.path.localeCompare(b.path));
  if (collisionFiles.length === 0) return {};

  const parsed: StageCollisionLayer[] = [];
  for (const file of collisionFiles) {
    parsed.push({
      layerIndex: layerIndexFromCollisionPath(file.path),
      grid: hitBin.parseStageHitGrid(await loader.fetchArrayBuffer(loader.stageAssetUrl(stageId, file.path))),
    });
  }
  const resources = stageCollisionFromHitGrids(parsed);
  if (!resources) throw new Error(`Stage collision produced no usable geometry for ${stageId}`);
  return resources ? { bounds: resources.bounds, collision: resources.collision } : {};
}

function layerIndexFromCollisionPath(path: string): number | null {
  const match = /hit[0-9a-f]{2}([0-2])\.bin$/i.exec(path);
  return match ? Number(match[1]) : null;
}
