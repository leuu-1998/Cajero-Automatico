#ifndef CAJERO_H
#define CAJERO_H

#define MAX_CLIENTES 20
#define MAX_CAJEROS 4
#define MAX_MOVIMIENTOS 10

// Definir monto maximo de depósito y retiro
#define MAX_DEPOSITO 4000
#define MAX_RETIRO   4000

// Definir tipos de transacción
#define DEPOSITO 1
#define RETIRO 2
#define ITF 3

struct cliente{
    int numCliente;
    char numTarjeta[9];
    char contrasenya[5];
    char nombres[31];
    char apellidos[31];
    float saldo;
    char archMov[31];
    int sigMov;
};

typedef struct cliente Cliente;

struct tarjeta{
    int numCliente;
    char numTarjeta[9];
    char nombres[31];
    char apellidos[31];
};

typedef struct tarjeta Tarjeta;

struct movimiento{
    int idCajero;
    time_t fecha;
    int tipoMovimiento;
    float saldoAnterior;
    float montoTransaccion;
};

typedef struct movimiento Movimiento;

//Variables globales
int idCajero;

#endif // CAJERO_H_INCLUDED
