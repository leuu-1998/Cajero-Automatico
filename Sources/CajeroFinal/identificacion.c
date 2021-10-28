#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "cajero.h"
#include "identificacion.h"
#include "operaciones.h"
#include "menus.h"
#include "manejoPantalla.h"

Tarjeta ingresarTarjeta(void){
    Tarjeta tarjCliente = {0, "", "", ""};
    char numTarjeta[9];
    char archT[30];
    sprintf(archT, "./TARJETAS/T");
    FILE *tfPtr;
    limpiarPantalla();
    cabeceraCajero();
    printf("\n\t\tPor favor, ingrese su número de tarjeta (8 dígitos):\n");
    printf("\n\t\t\t\t   ");
    fflush(stdin);
    scanf("%8s", numTarjeta);
    strcat(archT, numTarjeta);
    strcat(archT, ".dat");

    if((tfPtr = fopen(archT, "rb")) == NULL) {
        printf("\n\n\t\tNúmero de tarjeta no válido.\n\n\t\tPresione ENTER para continuar: ");
        pausa();
        return tarjCliente;
    }
    fread(&tarjCliente, sizeof(Tarjeta), 1, tfPtr);
    fclose(tfPtr);
    return tarjCliente;
}

Cliente validarDatos(Tarjeta datosTarjeta){
    FILE *cfPtr;
    Cliente datosCliente = {0, "", "", "", "", 0.0, "", 0};
    char contrasenya[5];
    if((cfPtr = fopen("./CLIENTES/Clientes.dat", "rb")) == NULL) {
        printf("\n\n\tNo se puede abrir el archivo de clientes. Presione ENTER para continuar: ");
        pausa();
        return datosCliente;
    }
    fseek(cfPtr, sizeof(Cliente) * (datosTarjeta.numCliente - 1), SEEK_SET);
    fread(&datosCliente, sizeof(Cliente), 1, cfPtr);

    if(datosCliente.numCliente == 0) {
        printf("\n\n\t\tCliente no existe. Presione ENTER para continuar: ");
        pausa();
        return datosCliente;
    }

    if((datosCliente.numCliente != datosTarjeta.numCliente) ||
          strcmp(datosTarjeta.nombres, datosCliente.nombres) ||
          strcmp(datosTarjeta.apellidos, datosCliente.apellidos)) {
        datosCliente.numCliente = 0;
        printf("\n\n\t\tLos datos no coinciden. Presione ENTER para continuar: ");
        pausa();
        return datosCliente;
    }
    limpiarPantalla();
    cabeceraCajero();
    printf("\n\t\tPor favor, Ingrese su contraseña(4 dígitos)\n");
    printf("\n\t\t\t\t   ");
    fflush(stdin);
    scanf("%4s", contrasenya);
    if(strcmp(contrasenya, datosCliente.contrasenya) != 0){
        datosCliente.numCliente = 0;
        printf("\n\n\t\tContraseña errada. Presione ENTER para continuar: ");
        pausa();
        return datosCliente;
    }
    printf("\n\n\n\n\t\tCliente Validado! Presione ENTER para continuar: ");
    pausa();
    return datosCliente;
}
