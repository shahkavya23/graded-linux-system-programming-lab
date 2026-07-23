# Question 5 — vi Recovery Strategy

## Evaluation

| Mechanism | What it protects against | Limitation |
|---|---|---|
| Swap file (`.filename.swp`) | Crash, power loss, or a second editor session | May be stale; inspect before recovering |
| Undo history | Accidental edits during the current session | Usually does not survive a crashed process unless persistent undo is configured |
| Registers | Deleted or yanked text | Not a complete-file recovery mechanism |
| Backup file (`filename~`) | A previous saved version | Does not contain unsaved edits after the latest save |
| Auto-recovery | Periodic recovery data in configured environments | Recovery point depends on the last write interval |

## Most reliable procedure

The swap file is the primary recovery source for unsaved edits. Reopen the exact file with `vi -r filename` (or start `vi filename` and choose `R` when vi reports a swap file), inspect the recovered buffer, and save it to a new filename first. Compare it with `filename~` and the original before replacing the original. Only delete the `.swp` file after the recovered content has been verified.

This approach is safest because it preserves the original file while allowing the crash-recovered buffer to be audited. Backups provide a fallback for the last saved state, while undo, registers, and auto-recovery are useful supporting mechanisms rather than substitutes for the swap file.
