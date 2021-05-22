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
#include "informes.h"
#include "plato.h"

void nombreMes(int mes) /// Busca el nombre del mes dependiendo del numero que se le brinda
{


switch ( mes )
    {
        case  1 :
                cout <<  " Enero ";
                  break;
        case  2 :
            cout <<  " Febrero ";
                  break;
        case  3 :
            cout <<  " Marzo ";
                  break;
        case  4 :
            cout <<  " Abril ";
                  break;
        case  5 :
            cout <<  " Mayo ";
                  break;
        case  6 :
            cout <<  " Junio ";
                  break;
        case  7 :
            cout <<  " Julio ";
                  break;
        case  8 :
            cout <<  " Agosto ";
                  break;
        case  9 :
            cout <<  " Septiembre ";
                  break;
        case 10 :
            cout <<  " Octubre ";
                  break;
        case 11 :
            cout <<  " Noviembre ";
                  break;
        case 12 :
                    cout <<  " Diciembre ";
                  break;
        default:
            entradaIncorrecta();
            break;
    }

}

void buscarVentasAnual() /// Busca y muestra las ventas realizadas en un año determinado por el usuario (Y lo valida)
{

bool validoAnio = false;
int anioActual = ObtenerAnio();
int anio;

while(validoAnio == false){
cout << "Ingrese el año que quiere ver la recaudacion" << endl;
cin >> anio;
if (anio > 1950 && anio <= anioActual){
    validoAnio = true;
}
else if(anio < 1950){
    cout << "No se puede ingresar un año tan antiguo" << endl;
    colorError();
    if(deseaContinuar()==false){
        Pausa();
        return;
    }
}else{
    cout << "No se puede ingresar un año superior al presente" << endl;
    colorError();
    if(deseaContinuar()==false){
        Pausa();
        return;
    }
    }
}
cout << "La recaudacion total del anio "<< anio << " fue de : $" << leerAnioenArchivoVenta(anio) << endl;


Pausa();
LimpiarPantalla();

}

int leerAnioenArchivoVenta(int anio) /// Lee el archivo de ventas de un año brindado por el usuario (Ya validado)
{
    int Recaudaciontotal=0;
    FILE* p;
    Venta venta;
    p = fopen("./venta.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }
    while(fread(&venta, sizeof (Venta), 1, p)){
        if(anio == venta.getAnioVenta()){
            Recaudaciontotal +=venta.getImporteTotal();
        }
    }
    fclose(p);
    return Recaudaciontotal;

}

void buscarVentasMensual() /// Busca y muestra las ventas realizadas en todos los años del mes que se brinde. (Cuando no haya ventas, no se mostrara)
{
    bool mescorrecto=false;
    int mes;
    while(mescorrecto==false){
    cout << "Ingrese el mes del cual quisiera realizar la comparacion: " << endl;
    cin >> mes;
    if(mes>=1 && mes<=12){
        colorCorrecto();
        mescorrecto=true;
    }else{
        colorError();
        if(deseaContinuar()==false){

        return;
        }
    }
    }
    cout << "Mes de: " ;
    nombreMes(mes);
    cout << endl << endl;
    leerMesenArchivoVenta(mes);
    Pausa();
    LimpiarPantalla();
}

int ventasAnioMes(int mes, int anio) /// Lee el archivo de ventas de un mes brindado por el usuario
{
    FILE* p;
    Venta venta;
    int recaudacionMes = 0;
    p = fopen("./venta.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }

    while(fread(&venta, sizeof (Venta), 1, p)){
        if(anio == venta.getAnioVenta() && mes == venta.getMesVenta()){
        recaudacionMes += venta.getImporteTotal();
            }
    }

    fclose(p);
    return recaudacionMes;

}

void leerMesenArchivoVenta (int mes) /// Muestra la recaudacion de un mes si es que hay
{
    int anio = 2000, rec;
    bool hubo = false;
    while(anio<2021){
    rec = ventasAnioMes(mes, anio);
    if(rec !=0){
        cout << "La recaudacion en ";
        nombreMes(mes);
        cout << " de " << anio << " fue: " << rec<<endl;
        hubo = true;
    }
    anio++;
    }
    if(hubo ==  false){
    cout << "No se encontró recaudación alguna en el mes especificado.";
    }
}


void buscarVentasPorTipo() /// Busca y muestra las ventas dependiendo el tipo de venta(Local o delivery)
{
    Venta venta;

    cout << "RECAUDACION TOTAL (LOCAL)     : " << "\t" << "$" << leerLocalenArchivoVenta() << endl;

    cout << "RECAUDACION TOTAL (DELIVERY)  : "  <<"\t" <<"$" << leerDeliveryenArchivoVenta() << endl;
}

int leerLocalenArchivoVenta() /// Muestra las ventas por local del archivo venta y lo suma a recaudacion total
{

int Recaudaciontotal=0;
    FILE* p;
    Venta venta;
    p = fopen("./venta.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }
    while(fread(&venta, sizeof (Venta), 1, p)){
        if(venta.getEnvio() == 0){
            Recaudaciontotal +=venta.getImporteTotal();

        }
    }
    fclose(p);
    return Recaudaciontotal;
}

int leerDeliveryenArchivoVenta() /// Muestra las ventas por delivery del archivo venta y lo suma a recaudacion total
{

    int Recaudaciontotal=0;
    FILE* p;
    Venta venta;
    p = fopen("./venta.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }
    while(fread(&venta, sizeof (Venta), 1, p)){
        if(venta.getEnvio() == 1){
            Recaudaciontotal +=venta.getImporteTotal();

        }
    }
    fclose(p);
    return Recaudaciontotal;
}


void buscarVentasPorIdTrabajador() /// Muestra las ventas realizadas por un trabajador cuya ID brinda el usuario
{

bool banderatrabajador =false;

    int idtrabajador;
    char trabajador[50];

    while(banderatrabajador==false){
        cout << "Ingrese el id de trabajador que quiere ver la recaudacion" << endl;
        cin >> idtrabajador;
        banderatrabajador=existeIdTrabajador(idtrabajador);
        if (banderatrabajador==false){
        cout << "Id de trabajador no encontrado. " << endl;
        colorError();
            if(deseaContinuar()==false){
                return;
            }
        }
    }

    mostrarNombreTrabajador(idtrabajador);
    cout << " tiene una recaudacion de: $ " << leerIdTrabajadorenArchivoVenta(idtrabajador) << endl;
    colorCorrecto();

    Pausa();


}

int leerIdTrabajadorenArchivoVenta(int idtrabajador) /// busca las ventas de un trabajador y devuelve la recaudacion total de este
{
    int Recaudaciontotal=0;

    FILE* v;
    Venta venta;
    int idventa;
    v = fopen("./venta.dat", "rb");
    if (v == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }


            while(fread(&venta, sizeof (venta), 1,v)){
                if(idtrabajador==venta.getIdTrabajador()){
                   Recaudaciontotal += venta.getImporteTotal();
                }
            }
    fclose(v);
    return Recaudaciontotal;
}

void buscarVentasxTipoPlato() /// Valida un tipo plato que le brindemos y luego muestra las ventas realizadas segun ese tipo
{

int numplato;
numplato=validarTipoPlato();
cout << "Se recaudo en el tipo de plato "<< numplato << " $ " << leerTipoPlatoenArchivoVenta(numplato) << endl;
}

int leerTipoPlatoenArchivoVenta(int numplato) ///busco el tipo de plato en plato.dat y comparo su id de plato con el id de plato venta para obtener el importe
{

int Recaudaciontotal=0;
    FILE* p;
    FILE* v;
    Venta venta;
    Plato plato;
    detalleVenta detalleventa;
    int idventa;
    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }
    v = fopen("./detalleventa.dat", "rb");
    if (v == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }
    while(fread(&plato, sizeof (Plato), 1, p)){
        if(numplato == plato.getTipoPlato()){
            while(fread(&detalleventa, sizeof (detalleVenta), 1,v)){
                if(plato.getIdPlato()==detalleventa.getIdPlatoVenta()){
                   Recaudaciontotal += detalleventa.getImporte();
                }
            }
        }
    }
    fclose(p);
    fclose(v);
    return Recaudaciontotal;
}


void buscarVentasxIdPlato() /// Busca las ventas de un determinado PLATO por su ID (Lo valida primero)
{

bool banderaplato =false;

int idplato;

    while(banderaplato==false){
    cout << "Ingrese el id de plato que quiere ver la recaudacion" << endl;
    cin >> idplato;
    banderaplato=existeIdPlato(idplato);
    if (banderaplato==0){
        cout << "El id de plato no existe. " << endl;
        colorError();
        cout << endl;
        if(deseaContinuar()==false){
            return;
        }
    }
    }
cout << "Se recaudo en el id de plato "<< idplato << " $ " << leerIdPlatoenArchivoVenta(idplato) << endl;
Pausa();
LimpiarPantalla();

}

int leerIdPlatoenArchivoVenta(int numplato){  ///busco el tipo de plato en plato.dat y comparo su id de plato con el id de plato venta para obtener el importe

int Recaudaciontotal=0;
    FILE* p;
    FILE* v;
    Venta venta;
    Plato plato;
    detalleVenta detalleventa;
    int idventa;
    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }
    v = fopen("./detalleventa.dat", "rb");
    if (v == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }
    while(fread(&plato, sizeof (Plato), 1, p)){
        if(numplato == plato.getIdPlato()){
            while(fread(&detalleventa, sizeof (detalleVenta), 1,v)){
                if(plato.getIdPlato()==detalleventa.getIdPlatoVenta()){
                   Recaudaciontotal += detalleventa.getImporte();
                }
            }
        }
    }
    fclose(p);
    fclose(v);
    return Recaudaciontotal;
}


void buscarVentasPorHorario() /// Busca las ventas por horario /Almuerzo y cena
{
    Venta venta;

    cout << "RECAUDACION TOTAL (ALMUERZO)  : "<<"\t" <<"$" << leerAlmuerzoArchivoVenta() << endl;
    cout << "RECAUDACION TOTAL (CENA)      : " << "\t" << "$" << leerCenaArchivoVenta() << endl;

}

int leerAlmuerzoArchivoVenta() /// Muestra la recaudacion total de las ventas en horario Almuerzo
{

    int Recaudaciontotal=0;
    FILE* p;
    Venta venta;
    p = fopen("./venta.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }
    while(fread(&venta, sizeof (Venta), 1, p)){
        if(venta.getHorarioComida() == 1){
            Recaudaciontotal +=venta.getImporteTotal();

        }
    }
    fclose(p);
    return Recaudaciontotal;
}

int leerCenaArchivoVenta() /// Muestra la recaudacion total de las ventas en horario Cena
{

    int Recaudaciontotal=0;
    FILE* p;
    Venta venta;
    p = fopen("./venta.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }
    while(fread(&venta, sizeof (Venta), 1, p)){
        if(venta.getHorarioComida() == 2){
            Recaudaciontotal +=venta.getImporteTotal();

        }
    }
    fclose(p);
    return Recaudaciontotal;
}

void cabeceraVentasPlatos()
{
    barraVertical(50, 50, 2);
    gotoxy(1, 1);
    liho(50);
    gotoxy(17, 2);
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "VENTAS POR PLATO  \n";
    rlutil::setColor(rlutil::WHITE);
    gotoxy(1, 3);
    liho(50);
    gotoxy(15, 4);
    cout << "PLATO";
    gotoxy(38, 4);
    cout << "RECAUDACIÓN" << endl;
    liho(50);
    barraVertical(36, 50, 4);
}

void importetotalxplato() /// Se usa para mostrar todas las recaudaciones de cada plato
{

    int id = 1, valorPlato = 0, col = 6;
    LimpiarPantalla();
    while(existePlato(id)==true){
        cabeceraVentasPlatos();
        valorPlato = leerIdPlatoenArchivoVenta(id);
        gotoxy(2,col);
        mostrarNombrePlato(id);
        gotoxy(41,col);
        cout << "$" << valorPlato;
        barraVertical(36, 50, col);
        col++;
        id++;
    }
    cout << endl;
    liho(50);
}


void platoMasVendido() /// buscamos y mostramos el plato mas vendido
{

int id =1, valorPlato, mayorrecaudacion=0, mejorplato = 0;

    while(BuscamosyvalidamosIdPlato(id)==true){

        valorPlato = leerIdPlatoenArchivoVenta(id);
        if(valorPlato > mayorrecaudacion){
            mayorrecaudacion=valorPlato;
            mejorplato=id;
        }
        id++;
    }
    cout << "El mas vendido es: ";
    mostrarNombrePlato(mejorplato);
    cout << " con una recaudacion de $ " << mayorrecaudacion << endl;
    colorCorrecto();
}

void comparativaTotal() /// Es la opcion final de informes. Muestra todos los datos juntos
{
    int y = 2;
    liho(55);
    cout << endl;
    buscarVentasPorHorario();
    liho(55);
    cout << endl;
    buscarVentasPorTipo();
    liho(55);
    cout << endl;
    cout << "RECAUDACION TOTAL (ENTRADAS)  : "<<"\t" <<"$" << leerTipoPlatoenArchivoVenta(1) << endl;
    cout << "RECAUDACION TOTAL (PRINCIPAL) : "<<"\t" <<"$" << leerTipoPlatoenArchivoVenta(2) << endl;
    cout << "RECAUDACION TOTAL (GUARNICION): "<<"\t" <<"$" << leerTipoPlatoenArchivoVenta(3) << endl;
    cout << "RECAUDACION TOTAL (POSTRE)    : "<<"\t" <<"$" << leerTipoPlatoenArchivoVenta(4) << endl;
    liho(55);
    cout << endl;
    for(y;y<12;y++){
    barraVertical(55, 35, y);
    }
    Pausa();

    LimpiarPantalla();
    importetotalxplato();
    cout << endl << endl;
    platoMasVendido();

}
