#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../../utils/utils.cpp"

using namespace std;

vector<Categoria> categorias;
vector<Producto> productos;

// función que agrega un nuevo pedido y lo guarda en pedidos.txt
void agregarPedido()
{
    // primero se verifica que haya productos y categorías antes de agregar un pedido
    if (!verificarArchivoContieneDatos("data/productos.txt"))
    {
        cout << "=> No hay productos disponibles. Volviendo al menu principal...\n";
        return;
    }

    if (!verificarArchivoContieneDatos("data/categorias.txt"))
    {
        cout << "=> No hay categorías disponibles. Volviendo al menu principal...\n";
        return;
    }

    // luego se muestra la lista de productos disponibles para que el usuario pueda escoger...
    listarProductos(); // llama a listarProductos desde utils.cpp

    string idProducto, ubicacion, cantidadStr;
    string nuevoID = generarNuevoID("data/pedidos.txt"); // genera un nuevo ID para el pedido
    int cantidad;

    cout << "\n==========================================\n";
    cout << "            AGREGAR PEDIDO\n";
    cout << "==========================================\n";

    // se solicitan los datos necesarios para registrar el pedido
    cout << "=> Ingrese el ID del producto: ";
    cin >> idProducto;

    // verifica si el producto existe
    if (!verificarExisteProducto(idProducto, productos)) // aquí se pasa 'productos' como parámetro
    {
        cout << "\n=> El producto con ID " << idProducto << " no se encontró. Volviendo al menú principal...\n";
        return;
    }

    // busca el producto seleccionado en la lista usando memoria dinámica
    Producto *productoSeleccionado = nullptr;

    for (const auto &producto : productos)
    {
        if (producto.idProducto == idProducto)
        {
            productoSeleccionado = new Producto(producto); // se asigna un nuevo Producto en el heap
            break;
        }
    }

    cout << "=> Ingrese la ubicación del cliente: ";
    cin.ignore();
    getline(cin, ubicacion);

    // se solicita la cantidad...
    cout << "=> Ingrese la cantidad del producto: ";
    cin >> cantidadStr;
    cantidad = stoi(cantidadStr); // convierte la cantidad de texto (string) a un número entero (int)

    // validar si la cantidad solicitada es mayor que el stock del producto
    if (cantidad > stoi(productoSeleccionado->stock))
    {
        cout << "\n=> No hay suficiente stock disponible para la cantidad solicitada. Volviendo al menú principal...\n";
        delete productoSeleccionado; // Liberamos la memoria
        return;
    }

    // calcula el total del pedido
    float total = cantidad * stof(productoSeleccionado->precio);

    // actualizo el stock del producto en el vector
    int nuevoStock = stoi(productoSeleccionado->stock) - cantidad;
    productoSeleccionado->stock = to_string(nuevoStock);

    // actualizo el stock del producto en el archivo
    actualizarStockEnArchivo(*productoSeleccionado, productos); // Pasamos el valor desreferenciado

    // y por último se guarda el pedido en el archivo con "~" como separador de cada campo
    ofstream archivoPedidos("data/pedidos.txt", ios::app);

    if (archivoPedidos.is_open())
    {
        archivoPedidos << productoSeleccionado->nombre << "~" << productoSeleccionado->idCategoria << "~" << ubicacion << "~" << cantidad << "~" << total << "\n";
        archivoPedidos.close();

        // muestro los detalles del producto actualizado después de realizar el pedido
        cout << "\n==========================================\n";
        cout << "\n=> Pedido agregado con éxito. Los detalles del pedido son:\n\n";

        cout << "  -> Producto: " << productoSeleccionado->nombre << "\n";
        cout << "  -> Categoría: " << productoSeleccionado->idCategoria << "\n";
        cout << "  -> Stock nuevo: " << productoSeleccionado->stock << "\n";
        cout << "  -> Cantidad pedida: " << cantidad << "\n";
        cout << "  -> Precio unitario: " << productoSeleccionado->precio << " S/.\n";
        cout << "  -> Total: " << total << " S/.\n";
    }
    else
    {
        cout << "\n=> No se pudo abrir el archivo de pedidos.\n";
    }

    // Liberamos la memoria asignada en el heap
    delete productoSeleccionado;
}

// menu principal para gestionar pedidos
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