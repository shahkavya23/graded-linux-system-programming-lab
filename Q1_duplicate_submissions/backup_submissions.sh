#!/usr/bin/env bash
set -u

SOURCE_DIR="${1:-submissions}"
BACKUP_DIR="${2:-run/unique_backup}"
REPORT="${3:-run/backup_report.txt}"
ERROR_LOG="${4:-run/errors.log}"

mkdir -p "$BACKUP_DIR" "$(dirname "$REPORT")" "$(dirname "$ERROR_LOG")" || exit 1
: > "$REPORT"
: > "$ERROR_LOG"

processed=0
duplicates=0
backed_up=0
declare -A seen_hashes=()

while IFS= read -r -d '' file; do
    processed=$((processed + 1))
    hash=$(sha256sum -- "$file" 2>>"$ERROR_LOG" | awk '{print $1}') || continue
    if [[ -n "${seen_hashes[$hash]+x}" ]]; then
        duplicates=$((duplicates + 1))
        printf 'DUPLICATE\t%s\t%s\n' "$file" "${seen_hashes[$hash]}" >> "$REPORT"
        continue
    fi
    seen_hashes[$hash]="$file"
    destination="$BACKUP_DIR/$(basename "$file")"
    if cp -- "$file" "$destination" 2>>"$ERROR_LOG"; then
        backed_up=$((backed_up + 1))
        printf 'BACKED_UP\t%s\n' "$destination" >> "$REPORT"
    fi
done < <(find "$SOURCE_DIR" -type f -print0 2>>"$ERROR_LOG")

{
    printf 'Files processed: %d\n' "$processed"
    printf 'Duplicates found: %d\n' "$duplicates"
    printf 'Unique files backed up: %d\n' "$backed_up"
    printf 'Error log: %s\n' "$ERROR_LOG"
} >> "$REPORT"

cat "$REPORT"
