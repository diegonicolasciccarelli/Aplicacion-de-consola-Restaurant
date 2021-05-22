#ifndef PLATO_H_INCLUDED
#define PLATO_H_INCLUDED

class Plato {

    private:
    int idPlato, tipoPlato, stock;
    char nombrePlato[50];
    float precio;
    bool estado;

    public:
    Plato();
    int getIdPlato();
    int getTipoPlato();
    int getStock();
    char* getNombrePlato();
    float getPrecio();
    bool getEstado();

    void setIdPlato(int);
    void setNombrePlato(char*);
    void setTipoPlato(int);
    void setStock(int);
    void setPrecio(float);
    void setEstado(bool);

    void cargar();
    void mostrar();
    void escribirArchivo();
    void leerArchivo();

    void validarNombrePlato();

};
    /// Opcion del menu 1
    int asignarIdPlato();
    int validarTipoPlato();
    int validarStockPlato();
    float validarPrecioPlato();
    int ValidoNombreSinRepeticion(char* );

    /// opcion del menu 2
    void mostrarTipoPlato(int);
    void mostrarstringEstado(bool);

    /// opcion del menu 3
    void mostrarCarta();
    void mostrarEntrada(int);
    void mostrarPrincipal();
    void mostrarGuarnicion();
    void mostrarPostre();

    int mostrarElTipo(int,int);


    /// opcion del menu 4
    void modificarPlatoPorId();
    void modificarPrecio(int);
    void modificarStock(int);
    bool elecciondeModificarPrecio();
    bool elecciondeModificarStock();
    bool deseaContinuar();
    void mostrarplatosparamodificar();

    /// opcion del menu 5
    void bajarPlato(int);
    void dardeBajaPlato();
    int validamosSiHayPlatoAlta();
    int PlatoExistenteyConAlta();
    bool ExisteIdPlatoConAlta(int);
    void verPlatoconAlta();

    /// opcion del menu 6
    void subirPlato(int);
    void dardeAltaPlato();
    int PlatoExistenteyConbaja();
    void verPlatoconBaja();
    bool ExisteIdPlatoConBaja(int);
    int validamosSiHayPlatoBaja();

    void mostrarNombrePlato(int);
    bool existeIdPlato(int);
    bool existePlato(int);
    int recibirStock(int);
    void restarStock(int, int);
    int recibirImporte(int);
    void verIdPlatosyNombres();
    bool BuscamosyvalidamosIdPlato(int );





#endif // PLATO_H_INCLUDED
