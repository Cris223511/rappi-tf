#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../../utils/utils.cpp"

using namespace std;

vector<Categoria> categorias;
vector<Producto> productos;

// en esta funcion se mostrara la lista de productos junto con sus categorias
void listarProductos()
{
    cargarCategorias(categorias);
    cargarProductos(productos);

    // encabezado de la tabla que mostrara los productos
    cout << "===================================================\n";
    cout << "                 LISTA DE PRODUCTOS\n";
    cout << "===================================================\n";
    cout << "idProducto | Categoria | Nombre | Precio | Stock\n";
    cout << "---------------------------------------------------\n";

    // se recorre cada producto para mostrarlo junto con el nombre de su categoria...
    for (const auto &producto : productos)
    {
        string nombreCategoria = "Desconocido";

        // se busca el nombre de la categoria correspondiente al idCategoria del producto...
        for (const auto &categoria : categorias)
        {
            if (categoria.idCategoria == producto.idCategoria)
            {
                nombreCategoria = categoria.nombreCategoria;
                break; // se detiene la busqueda una vez encontrada
            }
        }

        // y aca muestro el producto en el formato de tabla
        cout << "-> [" << producto.idProducto << "] | " << nombreCategoria << " | " << producto.nombre << " | " << producto.precio << " S/. | " << producto.stock << "\n";
    }
}

// funcion que agrega un nuevo pedido y lo guarda en pedidos.txt
void agregarPedido()
{
    // primero se verifica que haya productos y categorias antes de agregar un pedido
    if (!verificarArchivoContieneDatos("data/productos.txt"))
    {
        cout << "=> No hay productos disponibles. Volviendo al menu principal...\n";
        return;
    }

    if (!verificarArchivoContieneDatos("data/categorias.txt"))
    {
        cout << "=> No hay categorias disponibles. Volviendo al menu principal...\n";
        return;
    }

    // luego se muestra la lista de productos disponibles para que el usuario pueda escoger...
    listarProductos();

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
    if (!verificarExisteProducto(idProducto, productos)) // aqui se pasa 'productos' como parametro
    {
        cout << "\n=> El producto con ID " << idProducto << " no se encontro. Volviendo al menu principal...\n";
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

    // busca el nombre de la categoría del producto seleccionado usando memoria dinámica
    string nombreCategoria = "Desconocido";
    Categoria *categoriaSeleccionada = nullptr;

    if (productoSeleccionado) // se verifica que el producto haya sido encontrado
    {
        for (const auto &categoria : categorias)
        {
            if (categoria.idCategoria == productoSeleccionado->idCategoria)
            {
                categoriaSeleccionada = new Categoria(categoria); // se asigna un nuevo Categoria en el heap
                nombreCategoria = categoriaSeleccionada->nombreCategoria;
                break;
            }
        }
    }

    cout << "=> Ingrese la ubicacion del cliente: ";
    cin.ignore();
    getline(cin, ubicacion);

    // se solicita la cantidad...
    cout << "=> Ingrese la cantidad del producto: ";
    cin >> cantidadStr;
    cantidad = stoi(cantidadStr); // convierte la cantidad de texto (string) a un numero entero (int)

    // y luego valido que si la cantidad solicitada es mayor que el stock del producto elegido...
    if (cantidad > stoi(productoSeleccionado->stock))
    {
        cout << "\n=> No hay suficiente stock disponible para la cantidad solicitada. Volviendo al menu principal...\n";
        delete productoSeleccionado;  // Liberamos la memoria
        delete categoriaSeleccionada; // Liberamos la memoria
        return;
    }

    // calcula el total del pedido
    float total = cantidad * stof(productoSeleccionado->precio);

    // actualizo el stock del producto en el vector
    int nuevoStock = stoi(productoSeleccionado->stock) - cantidad;
    productoSeleccionado->stock = to_string(nuevoStock);

    // actualizo el stock del producto en el archivo
    actualizarStockEnArchivo(*productoSeleccionado, productos); // Pasamos el valor desreferenciado

    // y por ultimo se guarda el pedido en el archivo con "~" como separador de cada campo
    // usamos ios::app para añadir el pedido al final del archivo sin borrar el contenido existente
    ofstream archivoPedidos("data/pedidos.txt", ios::app);

    if (archivoPedidos.is_open())
    {
        archivoPedidos << productoSeleccionado->nombre << "~" << nombreCategoria << "~" << ubicacion << "~" << cantidad << "~" << total << "\n";
        archivoPedidos.close();

        cout << "\n==========================================\n";

        // muestro los detalles del producto actualizado despues de realizar el pedido
        cout << "\n=> Pedido agregado con exito. Los detalles del pedido son:\n\n";

        cout << "  -> Producto: " << productoSeleccionado->nombre << "\n";
        cout << "  -> Categoria: " << nombreCategoria << "\n";
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
    delete categoriaSeleccionada;
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
