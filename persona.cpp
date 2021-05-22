#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#include "rlutil.h"
#include "persona.h"
#include "cliente.h"
#include "menu.h"
#include "fecha.h"
#include "plato.h"




const char *FILE_PERSONA = "./persona.dat";

Persona::Persona(){
    Dni= 0;
    strcpy(Nombre, "Sin Nombre Registrado");
    strcpy(Apellido, "Sin Apellido Registrado");
    int DiaNacimiento = 0;
    int MesNacimiento = 0;
    int AnioNacimiento = 0;

}
int Persona::getDni(){
    return Dni;
}
char* Persona::getNombre(){
    return Nombre;
}

char* Persona::getApellido(){
    return Apellido;
    }
int Persona::getDiaNacimiento(){
    return DiaNacimiento;
    }
int Persona::getMesNacimiento(){
    return MesNacimiento;
    }
int Persona::getAnioNacimiento(){
    return AnioNacimiento;
    }

void Persona::setDni(int d){
    Dni=d;
}
void Persona::setNombre(char *n){
    strcpy(Nombre, n);
}
void Persona::setApellido(char* a){
    strcpy(Apellido, a);
}
void Persona::setDiaNacimiento(int fn){
    DiaNacimiento = fn;
}
void Persona::setMesNacimiento(int fn){
    MesNacimiento = fn;
}
void Persona::setAnioNacimiento(int fn){
    AnioNacimiento = fn;
}



void Persona::cargar() /// cargamos y validamos una persona
{
    setDni(validarDni());
    validarNombrePersona();
    validarApellidoPersona();
    validarFechaPersona();
    if(deseaContinuar()==false){
        return;
    }
    escribirArchivo();
}

bool validarDniValido (int dni)  ///validamos el numero de dni valio entre 5000000 y 99999999 millones
{

bool valida=false;

    if (dni > 5000000 && dni < 99999999){
        valida =true;
    }
    else {
        cout << "Por favor ingrese un dni valido"<< endl;
    }
return valida;
}

int validarDni()  ///validamos dni sea mayor a 0, que no exista en el archivo y llama a la funcion de los numeros de dni valio
{

bool vali = false;
    int Dni;

    while (!vali)
    {
        cout << "Dni : ";
        cin >> Dni;

        if (Dni <= 0)
        {
            cout << "El DNI ingresado es invalido. El DNI debe ser un valor entero positivo entre 5 y 100 millones, por favor ingreselo nuevamente...\n";
        }
            else if (existeDni(Dni)==1)
                {
            cout << "El DNI ingresado ya existe... por favor ingreselo nuevamente...\n";
            }
                else
                {
                vali= validarDniValido(Dni);
                }

    }
    return Dni;
}

bool existeDni(int Dni) /// valida si ya hay un dni con el mismo numero en el archivo
{
    FILE* p;
    Persona persona;
    p = fopen(FILE_PERSONA, "rb");
    if (p == NULL)
    {
        return 0;
    }
    while (fread(&persona, sizeof (Persona), 1, p) == 1)
    {
        if (Dni == persona.getDni())
        {
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return 0;
}

void Persona::validarNombrePersona() /// valida el nombre de la persona
{

    bool CadenaValida = false;

    while (!CadenaValida){

        char str[50];
        cout << "Ingrese nombre de la persona \n";
        cin.ignore();
        cin.getline(str, 50);

        if (str[0] == '\0')//La cadena está vacía
        {
            cout << "El valor ingresado es invalido, por favor ingreselo nuevamente...\n";
        }
        else
        {
            CadenaValida = true;
            setNombre(str);
        }
    }
}


void Persona::validarApellidoPersona() /// valida el apellido de la persona
{

    bool CadenaValida = false;

    while (!CadenaValida){

        char str[50];
        cout << "Ingrese apellido de la persona \n";
        cin.getline(str, 50);

        if (str[0] == '\0')//La cadena está vacía
        {
            cout << "El valor ingresado es invalido, por favor ingreselo nuevamente...\n";
        }
        else if (comparoNombreconApellido(str)==0)
            {
            cout << "No es valido tener el mismo apellido y nombre, por favor ingreselo nuevamente...\n";
            colorError();
            }
        else
        {
            CadenaValida = true;
            setApellido(str);
        }
    }
}

int comparoNombreconApellido(char *str) /// evaluamos si el nombre y el apéllido son iguales
{

    FILE* p;
    Persona persona;

    p = fopen("./persona.dat", "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        cout << "El archivo aún no existe." << endl;
        return -1;
    }

    while(fread(&persona, sizeof (Persona), 1, p)){
        if(strcmp(str,persona.getNombre()) == 0){
           return 0;
        }
    }
    return 1;
    fclose(p);
}

void Persona::validarFechaPersona() ///ingresamos la fecha de nacimiento, se valida y se asigna.
{

    bool ValidarFecha=false;

    Fecha fecha;
    cout << "Ingrese su fecha de nacimiento: " << endl;
    while (ValidarFecha==false){
    ValidarFecha= ValidoAnioNacimiento(&fecha);
    }
    setDiaNacimiento(fecha.getDia());
    setMesNacimiento(fecha.getMes());
    setAnioNacimiento(fecha.getAnio());
}

bool ValidoAnioNacimiento(Fecha *fecha) /// validamos si es una fecha valida y si cumple con un anio valido

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
    else if (anioActual - fecha->getAnio() < 13)
    {
        cout << "La fecha ingresada es una fecha invalida, el usuario no puede ser menor de 13 años por favor ingresela nuevamente...\n";
    }
    else
    {
        ValidarFecha = true;
    }

    return ValidarFecha;
}

bool validarFecha(Fecha *fecha) /// Valida una fecha. No permite utilizar dias invalidos.
{
    bool validarFecha = false;

    if (fecha->getAnio() >= 0)
    {
        switch (fecha->getMes()) {

        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (fecha->getDia() >= 1 && fecha->getDia() <= 31) {
                validarFecha = true;
            };
            break;

        case 4: case 6: case 9: case 11:
            if (fecha->getDia() >= 1 && fecha->getDia() <= 30) {
                validarFecha = true;
            };
            break;
        case 2:
            //Si el año es bisiesto se suma un día.
            if ((fecha->getAnio()  % 4 == 0) && (fecha->getAnio() % 100 != 0) || (fecha->getAnio() % 400 == 0)) {
                if (fecha->getDia() >= 1 && fecha->getDia() <= 29) {
                    validarFecha = true;
                };
            }
            else {
                if (fecha->getDia() >= 1 && fecha->getDia() <= 28) {
                    validarFecha = true;
                };
            };
            break;
        default:
            break;
        };
    }

    return validarFecha;
}

void Persona::mostrar()  /// muestra los atributos de una persona
{
    int x = 5, y = 5;
    recuadroPlato(x, y, 40, 11);
    gotoxy(x,y+2);
    cout << "*****************************************";
    gotoxy(x,y+3);
    cout << "\t" << "Nombre:    " << "\t"  << Nombre;
    gotoxy(x,y+4);
    cout << "\t"<< "Apellido:   " << "\t"  << Apellido;
    gotoxy(x,y+5);
    cout << "\t"<< "Nacimiento: " << "\t"  << DiaNacimiento << " / "<< MesNacimiento << " / "<< AnioNacimiento << endl;
    gotoxy(x,y+6);
    cout << "\t"<< "Dni:        " << "\t" <<Dni;
    rlutil::setColor(rlutil::LIGHTGREEN);
    coloresPrograma();
}

void Persona::escribirArchivo() /// escribe el archivo de persona
{
    FILE* p;
    p = fopen(FILE_PERSONA, "ab");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    fwrite(this, sizeof (Persona), 1, p);
    colorCorrecto();
    coloresPrograma();
    fclose(p);
    return;
}

void Persona::leerArchivo()  /// leemos el archivo por un id de persona que se ingresa
{
    FILE* p;
    Persona persona;
    int dni;
    cout << "Ingrese el ID de la persona que quisiera visualizar: " << endl;
    cin >> dni;
    p = fopen(FILE_PERSONA, "rb");
    if (p == NULL)
    {
        colorError();
        coloresPrograma();
        return;
    }
    while(fread(&persona, sizeof (Persona), 1, p)){
        if(dni == persona.Dni){
            persona.mostrar();
        }

    }
}
