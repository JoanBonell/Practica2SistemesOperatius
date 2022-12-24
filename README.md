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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
  // Verificar que se haya proporcionado al menos un archivo/carpeta a eliminar
  if (argc < 2) {
    fprintf(stderr, "Error: se debe proporcionar al menos un archivo/carpeta a eliminar.\n");
    return 1;
  }

  // Construir la ruta de la carpeta .trash
  char* home = getenv("HOME"); // Obtener el directorio home del usuario
  char trash_path[strlen(home) + 8]; // Reservar suficiente espacio para la ruta de la carpeta .trash
  sprintf(trash_path, "%s/.trash", home); // Construir la ruta

  // Crear la carpeta .trash si no existe
  struct stat st = {0};
  if (stat(trash_path, &st) == -1) {
    mkdir(trash_path, 0700);
  }

  // Recorrer cada archivo/carpeta proporcionado como argumento
  for (int i = 1; i < argc; i++) {
    char* src_path = argv[i]; // Obtener la ruta del archivo/carpeta a eliminar
    char dest_path[strlen(trash_path) + strlen(src_path) + 2]; // Reservar suficiente espacio para la ruta de destino

    // Construir la ruta de destino como "$HOME/.trash/$SRC_PATH"
    sprintf(dest_path, "%s/%s", trash_path, src_path);

    // Verificar si se tiene permiso de escritura en el archivo/carpeta
    if (access(src_path, W_OK) == 0) {
      // Si se tiene permiso, mover el archivo/carpeta a la carpeta .trash
      if (rename(src_path, dest_path) != 0) {
        // Si falla el movimiento, mostrar un mensaje de error
        fprintf(stderr, "Error al mover '%s' a la carpeta .trash.\n", src_path);
      }
    } else {
      // Si no se tiene permiso de escritura, pedir confirmación al usuario
      printf("¿Desea eliminar '%s'? [s/n] ", src_path);
      char response[3];
      scanf("%2s", response);

      if (response[0] == 's') {
        // Si el usuario confirma, mover el archivo/carpeta a la carpeta .trash
        if (rename(src_path, destpath) != 0) {
          // Si falla el movimiento, mostrar un mensaje de error.
          fprintf(stderr, "Error al mover '%s' a la carpeta .trash.\n!, src_path);
          }
      }
    }
    }
    return 0;
    }


## Part pràctica: Instal·lar la comanda al sistema rmsf

### Enunciat

Explique els pasos realitzats.

### Resposta

1 - Compila el codi font de rmsf utilitzant el compilador de C, com a GCC. Per ex. pots utilitzar la comanda 'gcc -o rmsf rmsf.c' per compilar i 'rmsf.' per generar el exectuable.

2 - Crear un enllaç a l'arxiu exectuable en un directori inclós en la variable 'PATH' del sistema. Per ex. 'ln -s /ruta/al/al/archivo/ejectuable/rmsf/usr/local/bin/rmsf' per a crear l'enllaç simbolic en el directori '/usr/local/bin'.

3 - Assegurar-se de que l'arxiu exectuable tingui permisos d'execució. 'chmod +x /ruta/al/archivo/ejectuable/rmsf' per otorgar permisos d'execució a l'arxiu.

Els usuaris haurien de poder utilitzar la comanda rmsf directament des de la línia de comandes, proporcionant el nom de l'arxiu o carpeta que desitgin eliminar com a argument. Per exemple, podrien utilitzar la comanda rmsf arxiu.txt per a moure l'arxiu arxivo.txt a la carpeta .trash.

## Part pràctica: Test

### Enunciat

La vostra tasca és prepar un fitxer test.sh que contingui totes les comandes que heu fet anar per testejar la vostra solució.

### Resposta

El nostre fitxer test.sh queda així:

#!/bin/bash

# Crear algunos archivos y carpetas de prueba
touch archivo1.txt archivo2.txt
mkdir carpeta1 carpeta2

# Ejecutar el comando rmsf con diferentes argumentos
rmsf archivo1.txt
rmsf archivo2.txt
rmsf carpeta1
rmsf carpeta2

# Verificar que los archivos y carpetas hayan sido movidos a la carpeta .trash
ls ~/.trash

# Limpiar la carpeta .trash
rm -r ~/.trash

## Part pràctica: Automatització amb Make

### Enunciat

La vostra tasca és revisar el funcionament dels Makefiles. Heu de preparar un Makefile que sigui capaç de compilar, executar, testejar amb el fitxer test.sh i instal·lar l’executable al sistema.``

### Resposta

CC = gcc
CFLAGS = -Wall -Wextra
TARGET = rmsf

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	bash test.sh

install: $(TARGET)
	ln -s $(PWD)/$(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	rm /usr/local/bin/$(TARGET)

