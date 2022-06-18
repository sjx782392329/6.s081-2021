#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

// 当前的程序名字是什么，argc 和 argv 是程序名字以及后面的东西
// 包含了程序的名字本身
// echo world | xargs    echo     hello
// argc = 3     argv[0]  argv[1]  argv[2]
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("xargs <command>\n");
        exit(1);
    }

    char *commmandArgv[MAXARG];
    int commandSize = argc - 1;
    // printf("argc: %d\n", argc);
    // for (int i = 0; i < argc; i++) {
    //     printf("argv[%d]: %s\n", i, argv[i]);
    // }
    for (int i = 0; i < commandSize; i++) {
        commmandArgv[i] = argv[i + 1];
        // printf("commmandArgv[%d]: %s\n", i, commmandArgv[i]);
    }

    char inputBuf[512];
    char inputChar;
    int inputNum = 0;
    while(read(0, &inputChar, sizeof(char)) > 0) {
        // printf("inputChar: %c \n", inputChar);
        // if (inputChar == '\n') {
        //     printf("========\n");
        // }
        //每一个 echo 输出都是以 \n 结尾
        if (inputChar == '\n') {
            // printf("inputNum: %d\n", inputNum);
            inputBuf[inputNum] = 0;
            commmandArgv[commandSize++] = inputBuf;
            commmandArgv[commandSize] = 0;
            for (int i = 0; i < commandSize; i++) {
                printf("commmandArgv[%d]: %s\n", i, commmandArgv[i]);
            }
            if (fork() == 0) {
                exec(argv[1], commmandArgv);
            }
            wait(0);
            // commandSize = argc - 1;
            // inputNum = 0;
        } 
        // else if (inputChar == ' ') {
        //     //如果有空格 说明这是第二个参数
        //     inputBuf[inputNum++] = 0;
        //     // printf("我被执行了\n");
        //     // char *pc = inputBuf;
        //     // while (*pc != '\0') {
        //     //     printf("%c\n", *pc++);
        //     // }
        // } 
        else {
            inputBuf[inputNum++] = inputChar;
        }
    }
    exit(0);
}