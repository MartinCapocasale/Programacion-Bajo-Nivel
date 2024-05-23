#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct estudiante {
    char nombre[50];
    char apellido[50];
    int edad;
    struct estudiante *siguiente;
} estudiante;

typedef struct materia {
    int codigo;
    char nombre[50];
    int cupo;
    struct materia *siguiente;
} materia;

typedef struct sistema {
    estudiante *estudiantes;
    materia *materias;
} sistema;

sistema *crear_sistema(void) {
    sistema *sistema = malloc(sizeof(sistema));
    sistema->estudiantes = NULL;
    sistema->materias = NULL;
    return sistema;
}

void agregar_estudiante(sistema *sistema, char *nombre,char *apellido, int edad) {
    estudiante *nuevo = malloc(sizeof(estudiante));
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->apellido, apellido);
    nuevo->edad = edad;
    nuevo->siguiente = sistema->estudiantes;
    sistema->estudiantes = nuevo;
}

void modificar_estudiante(sistema *sistema, char *nombre,char *apellido, int edad) {
    estudiante *actual = sistema->estudiantes;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0 && strcmp(actual->apellido, apellido) == 0) {
            actual->edad = edad;
            break;
        }
        actual = actual->siguiente;
    }
}

void eliminar_estudiante(sistema *sistema, char *nombre,char *apellido) {
    estudiante *actual = sistema->estudiantes;
    estudiante *anterior = NULL;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0 && strcmp(actual->apellido, apellido) == 0){
            if (anterior == NULL) {
                sistema->estudiantes = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}

void listar_estudiantes(sistema *sistema) {
    estudiante *actual = sistema->estudiantes;
    while (actual != NULL) {
        printf("%s,%s,%d\n", actual->nombre,actual->apellido, actual->edad);
        actual = actual->siguiente;
    }
}


int main() {
    sistema *sistema = crear_sistema();
    
    agregar_estudiante(sistema, "Martin", "Gomez", 20);
    agregar_estudiante(sistema, "Juan", "Perez", 22);
    agregar_estudiante(sistema, "Pedro", "Rodriguez", 19);
    
    printf("Lista de estudiantes:\n");
    listar_estudiantes(sistema);

    printf("\nModificando edad de Juan Perez a 18 anios:\n");
    modificar_estudiante(sistema, "Juan", "Perez", 18);
    listar_estudiantes(sistema);

    printf("\nEliminando a Juan Perez:\n");
    eliminar_estudiante(sistema, "Juan", "Perez");
    listar_estudiantes(sistema);

    return 0;
}
