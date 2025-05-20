#include <stdio.h>
#include <stdlib.h>

int main() {
    int* arreglo = NULL;
    int cantidad, opcion;
    char repetir;

    do {
        printf("\n¿Cuántos enteros desea reservar?: ");
        scanf("%d", &cantidad);

        printf("Seleccione método de asignación de memoria:\n");
        printf("1. malloc (no inicializa)\n");
        printf("2. calloc (inicializa en 0)\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            arreglo = (int*)malloc(cantidad * sizeof(int));
            if (arreglo == NULL) {
                printf("Error al reservar memoria con malloc.\n");
                return 1;
            }
            printf("\nMemoria reservada con malloc.\n");
        } else if (opcion == 2) {
            arreglo = (int*)calloc(cantidad, sizeof(int));
            if (arreglo == NULL) {
                printf("Error al reservar memoria con calloc.\n");
                return 1;
            }
            printf("\nMemoria reservada con calloc.\n");
        } else {
            printf("Opción no válida.\n");
            continue;
        }

        printf("\nIngrese %d valores enteros:\n", cantidad);
        for (int i = 0; i < cantidad; i++) {
            printf("Valor [%d]: ", i);
            scanf("%d", &arreglo[i]);
        }

        printf("\nContenido de la memoria:\n");
        for (int i = 0; i < cantidad; i++) {
            printf("arreglo[%d] = %d\n", i, arreglo[i]);
        }

        free(arreglo); 

        printf("\n¿Desea repetir el proceso? (s/n): ");
        scanf(" %c", &repetir);  

    } while (repetir == 's' || repetir == 'S');

    printf("Programa finalizado.\n");
    return 0;
}





