#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "../../utils/utils.cpp"

using namespace std;

// funcion que agrega una nueva categoria y la guarda en categorias.txt
void agregarCategoria()
{
    Categoria nuevaCategoria;

    cout << "==========================================\n";
    cout << "            AGREGAR CATEGORIA\n";
    cout << "==========================================\n";

    // generacion automatica de un nuevo ID correlativo para la categoria
    nuevaCategoria.idCategoria = generarNuevoID("data/categorias.txt");

    // solicita el nombre de la nueva categoria
    cout << "=> Ingrese el nombre de la categoria: ";
    cin.ignore();
    getline(cin, nuevaCategoria.nombreCategoria);

    // solicita la descripcion de la categoria
    cout << "=> Ingrese la descripcion de la categoria: ";
    getline(cin, nuevaCategoria.descripcion);

    // abre el archivo de categorias en modo de agregado y verifica si se abre correctamente
    ofstream archivoCategorias("data/categorias.txt", ios::app);

    if (archivoCategorias.is_open())
    {
        // guarda la nueva categoria en el archivo con "~" como delimitador de campos
        archivoCategorias << nuevaCategoria.idCategoria << "~" << nuevaCategoria.nombreCategoria << "~" << nuevaCategoria.descripcion << "\n";
        archivoCategorias.close();

        cout << "\n=> Categoria agregada con exito.\n";
    }
    else
    {
        cout << "\n=> No se pudo abrir el archivo de categorias para agregar la categoria.\n";
    }
}

// funcion para editar los detalles de una categoria existente
void editarCategoria()
{
    if (!verificarArchivoContieneDatos("data/categorias.txt"))
    {
        cout << "=> No hay categorias disponibles. Volviendo al menu principal...\n";
        return;
    }

    listarCategorias();

    string idCategoria;

    // solicita el id de la categoria a editar
    cout << "\n==========================================\n";
    cout << "            EDITAR CATEGORIA\n";
    cout << "==========================================\n";
    cout << "=> Ingrese el ID de la categoria que desea editar: ";
    cin >> idCategoria;

    vector<string> categorias;
    ifstream archivoCategorias("data/categorias.txt");
    bool categoriaEncontrada = false;
    string linea, nombre, descripcion;

    // recorre cada linea del archivo para buscar la categoria a editar
    while (getline(archivoCategorias, linea))
    {
        int pos1 = linea.find("~");
        int pos2 = linea.find("~", pos1 + 1);

        // extrae los campos de la categoria actual
        string idActual = linea.substr(0, pos1);
        nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        descripcion = linea.substr(pos2 + 1);

        // verifica si el id actual coincide con el ingresado
        if (idActual == idCategoria)
        {
            categoriaEncontrada = true;

            // solicita los nuevos datos para actualizar la categoria
            cout << "=> Ingrese el nuevo nombre de la categoria: ";
            cin.ignore();
            getline(cin, nombre);

            cout << "=> Ingrese la nueva descripcion de la categoria: ";
            getline(cin, descripcion);

            // actualiza la linea con los datos modificados
            linea = idCategoria + "~" + nombre + "~" + descripcion;
        }
        categorias.push_back(linea);
    }
    archivoCategorias.close();

    // mensaje si no se encuentra la categoria
    if (!categoriaEncontrada)
    {
        cout << "\n=> La categoria con ID " << idCategoria << " no se encontro. Volviendo al menu principal...\n";
        return;
    }

    // guarda los cambios en el archivo
    ofstream archivoCategoriasOut("data/categorias.txt");
    for (const string &categoria : categorias)
    {
        archivoCategoriasOut << categoria << "\n";
    }
    archivoCategoriasOut.close();

    cout << "\n=> Categoria editada con exito.\n";
}

// funcion para eliminar una categoria existente
void eliminarCategoria()
{
    // verifica si hay categorias en el archivo
    if (!verificarArchivoContieneDatos("data/categorias.txt"))
    {
        cout << "=> No hay categorias disponibles. Volviendo al menu principal...\n";
        return;
    }

    listarCategorias();

    string idCategoria;

    // solicita el id de la categoria a eliminar
    cout << "\n==========================================\n";
    cout << "            ELIMINAR CATEGORIA\n";
    cout << "==========================================\n";
    cout << "=> Ingrese el ID de la categoria que desea eliminar: ";
    cin >> idCategoria;

    ifstream archivoCategorias("data/categorias.txt");
    vector<string> categoriasActualizadas;
    string linea;
    bool encontrado = false;

    // recorre cada linea para buscar la categoria a eliminar
    while (getline(archivoCategorias, linea))
    {
        string idActual = linea.substr(0, linea.find("~"));

        if (idActual == idCategoria)
        {
            encontrado = true;
            cout << "\n=> Categoria con ID " << idCategoria << " eliminada con exito.\n";
        }
        else
        {
            categoriasActualizadas.push_back(linea);
        }
    }
    archivoCategorias.close();

    // mensaje si no se encuentra la categoria
    if (!encontrado)
    {
        cout << "\n=> La categoria con ID " << idCategoria << " no se encontro. Volviendo al menu principal...\n";
        return;
    }

    // reescribe el archivo sin la categoria eliminada
    ofstream archivoCategoriasSalida("data/categorias.txt");
    for (const auto &categoria : categoriasActualizadas)
    {
        archivoCategoriasSalida << categoria << "\n";
    }
    archivoCategoriasSalida.close();
}

// menu principal para gestionar categorias
void menuCategorias()
{
    int opcion;
    do
    {
        cout << "\n==========================================\n";
        cout << "                CATEGORIAS\n";
        cout << "==========================================\n";
        cout << "[1]. Agregar categorias\n";
        cout << "[2]. Editar categorias\n";
        cout << "[3]. Eliminar categorias\n";
        cout << "[4]. Volver\n";
        cout << "==========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cout << "\n";

        switch (opcion)
        {
        case 1:
            agregarCategoria();
            break;
        case 2:
            editarCategoria();
            break;
        case 3:
            eliminarCategoria();
            break;
        case 4:
            cout << "Volviendo al menu de inventarios...\n";
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);
}
