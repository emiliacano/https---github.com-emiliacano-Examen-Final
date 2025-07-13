#ifndef FUNCIONES_H
#define FUNCIONES_H

#define ZONAS 9

struct Zona {
    char nombre[30];
    float pm25;
    float so2;
    float no2;
    float co;
};

void leerDatos(const char *archivo, struct Zona zonas[]);
void mostrarDatos(struct Zona zonas[]);
void emitirAlertasNECA(struct Zona zonas[]);
void emitirAlertasOMS(struct Zona zonas[]);
void generarRecomendaciones(struct Zona zonas[]);
void exportarReporte(struct Zona zonas[]);
void buscarZona(struct Zona zonas[], const char *nombre);
void rankingPM25(struct Zona zonas[]);
void menorContaminacion(struct Zona zonas[]);

#endif

