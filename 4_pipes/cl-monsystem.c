/*
    cl−monsystem.c
    Une re−implementation de la fonction system
*/
# include "sys.h"

int monsystem(char * command){
    int pid, x, etat ;
    pid = fork() ;
    if (pid < 0){
        perror("fork");
        return -1;
    }
    if (pid != 0){ // parent
        for(;;) {
            x = wait(&etat);
            if ( x == pid)
            return etat ;
        }
    }
    // enfant
    execl("/bin/sh", "sh", "-c", command, NULL);
    perror("execl");
    return -1;
}