#include <stdio.h>
#include <locale.h>
#include <time.h>

#include "admClientes.h"
#include "clientes.h"
#include "movimientos.h"
#include "manejoPantallaC.h"

struct datosCliente clientes[] =
        {
            { 5, "82353001", "1234", "Humberto", "Alvarez",    3000, "./MOVIMIENTOS/mov05.dat", 0},
            { 2, "82353002", "4321", "Paul",     "Campos",     5300, "./MOVIMIENTOS/mov02.dat", 0},
            {15, "82353003", "9832", "Rocío",    "Silva",      2300, "./MOVIMIENTOS/mov15.dat", 0},
            { 7, "82353004", "1593", "Oscar",    "Romero",     7450, "./MOVIMIENTOS/mov07.dat", 0},
            { 1, "82353005", "3574", "Roberto",  "Sifuentes",  1320, "./MOVIMIENTOS/mov01.dat", 0},
            {12, "82353006", "2579", "Jose",     "Sanchez",    4520, "./MOVIMIENTOS/mov12.dat", 0}
        };

#define SIZE_CLIENTES sizeof(clientes) / sizeof (struct datosCliente)


int menuCliente(void);

int main(void) {
    setlocale(LC_ALL, "spanish");
    FILE *cfPtr;
    if((cfPtr = fopen(ARCH_CLIENTES, "rb+")) == NULL) {
        iniClientes();
    }
    fclose(cfPtr);
    funcionCliente();
    return 0;
}

int funcionCliente(void) {
    int opcion;
    FILE *cfPtr;
    if((cfPtr = fopen(ARCH_CLIENTES, "rb+")) == NULL) {
        printf( "Error al abrir el archivo.\n" );
        return 1;
    }
    while((opcion = menuCliente()) != 0) {
        switch(opcion) {
        case 1:
            iniClientes();
            ingresarListaClientes(clientes, SIZE_CLIENTES, cfPtr);
            mostrarClientes(cfPtr);
            break;
        case 2:
            ingresarCliente(cfPtr);
            break;
        case 3:
            borrarCliente(cfPtr);
            break;
        case 4:
            limpiarPantalla();
            cabeceraClientes();
            mostrarClientes(cfPtr);
            break;
        default:
            printf("Escoja una opcion valida\n");
        }
    }
    limpiarPantalla();
    fclose(cfPtr);
    return 0;
}

int menuCliente(void) {
    int opcion;
    limpiarPantalla();
    cabeceraClientes();
    printf("\n");
    printf("\t\t\t(1) Inicializar lista de clientes\n");
    printf("\t\t\t(2) Ingresar nuevo cliente\n");
    printf("\t\t\t(3) Borrar cliente\n");
    printf("\t\t\t(4) Mostrar lista de clientes\n");
    printf("\t\t\t(0) Salir\n\n\t\t\tIngrese su opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);
    return opcion;
}

