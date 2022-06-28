/*
   monexec.c
   Filtre les commandes utilisateur pour exécuter celle qui match avec le tableau des commandes : "commmandes"
   Permet également d'executer redirection si dans les commandes il y a présence d'un chevron
   Permet également d'executer monpipe si dans les commandes il y a présence d'un pipe
*/

# include "sys.h"


int moncd(int, char *[]);
int redirection(int, char *[], int, char *[]);
int chevronplacement(char *[], char *[]);
int dernierpipe(char *[]);
int monpipe(char * mot[], int lstpipe);

int manuel(void);

// source : https://askcodez.com/comment-comparer-pointeur-de-chaines-de-caracteres-en-c.html
int monexec(char * mot1[], int execution, int ac){
    char * commandes[3] = {"exit", "cd", "MAN"};
    char * chevrons[4] = {">", ">>", "<", "<<"};
    int placement = chevronplacement(mot1, chevrons);
    int lstpipe = dernierpipe(mot1);
    const char * str1 = * mot1;
    for(int i = 0; commandes[i] != NULL && i < 3; i++) {
        const char * str2 = commandes[i];
        if(execution != 0) { // Si c'est le parent
            if (strcmp(str1, str2) == 0) { // compare 2 chaines de caracteres et renvoie 0 si elles sont identiques
                switch(i) {
                    case 0: // exit
                        printf ("Bye\n");
                        exit(0);
                    case 1: // moncd
                        moncd(ac, mot1);
                    case 2: // moncd
                        manuel();
                }
            }
        } else { // Si c'est l'enfant
            if (strcmp(str1, str2) == 0) {// compare 2 chaines de caracteres et renvoie 0 si elles sont identiques
                exit(0);
            }
            else if (placement != -1) {
                redirection(ac, mot1, placement, chevrons);
            }
            else if (lstpipe != -1) {
                monpipe(mot1, lstpipe);
            }
        }
   }
   return 1;
}

// vérifier si un chevron est present dans une liste de chaine de caractere et retourne l'emplacement du premier chervon trouvé sinon retourn -1
int chevronplacement(char * mot[], char * chevrons[]) {
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

// vérifier si un pipe est present dans une liste de chaine de caractere et retourne l'emplacement du dernier pipe trouvé sinon retourn -1
int dernierpipe(char * mot[]) {
    int placement = -1;
    for(int j = 0; mot[j] != NULL; j++) {
        if(strcmp(mot[j], "|") == 0) {
            placement = j;
        }
    }
    return placement;
}
int manuel(void) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("./README.md", "r");
    if (fp == NULL)
        return 1;
    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }
    printf("\n");
    if (ferror(fp)) {
        /* handle error */
    }
    free(line);
    fclose(fp);
    return 0;
}
