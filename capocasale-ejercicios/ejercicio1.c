#include <stdio.h>

int main(){
    char nombre[100];
    int edad;

    printf("Ingrese un nombre: ");
    scanf("%s" ,nombre);
  
    printf("Ingrese su edad: ");
    scanf("%d",&edad);
    
    printf("Su nombre es: %s \n", nombre);
    printf("Su edad es: %d",edad);

    return 0;
}
