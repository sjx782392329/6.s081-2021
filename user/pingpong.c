#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) {
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    if (fork() == 0) {
        char buff[10];
        read(p1[0], buff, 5);
        printf("%d: received %s", getpid(), buff);
        write(p2[1], "pong\n", 5);
    } else {
        char buff[10];
        write(p1[1],"ping\n", 5);
        read(p2[0], buff, 5);
        printf("%d: received %s", getpid(), buff);
    }
    exit(0);
}
