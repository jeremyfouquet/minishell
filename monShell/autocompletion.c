/*
    autocompletion.c
    Permet de faire l'auto-completion des noms de fichier du repertoire courant avec la touch tabulation
*/

# include "sys.h"


int comptestr(char *);
char * dernierMot(char * ligne);

int autocompletion(char * ligne) {
    strcpy(ligne, "");
    char c;
    do {
        system("/bin/stty raw"); // source : https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar-for-reading-a-single-character-only
        c = getchar();
        if(c == 9){ // si appuis sur la touche tabulation
            system("/bin/stty cooked");
            struct dirent *dir;
            DIR *d = opendir(".");
            int iname = 0;
            if (d) {
                // source : https://waytolearnx.com/2019/09/lister-les-fichiers-dans-un-repertoire-en-c.html
                while ((dir = readdir(d)) != NULL && iname == 0) {
                    char * dernier = dernierMot(ligne);
                    int n = comptestr(dernier);
                    if(strncmp(dir->d_name, dernier, n) == 0){
                        for(; dir->d_name[n]; n++) {
                            char cnext = putchar(dir->d_name[n]);
                            strncat(ligne, &cnext, 1);
                        }
                        iname++;
                    }
                }
                closedir(d);
            }
        } else if(c == 13){ // si appuis sur la touche entrer
            system("/bin/stty cooked");
            putchar('\n');
        } else if(c == 127){ // si appuis sur la touche supprimer
            system("/bin/stty cooked");
            int size,i;
            i=size=comptestr(ligne);
            if(size > 0) {
                printf("\b");
                putchar(' ');
                printf("\b");
                while(i>size-2){
                    ligne[i]='\0';
                    i--;
                }
            }
        } else if(c == 27) { // si appuis sur une touche fleche
            // ne rien faire
        } else {
            system("/bin/stty cooked");
            putchar(c);
            strncat(ligne, &c, 1);
        }
    } while(c != 13); // boucle tant que la touche entrer n'est pas utilisé
    return strcmp(ligne, "");
}

// Compte et retourne le nombre de lettre dans une chaine de caractère
int comptestr(char * mot){
    int i;
    for(i=0; mot[i]; i++);
    return i;
}

// Retourne le dernier mot de la chaine de caractère passé en parametre
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
