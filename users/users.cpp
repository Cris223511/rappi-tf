#include <string>

using namespace std;

// estos son los arreglos que almacenan los nombres de usuario y las contraseñas
//                      0         1
string usuarios[] = {"admin", "admin2"};
//                        0         1
string contrasenas[] = {"admin", "admin2"};

// creo esta función para obtener la cantidad de usuarios en el sistema (o sea para saber si coincide o no su usuario y clave)
int obtenerCantidadUsuarios()
{
    return sizeof(usuarios) / sizeof(usuarios[0]);
}
