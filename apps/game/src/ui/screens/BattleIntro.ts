/**
 * BattleIntro — Challenge pre-battle VS / briefing screen.
 *
 * The original overlays player/enemy plates, a VS marker, arena preview, and the
 * objective ribbon before the A-button battle transition. The preview window is
 * transparent so the already-loaded stage canvas can show through behind this UI.
 *
 * Surface: the exported `brif00` scene GLB is the primary surface (promoted from
 * a faint low-opacity backdrop to the real full-opacity briefing stage this
 * screen is built around), matching the task's "use the real briefing/entry
 * scene sequencing" direction. No dedicated real capture exists for this
 * specific screen: `reference/captures/BRANCHES.md` and the numbered
 * `challenge-N-*` capture set stop at `challenge-6-edit-force.png` (the next
 * captured frame, `challenge-7-vs-battle-matchup.png`, is verified to actually
 * be the in-battle HUD mid-fight, not a pre-battle VS/briefing screen — see the
 * BRANCHES.md flow list, which has no separate "battle intro" entry). All
 * dynamic text (borg names, arena name, energy numbers, the battle label) is
 * the real exported ascii.tpl bitmap font (see bitmapText.ts) instead of plain
 * DOM text, per the same convention as every other rebuilt screen; only the
 * "Vs." mark and "DEFEAT ENEMY GOTCHA BORGS!" objective — copy the original
 * shows as fixed baked art, not per-battle data — also render in bitmap font
 * since there is no separate exported texture isolating just that glyph.
 */

import { arenaNameForStageByte, arenaNameForStageId, type MissionBattleConfig } from "@gf/missions";
import { bitmapText, setBitmapText } from "../bitmapText.js";
import { borgMiniPath } from "../assets.js";
import { el, legendItem } from "../dom.js";
import { subscribeMenuInput, type MenuAction } from "../menuInput.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";
import type { ForceBorg } from "./ForceBuilder.js";

export interface BattleIntroOptions {
  config: MissionBattleConfig;
  catalog: readonly ForceBorg[];
  onConfirm: () => void;
  onBack?: () => void;
}

export interface BattleIntroHandle {
  destroy: () => void;
}

export function createBattleIntro(
  container: HTMLElement,
  opts: BattleIntroOptions,
): BattleIntroHandle {
  const byId = new Map(opts.catalog.map((b) => [b.id, b] as const));
  const playerIds = opts.config.forces
    .filter((force) => force.team === "player")
    .flatMap((force) => force.borgIds);
  const enemyIds = opts.config.forces
    .filter((force) => force.team === "enemy")
    .flatMap((force) => force.borgIds);
  const playerEnergy = forceEnergy(playerIds, byId);
  const enemyEnergy = opts.config.meta?.enemyForceEnergy ?? forceEnergy(enemyIds, byId);
  const playerLead = playerIds[0] ?? "";
  const enemyLead = enemyIds[0] ?? "";
  const arenaName = arenaNameFor(opts.config);

  const root = el("div", { class: "gf-screen gf-battle-intro" });
  const briefingScene = createUiSceneHost("gf-ui-scene gf-brief-real-scene");
  root.appendChild(briefingScene);

  const title = bitmapText("gf-brief-title-text");
  setBitmapText(title, opts.config.label ?? "BATTLE VS", { bold: true, scale: 2, tint: "#ffd21e" });
  root.appendChild(el("h1", { class: "gf-brief-title", attrs: { "aria-label": opts.config.label ?? "BATTLE VS" } }, [title]));

  root.appendChild(sidePlate("player", playerLead, `${playerEnergy} ALLY`, byId.get(playerLead)?.name ?? "PLAYER"));
  root.appendChild(sidePlate("enemy", enemyLead, `ENEMY ${enemyEnergy}`, byId.get(enemyLead)?.name ?? "ENEMY"));

  const vsText = bitmapText("gf-brief-vs-text");
  setBitmapText(vsText, "VS.", { bold: true, scale: 3, tint: "#ffffff" });
  root.appendChild(el("div", { class: "gf-brief-vs" }, [vsText]));

  const objectiveText = bitmapText("gf-brief-objective-text");
  setBitmapText(objectiveText, "DEFEAT ENEMY GOTCHA BORGS!", { bold: true, scale: 1, tint: "#ffffff" });
  const arenaNameText = bitmapText("gf-brief-arena-name-text");
  if (arenaName) setBitmapText(arenaNameText, arenaName, { bold: true, scale: 1, tint: "#ffffff" });
  root.appendChild(
    el("div", { class: "gf-brief-preview" }, [
      ...(arenaName ? [el("div", { class: "gf-brief-arena-name" }, [arenaNameText])] : []),
      el("div", { class: "gf-brief-objective" }, [objectiveText]),
    ]),
  );

  const chooseLabel = bitmapText("gf-legend-label");
  setBitmapText(chooseLabel, "CHOOSE", { bold: true, scale: 1 });
  root.appendChild(
    el("div", { class: "gf-legend" }, [
      el("span", { class: "gf-legend-item" }, [chooseLabel]),
      legendItem("b", "BACK"),
      legendItem("a", "CONFIRM"),
    ]),
  );

  function onMenuAction(action: MenuAction): void {
    if (action === "confirm") {
      opts.onConfirm();
    } else if (action === "back") {
      opts.onBack?.();
    }
  }

  container.appendChild(root);
  const stopBriefingScene = mountUiSceneModels(briefingScene, {
    sceneId: "brif00",
    fitSize: 900,
    camera: { fov: 31, position: [0, 140, 780], lookAt: [0, 30, 0] },
    rotation: [-0.1, 0, 0],
    maxModels: 27,
  });
  const unsubscribeMenuInput = subscribeMenuInput((event) => onMenuAction(event.action));

  return {
    destroy: () => {
      unsubscribeMenuInput();
      stopBriefingScene();
      root.remove();
    },
  };
}

/**
 * Authentic Versus-select arena name for this battle's stage (DERIVED — see
 * STAGE_ARENA_NAMES in @gf/missions / research/decomp/challenge-stage-naming-2026-07-05.md).
 * Prefers the raw Challenge stage byte (meta.stageByte) so family variants
 * (st2x/st4x) resolve to their base arena's name; falls back to decoding the
 * `arena` (st## id) directly for non-Challenge callers.
 */
function arenaNameFor(config: MissionBattleConfig): string | null {
  const stageByte = config.meta?.stageByte;
  if (typeof stageByte === "number") {
    const name = arenaNameForStageByte(stageByte);
    if (name) return name;
  }
  return arenaNameForStageId(config.arena);
}

function forceEnergy(ids: readonly string[], byId: ReadonlyMap<string, ForceBorg>): number {
  return ids.reduce((sum, id) => sum + (byId.get(id)?.energy ?? 0), 0);
}

function sidePlate(kind: "player" | "enemy", lead: string, energyLabel: string, name: string): HTMLElement {
  const icon =
    lead === ""
      ? el("span", { class: "gf-brief-emblem" })
      : el("img", { class: "gf-brief-icon", attrs: { src: borgMiniPath(lead), alt: name } });
  const energyText = bitmapText("gf-brief-energy-text");
  setBitmapText(energyText, energyLabel, { bold: true, scale: 1, tint: "#ffffff" });
  const nameText = bitmapText("gf-brief-name-text");
  setBitmapText(nameText, name, { bold: true, scale: 1, tint: "#ffffff" });
  return el("div", { class: `gf-brief-side gf-brief-${kind}` }, [
    icon,
    el("div", { class: `gf-brief-energy gf-brief-energy-${kind}` }, [energyText]),
    el("div", { class: "gf-brief-name" }, [nameText]),
  ]);
}
