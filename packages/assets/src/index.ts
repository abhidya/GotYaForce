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

export interface ModelManifestEntry {
  id: string;
  name: string;
  dae: string;
}

export interface StageManifestModel {
  path: string;
}

export interface StageManifest {
  id?: string;
  models?: StageManifestModel[];
  visual?: {
    daeCount?: number;
    expectedDaeIndices?: number[];
  };
  collision?: Array<{ path: string }>;
}

export interface PublicAssetCatalogOptions {
  baseUrl?: string;
  fetchJson?: <T>(url: string) => Promise<T>;
}

export interface PublicAssetCatalog {
  loadModelManifest(): Promise<ModelManifestEntry[]>;
  loadStageManifest(stageId: string): Promise<StageManifest>;
  loadStageRenderState<T>(stageId: string): Promise<T | null>;
  stageAssetUrl(stageId: string, path: string): string;
  uiAssetUrl(path: string): string;
}

export function readBorgRoster(data: BorgRosterData): readonly BorgAssetEntry[] {
  const borgs = "borgs" in data ? data.borgs : data;
  return borgs.filter((b) => b.id.trim() !== "" && b.name.trim() !== "");
}

export function createPublicAssetCatalog(options: PublicAssetCatalogOptions = {}): PublicAssetCatalog {
  const baseUrl = options.baseUrl ?? defaultBaseUrl();
  const fetchJson = options.fetchJson ?? defaultFetchJson;
  const url = (path: string): string => new URL(path, baseUrl).toString();

  return {
    loadModelManifest() {
      return fetchJson<ModelManifestEntry[]>(url("/models/library/manifest.json")).catch(() => [] as ModelManifestEntry[]);
    },
    loadStageManifest(stageId: string) {
      return fetchJson<StageManifest>(url(`/stages/${stageId}/manifest.json`));
    },
    loadStageRenderState<T>(stageId: string) {
      return fetchJson<T>(url(`/stages/${stageId}/render-state.json`)).catch(() => null);
    },
    stageAssetUrl(stageId: string, path: string) {
      return url(`/stages/${stageId}/${path}`);
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

function defaultBaseUrl(): string {
  if (typeof document !== "undefined") return document.baseURI;
  if (typeof location !== "undefined") return location.href;
  return "http://localhost/";
}
