#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int dato;
    struct Nodo *siguiente;
};

//Cabeza se refiere al puntero que apunta al primer nodo de la lista ya que es importante mantener un puntero que apunte al primer nodo, porque este puntero es esencial 
//para recorrer la lista, agregar nuevos nodos al inicio de la lista o eliminar nodos de la lista
void insertarAlInicio(struct Nodo **cabeza, int dato) {
    //Crear un nuevo nodo
    struct Nodo *nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo\n");
        exit(1);
    }

    //Asignar el dato al nuevo nodo
    nuevoNodo->dato = dato;

    //Enlazar el nuevo nodo al inicio de la lista
    nuevoNodo->siguiente = *cabeza;
    *cabeza = nuevoNodo;
}

void insertarAlFinal(struct Nodo **cabeza, int dato) {
    struct Nodo *nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo\n");
        exit(1);
    }
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;

    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
        return;
    }

    struct Nodo *ultimo = *cabeza;
    while (ultimo->siguiente != NULL) {
        ultimo = ultimo->siguiente;
    }
    ultimo->siguiente = nuevoNodo;
}

void insertarEnIndice(struct Nodo **cabeza, int dato, int indice) {
    if (indice < 0) {
        printf("Error: El índice debe ser mayor o igual a cero\n");
        return;
    }

    if (indice == 0) {
        insertarAlInicio(cabeza, dato);
        return;
    }

    struct Nodo *nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo\n");
        exit(1);
    }
    nuevoNodo->dato = dato;

    struct Nodo *temp = *cabeza;
    for (int i = 0; i < indice - 1 && temp != NULL; i++) {
        temp = temp->siguiente;
    }

    if (temp == NULL || temp->siguiente == NULL) {
        printf("Error: El índice está fuera de rango\n");
        free(nuevoNodo);
        return;
    }

    nuevoNodo->siguiente = temp->siguiente;
    temp->siguiente = nuevoNodo;
}

void eliminarEnIndice(struct Nodo **cabeza, int indice) {
    if (*cabeza == NULL) {
        printf("Error: La lista está vacía\n");
        return;
    }

    if (indice < 0) {
        printf("Error: El índice debe ser mayor o igual a cero\n");
        return;
    }

    struct Nodo *temp = *cabeza;

    //Si se elimina el primer nodo
    if (indice == 0) {
        *cabeza = temp->siguiente;
        free(temp);
        return;
    }

    //Buscar el nodo anterior al nodo a eliminar
    for (int i = 0; temp != NULL && i < indice - 1; i++) {
        temp = temp->siguiente;
    }

    //Si el índice está fuera de rango
    if (temp == NULL || temp->siguiente == NULL) {
        printf("Error: El índice está fuera de rango\n");
        return;
    }

    struct Nodo *nodoAEliminar = temp->siguiente;
    temp->siguiente = nodoAEliminar->siguiente;
    free(nodoAEliminar);
}

void imprimirLista(struct Nodo *actual) {
    printf("Lista enlazada: ");
    while (actual != NULL) {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

int obtenerLargoLista(struct Nodo *cabeza) {
    int contador = 0;
    struct Nodo *temp = cabeza;

    //Recorrer la lista contando los nodos
    while (temp != NULL) {
        contador++;
        temp = temp->siguiente;
    }

    return contador;
}

int obtenerElementoEnPosicion(struct Nodo *cabeza, int posicion) {
    if (posicion < 0) {
        printf("Error: La posición debe ser mayor o igual a cero\n");
        exit(1);
    }

    struct Nodo *temp = cabeza;
    int contador = 0;

    //Recorrer la lista hasta la posición deseada
    while (temp != NULL) {
        if (contador == posicion) {
            return temp->dato;
        }
        contador++;
        temp = temp->siguiente;
    }

    //Si la posición está fuera de rango
    printf("Error: La posición está fuera de rango\n");
    exit(1);
}

//Función para intercambiar los datos de dos nodos
void intercambiarDatos(struct Nodo *nodo1, struct Nodo *nodo2) {
    int temp = nodo1->dato;
    nodo1->dato = nodo2->dato;
    nodo2->dato = temp;
}

//Función para ordenar la lista enlazada de menor a mayor (algoritmo de selección)
void ordenarLista(struct Nodo *cabeza) {
    struct Nodo *temp1 = cabeza;
    while (temp1 != NULL) {
        struct Nodo *temp2 = temp1->siguiente;
        while (temp2 != NULL) {
            if (temp1->dato > temp2->dato) {
                intercambiarDatos(temp1, temp2);
            }
            temp2 = temp2->siguiente;
        }
        temp1 = temp1->siguiente;
    }
}

//Función para imprimir la lista enlazada ordenada de menor a mayor
void imprimirListaOrdenada(struct Nodo *cabeza) {
    ordenarLista(cabeza); //Ordenar la lista antes de imprimir
    imprimirLista(cabeza); //Llamar a la función existente para imprimir la lista
}

int main() {
    struct Nodo *cabeza = NULL; //Inicializamos la lista como vacía

    //Insertamos algunos nodos al inicio de la lista
    insertarAlInicio(&cabeza, 10);
    insertarAlInicio(&cabeza, 20);
    insertarAlInicio(&cabeza, 30);

    //Imprimimos la lista enlazada antes de eliminar en índice
    imprimirLista(cabeza);
    //Insertamos un nodo en un índice específico
    insertarEnIndice(&cabeza, 40, 1); //Insertamos el nodo 40 en el índice 1
    //Imprimimos la lista enlazada antes de eliminar en índice
    imprimirLista(cabeza);
    //Eliminanos el nodo en el índice 1
    eliminarEnIndice(&cabeza, 1);

    //Imprimimos la lista enlazada después de eliminar en índice
    imprimirLista(cabeza);
    //Obtenemos el largo de la lista
    int largo = obtenerLargoLista(cabeza);
    printf("Largo de la lista: %d\n", largo);
    int posicion = 2;
    int elemento = obtenerElementoEnPosicion(cabeza, posicion);
    printf("Elemento en la posición %d: %d\n", posicion, elemento);    
    //Imprimimos la lista enlazada ordenada de menor a mayor (modifica la original)
    printf("\nLista enlazada ordenada de menor a mayor:\n");
    imprimirListaOrdenada(cabeza);    
    return 0;
}
