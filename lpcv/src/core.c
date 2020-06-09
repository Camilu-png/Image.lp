#include "../include/core.h"

// greetings: Imprime un saludo.
void greetings() {
    printf("Hola, Mundo!");
}


/* open: Carga una imagen en formato lp.
/  Retorna un puntero a un image almacenado en heap.*/
Image* open(char* lp_image_filepath) {
    int num_linea = -1;         // Se usa para saber en que lina se esta.
    int dim = 0;                // Contador que sirve de puntero para calcuar posicion de las dimensiones de level.
    int numero = 0;             // Numero que encuentra.
    int count_x_y = 0;          // Para saber si el numero que se encontro es de x, y o channels de level.
    int size_x = 0, size_y = 0, channels = 0; // tamños respectivos de iamge.

    //Se pide memoria para image.
    Image *image = malloc(sizeof(image));

    //Se abre el archivo file.
    FILE *fich;
    fich = fopen(lp_image_filepath, "r");

    char linea[1024];
    while (fgets(linea, 1024, (FILE *)fich))
    {
        num_linea++;

        // Array de char que guarda las dimensiones.
        char simbolo[strlen(linea)];

        if (num_linea == 0)
        {

            for (int i = 0; i < strlen(linea); i++)
            {
                if (linea[i] != ' ' && linea[i] != '\n')
                {
                    simbolo[i - dim] = linea[i];
                }
                else
                {
                    simbolo[i - dim] = '\0';

                    numero = 0;

                    for (int it = 0; it < strlen(simbolo); it++)
                    {
                        //Se convierte de un char a int.
                        //A simbolo se le resta '0' y esto da el valor numerico del digito
                        //Luego se eleva a la postenecia de 10 dependiendo de su posicion.
                        numero = numero + (simbolo[it] - '0') * pow(10, i - dim - it - 1);
                    }

                    dim = i + 1;

                    if (count_x_y == 0)
                    {
                        size_x = numero;
                        count_x_y++;
                    }
                    if (count_x_y == 1)
                    {
                        size_y = numero;
                        count_x_y++;
                    }
                    else {
                        channels = numero;
                    }

                    if (size_x != 0 && size_y != 0 && channels !=0)
                    {
                        //Se asigna las dimenciones de image. 
                        image->width = size_x;
                        image->height = size_y;
                        image->channels = channels;

                        //Se pide memoria.
                        image->matrix = malloc(image->channels * sizeof(char *));

                        for (int z = 0; z < image->channels; z++)
                        {
                            image->matrix[z] = malloc(image->channels * sizeof(char));

                            for (int y = 0; y < image->height; y++){
                                    image->matrix[y] = malloc(image->height * sizeof(char));
                                for (int x = 0; x < image->width; x++){
                                    image->matrix[x] = malloc(image->width * sizeof(char));
                                }
                            }
                        }
                    }
                }
            }
        }
        else{  
            if (num_linea <= channels){   
                for (int z = 0; z <= channels; z++){
                    for (int i = 0; i < 2 * size_x - 1; i++){
                        if (linea[i] == ' ') {
                            continue;
                        }
                        else{
                            image->matrix[z][num_linea - 1][i / 2] = linea[i];
                        }
                    }
                }
            }
        }
    }

    fclose(fich);
    return image;
}


/* info: Imprime informacion basica de la imagen */
void info(Image* image) {
    printf(&image);
}


/* write: Escribe una imagen en formato lp.
/ src_image no puede contener una imagen cerrada o vacia.*/
bool write(char* lp_image_filepath, Image* src_image) {
    return true;
}


/* close: Libera la memoria de una imagen.
/ image no puede ser una imagen ya cerrada (pixels == NULL) o vacia. 
/ OJO! esto libera el contenido de la imagen y el puntero a la imagen!*/
void close(Image** closing_image) {
    
}

/*void level_free(level *lvl){
    // Free each row first
    for(int y=0;y<lvl->size_y;y++){
        free(lvl->cells[y]);
    }
    // Free char* array
    free(lvl->cells);
    // Free the level
    free(lvl);
}
*/

/* copyTo: Copia la imagen source en una imagen destination
/ Crea en heap una nueva imagen, y retorna su direccion de memoria.
/ src_image no puede ser una imagen vacia o que se haya cerrado*/
Image* copyTo(Image* src_image) {
    return malloc(sizeof(Image));
}