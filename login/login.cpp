#include <iostream>
#include <string>

using namespace std;

// arreglo de usuarios y contraseñas definidos en el mismo archivo
string usuarios[] = {"admin", "admin2"};
string contrasenas[] = {"admin", "admin2"};

bool login()
{
    string usuario, clave;
    int intentos = 0;         // contador de intentos fallidos
    bool autenticado = false; // indicador de autenticación exitosa

    // variable para calcular el tamaño del arreglo de usuarios
    int numeroDeUsuarios = sizeof(usuarios) / sizeof(usuarios[0]);

    // el bucle permite hasta 3 intentos de autenticación
    while (intentos < 3 && !autenticado)
    {
        cout << "\n==========================================\n";
        cout << "       BIENVENIDO AL SISTEMA RAPPI      \n";
        cout << "==========================================\n";
        cout << "=> Por favor, ingrese sus credenciales\n";
        cout << "------------------------------------------\n";

        // solicitamos usuario y clave
        cout << "=> Usuario : ";
        cin >> usuario;
        cout << "=> Clave   : ";
        cin >> clave;

        // recorremos todos los usuarios para verificar las credenciales ingresadas
        for (int i = 0; i < numeroDeUsuarios; i++)
        {
            // si coinciden usuario y clave, se autentica y rompe el bucle
            if (usuario == usuarios[i] && clave == contrasenas[i])
            {
                autenticado = true;
                break;
            }
        }

        // si la autenticación es exitosa, mostramos un mensaje y salimos de la función con true
        if (autenticado)
        {
            cout << "\n=> Autenticacion exitosa. Ingresando al sistema...\n";
            return true;
        }
        else
        {
            // si falla la autenticación, incrementamos "intentos" y mostramos un mensaje
            intentos++;
            cout << "\n=> Credenciales incorrectas. Intento " << intentos << " / 3\n";
        }
    }

    // si se exceden los intentos permitidos, mostramos un mensaje de salida y retornamos false
    cout << "\n=> Ha excedido el numero de intentos permitidos. Saliendo del sistema...\n\n";
    return false;
}
