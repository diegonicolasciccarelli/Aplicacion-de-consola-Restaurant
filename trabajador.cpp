#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#include "rlutil.h"
#include "persona.h"
#include "trabajador.h"
#include "menu.h"
#include "plato.h"

const char *FILE_TRABAJADOR = "./trabajador.dat";



Trabajador::Trabajador()
{
    TipoTrabajador = 0;
    estadoTrabajador = false;
    IdTrabajador = 0;
    int DiaIngreso = 0;
    int MesIngreso = 0;
    int AnioIngreso = 0;
}


int Trabajador::getTipoTrabajador(){
    return TipoTrabajador;
}
bool Trabajador::getEstadoTrabajador(){
    return estadoTrabajador;
}
int Trabajador::getIdTrabajador(){
    return IdTrabajador;
}
int Trabajador::getDiaIngreso(){
    return DiaIngreso;
    }
int Trabajador::getMesIngreso(){
    return MesIngreso;
    }
int Trabajador::getAnioIngreso(){
    return AnioIngreso;
    }


void Trabajador::setTipoTrabajador(int t){
    TipoTrabajador = t;
}
void Trabajador::setEstadoTrabajador(bool e){
    estadoTrabajador = e;
}
void Trabajador::setIdTrabajador(int d){
    IdTrabajador = d;
}
void Trabajador::setDiaIngreso(int fn){
    DiaIngreso = fn;
}
void Trabajador::setMesIngreso(int fn){
    MesIngreso = fn;
}
void Trabajador::setAnioIngreso(int fn){
    AnioIngreso = fn;
}


void Trabajador::cargar() /// hereda la carga de persona y carga trabajador
{

    Persona::cargar();

    setIdTrabajador(asignarIdTrabajador());
    setEstadoTrabajador(1);
    setTipoTrabajador(validarTipoTrabajador());
    validarFechaTrabajador(getAnioNacimiento());
    if(deseaContinuar()==false){
        return;
    }
    LimpiarPantalla();
    mostrar();
    escribirArchivo();
    Pausa();
}

int asignarIdTrabajador() /// Asigna un valor autonumerico al Id de cliente
{
    int id = 0;
    FILE* p;
    Trabajador trabajador;
    p = fopen("trabajador.dat", "rb");
    if (p == NULL)
    {
        return 1;
    }

    while (fread(&trabajador, sizeof (Trabajador), 1, p))
    {
       id = trabajador.getIdTrabajador();

    }
    id += 1;
    cout << "Se le ha asignado el ID de trabajador " << id << endl;
    fclose(p);
    return id;
}
bool existeIdTrabajador(int id) /// valida si existe el id de trabajador
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

int validarTipoTrabajador() /// valida el tipo de trabajador
{
    bool vali = false;
    int tipo;
    Trabajador trabajador;

    while (!vali){
        cout << "Ingrese el tipo de trabajador (1 para trabajador de planta, 2 para delivery)" << endl;
        cin >> tipo;

        if (tipo >= 1 && tipo <= 2){
            vali = true;
            return tipo;
    }else{
        colorError();
        }
    }
    return 0;
}

void mostrarstringTipoTrabajador(int tipotrabajador) /// muestra que tipo de trabajador es
{

    if (tipotrabajador == 1){
        cout << "\t"  << "Tipo: " << "\t"<< "\t" << "De local" << endl;
    }
    else{
        cout << "\t" << "Tipo: " << "\t"<< "\t"<<"De delivery" << endl;
    }
}

void Trabajador::validarFechaTrabajador(int nac) /// valida fecha de trabajador
{

    bool ValidarFecha=false;

    Fecha fecha;
    cout << "Ingrese su fecha de ingreso: " << endl;
    while (ValidarFecha==false){
    ValidarFecha= ValidoAnioIngreso(&fecha, nac);
    }
    setDiaIngreso(fecha.getDia());
    setMesIngreso(fecha.getMes());
    setAnioIngreso(fecha.getAnio());
}

bool ValidoAnioIngreso(Fecha *fecha, int nac) /// valida el anio de ingreso de trabajador
{

    bool ValidarFecha = false;
    int anioActual = ObtenerAnio();
    Persona persona;
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
    else if (fecha -> getAnio()- nac < 18)
        ////(TrabajadorMayorEdad(fecha) == false)
    {

        cout << "La fecha ingresada es una fecha invalida, No puede ser menor de edad un trabajador por favor ingresela nuevamente...\n";

    }
    else
    {
        ValidarFecha = true;
    }

    return ValidarFecha;
}

void mostrarTrabajadores(int estado) /// muestra todos los trabajadores dados de alta
{
    FILE* p;
    Trabajador trabajador;
    int col = 6;
    p = fopen("./trabajador.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    LimpiarPantalla();
    cabeceraTrabajadores();
    while(fread(&trabajador, sizeof (Trabajador), 1, p)){
    if(trabajador.getEstadoTrabajador() == estado){
    gotoxy(2,col);
    cout << trabajador.getIdTrabajador();
    gotoxy(8,col);
    cout << trabajador.getNombre();
    cout << " " << trabajador.getApellido();
    barraVertical(6, 50, col);
    col++;
    }
    }
    cout << endl;
    liho(50);
    fclose(p);
}


void cabeceraTrabajadores(){
    barraVertical(50, 50, 2);
    gotoxy(1, 1);
    liho(50);
    gotoxy(17, 2);
    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "LOS TRABAJADORES  \n";
    rlutil::setColor(rlutil::WHITE);
    gotoxy(1, 3);
    liho(50);
    gotoxy(2, 4);
    cout << "ID";
    gotoxy(8, 4);
    cout << "NOMBRE Y APELLIDO" << endl;
    liho(50);
    barraVertical(6, 50, 4);
}

void mostrarNombreTrabajador(int id)/// muestra el nombre de trabajador del id que se le pasa por parametro
{

    FILE* p;
    Trabajador trabajador;
    char str[50];
    p = fopen("./trabajador.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while(fread(&trabajador, sizeof (Trabajador), 1, p)){
        if(id == trabajador.getIdTrabajador()){
            strcpy(str,trabajador.getNombre());
            cout << str;
            }

    }
    fclose(p);
}

void Trabajador::mostrar() /// muestra los datos de trabajador
{
    LimpiarPantalla();
    gotoxy(12,6);
    cout << "\t" << "ID Trabajador: " << IdTrabajador;
    Persona::mostrar();
    gotoxy(5,12);
    cout << "\t"<< "Ingreso:" << "\t"  << DiaIngreso << " / "<< MesIngreso << " / "<< AnioIngreso << endl;
    gotoxy(5,13);
    mostrarstringTipoTrabajador(TipoTrabajador);
    gotoxy(5,14);
    mostrarstringEstado(estadoTrabajador);
    gotoxy(6,17);
    rlutil::setColor(rlutil::LIGHTGREEN);
    system("pause");
    rlutil::setColor(rlutil::WHITE);


}

void Trabajador::escribirArchivo() /// escribe en el archivo de trabajador
{
    FILE* p;
    p = fopen("./trabajador.dat", "ab");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    fwrite(this, sizeof (Trabajador), 1, p);
    colorCorrecto();
    coloresPrograma();
    fclose(p);
    return;
}

void Trabajador::leerArchivo() /// lee el archivo con el id de trabajador que se ingresa
{
    FILE* p;
    Trabajador trabajador;
    int id;
    cout << "Ingrese el ID del trabajador que quisiera visualizar: " << endl;
    cin >> id;
    p = fopen("./trabajador.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while(fread(&trabajador, sizeof (Trabajador), 1, p)){
        if(id == trabajador.IdTrabajador){

            trabajador.mostrar();
        }

    }

}


/// dar de baja

void dardeBajaTrabajador() /// funcion que llama a las otras para dar de baja trabajador
{
    int id;
    if(validamosSiHayTrabajadorAlta()==0){
        return;
    }
    verTrabajadorconAlta();
    id=TrabajadorExistenteyConAlta();
    if(id==-1){
        return;
    }
    bajarTrabajador(id);
    colorCorrecto();
}

int validamosSiHayTrabajadorAlta() /// valida si hay trabajadores de alta si no lo hay retorna un int que va hacer que vuelva al menu anterior
{
int cont=0;
    FILE* p;
    Trabajador trabajador;

    p = fopen("./trabajador.dat", "rb");
    if (p == NULL)
    {
        return -1;
    }
    while (fread(&trabajador, sizeof (Trabajador), 1, p) == 1)
    {

        if (trabajador.getEstadoTrabajador()==1)
        {
            cont ++;
            fclose(p);
        }
    }
    if (cont==0){
        fclose(p);
        cout << "No hay trabajadores dados de alta para realizar la baja del mismo, Usted volvera al menu"<< endl;
        return 0;
    }
    return 1;
    fclose(p);
    }

void verTrabajadorconAlta() /// opcion para ver todos los trabajadores dados de alta
{

    char eleccion;

    cout << "Desea ver cuales son los trabajadores dados de alta o ya conoce el id de Trabajador que quiere dar de baja? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){
        LimpiarPantalla();
        mostrarTrabajadores(1);
        cout << endl;
    }
}



int TrabajadorExistenteyConAlta() /// se ingresa el id que quiere dar de baja
{
    int id;
    bool vali =false;
    while (vali==false){

        cout << "Ingrese el id del trabajador que desea dar de baja: ";
        cin >> id;
        if(ExisteIdTrabajadorConAlta(id)== false){

            colorError();
            coloresPrograma();
            vali=false;
            if(deseaContinuar()==false){
                return -1;
            }
            verTrabajadorconAlta();
        } else{
        vali=true;
        }
    }
    return id;
    }

bool ExisteIdTrabajadorConAlta(int id) /// se valida si existe el id de trabajador ingresado y si esta con alta
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
        if (id == idArchivo && trabajador.getEstadoTrabajador()==1)
        {
            fclose(p);
            return true;
        }

    }
    return false;
    fclose(p);
}

void bajarTrabajador(int id) /// se realiza la baja del trabajador
{
    FILE* p;
    Trabajador trabajador;
    bool es = false;
    p = fopen("./trabajador.dat", "rb+");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while (fread(&trabajador, sizeof (Trabajador), 1, p)){
        if (id == trabajador.getIdTrabajador()){
            trabajador.setEstadoTrabajador(es);
            fseek(p, ftell(p) - sizeof (Trabajador), 0);
            fwrite(&trabajador, sizeof(Trabajador), 1, p);
            Pausa();
            fclose(p);
            return;
        }
    }
    fclose(p);
}

///// subir trabajador

void dardeAltaTrabajador() /// funcion que llama a las otras para dar de alta trabajador
{
    int id;
    if(validamosSiHayTrabajadorBaja()==0){
        return;
    }
    verTrabajadorconBaja();
    id=TrabajadorExistenteyConbaja();
    if(id==-1){
        return;
    }
    subirTrabajador(id);
    colorCorrecto();
    coloresPrograma();
}

void verTrabajadorconBaja() /// opcion para ver todos los trabajadores dados de baja
{

    char eleccion;

    cout << "Desea ver cuales son los trabajadores dados de baja o ya conoce el id de trabajador que quiere dar de alta? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){
        LimpiarPantalla();
        mostrarTrabajadores(0);
        cout << endl;
    }
}

int validamosSiHayTrabajadorBaja() /// valida si hay trabajadores de baja si no lo hay retorna un int que va hacer que vuelva al menu anterior
{
int cont=0;
    FILE* p;
    Trabajador trabajador;

    p = fopen("./trabajador.dat", "rb");
    if (p == NULL)
    {
        return -1;
    }
    while (fread(&trabajador, sizeof (Trabajador), 1, p) == 1)
    {

        if (trabajador.getEstadoTrabajador()==0)
        {
            cont ++;
            fclose(p);
        }
    }
    if (cont==0){
        fclose(p);
        cout << "No hay trabajadores dados de baja para realizar el alta del mismo, Usted volvera al menu"<< endl;
        return 0;
    }
    return 1;
    }

int TrabajadorExistenteyConbaja() /// se ingresa el id que quiere dar de alta
{
    int id;
    bool vali =false;
    while (vali==false){

        cout << "Ingrese el id del trabajador que desea dar de alta: ";
        cin >> id;
        if(ExisteIdTrabajadorConBaja(id)== false){

            colorError();
            coloresPrograma();
            vali=false;
            if(deseaContinuar()==false){
                return -1;
            }
            verTrabajadorconBaja();
        } else{
        vali=true;
        }
    }
    return id;
    }

bool ExisteIdTrabajadorConBaja(int id) /// se valida si existe el id de trabajador ingresado y si esta con baja
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
        if (id == idArchivo && trabajador.getEstadoTrabajador()==0)
        {
            fclose(p);
            return true;
        }

    }
    return false;
    fclose(p);
}

void subirTrabajador(int id) /// se realiza la alta del trabajador
{

    FILE* p;
    Trabajador trabajador;
    bool es = true;
    p = fopen("./trabajador.dat", "rb+");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while (fread(&trabajador, sizeof (Trabajador), 1, p)){
        if (id == trabajador.getIdTrabajador()){
            trabajador.setEstadoTrabajador(es);
            fseek(p, ftell(p) - sizeof (Trabajador), 0);
            fwrite(&trabajador, sizeof(Trabajador), 1, p);
            Pausa();
            fclose(p);
            return;
        }
    }
    fclose(p);
}


void verIdTrabajadoresyNombres() /// funcion para ver cuales son los trabajadores dados de alta
{

    char eleccion;

    cout << "Desea ver cuales son los trabajadores para realizar una asignacion adecuada a la venta? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){
            mostrarTrabajadores(1);
    cout << endl;
    }
}

