#include <stdio.h>
#include <time.h>

#include "movimientos.h"
#include "admClientes.h"

int menuMovimiento(void);

int iniMovimientos(char aMov[], float deposito) {
    int i;
    struct datosMovimiento enBlanco = {0, (time_t)0, 0, 0.0, 0.0};
    FILE *cfPtr;
    if((cfPtr = fopen(aMov, "wb")) == NULL) {
        printf( "Error al abrir el archivo.\n" );
        return 1;
    }
    for(i = 1; i <= MAX_MOVIMIENTOS; i++) {
        fwrite(&enBlanco, sizeof(struct datosMovimiento), 1, cfPtr);
    }
    enBlanco.idCajero = 5;
    enBlanco.fecha = time(NULL);
    enBlanco.tipoMov = 1;
    enBlanco.saldoAnterior = 0;
    enBlanco.transaccion = deposito;
    rewind(cfPtr);
    fwrite(&enBlanco, sizeof(struct datosMovimiento), 1, cfPtr);
    fclose(cfPtr);
    return 0;
}

int funcionCajero(void) {
    int opcion;
    FILE *cfPtr;
    if((cfPtr = fopen(ARCH_MOVIMIENTOS, "rb+")) == NULL) {
        printf( "Error al abrir el archivo.\n" );
        return 1;
    }
    while((opcion = menuMovimiento()) != 0) {
        switch(opcion) {
        case 1:
            deposito(cfPtr);
            break;
        case 2:
            retiro(cfPtr);
            break;
        case 3:
            mostrarSaldo(cfPtr);
            break;
        case 4:
            mostrarMovimientos(cfPtr);
            break;
        case 5:
            cambioClave(cfPtr);
            break;
        default:
            printf("Escoja una opcion valida\n");
        }
    }
    fclose(cfPtr);
    return 0;
}

int deposito(FILE *fPtr) {
    return 0;
}
int retiro(FILE *fPtr) {
    return 0;
}
int mostrarSaldo(FILE *fPtr) {
    return 0;
}
int mostrarMovimientos(FILE *fPtr) {
    return 0;
}

int cambioClave(FILE *fPtr) {
    return 0;
}

int menuMovimiento(void) {
    int opcion;
    printf("Seleccione la operacion a realizar\n");
    printf("(1) Deposito\n");
    printf("(2) Retiro\n");
    printf("(3) Saldo\n");
    printf("(4) Ultimos movimientos\n");
    printf("(5) Cambio de clave\n");
    printf("(0) Salir\nIngrese su opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);
    return opcion;
}

