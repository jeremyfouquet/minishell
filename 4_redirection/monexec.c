/*
   monexec.c
   Filtre les commandes utilisateur pour exécuter celle qui match avec le tableau des commandes : "commmandes"
   Permet également d'executer redirection si dans les commandes il y a présence d'un chevron
*/

# include "sys.h"


int moncd(int, char *[]);
int redirection(int, char *[], int, char *[]);
int chevronplacement(char *[], char *[]);

// source : https://askcodez.com/comment-comparer-pointeur-de-chaines-de-caracteres-en-c.html
int monexec(char * mot1[], int execution, int ac){
    char * commandes[6] = {"exit", "cd"};
    char * chevrons[4] = {">", ">>", "<", "<<"};
    int placement = chevronplacement(mot1, chevrons);
    const char * str1 = * mot1;
    for(int i = 0; commandes[i] != NULL && i < 2; i++) {
        const char * str2 = commandes[i];
        if(execution != 0) { // Si c'est le parent
            if (strcmp(str1, str2) == 0) { // compare 2 chaines de caracteres et renvoie 0 si elles sont identiques
                switch(i) {
                    case 0: // exit
                        printf ("Bye\n");
                        exit(0);
                    case 1: // moncd
                        moncd(ac, mot1);
                }
            }
        } else { // Si c'est l'enfant
            if (strcmp(str1, str2) == 0) // compare 2 chaines de caracteres et renvoie 0 si elles sont identiques
                exit(0);
            else if (placement != -1)
                redirection(ac, mot1, placement, chevrons);
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
