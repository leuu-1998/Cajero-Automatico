#ifndef MANEJOPANTALLA_H
#define MANEJOPANTALLA_H

#ifdef __linux__
    #define SO 5
#elif _WIN32
    #define SO 10
#endif

//Definicion de prototipos
void cabeceraCajero(void);
void limpiarPantalla(void);
void pausa();

#endif // MANEJOPANTALLA_H
