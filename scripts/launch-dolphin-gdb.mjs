import { spawn } from "node:child_process";
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const argsByName = parseArgs(process.argv.slice(2));
const dolphinExe = argsByName.get("dolphin") ?? process.env.DOLPHIN_EXE ?? path.join(repoRoot, "dolphin", "Dolphin.exe");
const isoPath = argsByName.get("iso") ?? process.env.GF_ISO ?? path.join(repoRoot, "Gotcha Force.iso");
const userDir = argsByName.get("user") ?? process.env.DOLPHIN_USER ?? path.join(repoRoot, "user-data", "dolphin-trace");
const gdbPort = argsByName.get("port") ?? process.env.GDB_PORT ?? "5555";
const saveState = argsByName.get("save-state") ?? process.env.DOLPHIN_SAVE_STATE;

function parseArgs(argv) {
  const parsed = new Map();
  for (let i = 0; i < argv.length; i += 1) {
    const arg = argv[i];
    if (!arg.startsWith("--")) continue;
    const eq = arg.indexOf("=");
    if (eq >= 0) parsed.set(arg.slice(2, eq), arg.slice(eq + 1));
    else parsed.set(arg.slice(2), argv[++i] ?? "");
  }
  return parsed;
}

fs.mkdirSync(userDir, { recursive: true });

const args = [
  "--user",
  userDir,
  "--exec",
  isoPath,
  "--config",
  `Dolphin.General.GDBPort=${gdbPort}`,
  "--debugger",
  "--logger",
];

if ((argsByName.get("batch") ?? process.env.DOLPHIN_BATCH) !== "0") args.splice(2, 0, "--batch");
if (saveState) args.splice(args.indexOf("--config"), 0, "--save_state", saveState);

const child = spawn(dolphinExe, args, {
  detached: true,
  stdio: "ignore",
  windowsHide: true,
});

child.unref();

console.log(JSON.stringify({
  pid: child.pid,
  dolphinExe,
  args,
  userDir,
  gdbPort,
}, null, 2));
