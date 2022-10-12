# Activitat 01: Eliminació segura a UNIX (Mòdul 1)

*Instructor*: [Jordi Mateo Fornés](http:jordimateofornes.com)

*Course*: [Grau en Tècniques d'Interacció Digital i de Computació](http://www.grauinteraccioicomputacio.udl.cat/ca/index.html)

*University*: University of Lleida - Campus Igualada - Escola Politècnica Superior

*Estudiants*: Joan Bonell
              Ricard Bosch


## Part pràctica: Instal·lar un paquet 

### Enunciat
La vostra tasca és implementar en C aquesta funcionalitat.

### Resposta

#include <stdio.h> //rename()
#include <stdlib.h> //exit()
#include <unistd.h> // getuid()
#include <sys/types.h> //getuid()
#include <dirent.h> //opendir()
#include <pwd.h> //getpwuid()
#include <errno.h> // perror()
#include <string.h> //strcopy() strcat()
#include <sys/stat.h> //stat() mkdir()


int main(int argc, char *argv[]){
    //Rmsf utility
    //Check for arguments
    //  Comprovem que els arguments que ens passen siguin correctes:
    if(argc < 2){
       fprintf(stderr, "Usabilitat: ./rmsf fitxer1 fitxer2 fitxer3 ... fitxerN");
       exit(1);
    }
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
                    printf("Fitxer %s mogut a la carpeta trash", argv[i]);
                    //  Comprovem que el rename s'hagi fet correctament:
                    if(rename(argv[i], new) == -1){
                        perror("Error: No s'ha pogut moure el fitxer correctament.");
                        exit(1);
                    }
                    exit(1);
                }
            }
            
        }      
    }
    exit(1);
}


## Part pràctica: Instal·lar la comanda al sistema rmsf

### Enunciat

Explique els pasos realitzats.

### Resposta

Per a poder tenir una comanda, pròpia, haurem de posar el fitxer executable dins de la carpeta /bin/bash.
Amb la comanda MV ho podrem fer.
Pas 2: Donem permisos d’execució a l’executable.
chmod +x rmsf
Ara ja podem escriure ./rmsf desde qualsevol àrea del sistema amb els seus arguments.

## Part pràctica: Test

### Enunciat

La vostra tasca és prepar un fitxer test.sh que contingui totes les comandes que heu fet anar per testejar la vostra solució.

### Resposta

El nostre fitxer test.sh queda així:

mkdir dir
cd dir
mkdir subdir 
cd ..
./rmsf file1
./rmsf file1 dir
./rmsf file1 dir/file2
./rmsf file1 dir/subdir/file2

## Part pràctica: Automatització amb Make

### Enunciat

La vostra tasca és revisar el funcionament dels Makefiles. Heu de preparar un Makefile que sigui capaç de compilar, executar, testejar amb el fitxer test.sh i instal·lar l’executable al sistema.``

### Resposta

make: rmsf.c
  gcc -c rmsf.c

executable: rmsf.o
  gcc -o rmsf rmsf.o

test:
  ./rmsf < test.sh
