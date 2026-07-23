# Question 3 — POSIX Employee File Store

`employee_store.c` stores fixed-size employee records in a binary file using only Linux/POSIX system calls. `open()` creates the file, `write()` appends records, `lseek()` computes a record's byte offset, `read()` retrieves a record, and `write()` updates one record in place without rewriting the rest of the file. The menu's record-number lookup makes random access efficient.
