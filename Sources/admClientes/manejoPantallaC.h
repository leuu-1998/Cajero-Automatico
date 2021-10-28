#ifndef MANEJOPANTALLAC_H
#define MANEJOPANTALLAC_H

#ifdef __linux__
    #define SO 5
#elif __WIN32
    #define SO 10
#endif

//Definicion de prototipos
void cabeceraClientes(void);
void limpiarPantalla(void);
void pausa();

#endif // MANEJOPANTALLA_H
