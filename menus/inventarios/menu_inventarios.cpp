#include <iostream>
#include <unistd.h>
#include "menu_categorias.cpp"
#include "menu_productos.cpp"

using namespace std;

void menuInventarios()
{
    int opcion;
    do
    {
        cout << "\n=============================\n";
        cout << "   GESTION DE INVENTARIOS\n";
        cout << "=============================\n";
        cout << "[1]. Categorias\n";
        cout << "[2]. Productos\n";
        cout << "[3]. Volver\n";
        cout << "=============================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            menuCategorias(); // ir a categorías
            break;
        case 2:
            menuProductos(); // ir a productos
            break;
        case 3:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "\nOpcion invalida. Intente nuevamente.\n\n";
        }
    } while (opcion != 3);
}
