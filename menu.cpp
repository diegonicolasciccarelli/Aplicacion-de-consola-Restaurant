#include <iostream>
#include <windows.h>
using namespace std;
#include "Menu.h"
#include "fecha.h"
#include "ui.h"
#include "rlutil.h"
#include "plato.h"
#include "trabajador.h"
#include "venta.h"
#include "detalleVenta.h"
#include "cliente.h"
#include "informes.h"
#include "configuraciones.h"

bool AjustarVentana(int Ancho, int Alto) {
	_COORD Coordenada;
	Coordenada.X = Ancho;
	Coordenada.Y = Alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = Ancho - 1;
	Rect.Bottom = Alto - 1;

	// Obtener el handle de la consola
	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajustar el buffer al nuevo tamaño
	SetConsoleScreenBufferSize(hConsola, Coordenada);

	// Cambiar tamaño de consola a lo especificado en el buffer
	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
	return TRUE;
}

void coloresPrograma()
{
    rlutil::setBackgroundColor(rlutil::DARKGREY);
    rlutil::setColor(rlutil::WHITE);
}
void colorError()
{
    rlutil::setBackgroundColor(rlutil::RED);
    cout << "Ha ocurrido un error. Vuelta a intentarlo." << endl;
    coloresPrograma();
    Pausa();
}
void colorCorrecto()
{
 rlutil::setBackgroundColor(rlutil::LIGHTGREEN);
 cout << "Accion completada correctamente." << endl;
 coloresPrograma();

}
void Pausa()
{
system("pause>nul");
}
void LimpiarPantalla() /// systemcls
{
    system("cls");
}
void entradaIncorrecta() /// Mensaje default para el usuario cuando ingresa mal una opcion de menu
{
    colorError();
    cout << "Entrada incorrecta. Por favor eliga una opcion que se encuentre listada en el menu.";
    system("pause>nul");
}
void lihoCarta(){
cout << "====================================================================\n";
}

void liho(int cant){
int x=0;

for(x; x<cant; x++)
{
    cout << "=";
}
}
void barraVertical(int a, int b, int columna){
gotoxy(a,columna);
cout << "|";
gotoxy(b,columna);
cout << "|";
}

void barraVerticalCarta(int a, int b,int c, int d, int e, int columna){
gotoxy(a,columna);
cout << "|";
gotoxy(b,columna);
cout << "|";
gotoxy(c,columna);
cout << "|";
gotoxy(d,columna);
cout << "|";
gotoxy(e,columna);
cout << "|";

}





void recuadroPlato(int x, int y, int ancho, int alto)
{
    for (int i = x; i <= x + ancho; i++)
    {
        gotoxy(i,y);
        cout << "*";
    }

    for (int i = y; i <= y + alto; i++)
    {
        gotoxy(x, i);
        cout << "*";
        gotoxy(x+ancho, i);
        cout << "*";
    }

    for (int i = x; i <= x + ancho; i++)
    {
        gotoxy(i,y+alto);
        cout << "*";
    }
}




void mostrarMenuClientes() ///  Print del main
{

    MostrarFechaLocal();
    rlutil::locate(0,8);
    cout << "--------------\n";
    rlutil::locate(0,9);
    cout << "MENU DE CLIENTES\n";
    rlutil::locate(0,10);
    cout << "--------------\n";
    rlutil::locate(0,11);
    cout << "1) REGISTRAR UN CLIENTE\n";
    rlutil::locate(0,12);
    cout << "2) MOSTRAR LOS DATOS DE UN CLIENTE\n";
    rlutil::locate(0,13);
    cout << "3) MOSTRAR TODOS LOS CLIENTES \n";
    rlutil::locate(0,14);
    cout << "4) DAR DE BAJA UN CLIENTE\n";
    rlutil::locate(0,15);
    cout << "5) DAR DE ALTA UN CLIENTE\n";
    rlutil::locate(0,16);
    cout << "--------------\n";
    rlutil::locate(0,17);
    cout << "0) VOLVER AL MENU PRINCIPAL\n";
    rlutil::locate(0,18);
    cout << "Ingrese el numero de la opcion deseada: \n";
}

int entradaMenuClientes() /// Ingreso del main
{
    Cliente cliente;

    int opcion;
    cin >> opcion;
    switch (opcion)
    {
        case 1:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            cliente.cargar();
            Pausa();
        break;
        case 2:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            cliente.leerArchivo();
            gotoxy(9,19);
            colorCorrecto();
            Pausa();

        break;
        case 3:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            mostrarClientes(1);
            Pausa();
        break;
        case 4:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            dardeBajaCliente();
            Pausa();
        break;
        case 5:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            dardeAltaCliente();
            Pausa();
        break;
        case 0:
            colorCorrecto();
            Pausa();
        break;
        default:
        entradaIncorrecta();
        break;
    }
    return opcion;
}


void menuClientes() /// Main
{

    int input = -1;
    while (input != 0)
    {
        coloresPrograma();
        LimpiarPantalla();
        mostrarMenuClientes();
        input = entradaMenuClientes();
    }
    return;
}






void menuPlatos() /// Main
{

    int input = -1;
    while (input != 0)
    {
        coloresPrograma();
        LimpiarPantalla();
        mostrarMenuPlatos();
        input = entradaMenuPlatos();
    }
    return;
}

void mostrarMenuPlatos() ///  Print del main
{

    MostrarFechaLocal();
    rlutil::locate(0,8);
    cout << "--------------\n";
    rlutil::locate(0,9);
    cout << "MENU DE PLATOS\n";
    rlutil::locate(0,10);
    cout << "--------------\n";
    rlutil::locate(0,11);
    cout << "1) INGRESAR UN PLATO\n";
    rlutil::locate(0,12);
    cout << "2) MOSTRAR UN PLATO\n";
    rlutil::locate(0,13);
    cout << "3) CARTA (MOSTRAR TODOS LOS PLATOS) \n";
    rlutil::locate(0,14);
    cout << "4) MODIFICAR UN PLATO\n";
    rlutil::locate(0,15);
    cout << "5) DAR DE BAJA UN PLATO\n";
    rlutil::locate(0,16);
    cout << "6) DAR DE ALTA UN PLATO\n";
    rlutil::locate(0,17);
    cout << "--------------\n";
    rlutil::locate(0,18);
    cout << "0) VOLVER AL MENU PRINCIPAL\n";
    rlutil::locate(0,19);
    cout << "Ingrese el numero de la opcion deseada: \n";
}

int entradaMenuPlatos() /// Ingreso del main
{
    Plato plato;
    int opcion;
    cin >> opcion;

    switch (opcion)
    {
        case 1:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            plato.cargar();
        break;
        case 2:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            plato.leerArchivo();
            Pausa();
        break;
        case 3:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            LimpiarPantalla();
            mostrarCarta();
        break;
        case 4:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            LimpiarPantalla();
            modificarPlatoPorId();
            Pausa();
        break;
        case 5:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            LimpiarPantalla();
            dardeBajaPlato();
            Pausa();
        break;
        case 6:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            LimpiarPantalla();
            dardeAltaPlato();
            Pausa();
        break;
        case 0:
            colorCorrecto();
            Pausa();
        break;
        default:

        entradaIncorrecta();
        break;
    }
    return opcion;
}


void menuTrabajadores() /// Main
{

    int input = -1;
    while (input != 0)
    {
        coloresPrograma();
        LimpiarPantalla();
        mostrarMenuTrabajadores();
        input = entradaMenuTrabajadores();
    }
    return;
}

void mostrarMenuTrabajadores() ///  Print del main
{

    MostrarFechaLocal();
    rlutil::locate(0,8);
    cout << "--------------\n";
    rlutil::locate(0,9);
    cout << "MENU DE TRABAJADORES\n";
    rlutil::locate(0,10);
    cout << "--------------\n";
    rlutil::locate(0,11);
    cout << "1) REGISTRAR UN TRABAJADOR\n";
    rlutil::locate(0,12);
    cout << "2) MOSTRAR LOS DATOS DE UN TRABAJADOR\n";
    rlutil::locate(0,13);
    cout << "3) MOSTRAR TODOS LOS TRABAJADORES \n";
    rlutil::locate(0,14);
    cout << "4) DAR DE BAJA UN TRABAJADOR\n";
    rlutil::locate(0,15);
    cout << "5) DAR DE ALTA UN TRABAJADOR\n";
    rlutil::locate(0,16);
    cout << "--------------\n";
    rlutil::locate(0,17);
    cout << "0) VOLVER AL MENU PRINCIPAL\n";
    rlutil::locate(0,18);
    cout << "Ingrese el numero de la opcion deseada: \n";
}

int entradaMenuTrabajadores() /// Ingreso del main
{
    Trabajador trabajador;
    int opcion;
    cin >> opcion;
    switch (opcion)
    {
        case 1:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            trabajador.cargar();
        break;
        case 2:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            trabajador.leerArchivo();
            Pausa();
        break;
        case 3:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            mostrarTrabajadores(1);
            Pausa();
        break;
        case 4:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            dardeBajaTrabajador();
            Pausa();
        break;
        case 5:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            dardeAltaTrabajador();
            Pausa();
        break;
        case 0:
            colorCorrecto();
        break;
        default:

        entradaIncorrecta();
        break;
    }
    return opcion;
}


void menuVentas() /// Main
{

    int input = -1;
    while (input != 0)
    {
        coloresPrograma();
        LimpiarPantalla();
        mostrarMenuVentas();
        input = entradaMenuVentas();
    }
    return;
}

void mostrarMenuVentas() ///  Print del main
{

    MostrarFechaLocal();
    rlutil::locate(0,8);
    cout << "--------------\n";
    rlutil::locate(0,9);
    cout << "MENU DE VENTAS\n";
    rlutil::locate(0,10);
    cout << "--------------\n";
    rlutil::locate(0,11);
    cout << "1) REGISTRAR UNA VENTA\n";
    rlutil::locate(0,12);
    cout << "2) MOSTRAR LOS DATOS DE UNA VENTA\n";
    rlutil::locate(0,13);
    cout << "3) MOSTRAR TODAS LOS VENTAS \n";
    rlutil::locate(0,14);
    cout << "4) MOSTRAR LAS VENTAS CON DELIVERY \n";
    rlutil::locate(0,15);
    cout << "5) MOSTRAR LAS VENTAS EN LOCAL\n";
    rlutil::locate(0,16);
    cout << "6) MODIFICAR VENTA POR ID\n";
    rlutil::locate(0,17);
    cout << "--------------\n";
    rlutil::locate(0,18);
    cout << "0) VOLVER AL MENU PRINCIPAL\n";
    rlutil::locate(0,19);
    cout << "Ingrese el numero de la opcion deseada: \n";
}

int entradaMenuVentas() /// Ingreso del main
{
    Venta venta;


    int opcion;
    cin >> opcion;
    switch (opcion)
    {
        case 1:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            venta.cargar();
            Pausa();
        break;
        case 2:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            mostrarTodoUnDetalle();
            Pausa();
        break;
        case 3:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            venta.mostrarVentas();
            Pausa();
        break;
        case 4:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            mostrarDelivery();
            Pausa();
        break;
        case 5:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            mostrarLocal();
            Pausa();
        break;
         case 6:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            modificarVentaPorId();
            Pausa();
        break;
        case 0:
            colorCorrecto();
            Pausa();
        break;
        default:

        entradaIncorrecta();
        break;
    }
    return opcion;
}

void menuInformes() /// Main
{

    int input = -1;
    while (input != 0)
    {
        coloresPrograma();
        LimpiarPantalla();
        mostrarMenuInformes();
        input = entradaMenuInformes();
    }
    return;
}

void mostrarMenuInformes() ///  Print del main
{

    MostrarFechaLocal();
    rlutil::locate(0,8);
    cout << "--------------\n";
    rlutil::locate(0,9);
    cout << "MENU DE INFORMES\n";
    rlutil::locate(0,10);
    cout << "--------------\n";
    rlutil::locate(0,11);
    cout << "1) VER RECAUDACION ANUAL\n";
    rlutil::locate(0,12);
    cout << "2) VER RECAUDACION MENSUAL\n";
    rlutil::locate(0,13);
    cout << "3) MOSTRAR VENTAS REALIZADAS EN LOCAL O DELIVERY \n";
    rlutil::locate(0,14);
    cout << "4) MOSTRAR VENTAS POR ID DE TRABAJADOR \n";
    rlutil::locate(0,15);
    cout << "5) MOSTRAR VENTAS SEGUN TIPO DE PLATO\n";
    rlutil::locate(0,16);
    cout << "6) MOSTRAR VENTAS SEGUN ID DE PLATO\n";
    rlutil::locate(0,16);
    cout << "7) MOSTRAR VENTAS REALIZADAS EN CENA O ALMUERZO\n";
    rlutil::locate(0,17);
    cout << "8) MOSTRAR COMPARATIVAS\n";
    rlutil::locate(0,17);
    cout << "--------------\n";
    rlutil::locate(0,18);
    cout << "0) VOLVER AL MENU PRINCIPAL\n";
    rlutil::locate(0,19);
    cout << "Ingrese el numero de la opcion deseada: \n";
}

int entradaMenuInformes() /// Ingreso del main
{

    int opcion;
    cin >> opcion;
    switch (opcion)
    {
        case 1:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            buscarVentasAnual();
        break;
        case 2:
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            buscarVentasMensual();
            Pausa();
        break;
        case 3:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            LimpiarPantalla();
            buscarVentasPorTipo();
            Pausa();
        break;
        case 4:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            LimpiarPantalla();
            buscarVentasPorIdTrabajador();
            Pausa();

        break;
        case 5:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            LimpiarPantalla();
            buscarVentasxTipoPlato();
            Pausa();
            break;
        case 6:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            LimpiarPantalla();
            importetotalxplato();
            Pausa();
        break;
        case 7:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            LimpiarPantalla();
            buscarVentasPorHorario();
            Pausa();
        break;
        case 8:
            colorCorrecto();
            coloresPrograma();
            Pausa();
            LimpiarPantalla();
            comparativaTotal();
            Pausa();
        break;
        case 0:
            colorCorrecto();
            Pausa();
        break;
        default:

        entradaIncorrecta();
        break;
    }
    return opcion;
}

//////////////////////////////////////////////////////

void mostrarmenuGuardarBackups() ///  Print del main
{

    MostrarFechaLocal();
    rlutil::locate(0,8);
    cout << "--------------\n";
    rlutil::locate(0,9);
    cout << "MENU DE CONFIGURACION\n";
    rlutil::locate(0,10);
    cout << "--------------\n";
    rlutil::locate(0,11);
    cout << "1) GUARDAR EL ARCHIVO .DAT DE PLATO EN UN ARCHIVO .BKP\n";
    rlutil::locate(0,12);
    cout << "2) GUARDAR EL ARCHIVO .DAT DE PERSONA EN UN ARCHIVO .BKP\n";
    rlutil::locate(0,13);
    cout << "3) GUARDAR EL ARCHIVO .DAT DE CLIENTE EN UN ARCHIVO .BKP\n";
    rlutil::locate(0,14);
    cout << "4) GUARDAR EL ARCHIVO .DAT DE TRABAJADOR EN UN ARCHIVO .BKP\n";
    rlutil::locate(0,15);
    cout << "5) GUARDAR EL ARCHIVO .DAT DE VENTA EN UN ARCHIVO .BKP\n";
    rlutil::locate(0,16);
    cout << "6) GUARDAR EL ARCHIVO .DAT DE DETALLE VENTA EN UN ARCHIVO .BKP\n";
    rlutil::locate(0,17);
    cout << "--------------\n";

    cout << "0) VOLVER AL MENU PRINCIPAL\n";
    rlutil::locate(0,19);
    cout << "Ingrese el numero de la opcion deseada: \n";
}

int entradamenuGuardarBackups()
{
    int opcion;
    cin >> opcion;
    switch (opcion)
    {
        case 1:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            guardarBackupPlato();
            LimpiarPantalla();
            cout << "Se guardaron con exito los datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 2:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            guardarBackupPersona();
            LimpiarPantalla();
            cout << "Se guardaron con exito los datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 3:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            guardarBackupCliente();
            LimpiarPantalla();
            cout << "Se guardaron con exito los datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 4:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            guardarBackupTrabajador();
            LimpiarPantalla();
            cout << "Se guardaron con exito los datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 5:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            guardarBackupVenta();
            LimpiarPantalla();
            cout << "Se guardaron con exito los datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 6:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            guardarBackupdetalleVenta();
            LimpiarPantalla();
            cout << "Se guardaron con exito los datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 0:
        break;
        default:
        colorError();

        break;
    }
    return opcion;
}


void menuGuardarBackups() /// Main
{

    int input = -1;
    while (input != 0)
    {
        coloresPrograma();
        LimpiarPantalla();
        mostrarmenuGuardarBackups();
        input = entradamenuGuardarBackups();
    }
    return;
}

void mostrarmenuCargarBackups() ///  Print del main
{

    MostrarFechaLocal();
    rlutil::locate(0,8);
    cout << "--------------\n";
    rlutil::locate(0,9);
    cout << "MENU DE CONFIGURACION\n";
    rlutil::locate(0,10);
    cout << "--------------\n";
    rlutil::locate(0,11);
    cout << "1) RECUPERAR EL ARCHIVO .DAT DE PLATO\n";
    rlutil::locate(0,12);
    cout << "2) RECUPERAR EL ARCHIVO .DAT DE PERSONA\n";
    rlutil::locate(0,13);
    cout << "3) RECUPERAR EL ARCHIVO .DAT DE CLIENTE\n";
    rlutil::locate(0,14);
    cout << "4) RECUPERAR EL ARCHIVO .DAT DE TRABAJADOR\n";
    rlutil::locate(0,15);
    cout << "5) RECUPERAR EL ARCHIVO .DAT DE VENTA\n";
    rlutil::locate(0,16);
    cout << "6) RECUPERAR EL ARCHIVO .DAT DE DETALLE VENTA\n";
    rlutil::locate(0,17);
    cout << "--------------\n";

    cout << "0) VOLVER AL MENU PRINCIPAL\n";
    rlutil::locate(0,19);
    cout << "Ingrese el numero de la opcion deseada: \n";
}

int entradamenuCargarBackups()
{
    int opcion;
    cin >> opcion;
    switch (opcion)
    {
        case 1:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            cargarBackupPlato();
            cout << "Se realizo con exito la recuperacion de datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 2:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            cargarBackupPersona();
            LimpiarPantalla();
            cout << "Se realizo con exito la recuperacion de datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 3:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            cargarBackupCliente();
            LimpiarPantalla();
            cout << "Se realizo con exito la recuperacion de datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 4:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            cargarBackupTrabajador();
            LimpiarPantalla();
            cout << "Se realizo con exito la recuperacion de datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 5:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            cargarBackupVenta();
            LimpiarPantalla();
            cout << "Se realizo con exito la recuperacion de datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 6:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            cargarBackupdetalleVenta();
            LimpiarPantalla();
            cout << "Se realizo con exito la recuperacion de datos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 0:
        break;
        default:
            colorError();
        break;
    }
    return opcion;
}

void menuCargarBackups() /// Main
{

    int input = -1;
    while (input != 0)
    {
        coloresPrograma();
        LimpiarPantalla();
        mostrarmenuCargarBackups();
        input = entradamenuCargarBackups();
    }
    return;
}

void mostrarMenuConfiguracion() ///  Print del main
{

    MostrarFechaLocal();
    rlutil::locate(0,8);
    cout << "--------------\n";
    rlutil::locate(0,9);
    cout << "MENU DE CONFIGURACION\n";
    rlutil::locate(0,10);
    cout << "--------------\n";
    rlutil::locate(0,11);
    cout << "1) HACER BACKUPS DE LOS ARCHIVOS INDIVIDUALMENTE\n";
    rlutil::locate(0,12);
    cout << "2) HACER RECUPERACION DE DATOS INDIVIDUALMENTE\n";
    rlutil::locate(0,13);
    cout << "3) HACER TODOS LOS BACKUPS DE LOS ARCHIVOS\n";
    rlutil::locate(0,14);
    cout << "4) HACER RECUPERACION DE TODOS LOS DATOS\n";
    rlutil::locate(0,15);
    cout << "--------------\n";
    rlutil::locate(0,16);
    cout << "0) VOLVER AL MENU PRINCIPAL\n";
    rlutil::locate(0,17);
    cout << "Ingrese el numero de la opcion deseada: \n";
}

int entradaMenuConfiguracion()
{
    int opcion;
    cin >> opcion;
    switch (opcion)
    {
        case 1:
            colorCorrecto();
            Pausa();
            menuGuardarBackups();
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();

        break;
        case 2:
            colorCorrecto();
            Pausa();
            menuCargarBackups();
            colorCorrecto();
            Pausa();
            coloresPrograma();
            LimpiarPantalla();
            Pausa();
        break;
        case 3:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            guardarTodoslosBackups();
            LimpiarPantalla();
           cout << "Se guardaron con exito los datos de todos los archivos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 4:
            colorCorrecto();
            Pausa();
            codigoSeguridad();
            cargarTodoslosBackups();
            LimpiarPantalla();
            cout << "Se recupero con exito los datos de todos los archivos" << endl;
            colorCorrecto();
            Pausa();
        break;
        case 0:
            colorCorrecto();
            Pausa();
        break;
        default:
            entradaIncorrecta();
        break;
    }
    return opcion;
}

void menuConfiguracion() /// Main
{

    int input = -1;
    while (input != 0)
    {
        coloresPrograma();
        LimpiarPantalla();
        mostrarMenuConfiguracion();
        input = entradaMenuConfiguracion();
    }
    return;
}

//////////////////////////////////////////////////////

void MainMenu() /// Main
{

    int input = -1;
    while (input != 0)
    {
        coloresPrograma();
        LimpiarPantalla();
        mostrarMainMenu();
        input = entradaMainMenu();
    }
    return;
}

void mostrarMainMenu() ///  Print del main
{

    MostrarFechaLocal();
    rlutil::locate(0,8);
    cout << "--------------\n";
    rlutil::locate(0,9);
    cout << "MENU PRINCIPAL\n";
    rlutil::locate(0,10);
    cout << "--------------\n";
    rlutil::locate(0,11);
    cout << "1) PLATOS\n";
    rlutil::locate(0,12);
    cout << "2) VENTAS\n";
    rlutil::locate(0,13);
    cout << "3) CLIENTES\n";
    rlutil::locate(0,14);
    cout << "4) TRABAJADORES\n";
    rlutil::locate(0,15);
    cout << "5) INFORMES\n";
    rlutil::locate(0,15);
    cout << "6) CONFIGURACION\n";
    rlutil::locate(0,16);
    cout << "--------------\n";
    rlutil::locate(0,17);
    cout << "0) SALIR DEL PROGRAMA\n";
    rlutil::locate(0,18);
    cout << "Ingrese el numero de la opcion deseada: \n";
}

int entradaMainMenu() /// Ingreso del main
{
//    initUI();
//    title("", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
//    title("Menu principal", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

    int opcion;
    cin >> opcion;
    switch (opcion)
    {
        case 1:
            colorCorrecto();
            Pausa();
            menuPlatos();
        break;
        case 2:
            colorCorrecto();
            Pausa();
            menuVentas();
        break;
        case 3:
            colorCorrecto();
            Pausa();
            menuClientes();
        break;
        case 4:
            colorCorrecto();
            Pausa();
            menuTrabajadores();
        break;
        case 5:
            colorCorrecto();
            Pausa();
            menuInformes();
        case 0:
            colorCorrecto();
        break;
        case 6:
            colorCorrecto();
            Pausa();
            menuConfiguracion();
        break;
        default:
        colorError();
        break;
    }
    return opcion;
}
