#include <iostream>
#include <unistd.h>

using namespace std;

void menuReportesProductos()
{
    cout << "\n";

    // llamamos a la función que lista todos los productos desde utils.cpp
    listarProductos();

    cout << "\n=> Reporte de productos mostrado con exito.\n";
}
