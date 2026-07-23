# Commands and explanations

```bash
vi -r critical.conf
```
This asks vi to recover the swap-file contents after a crash; the recovered buffer should be inspected before saving.

```vim
:w critical.conf.recovered
```
Writing to a new file preserves the original configuration until the recovered contents have been checked.

```bash
diff -u critical.conf critical.conf.recovered
```
The comparison reveals exactly what would change, making the recovery decision auditable.
