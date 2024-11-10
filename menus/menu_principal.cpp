#include <iostream>
#include <unistd.h>
#include "inventarios/menu_inventarios.cpp"
#include "pedidos/menu_pedidos.cpp"
#include "historial/menu_reportes.cpp"

using namespace std;

void menuPrincipal()
{
    int opcion;
    do
    {
        cout << "\n================================\n";
        cout << "    SISTEMA DE GESTION RAPPI  \n";
        cout << "================================\n";
        cout << "[1]. Gestion de Inventarios\n";
        cout << "[2]. Almacenamiento de Pedidos\n";
        cout << "[3]. Historial de Reportes\n";
        cout << "[4]. Salir\n";
        cout << "================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            menuInventarios(); // ir a gestión de inventarios
            break;
        case 2:
            menuPedidos(); // ir a almacenamiento de pedidos
            break;
        case 3:
            menuReportes(); // ir a historial de reportes
            break;
        case 4:
            cout << "\n=> Gracias por usar el sistema Rappi. Hasta pronto!\n\n";
            break;
        default:
            cout << "\nOpcion invalida. Intente nuevamente.\n\n";
        }
    } while (opcion != 4);
}