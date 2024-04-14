#include <stdio.h>

int main(){
    int lista[] = {2,50,20,100,80,1};
    int min = lista[0];
    
    for (int i = 1; i < sizeof(lista) / sizeof(int); i++) {
        if (lista[i] < min) {
            min = lista[i];
        }
    }
    printf("El numero maximo en la lista es: %d", min);

    return 0;
}