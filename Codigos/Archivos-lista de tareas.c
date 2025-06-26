#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea {
    int id;
    char descripcion[100];
    char estado[20];
    struct Tarea* siguiente;
} Tarea_t;

typedef struct {
    Tarea_t* cabeza;
} ListaTareas;

Tarea_t* crear_tarea(int id, const char* descripcion) {
    Tarea_t* nueva = (Tarea_t*)malloc(sizeof(Tarea_t));
    nueva->id = id;
    strcpy(nueva->descripcion, descripcion);
    strcpy(nueva->estado, "pendiente");
    nueva->siguiente = NULL;
    return nueva;
}

void agregar_tarea(ListaTareas* lista, int id, const char* descripcion) {
    Tarea_t* nueva = crear_tarea(id, descripcion);
    if (lista->cabeza == NULL) {
        lista->cabeza = nueva;
    } else {
        Tarea_t* actual = lista->cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nueva;
    }
}

void mostrar_tareas(ListaTareas* lista) {
    Tarea_t* actual = lista->cabeza;
    if (actual == NULL) {
        printf("No hay tareas.\n");
        return;
    }
    while (actual != NULL) {
        printf("ID: %d, Descripción: %s, Estado: %s\n", actual->id, actual->descripcion, actual->estado);
        actual = actual->siguiente;
    }
}

Tarea_t* buscar_tarea(ListaTareas* lista, int id) {
    Tarea_t* actual = lista->cabeza;
    while (actual != NULL) {
        if (actual->id == id) return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

void marcar_completada(ListaTareas* lista, int id) {
    Tarea_t* tarea = buscar_tarea(lista, id);
    if (tarea != NULL) {
        strcpy(tarea->estado, "completada");
        printf("Tarea %d marcada como completada.\n", id);
    } else {
        printf("Tarea no encontrada.\n");
    }
}

void eliminar_tarea(ListaTareas* lista, int id) {
    Tarea_t* actual = lista->cabeza;
    Tarea_t* anterior = NULL;
    while (actual != NULL && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL) {
        printf("Tarea no encontrada.\n");
        return;
    }
    if (anterior == NULL) {
        lista->cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    free(actual);
    printf("Tarea eliminada.\n");
}

void guardar_en_archivo(ListaTareas* lista, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (!archivo) return;
    Tarea_t* actual = lista->cabeza;
    while (actual != NULL) {
        fprintf(archivo, "%d|%s|%s\n", actual->id, actual->descripcion, actual->estado);
        actual = actual->siguiente;
    }
    fclose(archivo);
}

void cargar_desde_archivo(ListaTareas* lista, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo) return;
    int id;
    char descripcion[100];
    char estado[20];
    char linea[150];
    while (fgets(linea, sizeof(linea), archivo)) {
        if (sscanf(linea, "%d|%99[^|]|%19[^\n]", &id, descripcion, estado) == 3) {
            Tarea_t* nueva = crear_tarea(id, descripcion);
            strcpy(nueva->estado, estado);
            agregar_tarea(lista, nueva->id, nueva->descripcion);
            buscar_tarea(lista, nueva->id)->siguiente = nueva->siguiente;
            strcpy(buscar_tarea(lista, nueva->id)->estado, nueva->estado);
            free(nueva);
        }
    }
    fclose(archivo);
}

void liberar_memoria(ListaTareas* lista) {
    Tarea_t* actual = lista->cabeza;
    while (actual != NULL) {
        Tarea_t* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
}

void menu() {
    printf("\n--- GESTOR DE TAREAS ---\n");
    printf("1. Agregar tarea\n");
    printf("2. Mostrar tareas\n");
    printf("3. Marcar tarea como completada\n");
    printf("4. Eliminar tarea\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
}

int main() {
    ListaTareas lista;
    lista.cabeza = NULL;
    cargar_desde_archivo(&lista, "tareas.txt");
    int opcion;
    int id;
    char descripcion[100];
    do {
        menu();
        scanf("%d", &opcion);
        getchar();
        switch (opcion) {
            case 1:
                printf("ID de la tarea: ");
                scanf("%d", &id);
                getchar();
                printf("Descripción: ");
                fgets(descripcion, sizeof(descripcion), stdin);
                descripcion[strcspn(descripcion, "\n")] = 0;
                agregar_tarea(&lista, id, descripcion);
                guardar_en_archivo(&lista, "tareas.txt");
                break;
            case 2:
                mostrar_tareas(&lista);
                break;
            case 3:
                printf("ID de la tarea a marcar como completada: ");
                scanf("%d", &id);
                marcar_completada(&lista, id);
                guardar_en_archivo(&lista, "tareas.txt");
                break;
            case 4:
                printf("ID de la tarea a eliminar: ");
                scanf("%d", &id);
                eliminar_tarea(&lista, id);
                guardar_en_archivo(&lista, "tareas.txt");
                break;
            case 0:
                printf("Saliendo del sistema.\n");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    } while (opcion != 0);
    liberar_memoria(&lista);
    return 0;
}