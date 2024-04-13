#include <stdio.h>
#include <limits.h>

int encontrarMinimo(int arr[], int n) {
    int min = INT_MAX; 

    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    return min;
}

int main() {
    int numeros[] = {10, 5, 8, 3, 12}; 
    int tamano = sizeof(numeros) / sizeof(numeros[0]);

    int minimo = encontrarMinimo(numeros, tamano);

    printf("El número mínimo es: %d\n", minimo);

    return 0;
}
