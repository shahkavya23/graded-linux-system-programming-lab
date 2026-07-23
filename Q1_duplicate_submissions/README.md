# Question 1 — Duplicate Submission Backup

`backup_submissions.sh` scans a directory of student submission files, identifies duplicate content with SHA-256 hashes, backs up exactly one copy of each unique submission, and writes a summary report. Errors are sent to a separate error log through `2>` so normal report output remains readable.

The script uses `find -print0` and a NUL-delimited `while read` loop so filenames containing spaces, quotes, or newlines are handled safely. Duplicate files are recorded but not copied again.
