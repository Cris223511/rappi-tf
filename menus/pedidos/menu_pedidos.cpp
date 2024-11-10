#include <iostream>
#include <unistd.h>

using namespace std;

void menuPedidos()
{
    int opcion;
    do
    {
        cout << "\n=============================\n";
        cout << "  ALMACENAMIENTO DE PEDIDOS\n";
        cout << "=============================\n";
        cout << "[1]. Listar Pedidos\n";
        cout << "[2]. Agregar Pedido\n";
        cout << "[3]. Administrar Pedidos\n";
        cout << "[4]. Volver\n";
        cout << "=============================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Listando pedidos...\n";
            break;
        case 2:
            cout << "Agregando pedido...\n";
            break;
        case 3:
            cout << "Administrando pedidos...\n";
            break;
        case 4:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "\nOpcion invalida. Intente nuevamente.\n\n";
        }
    } while (opcion != 4);
}
