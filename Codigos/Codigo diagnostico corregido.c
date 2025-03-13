
/*124.	La zapatería de barrio Alto Calzado necesita un programa para administrar su local. 
Para ello el programa debe cumplir las siguientes funciones:
a)	cargar los datos de sus 5 vendedores (DNI, nombre, apellido, genero, pares Vendidos).
b)	cargar los 10 tipos de calzado que venden (idCalzado, descripción, su stock remanente).
c)	Al vender un par de zapatillas
Armar un programa con las estructuras necesarias para contabilizar las ventas hechas por los vendedores 
(ingresando DNI y idCalzado de la venta) y 
mantenga actualizado el stock remanente de pares de zapatillas.
*/

#include <math.h>
#include <stdio.h>
#include <string.h>

#define NUM_VENDEDORES 5
#define NUM_CALZADOS 5
#define MAXCHAR 20
#define DNI 10
#define DESCRIPCION 50

typedef struct {
    char dni[DNI];
    char nombre[MAXCHAR];
    char apellido[MAXCHAR];
    char genero;
    int paresVendidos;
} Vendedor;

typedef struct {
    int idCalzado;
    char descripcion[DESCRIPCION];
    int stock;
} Calzado;

void datosVendedor(Vendedor vendedores[NUM_VENDEDORES]);
void datosCalzados(Calzado calzados[NUM_CALZADOS]);
void cargarVentas(Vendedor vendedores[NUM_VENDEDORES], Calzado calzados[NUM_CALZADOS]);

int main()
{
    Vendedor vendedores[NUM_VENDEDORES];
    Calzado calzados[NUM_CALZADOS];
    char continuar = 'S';
    
    datosVendedor(vendedores);
    datosCalzados(calzados);
    
    while (continuar == 'S' || continuar == 's') {
        cargarVentas(vendedores, calzados);
        printf("¿Quieres registrar otra venta? (S/N): ");
        scanf(" %c", &continuar);  
    }
    
    printf("Estadísticas de los vendedores:\n");  
    for (int i = 0; i < NUM_VENDEDORES ; i++) {
        printf("Vendedor %s %s, pares vendidos %d\n", vendedores[i].nombre, vendedores[i].apellido, vendedores[i].paresVendidos);
    }
    
    return 0;
}

void datosVendedor(Vendedor vendedores[NUM_VENDEDORES]) {
    for (int i=0; i < NUM_VENDEDORES; i++) {
        printf("Ingrese DNI del vendedor %d: ", i + 1);
        scanf("%s", vendedores[i].dni);
        printf("Ingrese nombre del vendedor %d: ", i + 1);
        scanf("%s", vendedores[i].nombre);
        printf("Ingrese apellido del vendedor %d: ", i + 1);
        scanf("%s", vendedores[i].apellido);
        printf("Ingrese genero del vendedor %d (M/H): ", i + 1);
        scanf(" %c", &vendedores[i].genero);
        vendedores[i].paresVendidos = 0;
    }
}

void datosCalzados(Calzado calzados[NUM_CALZADOS]) {
    for (int i=0; i < NUM_CALZADOS; i++) {
        printf("Ingrese ID del calzado %d: ", i + 1);
        scanf("%d", &calzados[i].idCalzado);
        printf("Ingrese descripcion del calzado %d: ", i + 1);
        scanf("%s", calzados[i].descripcion);
        printf("Ingrese stock del calzado %d: ", i + 1);
        scanf("%d", &calzados[i].stock);
    }
} 

void cargarVentas(Vendedor vendedores[NUM_VENDEDORES], Calzado calzados[NUM_CALZADOS]) {
    char dni[DNI];
    int idCalzado, i, y;
    
    printf("Ingrese el DNI del vendedor: ");
    scanf("%s", dni);
    
    for (i = 0; i < NUM_VENDEDORES; i++) {
        if (strcmp(vendedores[i].dni, dni) == 0) {
            break;
        }
    }
    
    if (i == NUM_VENDEDORES) {
        printf("Vendedor no encontrado.\n");
        return;
    }
    
    printf("Ingrese el ID del calzado vendido: ");
    scanf("%d", &idCalzado);
    
    for (y = 0; y < NUM_CALZADOS; y++) {
        if (calzados[y].idCalzado == idCalzado) {
            break;
        }
    }
    
    if (y == NUM_CALZADOS) {
        printf("Calzado no encontrado.\n");
        return;
    }
    
    if (calzados[y].stock > 0) {
        calzados[y].stock--;
        vendedores[i].paresVendidos++;
        printf("Venta registrada\n");
    } else {
        printf("No hay stock\n");
    }
}
