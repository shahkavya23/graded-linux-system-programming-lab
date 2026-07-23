# Commands and explanations

```bash
touch run/application.log run/error_report.txt
```
This ensures the monitored log and report exist before the pipeline starts.

```bash
timeout 2 ./monitor_errors.sh run/application.log run/error_report.txt & monitor_pid=$!
sleep 1; printf '%s\n' 'INFO server ready' 'ERROR database unavailable' >> run/application.log; wait "$monitor_pid" 2>/dev/null || true
```
The background monitor follows new lines in real time; the `ERROR` line is captured while ordinary output is suppressed.

```bash
cat run/error_report.txt
```
This displays the maintained report, which is separate from the source log.

## Captured output

See `run/error_report.txt`. Pipes stream data between commands, redirection sends the final display stream to `/dev/null`, and `2>/dev/null` suppresses expected termination noise.
