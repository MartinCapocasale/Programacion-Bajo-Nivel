#include <stdio.h>

int main(){
    int numeros[3];
    float promedio = 0;
    printf("Ingrese 3 enteros separados por coma: ");
    scanf("%d,%d,%d", &numeros[0], &numeros[1], &numeros[2]);
    printf("numero 1: %d, numero 2: %d, numero 3: %d", numeros[0],numeros[1], numeros[2]);

    for (int i = 0; i < 3; i++) {
        promedio += numeros[i];
    }
    promedio = promedio/(sizeof(numeros)/sizeof(numeros[0]));
    printf("\n El promedio es: %f", promedio);
    return 0;
}