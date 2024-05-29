#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct materias_alumno {
    int codigo_materia;
    struct materias_alumno *siguiente;
} materias_alumno;

typedef struct estudiante {
    char nombre[50];
    char apellido[50];
    int edad;
    materias_alumno *materias_alumno;
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
    nuevo->materias_alumno = NULL;
    nuevo->siguiente = sistema->estudiantes;
    sistema->estudiantes = nuevo;
}

void modificar_estudiante(sistema *sistema, char *nombre, char *apellido, char *nuevo_nombre, char *nuevo_apellido, int edad) {
    estudiante *actual = sistema->estudiantes;
    while (actual != NULL) {
        if (strcasecmp(actual->nombre, nombre) == 0 && strcasecmp(actual->apellido, apellido) == 0) {
            strcpy(actual->nombre, nuevo_nombre);
            strcpy(actual->apellido, nuevo_apellido);
            actual->edad = edad;
            printf("Modificacion exitosa: El Estudiante %s %s ahora se llama %s %s y tiene %d anios.\n", nombre, apellido, nuevo_nombre, nuevo_apellido, edad);
            return;
        }
        actual = actual->siguiente;
    }
    printf("Modificacion fallida: El Estudiante %s %s no fue encontrado.\n", nombre, apellido);
}

void listar_codigo_materias_cursadas(estudiante *estudiante) {
    materias_alumno *actual = estudiante->materias_alumno;
    while (actual != NULL) {
        printf("%s %s está cursando = %d\n", estudiante->nombre, estudiante->apellido, actual->codigo_materia);
        actual = actual->siguiente;
    }
}

void cursar_materia(sistema *sistema, char *nombre, char *apellido, int codigo_materia) {
    estudiante *actual = sistema->estudiantes;
    while (actual != NULL) {
        if (strcasecmp(actual->nombre, nombre) == 0 && strcasecmp(actual->apellido, apellido) == 0) {
            materias_alumno *nueva = malloc(sizeof(materias_alumno));
            nueva->codigo_materia = codigo_materia;
            nueva->siguiente = sistema->estudiantes->materias_alumno;
            sistema->estudiantes->materias_alumno = nueva;
            listar_codigo_materias_cursadas(actual);
            return;
        }
        actual = actual->siguiente;
    }
}

void eliminar_estudiante(sistema *sistema, char *nombre, char *apellido) {
    estudiante *actual = sistema->estudiantes;
    estudiante *anterior = NULL;
    while (actual != NULL) {
        if (strcasecmp(actual->nombre, nombre) == 0 && strcasecmp(actual->apellido, apellido) == 0) {
            if (anterior == NULL) {
                sistema->estudiantes = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
            printf("Eliminacion exitosa: El Estudiante %s %s fue eliminado.\n", nombre, apellido);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    printf("Eliminacion fallida: El Estudiante %s %s no fue encontrado.\n", nombre, apellido);
}


void listar_estudiantes(sistema *sistema) {
    estudiante *actual = sistema->estudiantes;
    while (actual != NULL) {
        printf("%s,%s,%d\n", actual->nombre,actual->apellido, actual->edad);
        actual = actual->siguiente;
    }
}

void listar_estudiantes_por_nombre(estudiante *estudiantes) {
    estudiante *actual = estudiantes;
    while (actual != NULL) {
        printf("%s,%s,%d\n", actual->nombre,actual->apellido, actual->edad);
        actual = actual->siguiente;
    }
}

estudiante estudiante_por_nombre(sistema *sistema, char *nombre){
    estudiante *actual = sistema->estudiantes;
    estudiante *lista = NULL;
    while (actual != NULL) {
        if (strcasecmp(actual->nombre, nombre) == 0) {
            estudiante *nuevo = malloc(sizeof(estudiante));
            strcpy(nuevo->nombre, actual->nombre);
            strcpy(nuevo->apellido, actual->apellido);
            nuevo->edad = actual->edad;
            nuevo->materias_alumno = actual->materias_alumno;
            nuevo->siguiente = lista;
            lista = nuevo;
        }
        actual = actual->siguiente;
    }
    listar_estudiantes_por_nombre(lista);
    return *lista;
}




void agregar_materia(sistema *sistema, char *nombre, int codigo, int cupo) {
    materia *nueva = malloc(sizeof(materia));
    strcpy(nueva->nombre, nombre);
    nueva->codigo = codigo;
    nueva->cupo = cupo;
    nueva->siguiente = sistema->materias;
    sistema->materias = nueva;
}

void listar_materias(sistema *sistema) {
    materia *actual = sistema->materias;
    while (actual != NULL) {
        printf("%s,%d,%d\n", actual->nombre, actual->codigo, actual->cupo);
        actual = actual->siguiente;
    }
}

void modificar_materia(sistema *sistema, char *nombre, char *nuevo_nombre, int nuevo_codigo, int nuevo_cupo) {
    materia *actual = sistema->materias;
    while (actual != NULL) {
        if (strcasecmp(actual->nombre, nombre) == 0) {
            strcpy(actual->nombre, nuevo_nombre);
            actual->codigo = nuevo_codigo;
            actual->cupo = nuevo_cupo;
            printf("Modificacion exitosa: La materia %s ahora se llama %s, tiene el codigo %d y el cupo %d.\n", nombre, nuevo_nombre, nuevo_codigo, nuevo_cupo);
            return;
        }
        actual = actual->siguiente;
    }
    printf("Modificacion fallida: La materia %s no fue encontrada.\n", nombre);
}

void eliminar_materia(sistema *sistema, char *nombre) {
    materia *actual = sistema->materias;
    materia *anterior = NULL;
    while (actual != NULL) {
        if (strcasecmp(actual->nombre, nombre) == 0) {
            if (anterior == NULL) {
                sistema->materias = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
            printf("Eliminacion exitosa: La Materia %s fue eliminada.\n", nombre);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    printf("Eliminacion fallida: La Materia %s no fue encontrada.\n", nombre);
}


int main() {
    sistema *sistema = crear_sistema();
    
    agregar_estudiante(sistema, "Jose", "Gomez", 20);
    agregar_estudiante(sistema, "Juan", "Perez", 22);
    agregar_estudiante(sistema, "Jose", "Rodriguez", 19);
    
    printf("Lista de estudiantes:\n");
    listar_estudiantes(sistema);

    printf("-------------------------------------------------------------\n");

    printf("\nModificando a Juan Perez por Pablo Perez y modificando la edad a 23 anios:\n");
    modificar_estudiante(sistema, "Juan", "Perez", "Pablo", "Perez", 23);
    listar_estudiantes(sistema);
    
    printf("\nIntentando modificar a Maria Gonzalez por Maria Lopez y modificando la edad a 21 anios:\n");
    modificar_estudiante(sistema, "Maria", "Gonzalez", "Maria", "Lopez", 21);
    listar_estudiantes(sistema);

    printf("-------------------------------------------------------------\n");

    printf("\nEliminando a Pablo Perez:\n");
    eliminar_estudiante(sistema, "Pablo", "Perez");

    printf("Lista de estudiantes:\n");
    listar_estudiantes(sistema);

    
    printf("\nIntentando eliminar a Maria Gonzalez:\n");
    eliminar_estudiante(sistema, "Maria", "Gonzalez");

    printf("Lista de estudiantes:\n");
    listar_estudiantes(sistema);

    printf("-------------------------------------------------------------\n");

    printf("\nProbar minusculas:\n");
    printf("\nIntentando eliminar a martin gomez:\n");
    eliminar_estudiante(sistema, "martin", "Gomez");

    printf("Lista de estudiantes:\n");
    listar_estudiantes(sistema);

    printf("-------------------------------------------------------------\n");

    printf("\nProbar Agregar materias:\n");
    agregar_materia(sistema, "Matematica", 1001, 30);
    agregar_materia(sistema, "Historia", 1002, 25);
    agregar_materia(sistema, "Geografia", 1003, 20);
    
    printf("Lista de materias:\n");
    listar_materias(sistema);

    printf("-------------------------------------------------------------\n"); 

    printf("\nModificando materia Historia por Quimica con nuevo codigo 2002 y cupo 35:\n");
    modificar_materia(sistema, "Historia", "Quimica", 2002, 35);
    listar_materias(sistema);

    printf("\nIntentando modificar materia Dibujo:\n");
    modificar_materia(sistema, "Dibujo", "Dibujo Tecnico", 2999, 15);
    listar_materias(sistema);

    printf("\nProbar minusculas:\n");
    printf("\nModificando materia geografia por Historia con nuevo codigo 2002 y cupo 35:\n");
    modificar_materia(sistema, "geografia", "Historia", 1002, 15);
    listar_materias(sistema);

    printf("-------------------------------------------------------------\n"); 

    printf("\nEliminando materia Historia:\n");
    eliminar_materia(sistema, "Historia");
    listar_materias(sistema);

    printf("\nIntentando eliminar materia Dibujo:\n");
    eliminar_materia(sistema, "Dibujo");
    listar_materias(sistema);

    estudiante_por_nombre(sistema, "Jose");
    cursar_materia(sistema, "Jose", "Rodriguez", 2022);
    cursar_materia(sistema, "Jose", "Rodriguez", 2028);
    cursar_materia(sistema, "Jose", "Rodriguez", 2032);

    return 0;
}
