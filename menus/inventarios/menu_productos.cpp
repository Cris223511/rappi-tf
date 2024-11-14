#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <unistd.h>

using namespace std;

// funcion que agrega un nuevo producto y lo guarda en productos.txt
void agregarProducto()
{
    // aca verifico si existen categorias
    if (!verificarArchivoContieneDatos("data/categorias.txt"))
    {
        cout << "=> No hay categorias disponibles. No se puede agregar un producto sin una categoria. Volviendo al menu principal...\n";
        return;
    }

    // muestro las categorias disponibles
    listarCategorias();

    Producto nuevoProducto;

    cout << "==========================================\n";
    cout << "            AGREGAR PRODUCTO\n";
    cout << "==========================================\n";

    // solicito los datos necesarios para registrar el producto
    cout << "=> Ingrese el ID de la categoria del producto: ";
    cin >> nuevoProducto.nombreCategoria;

    cout << "=> Ingrese el nombre del producto: ";
    cin.ignore();
    getline(cin, nuevoProducto.nombre);

    cout << "=> Ingrese el precio del producto: ";
    cin >> nuevoProducto.precio;

    cout << "=> Ingrese el stock del producto: ";
    cin >> nuevoProducto.stock;

    // aca genero un nuevo ID de producto correlativo
    nuevoProducto.idProducto = generarNuevoID("data/productos.txt");

    // y por ultimo se guarda el producto en el archivo con "~" como separador de cada campo
    // usamos ios::app para añadir el producto al final del archivo sin borrar el contenido existente
    ofstream archivoProductos("data/productos.txt", ios::app);

    if (archivoProductos.is_open())
    {
        archivoProductos << nuevoProducto.idProducto << "~" << nuevoProducto.nombreCategoria << "~" << nuevoProducto.nombre << "~" << nuevoProducto.precio << "~" << nuevoProducto.stock << "\n";
        archivoProductos.close();

        cout << "\n=> Producto agregado con exito.\n";
    }
    else
    {
        cout << "\n=> No se pudo abrir el archivo de productos para agregar el producto.\n";
    }
}

// funcion para editar los detalles de un producto existente
void editarProducto()
{
    if (!verificarArchivoContieneDatos("data/productos.txt"))
    {
        cout << "=> No hay productos disponibles. Volviendo al menu principal...\n";
        return;
    }

    listarProductos();

    string idProducto;

    // solicita el id del producto a editar
    cout << "\n==========================================\n";
    cout << "            EDITAR PRODUCTO\n";
    cout << "==========================================\n";
    cout << "=> Ingrese el ID del producto que desea editar: ";
    cin >> idProducto;

    vector<string> productos;
    ifstream archivoProductos("data/productos.txt");
    bool productoEncontrado = false;
    string linea, nombre, precio, stock, categoria;

    while (getline(archivoProductos, linea))
    {
        int pos1 = linea.find("~");
        int pos2 = linea.find("~", pos1 + 1);
        int pos3 = linea.find("~", pos2 + 1);
        int pos4 = linea.find("~", pos3 + 1);

        // extraccion de los campos del producto actual
        string idActual = linea.substr(0, pos1);
        categoria = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        nombre = linea.substr(pos2 + 1, pos3 - pos2 - 1);
        precio = linea.substr(pos3 + 1, pos4 - pos3 - 1);
        stock = linea.substr(pos4 + 1);

        // verifica si el id actual coincide con el id ingresado
        if (idActual == idProducto)
        {
            productoEncontrado = true;

            cout << "=> Ingrese el nuevo nombre del producto: ";
            cin.ignore();
            getline(cin, nombre);

            cout << "=> Ingrese el nuevo precio del producto: ";
            cin >> precio;

            cout << "=> Ingrese el nuevo stock del producto: ";
            cin >> stock;

            cout << "=> Ingrese la nueva categoria del producto (ID existente): ";
            cin >> categoria;

            // actualiza la linea con los datos modificados
            linea = idProducto + "~" + categoria + "~" + nombre + "~" + precio + "~" + stock;
        }
        productos.push_back(linea);
    }
    archivoProductos.close();

    // mensaje si no se encuentra el producto
    if (!productoEncontrado)
    {
        cout << "\n=> El producto con ID " << idProducto << " no se encontro. Volviendo al menu principal...\n";
        return;
    }

    // guarda los cambios en el archivo
    ofstream archivoProductosOut("data/productos.txt");
    for (const string &producto : productos)
    {
        archivoProductosOut << producto << "\n";
    }
    archivoProductosOut.close();

    cout << "\n=> Producto editado con exito.\n";
}

// funcion para eliminar un producto existente
void eliminarProducto()
{
    // verifico si hay productos en el archivo
    if (!verificarArchivoContieneDatos("data/productos.txt"))
    {
        cout << "=> No hay productos disponibles. Volviendo al menu principal...\n";
        return;
    }

    listarProductos();

    string idProducto;

    // aca solicita el id del producto a eliminar
    cout << "\n==========================================\n";
    cout << "            ELIMINAR PRODUCTO\n";
    cout << "==========================================\n";
    cout << "=> Ingrese el ID del producto que desea eliminar: ";
    cin >> idProducto;

    ifstream archivoProductos("data/productos.txt");
    vector<string> productosActualizados;
    string linea;
    bool encontrado = false;

    // recorre cada producto en el archivo
    while (getline(archivoProductos, linea))
    {
        // extrae el id del producto actual
        string idActual = linea.substr(0, linea.find("~"));

        if (idActual == idProducto)
        {
            encontrado = true;
            cout << "\n=> Producto con ID " << idProducto << " eliminado con exito.\n";
        }
        else
        {
            productosActualizados.push_back(linea);
        }
    }
    archivoProductos.close();

    // mensaje si no se encuentra el producto
    if (!encontrado)
    {
        cout << "\n=> El producto con ID " << idProducto << " no se encontro. Volviendo al menu principal...\n";
        return;
    }

    // reescribe el archivo sin el producto eliminado
    ofstream archivoProductosSalida("data/productos.txt");
    for (const auto &producto : productosActualizados)
    {
        archivoProductosSalida << producto << "\n";
    }
    archivoProductosSalida.close();
}

// menu principal para gestionar productos
void menuProductos()
{
    int opcion;
    do
    {
        cout << "\n==========================================\n";
        cout << "                PRODUCTOS\n";
        cout << "==========================================\n";
        cout << "[1]. Agregar productos\n";
        cout << "[2]. Editar productos\n";
        cout << "[3]. Eliminar productos\n";
        cout << "[4]. Volver\n";
        cout << "==========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cout << "\n";

        switch (opcion)
        {
        case 1:
            agregarProducto();
            break;
        case 2:
            editarProducto();
            break;
        case 3:
            eliminarProducto();
            break;
        case 4:
            cout << "Volviendo al menu de inventarios...\n";
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);
}
