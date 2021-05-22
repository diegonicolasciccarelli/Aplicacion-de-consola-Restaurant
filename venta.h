#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED
#include "fecha.h"




class Venta {

    private:
    int idVenta;
    int DiaVenta;
    int MesVenta;
    int AnioVenta;
    int idCliente;
    int idTrabajador;
    int importeTotal;
    int horarioComida; // Almuerzo(1) Cena(2)
    bool envio;
    char formaPago[15]; // e, c, d

    public:
    Venta();
    int getIdVenta();
    int getIdCliente();
    int getIdTrabajador();
    int getHorarioComida();
    int getImporteTotal();
    char* getFormaPago();
    bool getEnvio();
    int getDiaVenta();
    int getMesVenta();
    int getAnioVenta();

    void setIdVenta(int);
    void setFormaPago(int);
    void setIdCliente(int);
    void setImporteTotal(int);
    void setIdTrabajador(int);
    void setHorarioComida(int);
    void setDiaVenta(int);
    void setMesVenta(int);
    void setAnioVenta(int);
    void setEnvio(bool);


    void cargar();
    void mostrar();
    void escribirArchivo();
    void leerArchivo();



    void mostrarVentas();
    void muestraVentas(int, Venta*);
    void validarFechaVenta();


};
    void cabeceraDetalle();
    void cabeceraVentas();
    int asignarIdVenta();
    int validarIdVenta();
    int validarFormaPagoVenta();
    bool validarEnvio();
    int validarIdClienteVenta();
    int validarIdTrabajadordeVenta();
    bool ValidoAnioVenta(Fecha *);
    void verOpcionesEnvio();
    void verOpcionesPago();
    void mostrarEnvio(bool);
    int validarIdClientedeVenta();

    void mostrarTodoUnDetalle();
    void mostrarDelivery();
    void mostrarLocal();

    bool existeIdTrabajadorVenta(int);



#endif // VENTA_H_INCLUDED
