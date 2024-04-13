#include <stdio.h>
#include <limits.h>


int main() {
    int numeros[] = {10, 5, 8, 3, 12}; 
    int tamano = sizeof(numeros) / sizeof(numeros[0]);

    int minimo = INT_MAX; 

   
    for (int i = 0; i < tamano; i++) {
        if (numeros[i] < minimo) {
            minimo = numeros[i];
        }
    }

    printf("El número mínimo es: %d\n", minimo);

    return 0;
}
