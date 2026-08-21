import assert from 'node:assert/strict'
import fs from 'node:fs'
import path from 'node:path'
import test from 'node:test'
import { fileURLToPath } from 'node:url'

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..')

test('contributor CI uses immutable GitHub Action revisions', () => {
  const workflow = fs.readFileSync(
    path.join(repoRoot, '.github', 'workflows', 'ci.yml'),
    'utf8',
  )
  const actionRefs = [...workflow.matchAll(/^\s*(?:-\s*)?uses:\s*([^\s#]+)/gm)].map(
    (match) => match[1],
  )

  assert.ok(actionRefs.length > 0, 'ci.yml must invoke at least one action')
  for (const actionRef of actionRefs) {
    if (actionRef.startsWith('./') || actionRef.startsWith('docker://')) continue
    const separator = actionRef.lastIndexOf('@')
    assert.notEqual(separator, -1, `missing action revision: ${actionRef}`)
    assert.match(
      actionRef.slice(separator + 1),
      /^[0-9a-f]{40}$/,
      `mutable GitHub Action revision: ${actionRef}`,
    )
  }
})

test('pnpm lockfile importers refer to existing workspace packages', () => {
  const lockfile = fs.readFileSync(path.join(repoRoot, 'pnpm-lock.yaml'), 'utf8')
  const importerBlock = lockfile.match(/^importers:\r?\n([\s\S]*?)^packages:\r?$/m)
  assert.ok(importerBlock, 'pnpm-lock.yaml must contain an importers block')

  const importers = [...importerBlock[1].matchAll(/^  (\S.*?):(?:\s+\{\})?\r?$/gm)].map(
    (match) => match[1].replace(/^['"]|['"]$/g, ''),
  )
  assert.ok(importers.includes('.'), 'root workspace importer is missing')
  for (const importer of importers) {
    assert.ok(
      fs.existsSync(path.join(repoRoot, importer, 'package.json')),
      `lockfile importer has no workspace package: ${importer}`,
    )
  }
})
