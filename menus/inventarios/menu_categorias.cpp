#include <iostream>
#include <unistd.h>

using namespace std;

void menuCategorias()
{
    int opcion;
    do
    {
        cout << "\n=============================\n";
        cout << "         CATEGORIAS\n";
        cout << "=============================\n";
        cout << "[1]. Listar Categorias\n";
        cout << "[2]. Agregar Categoria\n";
        cout << "[3]. Administrar Categorias\n";
        cout << "[4]. Volver\n";
        cout << "=============================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Listando categorias...\n";
            break;
        case 2:
            cout << "Agregando categoria...\n";
            break;
        case 3:
            cout << "Administrando categorias...\n";
            break;
        case 4:
            cout << "Volviendo al menu de inventarios...\n";
            break;
        default:
            cout << "\nOpcion invalida. Intente nuevamente.\n\n";
        }
    } while (opcion != 4);
}
