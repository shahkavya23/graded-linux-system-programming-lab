# Question 2 — Child Process Monitor

`process_monitor.c` creates a configurable number of children with `fork()`. Each child performs a short task and exits. The parent uses non-blocking `waitpid(..., WNOHANG)` polling to monitor progress, reaps completed children to prevent zombies, and sends `SIGTERM` followed by `SIGKILL` if a child exceeds the timeout.

The parent ignores `SIGPIPE` only for robustness; child termination is performed with `kill()` and status is interpreted using `WIFEXITED`, `WEXITSTATUS`, and `WIFSIGNALED`.
