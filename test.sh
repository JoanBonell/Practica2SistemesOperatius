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
