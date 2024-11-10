#include <iostream>
#include <unistd.h>

using namespace std;

void menuPedidos()
{
    int opcion;
    do
    {
        cout << "\n==========================================\n";
        cout << "           GESTION DE PEDIDOS\n";
        cout << "==========================================\n";
        cout << "[1]. Agregar pedidos\n";
        cout << "[2]. Editar pedidos\n";
        cout << "[3]. Eliminar pedidos\n";
        cout << "[4]. Volver\n";
        cout << "==========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cout << "\n";

        switch (opcion)
        {
        case 1:
            cout << "Agregar pedidos...\n";
            break;
        case 2:
            cout << "Editar pedidos...\n";
            break;
        case 3:
            cout << "Eliminar pedidos...\n";
            break;
        case 4:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);
}
