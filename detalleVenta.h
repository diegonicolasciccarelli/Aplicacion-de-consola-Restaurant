#ifndef DETALLEVENTA_H_INCLUDED
#define DETALLEVENTA_H_INCLUDED
#include "venta.h"
#include "fecha.h"

class detalleVenta {
    private:

        int idVenta; // id de la venta
        int idPlatoVenta; // id de un plato de la venta
        int cantPorPlato; // cantidad vendida por el id plato de este detalle
        float importe;

    public:
        detalleVenta();

        int getIdPlatoVenta();
        int getCantPorPlato();
        int getIdVenta();
        float getImporte();

        void setIdPlatoVenta(int);
        void setCantPorPlato(int);
        void setIdVenta(int);
        void setImporte(float);

        int cargarDetalle(int);
        void mostrar();
        void escribirArchivo();
        void leerArchivo();

        void muestraDetalle(int,int);


};

        void modificarVentaPorId();
        int CargaDetalle(int);
        int validarIdPlatoVenta();
        void leerArchivodeIdVenta(int,int,int);
        bool opcionOtroPlato();


#endif // DETALLEVENTA_H_INCLUDED
