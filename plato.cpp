#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#include "plato.h"
#include "menu.h"
#include "rlutil.h"


const char *FILE_PLATO = "./plato.dat";
int sw=0;
bool valida=false;
char nombre [50];

Plato::Plato(){
    idPlato = 0;
    tipoPlato = 0;
    stock = 0;
    strcpy(nombrePlato, " ");
    precio = 0;
    estado = false;
}

int Plato::getIdPlato(){
    return idPlato;
}
int Plato::getTipoPlato(){
    return tipoPlato;
}
int Plato::getStock(){
    return stock;
}
char* Plato::getNombrePlato(){
    return nombrePlato;
}
float Plato::getPrecio(){
    return precio;
}
bool Plato::getEstado(){
    return estado;
}

void Plato::setIdPlato(int p){
    idPlato = p;
}
void Plato::setNombrePlato(char *np){
    strcpy(nombrePlato, np);
}
void Plato::setTipoPlato(int t){
    tipoPlato = t;
}
void Plato::setStock(int s){
        stock = s;
}
void Plato::setPrecio(float p){
    precio = p;
}
void Plato::setEstado(bool e){
    estado = e;
}


void Plato::cargar() /// Realiza la carga de un plato.
{

    setIdPlato(asignarIdPlato());
    setTipoPlato(validarTipoPlato());
    if(deseaContinuar()==false){
        return;
    }
    setStock(validarStockPlato());
    setPrecio(validarPrecioPlato());
    validarNombrePlato();
    setEstado(1);
    mostrar();
    escribirArchivo();
    /// anykey
}

/// VALIDACIONES

int asignarIdPlato() /// Asigna un valor autonumerico al Id del plato
{
    int id = 0;
    FILE* p;
    Plato plato;
    p = fopen("plato.dat", "rb");
    if (p == NULL)
    {
        return 1;
    }

    while (fread(&plato, sizeof (Plato), 1, p))
    {
       id = plato.getIdPlato();

    }
    id += 1;
    cout << "Se le ha asignado el ID de plato " << id << endl;
    fclose(p);
    return id;
}

int validarTipoPlato() /// Valida que el tipo de plato sea un numero positivo de 1 a 4
{
    bool vali = false;
    int tipo;
    Plato plato;

    while (!vali){
        cout << "Ingrese el tipo de plato (1 para entrada, 2 para plato principal, 3 para guarnicion o 4 para postre)..." << endl;
        cin >> tipo;

        if (tipo >= 1 && tipo <= 4){
            vali = true;
            return tipo;
        }else{
            colorError();

        }
    }
}

int validarStockPlato() /// Valida que el stock sea un numero entero positivo o cero.
{
    bool vali = false;
    int stock;
    Plato plato;

    while (!vali){
        cout << "Ingrese el stock del plato: " << endl;
        cin >> stock;

        if (stock >= 0 ){
            plato.setStock(stock);
            vali = true;
        }else{
        colorError();
        }
    }
    return stock;
}

float validarPrecioPlato() /// Valida que el precio del plato sea un numero float positivo
{
    bool vali = false;
    float precio;
    Plato plato;

    while (!vali){
        cout << "Ingrese el precio del plato: " << endl;
        cin >> precio;

        if (precio > 0 ){
            plato.setPrecio(precio);
            vali = true;
        }else{
        colorError();
        }
    }
    return precio;
}

void Plato::validarNombrePlato() /// Valida que la cadena char del plato no esté vacía ni que se repitan nombres.
{

    bool CadenaValida = false;

    while (!CadenaValida){

        char str[50];
        cin.ignore();
        cout << "Ingrese nombre del plato \n";
        cin.getline(str, 50);

        if (str[0] == '\0')//La cadena está vacía
        {
            cout << "El valor ingresado es invalido, por favor ingreselo nuevamente...\n";
        }
            else if (ValidoNombreSinRepeticion(str)==0)
            {
            cout << "Ya existe un plato con el mismo nombre, por favor ingreselo nuevamente...\n";
            }
                else
                {
                    CadenaValida = true;
                    setNombrePlato(str);
                    }
    }
}

int ValidoNombreSinRepeticion(char *str) /// Funcion que valida que un nombre se repita. Se usa en validarNombrePlato
{

    FILE* p;
    Plato plato;
    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        cout << "El archivo no fue creado aún " << endl;
        return -1;
    }

    while(fread(&plato, sizeof (Plato), 1, p)){
        if(strcmp(str,plato.getNombrePlato()) == 0){
           return 0;
        }
    }
    return 1;
    fclose(p);
}



void Plato::escribirArchivo() /// Guarda un archivo de plato
{
    FILE* p;
    p = fopen(FILE_PLATO, "ab");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    fwrite(this, sizeof (Plato), 1, p);
    colorCorrecto();
    coloresPrograma();
    fclose(p);
    return;
}

void Plato::leerArchivo() /// Lee un archivo de plato buscando una coincidencia por ID de plato
{
    FILE* p;
    Plato plato;
    int id;
    bool bandera = false;


    cout << "Ingrese el ID del plato que quisiera visualizar: " << endl;
    cin >> id;
    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    LimpiarPantalla();
    while(fread(&plato, sizeof (Plato), 1, p)){
        if(id == plato.idPlato){
            plato.mostrar();
            bandera = true;
        }
    }
    if(bandera==false){
        colorError();

        cout << "El id de plato que selecciono no existe." << endl;
        Pausa();


    }


    fclose(p);
}



void Plato::mostrar() /// Muestra un archivo de plato
{
    LimpiarPantalla();
    int x = 5, y = 5;
    recuadroPlato(x, y, 40, 9);
    gotoxy(x,y+1);
    cout << "\t"<<"Plato de " << nombrePlato;
    gotoxy(x,y+2);
    cout << "*****************************************";
    gotoxy(x,y+3);
    cout << "\t" << "Id del plato: " << "\t"  << idPlato;
    gotoxy(x,y+4);
    cout << "\t"<< "Precio:       " << "\t"  << "$" << precio;
    gotoxy(x,y+5);
    cout << "\t"<< "Stock:        " << "\t"  << stock << " (Porciones)";
    gotoxy(x,y+6);
    cout << "\t"<< "Tipo: "<< "\t"<< "\t";
    mostrarTipoPlato(tipoPlato); //// se muestra tipo de plato el string
    gotoxy(x,y+7);
    mostrarstringEstado(estado); ///ESTADO SE MUESTRA
    rlutil::setColor(rlutil::LIGHTGREEN);
    gotoxy(x+1,y+10);
    system("pause");
    gotoxy(x+1,y+12);
    coloresPrograma();


}

void mostrarTipoPlato(int tipoPlato) /// Funcion de "mostrar()" para el tipo de plato
{

    switch (tipoPlato){

        case 1:
        cout << "Entrada";
        break;
        case 2:
        cout << "Plato Principal";
        break;
        case 3:
        cout << "Guarnicion";
        break;
        case 4:
        cout << "Postre";
        break;
    }
}

void mostrarstringEstado(bool estado ) /// Funcion de "mostrar()" para el estado del plato
{

    if (estado == 1){
        cout << "\t"<< "Estado: " << "\t"  << "Activo";
    }
    else{
        cout << "\t"<< "Estado: " << "\t"  << "De Baja";
    }
}




void mostrarCarta() /// Muestra todos los platos existentes ordenados por tipo de plato
{
    int col=6;
    LimpiarPantalla();
    col = mostrarElTipo(col, 1);
    Pausa();
    col = mostrarElTipo(col, 2);
    Pausa();
    col = mostrarElTipo(col, 3);
    Pausa();
    col = mostrarElTipo(col, 4);
    colorCorrecto();
    Pausa();
}

void datosPlato(){
gotoxy(1, 1);
lihoCarta();
gotoxy(30, 2);
rlutil::setColor(rlutil::LIGHTGREEN);
cout << "LA CARTA  \n";
rlutil::setColor(rlutil::WHITE);
gotoxy(1, 3);
lihoCarta();
barraVertical(68,68,2);
gotoxy(2, 4);
cout << "ID";
gotoxy(6, 4);
cout << "NOMBRE";
gotoxy(35, 4);
cout << "PRECIO";
gotoxy(45, 4);
cout << "STOCK";
gotoxy(53, 4);
cout << "TIPO" << endl;
lihoCarta();
barraVerticalCarta(5, 33, 43, 51, 68, 4);
}

int mostrarElTipo(int col, int tipo){
    FILE* p;
    Plato plato;
    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return -1;
    }
    datosPlato();
    while(fread(&plato, sizeof (Plato), 1, p)){
    if(plato.getEstado() == 1 && plato.getTipoPlato() == tipo ){
    gotoxy(2, col);
    cout << plato.getIdPlato();
    gotoxy(6, col);
    cout << plato.getNombrePlato();
    gotoxy(35, col);
    cout << "$ " << plato.getPrecio();
    gotoxy(45, col);
    cout << plato.getStock();
    gotoxy(53,col);
    mostrarTipoPlato(tipo);
    barraVerticalCarta(5, 33, 43, 51, 68, col);
    col++;
    }
    }
    cout << endl;
    lihoCarta();
    return col+1;


}


void modificarPlatoPorId() /// Funcion para modificar atributos de un plato por ID
{
    LimpiarPantalla();
    int id;
    FILE* p;

    bool validaID=false;


    while(validaID==false){  ///valido que exista el id que ingresa para modificar
        cout << "Ingrese el id del plato que desea modificar: ";
        cin >> id;
        validaID=existeIdPlato(id);
        if (validaID==false){
            colorError();

            if (deseaContinuar()==false){  ////vuelvo al menu anterior si no quiere continuar en la opcion

                return;
            }
            verPlatoconAlta();
        }
    }

    modificarPrecio(id);
    if(deseaContinuar()==false){

        return;
    }
    modificarStock(id);

}

void modificarPrecio(int id) /// Funcion para modificar el precio de un plato. Se utiliza en modificarPlatoPorId
{
    Plato plato;
    FILE* p;
    float pr;
    bool validaID=false;
    p = fopen("./plato.dat", "rb+");

    if (p == NULL)
    {
        cout << "Error de archivo. Nombre de archivo: " << "./platos.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&plato, sizeof (Plato), 1, p))
    {
        if (id == plato.getIdPlato())
        {
            plato.mostrar();
            if(elecciondeModificarPrecio()==true){
            LimpiarPantalla();
            plato.setPrecio(validarPrecioPlato());
            fseek(p, ftell(p) - sizeof (Plato), 0);
            fwrite(&plato, sizeof(Plato), 1, p);
            fclose(p);
            cout << "Opcion elegida correctamente, continuamos con el stock" << endl;
            colorCorrecto();
            }
        }
    }
    fclose(p);
}

void modificarStock(int id)  /// Funcion para modificar el stock de un plato. Se utiliza en modificarPlatoPorId
{
    Plato plato;
    FILE* p;
    float pr;
    bool validaID=false;
    p = fopen("./plato.dat", "rb+");

    if (p == NULL)
    {
        cout << "Error de archivo. Nombre de archivo: " << "./platos.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&plato, sizeof (Plato), 1, p))
    {
        if (id == plato.getIdPlato())
        {

            if(elecciondeModificarStock()==true){
            plato.setStock(validarStockPlato());
            fseek(p, ftell(p) - sizeof (Plato), 0);
            fwrite(&plato, sizeof(Plato), 1, p);
            fclose(p);
            cout << "Opcion elegida correctamente, se volvera al menu de platos" << endl;
            colorCorrecto();
            }
        }
    }
    fclose(p);

}

bool elecciondeModificarPrecio() /// Pregunta si se desea modificar el precio
{
    bool valido = false;
    char eleccion;
    cout << "Desea modificar el precio del plato? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){

        valido=true;
    }
 return valido;
}

bool elecciondeModificarStock() /// Pregunta si se desea modificar el precio
{
    bool valido = false;
    char eleccion;
    cout << "Desea modificar el stock del plato? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){

        valido=true;
    }
 return valido;
}

bool deseaContinuar() /// Pregunta si se continuar en la opcion del menu que escogiste
{
    bool valido = false;
    char eleccion;
    coloresPrograma();
    cout << "Desea continuar en esta opcion del menu? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){
        valido=true;
    }else{
    cout << "Usted volvera al menu anterior, no se ha completado esta opcion del menu" << endl;
    }
 return valido;
}


///// bajar plato

void dardeBajaPlato() /// funcion del menu principal para bajar plato
{
    int id;

    if(validamosSiHayPlatoAlta()==0){
        return;
    }
    verPlatoconAlta();
    id=PlatoExistenteyConAlta();
    if(id==-1){
        return;
    }
    bajarPlato(id);
}

int validamosSiHayPlatoAlta() /// Valida si hay platos dados de alta. Si no existen vuelve al menu anterior
{
int cont=0;
    FILE* p;
    Plato plato;
    int idArchivo;
    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        return -1;
    }
    while (fread(&plato, sizeof (Plato), 1, p) == 1)
    {
        idArchivo = plato.getIdPlato();
        if (plato.getEstado()==1)
        {
            cont ++;
            fclose(p);
        }
    }
    if (cont==0){
        fclose(p);
        cout << "No hay platos dados de alta para realizar la baja del mismo, Usted volvera al menu"<< endl;
        return 0;
    }
    return 1;
    fclose(p);
    }

int PlatoExistenteyConAlta()  /// Se ingresa el id que quiere dar de baja para ver si existe
{
    int cont=0, id;
    bool vali =false;
    while (vali==false){

        cout << "Ingrese el id del plato que desea dar de baja: ";
        cin >> id;
        if(ExisteIdPlatoConAlta(id)== false){

            colorError();
            coloresPrograma();
            vali=false;
            if(deseaContinuar()==false){
                return -1;
            }
        verPlatoconAlta();
        } else{
        vali=true;
        colorCorrecto();
        }
    }
    return id;
    }

bool ExisteIdPlatoConAlta(int id) /// Valida si existe el id de plato ingresado y si esta con alta. Se utiliza en la funcion de arriba
{
    FILE* p;
    Plato plato;
    int idArchivo;

    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&plato, sizeof (Plato), 1, p) == 1)
    {
        idArchivo = plato.getIdPlato();
        if (id == idArchivo && plato.getEstado()==1)
        {
            fclose(p);
            return true;
        }

    }
    return false;
    fclose(p);
}

void verPlatoconAlta() /// Muestra todos los platos que esten con alta
{

    char eleccion;

    cout << "Desea ver cuales son los platos dados de alta o ya conoce el id de Plato que quiere dar de baja? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){
        FILE* p;
        Plato plato;
        int col = 6;
        p = fopen("./plato.dat", "rb");
        if (p == NULL)
        {
        colorError();
        coloresPrograma();
        return;
        }
        LimpiarPantalla();
        liho(50);
        gotoxy(3,2);
        cout << "LOS PLATOS DADOS DE ALTA SON  \n";
        liho(50);
        barraVertical(50, 50, 2);
        while(fread(&plato, sizeof (Plato), 1, p)){
        if(plato.getEstado() == 1){
        gotoxy(3,4);
        cout << "ID";
        barraVertical(7, 50, 4);
        gotoxy(9,4);
        cout << "NOMBRE ";
        gotoxy(1,5);
        liho(50);
        barraVertical(7, 50, col);
        gotoxy(3,col);
        cout << plato.getIdPlato();
        gotoxy(9,col);
        cout << plato.getNombrePlato();
        col++;
        }
        }
        cout << endl;
        liho(50);
        gotoxy(1, col+1);
        fclose(p);
    }
}

void bajarPlato(int id) /// Modifica el estado de un plato que estaba de alta a 0. (Lo da de baja)
{
    FILE* p;
    Plato plato;
    bool es = false;
    p = fopen("./plato.dat", "rb+");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while (fread(&plato, sizeof (Plato), 1, p)){
        if (id == plato.getIdPlato()){
            plato.setEstado(es);
            fseek(p, ftell(p) - sizeof (Plato), 0);
            fwrite(&plato, sizeof(Plato), 1, p);
            fclose(p);
            return;
        }
    }
    fclose(p);
}

///// subir plato

void dardeAltaPlato() /// funcion del menu principal para subir plato
{
    int id;
    if(validamosSiHayPlatoBaja()==0){
        return;
    }
    verPlatoconBaja();
    id=PlatoExistenteyConbaja();
    if(id==-1){
        return;
    }
    subirPlato(id);
}

int validamosSiHayPlatoBaja() /// Valida si hay platos dados de baja. Si no existen vuelve al menu anterior
{
int cont=0;
    FILE* p;
    Plato plato;
    int idArchivo;
    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        return -1;
    }
    while (fread(&plato, sizeof (Plato), 1, p) == 1)
    {
        idArchivo = plato.getIdPlato();
        if (plato.getEstado()==0)
        {
            cont ++;
            fclose(p);
        }
    }
    if (cont==0){
        fclose(p);
        cout << "No hay platos dados de baja para realizar el alta del mismo, Usted volvera al menu"<< endl;
        return 0;
    }
    return 1;
    }

int PlatoExistenteyConbaja()  /// Se ingresa el id que quiere dar de alta para ver si existe
{
    int cont=0, id;
    bool vali =false;
    while (vali==false){

        cout << "Ingrese el id del plato que desea dar de alta: ";
        cin >> id;
        if(ExisteIdPlatoConBaja(id)== false){

            colorError();
            coloresPrograma();
            vali=false;
            if(deseaContinuar()==false){
                cout << "Usted volvera al menu anterior";
                return -1;
            }
        verPlatoconBaja();

        } else{
        vali=true;
        colorCorrecto();
        }
    }
    return id;
    }

bool ExisteIdPlatoConBaja(int id)  /// Valida si existe el id de plato ingresado y si esta con baja. Se utiliza en la funcion de arriba
{
    FILE* p;
    Plato plato;
    int idArchivo;

    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&plato, sizeof (Plato), 1, p) == 1)
    {
        idArchivo = plato.getIdPlato();
        if (id == idArchivo && plato.getEstado()==0)
        {
            fclose(p);
            return true;
        }

    }
    return false;
    fclose(p);
}

void subirPlato(int id)  /// Modifica el estado de un plato que estaba de baja a 1. (Lo da de alta)
{

    FILE* p;
    Plato plato;
    bool es = true;
    p = fopen("./plato.dat", "rb+");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while (fread(&plato, sizeof (Plato), 1, p)){
        if (id == plato.getIdPlato()){
            plato.setEstado(es);
            fseek(p, ftell(p) - sizeof (Plato), 0);
            fwrite(&plato, sizeof(Plato), 1, p);
            fclose(p);
            return;
        }
    }
    fclose(p);
}

void verPlatoconBaja()  /// Muestra todos los platos que esten con baja
{

    char eleccion;
    cout << "Desea ver cuales son los platos dados de baja o ya conoce el id de plato que quiere dar de alta? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){
        LimpiarPantalla();
        FILE* p;
        Plato plato;
        int col = 6;
        p = fopen("./plato.dat", "rb");
        if (p == NULL)
        {
        colorError();
        coloresPrograma();
        return;
        }
        liho(50);
        gotoxy(3,2);
        cout << "  LOS PLATOS DADOS DE BAJA SON:  \n";
        liho(50);
        barraVertical(50,50,2);
        while(fread(&plato, sizeof (Plato), 1, p)){
        if(plato.getEstado() == 0){
        gotoxy(3,4);
        cout << "ID";
        gotoxy(9,4);
        cout << "NOMBRE ";
        gotoxy(1,5);
        liho(50);
        barraVertical(7,50,4);
        barraVertical(7,50,col);
        gotoxy(3,col);
        cout << plato.getIdPlato();
        gotoxy(9,col);
        cout << plato.getNombrePlato();
        col++;
        }
        }
        cout << endl;
        liho(50);
        gotoxy(3, col+1);
        fclose(p);
    }
}



/// Funciones de Plato que se usan en DETALLEVENTA.CPP

void mostrarNombrePlato(int id) /// Abre el archivo de platos para mostrar un nombre segun el ID de plato que le brindemos.
{

    FILE* p;
    Plato plato;
    char str[50];
    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while(fread(&plato, sizeof (Plato), 1, p)){
        if(id == plato.getIdPlato()){
            strcpy(str,plato.getNombrePlato());
            cout << str << endl;
            }

    }
    fclose(p);
}

bool existeIdPlato(int id) /// Funcion que valida que exista un ID de plato que le brindemos y muestra que nombre es.
{
    FILE* p;
    Plato plato;
    int idArchivo;
    char nombrePlato[50];

    p = fopen(FILE_PLATO, "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&plato, sizeof (Plato), 1, p) == 1)
    {
        idArchivo = plato.getIdPlato();
        if (id == idArchivo)
           {
           strcpy(nombrePlato, plato.getNombrePlato());
           cout << nombrePlato;
            fclose(p);
            return 1;
        }
    }

    fclose(p);
    return 0;
}

bool existePlato(int id) /// Funcion que valida que exista un ID de plato que le brindemos
{
    FILE* p;
    Plato plato;
    int idArchivo;

    p = fopen(FILE_PLATO, "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&plato, sizeof (Plato), 1, p) == 1)
    {
        idArchivo = plato.getIdPlato();
        if (id == idArchivo)
           {fclose(p);
            return 1;
        }
    }

    fclose(p);
    return 0;
}

int recibirStock (int id) /// Devuelve el stock de un archivo de plato con el ID que le brindemos
{
    FILE* p;
    Plato plato;
    int stock = 0;

    p = fopen("./plato.dat", "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&plato, sizeof (Plato), 1, p) == 1)
    {
        if (id == plato.getIdPlato()){
            stock = plato.getStock();
        }

    }
    fclose(p);
    return stock;
}

void restarStock (int platos, int id) /// Funcion que resta un stock determinado por los platos de una venta.
{
    FILE* p;
    Plato plato;
    int stock = 0;

    p = fopen("./plato.dat", "rb+");
    if (p == NULL)
    {
        return;
    }
    while (fread(&plato, sizeof (Plato), 1, p) == 1)
    {
        if (id == plato.getIdPlato()){
            stock = plato.getStock() - platos;
            plato.setStock(stock);
            fseek(p, ftell(p) - sizeof (Plato), 0);
            fwrite(&plato, sizeof (Plato), 1, p);
            Pausa();
            fclose(p);
            return;
        }

    }
    fclose(p);


}

int recibirImporte(int id) /// Funcion que devuelve el precio de un plato para utilizarlo en la venta.
{
    FILE* p;
    Plato plato;
    int importe = 0;

    p = fopen(FILE_PLATO, "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&plato, sizeof (Plato), 1, p) == 1)
    {
        if (id == plato.getIdPlato()){
            importe = plato.getPrecio();
        }

    }
    fclose(p);
    return importe;
}


void verIdPlatosyNombres() /// funcion para ver cuales son los platos dados de alta / Se usa en detalle venta
{

    char eleccion;

    cout << "Desea ver cuales son los platos para realizar una asignacion adecuada a la venta? S/N" << endl;
    cin >> eleccion;
    if(eleccion== 'S' || eleccion == 's'){
        FILE* p;
        Plato plato;
        int col = 3;
        LimpiarPantalla();
        p = fopen("./plato.dat", "rb");
        if (p == NULL)
        {
        colorError();
        coloresPrograma();
        return;
        }
        cout << "  PLATOS" << endl;
        while(fread(&plato, sizeof (Plato), 1, p)){
        if(plato.getEstado() == 1){
        gotoxy(3,2);
        cout << "ID";
        gotoxy(9,2);
        cout << "NOMBRE ";
        gotoxy(3,col);
        cout << plato.getIdPlato();
        gotoxy(9,col);
        cout << plato.getNombrePlato();
        col++;
        }
        }
        fclose(p);
    }
}


bool BuscamosyvalidamosIdPlato(int id) {/// Funcion que valida que exista un ID de plato que le brindemos
    FILE* p;
    Plato plato;
    int idArchivo;

    p = fopen(FILE_PLATO, "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&plato, sizeof (Plato), 1, p) == 1)
    {
        idArchivo = plato.getIdPlato();
        if (id == idArchivo)
           {
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return 0;
}




