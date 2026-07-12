// VitePress reliably copies normal public files, but the generated Borg model
// tree is large and can be absent from dist after build. Copy it explicitly so
// GitHub Pages contains every pl#### folder, not just the shared library.

import { cpSync, existsSync, mkdirSync, readdirSync } from 'node:fs'
import { dirname, join } from 'node:path'
import { fileURLToPath } from 'node:url'

const __filename = fileURLToPath(import.meta.url)
const __dirname = dirname(__filename)
const SITE_ROOT = join(__dirname, '..')
const PUBLIC_MODELS = join(SITE_ROOT, 'public', 'models')
const DIST_MODELS = join(SITE_ROOT, '.vitepress', 'dist', 'models')

if (process.env.GF_ATLAS_SKIP_MODELS === '1') {
  console.log('  dist model sync skipped (GF_ATLAS_SKIP_MODELS=1)')
  process.exit(0)
}

if (!existsSync(PUBLIC_MODELS)) {
  throw new Error(`Missing public model assets: ${PUBLIC_MODELS}`)
}

if (!existsSync(join(SITE_ROOT, '.vitepress', 'dist'))) {
  throw new Error('Missing .vitepress/dist; run vitepress build before sync-dist-models.')
}

mkdirSync(DIST_MODELS, { recursive: true })
cpSync(PUBLIC_MODELS, DIST_MODELS, {
  recursive: true,
  force: true
})

const sourceBorgs = readdirSync(PUBLIC_MODELS, { withFileTypes: true })
  .filter((entry) => entry.isDirectory() && /^pl[0-9a-f]{4}$/i.test(entry.name))
  .map((entry) => entry.name)
  .sort()

const distBorgs = readdirSync(DIST_MODELS, { withFileTypes: true })
  .filter((entry) => entry.isDirectory() && /^pl[0-9a-f]{4}$/i.test(entry.name))
  .map((entry) => entry.name)
  .sort()

const distSet = new Set(distBorgs)
const missing = sourceBorgs.filter((id) => !distSet.has(id))
if (missing.length) {
  throw new Error(`Missing ${missing.length} Borg model folders in dist: ${missing.slice(0, 20).join(', ')}`)
}

console.log(`  synced ${distBorgs.length} Borg model folders to .vitepress/dist/models`)
