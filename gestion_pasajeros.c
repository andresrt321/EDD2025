#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura del pasajero (Nodo)
typedef struct Pasajero {
    char tipoDocumento[3];
    char primerApellido[30];
    struct Pasajero* siguiente; // Puntero al siguiente nodo
} Pasajero;

// Función para crear un nuevo pasajero (malloc)
Pasajero* crearPasajero(char tipo[], char apellido[]) {
    Pasajero* nuevo = (Pasajero*)malloc(sizeof(Pasajero));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return NULL;
    }
    strcpy(nuevo->tipoDocumento, tipo);
    strcpy(nuevo->primerApellido, apellido);
    nuevo->siguiente = NULL;
    return nuevo;
}

// Función para agregar pasajero al final de la lista (FIFO)
void agregarPasajero(Pasajero** cabeza, char tipo[], char apellido[]) {
    Pasajero* nuevo = crearPasajero(tipo, apellido);
    if (*cabeza == NULL) {
        *cabeza = nuevo;
    } else {
        Pasajero* actual = *cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

// Función para mostrar la lista de pasajeros
void mostrarPasajeros(Pasajero* cabeza) {
    if (cabeza == NULL) {
        printf("\nNo hay pasajeros registrados.\n");
        return;
    }

    printf("\n--- LISTA DE PASAJEROS REGISTRADOS (ORDEN DE ABORDAJE) ---\n");
    int i = 1;
    while (cabeza != NULL) {
        printf("%d. Tipo de Documento: %s | Primer Apellido: %s\n", i, cabeza->tipoDocumento, cabeza->primerApellido);
        cabeza = cabeza->siguiente;
        i++;
    }
}

// Función para simular el abordaje (solo pueden abordar los que caben)
void simularAbordaje(Pasajero* cabeza, int capacidad, int totalRegistrados) {
    if (cabeza == NULL) {
        printf("\nNo hay pasajeros para abordar.\n");
        return;
    }

    printf("\n=== SIMULACIÓN DE ABORDAJE ===\n");
    printf("Capacidad real del avión: %d asientos.\n", capacidad);
    printf("Total de tiquetes vendidos: %d.\n", totalRegistrados);

    int abordados = 0;
    Pasajero* actual = cabeza;

    // Recorrer la lista, deteniéndose en la capacidad real
    while (actual != NULL && abordados < capacidad) {
        printf("✅ ABORDA: [%s] Apellido: %s\n", actual->tipoDocumento, actual->primerApellido);
        actual = actual->siguiente;
        abordados++;
    }

    printf("-----------------------------------------\n");
    printf("Total de pasajeros que abordaron: %d\n", abordados);

    // Reporte de overbooking
    if (totalRegistrados > capacidad) {
        int no_abordaron = totalRegistrados - abordados;
        printf("⚠️ **OVERBOOKING:** %d pasajeros se quedaron sin abordar.\n", no_abordaron);
    } else {
        printf("Todos los pasajeros con tiquete pudieron abordar.\n");
    }
}

// Función para liberar la memoria usada por la lista (free)
void liberarMemoria(Pasajero** cabeza) {
    Pasajero* actual = *cabeza;
    Pasajero* siguiente;
    printf("\n--- Liberando memoria (free) ---\n");
    int nodos_liberados = 0;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual); // ¡Memoria liberada!
        actual = siguiente;
        nodos_liberados++;
    }
    *cabeza = NULL;
    printf("Memoria de %d nodos liberada completamente.\n", nodos_liberados);
}

// Función principal
int main() {
    int capacidad;
    int maximoPasajeros;
    int opcion;
    int contador = 0;
    Pasajero* lista = NULL;
    int c; // Variable para limpiar buffer

    printf("=== SISTEMA DE GESTION DE PASAJEROS ===\n");

    // Solicitar capacidad del avión
    printf("Ingrese la capacidad máxima de asientos del avión: ");
    scanf("%d", &capacidad);

    // Calcular overbooking (10% adicional)
    maximoPasajeros = capacidad + (capacidad * 10) / 100;

    printf("Capacidad total de venta (con overbooking del 10%%): %d pasajeros.\n", maximoPasajeros);
    
    // Limpiar buffer
    while ((c = getchar()) != '\n' && c != EOF);

    do {
        printf("\n----- MENU PRINCIPAL -----\n");
        printf("1. Registrar pasajero\n");
        printf("2. Mostrar lista de pasajeros\n");
        printf("3. Simular abordaje\n"); 
        printf("4. Salir y liberar memoria\n");
        printf("Seleccione una opción: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("\nOpción no válida. Intente de nuevo.\n");
            // Limpiar buffer en caso de error de entrada
            while ((c = getchar()) != '\n' && c != EOF); 
            continue;
        }
        
        // Limpiar buffer después de leer la opción
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcion) {
            case 1:
                if (contador < maximoPasajeros) {
                    char tipo[3];
                    char apellido[30];

                    printf("Ingrese el tipo de documento (CC, TI, PA): ");
                    scanf("%2s", tipo);
                    printf("Ingrese el primer apellido: ");
                    scanf("%29s", apellido);

                    agregarPasajero(&lista, tipo, apellido);
                    contador++;

                    printf("Pasajero registrado correctamente (%d/%d).\n", contador, maximoPasajeros);
                } else {
                    printf("\nNo se pueden vender más tiquetes. Se alcanzó el límite de overbooking.\n");
                }
                // Limpiar buffer después de las lecturas de scanf
                while ((c = getchar()) != '\n' && c != EOF);
                break;

            case 2:
                mostrarPasajeros(lista);
                break;

            case 3:
                simularAbordaje(lista, capacidad, contador);
                break;
                
            case 4:
                printf("\nSaliendo del sistema...\n");
                break;

            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
        }

    } while (opcion != 4);

    liberarMemoria(&lista);
    return 0;
}
