#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;
#include "fecha.h"
#include "trabajador.h"

Fecha::Fecha(int d, int m, int a){
    dia = d;
    mes = m;
    anio = a;
}

int Fecha::getDia(){
    return dia;
}
int Fecha::getMes(){
    return mes;
}
int Fecha::getAnio(){
    return anio;
}

void Fecha::setDia(int d){
    dia = d;
}
void Fecha::setMes(int m){
    mes = m;
}
void Fecha::setAnio(int a){
    anio = a;
}

void Fecha::mostrar(){
    cout<< "Fecha " << dia << "/" << mes << "/" << anio<< endl;
}
void Fecha::cargar(){
    cout << "Día: ";
    cin >> dia;
    cout << "Mes: ";
    cin >> mes;
    cout << "Año: ";
    cin >> anio;
}

void MostrarFechaLocal() /// muestra la fecha actual del sistema
{
    char* dS[7] = {"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};
   time_t tSac = time(NULL);       // instante actual
   struct tm* tmP = localtime(&tSac);
   cout << "Dia: " << dS[tmP->tm_wday] << endl;
   cout << "Fecha: " << tmP->tm_mday << "-" << tmP->tm_mon+1 << "-" << tmP->tm_year+1900 << endl;
   cout << "Hora: " << tmP->tm_hour << ":" << tmP->tm_min << ":" <<tmP->tm_sec << endl;
}
int ObtenerAnio() /// obtiene el año actual
{
    time_t currentTime = time(0);
    tm* ltm = localtime(&currentTime);
    return ltm->tm_year + 1900;
}

