// Curates research source files into static JSON consumed by the docs site.
// Single source of truth: read from research/, emit into .vitepress/data/.
// Run: `node docs-site/scripts/curate-data.mjs`
//
// Replaces any hand-written JSON under .vitepress/data/. Never reads its own output.

import { cpSync, readFileSync, writeFileSync, readdirSync, statSync, existsSync, mkdirSync, copyFileSync } from 'node:fs'
import { join, dirname } from 'node:path'
import { fileURLToPath } from 'node:url'
import { execSync } from 'node:child_process'

const __filename = fileURLToPath(import.meta.url)
const __dirname = dirname(__filename)
const REPO_ROOT = join(__dirname, '..', '..')
const RESEARCH = join(REPO_ROOT, 'research')
const DATA_DIR = join(__dirname, '..', '.vitepress', 'data')
const PUBLIC_DIR = join(__dirname, '..', 'public')
const MODELS_SOURCE_DIR = join(REPO_ROOT, 'apps', 'game', 'public', 'models')
const MODELS_PUBLIC_DIR = join(PUBLIC_DIR, 'models')
const OGHIDRA_SESSIONS_DIR = join(REPO_ROOT, 'research', 'tools', 'OGhidra', 'analysis_sessions')
const GHIDRA_EXPORT_DIR = join(RESEARCH, 'decomp', 'ghidra-export')

const BASE = process.env.GH_PAGES_BASE ?? '/GotYaForce/'

const readJson = (rel) => JSON.parse(readFileSync(join(REPO_ROOT, rel), 'utf8'))
const readText = (rel) => readFileSync(join(REPO_ROOT, rel), 'utf8')
const writeJson = (name, data) => {
  if (!existsSync(DATA_DIR)) mkdirSync(DATA_DIR, { recursive: true })
  const out = join(DATA_DIR, name)
  writeFileSync(out, JSON.stringify(data, null, 2) + '\n', 'utf8')
  console.log(`  wrote ${name} (${(JSON.stringify(data).length / 1024).toFixed(1)} kB)`)
}

const syncModelAssets = () => {
  if (process.env.GF_ATLAS_SKIP_MODELS === '1') {
    console.log('  model assets skipped (GF_ATLAS_SKIP_MODELS=1)')
    return
  }

  if (!existsSync(MODELS_SOURCE_DIR)) {
    console.warn(`  model assets missing: ${MODELS_SOURCE_DIR}`)
    return
  }

  if (!existsSync(PUBLIC_DIR)) mkdirSync(PUBLIC_DIR, { recursive: true })
  console.log('  syncing model assets to public/models')
  cpSync(MODELS_SOURCE_DIR, MODELS_PUBLIC_DIR, {
    recursive: true,
    force: true
  })
}

console.log('Curating atlas data from research/ ...')
console.log(`  repo root: ${REPO_ROOT}`)

// ---------------------------------------------------------------------------
// metrics.json — top-line counts pulled straight from authoritative sources.
// ---------------------------------------------------------------------------
const fnIdx = readJson('research/decomp/index/function-evidence-index.json')
const borgAssets = readJson('research/asset-inventory/borg-assets.json')
const borgCsvLines = readText('research/symbols/NTSC_Borgs.csv').split(/\r?\n/).filter(Boolean)
const tuned = readText('research/tuned-burndown.md')
const mapTsv = readText('research/decomp/organized/_map.tsv').split(/\r?\n/).filter(Boolean)

const tunedRemaining = Number(
  (tuned.match(/TUNED markers remaining:\s*(\d+)/) || [, 0])[1]
)
const tunedDerived = Number(
  (tuned.match(/DERIVED markers:\s*(\d+)/) || [, 0])[1]
)
const tunedFilesWithDebt = Number(
  (tuned.match(/Files with TUNED debt:\s*(\d+)/) || [, 0])[1]
)
const tunedTotal = tunedRemaining + tunedDerived

// bucket counts from the organized decomp map (one row per function)
const bucketFnCounts = {}
for (const line of mapTsv.slice(1)) {
  const cols = line.split('\t')
  if (cols.length < 6) continue
  const bucket = cols[5] || 'unknown'
  bucketFnCounts[bucket] = (bucketFnCounts[bucket] || 0) + 1
}
const unsortedFunctions = bucketFnCounts['game-unsorted'] ?? 0
const totalFunctions = mapTsv.length - 1

// real .c file counts under organized/ (dir walk, no venv/cache)
function countFilesRecursive(dir, ext) {
  if (!existsSync(dir)) return 0
  let n = 0
  for (const entry of readdirSync(dir, { withFileTypes: true })) {
    if (entry.isDirectory()) n += countFilesRecursive(join(dir, entry.name), ext)
    else if (entry.name.endsWith(ext)) n += 1
  }
  return n
}
const organizedRoot = join(RESEARCH, 'decomp', 'organized')
const totalOrganizedFiles = countFilesRecursive(organizedRoot, '.c')
const unsortedFiles = countFilesRecursive(join(organizedRoot, 'game', 'unsorted'), '.c')

// git short sha (best-effort, falls back if no git or shallow clone)
let gitSha = 'unknown'
try {
  gitSha = execSync('git rev-parse --short HEAD', { cwd: REPO_ROOT }).toString().trim()
} catch {}

writeJson('metrics.json', {
  functionsIndexed: fnIdx.source.functionCount,
  borgsIndexed: borgAssets.summary.metadataRecords,
  borgsOnDisc: borgAssets.summary.discBorgIds,
  borgsInCsv: Math.max(0, borgCsvLines.length - 1),
  stagesMapped: 18, // sourced from challenge-stage-naming-2026-07-05.md; no JSON equivalent yet
  tunedTotal,
  tunedRemaining,
  tunedDerived,
  tunedFilesWithDebt,
  unsortedFunctions,
  totalFunctions,
  unsortedFiles,
  totalOrganizedFiles,
  organizedPct: totalOrganizedFiles ? Math.round(((totalOrganizedFiles - unsortedFiles) / totalOrganizedFiles) * 100) : 0,
  lastVerified: new Date().toISOString().slice(0, 10),
  gitSha,
  generatedAt: new Date().toISOString()
})

// ---------------------------------------------------------------------------
// progress.json — per-system coverage derived from function topic counts,
// TUNED debt, and presence of decoded tables.
// ---------------------------------------------------------------------------
const t = fnIdx.topicCounts
const totalFn = fnIdx.source.functionCount
// system coverage = % of all decompiled functions tagged with that topic
const pct = (n) => Math.round((n / totalFn) * 100)

const systems = [
  { name: 'Movement & Physics', href: `${BASE}systems/`, sourceTopic: 'movement-physics', table: 'movement-physics-constants.json' },
  { name: 'Force Setup / Battle', href: `${BASE}systems/`, sourceTopic: 'force-setup' },
  { name: 'Knockback / Targeting', href: `${BASE}systems/combat`, sourceTopic: 'knockback-targeting', table: 'knockback-direction-800300bc.json' },
  { name: 'Animation Assets', href: `${BASE}systems/`, sourceTopic: 'assets-animation' },
  { name: 'Challenge / Menu Flow', href: `${BASE}modes/challenge`, sourceTopic: 'challenge-menu-flow' },
  { name: 'Battle Initialization', href: `${BASE}systems/`, sourceTopic: 'battle-initialization' },
  { name: 'Damage', href: `${BASE}systems/damage`, sourceTopic: 'damage', table: 'damage-formula-tables-804335e0.json' },
  { name: 'Camera', href: `${BASE}systems/`, sourceTopic: 'camera' },
  { name: 'Front-End Menu', href: `${BASE}modes/`, sourceTopic: 'front-end-menu' },
  { name: 'Global Menu Mode', href: `${BASE}modes/`, sourceTopic: 'global-menu-mode' },
  { name: 'Audio', href: `${BASE}systems/audio-sfx`, sourceTopic: 'audio' },
  { name: 'Stage Load / Collision', href: `${BASE}stages/geometry`, sourceTopic: 'stage-load-collision' }
].map((s) => {
  const fnCount = t[s.sourceTopic] ?? 0
  const hasTable = s.table ? existsSync(join(RESEARCH, 'decomp', 'data', s.table)) : false
  return {
    name: s.name,
    href: s.href,
    pct: pct(fnCount),
    status: fnCount >= 500 ? 'observed' : fnCount >= 100 ? 'likely' : 'unknown',
    note: `${fnCount} functions indexed${hasTable ? ` · table ${s.table}` : ''}`
  }
})

// bucket rollups from the function-level organized map
const buckets = Object.entries(bucketFnCounts)
  .sort((a, b) => b[1] - a[1])
  .slice(0, 12)
  .map(([label, count]) => ({
    label,
    count,
    status: label.includes('unsorted') ? 'invalid' : 'observed'
  }))

writeJson('progress.json', { systems, buckets, topicCounts: t, totalFn })

// ---------------------------------------------------------------------------
// borgs.json — parsed straight from NTSC_Borgs.csv (the canonical symbol map).
// ---------------------------------------------------------------------------
const borgHeader = borgCsvLines[0].split(',')
const borgs = borgCsvLines.slice(1).map((line) => {
  const cols = line.split(',')
  const row = {}
  borgHeader.forEach((h, i) => (row[h] = cols[i]))
  return {
    id: row.filename,
    name: row.borgname,
    number: Number(row.Number),
    cost: Number(row.Cost),
    crystals: Number(row['Data Crystals Required']),
    tribe: row.Tribe,
    type: row.Type,
    rarity: row.Rarity,
    alt: row['Has Alternate?'] === 'Yes',
    hp1: row['Level 1 HP/Level 10 HP']?.split('/')[0],
    hp10: row['Level 1 HP/Level 10 HP']?.split('/')[1],
    defense: row.Defense,
    shot: row.Shot,
    attack: row.Attack,
    speed: row.Speed,
    jumpType: row['Jump Type'],
    levelSchedule: row['Level-up Schedule']
  }
})

writeJson('borgs.json', {
  source: 'research/symbols/NTSC_Borgs.csv',
  count: borgs.length,
  borgs
})

// ---------------------------------------------------------------------------
// data-tables.json — list every decoded game table in research/decomp/data/.
// ---------------------------------------------------------------------------
const dataDir = join(RESEARCH, 'decomp', 'data')
const tables = readdirSync(dataDir)
  .filter((f) => f.endsWith('.json'))
  .map((f) => {
    let parsed = {}
    try {
      parsed = JSON.parse(readFileSync(join(dataDir, f), 'utf8'))
    } catch {}
    return {
      file: f,
      address: parsed.address ?? parsed.romConstant ?? null,
      description: (parsed.description ?? '').split('. ')[0].slice(0, 140),
      keys: Object.keys(parsed).slice(0, 6)
    }
  })

writeJson('data-tables.json', { count: tables.length, tables })

// ---------------------------------------------------------------------------
// force.json — gacha + fusion + color variants, straight from decoded tables.
// ---------------------------------------------------------------------------
const spawnPools = readJson('research/decomp/data/spawn-pools-80380804.json')
const fusion = readJson('research/decomp/data/fusion-pairs-802d352c.json')
const fusionFamilyCount = fusion.families ? Object.keys(fusion.families).length : 0
const fusionPairCount = fusion.pairTable?.entries ? fusion.pairTable.entries.length : 0
const fusionNonNull = fusion.pairTable?.nonNullFamilies ?? 0
const spawnIdToPlId = (spawnId) => `pl${Number(spawnId).toString(16).padStart(4, '0')}`
const borgNameById = new Map(borgs.map((b) => [b.id, b.name]))
const spawnRows = (spawnPools.groups || []).map((group) => {
  const plIds = (group.ids || []).map(spawnIdToPlId)
  const familySet = new Set((group.ids_family_variant || []).map(([family]) => family))
  return {
    group: group.group,
    ptr: group.ptr,
    count: plIds.length,
    families: [...familySet].sort((a, b) => a - b).join(', '),
    borgs: plIds.map((id) => borgNameById.get(id) ? `${id} ${borgNameById.get(id)}` : id).join(', '),
    ids: plIds.join(', ')
  }
})
const fusionRows = Object.values(fusion.families || {}).flatMap((family) =>
  (family.variants || []).flatMap((variant) =>
    (variant.pairs || []).map((pair) => {
      const baseId = `pl${family.familyByte.toString(16).padStart(2, '0')}${variant.variant.toString(16).padStart(2, '0')}`
      return {
        family: family.familyByte,
        variant: variant.variant,
        base: borgNameById.get(baseId) ? `${baseId} ${borgNameById.get(baseId)}` : baseId,
        partner: borgNameById.get(pair.partner.plId) ? `${pair.partner.plId} ${borgNameById.get(pair.partner.plId)}` : pair.partner.plId,
        result: borgNameById.get(pair.result.plId) ? `${pair.result.plId} ${borgNameById.get(pair.result.plId)}` : pair.result.plId,
        pairCount: variant.pairCount,
        ptr: variant.subListPtr
      }
    })
  )
)
const fusionFamilyRows = Object.values(fusion.families || {}).map((family) => ({
  family: family.familyByte,
  listPtr: family.listPtr,
  variants: family.nonNullVariantCount,
  pairs: (family.variants || []).reduce((sum, variant) => sum + (variant.pairCount || 0), 0),
  listWords: family.listWordCount
}))

writeJson('force.json', {
  spawnPools: {
    address: spawnPools.address,
    groupCount: spawnPools.count,
    description: spawnPools.description?.slice(0, 200)
  },
  spawnRows,
  fusion: {
    address: fusion.provenance?.romConstant ?? '0x802d352c',
    familyCount: fusionFamilyCount,
    pairCount: fusionRows.length || fusionPairCount,
    nonNullFamilies: fusionNonNull,
    unknownIds: Array.isArray(fusion.unknownIds) ? fusion.unknownIds.length : 0,
    provenance: fusion.provenance
  },
  fusionRows,
  fusionFamilyRows,
  colorVariants: ['normal', 'alt', 'gold', 'silver', 'crystal', 'black'],
  source: [
    'research/decomp/data/spawn-pools-80380804.json',
    'research/decomp/data/fusion-pairs-802d352c.json'
  ]
})

// ---------------------------------------------------------------------------
// weapon-atlas.json — slim attachment/effect/projectile evidence for the atlas.
// ---------------------------------------------------------------------------
const weaponAttachmentMap = readJson('research/asset-inventory/weapon-attachment-map.json')
const weaponEffectsProjectiles = readJson('research/asset-inventory/weapons-effects-projectiles.json')
const confidenceRank = { High: 3, Medium: 2, Low: 1 }
const weaponFamilyRows = Object.entries(weaponAttachmentMap.families || {}).map(([family, value]) => ({
  family,
  label: value.label || family,
  borgCount: value.borgCount || 0,
  sharedAssets: (value.sharedAssets || []).length,
  topTribes: (value.byTribe || [])
    .slice(0, 4)
    .map((entry) => `${entry.tribe} (${entry.borgCount})`)
    .join(', '),
  sampleBorgs: (value.byTribe || [])
    .flatMap((entry) => entry.borgs || [])
    .slice(0, 8)
    .map((borg) => `${borg.id} ${borg.name}`)
    .join(', ')
}))
const weaponBorgRows = (weaponAttachmentMap.borgs || []).map((borg) => {
  const families = Object.entries(borg.families || {})
  const bestConfidence = families
    .map(([, value]) => value.confidence || 'Low')
    .sort((a, b) => (confidenceRank[b] || 0) - (confidenceRank[a] || 0))[0] || 'Low'
  const evidenceCount = families.reduce((sum, [, value]) => sum + (value.evidenceCount || 0), 0)
  return {
    id: borg.id,
    name: borg.name,
    number: borg.number,
    tribe: borg.tribe,
    type: borg.type,
    rarity: borg.stats?.rarity || '',
    energy: borg.stats?.energy || '',
    families: families.map(([family]) => family),
    familyList: families.map(([family]) => family).join(', '),
    confidence: bestConfidence,
    evidenceCount,
    archiveCount: (borg.archiveNames || []).length,
    attachmentCandidates: (borg.itemAttachmentCandidates || []).length,
    boneCandidates: (borg.attachmentBoneCandidates || []).length,
    attackClipCandidates: borg.mot?.attackClipCandidateCount || 0,
    runtimeTraceNeeded: Boolean(borg.runtimeTraceNeeded),
    runtimeTraceReasons: (borg.runtimeTraceReasons || []).join('; ')
  }
})
const sharedWeaponAssets = (weaponAttachmentMap.sharedAssets || []).slice(0, 80).map((asset) => ({
  path: asset.path,
  role: asset.role || (asset.roles || []).join(', '),
  families: (asset.families || []).join(', '),
  confidence: asset.confidence || 'Unknown',
  sizeBytes: asset.sizeBytes || 0,
  reason: asset.reason || (asset.reasons || [])[0] || ''
}))
writeJson('weapon-atlas.json', {
  source: [
    'research/asset-inventory/weapon-attachment-map.json',
    'research/asset-inventory/weapons-effects-projectiles.json',
    'research/asset-inventory/particle-effect-inventory.json',
    'research/asset-inventory/pzz-member-extraction-manifest.json'
  ],
  summary: {
    mappedBorgCount: weaponAttachmentMap.summary?.mappedBorgCount || 0,
    sharedAssetCount: weaponAttachmentMap.summary?.sharedAssetCount || 0,
    familyBorgCounts: weaponAttachmentMap.summary?.familyBorgCounts || {},
    borgsWithDaeAttachmentCandidates: weaponAttachmentMap.summary?.borgsWithDaeAttachmentCandidates || 0,
    runtimeTraceAttackClipCount: weaponAttachmentMap.summary?.runtimeTraceAttackClipCount || 0,
    sourceEvidenceCount: weaponAttachmentMap.summary?.sourceEvidenceCount || 0,
    candidateCount: weaponEffectsProjectiles.summary?.candidateCount || 0,
    textureCount: weaponEffectsProjectiles.summary?.textureCount || 0,
    archiveLikeFileCount: weaponEffectsProjectiles.archiveInventory?.archiveLikeFileCount || 0
  },
  families: weaponFamilyRows,
  borgs: weaponBorgRows,
  sharedAssets: sharedWeaponAssets,
  needs: (weaponEffectsProjectiles.needsExtractionConversion || []).map((need) => ({
    need: need.need,
    candidateCount: need.candidateCount,
    examples: (need.examples || []).slice(0, 5).join(', ')
  }))
})

// ---------------------------------------------------------------------------
// evidence.json — gather claims from decoded tables + trace validity counts.
// ---------------------------------------------------------------------------
const typeMatrix = readJson('research/decomp/data/type-multiplier-matrix-802c5d60.json')
const evidence = [
  {
    claim: typeMatrix.description?.slice(0, 120) || 'Type effectiveness 20x20 matrix',
    status: 'verified',
    addr: typeMatrix.address,
    file: 'research/decomp/data/type-multiplier-matrix-802c5d60.json',
    matrixRows: typeMatrix.matrix ? typeMatrix.matrix.length : 0
  },
  {
    claim: spawnPools.description?.slice(0, 120) || 'Challenge spawn pool table',
    status: 'verified',
    addr: spawnPools.address,
    file: 'research/decomp/data/spawn-pools-80380804.json'
  },
  {
    claim: 'Fusion pair table (Power Burst combine)',
    status: 'verified',
    addr: fusion.provenance?.romConstant ?? '0x802d352c',
    file: 'research/decomp/data/fusion-pairs-802d352c.json'
  }
]

// trace validity counts from dolphin-gdb-trace-results.md (best-effort parse)
let traceResults = null
const tracePath = join(RESEARCH, 'traces', 'GG4E', 'dolphin-gdb-trace-results.md')
if (existsSync(tracePath)) {
  const traceMd = readText('research/traces/GG4E/dolphin-gdb-trace-results.md')
  const counts = {
    pass: (traceMd.match(/\bPASS\b/gi) || []).length,
    fail: (traceMd.match(/\bFAIL\b/gi) || []).length,
    invalid: (traceMd.match(/\bINVALID\b/gi) || []).length
  }
  traceResults = { source: 'research/traces/GG4E/dolphin-gdb-trace-results.md', counts }
}

writeJson('evidence.json', {
  evidence,
  invalidTraces: traceResults,
  topicCounts: t,
  source: [
    'research/decomp/data/*.json',
    'research/traces/GG4E/dolphin-gdb-trace-results.md'
  ]
})

// ---------------------------------------------------------------------------
// mode-atlas.json — top-level game modes and their evidence hooks.
// ---------------------------------------------------------------------------
const modeRows = [
  {
    id: 'story',
    name: 'Story / Adventure',
    status: 'likely',
    route: '/modes/story',
    functions: (t['challenge-menu-flow'] || 0) + (t['force-setup'] || 0),
    source: 'research/asset-inventory/adventure-flow-ai.json',
    notes: 'Chapters, mission flow, recruits, partner/enemy force setup.'
  },
  {
    id: 'challenge',
    name: 'Challenge',
    status: 'observed',
    route: '/modes/challenge',
    functions: (t['challenge-menu-flow'] || 0) + (t['battle-initialization'] || 0),
    source: 'research/decomp/challenge-stage-naming-2026-07-05.md',
    notes: 'Stage byte names, spawn pools, battle setup, challenge rotation.'
  },
  {
    id: 'versus',
    name: 'Versus',
    status: 'likely',
    route: '/modes/versus',
    functions: t['battle-initialization'] || 0,
    source: 'research/decomp/index/start-code-flow.md',
    notes: 'Local multiplayer battle setup and quadrant HUD flow.'
  },
  {
    id: 'coop',
    name: 'Co-op',
    status: 'likely',
    route: '/modes/versus',
    functions: t['battle-initialization'] || 0,
    source: 'research/decomp/behavior-notes.md',
    notes: 'Partner AI and cooperative force setup still need deeper traces.'
  },
  {
    id: 'attract',
    name: 'Attract Demo',
    status: 'verified',
    route: '/modes/attract',
    functions: t['front-end-menu'] || 0,
    source: 'research/decomp/index/title-main-menu-flow.md',
    notes: 'Demo flow and stage pool identified in menu/title decode.'
  },
  {
    id: 'title',
    name: 'Title / Menu',
    status: 'verified',
    route: '/modes/',
    functions: (t['front-end-menu'] || 0) + (t['global-menu-mode'] || 0),
    source: 'research/decomp/index/title-main-menu-flow.md',
    notes: 'Top-level dispatcher, title screen widgets, transition resources.'
  }
]
writeJson('mode-atlas.json', {
  source: [
    'research/decomp/index/title-main-menu-flow.md',
    'research/decomp/index/start-code-flow.md',
    'research/asset-inventory/adventure-flow-ai.json',
    'research/decomp/challenge-stage-naming-2026-07-05.md'
  ],
  summary: {
    modes: modeRows.length,
    verified: modeRows.filter((mode) => mode.status === 'verified').length,
    observed: modeRows.filter((mode) => mode.status === 'observed').length,
    likely: modeRows.filter((mode) => mode.status === 'likely').length,
    relatedFunctions: modeRows.reduce((sum, mode) => sum + mode.functions, 0)
  },
  modes: modeRows
})

// ---------------------------------------------------------------------------
// latest.json — newest findings, derived from .md mtimes in research/decomp/.
// ---------------------------------------------------------------------------
const findingsDir = join(RESEARCH, 'decomp')
const findings = readdirSync(findingsDir)
  .filter((f) => f.endsWith('.md'))
  .map((f) => {
    const full = join(findingsDir, f)
    const st = statSync(full)
    const dateMatch = f.match(/(\d{4}-\d{2}-\d{2})/)
    return {
      title: f.replace(/\.md$/, '').replace(/-\d{4}-\d{2}-\d{2}$/, '').replace(/-/g, ' '),
      file: `research/decomp/${f}`,
      mtime: st.mtime.toISOString(),
      date: dateMatch ? dateMatch[1] : st.mtime.toISOString().slice(0, 10),
      area: 'Decomp'
    }
  })
  .sort((a, b) => b.mtime.localeCompare(a.mtime))
  .slice(0, 10)
  .map((f) => ({
    title: f.title,
    area: f.area,
    date: f.date,
    href: `${BASE}evidence/`
  }))

writeJson('latest.json', { findings })

// ---------------------------------------------------------------------------
// tooling.json — RE stack. Static-ish list, but kept here for single source.
// ---------------------------------------------------------------------------
writeJson('tooling.json', {
  tools: [
    { name: 'Ghidra 12.1.2', use: 'Full-corpus decompile.', link: 'https://ghidra-sre.org/', status: 'verified' },
    { name: 'GameCubeLoader', use: 'Load DOL + disc into Ghidra with symbols.', link: 'https://github.com/Cuyler36/GameCubeLoader', status: 'verified' },
    { name: 'HSDLib', use: 'HSD DAT / JOBJ skeleton / DAE export with skins.', link: '', status: 'verified' },
    { name: 'NeoGF', use: 'Gotcha Force archive / format readers.', link: '', status: 'verified' },
    { name: 'gotcha-afs-tool', use: 'AFS archive extraction.', link: '', status: 'verified' },
    { name: 'Dolphin (GDB)', use: 'Runtime traces via GDB stub.', link: 'https://dolphin-emu.org/', status: 'verified' },
    { name: 'degod / guessadx', use: 'ADX audio key brute-force.', link: '', status: 'verified' }
  ],
  patches: [
    {
      name: 'HSDLib texture fix',
      file: 'research/patches/hsdlib-modelexporter-texture-fix.patch',
      use: 'Fix texture export path in HSDLib ModelExporter.',
      present: existsSync(join(REPO_ROOT, 'research/patches/hsdlib-modelexporter-texture-fix.patch'))
    },
    {
      name: 'gltf-export harness',
      file: 'research/patches/gltf-export-Program.cs',
      use: 'C# harness for glTF export from runtime model capture.',
      present: existsSync(join(REPO_ROOT, 'research/patches/gltf-export-Program.cs'))
    }
  ],
  scriptsIndexed: readdirSync(join(REPO_ROOT, 'scripts')).filter((f) => f.endsWith('.mjs')).length
})

// ---------------------------------------------------------------------------
// memory.json — RAM regions + struct fields, sourced from research notes.
// ---------------------------------------------------------------------------
writeJson('memory.json', {
  regions: [
    { name: 'DOL .text', owner: 'executable code', confidence: 'verified', notes: `~${fnIdx.source.functionCount} functions indexed.` },
    { name: 'DOL .data', owner: 'constants / tables', confidence: 'verified', notes: `${tables.length} decoded data tables in research/decomp/data/.` },
    { name: '.bss globals', owner: 'globals', confidence: 'likely', notes: 'World state, mode dispatcher, current force pointers.' },
    { name: 'Heap', owner: 'borg/stage objects', confidence: 'observed', notes: 'World pos observed at render scene buffer. Gameplay struct base + HP still unpinned.' },
    { name: 'ARAM', addr: '0x01000000', owner: 'audio / streamed', confidence: 'verified', notes: '16MB audio RAM. ADX streams.' },
    { name: 'DVD / FST', owner: 'source files', confidence: 'verified', notes: 'Disc filesystem. AFS archives containing .arc (HSD DAT wrappers).' }
  ],
  structs: [
    {
      name: 'BorgRuntime',
      offset: 'actor + 0x34',
      fields: [
        { name: 'hp', type: 'int16', range: '0..650', confidence: 'observed', notes: 'Gameplay struct base + HP still unpinned (see ram-trace-analysis.md).' },
        { name: 'animSoundTable', type: 'ptr', offset: 'actor+0x4e8', confidence: 'verified', notes: 'Per-anim SFX event table' }
      ],
      source: 'research/decomp/ram-trace-analysis.md'
    }
  ],
  source: ['research/decomp/ram-trace-analysis.md', 'research/decomp/borg-struct-offsets.txt']
})

// ---------------------------------------------------------------------------
// stages.json — parse the arena-name table straight from the decode markdown.
// ---------------------------------------------------------------------------
let stages = []
const stageMdPath = join(RESEARCH, 'decomp', 'challenge-stage-naming-2026-07-05.md')
if (existsSync(stageMdPath)) {
  const stageMd = readFileSync(stageMdPath, 'utf8')
  // find the "Arena name (US)" table (the only one whose header has that text)
  const headerIdx = stageMd.indexOf('Arena name (US)')
  if (headerIdx !== -1) {
    const slice = stageMd.slice(headerIdx)
    const rowRe = /^\|\s*(0x[0-9a-fA-F]{2})\s*\|\s*([^|]+?)\s*\|\s*([^|]+?)\s*\|\s*([^|]+?)\s*\|/gm
    let match
    while ((match = rowRe.exec(slice)) !== null) {
      const [, byte, archive, name, poolRaw] = match
      // skip divider rows or empty cells
      if (!name.trim() || name.includes('---')) continue
      const inPool = poolRaw.trim().toUpperCase().startsWith('YES')
      stages.push({
        id: byte,
        archive: archive.trim(),
        name: name.trim(),
        inChallengePool: inPool,
        status: inPool ? 'verified' : 'observed'
      })
    }
  }
}

writeJson('stages.json', {
  source: 'research/decomp/challenge-stage-naming-2026-07-05.md',
  arenas: stages.length,
  challengePoolCount: stages.filter((s) => s.inChallengePool).length,
  stages
})

// ---------------------------------------------------------------------------
// stage-atlas.json — joins named arenas to export, collision, and render-state evidence.
// ---------------------------------------------------------------------------
const stageExportPlan = readJson('research/asset-inventory/stage-export-plan.json')
const stageLighting = readJson('research/asset-inventory/stage-lighting-render-state.json')
const namedByArchive = new Map()
for (const stage of stages) {
  for (const archive of String(stage.archive || '').split('/')) {
    namedByArchive.set(archive.trim(), stage)
  }
}
const lightingById = new Map((stageLighting.stages || []).map((stage) => [stage.stageId, stage]))
const stageAtlasRows = (stageExportPlan.stages || []).map((stage) => {
  const named = namedByArchive.get(stage.id) || null
  const lighting = lightingById.get(stage.id) || {}
  const visual = stage.public?.visual || {}
  const collision = stage.source?.collision || {}
  const sets = stage.source?.sets || {}
  const materials = lighting.exportedMaterialState || {}
  return {
    id: stage.id,
    code: stage.code,
    arena: named?.name || 'unmapped stage export',
    challengeByte: named?.id || '',
    archiveGroup: named?.archive || stage.id,
    inChallengePool: Boolean(named?.inChallengePool),
    status: visual.hasCompleteDaeExport && collision.hasHitFiles ? 'verified' : visual.hasCompleteDaeExport ? 'observed' : 'unknown',
    visualPieces: visual.daeCount || materials.daeFileCount || 0,
    nonEmptyPieces: visual.nonEmptyDaeCount || 0,
    collisionFiles: (collision.files || []).length,
    completeCollisionTriplet: Boolean(collision.hasCompleteHitTriplet),
    setArcs: (sets.files || []).length,
    jobjCount: lighting.scene?.jobjDescCount || 0,
    pobjCount: lighting.drawState?.pobjCount || 0,
    materialCount: materials.materialCount || 0,
    stageArcBytes: stage.source?.stageArc?.bytes || 0,
    pzzBytes: stage.source?.stagePzz?.bytes || 0,
    sourcePath: stage.source?.stageArc?.path || ''
  }
})
writeJson('stage-atlas.json', {
  source: [
    'research/decomp/challenge-stage-naming-2026-07-05.md',
    'research/asset-inventory/stage-export-plan.json',
    'research/asset-inventory/stage-lighting-render-state.json',
    'research/asset-inventory/stage-geometry-collision.json'
  ],
  summary: {
    namedArenas: stages.length,
    challengePoolCount: stages.filter((s) => s.inChallengePool).length,
    exportStageCount: stageAtlasRows.length,
    visualStageCount: stageExportPlan.summary?.verifiedVisualStageCount || 0,
    collisionStageCount: stageExportPlan.summary?.exportedCollisionHitStageCount || 0,
    setArcStageCount: stageExportPlan.summary?.sourceAnySetArcCount || 0
  },
  rows: stageAtlasRows
})

// ---------------------------------------------------------------------------
// functions.json — slim function index for the Function Explorer.
// Omits callers/callees arrays (kept in the full index) to keep this ~2 MB.
// ---------------------------------------------------------------------------
const allFns = fnIdx.functions
const topicListFor = (fn) => {
  const t = fn.topics || []
  return Array.isArray(t) ? t : []
}
const functionsSlim = allFns.map((f) => ({
  a: f.address,
  n: f.currentFunctionName || f.symbolMapName || f.inferredName || f.address,
  inf: f.inferredName || null,
  chunk: f.chunkFile,
  ls: f.lineStart,
  le: f.lineEnd,
  cnt: f.lineCount,
  cc: (f.callers || []).length,
  ce: (f.callees || []).length,
  t: topicListFor(f),
  src: f.sourceRef || null
}))
writeJson('functions.json', {
  source: 'research/decomp/index/function-evidence-index.json',
  count: functionsSlim.length,
  functions: functionsSlim
})

// ---------------------------------------------------------------------------
// functions-graph.json — top-N most-connected functions for the call graph.
// Full graph (11,972 nodes) is too dense; cap to ~400 highest-degree nodes.
// ---------------------------------------------------------------------------
const degreeMap = new Map()
for (const f of allFns) {
  const deg = (f.callers || []).length + (f.callees || []).length
  degreeMap.set(f.address, deg)
}
const topAddrs = [...degreeMap.entries()]
  .sort((a, b) => b[1] - a[1])
  .slice(0, 400)
  .map(([a]) => a)
const topSet = new Set(topAddrs)
const addrToName = new Map(allFns.map((f) => [f.address, f.currentFunctionName || f.symbolMapName || f.address]))
const addrToTopic = new Map(allFns.map((f) => [f.address, (f.topics || []).join('/') || 'unsorted']))
const graphNodes = topAddrs.map((a) => ({
  id: a,
  name: addrToName.get(a),
  topic: addrToTopic.get(a) || 'unsorted',
  degree: degreeMap.get(a)
}))
const graphEdges = []
const seenEdge = new Set()
for (const f of allFns) {
  if (!topSet.has(f.address)) continue
  for (const c of (f.callees || [])) {
    if (!topSet.has(c.address)) continue
    const k = `${f.address}>${c.address}`
    if (seenEdge.has(k)) continue
    seenEdge.add(k)
    graphEdges.push({ from: f.address, to: c.address })
  }
}
writeJson('functions-graph.json', {
  source: 'research/decomp/index/function-evidence-index.json',
  note: 'Top 400 highest-degree functions. Full graph in function-evidence-index.json.',
  nodes: graphNodes,
  edges: graphEdges
})

// ---------------------------------------------------------------------------
// ghidra-corpus.json — first-class metadata for the full Ghidra/OGhidra corpus.
// ---------------------------------------------------------------------------
const ghidraExportFiles = readdirSync(GHIDRA_EXPORT_DIR)
const chunkFiles = ghidraExportFiles.filter((f) => /^chunk_\d+\.c$/.test(f)).sort()
const ghidraIndexRows = readFileSync(join(GHIDRA_EXPORT_DIR, '_index.tsv'), 'utf8')
  .trim()
  .split(/\r?\n/)
  .filter(Boolean)

const topicRows = Object.entries(fnIdx.topicCounts)
  .map(([topic, count]) => ({
    topic,
    functions: count,
    pct: `${Math.round((count / fnIdx.source.functionCount) * 1000) / 10}%`
  }))
  .sort((a, b) => b.functions - a.functions)

const anchorFunctions = allFns
  .filter((f) => (f.topics || []).length)
  .sort((a, b) => (b.callers || []).length - (a.callers || []).length)
  .slice(0, 16)
  .map((f) => ({
    address: f.address,
    name: f.currentFunctionName || f.symbolMapName || f.inferredName || f.address,
    topics: (f.topics || []).join(', '),
    callers: (f.callers || []).length,
    callees: (f.callees || []).length,
    source: f.sourceRef || ''
  }))

const sessions = []
const uniqueAnalyzed = new Set()
if (existsSync(OGHIDRA_SESSIONS_DIR)) {
  for (const dirent of readdirSync(OGHIDRA_SESSIONS_DIR, { withFileTypes: true })) {
    if (!dirent.isDirectory()) continue
    const sessionPath = join(OGHIDRA_SESSIONS_DIR, dirent.name, 'session.json')
    if (!existsSync(sessionPath)) continue

    let parsed = null
    try {
      parsed = JSON.parse(readFileSync(sessionPath, 'utf8'))
    } catch {
      continue
    }

    const metadata = parsed.metadata || {}
    const analyzed = parsed.analyzed_functions || {}
    const analyzedAddresses = Object.keys(analyzed)
    for (const address of analyzedAddresses) uniqueAnalyzed.add(address)

    sessions.push({
      id: metadata.session_id || dirent.name,
      name: metadata.session_name || dirent.name,
      createdAt: metadata.created_at || '',
      lastModified: metadata.last_modified || '',
      totalFunctions: metadata.total_functions || 0,
      analyzedFunctions: metadata.analyzed_functions_count || analyzedAddresses.length,
      actualAnalyzedFunctions: analyzedAddresses.length,
      analysisLogEntries: Array.isArray(parsed.analysis_log) ? parsed.analysis_log.length : 0,
      path: `research/tools/OGhidra/analysis_sessions/${dirent.name}/session.json`
    })
  }
}
sessions.sort((a, b) => a.createdAt.localeCompare(b.createdAt))

const sessionFunctionRecords = sessions.reduce((sum, session) => sum + session.actualAnalyzedFunctions, 0)
const latestSession = sessions[sessions.length - 1] || null
const largestSession = sessions.slice().sort((a, b) => b.actualAnalyzedFunctions - a.actualAnalyzedFunctions)[0] || null

writeJson('ghidra-corpus.json', {
  source: [
    'research/decomp/GotchaForce.gpr',
    'research/decomp/GotchaForce.rep/',
    'research/decomp/ghidra-export/',
    'research/decomp/index/function-evidence-index.json',
    'research/tools/OGhidra/analysis_sessions/',
    'research/decomp/oghidra-first-pass-port-findings-2026-07-12.md'
  ],
  project: {
    ghidraProject: 'research/decomp/GotchaForce.gpr',
    ghidraRepository: 'research/decomp/GotchaForce.rep/',
    bootDol: 'user-data/GG4E/disc/sys/boot.dol',
    symbolMap: 'GG4E-CSM-20220412.map',
    ghidraVersion: 'Ghidra 12.1.2',
    exportDir: fnIdx.source.ghidraExportDir,
    exportIndex: fnIdx.source.indexFile,
    exportReadme: 'research/decomp/ghidra-export/README.md'
  },
  metrics: {
    functionCount: fnIdx.source.functionCount,
    chunkCount: chunkFiles.length,
    indexRows: ghidraIndexRows.length,
    sessionCount: sessions.length,
    sessionFunctionRecords,
    uniqueAnalyzedFunctions: uniqueAnalyzed.size,
    uniqueAnalyzedPct: fnIdx.source.functionCount
      ? Math.round((uniqueAnalyzed.size / fnIdx.source.functionCount) * 1000) / 10
      : 0,
    latestSessionId: latestSession?.id || '',
    latestSessionAt: latestSession?.createdAt || '',
    largestSessionId: largestSession?.id || '',
    largestSessionFunctions: largestSession?.actualAnalyzedFunctions || 0
  },
  topicRows,
  anchorFunctions,
  sessions: sessions.slice().reverse()
})

// ---------------------------------------------------------------------------
// Copy chunk_NNNN.c files to public/chunks/ for on-demand source fetch.
// ---------------------------------------------------------------------------
const chunkSrcDir = GHIDRA_EXPORT_DIR
const chunkDstDir = join(PUBLIC_DIR, 'chunks')
if (!existsSync(chunkDstDir)) mkdirSync(chunkDstDir, { recursive: true })
let chunkCount = 0
for (const f of readdirSync(chunkSrcDir)) {
  if (/^chunk_\d+\.c$/.test(f) || f === 'challenge_deobfuscated.c') {
    copyFileSync(join(chunkSrcDir, f), join(chunkDstDir, f))
    chunkCount++
  }
}
console.log(`  copied ${chunkCount} chunk files to public/chunks/`)

// ---------------------------------------------------------------------------
// type-matrix.json — 20x20 effectiveness matrix + axis labels.
// ---------------------------------------------------------------------------
const tm = readJson('research/decomp/data/type-multiplier-matrix-802c5d60.json')
const typeLabels = [
  'Ninja', 'Girl', 'Knight', 'Cyber', 'Battle',
  'Tank', 'Air', 'Heavy', 'Fortress', 'Supply',
  'Demon', 'Skeleton', 'Dragon', 'Machine', 'Insect',
  'Animal', 'Poltergeist', 'Ocean', 'Flame', 'Misc'
]
writeJson('type-matrix.json', {
  source: 'research/decomp/data/type-multiplier-matrix-802c5d60.json',
  address: tm.address,
  description: tm.description,
  labels: typeLabels,
  matrix: tm.matrix,
  // orientation: matrix[defenderCategory*20 + attackerCategory]
  indexing: 'row=defender, col=attacker'
})

// ---------------------------------------------------------------------------
// borg-moves.json — merge NTSC_Borgs.csv stats with wiki-borg-moves.json.
// ---------------------------------------------------------------------------
const wikiMoves = readJson('research/decomp/data/wiki-borg-moves.json')
const movesByBorgId = new Map()
for (const b of Object.values(wikiMoves.borgs || {})) {
  if (b.id) movesByBorgId.set(b.id, b.moves || [])
}
const borgsWithMoves = borgs.map((b) => ({
  ...b,
  moves: movesByBorgId.get(b.id) || []
}))
writeJson('borg-moves.json', {
  source: [
    'research/symbols/NTSC_Borgs.csv',
    'research/decomp/data/wiki-borg-moves.json'
  ],
  crossValidation: wikiMoves.crossValidation,
  count: borgsWithMoves.length,
  withMoves: borgsWithMoves.filter((b) => b.moves.length > 0).length,
  borgs: borgsWithMoves
})

syncModelAssets()
console.log('Done. Output in docs-site/.vitepress/data/')
