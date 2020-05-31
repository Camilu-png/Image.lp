#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lpcv/include/core.h"
#include "../lpcv/include/imgproc.h"


int main(int argc, char *argv[]) {

    if(argc!=3) {
        printf("Faltan rutas a la imagen en formato lp y/o carpeta de salida.\n");
        printf("Uso: %s <imagen.lp> <carpeta>", argv[0]);
        printf("\n\t<imagen.lp>: ruta a imagen con formato lp\n\t<carpeta>: ruta a carpeta de salida (con '/' al final)");
        exit(1);
    }
    char *src_image_path = argv[1];
    char *dst_folder_path = argv[2];
    char dst1_copy_path[120] = "";
    char dst2_copy_path[120] = "";
    char dst3_copy_path[120] = "";

    // Saludo
    greetings();

    // Voltear imagen 
    // 1. Abrir imagen original
    Image* original;
    original = open(src_image_path);
    
    // 2. Hacer tres copias para las 3 rotaciones
    Image *vertical_image, *horizontal_image, *both_image;
    
    // Eje vertical
    strcat(dst1_copy_path, dst_folder_path);
    strcat(dst1_copy_path, "/vertical.lp");
    vertical_image = copyTo(original);

    // Eje horizontal
    strcat(dst2_copy_path, dst_folder_path);
    strcat(dst2_copy_path, "/horizontal.lp");
    horizontal_image = copyTo(original);

    // Ambos
    strcat(dst3_copy_path, dst_folder_path);
    strcat(dst3_copy_path, "/both.lp");
    both_image = copyTo(original);

    // 3. Aplicar a cada copia, V, H y V+H
    flip(vertical_image, Vertical);
    flip(horizontal_image, Horizontal);
    flip(both_image, Vertical);
    flip(both_image, Horizontal);

    // 4. Guardar copia
    printf("Guardando 'vertical' en %s\n", dst1_copy_path);
    write(dst1_copy_path, vertical_image);

    printf("Guardando 'horizontal' en %s\n", dst2_copy_path);
    write(dst2_copy_path, horizontal_image);

    printf("Guardando 'ambas' en %s\n", dst3_copy_path);
    write(dst3_copy_path, both_image);

    // 5. Cerrar imagenes 
    close(&vertical_image);
    close(&horizontal_image);
    close(&both_image);
    close(&original);

    return 0;
}