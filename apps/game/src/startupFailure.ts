/** Visible host-level failure, never a claim that unsupported graphics can play. */
export function showStartupFailure(error: unknown): void {
  console.error("[startup] Game could not start", error);
  document.documentElement.dataset.gfRuntime = "boot-failed";
  const host = document.getElementById("ui");
  if (!host) return;
  host.replaceChildren();
  host.style.pointerEvents = "auto";
  const panel = document.createElement("div");
  panel.setAttribute("role", "alert");
  panel.style.cssText =
    "position:absolute;inset:35% 5% auto;margin:auto;max-width:640px;padding:24px;" +
    "color:#fff;background:#101722;border:1px solid #7388a4;text-align:center;font:16px/1.5 system-ui;";
  const detail = error instanceof Error ? error.message : String(error);
  const message = document.createElement("p");
  message.textContent = /webgl|graphics context/i.test(detail)
    ? "The game could not start 3D graphics. Try an up-to-date browser with WebGL 2 and hardware acceleration enabled, then reload."
    : "The game could not finish starting. Check your connection, then reload. If it keeps failing, share the error below.";
  const reason = document.createElement("p");
  reason.textContent = detail;
  const retry = document.createElement("button");
  retry.textContent = "Reload game";
  retry.addEventListener("click", () => window.location.reload());
  panel.append(message, reason, retry);
  host.appendChild(panel);
}
