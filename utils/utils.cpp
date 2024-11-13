#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// estructura para los productos
struct Producto
{
    string idProducto;
    string idCategoria;
    string nombre;
    string precio;
    string stock;
};

// estructura para las categorias
struct Categoria
{
    string idCategoria;
    string nombreCategoria;
};

// funcion para cargar productos desde el archivo en la lista de categorias
void cargarProductos(vector<Producto> &productos)
{
    productos.clear(); // asegura que el vector este vacio
    ifstream archivoProductos("data/productos.txt");
    string linea;

    // lee cada linea y extrae los datos del producto
    while (getline(archivoProductos, linea))
    {
        Producto producto;
        int pos1 = linea.find("~");
        int pos2 = linea.find("~", pos1 + 1);
        int pos3 = linea.find("~", pos2 + 1);
        int pos4 = linea.find("~", pos3 + 1);

        producto.idProducto = linea.substr(0, pos1);
        producto.idCategoria = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        producto.nombre = linea.substr(pos2 + 1, pos3 - pos2 - 1);
        producto.precio = linea.substr(pos3 + 1, pos4 - pos3 - 1);
        producto.stock = linea.substr(pos4 + 1);

        productos.push_back(producto); // añade el producto al vector
    }
    archivoProductos.close();
}

// funcion para cargar categorias desde el archivo en la lista de productos
void cargarCategorias(vector<Categoria> &categorias)
{
    categorias.clear(); // asegura que el vector este vacio
    ifstream archivoCategorias("data/categorias.txt");
    string linea;

    // lee cada linea y extrae los datos de la categoria
    while (getline(archivoCategorias, linea))
    {
        Categoria categoria;
        int pos1 = linea.find("~");
        int pos2 = linea.find("~", pos1 + 1);

        categoria.idCategoria = linea.substr(0, pos1);
        categoria.nombreCategoria = linea.substr(pos1 + 1, pos2 - pos1 - 1);

        categorias.push_back(categoria); // añade la categoria al vector
    }
    archivoCategorias.close();
}

// funcion para verificar si un producto existe en la lista de productos por su idProducto
bool verificarExisteProducto(const string &idProducto, const vector<Producto> &productos)
{
    for (const auto &producto : productos)
    {
        if (producto.idProducto == idProducto)
        {
            return true; // el producto fue encontrado
        }
    }
    return false; // el producto no fue encontrado
}

// funcion para verificar si una categoria existe en la lista de categorias por su idCategoria
bool verificarExisteCategoria(const string &idCategoria, const vector<Categoria> &categorias)
{
    for (const auto &categoria : categorias)
    {
        if (categoria.idCategoria == idCategoria)
        {
            return true; // la categoria fue encontrada
        }
    }
    return false; // la categoria no fue encontrada
}

// esta funcion verifica si un archivo tiene contenido
bool verificarArchivoContieneDatos(const string &rutaArchivo)
{
    ifstream archivo(rutaArchivo);

    // si el archivo se abre correctamente y se puede leer una linea, tiene datos...
    if (archivo.is_open() && archivo.peek() != EOF)
    {
        archivo.close(); // se cierra el archivo
        return true;     // retorna verdadero si hay datos
    }

    archivo.close(); // se cierra el archivo
    return false;    // retorna falso si no hay datos
}

// en esta funcion se generara un nuevo ID basado en el ID maximo de un archivo
string generarNuevoID(const string &rutaArchivo)
{
    ifstream archivo(rutaArchivo);
    string linea;
    int maxID = 0;

    // se lee cada linea para encontrar el ID mas alto...
    while (getline(archivo, linea))
    {
        int idNum = stoi(linea.substr(0, linea.find("~"))); // se toma el ID inicial de la linea
        if (idNum > maxID)
        {
            maxID = idNum; // el maximo se actualiza si se encuentra uno mayor
        }
    }
    archivo.close();

    // se incrementa el ID y se convierte en string con ceros al inicio si es necesario...
    maxID += 1;
    string nuevoID = to_string(maxID);
    if (nuevoID.length() < 4)
    {
        nuevoID.insert(0, 4 - nuevoID.length(), '0'); // y al final añaden ceros para completar 4 digitos
    }
    return nuevoID;
}

// función que actualiza el stock de un producto en el archivo productos.txt
void actualizarStockEnArchivo(const Producto &productoActualizado, vector<Producto> &productos)
{
    // actualiza el stock en la lista local de productos
    for (auto &producto : productos)
    {
        if (producto.idProducto == productoActualizado.idProducto)
        {
            producto.stock = productoActualizado.stock;
            break;
        }
    }

    // abre el archivo en modo de escritura para sobrescribirlo con el stock actualizado
    ofstream archivoProductos("data/productos.txt");
    if (archivoProductos.is_open())
    {
        for (const auto &producto : productos)
        {
            archivoProductos << producto.idProducto << "~" << producto.idCategoria << "~"
                             << producto.nombre << "~" << producto.precio << "~" << producto.stock << "\n";
        }
        archivoProductos.close();
    }
    else
    {
        cout << "\n=> No se pudo abrir el archivo de productos para actualizar el stock.\n";
    }
}
