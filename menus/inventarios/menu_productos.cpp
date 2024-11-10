#include <iostream>
#include <unistd.h>

using namespace std;

void menuProductos()
{
    int opcion;
    do
    {
        cout << "\n==========================================\n";
        cout << "                PRODUCTOS\n";
        cout << "==========================================\n";
        cout << "[1]. Agregar productos\n";
        cout << "[2]. Editar productos\n";
        cout << "[3]. Eliminar productos\n";
        cout << "[4]. Volver\n";
        cout << "==========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cout << "\n";

        switch (opcion)
        {
        case 1:
            cout << "Agregar productos...\n";
            break;
        case 2:
            cout << "Editar productos...\n";
            break;
        case 3:
            cout << "Eliminar productos...\n";
            break;
        case 4:
            cout << "Volviendo al menu de inventarios...\n";
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);
}
