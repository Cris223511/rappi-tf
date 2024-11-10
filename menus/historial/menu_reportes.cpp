#include <iostream>
#include <unistd.h>
#include "menu_reportes_pedidos.cpp"
#include "menu_reportes_productos.cpp"

using namespace std;

void menuReportes()
{
    int opcion;
    do
    {
        cout << "\n==========================================\n";
        cout << "          HISTORIAL DE REPORTES\n";
        cout << "==========================================\n";
        cout << "[1]. Reportes de pedidos\n";
        cout << "[2]. Reportes de productos\n";
        cout << "[3]. Volver\n";
        cout << "==========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            menuReportesPedidos(); // ir a reportes de pedidos
            break;
        case 2:
            menuReportesProductos(); // ir a reportes de productos
            break;
        case 3:
            cout << "\nVolviendo al menu principal...\n";
            break;
        default:
            cout << "\nOpcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 3);
}
