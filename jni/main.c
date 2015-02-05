#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "def.h"
#include "log.h"
#include "yasul.h"

#define YSL_LOGDIR "/tmp"

int main(int argc, char **argv) {

    
    ysl_log_init(YSL_LOGDIR, 1);
    
    ysl_session_t *s = yasul_open_session(YSL_LOGDIR,
            YSL_SF_EOUT | YSL_SF_EERR | YSL_SF_VERB);
        
    if (s) {        
        while (ysl_session_stat(s)) {
            printf("waiting for shell process ...\n");
            sleep(1);
        }
        printf("connected to shell process.\n");
        
        int lec;
        char *ltty = NULL;
        int err = ysl_session_exec(s, "id", &lec, &ltty);
        printf("err: %d\n", err);
        printf("lec: %d\n", lec);
        printf("txt: %s\n", ltty);
        
        err = ysl_session_exec(s, "uname -a", &lec, &ltty);
        printf("err: %d\n", err);
        printf("lec: %d\n", lec);
        printf("txt: %s\n", ltty);
        
        ysl_session_exit(s);
        
        while (1)
            sleep(1);
        printf(">> exit.\n");
        return 0;
    }
    
    return 1;    
}
