#include <stdio.h>

int main() {
    char nombre[100];
    int edad;

    // Solicitar al usuario que ingrese el nombre
    printf("Ingresa tu nombre: ");
    scanf("%s", nombre);

    // Solicitar al usuario que ingrese la edad
    printf("Ingresa tu edad: ");
    scanf("%d", &edad);

    // Imprimir el nombre y la edad
    printf("Su nombre es: %s\n", nombre);
    printf("Su edad es: %d\n", edad);

    return 0;
}
