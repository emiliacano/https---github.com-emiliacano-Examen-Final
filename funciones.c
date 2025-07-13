#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

void leerDatos(const char *archivo, struct Zona zonas[]) {
    FILE *f = fopen(archivo, "r");
    if (!f) {
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }
    char linea[200];
    fgets(linea, sizeof(linea), f);
    int i = 0;
    while (fgets(linea, sizeof(linea), f) && i < ZONAS) {
        sscanf(linea, "%[^,],%f,%f,%f,%f", zonas[i].nombre, &zonas[i].pm25, &zonas[i].so2, &zonas[i].no2, &zonas[i].co);
        i++;
    }
    fclose(f);
}

void mostrarDatos(struct Zona zonas[]) {
    printf("\n--- PROMEDIOS ANUALES POR ZONA ---\n");
    for (int i = 0; i < ZONAS; i++) {
        printf("Zona: %s\n", zonas[i].nombre);
        printf("PM2.5: %.2f \u00b5g/m3, SO2: %.2f \u00b5g/m3, NO2: %.2f \u00b5g/m3, CO: %.2f mg/m3\n\n",
               zonas[i].pm25, zonas[i].so2, zonas[i].no2, zonas[i].co);
    }
}

void emitirAlertasNECA(struct Zona zonas[]) {
    printf("\n--- ALERTAS NECA ---\n");
    for (int i = 0; i < ZONAS; i++) {
        if (zonas[i].pm25 > 15)
            printf("%s: PM2.5 supera l\u00edmite NECA (15 \u00b5g/m3)\n", zonas[i].nombre);
        if (zonas[i].so2 > 60)
            printf("%s: SO2 supera l\u00edmite NECA (60 \u00b5g/m3)\n", zonas[i].nombre);
        if (zonas[i].no2 > 40)
            printf("%s: NO2 supera l\u00edmite NECA (40 \u00b5g/m3)\n", zonas[i].nombre);
        if (zonas[i].co > 10)
            printf("%s: CO supera l\u00edmite NECA (10 mg/m3)\n", zonas[i].nombre);
    }
}

void emitirAlertasOMS(struct Zona zonas[]) {
    printf("\n--- ALERTAS OMS ---\n");
    for (int i = 0; i < ZONAS; i++) {
        if (zonas[i].pm25 > 5)
            printf("%s: PM2.5 supera gu\u00eda OMS (5 \u00b5g/m3)\n", zonas[i].nombre);
        if (zonas[i].so2 > 40)
            printf("%s: SO2 supera gu\u00eda OMS (40 \u00b5g/m3)\n", zonas[i].nombre);
        if (zonas[i].no2 > 10)
            printf("%s: NO2 supera gu\u00eda OMS (10 \u00b5g/m3)\n", zonas[i].nombre);
        if (zonas[i].co > 4)
            printf("%s: CO supera gu\u00eda OMS (4 mg/m3)\n", zonas[i].nombre);
    }
}

void generarRecomendaciones(struct Zona zonas[]) {
    printf("\n--- RECOMENDACIONES PERSONALIZADAS ---\n");
    for (int i = 0; i < ZONAS; i++) {
        printf("Zona: %s\n", zonas[i].nombre);

        if (zonas[i].pm25 > 15)
            printf("- PM2.5 elevado: Reforzar alertas a poblaci\u00f3n vulnerable, fomentar teletrabajo y evitar quemas.\n");
        if (zonas[i].so2 > 60)
            printf("- SO2 alto: Controlar emisiones industriales, instalar filtros y suspender procesos industriales.\n");
        if (zonas[i].no2 > 40)
            printf("- NO2 excesivo: Restringir circulaci\u00f3n vehicular, promover transporte p\u00fablico.\n");
        if (zonas[i].co > 10)
            printf("- CO peligroso: Mejorar ventilaci\u00f3n urbana, restringir combustibles contaminantes.\n");

        if (zonas[i].pm25 <= 15 && zonas[i].so2 <= 60 && zonas[i].no2 <= 40 && zonas[i].co <= 10)
            printf("- Contaminaci\u00f3n dentro de l\u00edmites. Mantener monitoreo y promover h\u00e1bitos sostenibles.\n");

        printf("\n");
    }
}

void exportarReporte(struct Zona zonas[]) {
    FILE *f = fopen("reporte_final.txt", "w");
    for (int i = 0; i < ZONAS; i++) {
        fprintf(f, "Zona: %s\n", zonas[i].nombre);
        fprintf(f, "PM2.5: %.2f, SO2: %.2f, NO2: %.2f, CO: %.2f\n\n",
                zonas[i].pm25, zonas[i].so2, zonas[i].no2, zonas[i].co);
    }
    fclose(f);
    printf("Reporte 'reporte_final.txt' generado correctamente.\n");
}

void buscarZona(struct Zona zonas[], const char *nombre) {
    for (int i = 0; i < ZONAS; i++) {
        if (strcasecmp(zonas[i].nombre, nombre) == 0) {
            printf("Zona: %s\nPM2.5: %.2f, SO2: %.2f, NO2: %.2f, CO: %.2f\n",
                   zonas[i].nombre, zonas[i].pm25, zonas[i].so2, zonas[i].no2, zonas[i].co);
            return;
        }
    }
    printf("Zona no encontrada.\n");
}

void rankingPM25(struct Zona zonas[]) {
    struct Zona copia[ZONAS];
    for (int i = 0; i < ZONAS; i++) copia[i] = zonas[i];

    for (int i = 0; i < ZONAS - 1; i++) {
        for (int j = i + 1; j < ZONAS; j++) {
            if (copia[i].pm25 < copia[j].pm25) {
                struct Zona temp = copia[i];
                copia[i] = copia[j];
                copia[j] = temp;
            }
        }
    }
    printf("\n--- RANKING PM2.5 ---\n");
    for (int i = 0; i < ZONAS; i++) {
        printf("%d. %s - %.2f \u00b5g/m3\n", i + 1, copia[i].nombre, copia[i].pm25);
    }
}

void menorContaminacion(struct Zona zonas[]) {
    int min = 0;
    float minValor = zonas[0].pm25 + zonas[0].so2 + zonas[0].no2 + zonas[0].co;
    for (int i = 1; i < ZONAS; i++) {
        float total = zonas[i].pm25 + zonas[i].so2 + zonas[i].no2 + zonas[i].co;
        if (total < minValor) {
            minValor = total;
            min = i;
        }
    }
    printf("\nZona con menor contaminaci\u00f3n total: %s\n", zonas[min].nombre);
    printf("PM2.5: %.2f, SO2: %.2f, NO2: %.2f, CO: %.2f\n",
           zonas[min].pm25, zonas[min].so2, zonas[min].no2, zonas[min].co);
}