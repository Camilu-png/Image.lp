#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lpcv/include/core.h"
#include "../lpcv/include/imgproc.h"


int main(int argc, char *argv[]) {

    if(argc!=4) {
        printf("Faltan rutas a la imagen en formato lp y/o carpeta de salida.\n");
        printf("Uso: %s <imagen_rgb.lp> <imagen_gray.lp> <carpeta>", argv[0]);
        printf("\n\t<imagen_rgb.lp>: ruta a imagen rgb con formato lp\n\t<imagen_gray.lp>: ruta a imagen en escala de grises con formato lp\n\t<carpeta>: ruta a carpeta de salida (con '/' al final)");
        exit(1);
    }
    char *src_image_rgb_path = argv[1];
    char *src_image_gray_path = argv[2];
    char *dst_folder_path = argv[3];
    char dst_copy_gray_path[120] = "";
    char dst_rgb_to_gray_path[120] = "";
    char dst_R_path[120] = "";
    char dst_G_path[120] = "";
    char dst_B_path[120] = "";

    // Saludo
    greetings();

    // Voltear imagen 
    // 1. Abrir imagenes originales
    Image *original_rgb, *original_gray;
    original_rgb = open(src_image_rgb_path);
    original_gray = open(src_image_gray_path);
    
    // 2. Hacer copias para los 3 canales y 2 copias
    Image *copy_gray, *new_gray;
    Image *r_image, *b_image, *g_image;
    
    // Copiar una imagen en escala de grises
    strcat(dst_copy_gray_path, dst_folder_path);
    strcat(dst_copy_gray_path, "/gray_copy.lp");
    copy_gray = copyTo(original_gray);

    // Crear una imagen de escala de grises
    strcat(dst_rgb_to_gray_path, dst_folder_path);
    strcat(dst_rgb_to_gray_path, "/gray_new.lp");
    new_gray = copyTo(original_rgb);
    toGray(new_gray);

    // 3. Separar canales a R G B
    strcat(dst_R_path, dst_folder_path);
    strcat(dst_R_path, "/R.lp");
    strcat(dst_G_path, dst_folder_path);
    strcat(dst_G_path, "/G.lp");
    strcat(dst_B_path, dst_folder_path);
    strcat(dst_B_path, "/B.lp");
    split(original_rgb, &r_image, &g_image, &b_image);

    // 4. Guardar resultados
    printf("Guardando 'gray copy' en %s\n", dst_copy_gray_path);
    write(dst_copy_gray_path, copy_gray);

    printf("Guardando 'gray new' en %s\n", dst_rgb_to_gray_path);
    write(dst_rgb_to_gray_path, new_gray);

    printf("Guardando 'R' en %s\n", dst_R_path);
    write(dst_R_path, r_image);

    printf("Guardando 'G' en %s\n", dst_G_path);
    write(dst_G_path, g_image);

    printf("Guardando 'B' en %s\n", dst_B_path);
    write(dst_B_path, b_image);

    // 5. Cerrar imagenes 
    close(&r_image);
    close(&g_image);
    close(&b_image);
    close(&copy_gray);
    close(&new_gray);
    close(&original_gray);
    close(&original_rgb);

    return 0;
}