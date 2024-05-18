#include <stdio.h>
#include <malloc.h>

typedef struct structNodo {
    int valor;
    struct structNodo *proximo;
} Nodo;

Nodo *buscarPorIndice(Nodo *lista, int indice);

Nodo *agregar(Nodo *lista, int valor, int indice) {
    Nodo *nuevoNodo = malloc(sizeof (Nodo));
    nuevoNodo->valor = valor;
    nuevoNodo->proximo =NULL;
    Nodo *cursor = lista;
    if (indice == 0) {
        if (lista == NULL) {
            lista = nuevoNodo;
        } else {
            nuevoNodo->proximo = lista;
            return nuevoNodo;
        }
    }
    Nodo *nodoAnterior = buscarPorIndice(lista, indice-1);
    Nodo *nodoActual = buscarPorIndice(lista, indice);
    if ( nodoAnterior != NULL){
        nodoAnterior->proximo = nuevoNodo;
    } else {
        return lista;
    }
    if(nodoActual == NULL){
        nuevoNodo->proximo = NULL;
    } else {
        nuevoNodo->proximo = nodoActual;
    }

    return lista;
}

Nodo *borrarElemento(Nodo *lista, int indice) {
    Nodo *nodoAnterior = buscarPorIndice(lista, indice-1);
    Nodo *nodoActual = buscarPorIndice(lista, indice);
    Nodo *nodoSiguiente = buscarPorIndice(lista, indice+1);
    if(nodoActual == NULL){
        return NULL;
    }
    if(nodoSiguiente == NULL){
        nodoAnterior->proximo = NULL;
    }
    nodoAnterior->proximo = nodoSiguiente;
    free(nodoActual);

    return lista;
}

Nodo *agregarAlFinal(Nodo *lista, int valor) {
    Nodo *nuevoNodo = malloc(sizeof (Nodo));
    nuevoNodo->valor = valor;
    nuevoNodo->proximo =NULL;
    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        Nodo *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
        cursor->proximo = nuevoNodo;
    }
    return lista;
}

Nodo *buscarPorIndice(Nodo *lista, int indice) {
    if (lista == NULL){
        return NULL;
    }
    Nodo *cursor = lista;
    int i = 0;
    while (i < indice && cursor->proximo != NULL) {
        cursor = cursor->proximo;
        i++;
    }
    if(i != indice){
        return NULL;
    }
    return cursor;
}

void imprimirLista(Nodo *lista) {
    if (lista == NULL){
        printf("La lista se escuentra vacía");;
    }
    Nodo *cursor = lista;
    printf("\n{%d", cursor->valor);
    while (cursor->proximo != NULL) {
        cursor = cursor->proximo;
        printf(", %d", cursor->valor);
    }
    printf("}\n");
}



int main(void) {
    Nodo *lista = NULL;

    lista = agregarAlFinal(lista,1);
    lista = agregarAlFinal(lista,2);
    lista = agregarAlFinal(lista,3);
    lista = agregarAlFinal(lista,4);
    lista = agregarAlFinal(lista,5);
    //lista = borrarElemento(lista,2);

    printf("%d\n", lista->valor);
    printf("%d\n", lista->proximo->valor);
    printf("%d\n", lista->proximo->proximo->valor);
    printf("%d\n", lista->proximo->proximo->proximo->valor);
    printf("%d\n", lista->proximo->proximo->proximo->proximo->valor);
    imprimirLista(lista);

    //printf("%d\n", buscarPorIndice(lista, 1)->valor);


}