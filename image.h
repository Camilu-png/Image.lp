#ifndef IMAGE
#define IMAGE

// Image: Contenedor de una imagen
struct _Image {
    int width, height, channels;
    char ***matrix;
};

typedef struct _Image Image;

#endif