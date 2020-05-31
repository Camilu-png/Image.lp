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
    char dst4_copy_path[120] = "";

    // Saludo
    greetings();

    // Voltear imagen 
    // 1. Abrir imagen original
    Image* original;
    original = open(src_image_path);
    
    // 2. Hacer tres copias para las 3 rotaciones
    Image *small, *medium, *big, *double_big;
    
    // kernel 3
    strcat(dst1_copy_path, dst_folder_path);
    strcat(dst1_copy_path, "/small.lp");
    small = copyTo(original);
    
    // kernel 5
    strcat(dst2_copy_path, dst_folder_path);
    strcat(dst2_copy_path, "/medium.lp");
    medium = copyTo(original);
    
    // kernel 7
    strcat(dst3_copy_path, dst_folder_path);
    strcat(dst3_copy_path, "/big.lp");
    big = copyTo(original);
    
    // kernel 7 x2
    strcat(dst4_copy_path, dst_folder_path);
    strcat(dst4_copy_path, "/double.lp");
    double_big = copyTo(original);

    // 3. Aplicar a cada copia
    blur(small, 3);
    blur(medium, 5);
    blur(big, 7);
    blur(double_big, 7);
    blur(double_big, 7);

    // 4. Guardar copia
    printf("Guardando 'small' en %s\n", dst1_copy_path);
    write(dst1_copy_path, small);

    printf("Guardando 'medium' en %s\n", dst2_copy_path);
    write(dst2_copy_path, medium);

    printf("Guardando 'big' en %s\n", dst3_copy_path);
    write(dst3_copy_path, big);

    printf("Guardando 'double' en %s\n", dst4_copy_path);
    write(dst4_copy_path, double_big);

    // 5. Cerrar imagenes 
    close(&small);
    close(&medium);
    close(&big);
    close(&double_big);
    close(&original);

    return 0;
}