#include <iostream>
#include <string>
#include <unistd.h>
#include "../users/users.cpp"

using namespace std;

bool login()
{
    string usuario, clave;
    int intentos = 0;
    bool autenticado = false;

    while (intentos < 3 && !autenticado)
    {
        cout << "==========================================\n";
        cout << "       BIENVENIDO AL SISTEMA RAPPI      \n";
        cout << "==========================================\n";
        cout << "=> Por favor, ingrese sus credenciales\n";
        cout << "------------------------------------------\n";

        cout << "=> Usuario : ";
        cin >> usuario;
        cout << "=> Clave   : ";
        cin >> clave;

        // verifico las credenciales (los arreglos de usuarios y contraseñas)
        for (int i = 0; i < obtenerCantidadUsuarios(); i++)
        {
            if (usuario == usuarios[i] && clave == contrasenas[i])
            {
                autenticado = true;
                break;
            }
        }

        if (autenticado)
        {
            cout << "\n=> Autenticacion exitosa. Ingresando al sistema...\n\n";
            return true;
        }
        else
        {
            intentos++;
            cout << "\n=> Credenciales incorrectas. Intento " << intentos << " / 3\n\n";
        }
    }

    cout << "\n=> Ha excedido el numero de intentos permitidos. Saliendo del sistema...\n\n";
    return false;
}
