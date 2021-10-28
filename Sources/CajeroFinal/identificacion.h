#ifndef IDENTIFICACION_H
#define IDENTIFICACION_H

#ifdef __linux__
    #define SO 5
#elif _WIN32
    #define SO 10
#endif

//Declaración de prototipos
Tarjeta ingresarTarjeta(void);
Cliente validarDatos(Tarjeta);

#endif // IDENTIFICACION_H
