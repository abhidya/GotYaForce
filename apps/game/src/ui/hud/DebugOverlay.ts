/**
 * DebugOverlay — a minimal, toggleable read-only readout of BorgRuntime sim fields for the
 * currently-focused borg. Built for ATK-015 (research/tasks/attack-port/ATK-015-debug-overlay-fields.md)
 * so trace sessions (T1-T10) can eyeball sim state against Dolphin side-by-side.
 *
 * Deliberately dead simple: one absolutely-positioned monospace <pre>, no framework, no SVG,
 * plain textContent updates from the render loop. Read-only over BattleState — never mutates
 * the borg/battle it reads (see the `update()` body below; it only reads `b.*` and formats
 * strings).
 *
 * Fields not yet present on BorgRuntime today (burstArmFrames/burstActive/statusId/statusTimer/
 * movementContext — landing in later ATK tickets) are feature-detected with `in` checks so this
 * compiles and degrades gracefully both before and after those tickets land. lastDamageDealt/
 * lastDamageTaken are intentionally deferred — see research/tasks/attack-port/NOTES-ATK-015.md.
 */

import type { BattleActorObservation } from "@gf/combat";

export interface DebugOverlayHandle {
  /** Read-only refresh from the current BorgRuntime (or null when nothing is focused/selected). */
  update: (borg: BattleActorObservation | null) => void;
  /** Show/hide without tearing down the DOM node. */
  setVisible: (visible: boolean) => void;
  visible: boolean;
  destroy: () => void;
}

/** Loosely-typed view of BorgRuntime fields that later ATK tickets may add. Feature-detected
 *  with `in` at read time — never assumed present. */
interface FutureBorgFields {
  burstArmFrames?: number;
  burstActive?: boolean;
  statusId?: string | number | null;
  statusTimer?: number;
  movementContext?: unknown;
  lastDamageDealt?: number;
  lastDamageTaken?: number;
}

function fmt(n: number | undefined | null, digits = 1): string {
  if (n === undefined || n === null || !Number.isFinite(n)) return "-";
  return n.toFixed(digits);
}

export function createDebugOverlay(container: HTMLElement): DebugOverlayHandle {
  const pre = document.createElement("pre");
  pre.className = "gf-debug-overlay";
  Object.assign(pre.style, {
    position: "absolute",
    top: "8px",
    left: "8px",
    margin: "0",
    padding: "8px 10px",
    background: "rgba(0, 0, 0, 0.72)",
    color: "#7CFC7C",
    font: "12px/1.4 'Consolas', 'Menlo', monospace",
    whiteSpace: "pre",
    pointerEvents: "none",
    zIndex: "50",
    borderRadius: "4px",
    maxWidth: "46ch",
  } satisfies Partial<CSSStyleDeclaration>);
  pre.textContent = "";
  pre.style.display = "none";
  container.appendChild(pre);

  const handle: DebugOverlayHandle = {
    update,
    setVisible,
    visible: false,
    destroy: () => {
      pre.remove();
    },
  };

  function setVisible(v: boolean): void {
    handle.visible = v;
    pre.style.display = v ? "block" : "none";
  }

  function update(borg: BattleActorObservation | null): void {
    if (!handle.visible) return;
    if (!borg) {
      pre.textContent = "[debug] no focused borg";
      return;
    }
    const b = borg as BattleActorObservation & FutureBorgFields;
    const lines: string[] = [];

    lines.push(`${b.borgId}  uid=${b.uid}  team=${b.team}`);
    lines.push(`state       ${b.state}  (t=${b.stateTime})`);
    lines.push(`balance     ${fmt(b.balanceGauge, 0)} / ${fmt(b.balanceGaugeMax, 0)}`);
    lines.push(`down        ${fmt(b.downGauge, 0)} / base ${fmt(b.downGaugeBase, 0)}`);
    lines.push(
      `combo       accum=${fmt(b.comboAccum, 0)} rank=${fmt(b.comboRank, 0)} window=${fmt(b.comboWindow, 0)}`,
    );
    lines.push(`invinc      ${fmt(b.invincTimer, 0)}`);

    // Ammo: weapon cells if present (future ticket), else the single pool + reload cooldown.
    if ("weaponCells" in b) {
      lines.push(`ammo(cells) ${JSON.stringify((b as unknown as { weaponCells: unknown }).weaponCells)}`);
    } else {
      const reload = b.cooldowns?.["reload"] ?? 0;
      lines.push(`ammo        ${fmt(b.ammo, 0)}  reload=${fmt(reload, 0)}`);
    }

    // Fields other ATK tickets will add; feature-detect so this compiles before and after.
    if ("burstArmFrames" in b || "burstActive" in b) {
      const armFrames = "burstArmFrames" in b ? fmt(b.burstArmFrames, 0) : "-";
      const active = "burstActive" in b ? String(Boolean(b.burstActive)) : "-";
      lines.push(`burst       arm=${armFrames} active=${active}`);
    }
    if ("statusId" in b || "statusTimer" in b) {
      const id = "statusId" in b ? String(b.statusId ?? "none") : "-";
      const timer = "statusTimer" in b ? fmt(b.statusTimer, 0) : "-";
      lines.push(`status      id=${id} timer=${timer}`);
    }
    if ("movementContext" in b) {
      lines.push(`moveCtx     ${JSON.stringify(b.movementContext)}`);
    }
    if ("lastDamageDealt" in b || "lastDamageTaken" in b) {
      const dealt = "lastDamageDealt" in b ? fmt(b.lastDamageDealt, 0) : "-";
      const taken = "lastDamageTaken" in b ? fmt(b.lastDamageTaken, 0) : "-";
      lines.push(`lastDamage  dealt=${dealt} taken=${taken}`);
    }

    pre.textContent = lines.join("\n");
  }

  return handle;
}
