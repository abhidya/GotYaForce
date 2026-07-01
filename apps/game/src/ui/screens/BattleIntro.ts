/**
 * BattleIntro — Challenge pre-battle VS / briefing screen.
 *
 * The original overlays player/enemy plates, a VS marker, arena preview, and the
 * objective ribbon before the A-button battle transition. The preview window is
 * transparent so the already-loaded stage canvas can show through behind this UI.
 */

import type { BattleConfig } from "@gf/missions";
import { ASSETS, borgMiniPath } from "../assets.js";
import { el, legendItem } from "../dom.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";
import type { ForceBorg } from "./ForceBuilder.js";

export interface BattleIntroOptions {
  config: BattleConfig;
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

  const root = el("div", { class: "gf-screen gf-battle-intro" });
  const briefingScene = createUiSceneHost("gf-ui-scene gf-brief-real-scene");
  root.appendChild(briefingScene);
  root.appendChild(
    el("img", { class: "gf-brief-vs-sheet", attrs: { src: ASSETS.briefingVs, alt: "", "aria-hidden": "true" } }),
  );
  root.appendChild(
    el("img", { class: "gf-brief-label-sheet", attrs: { src: ASSETS.vsSelectLabels, alt: "", "aria-hidden": "true" } }),
  );

  root.appendChild(el("h1", { class: "gf-brief-title", text: opts.config.label ?? "BATTLE VS" }));
  root.appendChild(
    sidePlate("player", playerLead, `${playerEnergy} ALLY`, byId.get(playerLead)?.name ?? "PLAYER"),
  );
  root.appendChild(
    sidePlate("enemy", enemyLead, `ENEMY ${enemyEnergy}`, byId.get(enemyLead)?.name ?? "ENEMY"),
  );
  root.appendChild(el("div", { class: "gf-brief-vs", text: "Vs." }));
  root.appendChild(
    el("div", { class: "gf-brief-preview" }, [
      el("div", { class: "gf-brief-objective", text: "DEFEAT ENEMY GOTCHA BORGS!" }),
    ]),
  );

  root.appendChild(
    el("div", { class: "gf-legend" }, [
      el("span", { class: "gf-legend-item" }, [el("span", { text: "CHOOSE" })]),
      legendItem("b", "BACK"),
      legendItem("a", "CONFIRM"),
    ]),
  );

  function onKey(ev: KeyboardEvent): void {
    if (ev.key === "Enter" || ev.key.toLowerCase() === "a") {
      opts.onConfirm();
      ev.preventDefault();
    } else if (ev.key === "Escape" || ev.key.toLowerCase() === "b") {
      opts.onBack?.();
      ev.preventDefault();
    }
  }

  container.appendChild(root);
  const stopBriefingScene = mountUiSceneModels(briefingScene, {
    sceneId: "brif00",
    fitSize: 720,
    camera: { fov: 31, position: [0, 130, 900], lookAt: [0, 20, 0] },
    rotation: [-0.12, 0, 0],
    maxModels: 27,
  });
  window.addEventListener("keydown", onKey);

  return {
    destroy: () => {
      window.removeEventListener("keydown", onKey);
      stopBriefingScene();
      root.remove();
    },
  };
}

function forceEnergy(ids: readonly string[], byId: ReadonlyMap<string, ForceBorg>): number {
  return ids.reduce((sum, id) => sum + (byId.get(id)?.energy ?? 0), 0);
}

function sidePlate(kind: "player" | "enemy", lead: string, energyLabel: string, name: string): HTMLElement {
  const icon =
    lead === ""
      ? el("span", { class: "gf-brief-emblem" })
      : el("img", { class: "gf-brief-icon", attrs: { src: borgMiniPath(lead), alt: name } });
  return el("div", { class: `gf-brief-side gf-brief-${kind}` }, [
    icon,
    el("div", { class: `gf-brief-energy gf-brief-energy-${kind}`, text: energyLabel }),
    el("div", { class: "gf-brief-name", text: name }),
  ]);
}
