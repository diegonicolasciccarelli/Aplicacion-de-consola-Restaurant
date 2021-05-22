#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#include "ui.h"
#include "rlutil.h"
#include "venta.h"
#include "menu.h"
#include "fecha.h"
#include "cliente.h"
#include "trabajador.h"
#include "persona.h"
#include "detalleVenta.h"
#include "plato.h"


const char *FILE_VENTA = "./venta.dat";


Venta::Venta(){
    idVenta = 0;
    idCliente = 0;
    idTrabajador = 0;
    strcpy(formaPago, " Sin pago");
    envio = false;
    importeTotal = 0;
    DiaVenta = 0;
    MesVenta =0;
    AnioVenta =0;
    horarioComida =0;
}


int Venta::getIdVenta(){
    return idVenta;
}
int Venta::getIdCliente(){
    return idCliente;
}
int Venta::getIdTrabajador(){
    return idTrabajador;
}
int Venta::getImporteTotal(){
    return importeTotal;
}
char* Venta::getFormaPago(){
    return formaPago;
}
bool Venta::getEnvio(){
    return envio;
}
int Venta::getDiaVenta(){
    return DiaVenta;
}
int Venta::getMesVenta(){
    return MesVenta;
}
int Venta::getAnioVenta(){
    return AnioVenta;
}
int Venta::getHorarioComida(){
    return horarioComida;
}

void Venta::setIdVenta(int iv){
    idVenta = iv;
}
void Venta::setFormaPago(int fp){
    if (fp == 1){
        strcpy(formaPago, "efectivo");
    }
        else if(fp==2){
            strcpy(formaPago, "credito");
        }   else{
            strcpy(formaPago, "debito");
            }

}
void Venta::setIdCliente(int ic){
    idCliente = ic;
}
void Venta::setImporteTotal(int it){
    importeTotal = it;
}
void Venta::setIdTrabajador(int it){
    idTrabajador = it;
}
void Venta::setDiaVenta(int fv){
    DiaVenta = fv;
}
void Venta::setMesVenta(int fv){
    MesVenta = fv;
}
void Venta::setAnioVenta(int fv){
    AnioVenta = fv;
}
void Venta::setEnvio(bool e){
    envio = e;
}
void Venta::setHorarioComida(int hc){
    horarioComida = hc;
}



int asignarIdVenta() /// Asigna un valor autonumerico al Id de cliente
{
    int id = 0;
    FILE* p;
    Venta venta;
    p = fopen(FILE_VENTA, "rb");
    if (p == NULL)
    {
        return 1;
    }

    while (fread(&venta, sizeof (Venta), 1, p))
    {
       id = venta.getIdVenta();
    }
    id += 1;
    fclose(p);
    return id;
}

int validarIdVenta() /// Valida que el id de venta exista.
{
    bool valida=false;
    int id;
    FILE* p;
    Venta venta;
    p = fopen("./venta.dat", "rb");
    if (p == NULL)
    {
        return 0;
    }
    cout << "Ingrese el ID de la venta que quisiera visualizar: " << endl;
    cin >> id;

    while (fread(&venta, sizeof (Venta), 1, p) == 1)
    {
        if (id == venta.getIdVenta())
        {
            valida=true;
        }
    }

        if (valida==false)
        {
            cout << "El ID de venta no existe, por favor ingrese el id del cliente correspondiente para registrar su venta" << endl;
            colorError();
            if(deseaContinuar()==false){
                fclose(p);
                return-1;
            }
        }
    fclose(p);
    return id;
    }




int validarFormaPagoVenta() /// Verifica que se ingresa una forma de pago valida (1, 2 o 3)
{
    bool vali = true;

    int fp;


    while (vali==true){

    cout << "Ingrese la forma de pago realizada: " << endl;
    cout << "(1) para Efectivo" << endl;
    cout << "(2) para Credito" << endl;
    cout << "(3) para Debito" << endl;
    cin >> fp;

    switch (fp)
    {
            case 1:
                colorCorrecto();
                cout << "Usted eligio efectivo" << endl;
                vali = false;
               break;
            case 2:
                colorCorrecto();
                cout << "Usted eligio credito" << endl;
                vali = false;
                break;
            case 3:
                colorCorrecto();
                cout << "Usted eligio debito" << endl;
                vali = false;
                break;
            default:
                colorError();
                coloresPrograma();
                verOpcionesPago ();
                LimpiarPantalla();
                break;
    }


    }
    return fp;

}

void verOpcionesPago ()  /// Muestra las opciones de forma de pago para ingresarlas en la funcion de arriba
{

    char eleccion;
    cout << "Desea ver las opciones a elegir para el pago y elegir la adecuada? S/N" << endl;
    cin >> eleccion;
    if (eleccion== 'S' || eleccion == 's'){

        cout << "Si su venta fue en efectivo, Ingrese: 1 " << endl;
        cout << "Si su venta fue con credito, Ingrese: 2 " << endl;
        cout << "Si su venta fue con debito, Ingrese: 3 " << endl;
        Pausa();
    }
}


int validarIdClientedeVenta() /// Valida que el ID de cliente que se ingrese sea valido y exista
{

    bool vali = false;

    int id;

    verIdClientesyNombres();
    while (!vali)
    {

        cout << "Ingrese el ID del cliente: \n";
        cin >> id;

        if (id <= 0)
        {
            cout << "El ID de cliente ingresado es invalido. El ID de cliente debe ser un valor entero positivo, por favor ingrese el ID de usuario nuevamente...\n" << endl;
            Pausa();
            LimpiarPantalla();
            mostrarClientes(1);
            cout << endl;
        }
        else if (!existeIdCliente(id)==1)
        {
            cout << "El ID de cliente no existe, por favor ingrese el id del cliente correspondiente para registrar su venta" << endl;
            Pausa();
            LimpiarPantalla();
            mostrarClientes(1);
            cout << endl;
        }
        else
        {
            vali = true;
        }
    }
    colorCorrecto();
    return id;
}

int validarIdTrabajadordeVenta() /// Valida que el ID de trabajador que se ingrese sea valido y exista
{

    bool vali = false;
    int id;

    verIdTrabajadoresyNombres();
    while (!vali)
    {
        cout << "Ingrese el ID del trabajador: \n";
        cin >> id;

        if (id <= 0)
        {
            cout << "El ID de trabajador ingresado es invalido. El ID de trabajador debe ser un valor entero positivo, por favor ingreselo nuevamente...\n";
                LimpiarPantalla();
            mostrarTrabajadores(1);
            cout << endl;
        }
        else if (!existeIdTrabajadorVenta(id)==1)
        {
            cout << "El ID de trabajador no existe, por favor ingrese el id del trabajador correspondiente para registrar su venta";
                LimpiarPantalla();
            mostrarTrabajadores(1);
            cout << endl;
        }
        else
        {
            vali = true;
        }
    }
    colorCorrecto();
    return id;
}

bool existeIdTrabajadorVenta(int id) /// Valida que el id de trabajaor exista. Se usa en la de arriba
{
    FILE* p;
    Trabajador trabajador;
    int idArchivo;
    p = fopen("./trabajador.dat", "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&trabajador, sizeof (Trabajador), 1, p) == 1)
    {
        idArchivo = trabajador.getIdTrabajador();
        if (id == idArchivo)
        {
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return 0;
}


int validarHorarioComida() /// Valida que sea un numero entre 1 y 2
{
    bool vali = false;
    int hc;
    while (!vali){
        cout <<"Se trata de un almuerzo (1) o de una cena (2)?" << endl;
        cin >> hc;

        if (hc >= 1 && hc <= 2){
            vali = true;
            colorCorrecto();
            return hc;
        }
    }
    return 0;
}

bool validarEnvio() /// Valida un bool de envio de la venta
{

    char env;
    cout << "Existio envio en la venta?:  ( S / N )" << endl;
    cin >> env;
    switch(env){
        case 's':
            env = true;
            colorCorrecto();
            break;
        case 'S':
            env = true;
            colorCorrecto();
            break;
        case 'n':
            env = false;
            colorCorrecto();
            break;
        case 'N':
            env = false;
            colorCorrecto();
            break;
        default:
            colorError();
            coloresPrograma();
            verOpcionesEnvio ();
            LimpiarPantalla();
            break;

    }
    return env;
}

void verOpcionesEnvio () /// Muestra las opciones validas para ingresar en el envio
{

    char eleccion;
    cout << "Desea ver las opciones a elegir para el envio y elegir la adecuada? S/N" << endl;
    cin >> eleccion;
    if (eleccion== 'S' || eleccion == 's'){
        cout << "Si su venta fue con envio, Ingrese: S " << endl;
        cout << "Si su venta fue sin envio, Ingrese: N " << endl;
    }
}


void Venta::validarFechaVenta() /// Setea la fecha de una venta, haciendo las validaciones ctes.
{

    bool ValidarFecha=false;

    Fecha fecha;
    cout << "Ingrese la fecha de la venta: " << endl;
    while (ValidarFecha==false){
    ValidarFecha= ValidoAnioVenta(&fecha);
    }
    setDiaVenta(fecha.getDia());
    setMesVenta(fecha.getMes());
    setAnioVenta(fecha.getAnio());
    colorCorrecto();
    cout << endl;
    cout << "Exitosa carga de datos de venta, Presione enter para pasar a la carga de los platos en el detalle de la venta" << endl;
    Pausa();

}

bool ValidoAnioVenta(Fecha *fecha) /// Valida que el año no sea mayor al actual o que la fecha no sea incorrecta
{

    bool ValidarFecha = false;
    int anioActual = ObtenerAnio();
    fecha->cargar();
    if ( fecha->getAnio() < 1920 || validarFecha(fecha)==false){
        cout << "La fecha ingresada es una fecha invalida, por favor ingresela nuevamente...\n";
    }
    else if (validarFecha(fecha)==false)
    {
        cout << "La fecha ingresada es una fecha invalida, por favor ingresela nuevamente...\n";
    }
    else if (fecha->getAnio() > anioActual)
    {
        cout << "La fecha ingresada es una fecha invalida, el año no puede ser mayor al año actual por favor ingresela nuevamente...\n";
    }
    else
    {
        ValidarFecha = true;
    }

    return ValidarFecha;




}


void Venta::cargar() /// Se realiza la carga de datos de una venta por parte del usuario
{

    int importe;
    detalleVenta detalledeventa;


    setIdVenta(asignarIdVenta());
    setFormaPago(validarFormaPagoVenta());
    setIdCliente(validarIdClientedeVenta());
    if(deseaContinuar()==false){
        return;
    }
    setIdTrabajador(validarIdTrabajadordeVenta());
    setHorarioComida(validarHorarioComida());
    if(deseaContinuar()==false){
        return;
    }
    setEnvio(validarEnvio());
    validarFechaVenta();

    LimpiarPantalla();

    importe = CargaDetalle(getIdVenta());
       if (importe==0)
        {
            cout << "Usted vuelve al menu." << endl;
            colorCorrecto();
            return;
        }

//    importe = detalledeventa.cargarDetalle(getIdVenta());

    setImporteTotal(importe);

    escribirArchivo();
    mostrar();

}


void Venta::mostrar() /// Muestra los datos de la venta del objeto que se esta utilizando en determinada funcion
{
    LimpiarPantalla();
    int x = 5, y = 5, z = 6;
    recuadroPlato(x, y, 43, 9);
    for (z; z<14; z++){
    barraVertical(24,24,z);
    }
    gotoxy(x+2,y+1);
    cout <<  "ID DE VENTA: " << idVenta;
    gotoxy(x+22, y+1);
    cout <<  "PROYECTO RESTAURANT";
    gotoxy(x,y+2);
    cout << "*******************************************";
    gotoxy(x,y+3);
    cout << "\t" << "CLIENTE: " << "\t  ";
    mostrarNombreCliente(idCliente);
    cout << " (" << idCliente << ")";
    gotoxy(x,y+4);
    cout << "\t"<< "TRABAJADOR: " << "\t  ";
    mostrarNombreTrabajador(idTrabajador);
    cout << " (" << idTrabajador << ")";
    gotoxy(x,y+5);
    cout << "\t"<< "FECHA:" << "\t"  << "\t  "<< DiaVenta << " / "<< MesVenta << " / "<< AnioVenta;
    gotoxy(x,y+6);
    cout << "\t"<< "ENVIO: "<< "\t"<< "\t  ";
    mostrarEnvio(envio);
    gotoxy(x,y+7);
    cout << "\t"<<"IMPORTE TOTAL: " << "\t  "<< "$" << importeTotal << endl;
}


void mostrarEnvio(bool envio) /// Funcion para que se muestre el tipo de envio
{
    if(envio==1)
    {
        cout << "Con envio" <<endl;
    }
        else
        {
            cout << "Sin envio"<<endl;
        }
}

void mostrarDelivery() /// Muestra todas las ventas donde se haya realizado delivery
{
    FILE* p;
    Venta venta;
    int col = 6;
    p = fopen(FILE_VENTA, "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    LimpiarPantalla();
    cabeceraVentas();
    while(fread(&venta, sizeof (Venta), 1, p)){
        if (venta.getEnvio() == true){
//        venta.muestraVentas(col,&venta);
//        col++;
        }

    }
    cout << endl;
    liho(115);
    fclose(p);
}


void Venta::mostrarVentas()  /// Muestra todas las ventas que estan guardadas en el archivo
{
    FILE* p;
    Venta venta;
    int col = 6;
    p = fopen("./venta.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    LimpiarPantalla();
    cabeceraVentas();
    while(fread(&venta, sizeof (Venta), 1, p)){
    muestraVentas(col,&venta);
    col++;
    }
    cout << endl;
    liho(115);
    fclose(p);
}

void Venta::muestraVentas(int col, Venta* venta){

    gotoxy(2, col);
    cout << venta->idVenta;
    gotoxy(7, col);
    mostrarNombreCliente(venta->idCliente);
    cout << "\t" << "(" << venta->idCliente << ")";
    gotoxy(29, col);
    mostrarNombreTrabajador(venta->idTrabajador);
    cout << "\t" <<"(" << venta->idTrabajador << ")";
    gotoxy(56, col);
    cout << venta->formaPago;
    gotoxy(70, col);
    mostrarEnvio(venta->envio);
    gotoxy(83, col);
    cout << venta->DiaVenta << " / "<< venta->MesVenta << " / "<< venta->AnioVenta << endl;
    gotoxy(104, col);
    cout << "$" << venta->importeTotal;
    barraVerticalCarta(5, 27, 53, 66, 81, col);
    barraVertical(98,115,col);

}


void cabeceraVentas(){
    gotoxy(1, 1);
    liho(115);
    gotoxy(45, 2);
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "LAS VENTAS  \n";
    rlutil::setColor(rlutil::WHITE);
    gotoxy(1, 3);
    liho(115);
    barraVertical(98,115,2);
    barraVertical(98,115,4);
    gotoxy(2, 4);
    cout << "ID";
    gotoxy(7, 4);
    cout << "CLIENTE"<<"\t"<< "(ID)";
    gotoxy(29, 4);
    cout << "TRABAJADOR" << "  (ID)";
    gotoxy(56, 4);
    cout << "  PAGO";
    gotoxy(70, 4);
    cout << " ENVIO" << endl;
    gotoxy(84, 4);
    cout << "    FECHA" << endl;
    gotoxy(104, 4);
    cout << "IMPORTE" << endl;
    liho(115);
    barraVerticalCarta(5, 27, 53, 66, 81, 4);
}

void mostrarTodoUnDetalle() /// Muestra el detalle completo de una venta con un id determinado
{

    Venta venta;
    int id;
    bool existeId = false;
    cout << "Ingrese ID de venta para mostrar el detallado" <<endl;
    cin >> id;
    if(id<1){
        colorError();
        return;
    };
    FILE* p;
    p = fopen(FILE_VENTA, "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while(fread(&venta, sizeof (Venta), 1, p)){
        if(id == venta.getIdVenta()){
        venta.mostrar();
        existeId = true;
        }
    }
    fclose(p);
    if(existeId == true){
    recuadroPlato(5, 14, 43, 2);
    cabeceraDetalle();
    leerArchivodeIdVenta(id, 7, 17);
    }   else{
        colorError();
        cout << "El id especificado no fue encontrado. Usted volverá al menú";

        }

}

void cabeceraDetalle(){
    gotoxy(7,15);
    cout << "PLATO";
    gotoxy(25,15);
    cout << "UNIDADES";
    gotoxy(38,15);
    cout << "IMPORTE";
}



void mostrarLocal() /// Muestra todas las ventas donde se hizo consumicion en el local
{
    FILE* p;
    Venta venta;
    int col = 6;
    p = fopen(FILE_VENTA, "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    LimpiarPantalla();
    cabeceraVentas();
    while(fread(&venta, sizeof (Venta), 1, p)){
        if (venta.getEnvio() == false){
        venta.muestraVentas(col,&venta);
        col++;
        }

    }
    cout << endl;
    liho(115);
    fclose(p);
}


void Venta::escribirArchivo() /// Guarda un archivo de venta
{
    FILE* p;
    p = fopen(FILE_VENTA, "ab");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    fwrite(this, sizeof (Venta), 1, p);
    colorCorrecto();
    coloresPrograma();
    fclose(p);
    return;
}

void Venta::leerArchivo() /// Lee el archivo de una venta determinado por un ID que ingresemos
{
    FILE* p;
    Venta venta;
    int id;
    cout << "Ingrese el ID de la venta que quisiera visualizar: " << endl;
    cin >> id;
    p = fopen(FILE_VENTA, "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while(fread(&venta, sizeof (Venta), 1, p)){
        if(id == venta.idVenta){
            venta.mostrar();
        }
    }
}




