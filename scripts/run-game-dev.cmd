@echo off
cd /d "%~dp0.."
"%CD%\tools\node\pnpm.cmd" --filter game dev -- --host localhost
