#include <stdio.h> //rename()
#include <stdlib.h> //exit()
#include <unistd.h> // getuid()
#include <sys/types.h> //getuid()
#include <dirent.h> //opendir()
#include <pwd.h> //getpwuid()
#include <errno.h> // perror()
#include <string.h> //strcopy() strcat()
#include <sys/stat.h> //stat() mkdir()

/*  The rmsf utility attempts to move files and foldes on the command line to the ./trash folder
    located at the user's home. This is not an actual remove. Note that the program will create
    the trash folder if it does not exist. If the file's permissions do not permit writing, and the
    standard input device is a terminal, the user is prompted (on the standerd error output)
    for confirmation.*/

int main(int argc, char *argv[]){
    //Rmsf utility
    //Check for arguments
    //  Comprovem que els arguments que ens passen siguin correctes:
    if(argc < 2){
        fprintf(stderr, "Usabilitat: ./rmsf fitxer1 fitxer2 fitxer3 ... fitxerN");
        exit(1);
    
    //Check if the trash folder exists
    //  Comprovem que existeixi el directori trash:
    struct stat st = {0};
    if(stat("./trash", &st) == -1){
        mkdir("./trash", S_IWOTH); // Creem el trash amb permisos S_IWOTH, el propietari i tots els altres grups tenen permisos per llegir, escriure i executar.
        
    }

    //  Comprovem que l'usuari no sigui root per evitar que borri fitxers que no li pertanyen:
    if(getuid() == 0){ //id de root = 0
        fprintf(stderr, "Error: rmsf no es pot carregar com a root \n");
        exit(1);
    }

    // Mirem que els arguments que ens passen siguin correctes:
    int i;
    for(i = 1; i < argc; i++){
        //  Comprovem que el fitxer existeixi:
        if(access(argv[i], F_OK) == -1){
            fprintf(stderr, "Error: %s no existeix", argv[i]);
            exit(1);
        }

        //  Comprovem que el fitxer no sigui un directori:
        if(opendir(argv[i]) != NULL){
            fprintf(stderr, "Error: %s es una carpeta", argv[i]);
            exit(1);
        }

        //  Comprovem que el fitxer sigui escribible:
        if(access(argv[i], W_OK) == -1){
            //  Comprovem que el dispositiu d'entrada estàndard sigui un terminal:
            if(isatty(fileno(stdin))){
                //  Demanem confirmació a l'usuari:
                char *input = malloc(10);
                fprintf(stderr, "Estàs segur que vols remoure el fitxer %s? (y/n): ", argv[i]);
                fgets(input, 10, stdin);
                if(strcmp(input, "y")==0){
                    //  Mirem el directori on es troba el fitxer:
                    char *home = getpwuid(getuid())->pw_dir;
                    //  Creem el path del fitxer:
                    char *trash = strcat(home, "/trash");
                    char *new = strcat(trash, argv[i]);
                    rename(argv[i], new);
                    //  Comprovem que el rename s'hagi fet correctament:
                    if(rename(argv[i], new) == -1){
                        perror("Error: No s'ha pogut moure el fitxer correctament.");
                        exit(1);
                    }
                }
            }
            
        }      
    }
    exit(1);
}
