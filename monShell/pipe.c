/*******************************************************
# Nom ......... : pipe
# Rôle ........ : creation d'un pipe et execution des arguments de gauche et de droite
# Auteur ...... : jeremy fouquet
# Version ..... : V1 du 05/05/2022
# Licence ..... : réalisé dans le cadre du cours de L2 de Philippe Kislin
********************************************************/

# include "sys.h"

int   fd[2];
pid_t pid;
int   fdd = 0;

// source : https://askcodez.com/le-codage-de-multiples-pipe-en-c.html
void pipeline(char *cmd[], int last) {
    pipe(fd);
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        dup2(fdd, 0); // change l'entrée par l'ancien
            if (last > 0) dup2(fd[1], 1);
        close(fd[0]);
        execvp(cmd[0], cmd);
        exit(1);
    } else {
        wait(NULL);
        close(fd[1]);
        fdd = fd[0]; // enregistre l'entrée pour la prochaine commande
    }
}