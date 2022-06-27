/*
    monpipe.c
    Permet de rediriger vers la fonction pipeline avec les arguments de gauche et de droite
*/

# include "sys.h"

enum {
    MaxDirs = 100
};

void pipeline(char *[], int);

int monpipe(char * mot[], int lstpipe) {
    int prevpipe = 0; // placement du pipe precedent+1 ou bien 0
    char **cmd[MaxDirs];
    int cmdindex = 0; // l'index pour cmd
    for(int i = 0; mot[i] != NULL ; i++) {
        if(strcmp(mot[i], "|") == 0) {
            char *arg[MaxDirs];
            int argindex = 0; // l'index pour arg
            for(int k = prevpipe+0; mot[k] != NULL && k < i; k++) {
                // printf("cmdindex : %d, argindex : %d,  : %s\n", cmdindex, argindex, mot[k]); // utile pour verifier que les argument sont bien stockés
                char * w = strdup(mot[k]);
                arg[argindex] = w;
                argindex++;
            }
            arg[argindex] = NULL;
            *(cmd+cmdindex) = arg;
            cmdindex++;
            prevpipe = i+1;
            pipeline(arg, 1);
        }
        if(i == lstpipe) {
            char *arg[MaxDirs];
            int argindex = 0;
            for(int k = prevpipe+0; mot[k] != NULL; k++) {
                // printf("cmdindex : %d, argindex : %d,  : %s\n", cmdindex, argindex, mot[k]); // utile pour verifier que les argument sont bien stockés
                char * w = strdup(mot[k]);
                arg[argindex] = w;
                argindex++;
            }
            arg[argindex] = NULL;
            *(cmd+cmdindex) = arg;
            *(cmd+cmdindex+1) = NULL;
            pipeline(arg, 0);
        }
    }
    exit(0);
}


