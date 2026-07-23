#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct { int id; char name[32]; double salary; } Employee;

static int position_for(int fd, int record_no) {
    off_t offset = (off_t)record_no * (off_t)sizeof(Employee);
    return lseek(fd, offset, SEEK_SET) == offset ? 0 : -1;
}

static void show(const Employee *e) { printf("id=%d name=%s salary=%.2f\n", e->id, e->name, e->salary); }

int main(int argc, char **argv) {
    const char *path = argc > 1 ? argv[1] : "employees.dat";
    int fd = open(path, O_CREAT | O_RDWR, 0644);
    if (fd < 0) { perror("open"); return EXIT_FAILURE; }
    Employee seed[] = {{101, "Asha", 62000}, {102, "Ravi", 71000}, {103, "Mina", 68000}};
    if (lseek(fd, 0, SEEK_END) == 0 && write(fd, seed, sizeof(seed)) != (ssize_t)sizeof(seed)) { perror("write"); close(fd); return EXIT_FAILURE; }
    Employee e;
    if (position_for(fd, 1) < 0 || read(fd, &e, sizeof(e)) != (ssize_t)sizeof(e)) { perror("read"); close(fd); return EXIT_FAILURE; }
    printf("Retrieved record 1: "); show(&e);
    e.salary = 75000;
    if (position_for(fd, 1) < 0 || write(fd, &e, sizeof(e)) != (ssize_t)sizeof(e)) { perror("update"); close(fd); return EXIT_FAILURE; }
    if (position_for(fd, 1) < 0 || read(fd, &e, sizeof(e)) != (ssize_t)sizeof(e)) { perror("verify"); close(fd); return EXIT_FAILURE; }
    printf("Updated record 1: "); show(&e);
    if (close(fd) < 0) { perror("close"); return EXIT_FAILURE; }
    return EXIT_SUCCESS;
}
