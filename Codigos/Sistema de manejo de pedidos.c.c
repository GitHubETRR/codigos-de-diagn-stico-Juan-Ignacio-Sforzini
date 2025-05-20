#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
    int id_pedido;
    char cliente[50];
    char producto[50];
    char estado[20];
    struct Pedido* siguiente;
} Pedido_t;

typedef struct {
    Pedido_t* cabeza;
} ListaPedidos;

Pedido_t* crear_pedido(int id, const char* cliente, const char* producto) {
    Pedido_t* nuevo = (Pedido_t*)malloc(sizeof(Pedido_t));
    nuevo->id_pedido = id;
    strcpy(nuevo->cliente, cliente);
    strcpy(nuevo->producto, producto);
    strcpy(nuevo->estado, "pendiente");
    nuevo->siguiente = NULL;
    return nuevo;
}

void agregar_pedido(ListaPedidos* lista, int id, const char* cliente, const char* producto) {
    Pedido_t* nuevo = crear_pedido(id, cliente, producto);
    if (lista->cabeza == NULL) {
        lista->cabeza = nuevo;
    } else {
        Pedido_t* actual = lista->cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void mostrar_pedidos(ListaPedidos* lista) {
    Pedido_t* actual = lista->cabeza;
    if (actual == NULL) {
        printf("No hay pedidos.\n");
    }
    while (actual != NULL) {
        printf("ID: %d, Cliente: %s, Producto: %s, Estado: %s\n",
               actual->id_pedido, actual->cliente, actual->producto, actual->estado);
        actual = actual->siguiente;
    }
}

Pedido_t* buscar_pedido(ListaPedidos* lista, int id) {
    Pedido_t* actual = lista->cabeza;
    while (actual != NULL) {
        if (actual->id_pedido == id) {
            printf("Pedido encontrado - ID: %d, Cliente: %s, Producto: %s, Estado: %s\n",
                   actual->id_pedido, actual->cliente, actual->producto, actual->estado);
            return actual;
        }
        actual = actual->siguiente;
    }
    printf("Pedido no encontrado.\n");
    return NULL;
}

void eliminar_pedido(ListaPedidos* lista, int id) {
    Pedido_t* actual = lista->cabeza;
    Pedido_t* anterior = NULL;
    while (actual != NULL && actual->id_pedido != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL) {
        printf("Pedido no encontrado.\n");
        return;
    }
    if (anterior == NULL) {
        lista->cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    free(actual);
    printf("Pedido con ID %d eliminado.\n", id);
}

void marcar_entregado(ListaPedidos* lista, int id) {
    Pedido_t* pedido = buscar_pedido(lista, id);
    if (pedido != NULL && strcmp(pedido->estado, "entregado") != 0) {
        strcpy(pedido->estado, "entregado");
        printf("Pedido %d marcado como entregado.\n", id);
    }
}

void mostrar_pedidos_por_estado(ListaPedidos* lista, const char* estado) {
    Pedido_t* actual = lista->cabeza;
    int encontrado = 0;
    while (actual != NULL) {
        if (strcmp(actual->estado, estado) == 0) {
            printf("ID: %d, Cliente: %s, Producto: %s, Estado: %s\n",
                   actual->id_pedido, actual->cliente, actual->producto, actual->estado);
            encontrado = 1;
        }
        actual = actual->siguiente;
    }
    if (!encontrado) {
        printf("No hay pedidos con estado '%s'.\n", estado);
    }
}

void menu() {
    printf("\n--- MENU DE PEDIDOS ---\n");
    printf("1. Agregar pedido\n");
    printf("2. Mostrar todos los pedidos\n");
    printf("3. Buscar pedido por ID\n");
    printf("4. Marcar pedido como entregado\n");
    printf("5. Mostrar pedidos pendientes\n");
    printf("6. Mostrar pedidos entregados\n");
    printf("7. Eliminar pedido por ID\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
}

int main() {
    ListaPedidos lista;
    lista.cabeza = NULL;
    int opcion;
    int id;
    char cliente[50];
    char producto[50];

    do {
        menu();
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("ID del pedido: ");
                scanf("%d", &id);
                getchar();
                printf("Nombre del cliente: ");
                fgets(cliente, sizeof(cliente), stdin);
                cliente[strcspn(cliente, "\n")] = 0;
                printf("Nombre del producto: ");
                fgets(producto, sizeof(producto), stdin);
                producto[strcspn(producto, "\n")] = 0;
                agregar_pedido(&lista, id, cliente, producto);
                break;

            case 2:
                mostrar_pedidos(&lista);
                break;

            case 3:
                printf("Ingrese ID a buscar: ");
                scanf("%d", &id);
                buscar_pedido(&lista, id);
                break;

            case 4:
                printf("ID del pedido a marcar como entregado: ");
                scanf("%d", &id);
                marcar_entregado(&lista, id);
                break;

            case 5:
                mostrar_pedidos_por_estado(&lista, "pendiente");
                break;

            case 6:
                mostrar_pedidos_por_estado(&lista, "entregado");
                break;

            case 7:
                printf("Ingrese ID del pedido a eliminar: ");
                scanf("%d", &id);
                eliminar_pedido(&lista, id);
                break;

            case 0:
                printf("Saliendo del sistema.\n");
                break;

            default:
                printf("Opción no válida.\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}
