/*******************************************************
# Nom ......... : co-main
# Rôle ........ : shell élémentaire qui prend en capacité les fonctions cd et exit, les redirection d'entrées-sorties, les pipes ainsi que l'auto-complétion des noms de fichiers
# Auteur ...... : jeremy fouquet
# Version ..... : 27/06/2022
# Licence ..... : réalisé dans le cadre du cours de L2 de Philippe Kislin
# Compilation : gcc -Wall *.c
# Usage : ./a.out
********************************************************/

# include "sys.h"

enum {
    MaxLigne = 1024, // longueur max d'une ligne de commandes
    MaxMot = MaxLigne / 2, // nbre max de mot dans la ligne
    MaxDirs = 100, // nbre max de repertoire dans PATH
    MaxPathLength = 512, // longueur max d'un nom de fichier
};

void decouper(char *, char *, char **, int);
int monexec(char *[], int, int);
int compte(char * []);
int redirection(int, char *[]);

int ecouteTab(char *, char *);
int comptestr(char *);
char * dernierMot(char * ligne);

# define PROMPT "? "

int main(int argc, char * argv[]) {
    char ligne[MaxLigne];
    char pathname[MaxPathLength];
    char * mot[MaxMot];
    char * dirs [MaxDirs];
    int i , tmp;

    /* Decouper UNE COPIE de PATH en repertoires */
    decouper(strdup(getenv("PATH")), ":", dirs, MaxDirs);
    /* Lire et traiter chaque ligne de commande */
    for(printf (PROMPT); ecouteTab(ligne, "") > 0; printf (PROMPT)){
        decouper(ligne, " \t\n", mot, MaxMot);
        int ac = compte(mot);
        if (mot[0] == 0) // ligne vide
            continue;
        tmp = fork(); // lancer le processus enfant
        if ( tmp < 0){
            perror("fork");
            continue;
        }

        if ( tmp != 0){ // parent : attendre la fin de l' enfant
            while(wait(0) != tmp);
            monexec(mot, tmp, ac);
            continue;
        }

        // enfant : exec du programme
        for( i = 0; dirs [ i ] != 0; i ++){
            snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
            monexec(mot, tmp, ac);
            redirection(ac, mot);
            execv(pathname, mot);
        }
        fprintf(stderr, "%s: not found\n", mot[0]);
        exit(1) ;
    }

    printf ("Bye\n");
    return 0;
}

// Compte et retourne le nombre de mot dans un tableau de mot passé en paramètre
int compte(char * mot[]){
    int i;
    for(i=0; mot[i] != NULL; i++){
    }
    return i;
}
// Compte et retourne le nombre de lettre dans une chaine de caractère
int comptestr(char * mot){
    int i;
    for(i=0; mot[i]; i++);
    return i;
}

int ecouteTab(char * ligne, char * str) {
    strcpy(ligne, str);
    char sentence;
    system ("/bin/stty raw");
    do {
        sentence = getchar();
        if(sentence == '\t'){
            struct dirent *dir;
            DIR *d = opendir(".");
            int iname = 0;
            if (d) {
                while ((dir = readdir(d)) != NULL && iname == 0) {
                    char * dernier = dernierMot(ligne);
                    int n = comptestr(dernier);
                    if(strncmp(dir->d_name, dernier, n) == 0){
                        for(; dir->d_name[n]; n++) {
                            sentence = putchar(dir->d_name[n]);
                            strncat(ligne, &sentence, 1);
                        }
                        iname++;
                    }
                }
                closedir(d);
            }
        } else if(sentence == 13){
            putchar('\n');
        } else {
            putchar(sentence);
            strncat(ligne, &sentence, 1);
        }
    } while(sentence != 13);
    system ("/bin/stty cooked");
    return strcmp(ligne, "");
}

char * dernierMot(char * str) {
    char d[] = " ";
    char *p = strtok(strdup(str), d);
    int i = 0;
    while(p != NULL) {
        p = strtok(NULL, d);
        if(p != NULL) {
            i++;
        }
    }
    p = strtok(strdup(str), d);
    char * final;
    while(p != NULL) {
        if(i == 0) final = p;
        p = strtok(NULL, d);
        i--;
    }
    return final;
}
