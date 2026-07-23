# Commands and explanations

```bash
gcc -Wall -Wextra -O2 -o employee_store employee_store.c
```
This compiles the fixed-record file utility and checks for common C mistakes.

```bash
rm -f run/employees.dat && ./employee_store run/employees.dat
```
The program creates three records, retrieves record 1 by offset, updates its salary in place, reads it again, and closes the descriptor.

## Captured output

See `run/output.txt`. The unchanged record count demonstrates that the update did not rewrite the whole file.
