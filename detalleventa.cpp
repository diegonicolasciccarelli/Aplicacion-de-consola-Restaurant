#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#include "detalleVenta.h"
#include "rlutil.h"
#include "menu.h"
#include "plato.h"


const char *FILE_DETALLEVENTA = "./detalleventa.dat";

detalleVenta::detalleVenta(){
    idPlatoVenta =  0;
    cantPorPlato = 0;
    idVenta = 0;
    importe = 0;
}

int detalleVenta::getIdPlatoVenta(){
    return idPlatoVenta;
}
int detalleVenta::getCantPorPlato(){
    return cantPorPlato;
}
int detalleVenta::getIdVenta(){
    return idVenta;
}
float detalleVenta::getImporte(){
    return importe;
}

void detalleVenta::setIdPlatoVenta(int p){
    idPlatoVenta = p;
}
void detalleVenta::setCantPorPlato(int cp){
    cantPorPlato = cp;
}
void detalleVenta::setIdVenta(int pv){
    idVenta = pv;
}
void detalleVenta::setImporte(float im){
    importe =im;
}

void detalleVenta::escribirArchivo() /// Guarda un archivo de detalleventa
{
    FILE* p;
    p = fopen("./detalleventa.dat", "ab");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    fwrite(this, sizeof (detalleVenta), 1, p);
    colorCorrecto();
    coloresPrograma();
    fclose(p);
    return;
}

int validarIdPlatoVenta() /// Valida si existe el id de plato que ingresemos
{
    int p=0, e;

    while(p==0){
        cout << "Id Plato : " << endl;
        cin >> p;
        e = existeIdPlato(p);
        if (e==0){
            colorError();
            cout << "Id de plato inexistente. Vuelva a intentarlo. ";
            coloresPrograma();
            // verIdPlatosyNombres();
        }
        }

        return p;
}

int validarCantPorPlato(int stock) /// Valida que la cantidad ordenado del plato sea un numero positivo y no sea mayor a la del stock del plato
{

    int p = 0;

    while(stock < p || p<1)
    {
    cout << "El stock es: " << stock << endl;
    cout << "Cantidad de unidades (por cada plato) : " << endl;
    cin >> p;
    if (stock < p || p < 1){
        colorError();
        cout << "La cantidad de platos no es valida o es mayor al stock disponible, ingresela nuevamente ... " << endl;
        coloresPrograma();
        p = 0;
    }
        else
        {
        colorCorrecto();
        coloresPrograma();
        }

    }


    return p;

}


//int detalleVenta::cargarDetalle(int idVen)
//{
//
//    detalleVenta detalledeventa;
//    bool otroPlato = true;
//    int a = 0, stock = 0, id, cantidad, importePlato = 0, importeVenta = 0;
//
//        while (otroPlato == true){
//        a = a+1;
//        detalledeventa.setIdVenta(idVen);
//
//        cout << "Ingrese los detalles del plato numero " << a << " " << endl;
//
//        detalledeventa.setIdPlatoVenta(validarIdPlatoVenta());
//        cout << endl;
//        id = detalledeventa.getIdPlatoVenta();
//
//        stock = recibirStock(id);
//        if (stock ==0){
//            cout << "No hay existencias del plato seleccionado. Se volvera al Menu ya que no puede agendar una venta de un plato sin stock " << endl;
//            return 0;
//        }
//        detalledeventa.setCantPorPlato(validarCantPorPlato(stock));
//
//        if(detalledeventa.getCantPorPlato()>0){
//        cantidad = detalledeventa.getCantPorPlato();
//        restarStock(detalledeventa.getCantPorPlato(), id);
//        importePlato = recibirImporte(id) * cantidad;
//        detalledeventa.setImporte(importePlato);
//        importeVenta += importePlato;
//        detalledeventa.mostrar();
//        detalledeventa.escribirArchivo();
//        Pausa();
//        }
//        else{
//            cout << "No se han restado unidades al stock. " << endl;
//            a = a-1;
//        }
//
//        if(a!= 0)
//        {
//        otroPlato = opcionOtroPlato();
//        }
//
//        LimpiarPantalla();
//        }
//
//        return importeVenta;
//
//}

int CargaDetalle(int idVen)
{
    detalleVenta detalledeventa;
    int cant = -1, i = 0, stock = 0, id, cantidad, importePlato = 0, importeVenta = 0;
    while(cant<0)
    {
        cout << "Ingresar la cantidad de platos DIFERENTES que se cargarán en la venta: (O ingrese 0 para salir al menú)" << endl;
        cin >> cant;
        if (cant<0)
        {
            colorError();
            cout << "Ingrese un numero de platos positivos.";
            Pausa();
            LimpiarPantalla();
        }
    }

    for(i; i<cant; i++)
    {
        /// ID VENTA

        detalledeventa.setIdVenta(idVen);

        cout << "Ingrese los detalles del plato numero " << i+1 << " " << endl;

        /// EXISTE ID

        detalledeventa.setIdPlatoVenta(validarIdPlatoVenta());
        id = detalledeventa.getIdPlatoVenta();


        /// REVISAR STOCK

        stock = recibirStock(id);
        if (stock <1){
            cout << "No hay existencias del plato seleccionado. Se debe volver a ingresar otro plato " << endl;
            i--;
        }
        else
        {
        detalledeventa.setCantPorPlato(validarCantPorPlato(stock));
        if(detalledeventa.getCantPorPlato()>=1){
        cantidad = detalledeventa.getCantPorPlato();
        restarStock(detalledeventa.getCantPorPlato(), id);
        importePlato = recibirImporte(id) * cantidad;
        detalledeventa.setImporte(importePlato);
        importeVenta += importePlato;
        detalledeventa.mostrar();
        detalledeventa.escribirArchivo();
        Pausa();
        }
            else{
                cout << "No se han restado unidades al stock. " << endl;
                i--;
            }
        }
    }
    return importeVenta;
}


bool opcionOtroPlato() /// Verifica que el usuario quiera ingresar otro plato en el detalle de la venta
{
    bool otroPlato = true, vali = true;
    char x;
    while(vali==true){
    cout << "Desea ingresar otro plato mas? ( S / N )" << endl;
    cin >> x;
            if (x == 'N' || x == 'n')
                {
                        otroPlato = false;
                        vali = false;
                }
                    else if (x == 'S' || x == 's')
                    {   otroPlato = true;
                        vali = false;
                    }   else{
                            colorError();
                            coloresPrograma();
                        }
    }
    return otroPlato;

}

void leerArchivodeIdVenta(int id, int x, int y) /// Se abre el archivo para mostrar los detalles de un ID venta
{

    FILE* p;
    detalleVenta detalleventa;
    p = fopen("./detalleventa.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while(fread(&detalleventa, sizeof (detalleVenta), 1, p)){
        if(id == detalleventa.getIdVenta()){
            detalleventa.muestraDetalle(x, y);
            y++;
        }
    }
    recuadroPlato(5, 16, 43, y-16);
fclose(p);
}

void detalleVenta::mostrar() /// Muestra los datos de un detalle de venta que estan en el objeto
{

    cout << "Id Plato : " << idPlatoVenta << endl;
    mostrarNombrePlato(idPlatoVenta);
    cout << "Cantidad de unidades (por cada plato) : " << cantPorPlato << endl;
    cout << "Importe : $" << importe << endl;
    cout << "--------------\n";
}

void detalleVenta::muestraDetalle(int x, int y) /// Muestra los datos de un detalle de venta que estan en el objeto
{

    gotoxy(x, y);
    mostrarNombrePlato(idPlatoVenta);
    gotoxy(x+18, y);
    cout << cantPorPlato;
    gotoxy(x+31, y);
    cout << importe << endl;
}

bool elecciondeModificarFormaPago() /// Pregunta si se desea modificar el precio
{
    bool valido = false;
    char eleccion;
    cout << "Desea modificar la forma de pago de la venta? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){

        valido=true;
    }
 return valido;
}

void modificarFormaPago(int id) /// Funcion para modificar el precio de un plato. Se utiliza en modificarPlatoPorId
{
    Venta venta;
    FILE* p;
    float pr;
    bool validaID=false;
    p = fopen("./venta.dat", "rb+");

    if (p == NULL)
    {
        cout << "Error de archivo. Nombre de archivo: " << "./venta.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&venta, sizeof (Venta), 1, p))
    {
        if (id == venta.getIdVenta())
        {
            venta.mostrar();
            cout << endl;
            if(elecciondeModificarFormaPago()==true){
            LimpiarPantalla();
            venta.setFormaPago(validarFormaPagoVenta());
            fseek(p, ftell(p) - sizeof (Venta), 0);
            fwrite(&venta, sizeof(Venta), 1, p);
            fclose(p);
            cout << "Opcion elegida correctamente, continuamos con el stock" << endl;
            colorCorrecto();
            }
        }
    }
    fclose(p);
}

bool elecciondeModificarCliente() /// Pregunta si se desea modificar el precio
{
    bool valido = false;
    char eleccion;
    cout << "Desea modificar el cliente de la venta? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){

        valido=true;
    }
 return valido;
}

void modificarClienteVenta(int id) /// Funcion para modificar el precio de un plato. Se utiliza en modificarPlatoPorId
{
    Venta venta;
    FILE* p;
    float pr;
    bool validaID=false;
    p = fopen("./venta.dat", "rb+");

    if (p == NULL)
    {
        cout << "Error de archivo. Nombre de archivo: " << "./venta.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&venta, sizeof (Venta), 1, p))
    {
        if (id == venta.getIdVenta())
        {
            venta.mostrar();
            cout << endl;
            if(elecciondeModificarCliente()==true){
            LimpiarPantalla();
            venta.setIdCliente(validarIdClientedeVenta());
            fseek(p, ftell(p) - sizeof (Venta), 0);
            fwrite(&venta, sizeof(Venta), 1, p);
            fclose(p);
            cout << "Opcion elegida correctamente, continuamos con el stock" << endl;
            colorCorrecto();
            }
        }
    }
    fclose(p);
}




bool elecciondeModificarVendedor() /// Pregunta si se desea modificar el precio
{
    bool valido = false;
    char eleccion;
    cout << "Desea modificar el trabajador de la venta? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){

        valido=true;
    }
 return valido;
}

void modificarVendedor(int id) /// Funcion para modificar el precio de un plato. Se utiliza en modificarPlatoPorId
{
    Venta venta;
    FILE* p;
    float pr;
    bool validaID=false;
    p = fopen("./venta.dat", "rb+");

    if (p == NULL)
    {
        cout << "Error de archivo. Nombre de archivo: " << "./venta.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&venta, sizeof (Venta), 1, p))
    {
        if (id == venta.getIdVenta())
        {
            venta.mostrar();
            cout << endl;
            if(elecciondeModificarVendedor()==true){
            LimpiarPantalla();
            venta.setIdTrabajador(validarIdTrabajadordeVenta());
            fseek(p, ftell(p) - sizeof (Venta), 0);
            fwrite(&venta, sizeof(Venta), 1, p);
            fclose(p);
            cout << "Opcion elegida correctamente, continuamos con el stock" << endl;
            colorCorrecto();
            }
        }
    }
    fclose(p);
}


bool existeIdVenta(int id) /// Funcion que valida que exista un ID de plato que le brindemos y muestra que nombre es.
{
    FILE* p;
    Venta venta;
    int idArchivo;
    char nombrePlato[50];

    p = fopen("./venta.dat", "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&venta, sizeof (Venta), 1, p) == 1)
    {
        idArchivo = venta.getIdVenta();
        if (id == idArchivo)
           {
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return 0;
}
void modificarVentaPorId() /// Funcion para modificar atributos de una venta por ID
{
    LimpiarPantalla();
    Venta venta;
    int id;
    FILE* p;

    bool validaID=false;


    while(validaID==false){  ///valido que exista el id que ingresa para modificar
        cout << "Ingrese el id de venta que desea modificar: ";
        cin >> id;
        validaID=existeIdVenta(id);
        if (validaID==false){
            colorError();

            if (deseaContinuar()==false){  ////vuelvo al menu anterior si no quiere continuar en la opcion

                return;
            }
            else{

              venta.mostrarVentas();
              cout << endl;
            }

        }
    }

    modificarVendedor(id);
    if(deseaContinuar()==false){

        return;
    }
    modificarClienteVenta(id);
    if(deseaContinuar()==false){

        return;
    }
    modificarFormaPago(id);
    if(deseaContinuar()==false){

        return;
    }
}
