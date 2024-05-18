#include <stdio.h>
#include <stdlib.h>


typedef struct lista {
    int info;
    struct lista *siguiente;
} Lista;

Lista *crear_lista(void){
    return NULL;
}

Lista *insertar_elemento_de_lista(Lista *l, int v){
    Lista *nuevo = (Lista *)malloc(sizeof(Lista));
    if (nuevo == NULL)
    {
        printf("Memória insuficiente");
        exit(1);
    }
    nuevo->info = v;
    nuevo->siguiente = l;
    return nuevo;
}

void imprimir_lista(Lista *l){
    Lista *p;
    for (p = l; p != NULL; p = p->siguiente)
    {
        printf(" Nodo = %d \n", p->info);
    }
}

int lista_es_vacia(Lista *l){
    return (l == NULL);
}

Lista *obtener_elemento_de_lista(int elemento, Lista *l)
{
    Lista *p;
    for (p = l; p != NULL; p = p->siguiente)
    {
        if (p->info == elemento)
            return p;
    }
    return NULL;
}

Lista *eliminar_elemento_de_lista(Lista *l, int v){
    Lista *ant = NULL;
    Lista *p = l;
    while (p->info != v)
    {
        if (p == NULL)
            return l;
        ant = p;
        p = p->siguiente;
    }
    if (ant == NULL)
        l = p->siguiente;
    else
        ant->siguiente = p->siguiente;
    free(p);
    return l;
}

int main() {
    Lista *lista = crear_lista(); 

    
    lista = insertar_elemento_de_lista(lista, 42);
    lista = insertar_elemento_de_lista(lista, 17);
    lista = insertar_elemento_de_lista(lista, 65);
    lista = insertar_elemento_de_lista(lista, 23);

    printf("Se insertan elementos en la lista:\n");
    imprimir_lista(lista);
	printf("\n");

    
    if (lista_es_vacia(lista)) {
        printf("La lista esta vacia.\n");
    } else {
        printf("La lista no esta vacia.\n");
    }
	printf("\n");

   
    Lista *resultadoBuscar = obtener_elemento_de_lista(65, lista);
    if (resultadoBuscar != NULL) {
        printf("Elemento %d encontrado en la lista.\n", resultadoBuscar->info);
    } else {
        printf("Elemento no encontrado en la lista.\n");
    }
	printf("\n");

    lista = eliminar_elemento_de_lista(lista, 17);
    printf("Se elimina elemento de la lista %d:\n", 17);
    imprimir_lista(lista);
	printf("\n");

    return 0; 
}

