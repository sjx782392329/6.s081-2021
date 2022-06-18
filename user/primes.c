#include "kernel/types.h"
#include "user/user.h"

int primes(int p1[], int p2[]);
int 
main() {
    int p1[2];
    int p2[2];
    
    // 0: read
    // 1: write
    pipe(p1);
    pipe(p2);

    int num[1];
    for (num[0] = 2; num[0] <= 35; num[0]++) {
        write(p1[1], num, sizeof(num));
    }
    close(p1[1]);
    primes(p1, p2);
    exit(0);
}

int 
primes(int p1[], int p2[]) {
    if (fork() == 0) {
        int num[1];
        if (read(p1[0], num, sizeof(num)) != sizeof(num)) {
            close(p1[0]);
            close(p2[0]);
            close(p2[1]);
            exit(0);
        }
        int out = num[0];
        printf("prime %d\n", out);
        while (read(p1[0], num, sizeof(num)) == sizeof(num)) {
            if (num[0] % out != 0) {
                write(p2[1], num, sizeof(num));
            }
        }
        close(p2[1]);
        pipe(p1);
        primes(p2, p1);
        exit(0);
    } else {
        close(p1[0]);
        close(p2[0]);
        close(p2[1]);
        wait(0);
        exit(0);
    }
}
