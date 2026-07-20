// force_create_missing_functions.java
// Run in Ghidra (Script Manager or analyzeHeadless) to force-create the 8 functions
// that the OGhidra coverage scan flagged as Ghidra-side gaps.
//
// Source: research/decomp/ogh-coverage-<date>.json -> ghidra_missing_true_gaps
// Plus the 3 Borg-constructor template entries that the prologue scan can't see.
//
// Headless invocation:
//   analyzeHeadless.bat D:\GotYaForce\research\decomp GotchaForce ^
//       -process boot.dol -noanalysis ^
//       -scriptPath D:\GotYaForce\scripts ^
//       -postScript force_create_missing_functions.java
//
// @category OGhidra

import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.listing.Listing;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;
import java.util.regex.Pattern;

public class force_create_missing_functions extends GhidraScript {

    // Hand-curated template-ctor entries (no prologue; reached via function-pointer table).
    private static final String[] TEMPLATE_CTORS = {
        "0x8007ca5c",  // NORMAL TANK / LEOPARD ctor
        "0x800cfe9c",  // ARROW NINJA / SHIJIMA ctor
        "0x80129608",  // EAGLE ROBOT / PROTO EAGLE ctor
    };

    private static final Pattern REPORT_PATTERN =
        Pattern.compile("ogh-coverage-\\d{4}-\\d{2}-\\d{2}\\.json$");

    @Override
    protected void run() throws Exception {
        // Repo root: D:\GotYaForce (script is in D:\GotYaForce\scripts)
        File repoRoot = new File("D:\\GotYaForce");
        if (!repoRoot.exists()) {
            // Fall back: derive from getSourceFile() which returns a ResourceFile
            try {
                Object src = getSourceFile();
                if (src != null) {
                    String path = src.toString();
                    File scriptFile = new File(path);
                    repoRoot = scriptFile.getParentFile().getParentFile();
                }
            } catch (Throwable t) {
                // ignore - use hardcoded path above
            }
        }
        if (repoRoot == null || !repoRoot.exists()) {
            println("ERROR: could not resolve repo root");
            return;
        }

        File decompDir = new File(repoRoot, "research" + File.separator + "decomp");
        List<String> gapList = new ArrayList<>();
        String reportName = null;

        if (decompDir.isDirectory()) {
            File[] reports = decompDir.listFiles(
                (dir, name) -> REPORT_PATTERN.matcher(name).matches());
            if (reports != null && reports.length > 0) {
                File latest = reports[0];
                for (File r : reports) {
                    if (r.getName().compareTo(latest.getName()) > 0) latest = r;
                }
                reportName = latest.getName();
                try (FileReader fr = new FileReader(latest)) {
                    JsonObject root = JsonParser.parseReader(fr).getAsJsonObject();
                    if (root.has("ghidra_missing_true_gaps")) {
                        for (JsonElement e : root.getAsJsonArray("ghidra_missing_true_gaps")) {
                            gapList.add(e.getAsString());
                        }
                    }
                } catch (Exception ex) {
                    println("WARN: failed to parse " + latest + ": " + ex.getMessage());
                }
            }
        }

        println("Loaded " + gapList.size() + " gaps from " +
                (reportName != null ? reportName : "(no report)"));

        // Merge gap list with template ctors (preserve order, dedup, normalize).
        Set<String> merged = new LinkedHashSet<>();
        for (String h : gapList) merged.add(normalize(h));
        for (String h : TEMPLATE_CTORS) merged.add(normalize(h));

        println("Force-creating " + merged.size() + " functions:");
        monitor.initialize(merged.size());
        int created = 0, existing = 0, failed = 0;

        for (String hex : merged) {
            String msg = forceCreate(hex);
            println("  " + hex + " : " + msg);
            if (msg.startsWith("created")) created++;
            else if (msg.startsWith("exists")) existing++;
            else failed++;
            monitor.incrementProgress(1);
            if (monitor.isCancelled()) {
                println("CANCELLED by user");
                break;
            }
        }

        println();
        println("Summary: created=" + created + "  existing=" + existing + "  failed=" + failed);

        try {
            currentProgram.save("force-create " + created + " missing functions", monitor);
            println("Program saved.");
        } catch (Exception ex) {
            println("WARN: save failed: " + ex.getMessage());
        }
    }

    private String normalize(String h) {
        String s = h.toLowerCase();
        if (!s.startsWith("0x")) s = "0x" + s;
        return s;
    }

    private String forceCreate(String addressHex) {
        Address addr = currentProgram.getAddressFactory().getAddress(addressHex);
        if (addr == null) return "skip: bad address";

        FunctionManager fm = currentProgram.getFunctionManager();
        Function existing = fm.getFunctionAt(addr);
        if (existing != null) {
            return "exists: already defined as '" + existing.getName() + "'";
        }

        int tx = currentProgram.startTransaction("forceCreate " + addressHex);
        boolean ok = false;
        try {
            // DisassembleCommand handles clearing any conflicting data typing at the address.
            DisassembleCommand disCmd = new DisassembleCommand(addr, null, true);
            disCmd.applyTo(currentProgram, monitor);

            CreateFunctionCmd fnCmd = new CreateFunctionCmd(addr);
            fnCmd.applyTo(currentProgram, monitor);

            Function newFn = fm.getFunctionAt(addr);
            ok = true;
            return (newFn != null) ? "created: '" + newFn.getName() + "'" : "fail: createFunction returned null";
        } catch (Exception ex) {
            return "fail: " + ex.getMessage();
        } finally {
            currentProgram.endTransaction(tx, ok);
        }
    }
}
