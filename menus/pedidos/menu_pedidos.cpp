#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include "../../utils/utils.cpp"

using namespace std;

vector<Categoria> categorias;
vector<Producto> productos;

// funcion que agrega un nuevo pedido y lo guarda en pedidos.txt
void agregarPedido()
{
    // Carga los productos antes de continuar
    cargarProductos(productos);

    // Verifica si hay productos y categorias antes de agregar un pedido
    if (!verificarArchivoContieneDatos("data/productos.txt"))
    {
        cout << "=> No hay productos disponibles. Volviendo al menu principal...\n";
        return;
    }

    // Muestra la lista de productos disponibles para que el usuario pueda escoger
    listarProductos();

    string idProducto, ubicacion, cantidadStr;
    string nuevoID = generarNuevoID("data/pedidos.txt"); // genera un nuevo ID para el pedido
    int cantidad;

    cout << "\n==========================================\n";
    cout << "            AGREGAR PEDIDO\n";
    cout << "==========================================\n";

    // Solicita los datos necesarios para registrar el pedido
    cout << "=> Ingrese el ID del producto: ";
    cin >> idProducto;

    // Verifica si el producto existe
    if (!verificarExisteProducto(idProducto, productos))
    {
        cout << "\n=> El producto con ID " << idProducto << " no se encontro. Volviendo al menu principal...\n";
        return;
    }

    // Busca el producto seleccionado en la lista usando memoria dinamica
    Producto *productoSeleccionado = nullptr;

    for (const auto &producto : productos)
    {
        if (producto.idProducto == idProducto)
        {
            productoSeleccionado = new Producto(producto);
            break;
        }
    }

    cout << "=> Ingrese la ubicacion del cliente: ";
    cin.ignore();
    getline(cin, ubicacion);

    // Solicita la cantidad y la valida
    cout << "=> Ingrese la cantidad del producto: ";
    cin >> cantidadStr;
    cantidad = stoi(cantidadStr);

    if (cantidad > stoi(productoSeleccionado->stock))
    {
        cout << "\n=> No hay suficiente stock disponible para la cantidad solicitada. Volviendo al menu principal...\n";
        delete productoSeleccionado;
        return;
    }

    // Calcula el total del pedido y lo formatea a dos decimales
    float total = cantidad * stof(productoSeleccionado->precio);
    ostringstream streamTotal;
    streamTotal << fixed << setprecision(2) << total;

    // Actualiza el stock en el vector y archivo
    int nuevoStock = stoi(productoSeleccionado->stock) - cantidad;
    productoSeleccionado->stock = to_string(nuevoStock);
    actualizarStockEnArchivo(*productoSeleccionado, productos);

    // Guarda el pedido en el archivo con "~" como separador
    ofstream archivoPedidos("data/pedidos.txt", ios::app);

    if (archivoPedidos.is_open())
    {
        archivoPedidos << nuevoID << "~" << productoSeleccionado->nombre << "~"
                       << productoSeleccionado->nombreCategoria << "~"
                       << ubicacion << "~" << cantidad << "~"
                       << streamTotal.str() << "\n";
        archivoPedidos.close();

        // Muestra los detalles del producto actualizado despues de realizar el pedido
        cout << "\n==========================================\n";
        cout << "\n=> Pedido agregado con exito. Los detalles del pedido son:\n\n";

        cout << "  -> Producto: " << productoSeleccionado->nombre << "\n";
        cout << "  -> Categoria: " << productoSeleccionado->nombreCategoria << "\n";
        cout << "  -> Stock nuevo: " << productoSeleccionado->stock << "\n";
        cout << "  -> Cantidad pedida: " << cantidad << "\n";
        cout << "  -> Precio unitario: " << productoSeleccionado->precio << " S/.\n";
        cout << "  -> Total: " << streamTotal.str() << " S/.\n";
    }
    else
    {
        cout << "\n=> No se pudo abrir el archivo de pedidos.\n";
    }

    // Liberamos la memoria asignada en el heap
    delete productoSeleccionado;
}

// Funcion que permite editar un pedido en el archivo pedidos.txt
void editarPedido()
{
    if (!verificarArchivoContieneDatos("data/pedidos.txt"))
    {
        cout << "=> No hay pedidos disponibles. Volviendo al menu principal...\n";
        return;
    }

    listarPedidos();

    string idPedido, nuevaUbicacion, nuevaCantidadStr;
    int nuevaCantidad;

    cout << "\n==========================================\n";
    cout << "            EDITAR PEDIDO\n";
    cout << "==========================================\n";

    cout << "=> Ingrese el ID del pedido que desea editar: ";
    cin >> idPedido;

    vector<string> pedidos;
    ifstream archivoPedidos("data/pedidos.txt");
    bool pedidoEncontrado = false;
    string linea;
    string nombreProducto, nombreCategoria, ubicacion, cantidadStr, totalStr;

    while (getline(archivoPedidos, linea))
    {
        int pos1 = linea.find("~");
        int pos2 = linea.find("~", pos1 + 1);
        int pos3 = linea.find("~", pos2 + 1);
        int pos4 = linea.find("~", pos3 + 1);
        int pos5 = linea.find("~", pos4 + 1);

        string idActual = linea.substr(0, pos1);
        nombreProducto = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        nombreCategoria = linea.substr(pos2 + 1, pos3 - pos2 - 1);
        ubicacion = linea.substr(pos3 + 1, pos4 - pos3 - 1);
        cantidadStr = linea.substr(pos4 + 1, pos5 - pos4 - 1);
        totalStr = linea.substr(pos5 + 1);

        if (idActual == idPedido)
        {
            pedidoEncontrado = true;

            cout << "=> Ingrese la nueva ubicacion del cliente: ";
            cin.ignore();
            getline(cin, nuevaUbicacion);

            cout << "=> Ingrese la nueva cantidad del producto: ";
            cin >> nuevaCantidadStr;
            nuevaCantidad = stoi(nuevaCantidadStr);

            int cantidad = stoi(cantidadStr);
            float precio = stof(totalStr) / cantidad; // Reconstruye el precio unitario

            // Calcula el nuevo total con la nueva cantidad
            float nuevoTotal = nuevaCantidad * precio;

            // Formatear el total con dos decimales
            ostringstream streamTotal;
            streamTotal << fixed << setprecision(2) << nuevoTotal;

            // Actualiza la linea con los nuevos datos
            linea = idPedido + "~" + nombreProducto + "~" + nombreCategoria + "~" + nuevaUbicacion + "~" + to_string(nuevaCantidad) + "~" + streamTotal.str();
        }
        pedidos.push_back(linea);
    }
    archivoPedidos.close();

    if (!pedidoEncontrado)
    {
        cout << "\n=> El pedido con ID " << idPedido << " no se encontro. Volviendo al menu principal...\n";
        return;
    }

    // Sobreescribe el archivo con los pedidos actualizados
    ofstream archivoPedidosOut("data/pedidos.txt");
    for (const string &pedido : pedidos)
    {
        archivoPedidosOut << pedido << "\n";
    }
    archivoPedidosOut.close();

    // Muestra los detalles del pedido actualizado
    cout << "\n==========================================\n";
    cout << "\n=> Pedido editado con exito. Los detalles del pedido actualizado son:\n\n";
    cout << "  -> Producto: " << nombreProducto << "\n";
    cout << "  -> Categoria: " << nombreCategoria << "\n";
    cout << "  -> Nueva ubicacion: " << nuevaUbicacion << "\n";
    cout << "  -> Nueva cantidad: " << nuevaCantidad << "\n";
    cout << "  -> Precio unitario: " << fixed << setprecision(2) << (stof(totalStr) / stoi(cantidadStr)) << " S/.\n";
    cout << "  -> Total actualizado: " << fixed << setprecision(2) << (stof(totalStr) / stoi(cantidadStr)) * nuevaCantidad << " S/.\n";
}

// funcion que permite eliminar un pedido existente en el archivo pedidos.txt
void eliminarPedido()
{
    // Verifica si hay pedidos en el archivo
    if (!verificarArchivoContieneDatos("data/pedidos.txt"))
    {
        cout << "=> No hay pedidos disponibles. Volviendo al menu principal...\n";
        return;
    }

    // Lista los pedidos para que el usuario vea cual desea eliminar
    listarPedidos();

    string idPedido;

    cout << "\n==========================================\n";
    cout << "             ELIMINAR PEDIDO\n";
    cout << "==========================================\n";

    // Solicita el ID del pedido a eliminar
    cout << "=> Ingrese el ID del pedido que desea eliminar: ";
    cin >> idPedido;

    // Abre el archivo de pedidos para leer y almacenar los datos temporalmente
    ifstream archivoPedidos("data/pedidos.txt");
    vector<string> pedidosActualizados;
    string linea;
    bool encontrado = false;

    while (getline(archivoPedidos, linea))
    {
        // Extrae el ID del pedido actual en la linea
        string idActual = linea.substr(0, linea.find("~"));

        if (idActual == idPedido)
        {
            encontrado = true; // marca el pedido como encontrado para eliminarlo
            cout << "\n=> Pedido con ID " << idPedido << " eliminado con exito.\n";
            // No se agrega a pedidosActualizados, por lo que sera eliminado
        }
        else
        {
            // Guarda la linea sin cambios si no coincide el ID
            pedidosActualizados.push_back(linea);
        }
    }
    archivoPedidos.close();

    if (!encontrado)
    {
        cout << "\n=> El pedido con ID " << idPedido << " no se encontro. Volviendo al menu principal...\n";
        return;
    }

    // Sobrescribe el archivo con los pedidos actualizados
    ofstream archivoPedidosSalida("data/pedidos.txt");
    for (const auto &pedido : pedidosActualizados)
    {
        archivoPedidosSalida << pedido << "\n";
    }
    archivoPedidosSalida.close();
}

// menu principal para gestionar pedidos
void menuPedidos()
{
    int opcion;
    do
    {
        cout << "\n==========================================\n";
        cout << "            GESTION DE PEDIDOS\n";
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
            agregarPedido();
            break;
        case 2:
            editarPedido();
            break;
        case 3:
            eliminarPedido();
            break;
        case 4:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);
}
