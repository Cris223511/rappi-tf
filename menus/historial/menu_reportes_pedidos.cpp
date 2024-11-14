#include <iostream>
#include <unistd.h>

using namespace std;

void menuReportesPedidos()
{
    cout << "\n";

    // llamamos a la función que lista todos los pedidos desde utils.cpp
    listarPedidos();

    cout << "\n=> Reporte de pedidos mostrado con exito.\n";
}
