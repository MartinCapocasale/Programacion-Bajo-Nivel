#include <stdio.h>

int main() {
    char nombre[100];
    int edad;

    // Solicitar al usuario que ingrese el nombre
    printf("Ingresa tu nombre: ");
    scanf("%s", nombre);

    // Solicitar al usuario que ingrese la edad
    printf("Ingresa tu edad: ");
    scanf("%d", &edad); // se usa & para indicar la dirección de memoria de la variable donde se almacenará el valor ingresado por el usuario 

    // Imprimir el nombre y la edad
    printf("Su nombre es: %s\n", nombre);
    printf("Su edad es: %d\n", edad);

    return 0;
}
