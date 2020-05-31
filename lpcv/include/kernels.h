#ifndef KERNELS
#define KERNELS

/* gaussian_kernel_approximation: obtiene el valor para una posicion y tamano dados.
/  Considera solo los casos en que, tanto i como j cumplen con
/  i, j \in [-(size-1)/2, (size-1)/2]. Además size debe ser entero, positivo e impar.
/  Solo se consideren valores de size igual a 3, 5 o 7.*/
float gaussian_kernel_approximation(int i, int j, int size);

#endif