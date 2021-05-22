#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void LimpiarPantalla();
void entradaIncorrecta();
void Pausa();

void coloresPrograma();
void colorError();
void colorCorrecto();
void recuadroPlato(int,int,int,int);
void liho(int);
void lihoCarta();
void barraVertical(int,int,int);
void barraVerticalCarta(int,int,int,int,int,int);

bool AjustarVentana(int Ancho, int Alto);
void MainMenu();
void mostrarMainMenu();
int entradaMainMenu();

void menuPlatos();
void mostrarMenuPlatos();
int entradaMenuPlatos();

void menuTrabajadores();
void mostrarMenuTrabajadores();
int entradaMenuTrabajadores();

void menuVentas();
void mostrarMenuVentas();
int entradaMenuVentas();

void menuInformes();
void mostrarMenuInformes();
int entradaMenuInformes();


#endif // MENU_H_INCLUDED
