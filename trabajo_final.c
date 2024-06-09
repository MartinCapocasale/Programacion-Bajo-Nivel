#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

typedef struct materias_alumno {
    int codigo_materia;
    struct materias_alumno *siguiente;
} materias_alumno;

typedef struct materias_aprobadas {
    int codigo_materia;
    int nota_materia;
    struct materias_aprobadas *siguiente;
} materias_aprobadas;

typedef struct materias_correlativas {
    int codigo_materia;
    struct materias_correlativas *siguiente;
} materias_correlativas;

typedef struct estudiante {
    char nombre[50];
    char apellido[50];
    int edad;
    int legajo;
    materias_alumno *materias_alumno;
    materias_aprobadas *materias_aprobadas;
    struct estudiante *siguiente;
} estudiante;

typedef struct materia {
    int codigo;
    char nombre[50];
    int cupo;
    materias_correlativas *materias_correlativas;
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

int verificar_mayor_legajo(sistema *sistema){
    estudiante *actual = sistema->estudiantes;
    int legajo = 1000;
    while (actual != NULL) {
        if (legajo < actual->legajo) {
            legajo = actual->legajo;
        }
        actual = actual->siguiente;
    }
    return legajo + 1;
}

void agregar_estudiante(sistema *sistema, char *nombre,char *apellido, int edad) {
    estudiante *nuevo = malloc(sizeof(estudiante));
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->apellido, apellido);
    nuevo->edad = edad;
    nuevo->legajo = verificar_mayor_legajo(sistema);
    nuevo->materias_alumno = NULL;
    nuevo->materias_aprobadas = NULL;
    nuevo->siguiente = sistema->estudiantes;
    sistema->estudiantes = nuevo;
    printf("Se creo el Estudiante %s %s con %d anios y legajo número %d.\n", nuevo->nombre, nuevo->apellido, nuevo->edad, nuevo->legajo);
}

void modificar_estudiante(sistema *sistema, int legajo, char *nuevo_nombre, char *nuevo_apellido, int edad) {
    estudiante *actual = sistema->estudiantes;
    while (actual != NULL) {
        if (legajo == actual->legajo) {
            strcpy(actual->nombre, nuevo_nombre);
            strcpy(actual->apellido, nuevo_apellido);
            actual->edad = edad;
            printf("Modificacion exitosa: El Estudiante con el legajo número %d ahora se llama %s %s y tiene %d anios.\n", legajo, nuevo_nombre, nuevo_apellido, edad);
            return;
        }
        actual = actual->siguiente;
    }
    printf("Modificacion fallida: El Estudiante con legajo número %d no fue encontrado.\n", legajo);
}

materia *materia_por_codigo (sistema *sistema, int codigo_materia){
    materia *actual = sistema->materias;
    while (actual != NULL){
        if (actual->codigo == codigo_materia){
            return actual;
        }
        actual = actual->siguiente;
    }
    return actual;
}

estudiante *estudiante_por_nombre_apellido(sistema *sistema, char *nombre, char *apellido) {
    estudiante *actual = sistema->estudiantes;
    while (actual != NULL) {
        if (strcasecmp(actual->nombre, nombre) == 0 && strcasecmp(actual->apellido, apellido) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return actual;
}

materias_alumno *materias_cursada(estudiante *estudiantes, int codigo_materia) {
    materias_alumno *actual = estudiantes->materias_alumno;
    while (actual != NULL) {
        if (actual->codigo_materia == codigo_materia) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return actual;
}

materias_aprobadas *materias_aprobada(estudiante *estudiantes, int codigo_materia) {
    materias_aprobadas *actual = estudiantes->materias_aprobadas;
    while (actual != NULL) {
        if (actual->codigo_materia == codigo_materia) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return actual;
}

void listar_materias_cursadas(estudiante *estudiante, sistema *sistema) {
    materias_alumno *actual = estudiante->materias_alumno;
    while (actual != NULL) {
        materia *materia_actual = materia_por_codigo (sistema, actual->codigo_materia);
        printf("%s %s está cursando la materia %s con el código %d\n", estudiante->nombre, estudiante->apellido, materia_actual->nombre, actual->codigo_materia);
        actual = actual->siguiente;
    }
}

void listar_materias_aprobadas(estudiante *estudiante, sistema *sistema) {
    materias_aprobadas *actual = estudiante->materias_aprobadas;
    while (actual != NULL) {
        materia *materia_actual = materia_por_codigo (sistema, actual->codigo_materia);
        printf("%s %s tiene aprobada la materia %s con una nota de %d\n", estudiante->nombre, estudiante->apellido, materia_actual->nombre, actual->nota_materia);
        actual = actual->siguiente;
    }
}

void calcular_promedio_estudiante(estudiante *estudiante) {
    materias_aprobadas *actual = estudiante->materias_aprobadas;
    float promedio = 0;
    int cantidad_materias = 0;
    while (actual != NULL) {
        promedio += actual->nota_materia;
        cantidad_materias += 1;
        actual = actual->siguiente;
    }
    promedio = promedio / cantidad_materias;
    printf("El estudiante %s %s tiene un promedio de %0.1f\n", estudiante->nombre, estudiante->apellido, promedio);
}

bool verificar_cumplir_correlativas (sistema *sistema, estudiante *estudiante, materia *materia){
    materias_correlativas *actual = materia->materias_correlativas;
    while (actual != NULL) {
        if (materias_aprobada(estudiante, actual->codigo_materia) == NULL) {
            printf("La materia correlativa %s no se encuentra aprobada para poder cursar %s.\n", materia_por_codigo(sistema, actual->codigo_materia)->nombre,materia->nombre);
            return false;
        }
        actual = actual->siguiente;
    }
    return true;
}

void cursar_materia(sistema *sistema, int legajo, int codigo_materia) {
    estudiante *actual = sistema->estudiantes;
    while (actual != NULL) {
        if (legajo == actual->legajo) {
            if(materia_por_codigo(sistema, codigo_materia) == NULL){
                printf("La materia con el código %d no existe.\n", codigo_materia);
                return;
            }
            materias_alumno *materia_alumno_a_cursar = materias_cursada(actual, codigo_materia);
            materias_aprobadas *materia_alumno_a_cursar_aprobada = materias_aprobada(actual, codigo_materia);
            materia *materia_a_cursar = materia_por_codigo (sistema, codigo_materia);
            if (materia_alumno_a_cursar != NULL){
                printf("El estudiante %s %s ya se encuentra cursando la materia %s con el código %d\n", actual->nombre, actual->apellido, materia_a_cursar->nombre, materia_alumno_a_cursar->codigo_materia);
                return;
            }
            if (materia_alumno_a_cursar_aprobada != NULL){
                printf("El estudiante %s %s ya tiene la materia %s aprobada con una nota de %d\n", actual->nombre, actual->apellido, materia_a_cursar->nombre, materia_alumno_a_cursar_aprobada->nota_materia);
                return;
            }
            if (!verificar_cumplir_correlativas (sistema, actual, materia_a_cursar)){
                return;
            }
            if (materia_a_cursar->cupo == 0){
                printf("La materia con %s no tiene cupos disponibles.\n", materia_a_cursar->nombre);
                return;
            }
            materias_alumno *nueva = malloc(sizeof(materias_alumno));
            nueva->codigo_materia = codigo_materia;
            nueva->siguiente = sistema->estudiantes->materias_alumno;
            sistema->estudiantes->materias_alumno = nueva;
            materia_a_cursar->cupo -= 1;
            printf("La materia %s quedo con un cupo de %d\n", materia_a_cursar->nombre, materia_a_cursar->cupo);
            printf("El estudiante %s %s se ha anotado correctamente a la materia %s con el código %d\n", actual->nombre, actual->apellido, materia_a_cursar->nombre, nueva->codigo_materia);
            return;
        }
        actual = actual->siguiente;
    }
}

void eliminar_materia_cursada(sistema *sistema, estudiante *estudiante, int codigo_materia) {
    materias_alumno *actual = estudiante->materias_alumno;
    materias_alumno *anterior = NULL;
    while (actual != NULL) {
        if (actual->codigo_materia == codigo_materia) {
            materia *materia = materia_por_codigo (sistema, codigo_materia);
            if (anterior == NULL) {
                estudiante->materias_alumno = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            materia->cupo += 1;
            free(actual);
            printf("Eliminacion exitosa: El alumno %s %s dejo de cursar la materia %s.\n", estudiante->nombre, estudiante->apellido, materia->nombre);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    printf("Eliminacion fallida: El alumno %s %s no se encontraba cursando la materia %s.\n", estudiante->nombre, estudiante->apellido, materia_por_codigo (sistema, codigo_materia)->nombre);
}

void aprobar_materia_cursada_estudiante(sistema *sistema, int legajo, int codigo_materia, int nota_materia){
    estudiante *estudiante_actual = sistema->estudiantes;
    while (estudiante_actual != NULL) {
        if (legajo == estudiante_actual->legajo) {
            if(materia_por_codigo(sistema, codigo_materia) == NULL){
                printf("La materia con el código %d no existe.\n", codigo_materia);
                return;
            }

            materias_alumno *materia_alumno_a_cursar = materias_cursada(estudiante_actual, codigo_materia);
            materia *materia = materia_por_codigo (sistema, codigo_materia);
            if (materia_alumno_a_cursar == NULL){
                printf("El estudiante %s %s no se encuentra anotado en la materia %s con el código %d\n", estudiante_actual->nombre, estudiante_actual->apellido, materia->nombre, materia->codigo);
                return;
            }

            eliminar_materia_cursada(sistema, estudiante_actual, codigo_materia);
            if (nota_materia < 4){
                printf("El estudiante %s %s ha desaprobado la materia %s.\n", estudiante_actual->nombre, estudiante_actual->apellido, materia->nombre);
                return;
            }
            materias_aprobadas *nueva = malloc(sizeof(materias_aprobadas));
            nueva->codigo_materia = codigo_materia;
            nueva->nota_materia = nota_materia;
            nueva->siguiente = sistema->estudiantes->materias_aprobadas;
            sistema->estudiantes->materias_aprobadas = nueva;
            printf("El estudiante %s %s ha aprobado la materia %s con una nota de %d\n", estudiante_actual->nombre, estudiante_actual->apellido, materia->nombre, nueva->nota_materia);
            return;

        }
        estudiante_actual = estudiante_actual->siguiente;
    }
}

void eliminar_estudiante(sistema *sistema, int legajo) {
    estudiante *actual = sistema->estudiantes;
    estudiante *anterior = NULL;
    while (actual != NULL) {
        if (legajo == actual->legajo) {
            if (anterior == NULL) {
                sistema->estudiantes = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
            printf("Eliminacion exitosa: El Estudiante con el legajo número %d fue eliminado.\n", legajo);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    printf("Eliminacion fallida: El Estudiante con el legajo %d no fue encontrado.\n", legajo);
}


void listar_estudiantes(sistema *sistema) {
    estudiante *actual = sistema->estudiantes;
    while (actual != NULL) {
        printf("%s,%s,%d,%d\n", actual->nombre,actual->apellido, actual->edad, actual->legajo);
        actual = actual->siguiente;
    }
}

void listar_estudiantes_por_nombre(estudiante *estudiantes) {
    estudiante *actual = estudiantes;
    while (actual != NULL) {
        printf("%s,%s,%d,%d\n", actual->nombre,actual->apellido, actual->edad, actual->legajo);
        actual = actual->siguiente;
    }
}

void listar_estudiantes_filtrados_por_nombre(sistema *sistema, char *nombre){
    estudiante *actual = sistema->estudiantes;
    estudiante *lista = NULL;
    while (actual != NULL) {
        if (strcasecmp(actual->nombre, nombre) == 0) {
            printf("%s,%s,%d,%d\n", actual->nombre,actual->apellido, actual->edad, actual->legajo);
        }
        actual = actual->siguiente;
    }
}

int verificar_mayor_codigo_materia(sistema *sistema){
    materia *actual = sistema->materias;
    int codigo = 100;
    while (actual != NULL) {
        if (codigo < actual->codigo) {
            codigo = actual->codigo;
        }
        actual = actual->siguiente;
    }
    return codigo + 1;
}

void agregar_materia(sistema *sistema, char *nombre, int cupo) {
    materia *nueva = malloc(sizeof(materia));
    strcpy(nueva->nombre, nombre);
    nueva->codigo = verificar_mayor_codigo_materia(sistema);
    nueva->cupo = cupo;
    nueva->materias_correlativas = NULL;
    nueva->siguiente = sistema->materias;
    sistema->materias = nueva;
}

/*materia obtener_materia_por_codigo(sistema *sistema) {
    materia *actual = sistema->materias;
    while (actual != NULL) {
        printf("%s,%d,%d\n", actual->nombre, actual->codigo, actual->cupo);
        actual = actual->siguiente;
    }
}*/

void agregar_materia_correlativa(sistema *sistema, int codigo_materia_actual, int codigo_materia_correlativa) {
    materia *materia_actual = materia_por_codigo (sistema, codigo_materia_actual);
    if (materia_actual == NULL){
        printf("La materia con el código %d no exite.\n", codigo_materia_actual);
        return;
    }
    materia *materia_correlativa = materia_por_codigo (sistema, codigo_materia_correlativa);
    if (materia_correlativa == NULL){
        printf("La materia correlativa con el código %d no exite.\n", codigo_materia_correlativa);
        return;
    }
    materias_correlativas *nueva = malloc(sizeof(materias_correlativas));
    nueva->codigo_materia = codigo_materia_correlativa;
    nueva->siguiente = sistema->materias->materias_correlativas;
    sistema->materias->materias_correlativas = nueva;
    printf("Se ha agregado a la materia %s como correlativa de %s.\n", materia_correlativa->nombre, materia_actual->nombre);
}

void listar_materias(sistema *sistema) {
    materia *actual = sistema->materias;
    while (actual != NULL) {
        printf("%s,%d,%d\n", actual->nombre, actual->codigo, actual->cupo);
        actual = actual->siguiente;
    }
}

void modificar_materia(sistema *sistema, int codigo, char *nuevo_nombre, int nuevo_cupo) {
    materia *actual = sistema->materias;
    while (actual != NULL) {
        if (codigo == actual->codigo) {
            strcpy(actual->nombre, nuevo_nombre);
            actual->cupo = nuevo_cupo;
            printf("Modificacion exitosa: La materia con el código %d ahora se llama %s y tiene el cupo %d.\n", codigo, nuevo_nombre, codigo, nuevo_cupo);
            return;
        }
        actual = actual->siguiente;
    }
    printf("Modificacion fallida: La materia con el código %d no fue encontrada.\n", codigo);
}

void eliminar_materia(sistema *sistema, int codigo) {
    materia *actual = sistema->materias;
    materia *anterior = NULL;
    while (actual != NULL) {
        if (codigo == actual->codigo) {
            if (anterior == NULL) {
                sistema->materias = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
            printf("Eliminacion exitosa: La Materia con el código %d fue eliminada.\n", codigo);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    printf("Eliminacion fallida: La Materia con el código %d no fue encontrada.\n", codigo);
}

void buscar_estudiantes_por_rango_edad(sistema *sistema, int edad_min, int edad_max) {
    estudiante *actual = sistema->estudiantes;
    printf("Estudiantes en el rango de edad %d - %d:\n", edad_min, edad_max);
    while (actual != NULL) {
        if (actual->edad >= edad_min && actual->edad <= edad_max) {
            printf("%s, %s, %d\n", actual->nombre, actual->apellido, actual->edad);
        }
        actual = actual->siguiente;
    }
}

void liberar_memoria_estudiantes(estudiante *estudiantes) {
    while (estudiantes != NULL) {
        estudiante *temp = estudiantes;
        estudiantes = estudiantes->siguiente;
        while (temp->materias_alumno != NULL) {
            materias_alumno *temp_mat = temp->materias_alumno;
            temp->materias_alumno = temp->materias_alumno->siguiente;
            free(temp_mat);
        }
        free(temp);
    }
}

void liberar_memoria_materias(materia *materias) {
    while (materias != NULL) {
        materia *temp = materias;
        materias = materias->siguiente;
        free(temp);
    }
}

void calcular_estadisticas_materias_cursadas_actualmente(sistema *sistema) {
    materia *actual_materia = sistema->materias;
    int total_materias = 0;
    int total_estudiantes = 0;
    int *materias_cursadas = NULL;

    //Contamos el número total de materias y estudiantes
    while (actual_materia != NULL) {
        total_materias++;
        actual_materia = actual_materia->siguiente;
    }

    estudiante *actual_estudiante = sistema->estudiantes;
    while (actual_estudiante != NULL) {
        total_estudiantes++;
        actual_estudiante = actual_estudiante->siguiente;
    }

    //Reservamos memoria para el contador de materias cursadas
    materias_cursadas = malloc(total_materias * sizeof(int));
    for (int i = 0; i < total_materias; i++) {
        materias_cursadas[i] = 0;
    }

    //Contamos cuántos estudiantes cursan cada materia
    actual_estudiante = sistema->estudiantes;
    while (actual_estudiante != NULL) {
        materias_alumno *materia_alumno = actual_estudiante->materias_alumno;
        while (materia_alumno != NULL) {
            int codigo = materia_alumno->codigo_materia;
            materia *materia_actual = sistema->materias;
            int index = 0;
            while (materia_actual != NULL) {
                if (materia_actual->codigo == codigo) {
                    materias_cursadas[index]++;
                    break;
                }
                materia_actual = materia_actual->siguiente;
                index++;
            }
            materia_alumno = materia_alumno->siguiente;
        }
        actual_estudiante = actual_estudiante->siguiente;
    }

    //Imprimimos las estadísticas
    actual_materia = sistema->materias;
    int index = 0;
    while (actual_materia != NULL) {
        float porcentaje = ((float) materias_cursadas[index] / total_estudiantes) * 100;
        printf("Materia: %s (Código: %d) es cursada por %d estudiantes actualmente(%0.2f%%)\n", actual_materia->nombre, actual_materia->codigo, materias_cursadas[index], porcentaje);
        actual_materia = actual_materia->siguiente;
        index++;
    }

    free(materias_cursadas);
}

void calcular_estadisticas_materias_aprobadas(sistema *sistema) {
    materia *actual_materia = sistema->materias;
    int total_materias = 0;
    int total_estudiantes = 0;
    int *materias_aprobadass = NULL;

    //Contamos el número total de materias y estudiantes
    while (actual_materia != NULL) {
        total_materias++;
        actual_materia = actual_materia->siguiente;
    }

    estudiante *actual_estudiante = sistema->estudiantes;
    while (actual_estudiante != NULL) {
        total_estudiantes++;
        actual_estudiante = actual_estudiante->siguiente;
    }

    //Reservamos memoria para el contador de materias aprobadas
    materias_aprobadass = malloc(total_materias * sizeof(int));
    for (int i = 0; i < total_materias; i++) {
        materias_aprobadass[i] = 0;
    }

    //Contamos cuántos estudiantes han aprobado cada materia
    actual_estudiante = sistema->estudiantes;
    while (actual_estudiante != NULL) {
        materias_aprobadas *materia_aprobada_alumno = actual_estudiante->materias_aprobadas;
        while (materia_aprobada_alumno != NULL) {
            int codigo = materia_aprobada_alumno->codigo_materia;
            materia *materia_actual = sistema->materias;
            int index = 0;
            while (materia_actual != NULL) {
                if (materia_actual->codigo == codigo) {
                    materias_aprobadass[index]++;
                    break;
                }
                materia_actual = materia_actual->siguiente;
                index++;
            }
            materia_aprobada_alumno = materia_aprobada_alumno->siguiente;
        }
        actual_estudiante = actual_estudiante->siguiente;
    }

    //Imprimimos las estadísticas
    actual_materia = sistema->materias;
    int index = 0;
    while (actual_materia != NULL) {
        float porcentaje = ((float) materias_aprobadass[index] / total_estudiantes) * 100;
        printf("Materia: %s (Código: %d) ha sido aprobada por %d estudiantes (%0.2f%%)\n", actual_materia->nombre, actual_materia->codigo, materias_aprobadass[index], porcentaje);
        actual_materia = actual_materia->siguiente;
        index++;
    }

    free(materias_aprobadass);
}

/*void exportar_estudiantes_a_archivo(sistema *sistema, const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    estudiante *actual = sistema->estudiantes;
    while (actual != NULL) {
        fprintf(archivo, "%s,%s,%d\n", actual->nombre, actual->apellido, actual->edad);
        actual = actual->siguiente;
    }

    fclose(archivo);
}

void exportar_materias_a_archivo(sistema *sistema, const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    materia *actual = sistema->materias;
    while (actual != NULL) {
        fprintf(archivo, "%s,%d,%d\n", actual->nombre, actual->codigo, actual->cupo);
        actual = actual->siguiente;
    }

    fclose(archivo);
}

void leer_estudiantes_de_archivo(sistema *sistema, const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para leer.\n");
        return;
    }

    char nombre[50], apellido[50];
    int edad;
    while (fscanf(archivo, "%49[^,],%49[^,],%d\n", nombre, apellido, &edad) != EOF) {
        agregar_estudiante(sistema, nombre, apellido, edad);
    }

    fclose(archivo);
}

void leer_materias_de_archivo(sistema *sistema, const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para leer.\n");
        return;
    }

    char nombre[50];
    int codigo, cupo;
    while (fscanf(archivo, "%49[^,],%d,%d\n", nombre, &codigo, &cupo) != EOF) {
        agregar_materia(sistema, nombre, codigo, cupo);
    }

    fclose(archivo);
}*/

int main() {
    sistema *sistema = crear_sistema();
    
    agregar_estudiante(sistema, "Jose", "Gomez", 20);
    agregar_estudiante(sistema, "Juan", "Perez", 22);
    agregar_estudiante(sistema, "Jose", "Rodriguez", 19);
    
    printf("Lista de estudiantes:\n");
    listar_estudiantes(sistema);

    printf("-------------------------------------------------------------\n");

    printf("\nModificando a Juan Perez por Pablo Perez y modificando la edad a 23 anios:\n");
    modificar_estudiante(sistema, 1002, "Pablo", "Perez", 23);
    listar_estudiantes(sistema);
    
    printf("\nIntentando modificar a Maria Gonzalez por Maria Lopez y modificando la edad a 21 anios:\n");
    modificar_estudiante(sistema, 1020, "Maria", "Lopez", 21);
    listar_estudiantes(sistema);

    printf("-------------------------------------------------------------\n");

    printf("\nEliminando a Pablo Perez:\n");
    eliminar_estudiante(sistema, 1002);

    printf("Lista de estudiantes:\n");
    listar_estudiantes(sistema);

    
    printf("\nIntentando eliminar a Maria Gonzalez:\n");
    eliminar_estudiante(sistema, 1020);

    printf("Lista de estudiantes:\n");
    listar_estudiantes(sistema);

    printf("-------------------------------------------------------------\n");

    printf("\nProbar minusculas:\n");
    printf("\nIntentando eliminar a martin gomez:\n");
    eliminar_estudiante(sistema, 1050);

    printf("Lista de estudiantes:\n");
    listar_estudiantes(sistema);

    printf("-------------------------------------------------------------\n");

    printf("\nProbar Agregar materias:\n");
    agregar_materia(sistema, "Matematica", 100);
    agregar_materia(sistema, "Historia", 20);
    agregar_materia(sistema, "Geografia", 50);
    
    printf("Lista de materias:\n");
    listar_materias(sistema);

    printf("-------------------------------------------------------------\n"); 

    printf("\nModificando materia Historia por Quimica con nuevo codigo 2002 y cupo 35:\n");
    modificar_materia(sistema, 102, "Quimica", 35);
    listar_materias(sistema);

    printf("\nIntentando modificar materia Dibujo:\n");
    modificar_materia(sistema, 154, "Dibujo Tecnico", 15);
    listar_materias(sistema);

    printf("\nProbar minusculas:\n");
    printf("\nModificando materia geografia por Historia con nuevo codigo 2002 y cupo 35:\n");
    modificar_materia(sistema, 103, "Historia", 15);
    listar_materias(sistema);

    printf("-------------------------------------------------------------\n"); 

    printf("\nEliminando materia Historia:\n");
    eliminar_materia(sistema, 103);
    listar_materias(sistema);

    printf("\nIntentando eliminar materia Dibujo:\n");
    eliminar_materia(sistema, 180);
    listar_materias(sistema);

    listar_estudiantes_filtrados_por_nombre(sistema, "Jose");
    cursar_materia(sistema, 1003, 101);
    cursar_materia(sistema, 1003, 102);


    cursar_materia(sistema,1003, 107);
    estudiante *estudiante_en_cuestion = estudiante_por_nombre_apellido(sistema, "Jose", "Rodriguez");
    listar_materias_aprobadas(estudiante_en_cuestion, sistema);
    aprobar_materia_cursada_estudiante(sistema, 1003, 101, 9);
    aprobar_materia_cursada_estudiante(sistema, 1003, 102, 5);
    //eliminar_materia_cursada(sistema, estudiante_en_cuestion, 2002);
    listar_materias_cursadas(estudiante_en_cuestion, sistema);
    listar_materias_aprobadas(estudiante_en_cuestion, sistema);

    agregar_materia_correlativa(sistema, 101, 103);
    cursar_materia(sistema, 1003, 102);
    calcular_promedio_estudiante(estudiante_en_cuestion);

    printf("-------------------------------------------------------------\n");

    printf("\nBuscando estudiantes por rango de edad 20 - 22:\n");
    buscar_estudiantes_por_rango_edad(sistema, 20, 22);
    cursar_materia(sistema, 1050, 101);
    agregar_estudiante(sistema, "Jaime", "Perez", 23);
    cursar_materia(sistema, 1004, 101);
    calcular_estadisticas_materias_cursadas_actualmente(sistema);
    calcular_estadisticas_materias_aprobadas(sistema);
    //exportar_estudiantes_a_archivo(sistema,"estudiantes.csv");
    //exportar_materias_a_archivo(sistema,"materias.csv");
    liberar_memoria_estudiantes(sistema->estudiantes);
    liberar_memoria_materias(sistema->materias);
    free(sistema);

    return 0;
}
