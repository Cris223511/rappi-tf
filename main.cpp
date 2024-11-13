#include <iostream>
#include "login/login.cpp"
#include "menus/menu_principal.cpp"

using namespace std;

int main()
{
    if (login())
    {
        // si el login es exitoso, se carga el menu principal
        menuPrincipal();
    }
    else
    {
        // si el login falla despues de 3 intentos, se cierra el programa
        cout << "\n=> Gracias por usar el sistema Rappi. Hasta pronto!\n\n";
    }

    return 0;
}
