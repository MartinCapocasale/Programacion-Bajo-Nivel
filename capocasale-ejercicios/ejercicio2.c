#include <stdio.h>

int main(){
    int lista[] = {2,50,20,100,80,1};
    int max = lista[0];
    
    for (int i = 1; i < sizeof(lista) / sizeof(int); i++) {
        if (lista[i] > max) {
            max = lista[i];
        }
    }
    printf("El numero maximo en la lista es: %d", max);

    return 0;
}