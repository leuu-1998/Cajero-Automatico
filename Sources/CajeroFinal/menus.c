#include <stdio.h>
#include <math.h>
#include <time.h>

#include "cajero.h"
#include "identificacion.h"
#include "operaciones.h"
#include "menus.h"
#include "manejoPantalla.h"

int menuCajero(void){
    int opcion;
    limpiarPantalla();
    cabeceraCajero();
    printf("\n\t\t\t(1) Cajero 1\n");
    printf("\t\t\t(2) Cajero 2\n");
    printf("\t\t\t(3) Cajero 3\n");
    printf("\t\t\t(4) Cajero 4\n");
    printf("\t\t\t(0) Salir\n");
    printf("\t\t\tIngrese su opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);
    return opcion;
}

int menuOperacion(void){
    int opcion;
    limpiarPantalla();
    cabeceraCajero();
    printf("\n\t\t\tBIENVENIDO A NUESTRO SISTEMA\n\n");
    printf("\t\t\t¿Qué operación desea realizar?\n\n");
    printf("\t\t\t1) Retiro\n");
    printf("\t\t\t2) Depósito\n");
    printf("\t\t\t3) Consulta de saldo\n");
    printf("\t\t\t4) Consulta de movimientos\n");
    printf("\t\t\t5) Cambio de Clave\n");
    printf("\t\t\t0) Regresar\n");
    printf("\n\t\tElija una de las alternativas: [ ]\b\b");
    fflush(stdin);
    scanf("%d", &opcion);
    return opcion;
}

int menuRetiro(void){
    int opcion;
    limpiarPantalla();
    cabeceraCajero();
    printf("\n\t\tUsted ha seleccionado \"Retiro\"\n\n");
    printf("\t\t¿Cuánto desea retirar?\n\n");
    printf("\t\t\t[1] s/. 20\n");
    printf("\t\t\t[2] s/. 100\n");
    printf("\t\t\t[3] s/. 200\n");
    printf("\t\t\t[4] s/. 400\n");
    printf("\t\t\t[5] s/. 800\n");
    printf("\t\t\t[6] s/. 1000\n");
    printf("\t\t\t[7] s/. 3000\n");
    printf("\t\t\t[8] Otro monto\n");
    printf("\t\t\t[0] Regresar\n");
    printf("\n\t\tElija su opción: [ ]\b\b");
    fflush(stdin);
    scanf("%d", &opcion);
    return opcion;
}

float menuDeposito(void){
    float montoDeposito;
    limpiarPantalla();
    cabeceraCajero();
    printf("\n\t\tUsted ha seleccionado \"Depósito\"\n\n");
    printf("\t\t¿Cuánto desea depositar?\n\n\t\t(MAX S./%d por depósito)\n\t\t(0) para regresar\n", MAX_DEPOSITO);
    printf("\n\t\tCantidad a depositar: ");
    fflush(stdin);
    scanf("%f", &montoDeposito);
    return montoDeposito;
}
