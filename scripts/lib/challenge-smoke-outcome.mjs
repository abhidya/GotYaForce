/** Describe exactly what a Challenge simulation established, without equating
 * partial attrition with a completed battle. Strict mode is for victory checks. */
export function challengeSmokeOutcome(result, enemyAttrition, requireVictory = false) {
  if (requireVictory && result !== 'win') {
    throw new Error(`1P Challenge victory check failed: result=${result}, enemyAttrition=${enemyAttrition}`);
  }
  if (result === 'ongoing' && enemyAttrition <= 0) {
    throw new Error('1P Challenge smoke failed: battle neither resolved nor produced enemy attrition');
  }
  return result === 'ongoing' ? 'partial-attrition-only' : `battle-${result}`;
}
