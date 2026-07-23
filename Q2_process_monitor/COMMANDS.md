# Commands and explanations

```bash
gcc -Wall -Wextra -O2 -o process_monitor process_monitor.c
```
This compiles the POSIX program with warnings enabled so incorrect process and signal handling is easier to detect.

```bash
./process_monitor 3 5
```
The parent creates three children, polls them with `waitpid(WNOHANG)`, and reaps each child after it exits. The final line confirms that no zombie children remain.

## Captured output

See `run/output.txt` for a representative execution transcript.
