/*
    redirection.c
    Permet la redirections d’entrée-sortie comme dans un shell ordinaire, avec les chevrons
*/

# include "sys.h"

enum {
    Size = 1,
};
char buffer[ Size];

int monsystem(char *);
void copier(int, int);

int redirection(int ac, char * mot[], int placement, char * chevrons[]) {
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
                // A faire fonctionnement du chevron "<<"
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
}

// Permet de copier l'entrée in en lecture dans la sortie out en écriture
void copier(int in, int out){
    int t;
    while((t = read(in, buffer, sizeof buffer) ) > 0) write(out, buffer, t);
    if ( t < 0) perror("read");
}