#include <stdio.h>

int main(){
    int num1, num2, num3;
    float promedio;
    
    printf("Ingrese el numero1: ");
    scanf("%d", &num1);
    printf("Ingrese el numero2: ");
    scanf("%d", &num2);
    printf("Ingrese el numero3: ");
    scanf("%d", &num3);

    promedio = (num1 + num2 + num3) / 3 ;

    printf("El promedio de los 3 numeros es: %.2f ", promedio);
    
    return 0;
}