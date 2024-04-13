#include <stdio.h>

int main() {
    int n, i;
    int max = 0; //Supongo que todos los numeros son positivos

    //Solicito al usuario el número de elementos en la lista
    printf("Ingrese la cantidad de números: ");
    scanf("%d", &n);

    //Solicito al usuario los números y encontrar el máximo
    for (i = 0; i < n; i++) {
        int num;
        printf("Ingrese el número %d: ", i + 1);
        scanf("%d", &num);

        if (i == 0 || num > max) {
            max = num;
        }
    }

    printf("El número máximo es: %d\n", max);

    return 0;
}
