using System;
using System.IO;
using System.Linq;
using HSDRaw;
using HSDRaw.Common;
using HSDRawViewer.Converters;
using HSDRawViewer.Tools.Animation;

class Exporter {
    static void ExportArc(string path, int skip, string outDir, bool tex, int maxModels = int.MaxValue) {
        Directory.CreateDirectory(outDir);
        byte[] all = File.ReadAllBytes(path);
        var f = new HSDRawFile(skip>0 ? all.Skip(skip).ToArray() : all);
        int mi = 0, ok = 0, err = 0;
        foreach (var r in f.Roots) {
            var sobj = new HSD_SOBJ(){ _s = r.Data._s };
            if (sobj.JOBJDescs?.Array == null) continue;
            foreach (var jd in sobj.JOBJDescs.Array) {
                if (mi >= maxModels) break;
                if (jd?.RootJoint == null) { mi++; continue; }
                var settings = new ModelExportSettings { ExportMesh=true, ExportTextures=tex, ExportBindPose=true, Optimize=true };
                string outPath = Path.Combine(outDir, $"model_{mi:D2}.dae");
                try {
                    ModelExporter.ExportFile(outPath, jd.RootJoint, settings, new JointMap());
                    long sz = File.Exists(outPath)? new FileInfo(outPath).Length : 0;
                    if (mi<3 || sz>50000) Console.WriteLine($"  [{mi:D2}] OK model_{mi:D2}.dae ({sz} b)");
                    ok++;
                } catch (Exception e) {
                    if (err<2) Console.WriteLine($"  [{mi:D2}] ERR {e.GetType().Name}@{e.StackTrace?.Split('\n')[0]?.Trim()}: {e.Message}");
                    err++;
                }
                mi++;
            }
        }
        var files = Directory.GetFiles(outDir);
        Console.WriteLine($"  => {Path.GetFileName(outDir)}: models ok={ok} err={err}; files dae={files.Count(x=>x.EndsWith(".dae"))} png={files.Count(x=>x.EndsWith(".png"))}");
    }
    static void Main() {
        string root=@"D:\GotYaForce\user-data\GG4E\afs_data\root\";
        string outb=@"D:\GotYaForce\user-data\GG4E\gltf-export\";
        bool TEX = Environment.GetEnvironmentVariable("TEX")=="1";
        Console.WriteLine($"Textures={TEX}");
        // Batch mode for the fixed-pipeline borg model re-export: iterate every staged
        // pl####_mdl.arc and export ONLY model_00 (the runtime model) per borg.
        string batchDir = Environment.GetEnvironmentVariable("BATCH_DIR");
        if (!string.IsNullOrEmpty(batchDir)) {
            string batchOut = Environment.GetEnvironmentVariable("BATCH_OUT") ?? Path.Combine(outb, "borg-models-fixed");
            var arcs = Directory.GetFiles(batchDir, "pl*_mdl.arc").OrderBy(x => x).ToArray();
            Console.WriteLine($"batch: {arcs.Length} arcs -> {batchOut}");
            int done = 0;
            foreach (var arc in arcs) {
                string borg = Path.GetFileName(arc).Replace("_mdl.arc", "");
                try {
                    ExportArc(arc, 0x100, Path.Combine(batchOut, borg), TEX, 1);
                } catch (Exception e) {
                    Console.WriteLine($"  == {borg}: ARC-LEVEL ERR {e.GetType().Name}: {e.Message}");
                }
                done++;
                if (done % 25 == 0) Console.WriteLine($"batch progress {done}/{arcs.Length}");
            }
            Console.WriteLine($"batch complete {done}/{arcs.Length}");
            return;
        }
        string only = Environment.GetEnvironmentVariable("ONLY");
        if (!string.IsNullOrEmpty(only)) {
            string outName = Environment.GetEnvironmentVariable("OUTDIR") ?? only;
            Console.WriteLine($"== {only} -> {outName} ==");
            int skip = only.StartsWith("pl") ? 0x100 : 0;
            ExportArc(root+only+"_mdl.arc", skip, outb+outName, TEX);
            return;
        }
        Console.WriteLine("== box00 =="); ExportArc(root+"box00_mdl.arc", 0, outb+"box00", TEX);
        Console.WriteLine("== pl0f06k =="); ExportArc(root+"pl0f06k_mdl.arc", 0x100, outb+"pl0f06k", TEX);
        Console.WriteLine("== pl0000 =="); ExportArc(root+"pl0000_mdl.arc", 0x100, outb+"pl0000", TEX);
    }
}
