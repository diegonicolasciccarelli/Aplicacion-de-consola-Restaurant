#ifndef INFORMES_H_INCLUDED
#define INFORMES_H_INCLUDED
#include "menu.h"

void buscarVentasAnual();

void buscarVentasMensual();

void buscarVentasDelivery();

void buscarVentaslocal();

void buscarVentasxTipoPlato();

void buscarVentasxIdPlato();

void buscarVentasPorHorario();

int leerAlmuerzoArchivoVenta();
int leerCenaArchivoVenta();
int leerTipoPlatoenArchivoVenta(int);
int leerAnioenArchivoVenta(int);
void leerMesenArchivoVenta(int);
int leerDeliveryenArchivoVenta();
int leerLocalenArchivoVenta();
int leerIdPlatoenArchivoVenta(int);
bool existeVentasconAnio(int);
bool existeIdTrabajador(int);
int leerIdTrabajadorenArchivoVenta(int);
void buscarVentasPorIdTrabajador();


void buscarVentasPorTipo();
void comparativaTotal();
void importetotalxplato();
void platoMasVendido();

#endif // INFORMES_H_INCLUDED
