#ifndef TRABAJADOR_H_INCLUDED
#define TRABAJADOR_H_INCLUDED
#include "persona.h"
#include "fecha.h"




class Trabajador : public Persona {

    private:
    int TipoTrabajador;
    bool estadoTrabajador;
    int IdTrabajador;
    int DiaIngreso;
    int MesIngreso;
    int AnioIngreso;

    public:
    Trabajador();

    int getTipoTrabajador();
    bool getEstadoTrabajador();
    int getIdTrabajador();
    int getDiaIngreso();
    int getMesIngreso();
    int getAnioIngreso();


    void setTipoTrabajador(int);
    void setEstadoTrabajador(bool);
    void setIdTrabajador(int);
    void setDiaIngreso(int);
    void setMesIngreso(int);
    void setAnioIngreso(int);

    void cargar();
    void mostrar();
    void escribirArchivo();
    void leerArchivo();

    void validarFechaTrabajador(int);


};

    void mostrarTrabajadores(int);
    void cabeceraTrabajadores();
    void mostrarstringTipoTrabajador(int);
    int leerFechaNac(int);
    int validarTipoTrabajador();
    void mostrarNombreTrabajador(int);
    int asignarIdTrabajador();
    bool ValidoAnioIngreso(Fecha *, int);

    void bajarTrabajador(int);
    void dardeBajaTrabajador();
    int validamosSiHayTrabajadorAlta();
    int TrabajadorExistenteyConAlta();
    bool ExisteIdTrabajadorConAlta(int);
    void verTrabajadorconAlta();

    void subirTrabajador(int);
    void dardeAltaTrabajador();
    int TrabajadorExistenteyConbaja();
    void verTrabajadorconBaja();
    bool ExisteIdTrabajadorConBaja(int);
    int validamosSiHayTrabajadorBaja();
    void verIdTrabajadoresyNombres();




#endif // TRABAJADOR_H_INCLUDED
