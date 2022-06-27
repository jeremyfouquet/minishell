# include "sys.h"
char * chevrons[4] = {">", ">>", "<", "<<"};

enum {
    Size = 1,
};

enum {
    MaxDirs = 100
};

char buffer[ Size];

int monsystem(char *);
void copier(int, int);
int chevronplacement(char *[]);

int dernierpipe(char *[]);
void pipeline(char *[], int);

int redirection(int ac, char * mot[]) {
    int placement = chevronplacement(mot);
    int prevpipe = 0; // placement du pipe precedent+1 ou bien 0
    int lstpipe = dernierpipe(mot); // placement du dernier pipe
    // int i = 0;
    char **cmd[MaxDirs];
    int cmdindex = 0; // l'index pour cmd
    if (placement != -1) {
        if (placement == 0) {
            for(int i = 0; mot[i] != NULL && i < ac - 1; i++) {
                if(strcmp(mot[i], chevrons[0]) == 0) {
                    int t = open(mot[i+1], O_WRONLY|O_TRUNC|O_CREAT, 0666);
                    copier(0, t);
                } else if (strcmp(mot[i], chevrons[1]) == 0) {
                    int t = open(mot[i+1], O_WRONLY|O_APPEND|O_CREAT, 0666);
                    copier(0, t);
                } else if (strcmp(mot[i], chevrons[2]) == 0) {
                    FILE * fp;
                    int c;
                    fp = fopen(mot[i+1],"r");
                    while(1) {
                        c = fgetc(fp);
                        if( feof(fp) ) {
                            break ;
                        }
                        printf("%c", c);
                    }
                    fclose(fp);
                } else if (strcmp(mot[i], chevrons[3]) == 0) {
                    // todo
                }
            }
        } else {
            for(int i = 0; mot[i] != NULL && i < ac - 1; i++) {
                if(strcmp(mot[i], chevrons[0]) == 0) {
                    freopen(mot[i+1], "w+", stdout);
                } else if (strcmp(mot[i], chevrons[1]) == 0) {
                    freopen(mot[i+1], "a+", stdout);
                } else if (strcmp(mot[i], chevrons[2]) == 0) {
                    freopen(mot[i+1], "r", stdin);
                } else if (strcmp(mot[i], chevrons[3]) == 0) {
                    freopen(mot[i+1], "r", stdin);
                }
                if (i == placement) {
                    char commande[100];
                    strcpy(commande, mot[0]);
                    for(int i = 1; mot[i] != NULL && i < placement; i++) {
                        if (i > 0) strcat(commande, " ");
                        strcat(commande, mot[i]);
                    }
                    monsystem(commande);
                }
            }
        }
        exit(0);
    } else if (lstpipe != -1) {// si il y a un pipe dans les arguments
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
        exit(0); // sort avec exit(0) si au moins un pipe dans les arguments
    }
    return 1;
}

int chevronplacement(char * mot[]) {
    int placement = -1;
    for(int i = 0; chevrons[i] != NULL && i < 4; i++) {
        for(int j = 0; mot[j] != NULL; j++) {
            if(strcmp(mot[j], chevrons[i]) == 0) {
                placement = j;
                break;
            }
        }
    }
    return placement;
}

void copier(int in, int out){
    int t;
    while((t = read(in, buffer, sizeof buffer) ) > 0) write(out, buffer, t);
    if ( t < 0) perror("read");
}

int dernierpipe(char * mot[]) {
    int placement = -1;
    for(int j = 0; mot[j] != NULL; j++) {
        if(strcmp(mot[j], "|") == 0) {
            placement = j;
        }
    }
    return placement;
}