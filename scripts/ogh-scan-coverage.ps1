<#
.SYNOPSIS
  Cross-check OGhidra / Ghidra-MCP function coverage against the DOL and source citations.

.DESCRIPTION
  Three signals are joined:
    1. Live MCP /list_functions dump (ground-truth Ghidra FunctionManager set)
    2. DOL prologue scan (stwu r1,-N(r1) preceded by blr/bclr) — what Ghidra SHOULD have defined
    3. Citation harvest from research/ packages/ scripts/ — what the port actually references

  Output: JSON report keyed by gap category. Re-runnable; no hardcoded addresses.

.PARAMETER McpUrl
  OGhidra MCP base URL. Default http://localhost:8080/

.PARAMETER DolPath
  Path to boot.dol. Default repo-relative.

.PARAMETER OutFile
  Where to write the JSON report. Default repo-relative research/decomp/ogh-coverage-<date>.json.

.PARAMETER ScanDirs
  Comma-separated list of dirs to scan for 0x80xxxxxx citations.

.EXAMPLE
  .\scripts\ogh-scan-coverage.ps1
  .\scripts\ogh-scan-coverage.ps1 -McpUrl http://localhost:8081/
#>
[CmdletBinding()]
param(
    [string]$McpUrl = "http://localhost:8080",
    [string]$DolPath = (Join-Path $PSScriptRoot "..\user-data\GG4E\disc\sys\boot.dol"),
    [string]$OutFile,
    [string[]]$ScanDirs = @(
        (Join-Path $PSScriptRoot "..\research"),
        (Join-Path $PSScriptRoot "..\packages"),
        (Join-Path $PSScriptRoot "..\scripts")
    ),
    [int]$PageSize = 500,
    [int]$MaxPages = 60
)

$ErrorActionPreference = "Stop"
$root = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$DolPath = (Resolve-Path $DolPath).Path
if (-not $OutFile) {
    $stamp = Get-Date -Format "yyyy-MM-dd"
    $OutFile = Join-Path $root "research\decomp\ogh-coverage-$stamp.json"
}

function Read-Be32([byte[]]$b, [int]$o) {
    return ([uint32]$b[$o] -shl 24) -bor ([uint32]$b[$o+1] -shl 16) -bor ([uint32]$b[$o+2] -shl 8) -bor [uint32]$b[$o+3]
}

function Test-BlrVariant([uint32]$w) {
    # PowerShell 5.1 parses high-bit hex literals as Int32 (negative), so use [Convert]::ToUInt32
    # to get true unsigned 32-bit values for the comparisons.
    $blr   = [Convert]::ToUInt32('4E800020', 16)
    $blrl  = [Convert]::ToUInt32('4E800021', 16)
    $bctr  = [Convert]::ToUInt32('4E800420', 16)
    $bctrl = [Convert]::ToUInt32('4E800421', 16)
    $bclrMask = [Convert]::ToUInt32('FC0007FF', 16)
    $bclrEq   = [Convert]::ToUInt32('4C000020', 16)
    $bcctrEq  = [Convert]::ToUInt32('4C000420', 16)
    if ($w -eq $blr)   { return $true }
    if ($w -eq $blrl)  { return $true }
    if ($w -eq $bctr)  { return $true }
    if ($w -eq $bctrl) { return $true }
    if (($w -band $bclrMask) -eq $bclrEq)  { return $true }  # bclr[cond]
    if (($w -band $bclrMask) -eq $bcctrEq) { return $true }  # bcctr[cond]
    return $false
}

function Get-McpFunctions {
    param([string]$BaseUrl, [int]$Limit, [int]$MaxP)
    $set = @{}
    $offset = 0
    $page = 0
    $rx = [regex]'^(.+?)\sat\s+([0-9a-fA-F]{8})\s*$'
    while ($page -lt $MaxP) {
        $url = "$BaseUrl/list_functions?offset=$offset&limit=$Limit"
        try {
            $resp = Invoke-WebRequest -Uri $url -TimeoutSec 30 -UseBasicParsing
        } catch {
            Write-Warning "MCP request failed at offset ${offset}: $($_.Exception.Message)"
            break
        }
        $added = 0
        foreach ($line in ($resp.Content -split "`r?`n")) {
            $m = $rx.Match($line.Trim())
            if ($m.Success) {
                $addr = $m.Groups[2].Value.ToLower()
                if (-not $set.ContainsKey($addr)) {
                    $set[$addr] = $m.Groups[1].Value.Trim()
                    $added++
                }
            }
        }
        $page++
        if ($added -eq 0) { break }
        if ($resp.Content -notmatch '\[Next:') { break }
        $offset += $Limit
    }
    return $set
}

function Get-DolPrologueEntries {
    param([string]$Path)
    $bytes = [System.IO.File]::ReadAllBytes($Path)

    # Parse DOL text section headers (text[0..6])
    $sects = @()
    for ($i = 0; $i -lt 7; $i++) {
        $fo = Read-Be32 $bytes (0x00 + $i*4)
        $va = Read-Be32 $bytes (0x48 + $i*4)
        $sz = Read-Be32 $bytes (0x90 + $i*4)
        if ($fo -ne 0 -and $sz -gt 0) {
            $sects += [pscustomobject]@{ i=$i; fo=$fo; va=$va; sz=$sz }
        }
    }

    $entries = @{}
    foreach ($s in $sects) {
        $prev = [uint32]0
        for ($off = 0; $off -lt $s.sz; $off += 4) {
            $w = Read-Be32 $bytes ($s.fo + $off)
            # stwu r1,-N(r1) => 0x9421FFxx (high byte 0x94 0x21, low 16 bits in 0xFF00..0xFFFF)
            # PowerShell 5.1 parses high-bit hex literals as Int32, so use [Convert]::ToUInt32.
            $prologueHi  = [Convert]::ToUInt32('94210000', 16)
            $prologueLow = [Convert]::ToUInt32('FF00', 16)
            $maskHi = [Convert]::ToUInt32('FFFF0000', 16)
            $maskLo = [Convert]::ToUInt32('FFFF', 16)
            if (($w -band $maskHi) -eq $prologueHi -and ($w -band $maskLo) -ge $prologueLow) {
                $boundary = (Test-BlrVariant $prev) -or ($off -eq 0)
                if ($boundary) {
                    $va = $s.va + $off
                    $hex = ('{0:X8}' -f $va).ToLower()
                    if (-not $entries.ContainsKey($hex)) { $entries[$hex] = $va }
                }
            }
            $prev = $w
        }
    }
    return $entries
}

function Get-CitedAddresses {
    param([string[]]$Dirs)
    $set = @{}
    # Match both `0x80xxxxxx` and bare `80xxxxxx` (8 hex chars starting with `80`).
    # The naive `\b80...\b` misses the very common `0x80...` form because `x` is a word char.
    # Restrict prefix to `80` (vs any `8x`) to avoid false matches inside ASCII bytes / hashes.
    $rx = [regex]'(?:0[xX])?(80[0-9a-fA-F]{6})(?![0-9a-fA-F])'
    $exts = @('.ts','.js','.mjs','.json','.md','.py')
    foreach ($d in $Dirs) {
        if (-not (Test-Path $d)) { continue }
        $resolved = (Resolve-Path $d).Path
        Get-ChildItem -Path $resolved -Recurse -File -ErrorAction SilentlyContinue | ForEach-Object {
            if ($exts -notcontains $_.Extension) { return }
            try {
                $content = Get-Content -Raw -LiteralPath $_.FullName -ErrorAction Stop
                foreach ($m in $rx.Matches($content)) {
                    $a = $m.Groups[1].Value.ToLower()
                    if (-not $set.ContainsKey($a)) { $set[$a] = 0 }
                    $set[$a] = $set[$a] + 1
                }
            } catch { }
        }
    }
    return $set
}

# ---------- Run ----------
Write-Host "OGhidra coverage scan"
Write-Host "  DOL:     $DolPath"
Write-Host "  MCP:     $McpUrl"
Write-Host "  Output:  $OutFile"
Write-Host ""

Write-Progress -Activity "OGhidra coverage" -Status "Pulling MCP function list" -PercentComplete 5
$mcp = Get-McpFunctions -BaseUrl $McpUrl -Limit $PageSize -MaxP $MaxPages
Write-Host "  MCP functions:        $($mcp.Count)"

Write-Progress -Activity "OGhidra coverage" -Status "Scanning DOL prologues" -PercentComplete 30
$dol = Get-DolPrologueEntries -Path $DolPath
Write-Host "  DOL prologue entries: $($dol.Count)"

Write-Progress -Activity "OGhidra coverage" -Status "Harvesting source citations" -PercentComplete 60
$cited = Get-CitedAddresses -Dirs $ScanDirs
Write-Host "  Cited addresses:      $($cited.Count)"
Write-Progress -Activity "OGhidra coverage" -Completed

# ---------- Diffs ----------
$dolNotMcp      = @($dol.Keys | Where-Object { -not $mcp.ContainsKey($_) } | Sort-Object)
$dolInMcp       = @($dol.Keys | Where-Object { $mcp.ContainsKey($_) } | Sort-Object)
$citedNotMcp    = @($cited.Keys | Where-Object { -not $mcp.ContainsKey($_) } | Sort-Object)
$citedInMcp     = @($cited.Keys | Where-Object { $mcp.ContainsKey($_) } | Sort-Object)

# Triaged actionable set: cited AND in DOL prologue AND not in MCP
$actionableGaps = @($dolNotMcp | Where-Object { $cited.ContainsKey($_) } | Sort-Object)

# Top-cited not-in-MCP, sorted by citation count descending (need explicit sort).
$topCitedNotMcp = $citedNotMcp | Sort-Object { -$cited[$_] } | Select-Object -First 50

$summary = [ordered]@{
    generated_at    = (Get-Date).ToString("o")
    mcp_url         = $McpUrl
    dol_path        = $DolPath
    counts          = [ordered]@{
        mcp_functions        = $mcp.Count
        dol_prologue_entries = $dol.Count
        cited_addresses      = $cited.Count
        dol_entries_in_mcp   = $dolInMcp.Count
        dol_entries_not_mcp  = $dolNotMcp.Count
        cited_in_mcp         = $citedInMcp.Count
        cited_not_in_mcp     = $citedNotMcp.Count
    }
    ghidra_missing_true_gaps   = $dolNotMcp
    actionable_cited_not_mcp  = $actionableGaps
    cited_not_in_mcp_all      = $citedNotMcp
    top_cited_not_in_mcp      = @($topCitedNotMcp)
}

# Pretty-print to console
Write-Host ""
Write-Host "Coverage summary:"
Write-Host "  DOL prologue entries: $($dol.Count)"
Write-Host "    of those in MCP:    $($dolInMcp.Count)"
Write-Host "    NOT in MCP (gaps):  $($dolNotMcp.Count)"
Write-Host "  Cited in code:        $($cited.Count)"
Write-Host "    of those in MCP:    $($citedInMcp.Count)"
Write-Host "    NOT in MCP:         $($citedNotMcp.Count)"
Write-Host ""
if ($dolNotMcp.Count -gt 0) {
    Write-Host "True Ghidra gaps (DOL prologue entries NOT defined in Ghidra):"
    foreach ($a in $dolNotMcp) { Write-Host "  0x$a" }
    Write-Host ""
}
if ($actionableGaps.Count -gt 0) {
    Write-Host "Actionable: cited AND missing from MCP:"
    foreach ($a in $actionableGaps) { Write-Host "  0x$a  (cited $($cited[$a])x)" }
    Write-Host ""
}

# Write JSON report
$dir = Split-Path -Parent $OutFile
if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Path $dir | Out-Null }
$json = $summary | ConvertTo-Json -Depth 6
Set-Content -Path $OutFile -Value $json -Encoding UTF8
Write-Host "Report written to: $OutFile"
