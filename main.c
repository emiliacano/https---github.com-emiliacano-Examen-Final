#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int main() {
    struct Zona zonas[ZONAS];
    int datosCargados = 0;
    int opcion;
    char buscar[30];

    do {
        printf("\n====== SISTEMA DE CALIDAD DEL AIRE - QUITO 2021 ======\n");
        printf("1. Cargar datos desde archivo CSV\n");
        printf("2. Mostrar todos los promedios anuales por zona\n");
        printf("3. Mostrar zonas que superan los l\u00edmites NECA\n");
        printf("4. Mostrar zonas que superan los l\u00edmites OMS\n");
        printf("5. Ver recomendaciones de mitigaci\u00f3n por zona\n");
        printf("6. Generar y guardar un reporte detallado en archivo\n");
        printf("7. Buscar por nombre de zona y ver sus valores\n");
        printf("8. Mostrar ranking de zonas con mayor contaminaci\u00f3n PM2.5\n");
        printf("9. Mostrar zona con menor contaminaci\u00f3n general\n");
        printf("10. Salir del sistema\n");
        printf("Seleccione una opci\u00f3n: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                leerDatos("datos_calidad_aire_quito_2021.csv", zonas);
                datosCargados = 1;
                printf("\nDatos cargados correctamente.\n");
                break;
            case 2:
                if (datosCargados) mostrarDatos(zonas);
                else printf("Primero debes cargar los datos (opci\u00f3n 1).\n");
                break;
            case 3:
                if (datosCargados) emitirAlertasNECA(zonas);
                else printf("Primero debes cargar los datos (opci\u00f3n 1).\n");
                break;
            case 4:
                if (datosCargados) emitirAlertasOMS(zonas);
                else printf("Primero debes cargar los datos (opci\u00f3n 1).\n");
                break;
            case 5:
                if (datosCargados) generarRecomendaciones(zonas);
                else printf("Primero debes cargar los datos (opci\u00f3n 1).\n");
                break;
            case 6:
                if (datosCargados) exportarReporte(zonas);
                else printf("Primero debes cargar los datos (opci\u00f3n 1).\n");
                break;
            case 7:
                if (datosCargados) {
                    printf("Ingrese el nombre de la zona a buscar: ");
                    fgets(buscar, sizeof(buscar), stdin);
                    buscar[strcspn(buscar, "\n")] = 0;
                    buscarZona(zonas, buscar);
                } else printf("Primero debes cargar los datos (opci\u00f3n 1).\n");
                break;
            case 8:
                if (datosCargados) rankingPM25(zonas);
                else printf("Primero debes cargar los datos (opci\u00f3n 1).\n");
                break;
            case 9:
                if (datosCargados) menorContaminacion(zonas);
                else printf("Primero debes cargar los datos (opci\u00f3n 1).\n");
                break;
            case 10:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 10);

    return 0;
}
