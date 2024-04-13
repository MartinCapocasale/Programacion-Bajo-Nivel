#include <stdio.h>

int maximo(int numeros[], int size);
int minimo(int numeros[], int size);


int main() {
    int numeros[] = {4, 3, 2, 8, 80, 5, 20, 6, 30, 5};
    int size = sizeof(numeros)/sizeof(numeros[0]);
    int numeroMaximo = maximo(numeros, size);
    int numeroMinimo = minimo(numeros, size);
    printf("El máximo número del array es: %d", numeroMaximo);
    printf("\n El mínimo número del array es: %d", numeroMinimo);
    return 0;
}

int maximo(int numeros[], int size){
    int maximo = numeros [0];
    for (int i = 1; i < size; i++) {
        if (numeros[i] > maximo) {
            maximo = numeros [i];
        }
    }
    return maximo;
}

int minimo(int numeros[], int size){
    int minimo = numeros [0];
    for (int i = 1; i < size; i++) {
        if (numeros[i] < minimo) {
            minimo = numeros[i];
        }
    }
    return minimo;
}