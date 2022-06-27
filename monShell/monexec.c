/*
  monexec.c
  Filtre les commandes utilisateur pour exécuter celle qui match avec le tableau des commandes : "commmandes"
*/

# include "sys.h"

int moncd(int, char *[]);

// source : https://askcodez.com/comment-comparer-pointeur-de-chaines-de-caracteres-en-c.html
int monexec(char * mot1[], int execution, int ac){
    char * commandes[2] = {"exit", "cd"};
    const char * str1 = * mot1;
    for(int i = 0; commandes[i] != NULL && i < 2; i++) {
        const char * str2 = commandes[i];
        if(execution != 0) { // si c'est le parent
            if (strcmp(str1, str2) == 0) { // compare 2 chaines de caracteres et renvoie 0 si elles sont identiques
                switch(i) {
                    case 0: // exit
                        printf ("Bye\n");
                        exit(0);
                    case 1: // moncd
                        moncd(ac, mot1);
                }
            }
        } else { // si c'est l'enfant
            if (strcmp(str1, str2) == 0) { // compare 2 chaines de caracteres et renvoie 0 si elles sont identiques
                exit(0);
            }
        }
    }
    return 1;
}