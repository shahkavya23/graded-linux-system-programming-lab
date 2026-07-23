# Commands and explanations

```bash
mkdir -p submissions run/unique_backup
```
This creates the input and output directories before the script runs, so the backup operation has a known destination.

```bash
printf 'answer=42\n' > submissions/alice.txt
printf 'answer=42\n' > submissions/bob.txt
printf 'answer=17\n' > submissions/carol.txt
```
These commands create three submissions; Alice and Bob intentionally have identical content.

```bash
chmod +x backup_submissions.sh
./backup_submissions.sh submissions run/unique_backup run/backup_report.txt run/errors.log
```
The script hashes each file, copies only the first file for each hash, reports the duplicate, and sends diagnostics to `run/errors.log`.

## Captured output

See `run/backup_report.txt` and `run/errors.log`. Expected summary: 3 files processed, 1 duplicate, and 2 unique backups.
