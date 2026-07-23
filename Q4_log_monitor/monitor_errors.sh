#!/usr/bin/env bash
set -u
LOG_FILE="${1:-run/application.log}"
REPORT="${2:-run/error_report.txt}"
mkdir -p "$(dirname "$LOG_FILE")" "$(dirname "$REPORT")"
touch "$LOG_FILE"
tail -F "$LOG_FILE" 2>/dev/null | grep --line-buffered 'ERROR' | tee -a "$REPORT" >/dev/null
