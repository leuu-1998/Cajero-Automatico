#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "manejoPantallaC.h"

void cabeceraClientes(void){
    printf("================================================================================");
    printf("\n\t\t\tADMINISTRACION DE CLIENTES\n\n");
    printf("================================================================================");
    return;
}


//FUNCION "limpiarPantalla": detecta si el sistema operativo a usar es windows o linux
//y limpia la consola al ser llamada.

void limpiarPantalla(void){
    if(SO == 5){
        system("clear");
    } else if(SO == 10){
        system("cls");
    }
    return;
}

void pausa(void){
    if(SO == 5) {
        getchar();
    } else if(SO == 10) {
        fflush(stdin);
    }
    getchar();
    return;
}
