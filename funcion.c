
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcion.h"

#define MaxProducts 100
#define MaxStringLength 100

void verProductos(char nombre[][100], char describ[][100], int *cantidades, float *precios, int numProductos) {
    FILE *archivo = fopen("inventario.txt", "r");
    if (archivo == NULL) {
        printf("El inventario está vacío.\n");
        return;
    }

    printf("=== PRODUCTOS ===\n");
    printf("%-20s %-20s %-10s %-10s\n", "Nombre", "Descripción", "Cantidad", "Precio");

    char nombreStr[MaxStringLength];
    char describStr[MaxStringLength];
    int cantidad;
    float precio;

    while (fscanf(archivo, "%s %s %d %f", nombreStr, describStr, &cantidad, &precio) == 4) {
        printf("%-20s %-20s %-10d %-10.2f\n", nombreStr, describStr, cantidad, precio);
    }

    fclose(archivo);
}

void ingresarProducto(char nombre[][100], char describ[][100], int *cantidades, float *precios, int *numProductos) {
    FILE *archivo = fopen("inventario.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char nombreStr[MaxStringLength];
    char describStr[MaxStringLength];
    int cantidad;
    float precio;

    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombreStr);
    printf("Ingrese la descripción del producto: ");
    scanf("%s", describStr);
    printf("Ingrese la cantidad: ");
    scanf("%d", &cantidad);
    printf("Ingrese el precio: ");
    scanf("%f", &precio);

    fprintf(archivo, "%s %s %d %.2f\n", nombreStr, describStr, cantidad, precio);

    fclose(archivo);

    printf("Producto agregado al inventario.\n");

    if (*numProductos < MaxProducts) {
        strcpy(nombre[*numProductos], nombreStr);
        strcpy(describ[*numProductos], describStr);
        cantidades[*numProductos] = cantidad;
        precios[*numProductos] = precio;
        (*numProductos)++;
    }
}

void modificarProducto(char nombre[][100], char describ[][100], int *cantidades, float *precios, int numProductos) {
    FILE *archivo = fopen("inventario.txt", "r+");
    if (archivo == NULL) {
        printf("El inventario está vacío.\n");
        return;
    }

 printf("Ingrese el número de producto a modificar (1-%d): ", numProductos);
    int numeroProducto;
       scanf("%d", &numeroProducto);

    char nombreStr[MaxStringLength];
    char describStr[MaxStringLength];
    int cantidad;
    float precio;

    fseek(archivo, (numeroProducto - 1) * (MaxStringLength * 2 + sizeof(int) + sizeof(float)), SEEK_SET);
    if (fscanf(archivo, "%s %s %d %f", nombreStr, describStr, &cantidad, &precio) != 4) {
        printf("Número de producto inválido.\n");
        fclose(archivo);
        return;
    }

    printf("Producto actual:\n");
    printf("Nombre: %s\n", nombreStr);
    printf("Descripción: %s\n", describStr);
    printf("Cantidad: %d\n", cantidad);
    printf("Precio: %.2f\n", precio);

    printf("Ingrese el nuevo nombre: ");
    scanf("%s", nombreStr);
    printf("Ingrese la nueva descripción: ");
    scanf("%s", describStr);
    printf("Ingrese la nueva cantidad: ");
    scanf("%d", &cantidad);
    printf("Ingrese el nuevo precio: ");
    scanf("%f", &precio);

    fseek(archivo, (numeroProducto - 1) * (MaxStringLength * 2 + sizeof(int) + sizeof(float)), SEEK_SET);
    fprintf(archivo, "%s %s %d %.2f\n", nombreStr, describStr, cantidad, precio);

    fclose(archivo);

    printf("Producto modificado.\n");

    if (numeroProducto >= 1 && numeroProducto <= numProductos) {
        strcpy(nombre[numeroProducto - 1], nombreStr);
        strcpy(describ[numeroProducto - 1], describStr);
        cantidades[numeroProducto - 1] = cantidad;
        precios[numeroProducto - 1] = precio;
    }
}

void eliminarProducto(char nombre[][100], char describ[][100], int *cantidades, float *precios, int *numProductos) {
    FILE *archivo = fopen("inventario.txt", "r+");
    if (archivo == NULL) {
        printf("El inventario está vacío.\n");
        return;
    }

    printf("Ingrese el número de producto a eliminar (1-%d): ", *numProductos);
    int numeroProducto;
        scanf("%d", &numeroProducto);

    if (numeroProducto < 1 || numeroProducto > *numProductos) {
        printf("Número de producto inválido.\n");
        fclose(archivo);
        return;
    }

    printf("Producto eliminado:\n");
    printf("Nombre: %s\n", nombre[numeroProducto - 1]);
    printf("Descripción: %s\n", describ[numeroProducto - 1]);
    printf("Cantidad: %d\n", cantidades[numeroProducto - 1]);
    printf("Precio: %.2f\n", precios[numeroProducto - 1]);

    fseek(archivo, (numeroProducto - 1) * (MaxStringLength * 2 + sizeof(int) + sizeof(float)), SEEK_SET);
    fprintf(archivo, "");

    fclose(archivo);

    for (int i = numeroProducto - 1; i < *numProductos - 1; i++) {
        strcpy(nombre[i], nombre[i + 1]);
        strcpy(describ[i], describ[i + 1]);
        cantidades[i] = cantidades[i + 1];
        precios[i] = precios[i + 1];
    }

    (*numProductos)--;


    printf("Producto eliminado.\n");




}
