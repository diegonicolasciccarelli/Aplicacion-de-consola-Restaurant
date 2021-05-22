#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>

using namespace std;

#include "rlutil.h"
#include "venta.h"
#include "menu.h"
#include "fecha.h"
#include "cliente.h"
#include "trabajador.h"
#include "persona.h"
#include "detalleVenta.h"
#include "informes.h"
#include "plato.h"



int Rng(){  /// Generador de numeros al azar
int i;
srand ( time ( NULL ));
    i =1 + rand ()% 999 ;
    return i;
}

void codigoSeguridad(){
    LimpiarPantalla();
    int w, i;
    i= Rng();
    cout << "EL PIN DE SEGURIDAD AUTOMATICO ES: " << i << endl;
    cout << "Para confirmar, ingrese el pin de seguridad que se genero automaticamente en pantalla, por favor " << endl;
    cin >> w;
    while (w != i) {
        colorError();
        coloresPrograma();
        cout << "EL PIN DE SEGURIDAD AUTOMATICO ES: " << i << endl;
        cout << "Para confirmar, ingrese el pin de seguridad que se genero automaticamente en pantalla, por favor " << endl;
        cin >> w;
    }
    colorCorrecto();
    Pausa();
}

void guardarBackupPlato() { /// Transfiere los registros de plato.dat a plato.bkp

    Plato plato;

    FILE* pFile;
    FILE* backupFile;


    pFile = fopen("./plato.dat", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./plato.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }

    backupFile = fopen("./plato.bkp", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./plato.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&plato, sizeof (Plato), 1, pFile) == 1)
    {
        fwrite(&plato, sizeof (Plato), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}

void guardarBackupPersona() { /// Transfiere los registros de persona.dat a  persona.bkp

    Persona persona;

    FILE* pFile;
    FILE* backupFile;


    pFile = fopen("./persona.dat", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./persona.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    backupFile = fopen("./persona.bkp", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./persona.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&persona, sizeof (Persona), 1, pFile) == 1)
    {
        fwrite(&persona, sizeof (Persona), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}
void guardarBackupCliente() { /// Transfiere los registros de cliente.dat y persona.dat a cliente y persona.bkp

    Cliente cliente;

    FILE* pFile;
    FILE* backupFile;

    pFile = fopen("./cliente.dat", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./cliente.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    backupFile = fopen("./cliente.bkp", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./cliente.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&cliente, sizeof (Cliente), 1, pFile) == 1)
    {
        fwrite(&cliente, sizeof (Cliente), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}

void guardarBackupTrabajador() { /// Transfiere los registros de trabajador.dat y persona.dat a trabajador y persona.bkp

    Trabajador trabajador;

    FILE* pFile;
    FILE* backupFile;


    pFile = fopen("./trabajador.dat", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./trabajador.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    backupFile = fopen("./trabajador.bkp", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
       cout << "Error de archivo. Nombre de archivo: " << "./trabajador.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&trabajador, sizeof (Trabajador), 1, pFile) == 1)
    {
    fwrite(&trabajador, sizeof (Trabajador), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}

void guardarBackupdetalleVenta() { /// Transfiere los registros de detalleventa.dat a detalleventa.bkp

    detalleVenta detalleventa;

    FILE* pFile;
    FILE* backupFile;

    pFile = fopen("./detalleventa.dat", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./detalleventa.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    backupFile = fopen("./detalleventa.bkp", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./detalleventa.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&detalleventa, sizeof (detalleVenta), 1, pFile) == 1)
    {
        fwrite(&detalleventa, sizeof (detalleVenta), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}

void guardarBackupVenta() { /// Transfiere los registros de venta.dat y detalleventa.dat a venta y detalleventa.bkp

    Venta venta;

    FILE* pFile;
    FILE* backupFile;

    pFile = fopen("./venta.dat", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./venta.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    backupFile = fopen("./venta.bkp", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./venta.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&venta, sizeof (Venta), 1, pFile) == 1)
    {
        fwrite(&venta, sizeof (Venta), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}


///////////////////////////////////////////////

void cargarBackupPlato() {

    Plato plato;

    FILE* pFile;
    FILE* backupFile;

    pFile = fopen("./plato.bkp", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./plato.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    backupFile = fopen("./plato.dat", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./plato.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
        while (fread(&plato, sizeof (Plato), 1, pFile) == 1)
    {
        fwrite(&plato, sizeof (Plato), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}

void cargarBackupPersona() {

    Persona persona;

    FILE* pFile;
    FILE* backupFile;


    pFile = fopen("./persona.bkp", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./persona.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    backupFile = fopen("./persona.dat", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./persona.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&persona, sizeof (Persona), 1, pFile) == 1)
    {
        fwrite(&persona, sizeof (Persona), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}

void cargarBackupCliente() {

    Cliente cliente;

    FILE* pFile;
    FILE* backupFile;

    pFile = fopen("./cliente.bkp", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./cliente.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    backupFile = fopen("./cliente.dat", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
        {
    cout << "Error de archivo. Nombre de archivo: " << "./cliente.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&cliente, sizeof (Cliente), 1, pFile) == 1)
    {
        fwrite(&cliente, sizeof (Cliente), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}

void cargarBackupTrabajador() {

    Trabajador trabajador;

    FILE* pFile;
    FILE* backupFile;

    pFile = fopen("./trabajador.bkp", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./trabajador.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    backupFile = fopen("./trabajador.dat", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./trabajador.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&trabajador, sizeof (Trabajador), 1, pFile) == 1)
    {
        fwrite(&trabajador, sizeof (Trabajador), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}
void cargarBackupdetalleVenta() {

    detalleVenta detalleventa;

    FILE* pFile;
    FILE* backupFile;
    pFile = fopen("./detalleventa.bkp", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./detalleventa.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    backupFile = fopen("./detalleventa.dat", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./detalleventa.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&detalleventa, sizeof (detalleVenta), 1, pFile) == 1)
    {
        fwrite(&detalleventa, sizeof (detalleVenta), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);

}

void cargarBackupVenta() {

    Venta venta;

    FILE* pFile;
    FILE* backupFile;

    pFile = fopen("./venta.bkp", "rb+"); //Se abre el archivo en modo lectura/escritura
    if (pFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./venta.bkp" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }

    backupFile = fopen("./venta.dat", "wb"); //Se abre el archivo en modo escritura
    if (backupFile == NULL)// Se comprueba que la apertura fue correcta
    {
        cout << "Error de archivo. Nombre de archivo: " << "./venta.dat" << " -- Es posible que el archivo que intenta leer no exista aun, por favor cree un nuevo usuario para que el archivo de usuarios sea creado." << "\n";
        return;
    }
    while (fread(&venta, sizeof (Venta), 1, pFile) == 1)
    {
        fwrite(&venta, sizeof (Venta), 1, backupFile);
    }
    fclose(pFile);
    fclose(backupFile);
}

void guardarTodoslosBackups(){

    guardarBackupPlato();
    guardarBackupPersona();
    guardarBackupCliente();
    guardarBackupTrabajador();
    guardarBackupVenta();
    guardarBackupdetalleVenta();
}

void cargarTodoslosBackups(){

    cargarBackupPlato();
    cargarBackupPersona();
    cargarBackupCliente();
    cargarBackupTrabajador();
    cargarBackupVenta();
    cargarBackupdetalleVenta();
}



