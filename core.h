#ifndef CORE
#define CORE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "image.h"

// greetings: Imprime un mensaje de saludo.
void greetings();


/* open: Carga una imagen en formato lp.
/  Retorna un puntero a un image almacenado en heap.*/
Image* open(char* lp_image_filepath);


/* info: Imprime informacion basica de la imagen */
void info(Image* image);

/* write: Escribe una imagen en formato lp.
/ src_image no puede contener una imagen cerrada o vacia.*/
bool write(char* lp_image_filepath, Image* src_image);


/* close: Libera la memoria de una imagen.
/ image no puede ser una imagen ya cerrada (pixels == NULL) o vacia. 
/ OJO! esto libera el contenido de la imagen, y el puntero a la imagen!*/
void close(Image** closing_image);


/* copyTo: Copia la imagen source en una imagen destination
/ Crea en heap una nueva imagen, y retorna su direccion de memoria.
/ src_image no puede ser una imagen vacia o que se haya cerrado*/
Image* copyTo(Image* src_image);


#endif