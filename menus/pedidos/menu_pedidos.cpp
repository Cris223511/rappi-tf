#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// función para mostrar la lista de productos en formato básico
void listarProductos()
{
    ifstream archivoProductos("../data/productos.txt"); // abrimos el archivo de productos en modo lectura
    string linea; // se usará para almacenar cada línea del archivo de productos

    cout << "\n==========================================\n";
    cout << "            LISTA DE PRODUCTOS\n";
    cout << "==========================================\n";

    if (archivoProductos.is_open()) // verifica si el archivo se abrió correctamente
    {
        while (getline(archivoProductos, linea)) // lee cada línea del archivo
        {
            cout << linea << "\n"; // muestra cada línea completa, que contiene un producto
        }
        archivoProductos.close(); // cerramos el archivo al terminar de leerlo
    }
    else
    {
        cout << "\n=> No se pudo abrir el archivo de productos.\n"; // muestra un mensaje si no se puede abrir el archivo
    }
}

// función para verificar si hay productos en productos.txt
bool hayProductos()
{
    ifstream archivoProductos("../data/productos.txt"); // se abre el archivo de productos en modo lectura
    bool existe = archivoProductos.good(); // verifica si el archivo existe y está accesible
    archivoProductos.close(); // cerramos el archivo
    return existe; // retorna verdadero si el archivo existe
}

// función para generar un nuevo ID de pedido en formato básico de cuatro dígitos
string generarNuevoID()
{
    ifstream archivoPedidos("../data/pedidos.txt"); // se abre el archivo de pedidos en modo lectura
    string linea; // variable para almacenar cada línea del archivo de pedidos
    int maxID = 0; // almacena el ID más alto encontrado en el archivo

    // en esta parte, buscamos el último ID en el archivo
    if (archivoPedidos.is_open()) // verifica si el archivo se abrió correctamente
    {
        while (getline(archivoPedidos, linea)) // lee cada línea del archivo
        {
            // aqui se toman los primeros 4 caracteres de cada línea como ID...
            string id = linea.substr(0, 4);
            
            // luego, el ID de texto se convierte en un número entero...
            int idNum = stoi(id);
            
            // y al final, se compara el ID actual con el máximo ID encontrado.
            if (idNum > maxID)
            {
                maxID = idNum; // actualiza maxID si encontramos un ID más alto
            }
        }
        archivoPedidos.close(); // cierra el archivo al terminar de leerlo
    }

    // aquí incrementamos el ID en 1 y lo convertimos a un string de cuatro dígitos
    maxID += 1;
    string nuevoID = to_string(maxID);
    while (nuevoID.length() < 4) // se añaden ceros a la izquierda si el ID es menor a cuatro dígitos
    {
        nuevoID = "0" + nuevoID;
    }

    return nuevoID; // retorna el nuevo ID generado
}

// función para agregar un pedido y guardarlo en pedidos.txt
void agregarPedido()
{
    // primero, validamos si hay productos en el archivo productos.txt
    if (!hayProductos())
    {
        cout << "\n=> No hay productos disponibles para realizar pedidos. Volviendo al menu principal...\n";
        return; // si no hay productos, volvemos al menú sin realizar el pedido
    }

    listarProductos(); // muestra la lista de productos para que el usuario pueda elegir

    string idProducto, ubicacion, cantidad; // variables para almacenar los datos del pedido
    string nuevoID = generarNuevoID(); // genera el nuevo ID del pedido
    cout << "\n==========================================\n";
    cout << "            AGREGAR PEDIDO\n";
    cout << "==========================================\n";

    // solicita al trabajador que ingrese los datos del pedido
    cout << "=> Ingrese el ID del producto: ";
    cin >> idProducto;
    cout << "=> Ingrese la ubicacion del cliente: ";
    cin.ignore(); // ignoramos el salto de línea previo para getline
    getline(cin, ubicacion); // lee toda la línea para permitir espacios en la ubicación
    cout << "=> Ingrese la cantidad del producto: ";
    cin >> cantidad;

    // en esta parte, guardamos el pedido en el archivo pedidos.txt usando "~" como separador entre los datos
    ofstream archivoPedidos("../data/pedidos.txt", ios::app); // se abre el archivo en modo agregar
    if (archivoPedidos.is_open())
    {
        archivoPedidos << nuevoID << "~" << idProducto << "~" << ubicacion << "~" << cantidad << "\n"; // escribe el pedido en el archivo
        archivoPedidos.close(); // cierra el archivo después de escribir
        cout << "\n=> Pedido agregado correctamente con ID " << nuevoID << ".\n"; // muestra un mensaje de confirmación
    }
    else
    {
        cout << "\n=> No se pudo abrir el archivo de pedidos para guardar el pedido.\n"; // muestra un mensaje si no se puede abrir el archivo
    }
}

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
            agregarPedido(); // ejecuta la opcion de agregar pedido
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
