Cajero Autom�tico V2:

-Se dividi� el programa en varios .c y .h (sources)
-Hay 2 carpetas, la primera es "admClientes" que tiene todas las funcionalidades de crear clientes, inicializar, etc.

Para compilar en linux:
-Van con el explorador a la carpeta "admClientes", una vez all� dan SHIFT + click derecho en una parte vac�a de esa carpeta
y les aparecer� la opci�n "Abrir terminal aqu�". Le dan click y les abrir� el terminal en esa carpeta.

-Luego ponen este comando: gcc \*.c -lm -o admClientes

Si lo compilaron bien, les aparecer� el ejecutable. Lo pasan a la carpeta "Cajero" anterior a la carpeta actual.

La segunda carpeta "CajeroFinal" tiene todos los archivos fuente del cajero.

Para compilar en linux:
-Van con el explorador a la carpeta "CajeroFinal", una vez all� dan SHIFT + click derecho en una parte vac�a de esa carpeta
y les aparecer� la opci�n "Abrir terminal aqu�". Le dan click y les abrir� el terminal en esa carpeta.

-Luego ponen este comando: gcc \*.c -lm -o CajeroFinal

Si lo compilaron bien, les aparecer� el ejecutable. Lo pasan a la carpeta "Cajero" anterior a la carpeta actual.

Pueden ver la imagen "ClientesDefault" Para saber los datos respectivos de cada cliente por default.

PD: borrarBD te borra todos los archivos de tarjetas, movimientos, clientes y vouchers(Solo funciona en windows)
PD2: Si quieres inicializar a default los clientes, utilizas el "admClientes" en la opcion "inicializar lista de clientes".
PD3: Si quieren ver los vouchers que se imprimen, van a la carpeta "VOUCHERS"
