#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#include "rlutil.h"
#include "persona.h"
#include "cliente.h"
#include "menu.h"
#include "plato.h"

const char *FILE_CLIENTE = "./cliente.dat";

Cliente::Cliente(){
    IdCliente = 0;
    Telefono = 0;
    EstadoCliente = true;
}
int Cliente::getIdCliente(){
    return IdCliente;
}
int Cliente::getTelefono(){
    return Telefono;
}
bool Cliente::getEstadoCliente(){
    return EstadoCliente;
}
void Cliente::setIdCliente(int i){
    IdCliente = i;
}
void Cliente::setTelefono(int t){
    Telefono = t;
}
void Cliente::setEstadoCliente(bool e){
    EstadoCliente = e;
}


int asignarIdCliente() /// Asigna un valor autonumerico al Id de cliente
{
    int id = 0;
    FILE* p;
    Cliente cliente;
    p = fopen(FILE_CLIENTE, "rb");
    if (p == NULL)
    {
        return 1;
    }
    while (fread(&cliente, sizeof (Cliente), 1, p))
    {
       id = cliente.getIdCliente();
    }
    id += 1;
    fclose(p);
    return id;
}

int validarTelefono() /// validamos un numero de telefono
{
    int Telefono;
    bool vali = false;
    while (!vali)
    {
        cout << "Telefono : ";
        cin >> Telefono;

        if (Telefono <= 0 || Telefono >= 9999999999 )
        {
            cout << "El Telefono ingresado es invalido. El Telefono debe ser un valor entero positivo, por favor ingreselo nuevamente...\n";
        }
        else{
            vali = true;
        }

    }
    return Telefono;
}

void Cliente::cargar() /// hereda la carga de persona y se realiza la carga de cliente
{
    Persona::cargar();

    setIdCliente(asignarIdCliente());
    setTelefono(validarTelefono());
    setEstadoCliente(1);
    if(deseaContinuar()==false){
        return;
    }
    mostrar();
    escribirArchivo();

}

void Cliente::mostrar()
{

    LimpiarPantalla();
    gotoxy(12,6);
    cout << "\t" << "ID cliente: " << IdCliente;
    Persona::mostrar();
    gotoxy(5,12);
    cout << "\t"<< "Telefono:" << "\t"  << Telefono;
    gotoxy(6,17);
    rlutil::setColor(rlutil::LIGHTGREEN);
    system("pause");
    rlutil::setColor(rlutil::WHITE);
}

void mostrarNombreCliente(int id) /// buscamos en archivo y mostramos el nombre del cliente que lo buscamos por medio del id de cliente que tiene asignado
{
    FILE* p;
    Cliente cliente;
    char str[50];
    p = fopen("./cliente.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while(fread(&cliente, sizeof (Cliente), 1, p)){
        if(id == cliente.getIdCliente()){
            strcpy(str,cliente.getNombre());
           cout << str;
            }
    }
    fclose(p);
}

void mostrarClientes(int estado) /// muestra todos los clientes dados de alta (con estado 1)
{
    FILE* p;
    Cliente cliente;
    int col = 6;
    p = fopen(FILE_CLIENTE, "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }

    cabeceraCliente();
    while(fread(&cliente, sizeof (Cliente), 1, p)){
    if(cliente.getEstadoCliente() == estado){
    gotoxy(2,col);
    cout << cliente.getIdCliente();
    gotoxy(8,col);
    cout << cliente.getNombre();
    cout << " " << cliente.getApellido();
    barraVertical(5, 50, col);
    col++;
    }
    }
    cout << endl;
    liho(50);
    fclose(p);
}

void cabeceraCliente(){
    barraVertical(50, 50, 2);
    gotoxy(1, 1);
    liho(50);
    gotoxy(20, 2);
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "LOS CLIENTES  \n";
    rlutil::setColor(rlutil::WHITE);
    gotoxy(1, 3);
    liho(50);
    gotoxy(2, 4);
    cout << "ID";
    gotoxy(8, 4);
    cout << "NOMBRE Y APELLIDO" << endl;
    liho(50);
    barraVertical(5, 50, 4);

}

void Cliente::leerArchivo() /// ingresa el id que quiere ver y lee el archivo y muestra el cliente
{
    Cliente cliente;
    FILE* p;
    int id;
    cout << "Ingrese el ID de CLIENTE que quisiera visualizar: " << endl;
    cin >> id;
    p = fopen(FILE_CLIENTE, "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        Pausa();
        return;
    }
    while(fread(&cliente, sizeof (Cliente), 1, p)){
        if(id == cliente.IdCliente){
            cliente.mostrar();
        }
    }
}

void Cliente::escribirArchivo() /// guarda los datos del cliente
{
    FILE* p;
    p = fopen(FILE_CLIENTE, "ab");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    fwrite(this, sizeof (Cliente), 1, p);
    colorCorrecto();
    coloresPrograma();
    fclose(p);
    return;
}

//// baja cliente

void dardeBajaCliente() /// llama a las funciones que realizan la baja de cliente
{
    int id;
    if(validamosSiHayClientesAlta()==0){
        return;
    }
    verClientesconAlta();
    id=ClienteExistenteyConAlta();
    if(id==-1){
        return;
    }
    bajarCliente(id);
    colorCorrecto();
}

int validamosSiHayClientesAlta() /// validamos si hay clientes dados de alta asi nos permite realizar la baja, si no lo hay retorna un int y se retorna al menu
{
int cont=0;
    FILE* p;
    Cliente cliente;
    int idArchivo;
    p = fopen("./cliente.dat", "rb");
    if (p == NULL)
    {
        return -1;
    }
    while (fread(&cliente, sizeof (Cliente), 1, p) == 1)
    {
        idArchivo = cliente.getIdCliente();
        if (cliente.getEstadoCliente()==1)
        {
            cont ++;
            fclose(p);
        }
    }
    if (cont==0){
        fclose(p);
        cout << "No hay clientes dados de alta para realizar la baja del mismo, Usted volvera al menu"<< endl;
        return 0;
    }
    return 1;
    fclose(p);
    }

void verClientesconAlta() /// opcion para ver cuales son los clientes con alta para elegir la opcion a dar de baja
{
    char eleccion;
    cout << "Desea ver cuales son los clientes dados de alta o ya conoce el id de cliente que quiere dar de baja? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){
        LimpiarPantalla();
        mostrarClientes(1);
    }
}

int ClienteExistenteyConAlta() /// funcion para ingresar el cliente a dar de baja
{
    int cont=0, id;
    bool vali =false;
    while (vali==false){
        cout << endl;
        cout << "Ingrese el id del cliente que desea dar de baja: ";
        cin >> id;
        if(ExisteIdClienteConAlta(id)== false){

            colorError();
            coloresPrograma();
            vali=false;
            if(deseaContinuar()==false){
                return -1;
            }
        verClientesconAlta();
        } else{
        vali=true;
        }
    }
    return id;
    }

bool ExisteIdClienteConAlta(int id) /// valida si el cliente que ingreso existe y esta con alta
{
    FILE* p;
    Cliente cliente;
    int idArchivo;

    p = fopen("./cliente.dat", "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&cliente, sizeof (Cliente), 1, p) == 1)
    {
        idArchivo = cliente.getIdCliente();
        if (id == idArchivo && cliente.getEstadoCliente()==1)
        {
            fclose(p);
            return true;
        }

    }
    return false;
    fclose(p);
}

void bajarCliente(int id) /// se realiza la baja del cliente luego de todas las validaciones anteriores
{
    FILE* p;
    Cliente cliente;
    bool es = false;
    p = fopen(FILE_CLIENTE, "rb+");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while (fread(&cliente, sizeof (Cliente), 1, p)){
        if (id == cliente.getIdCliente()){
            cliente.setEstadoCliente(es);
            fseek(p, ftell(p) - sizeof (Cliente), 0);
            fwrite(&cliente, sizeof(Cliente), 1, p);
            Pausa();
            fclose(p);
            return;
        }
    }
    fclose(p);
}

///// alta cliente

void dardeAltaCliente() /// llama a las funciones que realizan el alta de cliente
{
    int id;
    if(validamosSiHayClientesBaja()==0){
        return;
    }
    verClientesconBaja();
    id=ClienteExistenteyConbaja();
    if(id==-1){
        return;
    }
    subirCliente(id);
    colorCorrecto();
}

int validamosSiHayClientesBaja() /// validamos si hay clientes dados de baja asi nos permite realizar el alta, si no lo hay retorna un int y se retorna al menu
{
int cont=0;
    FILE* p;
    Cliente cliente;
    int idArchivo;
    p = fopen("./cliente.dat", "rb");
    if (p == NULL)
    {
        return -1;
    }
    while (fread(&cliente, sizeof (Cliente), 1, p) == 1)
    {
        idArchivo = cliente.getIdCliente();
        if (cliente.getEstadoCliente()==0)
        {
            cont ++;
            fclose(p);
        }
    }
    if (cont==0){
        fclose(p);
        cout << "No hay clientes dados de baja para realizar el alta del mismo, Usted volvera al menu"<< endl;
        return 0;
    }
    return 1;
    }

void verClientesconBaja() /// opcion para ver cuales son los clientes con baja para elegir la opcion a dar de alta
{

    char eleccion;

    cout << "Desea ver cuales son los clientes dados de baja o ya conoce el id de cliente que quiere dar de alta? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){
        LimpiarPantalla();
        mostrarClientes(0);
    }
}

int ClienteExistenteyConbaja() /// funcion para ingresar el cliente a dar de alta
{
    int cont=0, id;
    bool vali =false;
    while (vali==false){
        cout << endl;
        cout << "Ingrese el id del cliente que desea dar de alta: ";
        cin >> id;
        if(ExisteIdClienteConBaja(id)== false){

            colorError();
            coloresPrograma();
            vali=false;
            if(deseaContinuar()==false){
                return -1;
            }
            verClientesconBaja();
        } else{
        vali=true;
        }
    }
    return id;
    }

bool ExisteIdClienteConBaja(int id) /// valida si el cliente que ingreso existe y esta con baja
{
    FILE* p;
    Cliente cliente;
    int idArchivo;

    p = fopen("./cliente.dat", "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&cliente, sizeof (Cliente), 1, p) == 1)
    {
        idArchivo = cliente.getIdCliente();
        if (id == idArchivo && cliente.getEstadoCliente()==0)
        {
            fclose(p);
            return true;
        }

    }
    return false;
    fclose(p);
}

void subirCliente(int id) /// se realiza el alta del cliente luego de todas las validaciones anteriores
{

    FILE* p;
    Cliente cliente;
    bool es = true;
    p = fopen(FILE_CLIENTE, "rb+");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while (fread(&cliente, sizeof (Cliente), 1, p)){
        if (id == cliente.getIdCliente()){
            cliente.setEstadoCliente(es);
            fseek(p, ftell(p) - sizeof (Cliente), 0);
            fwrite(&cliente, sizeof(Cliente), 1, p);
            Pausa();
            fclose(p);
            return;
        }
    }
    fclose(p);
}


bool existeIdCliente(int id) /// valida si existe el id cliente y retorna true o false
{
    FILE* p;
    Cliente cliente;
    int idArchivo;
    p = fopen("./cliente.dat", "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&cliente, sizeof (Cliente), 1, p) == 1)
    {
        idArchivo = cliente.getIdCliente();
        if (id == idArchivo)
        {   fclose(p);
            return 1;
        }
    }
    fclose(p);
    return 0;
}


void verIdClientesyNombres() /// muesta los clientes , su numero y nombre de cliente. solo esos datos
{

    char eleccion;

    cout << "Desea ver cuales son los clientes para realizar una asignacion adecuada a la venta? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){
        LimpiarPantalla();
      mostrarClientes(1);
    cout << endl;
    }
}
