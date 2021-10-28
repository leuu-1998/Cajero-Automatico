#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

#include "cajero.h"
#include "identificacion.h"
#include "operaciones.h"
#include "menus.h"
#include "manejoPantalla.h"


int main(void){
    setlocale(LC_ALL, "spanish"); //Permite imprimir carácteres de español(tildes, "ñ")
    int opcion;
    FILE *cfPtr;
    Tarjeta datosTarjeta;
    Cliente datosCliente;
    while((opcion = menuCajero()) != 0){
        switch(opcion){
        case 1:
            idCajero = 1;
            break;
        case 2:
            idCajero = 2;
            break;
        case 3:
            idCajero = 3;
            break;
        case 4:
            idCajero = 4;
            break;
        default:
            idCajero = 0;
            printf("\n\tEscoja una opción valida! Presione ENTER para continuar: ");
            pausa();
        }
        if(idCajero == 0){
            continue;
        }
        datosTarjeta = ingresarTarjeta();
        if(datosTarjeta.numCliente == 0){
            continue;
        }
        datosCliente = validarDatos(datosTarjeta);
        if(datosCliente.numCliente == 0){
            continue;
        }
        while((opcion = menuOperacion()) != 0){
            if((cfPtr = fopen("./CLIENTES/Clientes.dat", "rb")) == NULL) {
                printf("\n\tNo se puede abrir el archivo de clientes. Presione ENTER para continuar: ");
                pausa();
                continue;
            }
            fseek(cfPtr, sizeof(Cliente) * (datosCliente.numCliente - 1), SEEK_SET);
            fread(&datosCliente, sizeof(Cliente), 1, cfPtr);
            fclose(cfPtr);
            switch(opcion){
            case 1:
                retiro(datosCliente);
                break;
            case 2:
                deposito(datosCliente);
                break;
            case 3:
                consultaSaldo(datosCliente);
                break;
            case 4:
                consultaMovimientos(datosCliente);
                break;
            case 5:
                cambioClave(datosCliente);
                break;
            default:
                printf("\n\n\tEscoja una opción válida! Presione ENTER para continuar: ");
                pausa();
            }
        }
    }
    limpiarPantalla();
    return 0;
}
