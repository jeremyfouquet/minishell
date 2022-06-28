
# DOCUMENTATION DU PROGRAMME

## CONFIGURATION
### compilation et lancement
    ```
    make && ./minishell
    ```
### mise à jour et lancement
    ```
    make all && ./miniShell
    ```

### supprimer les executables
    ```
    make clean
    make cleanall
    ```

## DESCRIPTION
    ```
    shell élémentaire qui prend en capacité les fonctions cd et exit, les redirections d'entrées-sorties, les pipes ainsi que l'auto-complétion des noms de fichiers
    ```

## COMMANDES
### Exit
    ```
    Permet la sortie du shell
    Utilisation :
        exit
    ```
### Cd
    ```
    Changer de repertoire courant
    Exemple d'utilisation :
        cd
        cd ..
        cd ./<nom du repertoire>
    ```
### les redirections
    ```
    Permet la redirections d’entrée-sortie comme dans un shell ordinaire, avec les chevrons ('<' ; '>' ; '<<' ; '>>')
    Exemple d'utilisation :
        echo 'ecrire quelque chose' > <nom du fichier>
        < <nom du fichier>
        wc < <nom du fichier d'entré> > <nom du fichier de sortie>
        >> <nom du fichier>
    ```
### les pipes
    ```
    Permet de passer le résultat d'une commande shell à une autre commande shell
    Exemple d'utilisation :
        ls | wc
        ls -l | wc
        cat <nom du fichier> | sort | uniq
    ```
### l'auto-completion
    ```
    Permet l'auto-completion des nom de fichier present dans le repertoire courant
    Exemple d'utilisation :
        <debut du nom du fichier> + touche tab
    ```

## NOTES
    ```
    Projet réalisé dans le cadre du cours de L2 Systeme d'Exploitation de Philippe Kislin
    ```

## BUGS (BOGUES)
    ```
    Certaines commandes ne sont pas fonctionnelles :
        touche directionnelle
        ctrl + ...
        le chevron de redirection '<<'
        les procedures d'arrière plan avec '&'
    ```

## AUTHOR (AUTEUR)
    ```
    jeremy fouquet
    ```