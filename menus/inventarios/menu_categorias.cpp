#include <iostream>
#include <unistd.h>

using namespace std;

void menuCategorias()
{
    int opcion;
    do
    {
        cout << "\n==========================================\n";
        cout << "                CATEGORIAS\n";
        cout << "==========================================\n";
        cout << "[1]. Agregar categorias\n";
        cout << "[2]. Editar categorias\n";
        cout << "[3]. Eliminar categorias\n";
        cout << "[4]. Volver\n";
        cout << "==========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cout << "\n";

        switch (opcion)
        {
        case 1:
            cout << "Agregar categorias...\n";
            break;
        case 2:
            cout << "Editar categorias...\n";
            break;
        case 3:
            cout << "Eliminar categorias...\n";
            break;
        case 4:
            cout << "Volviendo al menu de inventarios...\n";
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);
}
