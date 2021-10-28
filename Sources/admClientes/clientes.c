#include <stdio.h>
#include <string.h>
#include <time.h>

#include "admClientes.h"
#include "clientes.h"
#include "movimientos.h"
#include "manejoPantallaC.h"

char nTarjetas[16][9] = {"82353007", "82353008", "82353009", "82353010", "82353011",
 "82353012", "82353013", "82353014", "82353015", "82353016", "82353017", "82353018",
 "82353019", "82353020", "82353021", "82353022"};

#define SIZE_nTARJETAS 16

char nClaves[16][9] = {"3007", "3008", "3009", "3010", "3011", "3012", "3013",
 "3014", "3015", "3016", "3017", "3018", "3019", "3020", "3021", "3022"};

int iniClientes(void) {
    int i;
    struct datosCliente enBlanco = {0, "", "", "", "", 0.0, "", 0};
    FILE *cfPtr;
    if((cfPtr = fopen(ARCH_CLIENTES, "wb")) == NULL) {
        printf( "Error al abrir el archivo.\n" );
        return 1;
    }
    for(i = 1; i <= MAX_CLIENTES; i++) {
        fwrite(&enBlanco, sizeof(struct datosCliente), 1, cfPtr);
    }
    fclose(cfPtr);
    return 0;
}

int ingresarListaClientes(struct datosCliente clientes[], int cantidad, FILE *cfPtr) {
    int i;
    char archTarjeta[30];
    struct tarjeta dTarjeta;
    FILE *tfPtr;
    limpiarPantalla();
    cabeceraClientes();
    for(i = 1; i <= cantidad; i++) {

        if(iniMovimientos(clientes[i-1].archMov, clientes[i-1].saldo) == 1) {
            printf("No se puede crear archivo de movimientos del cliente %d\n", clientes[i-1].numCliente);
            return 1;
        }
        clientes[i-1].sigMov++;
        fseek(cfPtr, (clientes[i-1].numCliente - 1) * sizeof(struct datosCliente), SEEK_SET);
        fwrite(&clientes[i-1], sizeof(struct datosCliente), 1, cfPtr);

        sprintf(archTarjeta, ARCH_TARJETAS);
        strcat(archTarjeta, clientes[i-1].numTarjeta);
        strcat(archTarjeta, ".dat");
        if((tfPtr = fopen(archTarjeta, "wb")) == NULL) {
            printf( "Error al abrir el archivo.\n" );
            return 1;
        }
        dTarjeta.numCliente = clientes[i-1].numCliente;
        sprintf(dTarjeta.numTarjeta, "%s", clientes[i-1].numTarjeta);
        sprintf(dTarjeta.nombres, "%s", clientes[i-1].nombres);
        sprintf(dTarjeta.apellidos, "%s", clientes[i-1].apellidos);
        fwrite(&dTarjeta, sizeof(struct tarjeta), 1, tfPtr);
        fclose(tfPtr);
    }
    return 0;
}

int ingresarCliente(FILE *fPtr) {
    struct datosCliente cliente = {0,"", "", "", "", 0.0, "", 0};
    int i = 0;
    int nCliente;
    char archTarjeta[30];
    struct tarjeta dTarjeta;
    FILE *tfPtr;
    limpiarPantalla();
    cabeceraClientes();
    printf( "\n\t\tIngresar nuevo número de cliente ( 1 - %d ): ", MAX_CLIENTES);
    fflush(stdin);
    scanf("%d", &nCliente);
    fseek(fPtr, (nCliente - 1) * sizeof(struct datosCliente), SEEK_SET);
    fread(&cliente, sizeof(struct datosCliente), 1, fPtr);
    if(cliente.numCliente != 0) {
        printf("\n\tNumero de cliente %d ya contiene informacion. Presione ENTER: ", cliente.numCliente);
        pausa();
        return 1;
    }
    printf("\n\t\tIngrese nombre, apellido y saldo: ");
    scanf("%s%s%f", cliente.nombres, cliente.apellidos, &cliente.saldo);
    while (strcmp(nTarjetas[i], "") == 0) {
        i++;
    }
    sprintf(cliente.numTarjeta, "%s", nTarjetas[i]);
    nTarjetas[i][0] = 0;
    sprintf(cliente.contrasenya, "%s", nClaves[i]);
    nClaves[i][0] = 0;
    sprintf(cliente.archMov, "./MOVIMIENTOS/mov%.2d.dat", nCliente);
    if(iniMovimientos(cliente.archMov, cliente.saldo) == 1) {
        printf("\n\tNo se puede crear archivo de movimientos del cliente %d\n", cliente.numCliente);
        return 1;
    }
    cliente.numCliente = nCliente;
    cliente.sigMov++;
    fseek(fPtr, (nCliente - 1) * sizeof(struct datosCliente), SEEK_SET);
    fwrite(&cliente, sizeof(struct datosCliente), 1, fPtr);

    sprintf(archTarjeta, ARCH_TARJETAS);
    strcat(archTarjeta, cliente.numTarjeta);
    strcat(archTarjeta, ".dat");
    if((tfPtr = fopen(archTarjeta, "wb")) == NULL) {
        printf( "Error al abrir el archivo.\n" );
        return 1;
    }
    dTarjeta.numCliente = cliente.numCliente;
    sprintf(dTarjeta.numTarjeta, "%s", cliente.numTarjeta);
    sprintf(dTarjeta.nombres, "%s", cliente.nombres);
    sprintf(dTarjeta.apellidos, "%s", cliente.apellidos);
    fwrite(&dTarjeta, sizeof(struct tarjeta), 1, tfPtr);
    fclose(tfPtr);
    printf("\n\t\tNuevo cliente creado satisfactoriamente. Presione ENTER: ");
    pausa();
    return 0;
}

int borrarCliente(FILE *fPtr) {
    struct datosCliente enBlanco = {0, "", "", "", "", 0.0, "", 0};
    struct datosCliente cliente;
    int nCliente;
    limpiarPantalla();
    cabeceraClientes();
    printf( "\n\t\tIngresar numero de cliente a borrar ( 1 - %d ): ", MAX_CLIENTES);
    fflush(stdin);
    scanf("%d", &nCliente);
    fseek(fPtr, (nCliente - 1) * sizeof(struct datosCliente), SEEK_SET);
    fread(&cliente, sizeof(struct datosCliente), 1, fPtr);
    if(cliente.numCliente == 0) {
        printf("\n\t\tNumero de cliente %d no existe. Presione ENTER: ", nCliente);
        pausa();
        return 1;
    }
    fseek(fPtr, (nCliente - 1) * sizeof(struct datosCliente), SEEK_SET);
    fwrite(&enBlanco, sizeof(struct datosCliente), 1, fPtr);
    printf("\n\t\tCliente %d borrado. Presione ENTER: ", nCliente);
    pausa();
    return 0;
}

int actualizarCliente(FILE *fPtr) {
    struct datosCliente cliente = {0, "", "", "", "", 0.0, "", 0};
    int nCliente;
    double transaccion;
    printf( "Ingresar numero de cliente a actualizar ( 1 - %d ): ", MAX_CLIENTES);
    fflush(stdin);
    scanf("%d", &nCliente);
    fseek(fPtr, (nCliente - 1) * sizeof(struct datosCliente), SEEK_SET);
    fread(&cliente, sizeof(struct datosCliente), 1, fPtr);
    if(cliente.numCliente == 0) {
        printf("Numero de cliente %d no contiene informacion\n", cliente.numCliente);
        return 1;
    }
    printf("%-8d%-16s%-16s%10.2f\n", cliente.numCliente, cliente.nombres,
                                     cliente.apellidos, cliente.saldo);
    printf( "Ingresar deposito (+) o retiro (-): ");
    fflush(stdin);
    scanf("%lf", &transaccion);
    cliente.saldo += transaccion;
    printf("%-8d%-16s%-16s%10.2f\n", cliente.numCliente, cliente.nombres,
                                     cliente.apellidos, cliente.saldo);
    fseek(fPtr, (nCliente - 1) * sizeof(struct datosCliente), SEEK_SET);
    fwrite(&cliente, sizeof(struct datosCliente), 1, fPtr);
    return 0;
}

void mostrarClientes(FILE *fPtr) {
    int i;
    struct datosCliente cliente = {0, "", "", "", "", 0.0, "", 0};
    rewind(fPtr);
    printf("\n\t\t\tLISTA DE CLIENTES POR DEFECTO\n");
    printf("\n\t%-8s%-12s%-6s%-16s%-16s%10s\n", "Cliente", "Tarjeta", "Clave", "Nombre", "Apellido", "Saldo");
    printf("\t--------------------------------------------------------------------\n");
    for(i = 1;i <= MAX_CLIENTES; i++) {
        fread(&cliente, sizeof(struct datosCliente), 1, fPtr);
        if(cliente.numCliente != 0) {
            printf("\t%-8d%-12s%-6s%-16s%-16s%10.2f\n", cliente.numCliente, cliente.numTarjeta,
                   cliente.contrasenya, cliente.nombres,cliente.apellidos, cliente.saldo);
        }
    }
    printf("\n\t\tLista de Clientes inicializada. Presione ENTER: ");
    fflush(stdin);
    pausa();
    return;
}

