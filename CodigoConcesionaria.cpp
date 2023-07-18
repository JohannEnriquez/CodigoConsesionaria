#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 1000

// Función para ingresar un nuevo producto
void ingresarProducto(char nombres[][100], int cantidades[], float precios[], int *numProductos) {
    int repetir;
    do {
        char nombre[100];
        int cantidad;
        float precio;

        printf("Ingrese el nombre del producto: ");
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = '\0';  // Eliminar el salto de línea al final

        printf("Ingrese la cantidad: ");
        scanf("%d", &cantidad);
        printf("Ingrese el precio incluido el iva: ");
        scanf("%f", &precio);

        // Agregar el nuevo producto a los arreglos
        strcpy(nombres[*numProductos], nombre);
        cantidades[*numProductos] = cantidad;
        precios[*numProductos] = precio;
        (*numProductos)++;

        printf("Producto agregado exitosamente.\n");
        printf("¿Desea ingresar otro producto? (1: Sí, 0: No): ");
        scanf("%d", &repetir);
        getchar();  // Limpiar el buffer de entrada
    } while (repetir == 1);
}

// Función para mostrar una tabla con los productos ingresados
void mostrarTablaProductos(char nombres[][100], int cantidades[], float precios[], int numProductos) {
    printf("-------------------------------------------------------------------\n");
    printf("| Índice |   Nombre del Producto   | Cantidad |    Precio+IVA    |\n");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < numProductos; i++) {
        printf("|   %2d   | %-23s |   %3d    | $ %9.2f |\n", i, nombres[i], cantidades[i], precios[i]);
    }
    printf("-------------------------------------------------------------------\n");
}

// Función para listar todos los productos ingresados
void listarProductos(char nombres[][100], int cantidades[], float precios[], int numProductos) {
    if (numProductos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }

    mostrarTablaProductos(nombres, cantidades, precios, numProductos);
}

// Función para editar un producto existente
void editarProducto(char nombres[][100], int cantidades[], float precios[], int numProductos) {
    int repetir;
    do {
        printf("Productos existentes:\n");
        mostrarTablaProductos(nombres, cantidades, precios, numProductos);

        int indice;
        printf("Ingrese el índice del producto a editar: ");
        scanf("%d", &indice);

        if (indice >= 0 && indice < numProductos) {
            printf("Ingrese el nuevo nombre del producto: ");
            getchar();  // Limpiar el buffer de entrada antes de leer el nombre
            fgets(nombres[indice], sizeof(nombres[indice]), stdin);
            nombres[indice][strcspn(nombres[indice], "\n")] = '\0';  // Eliminar el salto de línea al final

            printf("Ingrese la nueva cantidad: ");
            scanf("%d", &(cantidades[indice]));
            printf("Ingrese el nuevo precio incluido el iva: ");
            scanf("%f", &(precios[indice]));

            printf("Producto editado exitosamente.\n");
        } else {
            printf("Índice inválido.\n");
        }

        printf("¿Desea editar otro producto? (1: Sí, 0: No): ");
        scanf("%d", &repetir);
        getchar();  // Limpiar el buffer de entrada
    } while (repetir == 1);
}

// Función para eliminar un producto existente
void eliminarProducto(char nombres[][100], int cantidades[], float precios[], int *numProductos) {
    int repetir;
    do {
        printf("Productos existentes:\n");
        mostrarTablaProductos(nombres, cantidades, precios, *numProductos);

        int indice;
        printf("Ingrese el índice del producto a eliminar: ");
        scanf("%d", &indice);

        if (indice >= 0 && indice < *numProductos) {
            // Desplazar los elementos hacia atrás para eliminar el producto
            for (int i = indice; i < *numProductos - 1; i++) {
                strcpy(nombres[i], nombres[i + 1]);
                cantidades[i] = cantidades[i + 1];
                precios[i] = precios[i + 1];
            }
            (*numProductos)--;
            printf("Producto eliminado exitosamente.\n");
        } else {
            printf("Índice inválido.\n");
        }

        printf("¿Desea eliminar otro producto? (1: Sí, 0: No): ");
        scanf("%d", &repetir);
        getchar();  // Limpiar el buffer de entrada
    } while (repetir == 1);
}

int main() {
    char nombres[MAX_PRODUCTOS][100];
    int cantidades[MAX_PRODUCTOS];
    float precios[MAX_PRODUCTOS];
    int numProductos = 0;
    int opcion;

    do {
        printf("Sistema de Inventarios\n");
        printf("1. Ingresar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Listar productos\n");
        printf("5. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        getchar();  // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                ingresarProducto(nombres, cantidades, precios, &numProductos);
                break;
            case 2:
                editarProducto(nombres, cantidades, precios, numProductos);
                break;
            case 3:
                eliminarProducto(nombres, cantidades, precios, &numProductos);
                break;
            case 4:
                listarProductos(nombres, cantidades, precios, numProductos);
                break;
            case 5:
                printf("¡Hasta luego!\n");
                break;
            default:
                printf("Opción inválida.\n");
                break;
        }

        printf("\n");
    } while (opcion != 5);

    return 0;
}