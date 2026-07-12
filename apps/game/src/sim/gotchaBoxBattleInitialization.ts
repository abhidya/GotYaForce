/** Minimal settlement lifecycle needed while turning a successful bootstrap into an active battle. */
export interface BattleSettlementLifecycle {
  begin(): void;
  revert(): void;
}

/**
 * Bootstrap has no Gotcha-Box side effects. Once begin succeeds, every initialization failure
 * reverts the transaction before the original error continues to the caller's recovery path.
 */
export async function initializeGotchaBoxBattle<TBoot>(
  bootstrap: () => Promise<TBoot>,
  settlement: BattleSettlementLifecycle,
  initialize: (boot: TBoot) => void | Promise<void>,
): Promise<void> {
  const boot = await bootstrap();
  let began = false;
  try {
    settlement.begin();
    began = true;
    await initialize(boot);
  } catch (error) {
    if (began) settlement.revert();
    throw error;
  }
}
