#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED
#include "fecha.h"




class Persona {

    protected:
    int Dni;
    char Nombre[50];
    char Apellido [50];
    int DiaNacimiento;
    int MesNacimiento;
    int AnioNacimiento;

    public:
    Persona();
    int getDni();
    char* getNombre();
    char* getApellido();
    int getDiaNacimiento();
    int getMesNacimiento();
    int getAnioNacimiento();

    void setDiaNacimiento(int);
    void setMesNacimiento(int);
    void setAnioNacimiento(int);
    void setDni(int);
    void setNombre(char*);
    void setApellido(char*);

    void cargar();
    void mostrar();
    void escribirArchivo();
    void leerArchivo();

    void validarApellidoPersona();
    void validarNombrePersona();
    void validarFechaPersona();

};

    void validarFechaNacimiento();
    bool existeDni(int);
    int validarDni();
    bool ValidoAnioNacimiento(Fecha*);
    bool validarFecha(Fecha*);
    int comparoNombreconApellido(char *str);

#endif // PERSONA_H_INCLUDED
