import { test } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';

test('Node consumes built camera math while browser tooling consumes source', async () => {
  assert.match(import.meta.resolve('@gf/camera-math'), /\/dist\/index\.js$/);
  const pkg = JSON.parse(await readFile(new URL('./package.json', import.meta.url), 'utf8'));
  assert.equal(pkg.exports['.'].browser, './src/index.ts');
  const camera = await import('@gf/camera-math');
  assert.ok(Object.keys(camera).length > 0);
});
