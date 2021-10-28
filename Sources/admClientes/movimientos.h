#ifndef MOVIMIENTOS_H_INCLUDED
#define MOVIMIENTOS_H_INCLUDED

#define ARCH_MOVIMIENTOS "./mov05.dat"

struct datosMovimiento {
    int    idCajero;
    time_t fecha;
    int    tipoMov;
    float  saldoAnterior;
    float  transaccion;
};

int iniMovimientos(char [], float);
int funcionCajero(void);

int deposito(FILE *);
int retiro(FILE *);
int mostrarSaldo(FILE *);
int mostrarMovimientos(FILE *);
int cambioClave(FILE *);

#endif // MOVIMIENTOS_H_INCLUDED
