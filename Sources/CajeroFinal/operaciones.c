#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "cajero.h"
#include "identificacion.h"
#include "operaciones.h"
#include "menus.h"
#include "manejoPantalla.h"

int retiro(Cliente dCliente){
    FILE *mfPtr;
    FILE *cfPtr;
    FILE *vfPtr;
    char archV[31] = "./VOUCHERS/voucher";
    struct tm *tiempo;
    int opcion;
    Movimiento dMov;
    float montoRetiro;
    float montoITF;
    opcion = menuRetiro();
    switch(opcion){
    case 0:
        return 0;
    case 1:
        montoRetiro = 20;
        break;
    case 2:
        montoRetiro = 100;
        break;
    case 3:
        montoRetiro = 200;
        break;
    case 4:
        montoRetiro = 400;
        break;
    case 5:
        montoRetiro = 800;
        break;
    case 6:
        montoRetiro = 1000;
        break;
    case 7:
        montoRetiro = 3000;
        break;
    case 8:
        printf("\n\t\t¿Cuánto desea retirar?: ");
        fflush(stdin);
        scanf("%f", &montoRetiro);
        break;
    default:
        printf("\n\n\t\tNo es una opción válida!\n");
        pausa();
        return 1;
    }
    if(montoRetiro > MAX_RETIRO){
        printf("\n\n\t\tNo puede retirar esa cantidad de dinero\n");
        printf("\t\t(monto a retirar mayor a S./%d)!\n\n\t\tPresione ENTER para regresar: ", MAX_RETIRO);
        pausa();
        return 1;
    }
    if(dCliente.saldo < montoRetiro){
        printf("\n\n\t\tNo puede retirar esa cantidad de dinero\n\t\t(saldo menor al monto a retirar)!");
        printf("\n\n\t\tPresione ENTER para continuar: ");
        pausa();
        return 1;
    }

    dMov.idCajero = idCajero;
    dMov.fecha = time(NULL);
    dMov.tipoMovimiento = RETIRO;
    dMov.saldoAnterior = dCliente.saldo;
    dMov.montoTransaccion = - montoRetiro;

    dCliente.saldo -= montoRetiro;

    if((mfPtr = fopen(dCliente.archMov, "rb+")) == NULL) {
        printf("\n\t\tNo se puede abrir el archivo de movimientos. Presione ENTER para continuar: ");
        pausa();
        return 1;
    }
    fseek(mfPtr, sizeof(Movimiento) * dCliente.sigMov, SEEK_SET);
    fwrite(&dMov, sizeof(Movimiento), 1, mfPtr);
    dCliente.sigMov = (dCliente.sigMov + 1) % MAX_MOVIMIENTOS;
    if((montoRetiro >= 1000)){
        dMov.tipoMovimiento = ITF;
        dMov.saldoAnterior = dCliente.saldo;
        montoITF = 0.05 * (int)(montoRetiro / 1000);
        dMov.montoTransaccion = - montoITF;
        dCliente.saldo -= montoITF;
        rewind(mfPtr);
        fseek(mfPtr, sizeof(Movimiento) * dCliente.sigMov, SEEK_SET);
        fwrite(&dMov, sizeof(Movimiento), 1, mfPtr);
        dCliente.sigMov = (dCliente.sigMov + 1) % MAX_MOVIMIENTOS;
    }
    if((cfPtr = fopen("./CLIENTES/Clientes.dat", "rb+")) == NULL) {
        printf("\n\tNo se puede abrir el archivo de clientes. Presione ENTER para continuar: ");
        pausa();
        return 1;
    }
    fseek(cfPtr, sizeof(Cliente) * (dCliente.numCliente - 1), SEEK_SET);
    fwrite(&dCliente, sizeof(Cliente), 1, cfPtr);

    fclose(mfPtr);
    fclose(cfPtr);

    //IMPRIMIR VOUCHER RETIRO
    tiempo = localtime(&dMov.fecha);

    strcat(archV, dCliente.numTarjeta);
    strcat(archV, ".txt");

    if((vfPtr = fopen(archV, "wt")) == NULL) {
        printf("\n\tError al abrir el archivo voucher. Presione ENTER para continuar: ");
        pausa();
        return 1;
    }
    fprintf(vfPtr, "CLIENTE: ");
    fprintf(vfPtr, "%s %s\n", dCliente.nombres, dCliente.apellidos);
    fprintf(vfPtr, "LUGAR: CAJERO %d\n", idCajero);
    fprintf(vfPtr, "FECHA: ");
    fprintf(vfPtr, "%.2d/%.2d/%.2d", tiempo->tm_mday,
                                     tiempo->tm_mon + 1,
                                    (tiempo->tm_year + 1900) % 2000); //Fecha
    fprintf(vfPtr, " HORA: ");
    fprintf(vfPtr, "%.2d:%.2d", tiempo->tm_hour,
                                 tiempo->tm_min);                     //Hora
    fprintf(vfPtr, "\n---------------------------\n");
    fprintf(vfPtr, "MONTO RETIRADO: S./");
    fprintf(vfPtr, "%.2f\n", montoRetiro);
    fprintf(vfPtr, "SALDO ACTUAL: S./");
    fprintf(vfPtr, "%.2f\n", dCliente.saldo);
    fprintf(vfPtr, "---------------------------");

    fclose(vfPtr);

    printf("\n\n\t\tTRANSACCIÓN COMPLETADA SATISFACTORIAMENTE");
    printf("\n\t\tPor favor, retire su dinero y recoja su voucher");
    printf("\n\n\t\tPresione ENTER para continuar: ");
    pausa();
    return 0;
}

int deposito(Cliente dCliente){
    FILE *mfPtr;
    FILE *cfPtr;
    FILE *vfPtr;
    char archV[31] = "./VOUCHERS/voucher";
    struct tm *tiempo;
    Movimiento dMov;
    float montoDeposito;
    float montoITF;
    montoDeposito = menuDeposito();
    if(montoDeposito == 0){
        return 0;
    }

    if(montoDeposito > MAX_DEPOSITO){
        printf("\n\n\t\tNo puede depositar esa cantidad de dinero\n");
        printf("\t\t(monto a depositar mayor a S./%d)!\n\n\t\tPresione ENTER para regresar: ", MAX_DEPOSITO);
        pausa();
        return 1;
    }

    dMov.idCajero = idCajero;
    dMov.fecha = time(NULL);
    dMov.tipoMovimiento = DEPOSITO;
    dMov.saldoAnterior = dCliente.saldo;
    dMov.montoTransaccion = montoDeposito;

    dCliente.saldo += montoDeposito;

    if((mfPtr = fopen(dCliente.archMov, "rb+")) == NULL) {
        printf("\n\t\tNo se puede abrir el archivo de movimientos.\n\t\t\tPresione ENTER para regresar: ");
        pausa();
        return 1;
    }

    fseek(mfPtr, sizeof(Movimiento) * dCliente.sigMov, SEEK_SET);
    fwrite(&dMov, sizeof(Movimiento), 1, mfPtr);
    dCliente.sigMov = (dCliente.sigMov + 1) % MAX_MOVIMIENTOS;

    if((montoDeposito >= 1000)){
        dMov.tipoMovimiento = ITF;
        dMov.saldoAnterior = dCliente.saldo;
        montoITF = 0.05 * (int)(montoDeposito / 1000);
        dMov.montoTransaccion = - montoITF;
        dCliente.saldo -= montoITF;
        rewind(mfPtr);
        fseek(mfPtr, sizeof(Movimiento) * dCliente.sigMov, SEEK_SET);
        fwrite(&dMov, sizeof(Movimiento), 1, mfPtr);
        dCliente.sigMov = (dCliente.sigMov + 1) % MAX_MOVIMIENTOS;
    }
    if((cfPtr = fopen("./CLIENTES/Clientes.dat", "rb+")) == NULL) {
        printf("\n\tNo se puede abrir el archivo de clientes.\n\t\tPresione ENTER para regresar: ");
        pausa();
        return 1;
    }
    fseek(cfPtr, sizeof(Cliente) * (dCliente.numCliente - 1), SEEK_SET);
    fwrite(&dCliente, sizeof(Cliente), 1, cfPtr);

    fclose(mfPtr);
    fclose(cfPtr);

    //IMPRIMIR VOUCHER DEPOSITO
    tiempo = localtime(&dMov.fecha);

    strcat(archV, dCliente.numTarjeta);
    strcat(archV, ".txt");

    if((vfPtr = fopen(archV, "wt")) == NULL) {
        printf("\n\tError al abrir el archivo voucher. Presione ENTER para regresar: ");
        pausa();
        return 1;
    }
    fprintf(vfPtr, "CLIENTE: ");
    fprintf(vfPtr, "%s %s\n", dCliente.nombres, dCliente.apellidos);
    fprintf(vfPtr, "LUGAR: CAJERO %d\n", idCajero);
    fprintf(vfPtr, "FECHA: ");
    fprintf(vfPtr, "%.2d/%.2d/%.2d", tiempo->tm_mday,
                                     tiempo->tm_mon + 1,
                                    (tiempo->tm_year + 1900) % 2000); //Fecha
    fprintf(vfPtr, " HORA: ");
    fprintf(vfPtr, "%.2d:%.2d", tiempo->tm_hour,
                                 tiempo->tm_min);                     //Hora
    fprintf(vfPtr, "\n---------------------------\n");
    fprintf(vfPtr, "MONTO DEPOSITADO: S./");
    fprintf(vfPtr, "%.2f\n", montoDeposito);
    fprintf(vfPtr, "SALDO ACTUAL: S./");
    fprintf(vfPtr, "%.2f\n", dCliente.saldo);
    fprintf(vfPtr, "---------------------------");

    fclose(vfPtr);

    printf("\n\n\t\tTRANSACCIÓN COMPLETADA SATISFACTORIAMENTE");
    printf("\n\t\tPor favor, recoja su voucher.\n\n\t\tPresione ENTER para continuar: ");
    pausa();
    return 0;

}

void consultaSaldo(Cliente dCliente){
    limpiarPantalla();
    cabeceraCajero();
    FILE *vfPtr;
    char archV[31] = "./VOUCHERS/voucher";
    struct tm *tiempo;
    time_t tiempoActual;
    printf("\n\t\tCajero%d\n\n", idCajero);
    printf("\t\tSu saldo es: %.2f\n", dCliente.saldo);
    printf("\n\n\n\t\tPor favor, recoja su voucher\n\n\t\tPresione ENTER para continuar: ");

    //IMPRIMIR VOUCHER SALDO

    tiempoActual = time(NULL);
    tiempo = localtime(&tiempoActual);
    strcat(archV, dCliente.numTarjeta);
    strcat(archV, ".txt");

    if((vfPtr = fopen(archV, "wt")) == NULL) {
        printf("\n\tError al abrir el archivo voucher. Presione ENTER para continuar: ");
        pausa();
        return;
    }
    fprintf(vfPtr, "CLIENTE: ");
    fprintf(vfPtr, "%s %s\n", dCliente.nombres, dCliente.apellidos);
    fprintf(vfPtr, "LUGAR: CAJERO %d\n", idCajero);
    fprintf(vfPtr, "FECHA: ");
    fprintf(vfPtr, "%.2d/%.2d/%.2d", tiempo->tm_mday,
                                     tiempo->tm_mon + 1,
                                    (tiempo->tm_year + 1900) % 2000); //Fecha
    fprintf(vfPtr, " HORA: ");
    fprintf(vfPtr, "%.2d:%.2d", tiempo->tm_hour,
                                 tiempo->tm_min);                     //Hora
    fprintf(vfPtr, "\n---------------------------\n");
    fprintf(vfPtr, "SALDO ACTUAL: S./");
    fprintf(vfPtr, "%.2f\n", dCliente.saldo);
    fprintf(vfPtr, "---------------------------");

    fclose(vfPtr);
    pausa();
    return;
}

void consultaMovimientos(Cliente dCliente){
    struct tm *tiempo;
    time_t tiempoActual;
    FILE *mfPtr;
    FILE *vfPtr;
    char archV[31] = "./VOUCHERS/voucher";
    int i, movPtr;
    Movimiento mov;
    movPtr = dCliente.sigMov;
    if((mfPtr = fopen(dCliente.archMov, "rb")) == NULL) {
        printf("\n\tNo se puede abrir el archivo de movimientos. \n\t\tPresione ENTER para continuar: ");
        pausa();
        return;
    }
    //Cabecera Movimientos

    limpiarPantalla();
    cabeceraCajero();

    printf("\nÚLTIMOS DIEZ MOVIMIENTOS:\n\n");

    printf("-------------------------------------------------------------------------------\n");
    printf("|  LUGAR  |   FECHA   |  HORA  | TIPO |  S. ANTERIOR  |   MONTO  |    SALDO   |\n");
    printf("-------------------------------------------------------------------------------\n");

    //IMPRIMIR PRIMERA PARTE VOUCHER
    tiempoActual = time(NULL);
    tiempo = localtime(&tiempoActual);
    strcat(archV, dCliente.numTarjeta);
    strcat(archV, ".txt");

    if((vfPtr = fopen(archV, "wt")) == NULL) {
        printf("\n\tError al abrir el archivo voucher. Presione ENTER para continuar: ");
        pausa();
        return;
    }
    fprintf(vfPtr, "CLIENTE: ");
    fprintf(vfPtr, "%s %s\n", dCliente.nombres, dCliente.apellidos);
    fprintf(vfPtr, "LUGAR: CAJERO %d\n", idCajero);
    fprintf(vfPtr, "FECHA: ");
    fprintf(vfPtr, "%.2d/%.2d/%.2d", tiempo->tm_mday,
                                     tiempo->tm_mon + 1,
                                    (tiempo->tm_year + 1900) % 2000); //Fecha
    fprintf(vfPtr, " HORA: ");
    fprintf(vfPtr, "%.2d:%.2d", tiempo->tm_hour,
                                 tiempo->tm_min);                     //Hora
    fprintf(vfPtr, "\n---------------------------\n");
    fprintf(vfPtr, " ULTIMOS DIEZ MOVIMIENTOS\n\n");
    fprintf(vfPtr, "LUGAR     FECHA      MONTO\n");

    //FIN PRIMERA PARTE
    for(i = 0; i < MAX_MOVIMIENTOS; i++) {
        fseek(mfPtr, sizeof(Movimiento) * movPtr, SEEK_SET);
        fread(&mov, sizeof(Movimiento), 1, mfPtr);
        tiempo = localtime(&mov.fecha);
        if(mov.idCajero != 0) {
            if(mov.idCajero == 5){
                printf("  Central ");
                //CENTRAL VOUCHER
                fprintf(vfPtr, "CENTRAL   ");
            } else {
                printf("  Cajero%d ", mov.idCajero);
                //CAJERO # VOUCHER
                fprintf(vfPtr, "CAJERO %d  ", mov.idCajero);
            }
            printf("   %.2d/%.2d/%.2d", tiempo->tm_mday,
                                        tiempo->tm_mon + 1,
                                       (tiempo->tm_year + 1900) % 2000); //Fecha
            //FECHA VOUCHER POR CADA MOVIMIENTO
            fprintf(vfPtr, "%.2d/%.2d/%.2d ", tiempo->tm_mday,
                                             tiempo->tm_mon + 1,
                                            (tiempo->tm_year + 1900) % 2000);//IMPRIMIR FECHA EN VOUCHER

            printf("    %.2d:%.2d ", tiempo->tm_hour,
                                     tiempo->tm_min);                     //Hora
            switch(mov.tipoMovimiento){
            case DEPOSITO:
                printf(" Depósito ");
                break;
            case RETIRO:
                printf(" Retiro   ");
                break;
            case ITF:
                printf(" ITF      ");
                break;
            }
            //MONTO TRANSACCION VOUCHER
            fprintf(vfPtr, "%.2f\n", mov.montoTransaccion);

            printf(" %8.2f      %8.2f     %8.2f\n", mov.saldoAnterior,
                                                    mov.montoTransaccion,
                                                    mov.saldoAnterior + mov.montoTransaccion);
        }
        movPtr = (movPtr + 1) % MAX_MOVIMIENTOS;
    }
    //IMPRIMIR EL SALDO ACTUAL AL VOUCHER
    fprintf(vfPtr, "\n");
    fprintf(vfPtr, "SALDO ACTUAL: S./");
    fprintf(vfPtr, "%.2f\n", dCliente.saldo);
    fprintf(vfPtr, "---------------------------");
    //

    printf("-------------------------------------------------------------------------------");
    printf("\n\n\t\tPor favor, recoja su voucher\n\n\t\tPresione ENTER para continuar: ");
    fclose(mfPtr);
    fclose(vfPtr);
    pausa();
}

int cambioClave(Cliente dCliente){
    FILE *cfPtr;
    char contrasenyaActual[5];
    char contrasenya1[5];
    char contrasenya2[5];
    limpiarPantalla();
    cabeceraCajero();
    printf("\n\t\tIngrese su contraseña actual:\n");
    printf("\n\t\t\t");
    fflush(stdin);
    scanf("%4s", contrasenyaActual);
    if(strcmp(dCliente.contrasenya, contrasenyaActual) != 0){
        printf("\n\t\tCONTRASEÑA ERRADA!\n\n\t\tPresione ENTER para continuar: ");
        pausa();
        return 1;
    }
    limpiarPantalla();
    cabeceraCajero();
    printf("\n\t\tIngrese nueva contraseña:\n");
    printf("\n\t\t\t");
    fflush(stdin);
    scanf("%4s", contrasenya1);
    limpiarPantalla();
    cabeceraCajero();
    printf("\n\t\tConfirme la contraseña:\n");
    printf("\n\t\t\t");
    fflush(stdin);
    scanf("%4s", contrasenya2);
    if(strcmp(contrasenya1, contrasenya2) != 0){
        printf("\n\t\tLAS CONTRASEÑAS NO COINCIDEN!\n\n\t\tPresione ENTER para continuar: ");
        pausa();
        return 1;
    }
    sprintf(dCliente.contrasenya, "%s", contrasenya1);
    if((cfPtr = fopen("./CLIENTES/Clientes.dat", "rb+")) == NULL) {
        printf("\n\tNo se puede abrir el archivo de clientes. Presione ENTER para continuar: ");
        pausa();
        return 1;
    }
    fseek(cfPtr, sizeof(Cliente) * (dCliente.numCliente - 1), SEEK_SET);
    fwrite(&dCliente, sizeof(Cliente), 1, cfPtr);
    fclose(cfPtr);
    printf("\n\n\t\tCONTRASEÑA CAMBIADA SATISFACTORIAMENTE.\n\n\t\tPresione ENTER para continuar: ");
    pausa();
    return 0;
}

