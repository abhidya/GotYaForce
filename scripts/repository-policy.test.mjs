import assert from 'node:assert/strict'
import fs from 'node:fs'
import path from 'node:path'
import test from 'node:test'
import { fileURLToPath } from 'node:url'

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..')

// Every workflow, not just ci.yml: deploy-pages.yml floated on `@v4`/`@v5`
// tags until 2026-08-29 while ci.yml was pinned, so the rule only covered the
// workflow that could not push anything. The deploy workflow is the one with
// `pages: write` and `id-token: write`, so it is the one a retagged upstream
// action would hurt most.
test('GitHub Action revisions are immutable in every workflow', () => {
  const workflowDir = path.join(repoRoot, '.github', 'workflows')
  const workflowFiles = fs
    .readdirSync(workflowDir)
    .filter((name) => name.endsWith('.yml') || name.endsWith('.yaml'))
  assert.ok(workflowFiles.length > 0, '.github/workflows must contain at least one workflow')

  let seen = 0
  for (const file of workflowFiles) {
    const workflow = fs.readFileSync(path.join(workflowDir, file), 'utf8')
    const actionRefs = [...workflow.matchAll(/^\s*(?:-\s*)?uses:\s*([^\s#]+)/gm)].map(
      (match) => match[1],
    )
    for (const actionRef of actionRefs) {
      if (actionRef.startsWith('./') || actionRef.startsWith('docker://')) continue
      seen += 1
      const separator = actionRef.lastIndexOf('@')
      assert.notEqual(separator, -1, `missing action revision: ${file}: ${actionRef}`)
      assert.match(
        actionRef.slice(separator + 1),
        /^[0-9a-f]{40}$/,
        `mutable GitHub Action revision: ${file}: ${actionRef}`,
      )
    }
  }
  assert.ok(seen > 0, 'workflows must invoke at least one external action')
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

// Combat and other workspace packages are part of the shipped game bundle.
// A merge that changes only those packages must not leave Pages on old code.
test('Pages deploy watches shared game code and build inputs', () => {
  const workflow = fs.readFileSync(path.join(repoRoot, '.github/workflows/deploy-pages.yml'), 'utf8')
  const push = workflow.match(/^  push:\r?\n([\s\S]*?)^  workflow_dispatch:/m)
  assert.ok(push, 'Pages must deploy main pushes as well as manual runs')
  assert.match(push[1], /branches: \[main\]/)
  const paths = [...push[1].matchAll(/^      - '([^']+)'/gm)].map((match) => match[1])
  for (const input of ['apps/game/**', 'packages/**', 'scripts/**', 'package.json',
    'pnpm-lock.yaml', 'pnpm-workspace.yaml', 'tsconfig*.json']) {
    assert.ok(paths.includes(input), `Pages push filter excludes game build input: ${input}`)
  }
})

test('Contributor gate runs the Double clone mirror selfcheck', () => {
  const { scripts } = JSON.parse(fs.readFileSync(path.join(repoRoot, 'package.json'), 'utf8'))
  assert.equal(scripts['selfcheck:double-clone-mirror'],
    'node scripts/run-double-clone-mirror-selfcheck.mjs')
  const checks = scripts['verify:contributor'].split(/\s*&&\s*/)
  assert.ok(checks.includes('pnpm selfcheck:double-clone-mirror'),
    'clone pose and resource-isolation tests must run in the contributor gate')
})
