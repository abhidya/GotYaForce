import { test } from 'node:test';
import assert from 'node:assert/strict';
import { challengeSmokeOutcome } from './challenge-smoke-outcome.mjs';

test('partial attrition is reported as incomplete, not a battle victory', () => {
  assert.equal(challengeSmokeOutcome('ongoing', 100), 'partial-attrition-only');
  assert.throws(() => challengeSmokeOutcome('ongoing', 0), /neither resolved/);
  assert.throws(() => challengeSmokeOutcome('ongoing', 100, true), /victory check failed/);
});
test('strict mode accepts only a player win', () => {
  assert.equal(challengeSmokeOutcome('win', 100, true), 'battle-win');
  for (const result of ['lose', 'draw']) assert.throws(() => challengeSmokeOutcome(result, 100, true), /victory check failed/);
});
