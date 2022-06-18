#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(2, "usage: sleep number \n");
        exit(1);
    }
    int num = atoi(argv[0]);
    sleep(num);
    exit(0);   
}
