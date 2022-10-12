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

#include <stdio.h> //Funció rename()
#include <stdlib.h>
#include <unistd.h> //Funció getuid()
#include ‹dirent.h> //Funció oendir()
#include <sys/types.h>
#include <pwd.h> //getpwuid()
#include cerrno.h> //perror()
#include <string.h> //strcopy() strncpy() streat()
#include <sys/stat.h> //mkdir()
#include <stdbool.h>
//#include ciostream.h>

bool existe_papelera();

DIR *dirp;
int main(int c, char *argvt[]){
    char pathname [50];
    //strcat(pathname, geteuid());
    if(!existe_papelera){
        //Creamos la papelera 
        printf ("NO existe papelera.");
        int status;
        status - mkdir("/home/bin/trash", S_IRWXU);
        strcat (pathname, argv[0]),
        rename (pathname,"/home/bin/trash");
    }
    else {
        printf ("La papelera existe");
        strcat (pathname, argv[0]);
        rename (pathname, "/bin/trash");
        //Movemos el argv[0] a la papelera.
        //System.IO.Directory.Move(argv[0], dirp);
    }
    printf("Is working...");
    return 0;
}

bool existe_papelera(){
    //DIR *dirp;
    dirp = opendir ("bin/trash");
    if(dirp == NULL){
        return false;
    }
    return true;


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
