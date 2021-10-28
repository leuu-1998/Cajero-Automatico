#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>

#include "manejoPantalla.h"
#include "cajero.h"
#include "identificacion.h"
#include "operaciones.h"
#include "menus.h"
#include "manejoPantalla.h"

void cabeceraCajero(void){
    printf("================================================================================");
    printf("\n\t\t\tSIMULACION DE CAJERO AUTOMATICO\n\n");
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
