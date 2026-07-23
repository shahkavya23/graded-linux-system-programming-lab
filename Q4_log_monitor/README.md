# Question 4 — Real-Time Log Monitor

The command pipeline below follows a log from the end, extracts only `ERROR` entries, appends them to a separate report, and suppresses the ordinary `tail` stream with `/dev/null`. `tail -F` keeps following the file across common log rotation patterns; `grep --line-buffered` makes matching lines available promptly; `tee -a` preserves the report while also displaying matches.
