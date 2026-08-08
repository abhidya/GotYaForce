#requires -version 5.1

[CmdletBinding()]
param(
    [int]$PollSeconds = 3,
    [int]$EmptyGraceSeconds = 60,
    [int]$StopGraceSeconds = 5,
    # How long a block persists before its CONDITION is re-evaluated. This is
    # not a retry loop: the unit is only unblocked if the underlying condition
    # is genuinely healthy again. During the 2026-08-01..06 outage the
    # condition never became healthy, so the block would have correctly held
    # for all five days.
    [int]$BlockRecheckMinutes = 10,
    # A run shorter than this counts as a failure to start, not as work.
    [int]$MinHealthyRuntimeSeconds = 120,
    [int]$MaxShortRuns = 3
)

$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'

$PalConfig = 'C:\Program Files (x86)\Steam\steamapps\common\PalServer\Pal\Saved\Config\WindowsServer\PalWorldSettings.ini'
$PalMetricsUrl = 'http://127.0.0.1:8212/v1/api/metrics'
$OGhidraRoot = 'D:\GotYaForce\research\tools\OGhidra'
$OGhidraMain = Join-Path $OGhidraRoot 'main.py'
$OGhidraPython = Join-Path $OGhidraRoot '.venv\Scripts\python.exe'
$ControlPath = 'D:\GotYaForce\research\decomp\generated\finish-game-port\control.json'
$RunStatePath = 'D:\GotYaForce\research\decomp\generated\finish-game-port\run-state.json'
$LedgerPath = 'D:\GotYaForce\research\decomp\generated\finish-game-port\port-ledger.json'
$LivenessPath = 'D:\GotYaForce\research\decomp\generated\finish-game-port\llm-liveness.json'
$MonitorRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$LogPath = Join-Path $MonitorRoot 'palworld-oghidra-monitor.log'
$StatePath = Join-Path $MonitorRoot 'palworld-oghidra-monitor-state.json'
$OGhidraOut = Join-Path $MonitorRoot 'oghidra-resume.out.log'
$OGhidraErr = Join-Path $MonitorRoot 'oghidra-resume.err.log'
$UnslothOut = Join-Path $MonitorRoot 'unsloth-studio.out.log'
$UnslothErr = Join-Path $MonitorRoot 'unsloth-studio.err.log'

# Chat is served by Unsloth on :8888; LM Studio is embeddings-only on :1234.
. (Join-Path $MonitorRoot 'unsloth-control.ps1')
. (Join-Path $MonitorRoot 'lmstudio-embeddings.ps1')

$script:UnslothProcess = $null
$script:LastUnslothAttempt = [datetime]::MinValue
$script:LastEmbeddingAttempt = [datetime]::MinValue
$script:Blocked = $false
$script:BlockedReason = ''
$script:BlockedSince = [datetime]::MinValue
$script:LastOGhidraStart = [datetime]::MinValue
$script:ShortRunCount = 0
$script:OGhidraProcess = $null
$script:LockedRunCount = 0
$script:LastPalSample = [datetime]::MinValue
$script:LastPalMetrics = $null
$ResetRequestPath = 'D:\rig\state\reset-request.marker'
$PalPlayersUrl = 'http://127.0.0.1:8212/v1/api/players'
$PalSamplePath = 'D:\rig\state\palworld-metrics.jsonl'
$PalPlayersPath = 'D:\rig\state\palworld-players.json'
$script:Mode = 'starting'
$script:EmptySince = $null
$script:ApiFailures = 0
$script:LastProtectionCheck = [datetime]::MinValue

function Write-MonitorLog {
    param([string]$Message, [string]$Level = 'INFO')
    if (Test-Path -LiteralPath $LogPath) {
        $item = Get-Item -LiteralPath $LogPath -ErrorAction SilentlyContinue
        if ($item -and $item.Length -gt 5MB) {
            Move-Item -LiteralPath $LogPath -Destination "$LogPath.previous" -Force
        }
    }
    $line = '{0} [{1}] {2}' -f (Get-Date).ToString('o'), $Level, $Message
    Add-Content -LiteralPath $LogPath -Value $line -Encoding UTF8
}

function Write-JsonAtomic {
    <#  PS 5.1's Move-Item (FileInfo.MoveTo) is not an atomic replace: with the
        destination present and a reader holding it, it throws IOException --
        the exact failure that killed the monitor on 2026-08-07 18:03. Use the
        Win32 atomic Replace instead, retry transient reader/AV locks, and
        still throw after retries: callers decide whether the write is
        telemetry (swallow) or protection-relevant (surface). #>
    param([string]$Path, [object]$Value)
    $directory = Split-Path -Parent $Path
    if (-not (Test-Path -LiteralPath $directory)) {
        New-Item -ItemType Directory -Path $directory -Force | Out-Null
    }
    $temporary = '{0}.{1}.{2}.tmp' -f $Path, $PID, [Guid]::NewGuid().ToString('N')
    $json = $Value | ConvertTo-Json -Depth 8
    [IO.File]::WriteAllText($temporary, $json, [Text.UTF8Encoding]::new($false))
    try {
        for ($attempt = 1; $attempt -le 3; $attempt++) {
            try {
                if (Test-Path -LiteralPath $Path) {
                    # [NullString]::Value, not $null: PowerShell binds $null to
                    # "" for string parameters, and Replace rejects "" as an
                    # illegal backup path.
                    [IO.File]::Replace($temporary, $Path, [NullString]::Value)
                } else {
                    [IO.File]::Move($temporary, $Path)
                }
                return
            } catch [IO.IOException] {
                if ($attempt -eq 3) { throw }
                Start-Sleep -Milliseconds 50
            }
        }
    } finally {
        Remove-Item -LiteralPath $temporary -Force -ErrorAction SilentlyContinue
    }
}

function Write-MonitorState {
    param([Nullable[int]]$Players, [string]$Reason, [string]$LastError = '')
    $roots = @(Get-OGhidraRoots | Select-Object -ExpandProperty ProcessId)
    $value = [ordered]@{
        updated_at = (Get-Date).ToString('o')
        mode = $script:Mode
        players = $Players
        reason = $Reason
        api_failures = $script:ApiFailures
        oghidra_pids = $roots
        unsloth_pid = if ($script:UnslothProcess -and -not $script:UnslothProcess.HasExited) { $script:UnslothProcess.Id } else { $null }
        blocked = $script:Blocked
        blocked_reason = $script:BlockedReason
        last_error = $LastError
    }
    try {
        Write-JsonAtomic -Path $StatePath -Value $value
    } catch {
        # Telemetry may never kill protection (post-mortem defect A). Dropping
        # one state sample is the intended outcome of a persistent lock.
        try { Write-MonitorLog "Monitor state write failed: $($_.Exception.Message)" 'WARN' } catch {}
    }
}

function Get-PalApiHeaders {
    $text = [IO.File]::ReadAllText($PalConfig)
    $match = [regex]::Match($text, 'AdminPassword="([^"]+)"')
    if (-not $match.Success) {
        throw 'Palworld AdminPassword is missing; REST authentication cannot be built.'
    }
    $pair = 'admin:{0}' -f $match.Groups[1].Value
    $token = [Convert]::ToBase64String([Text.Encoding]::UTF8.GetBytes($pair))
    return @{ Authorization = "Basic $token"; Accept = 'application/json' }
}

function Get-PalPlayerCount {
    $headers = Get-PalApiHeaders
    $metrics = Invoke-RestMethod -Method Get -Uri $PalMetricsUrl -Headers $headers -TimeoutSec 2
    if ($null -eq $metrics.currentplayernum) {
        throw 'Palworld metrics response did not contain currentplayernum.'
    }
    $script:LastPalMetrics = $metrics
    Save-PalworldSample -Headers $headers -Metrics $metrics
    return [int]$metrics.currentplayernum
}

function Save-PalworldSample {
    <#  Time-series for the dashboard: one JSONL sample every ~30s
        (players/fps/uptime/frametime), plus the current per-player list.
        Best-effort -- a sampling failure must never break gameplay
        protection. #>
    param($Headers, $Metrics)
    if (((Get-Date) - $script:LastPalSample).TotalSeconds -lt 30) { return }
    $script:LastPalSample = Get-Date
    try {
        $dir = Split-Path -Parent $PalSamplePath
        if (-not (Test-Path -LiteralPath $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
        $item = Get-Item -LiteralPath $PalSamplePath -ErrorAction SilentlyContinue
        if ($item -and $item.Length -gt 5MB) {
            Move-Item -LiteralPath $PalSamplePath -Destination "$PalSamplePath.previous" -Force
        }
        $sample = [ordered]@{
            ts        = (Get-Date).ToString('o')
            players   = [int]$Metrics.currentplayernum
            fps       = $Metrics.serverfps
            frametime = $Metrics.serverframetime
            uptime    = $Metrics.uptime
        } | ConvertTo-Json -Compress
        Add-Content -LiteralPath $PalSamplePath -Value $sample -Encoding UTF8

        $players = Invoke-RestMethod -Method Get -Uri $PalPlayersUrl -Headers $Headers -TimeoutSec 3
        Write-JsonAtomic -Path $PalPlayersPath -Value ([ordered]@{
            updated_at = (Get-Date).ToString('o')
            players    = @($players.players)
        })
    } catch {
        # sampling is never allowed to interfere with protection
    }
}

function Test-PalServerRunning {
    return $null -ne (Get-Process -Name 'PalServer-Win64-Shipping-Cmd' -ErrorAction SilentlyContinue)
}

function Set-OGhidraControl {
    param([ValidateSet('run', 'stop_after_stage')][string]$Command)
    Write-JsonAtomic -Path $ControlPath -Value ([ordered]@{
        command = $Command
        updated_at = (Get-Date).ToUniversalTime().ToString('s')
        source = 'palworld-oghidra-monitor'
    })
}

function Get-OGhidraProcesses {
    # Match any python running finish-port, whether launched with the absolute
    # main.py path (this monitor) or a relative main.py from a shell in the
    # OGhidra root. The 2026-08-08 stopgap driver used the relative form and
    # was invisible to the old absolute-path needle, which meant gameplay
    # protection could not kill it.
    return @(Get-CimInstance Win32_Process -ErrorAction SilentlyContinue | Where-Object {
        $_.Name -ieq 'python.exe' -and
        $_.CommandLine -and
        $_.CommandLine -match '(?i)main\.py' -and
        $_.CommandLine -match 'finish-port'
    })
}

function Get-OGhidraRoots {
    $processes = @(Get-OGhidraProcesses)
    $ids = @($processes | ForEach-Object { [int]$_.ProcessId })
    return @($processes | Where-Object { $ids -notcontains [int]$_.ParentProcessId })
}

function Stop-OGhidraTrees {
    $all = @(Get-CimInstance Win32_Process -ErrorAction SilentlyContinue)
    $roots = @(Get-OGhidraRoots)
    foreach ($root in $roots) {
        $pending = [Collections.Generic.List[int]]::new()
        $pending.Add([int]$root.ProcessId)
        for ($index = 0; $index -lt $pending.Count; $index++) {
            $parent = $pending[$index]
            foreach ($child in @($all | Where-Object { [int]$_.ParentProcessId -eq $parent })) {
                if (-not $pending.Contains([int]$child.ProcessId)) {
                    $pending.Add([int]$child.ProcessId)
                }
            }
        }
        for ($index = $pending.Count - 1; $index -ge 0; $index--) {
            Stop-Process -Id $pending[$index] -Force -ErrorAction SilentlyContinue
        }
        Write-MonitorLog "Stopped OGhidra process tree rooted at PID $($root.ProcessId)."
    }
    if ($roots.Count -gt 0) {
        Reset-OGhidraLiveness
    }
}

function Reset-OGhidraLiveness {
    <#  The killer must clean up (post-mortem defect C): a SIGKILLed client
        cannot clear active:true in llm-liveness.json, which trips the rig
        staleness assertion and makes a dead driver look alive (observed 1386
        min stale). Only touch the flag when no driver is visible, so a live
        client is never clobbered; a live client rewrites the file on its next
        request anyway. #>
    if (@(Get-OGhidraRoots).Count -gt 0) { return }
    if (-not (Test-Path -LiteralPath $LivenessPath)) { return }
    try {
        $liveness = Get-Content -LiteralPath $LivenessPath -Raw | ConvertFrom-Json
        if (-not $liveness.active) { return }
        $liveness.active = $false
        $liveness | Add-Member -NotePropertyName status -NotePropertyValue 'stopped_by_monitor' -Force
        $liveness.updated_at = (Get-Date).ToString('o')
        Write-JsonAtomic -Path $LivenessPath -Value $liveness
        Write-MonitorLog 'Cleared stale llm-liveness active flag after driver stop.'
    } catch {
        try { Write-MonitorLog "Liveness reset failed: $($_.Exception.Message)" 'WARN' } catch {}
    }
}

function Set-Blocked {
    <#  Stop attempting heavy work and say why, until the condition clears.
        Deliberately does not auto-retry in a tight loop: the failure this
        replaces relaunched OGhidra 17 times over 21 hours without ever
        reporting that every run was useless. #>
    param([string]$Reason)
    if (-not $script:Blocked -or $script:BlockedReason -ne $Reason) {
        Write-MonitorLog "BLOCKED: $Reason" 'ERROR'
        $script:BlockedSince = Get-Date
    }
    $script:Blocked = $true
    $script:BlockedReason = $Reason
}

function Clear-Blocked {
    if ($script:Blocked) {
        Write-MonitorLog 'Block cleared; heavy work may resume.'
    }
    $script:Blocked = $false
    $script:BlockedReason = ''
    $script:BlockedSince = [datetime]::MinValue
}

function Test-ResetRequested {
    <#  `rig reset` drops a marker file. Consume it so the request fires once. #>
    if (-not (Test-Path -LiteralPath $ResetRequestPath)) { return $false }
    Remove-Item -LiteralPath $ResetRequestPath -Force -ErrorAction SilentlyContinue
    Write-MonitorLog 'Manual reset requested via rig reset.'
    return $true
}

function Test-BlockRecheckDue {
    <#  Re-evaluate the CONDITION on a slow cadence. Without this, nothing ever
        clears a block short of restarting the task -- the original design
        called for `rig reset` but left no automatic recovery at all. #>
    if (-not $script:Blocked) { return $false }
    if ($script:BlockedSince -eq [datetime]::MinValue) { return $true }
    return (((Get-Date) - $script:BlockedSince).TotalMinutes -ge $BlockRecheckMinutes)
}

function Start-UnslothModelLoad {
    <#  Brings Unsloth Studio up on :8888 and loads the chat model. Returns
        $true once the model is serving. Never falls back to LM Studio -- that
        substitution is precisely what caused the five-day outage. #>
    if (((Get-Date) - $script:LastUnslothAttempt).TotalSeconds -lt 60) {
        return (Test-UnslothModelLoaded)
    }
    $script:LastUnslothAttempt = Get-Date

    if ($script:UnslothProcess -and $script:UnslothProcess.HasExited) {
        $errorText = if (Test-Path -LiteralPath $UnslothErr) { [IO.File]::ReadAllText($UnslothErr).Trim() } else { '' }
        Write-MonitorLog "Unsloth Studio exited with code $($script:UnslothProcess.ExitCode): $errorText" 'WARN'
        $script:UnslothProcess = $null
    }

    if (-not (Test-UnslothServerUp)) {
        try {
            $started = Start-UnslothStudio -StdOutPath $UnslothOut -StdErrPath $UnslothErr
            if ($started) {
                $script:UnslothProcess = $started
                Write-MonitorLog "Started Unsloth Studio as PID $($started.Id); waiting for API."
            }
        } catch {
            Set-Blocked -Reason "Unsloth Studio cannot start: $($_.Exception.Message)"
            return $false
        }
        # Fast-fail on immediate death. A process that refuses to start (bad CWD,
        # ACL-locked llama.cpp, port conflict) is gone in under a second, but the
        # old code still waited the full 300 s and then reported a timeout --
        # hiding the actual reason, which was sitting in the stderr log the whole
        # time. Check the process before committing to the long wait.
        if ($script:UnslothProcess) {
            Start-Sleep -Seconds 3
            if ($script:UnslothProcess.HasExited) {
                $errorText = if (Test-Path -LiteralPath $UnslothErr) {
                    (([IO.File]::ReadAllText($UnslothErr).Trim() -split "`r?`n") | Where-Object { $_ } | Select-Object -First 4) -join ' / '
                } else { '(no stderr captured)' }
                Set-Blocked -Reason "Unsloth Studio exited immediately (code $($script:UnslothProcess.ExitCode)): $errorText"
                $script:UnslothProcess = $null
                return $false
            }
        }
        if (-not (Wait-UnslothServerUp -TimeoutSeconds 300)) {
            Set-Blocked -Reason 'Unsloth Studio did not answer /api/inference/status within 300s.'
            return $false
        }
        Write-MonitorLog 'Unsloth Studio API is up.'
    }

    if (-not (Test-UnslothOwnsPort)) {
        $owner = Get-PortOwner -Port 8888
        $who = if ($owner) { '{0} (PID {1})' -f $owner.Name, $owner.Pid } else { 'unknown' }
        Set-Blocked -Reason "Port 8888 is answering but it is not Unsloth (owner: $who)."
        return $false
    }

    if (Test-UnslothModelLoaded) { return $true }

    try {
        Invoke-UnslothLoad | Out-Null
        Write-MonitorLog "Requested Unsloth load of $script:UnslothModelPath ($script:UnslothGgufVariant)."
    } catch {
        Set-Blocked -Reason "Unsloth model load request failed: $($_.Exception.Message)"
        return $false
    }
    if (-not (Wait-UnslothModelReady -TimeoutSeconds 900)) {
        Set-Blocked -Reason 'Unsloth model did not become ready within 900s.'
        return $false
    }
    Write-MonitorLog 'Unsloth model is loaded and serving.'
    return $true
}

function Confirm-ChatContract {
    <#  Preflight before handing work to OGhidra. Asserts the endpoint accepts
        tool_choice as an object -- the exact contract LM Studio's backend
        violates, which drove structured_tool_calls to 0 across 2316 calls. #>
    $contract = Test-UnslothChatContract
    if ($contract.Ok) { return $true }
    $status = if ($contract.Status) { $contract.Status } else { 'n/a' }
    Set-Blocked -Reason "Chat contract preflight failed (HTTP $status): $($contract.Reason)"
    return $false
}

function Sync-EmbeddingServer {
    <#  LM Studio's only job. Best-effort: embeddings being down should not
        block port work, but it must be visible rather than silent. #>
    if (((Get-Date) - $script:LastEmbeddingAttempt).TotalSeconds -lt 300) { return }
    $script:LastEmbeddingAttempt = Get-Date
    if (Test-EmbeddingModelLoaded) { return }
    try {
        $result = Start-EmbeddingServer
        foreach ($step in $result.Steps) { Write-MonitorLog "embeddings: $step" }
        if (-not $result.ModelLoaded) {
            Write-MonitorLog 'Embedding model is still not loaded on :1234.' 'WARN'
        }
    } catch {
        Write-MonitorLog "Embedding server start failed: $($_.Exception.Message)" 'WARN'
    }
}

function Start-OGhidraResume {
    if (@(Get-OGhidraRoots).Count -gt 0) {
        return
    }

    # Our driver is gone: capture its exit code (the handle was cached at
    # launch, so ExitCode survives process death) and clear stale liveness.
    $exitCode = $null
    if ($script:OGhidraProcess) {
        if (-not $script:OGhidraProcess.HasExited) {
            # Roots query missed a live process (CIM race); do not double-launch.
            return
        }
        $exitCode = $script:OGhidraProcess.ExitCode
        $script:OGhidraProcess = $null
    }
    Reset-OGhidraLiveness

    # run-state.json is only trustworthy at rest (two writers race mid-step:
    # port_driver run_mode=driver vs port_chunk_workflow run_mode=chunk_unit).
    # We only reach this point with no driver running, so reading it is safe.
    try {
        $runState = Get-Content -LiteralPath $RunStatePath -Raw -ErrorAction Stop | ConvertFrom-Json
    } catch {
        $runState = $null
    }
    # Exit-4 liveness backoff (driver design D6, locked decision #3): the driver
    # exits 4 and records status paused_provider_unavailable when the model
    # provider vanished mid-run. Relaunching before the provider is actually
    # answering would burn a launch cycle and re-pause immediately, so require a
    # genuine Unsloth status response first (Get-UnslothStatus shape-validates;
    # a foreign server squatting the port returns $null).
    if ($runState -and $runState.status -eq 'paused_provider_unavailable') {
        if ($null -eq (Get-UnslothStatus)) {
            Write-MonitorLog 'OGhidra paused on provider outage (exit 4); Unsloth not answering yet -- holding relaunch.' 'WARN'
            return
        }
        Write-MonitorLog 'Provider answered after exit-4 pause; resuming OGhidra.'
    }
    if ($runState -and $runState.status -eq 'completed' -and $runState.run_mode -eq 'driver') {
        # Exit 0 = no work left -- but 'completed' must not latch forever. New
        # work arrives by resetting/extending port-ledger.json, which makes the
        # ledger file newer than the run-state snapshot (the driver always
        # writes ledger first, run-state last, so at rest ledger <= run-state).
        # Compare file mtimes rather than parsing timestamps: same clock, no
        # timezone ambiguity. Worst case is one harmless exit-0 probe run.
        $ledgerItem = Get-Item -LiteralPath $LedgerPath -ErrorAction SilentlyContinue
        $stateItem = Get-Item -LiteralPath $RunStatePath -ErrorAction SilentlyContinue
        if (-not ($ledgerItem -and $stateItem -and $ledgerItem.LastWriteTimeUtc -gt $stateItem.LastWriteTimeUtc)) {
            return
        }
        Write-MonitorLog 'port-ledger.json changed after completed state; probing for new work.'
    }
    # Crash-loop guard, now exit-code aware. Duration alone cannot distinguish a
    # crash from a healthy fast exit: 0 = no work, 2 = stopped by control.json,
    # 3 = budget reached, 4 = provider paused, 5 = lock held elsewhere. Only an
    # unknown or unexpected code dying young counts toward the block.
    if ($script:LastOGhidraStart -ne [datetime]::MinValue) {
        $elapsedSeconds = ((Get-Date) - $script:LastOGhidraStart).TotalSeconds
        $codeText = if ($null -ne $exitCode) { $exitCode } else { 'unknown' }
        Write-MonitorLog ("Previous OGhidra run ended after {0:N0}s (exit code: {1})." -f $elapsedSeconds, $codeText)
        $healthyExit = ($null -ne $exitCode) -and (@(0, 2, 3, 4, 5) -contains $exitCode)
        if ($elapsedSeconds -lt $MinHealthyRuntimeSeconds -and -not $healthyExit) {
            $script:ShortRunCount++
            if ($script:ShortRunCount -ge $MaxShortRuns) {
                $tail = ''
                if (Test-Path -LiteralPath $OGhidraErr) {
                    $lines = @(Get-Content -LiteralPath $OGhidraErr -Tail 3 -ErrorAction SilentlyContinue)
                    $tail = ($lines -join ' / ')
                }
                Set-Blocked -Reason ("OGhidra exited in under {0}s on {1} consecutive attempts. Last stderr: {2}" -f `
                    $MinHealthyRuntimeSeconds, $script:ShortRunCount, $tail)
                return
            }
        } else {
            $script:ShortRunCount = 0
        }
    }
    # Exit 5 with no visible driver means driver.lock is held by a process we
    # cannot see (elevated, so CIM hides its command line) or the lock is
    # stale. Hammering relaunches every poll would churn forever; block and let
    # the recheck cadence retry.
    if ($exitCode -eq 5) {
        $script:LockedRunCount++
        if ($script:LockedRunCount -ge $MaxShortRuns) {
            Set-Blocked -Reason 'driver.lock is held but no OGhidra process is visible; possible elevated driver or stale lock.'
            return
        }
    } else {
        $script:LockedRunCount = 0
    }
    # A long-lived --until-blocked driver can grow these without bound; keep
    # the tail of the previous run readable for the crash-block stderr report.
    foreach ($logFile in @($OGhidraOut, $OGhidraErr)) {
        $item = Get-Item -LiteralPath $logFile -ErrorAction SilentlyContinue
        if ($item -and $item.Length -gt 5MB) {
            Move-Item -LiteralPath $logFile -Destination "$logFile.previous" -Force -ErrorAction SilentlyContinue
        }
    }
    Set-OGhidraControl -Command run
    # --drive --until-blocked: the autonomous driver loops durable steps
    # internally (resuming from port-ledger.json) and exits on no-work /
    # control-stop / provider-pause / crash. It re-reads control.json at every
    # step boundary, so stop_after_stage still stops it cooperatively.
    $process = Start-Process -FilePath $OGhidraPython -ArgumentList @($OGhidraMain, 'finish-port', '--drive', '--until-blocked') -WorkingDirectory $OGhidraRoot -WindowStyle Hidden -PassThru -RedirectStandardOutput $OGhidraOut -RedirectStandardError $OGhidraErr
    $null = $process.Handle  # cache so ExitCode is readable after death
    $script:OGhidraProcess = $process
    $script:LastOGhidraStart = Get-Date
    Write-MonitorLog "Started OGhidra port driver as PID $($process.Id)."
}

function Protect-Gameplay {
    param([string]$Reason, [Nullable[int]]$Players)
    $script:Mode = 'protected'
    # Nothing before Stop-OGhidraTrees may abort protection: the cooperative
    # stop signal and the VRAM unload are both best-effort, the kill is not.
    try {
        Set-OGhidraControl -Command stop_after_stage
    } catch {
        try { Write-MonitorLog "control.json write failed during protection: $($_.Exception.Message)" 'WARN' } catch {}
    }
    # Give the model back its VRAM and CPU threads. force_cancel_active stops
    # in-flight generations instead of returning 409 -- players come first.
    try {
        Invoke-UnslothUnload -Force | Out-Null
    } catch {
        try { Write-MonitorLog "Unsloth unload failed during protection: $($_.Exception.Message)" 'WARN' } catch {}
    }
    $deadline = (Get-Date).AddSeconds($StopGraceSeconds)
    while ((Get-Date) -lt $deadline -and @(Get-OGhidraRoots).Count -gt 0) {
        Start-Sleep -Milliseconds 250
    }
    Stop-OGhidraTrees
    # A run we killed on purpose says nothing about driver health -- it must
    # not feed the crash-loop guard when heavy work resumes.
    $script:OGhidraProcess = $null
    $script:LastOGhidraStart = [datetime]::MinValue
    $script:ShortRunCount = 0
    $script:LockedRunCount = 0
    $script:LastProtectionCheck = Get-Date
    Write-MonitorLog "Gameplay protection active: $Reason"
    Write-MonitorState -Players $Players -Reason $Reason
}

function Enable-HeavyWorkflow {
    Sync-EmbeddingServer

    # Work already in progress: report and get out. Everything below exists to
    # decide whether it is safe to START OGhidra; none of it may run while a
    # port job is mid-inference. The server exposes a single decode slot
    # (parallel_slots=1), so a contract preflight issued while OGhidra's
    # request is generating queues behind it, times out at 120s, and trips a
    # false BLOCKED -- observed live on 2026-08-06 17:25 six minutes into the
    # first healthy run in days.
    if (@(Get-OGhidraRoots).Count -gt 0) {
        if ($script:Mode -ne 'running') {
            $script:Mode = 'running'
            Write-MonitorState -Players 0 -Reason 'Palworld empty; Unsloth and OGhidra running.'
        }
        return
    }

    if ($script:Blocked) {
        # Clear only on an explicit reset, or when it is time to re-test the
        # condition. Falling through re-runs the real checks below; if they
        # still fail, Set-Blocked simply blocks again with a fresh timestamp.
        if (Test-ResetRequested) {
            Clear-Blocked
        } elseif (Test-BlockRecheckDue) {
            Write-MonitorLog "Re-evaluating block after $BlockRecheckMinutes min: $($script:BlockedReason)"
            $script:Blocked = $false
            $script:BlockedReason = ''
        } else {
            $script:Mode = 'blocked'
            Write-MonitorState -Players 0 -Reason "Blocked: $($script:BlockedReason)" -LastError $script:BlockedReason
            return
        }
    }

    if (-not (Start-UnslothModelLoad)) {
        $script:Mode = if ($script:Blocked) { 'blocked' } else { 'loading_model' }
        $reason = if ($script:Blocked) { "Blocked: $($script:BlockedReason)" } else { 'Palworld empty; bringing up Unsloth before OGhidra resume.' }
        Write-MonitorState -Players 0 -Reason $reason -LastError $script:BlockedReason
        return
    }

    if (-not (Confirm-ChatContract)) {
        $script:Mode = 'blocked'
        Write-MonitorState -Players 0 -Reason "Blocked: $($script:BlockedReason)" -LastError $script:BlockedReason
        return
    }

    Clear-Blocked
    Set-OGhidraControl -Command run
    Start-OGhidraResume
    $script:Mode = 'running'
    Write-MonitorState -Players 0 -Reason 'Palworld empty; Unsloth and OGhidra running.'
}

$createdNew = $false
$mutex = [Threading.Mutex]::new($true, 'Local\PalworldOGhidraPlayerMonitor', [ref]$createdNew)
if (-not $createdNew) {
    exit 0
}

try {
    Write-MonitorLog 'Monitor started.'
    $consecutiveLoopFailures = 0
    while ($true) {
      # One failed iteration may never kill the monitor (post-mortem defect A:
      # a telemetry throw under $ErrorActionPreference='Stop' took protection
      # down for 23 h). Log, count, and only die after sustained failure --
      # the scheduled task is the restart backstop for that terminal case.
      try {
        $players = $null
        try {
            $players = Get-PalPlayerCount
            $script:ApiFailures = 0
        } catch {
            $script:ApiFailures++
            Write-MonitorState -Players $null -Reason 'Palworld API unavailable.' -LastError $_.Exception.Message
        }

        if ($null -ne $players) {
            if ($players -gt 0) {
                $script:EmptySince = $null
                if ($script:Mode -ne 'protected' -or ((Get-Date) - $script:LastProtectionCheck).TotalSeconds -ge 30) {
                    Protect-Gameplay -Reason "$players Palworld player(s) connected." -Players $players
                }
            } else {
                if ($null -eq $script:EmptySince) {
                    $script:EmptySince = Get-Date
                    Write-MonitorLog "Palworld is empty; waiting $EmptyGraceSeconds seconds before resuming heavy work."
                }
                if (((Get-Date) - $script:EmptySince).TotalSeconds -ge $EmptyGraceSeconds) {
                    Enable-HeavyWorkflow
                }
            }
        } elseif ($script:ApiFailures -ge 3) {
            if (Test-PalServerRunning) {
                $script:EmptySince = $null
                if ($script:Mode -ne 'protected') {
                    Protect-Gameplay -Reason 'Palworld is running but player status is unknown; fail-safe protection.' -Players $null
                }
            } else {
                if ($null -eq $script:EmptySince) { $script:EmptySince = Get-Date }
                if (((Get-Date) - $script:EmptySince).TotalSeconds -ge $EmptyGraceSeconds) {
                    Enable-HeavyWorkflow
                }
            }
        }
        $consecutiveLoopFailures = 0
      } catch {
        $consecutiveLoopFailures++
        try { Write-MonitorLog ("Iteration failed ({0}/10): {1}" -f $consecutiveLoopFailures, $_.Exception.ToString()) 'ERROR' } catch {}
        if ($consecutiveLoopFailures -ge 10) { throw }
      }
        Start-Sleep -Seconds $PollSeconds
    }
} catch {
    Write-MonitorLog $_.Exception.ToString() 'ERROR'
    Write-MonitorState -Players $null -Reason 'Monitor terminated unexpectedly.' -LastError $_.Exception.Message
    throw
} finally {
    $mutex.ReleaseMutex()
    $mutex.Dispose()
}
