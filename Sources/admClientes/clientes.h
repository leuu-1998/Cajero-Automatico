#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#define ARCH_CLIENTES "./CLIENTES/Clientes.dat"
#define ARCH_TARJETAS "./TARJETAS/T"

struct datosCliente {
    int numCliente;
    char numTarjeta[9];
    char contrasenya[5];
    char nombres[31];
    char apellidos[31];
    float saldo;
    char archMov[31];
    int sigMov;
};

struct tarjeta {
    int numCliente;
    char numTarjeta[9];
    char nombres[31];
    char apellidos[31];
};

int iniClientes(void);
int ingresarListaClientes(struct datosCliente[], int, FILE *);

int funcionCliente(void);
int ingresarCliente(FILE *);
int borrarCliente(FILE *);
int actualizarCliente(FILE *);
void mostrarClientes(FILE *);

#endif // CLIENTES_H_INCLUDED
