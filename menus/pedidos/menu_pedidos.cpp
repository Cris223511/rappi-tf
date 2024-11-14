#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

vector<Producto> productos;

// funcion que agrega un nuevo pedido y lo guarda en pedidos.txt
void agregarPedido()
{
    // cargo los productos antes de continuar
    cargarProductos(productos);

    // aca verifico si hay productos y antes de agregar un pedido
    if (!verificarArchivoContieneDatos("data/productos.txt"))
    {
        cout << "=> No hay productos disponibles. Volviendo al menu principal...\n";
        return;
    }

    // muestra la lista de productos disponibles para que el usuario pueda escoger
    listarProductos();

    string idProducto, ubicacion, cantidadStr;
    string nuevoID = generarNuevoID("data/pedidos.txt"); // genera un nuevo ID correlativo para el pedido
    int cantidad;

    cout << "\n==========================================\n";
    cout << "            AGREGAR PEDIDO\n";
    cout << "==========================================\n";

    // solicitamos los datos necesarios para registrar el pedido
    cout << "=> Ingrese el ID del producto: ";
    cin >> idProducto;

    // hacemos la verificacion de que si el producto existe
    if (!verificarExisteProducto(idProducto, productos))
    {
        cout << "\n=> El producto con ID " << idProducto << " no se encontro. Volviendo al menu principal...\n";
        return;
    }

    // busca el producto seleccionado en la lista usando memoria dinamica
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

    cout << "=> Ingrese la cantidad del producto: ";
    cin >> cantidadStr;
    cantidad = stoi(cantidadStr);

    if (cantidad > stoi(productoSeleccionado->stock))
    {
        cout << "\n=> No hay suficiente stock disponible para la cantidad solicitada. Volviendo al menu principal...\n";
        delete productoSeleccionado;
        return;
    }

    // ahora a calcular el total del pedido y lo formatea a dos decimales
    float total = cantidad * stof(productoSeleccionado->precio);
    ostringstream streamTotal;
    streamTotal << fixed << setprecision(2) << total;

    // y actualizamos el stock en el vector y en el archivo correspondiente
    int nuevoStock = stoi(productoSeleccionado->stock) - cantidad;
    productoSeleccionado->stock = to_string(nuevoStock);
    actualizarStockEnArchivo(*productoSeleccionado, productos);

    // y por ultimo se guarda el pedido en el archivo con "~" como separador de cada campo
    // usamos ios::app para añadir el pedido al final del archivo sin borrar el contenido existente
    ofstream archivoPedidos("data/pedidos.txt", ios::app);

    if (archivoPedidos.is_open())
    {
        archivoPedidos << nuevoID << "~" << productoSeleccionado->nombre << "~" << productoSeleccionado->nombreCategoria << "~" << ubicacion << "~" << cantidad << "~" << streamTotal.str() << "\n";
        archivoPedidos.close();

        // muestra los detalles del producto actualizado despues de realizar el pedido
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

    // liberamos la memoria asignada en el heap
    delete productoSeleccionado;
}

// funcion que permite editar un pedido en el archivo pedidos.txt
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

            // calcula el nuevo total con la nueva cantidad
            float nuevoTotal = nuevaCantidad * precio;

            // formateo el total con dos decimales
            ostringstream streamTotal;
            streamTotal << fixed << setprecision(2) << nuevoTotal;

            // y aca actualiza la linea con los nuevos datos
            linea = idPedido + "~" + nombreProducto + "~" + nombreCategoria + "~" + nuevaUbicacion + "~" + to_string(nuevaCantidad) + "~" + streamTotal.str();
        }
        pedidos.push_back(linea);
    }
    archivoPedidos.close();

    // si no encontro el pedido...
    if (!pedidoEncontrado)
    {
        cout << "\n=> El pedido con ID " << idPedido << " no se encontro. Volviendo al menu principal...\n";
        return;
    }

    // si todo ok, sobreescribe el archivo con los pedidos actualizados
    ofstream archivoPedidosOut("data/pedidos.txt");
    for (const string &pedido : pedidos)
    {
        archivoPedidosOut << pedido << "\n";
    }
    archivoPedidosOut.close();

    // muestra los detalles del pedido actualizado
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
    // verifica si hay pedidos en el archivo
    if (!verificarArchivoContieneDatos("data/pedidos.txt"))
    {
        cout << "=> No hay pedidos disponibles. Volviendo al menu principal...\n";
        return;
    }

    // lista los pedidos para que el usuario vea cual desea eliminar
    listarPedidos();

    string idPedido;

    cout << "\n==========================================\n";
    cout << "             ELIMINAR PEDIDO\n";
    cout << "==========================================\n";

    // solicito el ID del pedido a eliminar
    cout << "=> Ingrese el ID del pedido que desea eliminar: ";
    cin >> idPedido;

    // abro el archivo de pedidos para leer y almacenar los datos temporalmente
    ifstream archivoPedidos("data/pedidos.txt");
    vector<string> pedidosActualizados;
    string linea;
    bool encontrado = false;

    while (getline(archivoPedidos, linea))
    {
        // extraigo el ID del pedido actual en la linea
        string idActual = linea.substr(0, linea.find("~"));

        if (idActual == idPedido)
        {
            encontrado = true; // marca el pedido como encontrado para eliminarlo
            cout << "\n=> Pedido con ID " << idPedido << " eliminado con exito.\n";
        }
        else
        {
            // guarda la linea sin cambios si no coincide el ID
            pedidosActualizados.push_back(linea);
        }
    }
    archivoPedidos.close();

    // si no encontro el pedido...
    if (!encontrado)
    {
        cout << "\n=> El pedido con ID " << idPedido << " no se encontro. Volviendo al menu principal...\n";
        return;
    }

    // si todo ok, entonces sobreescribe el archivo con los pedidos actualizados
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
