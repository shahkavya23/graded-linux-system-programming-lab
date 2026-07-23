#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static double elapsed(const struct timespec *start) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (double)(now.tv_sec - start->tv_sec) +
           (double)(now.tv_nsec - start->tv_nsec) / 1e9;
}

int main(int argc, char **argv) {
    int count = argc > 1 ? atoi(argv[1]) : 3;
    int timeout = argc > 2 ? atoi(argv[2]) : 5;
    if (count < 1 || count > 32 || timeout < 1) {
        fprintf(stderr, "Usage: %s CHILD_COUNT TIMEOUT_SECONDS\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t *children = calloc((size_t)count, sizeof(*children));
    if (!children) return EXIT_FAILURE;
    struct timespec started;
    clock_gettime(CLOCK_MONOTONIC, &started);
    for (int i = 0; i < count; i++) {
        pid_t pid = fork();
        if (pid < 0) { perror("fork"); return EXIT_FAILURE; }
        if (pid == 0) {
            printf("child[%d] pid=%ld started\n", i, (long)getpid());
            fflush(stdout);
            sleep((unsigned)(i % 3 + 1));
            _exit(10 + i);
        }
        children[i] = pid;
        printf("parent: created child[%d] pid=%ld\n", i, (long)pid);
    }

    int remaining = count;
    while (remaining > 0) {
        for (int i = 0; i < count; i++) {
            if (children[i] <= 0) continue;
            int status;
            pid_t result = waitpid(children[i], &status, WNOHANG);
            if (result == children[i]) {
                if (WIFEXITED(status)) printf("parent: child[%d] reaped exit=%d\n", i, WEXITSTATUS(status));
                else if (WIFSIGNALED(status)) printf("parent: child[%d] reaped signal=%d\n", i, WTERMSIG(status));
                children[i] = -1;
                remaining--;
            } else if (result < 0 && errno != EINTR) {
                perror("waitpid");
                children[i] = -1;
                remaining--;
            }
        }
        if (elapsed(&started) > timeout) {
            for (int i = 0; i < count; i++) if (children[i] > 0) {
                printf("parent: timeout; sending SIGTERM to child[%d]\n", i);
                kill(children[i], SIGTERM);
            }
            for (int i = 0; i < count; i++) if (children[i] > 0) {
                waitpid(children[i], NULL, 0);
                children[i] = -1;
                remaining--;
            }
        }
        usleep(100000);
    }
    free(children);
    puts("parent: all children reaped; no zombies remain");
    return EXIT_SUCCESS;
}
