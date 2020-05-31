#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lpcv/include/core.h"


int main(int argc, char *argv[]) {

    if(argc!=3) {
        printf("Faltan rutas a la imagen en formato lp y/o carpeta de salida.\n");
        printf("Uso: %s <imagen.lp> <carpeta>", argv[0]);
        printf("\n\t<imagen.lp>: ruta a imagen con formato lp\n\t<carpeta>: ruta a carpeta de salida (con '/' al final)");
        exit(1);
    }
    char *src_image_path = argv[1];
    char *dst_folder_path = argv[2];
    char dst_copy_path[120] = "";

    // Saludo
    greetings();

    // Input Output
    // 1. Abrir imagen original
    Image* original;
    original = open(src_image_path);
    info(original);
    
    // 2. Hacer una copia
    strcat(dst_copy_path, dst_folder_path);
    strcat(dst_copy_path, "/copy.lp");
    Image* copy = copyTo(original);
    
    // 3. Guardar copia
    printf("Guardando copia en %s\n", dst_copy_path);
    write(dst_copy_path, copy);

    // Cerrar imagenes 
    close(&copy);
    close(&original);

    return 0;
}