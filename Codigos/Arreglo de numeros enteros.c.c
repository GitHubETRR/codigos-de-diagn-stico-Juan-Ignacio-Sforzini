#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void agregar_numero(int* arreglo, int* cantidad, int numero) {
    if (*cantidad < MAX) {
        *(arreglo + *cantidad) = numero;
        (*cantidad)++;
    } else {
        printf("Arreglo lleno.\n");
    }
}

void mostrar_numeros(int* arreglo, int cantidad) {
    if (cantidad == 0) {
        printf("No hay números cargados.\n");
        return;
    }
    printf("Números cargados:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d ", *(arreglo + i));
    }
    printf("\n");
}

float calcular_promedio(int* arreglo, int cantidad) {
    if (cantidad == 0) return 0;
    int suma = 0;
    for (int i = 0; i < cantidad; i++) {
        suma += *(arreglo + i);
    }
    return (float)suma / cantidad;
}

int buscar_numero(int* arreglo, int cantidad, int buscado) {
    for (int i = 0; i < cantidad; i++) {
        if (*(arreglo + i) == buscado) {
            return i;
        }
    }
    return -1;
}

void menu() {
    printf("\n--- MENU ---\n");
    printf("1. Agregar número\n");
    printf("2. Mostrar números\n");
    printf("3. Calcular promedio\n");
    printf("4. Buscar número\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
}

int main() {
    int* arreglo = (int*)malloc(MAX * sizeof(int));
    if (arreglo == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    int cantidad = 0;
    int opcion, numero;

    do {
        menu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese un número: ");
                scanf("%d", &numero);
                agregar_numero(arreglo, &cantidad, numero);
                break;

            case 2:
                mostrar_numeros(arreglo, cantidad);
                break;

            case 3:
                printf("Promedio: %.2f\n", calcular_promedio(arreglo, cantidad));
                break;

            case 4:
                printf("Ingrese número a buscar: ");
                scanf("%d", &numero);
                int pos = buscar_numero(arreglo, cantidad, numero);
                if (pos >= 0)
                    printf("Número encontrado en la posición %d.\n", pos);
                else
                    printf("Número no encontrado.\n");
                break;

            case 0:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opción no válida.\n");
                break;
        }

    } while (opcion != 0);

    free(arreglo);
    return 0;
}

