#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "persona.h"

class Cliente : public  Persona{

    private:
    int IdCliente;
    int Telefono;
    bool EstadoCliente;

    public:
    Cliente();
    int getIdCliente();
    int getTelefono();
    bool getEstadoCliente();
    void setIdCliente(int);
    void setTelefono(int);
    void setEstadoCliente(bool);
    void cargar();
    void mostrar();
    void escribirArchivo();
    void leerArchivo();
};
    void mostrarNombreCliente(int);
    void mostrarClientes(int);
    void cabeceraCliente();

    void bajarCliente(int);
    void dardeBajaCliente();
    int validamosSiHayClientesAlta();
    int ClienteExistenteyConAlta();
    bool ExisteIdClienteConAlta(int);
    void verClientesconAlta();

    void subirCliente(int);
    void dardeAltaCliente();
    int ClienteExistenteyConbaja();
    void verClientesconBaja();
    bool ExisteIdClienteConBaja(int);
    int validamosSiHayClientesBaja();

    int validarIdCliente(int);
    bool existeIdTrabajador(int id);
    bool existeIdCliente(int);

    void verIdClientesyNombres();

#endif // CLIENTE_H_INCLUDED
