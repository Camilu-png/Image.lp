#include "../include/imgproc.h"


/* flip: Refleja una imagen en el eje Horizontal o Vertical
/  Donde Vertical intercambia los valores de las columnas ><
/  y Horizontal intercambia los valores de las filas  ^v .
/  image no puede contener una imagen cerrada o vacia.*/
void flip(Image* image, enum direction d) {
}


/* toGray: Convierte una imagen en rgb a escala de grises.
/ Esto ocurre en la misma imagen, modificando pixels y/o sus valores.
/ rgb_image no puede estar cerrada, y debe tener 3 canales*/
void toGray(Image* rgb_image) {
}


/* split: Divide una imagen rgb a en sus tres canales.
/  A Partir de una imagen rgb con tres canales, guarda los
/  valores de cada canal en 3 imagenes de 1 canal.
/  rgb_image no puede estar cerrada, y debe tener 3 canales
/  r_imagen, g_image y b_image no puede contener una imagen abierta.*/ 
void split(Image* rgb_image, Image** r_image, Image** g_image, Image** b_image) {
}


/* blur: Aplica un filtro para difuminar la imagen.
/  Aplica un filtro gaussiano de tamano impar (considerar solo tamanos 3, 5 y 7),
/  Se calcula con una convolucion entre la imagen y un kernel, con padding 0. 
/  Notar que cuando la imagen tiene mas de un canal, la convolucion se aplica 
/  a cada canal por separado.
/  image no puede estar cerrada*/
void blur(Image* image, unsigned int size) {
}