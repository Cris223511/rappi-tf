#include <iostream>
#include <unistd.h>

using namespace std;

void menuProductos()
{
    int opcion;
    do
    {
        cout << "=============================\n";
        cout << "          PRODUCTOS\n";
        cout << "=============================\n";
        cout << "[1]. Listar Productos\n";
        cout << "[2]. Agregar Producto\n";
        cout << "[3]. Administrar Productos\n";
        cout << "[4]. Volver\n";
        cout << "=============================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Listando productos...\n";
            break;
        case 2:
            cout << "Agregando producto...\n";
            break;
        case 3:
            cout << "Administrando productos...\n";
            break;
        case 4:
            cout << "Volviendo al menu de inventarios...\n";
            break;
        default:
            cout << "\nOpcion invalida. Intente nuevamente.\n\n";
        }
    } while (opcion != 4);
}
