/*  Autors:
    - Ricard Bosch Perianes.
    - Joan Bonell Ruiz.*/
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
            //Si falla el movimento, mostrar un mensaje de error.
            fprintf(sterr, "Error al mover '%s' a la carpeta .trash.\n", src_path);
        }
      }
    }
  }
    return 0;
}


