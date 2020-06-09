#include "../include/kernels.h"

/* gaussian_kernel_approximation: obtiene el valor para una posicion y tamano dados.
/  Considera solo los casos en que, tanto i como j cumplen con
/  i, j \in [-(size-1)/2, (size-1)/2]. Además size debe ser entero, positivo e impar.
/  Solo se consideren valores de size igual a 3, 5 o 7.*/
float gaussian_kernel_approximation(int i, int j, int size)
{
    static const float k3_values[] = {0.25f, 0.5f, 0.25f};
    static const float k5_values[] = {0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f};
    static const float k7_values[] = {0.03125f, 0.109375f, 0.21875f, 0.28125f, 0.21875f, 0.109375f, 0.03125f};

    // Trasladar del dominio [-(size-1)/2, (size-1)/2] a [0, size-1]
    i = (int)(i + ((float)size - 1.0)/2.0);
    j = (int)(j + ((float)size - 1.0)/2.0);

    //Retorna -1 si los argumenos son invalidos
    if ((i < 0) || (i >= size)) return -1.0;
    if ((j < 0) || (j >= size)) return -1.0;

    // Calcular items del kernel
    if (size == 3) {
        return k3_values[i] * k3_values[j];
    } else if (size == 5) {
        return k5_values[i] * k5_values[j];
    } else if (size == 7) {
        return k7_values[i] * k7_values[j];
    } else {
        //Retorna -1 si los argumenos son invalidos
        return -1.0;
    }
}
