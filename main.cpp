#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "HashMap/HashLista.h"
#include "HashMap/HashEntry.h"
#include "Lista/Lista.h"
#include "Arbol/ArbolBinarioAVL.h"
#include "Arbol/ArbolBinarioContenedor.h"
#include "structs.h"

using namespace std;

int i, j, nMin, nMax, *nDeposito, cantArticulosDiferentes = 0, cantArticulos = 0, cantDepositos, depos;
//  argumento indica la cantidad de argumentos que hay en total
bool argumento[7] = {false};
//  comandos es un arreglo de strings que contiene los comandos que se pueden ingresar
string comandos[5] = {"total_art_dif", "total_art", "min_stock", "stock", "max_stock"};
Lista<string> nombresBusqueda;

unsigned int hashFuncString(string clave)
{
    int x = clave[0], suma = 0, final = clave.size() - 1;

    suma += clave[1] * pow(x, 3) + clave[2] * pow(x, 2) + clave[3] * x;
    suma += clave[final] * pow(x, 3) + clave[final - 1] * pow(x, 2) + clave[final - 2] * x;

    return suma;
}

int contarColumnasCSV()
{
    // Se crea objeto asociado al archivo de inventario
    ifstream archivoCSV("Inventariado Fisico.csv");

    char buffer[4096];
    // Se lee la primera linea del CSV (el encabezado)
    archivoCSV.getline(buffer, 4096);

    // Objeto stringstream con contenido del encabezado
    // El stringstream permite leer como si fuera un flujo de caracteres
    stringstream encabezado(buffer);
    string columna;
    int contadorColumnas = 0;

    // Se divide al encabezado en columnas, separadas por ';'
    while (getline(encabezado, columna, ';'))
    {
        contadorColumnas++;
    }

    archivoCSV.close();
    return contadorColumnas;
}

int main(int argc, char *argv[])
{
    cantDepositos = contarColumnasCSV() - 3;

    nDeposito = new int[cantDepositos];
    for (i = 0; i < cantDepositos; i++)
    {
        nDeposito[i] = -1;
    }

    //  Se leen los argumentos ingresados en consola
    bool check;
    for (i = 0; i < argc; i++)
    {
        check = false;
        if (argv[i] == comandos[0])
        {
            argumento[0] = true;
        }
        else if (argv[i] == comandos[1])
        {
            argumento[1] = true;
        }
        else if (argv[i] == comandos[2])
        {
            if (argc <= i + 2)
            {
                argumento[2] = true;
                nMin = stoi(argv[i + 1]);
            }
            else
            {
                for (j = 0; j < 5; j++)
                {
                    if (argv[i + 2] == comandos[j])
                    {
                        check = true;
                        argumento[2] = true;
                        nMin = stoi(argv[i + 1]);
                        i++;
                    }
                }
                if (!check)
                {
                    argumento[3] = true;
                    nDeposito[stoi(argv[i + 2]) - 1] = stoi(argv[i + 1]);
                    depos = stoi(argv[i + 2]);
                    i += 2;
                }
            }
        }
        else if (argv[i] == comandos[3])
        {
            if (argc <= i + 2)
            {
                argumento[4] = true;
                nombresBusqueda.insertarUltimo(argv[i + 1]);
            }
            else
            {
                for (j = 0; j < 5; j++)
                {
                    if (argv[i + 2] == comandos[j])
                    {
                        check = true;
                        argumento[4] = true;
                        nombresBusqueda.insertarUltimo(argv[i + 1]);
                        i++;
                    }
                }
                if (!check)
                {
                    argumento[5] = true;
                    nombresBusqueda.insertarUltimo(argv[i + 1]);
                    depos = stoi(argv[i + 2]);
                    i += 2;
                }
            }
        }
        else if (argv[i] == comandos[4])
        {
            argumento[6] = true;
            nMax = stoi(argv[i + 1]);
        }
    }

    //  mapaArticulos es un HashMap que contiene todos los articulos, con su nombre como clave
    HashMapL<string, Articulo *> mapaArticulos(1024, *hashFuncString);

    //  listaArbolesDepositos es una lista de arboles, cada uno contiene los articulos de un deposito
    Lista<ArbolBinarioContenedor<int>> listaArbolesDepositos;

    //  arbolMinimo y arbolMaximo son arboles que contienen en su nodo raíz un objeto articulo nulo asociado con la cantidad n según la que queremos ordenar.
    ArbolBinarioContenedor<int> arbolMinimo(nMin, new Articulo());
    ArbolBinarioContenedor<int> arbolMaximo(nMax, new Articulo());

    for (i = 0; i < cantDepositos; i++)
    {
        ArbolBinarioContenedor<int> arbolDeposito(nDeposito[i], new Articulo());
        listaArbolesDepositos.insertarUltimo(arbolDeposito);
    }

    // Se abre el archivo a leer.
    ifstream archivoCSV("Inventariado Fisico.csv");

    // Se declaran variables necesarias para guardar datos de objetos.
    int total, *deposito = new int[cantDepositos];;
    char separador = ';';
    string grupo, codigo, nombreArticulo, linea, *d;
    bool presente;
    Articulo *articuloActual;

    //  Se lee la primera linea del CSV, que contiene los nombres de los depositos
    getline(archivoCSV, linea);

    //  Se procede a realizar la lectura del CSV
    while (getline(archivoCSV, linea))
    {
        stringstream stream(linea);
        deposito = new int[cantDepositos];
        d = new string[cantDepositos];

        total = 0;
        presente = false;

        getline(stream, grupo, separador);
        getline(stream, codigo, separador);
        getline(stream, nombreArticulo, separador);
        for (i = 0; i < cantDepositos; i++)
        {
            getline(stream, d[i], separador);
            try
            {
                deposito[i] = stoi(d[i]);
            }
            catch (std::invalid_argument)
            {
                deposito[i] = 0;
            }
            total += deposito[i];
        }

        articuloActual = new Articulo(grupo, codigo, nombreArticulo, deposito, total);

        arbolMinimo.put(total, articuloActual);
        arbolMaximo.put(total, articuloActual);

        Lista<HashEntry<string, Articulo *> *> *listaPrueba;
        try
        {
            listaPrueba = mapaArticulos.get(nombreArticulo);
            for (i = 0; i < listaPrueba->getTamanio(); i++)
            {
                if (listaPrueba->getDato(i)->getValor()->getNombre() == nombreArticulo)
                {
                    presente = true;
                }
            }
            if (!presente)
            {
                mapaArticulos.put(nombreArticulo, articuloActual);
                cantArticulos += total;
                cantArticulosDiferentes++;
            }
        }
        catch (int e)
        {
            mapaArticulos.put(nombreArticulo, articuloActual);
            cantArticulos += total;
            cantArticulosDiferentes++;
        }

        for (i = 0; i < cantDepositos; i++)
        {
            listaArbolesDepositos.getDato(i).put(deposito[i], articuloActual);
        }
    }
    archivoCSV.close();

    clock_t begin;
    std::cout << "Comenzando a medir Tiempo\n"
              << endl;
    begin = clock();

    //  Se procede a mostrar los argumentos ingresados
    if (argumento[0])
    {
        cout << "La cantidad total de articulos diferentes es de: " << cantArticulosDiferentes << endl;
    }
    if (argumento[1])
    {
        cout << "La cantidad total de articulos es de: " << cantArticulos << endl;
    }
    if (argumento[2])
    {
        cout << "Mostrando codigos de productos con " << nMin << " o menos en stock: " << endl;
        arbolMinimo.min();
        cout << endl;
    }
    if (argumento[3])
    {
        for(i = 0; i < cantDepositos; i++){
            if(nDeposito[i] != -1){
                cout << "Mostrando codigos de productos con " << nDeposito[i] << " o menos en el deposito " << i+1 <<": "<<endl;
                listaArbolesDepositos.getDato(i).min();
                cout << endl;
            }
        }
    }
    if (argumento[4])
    {
        Lista<HashEntry<string, Articulo *> *> *listaBusqueda;
        for (int i = 0; i < nombresBusqueda.getTamanio(); i++)
        {
            listaBusqueda = mapaArticulos.get(nombresBusqueda.getDato(i));
            string nombreBuscar = nombresBusqueda.getDato(i);

            for (j = 0; j < listaBusqueda->getTamanio(); j++)
            {
                if (listaBusqueda->getDato(j)->getValor()->getNombre() == nombreBuscar)
                {
                    listaBusqueda->getDato(j)->getValor()->printStock();
                }
            }
        }
    }
    if (argumento[5])
    {
        Lista<HashEntry<string, Articulo *> *> *listaBusqueda;
        for (int i = 0; i < nombresBusqueda.getTamanio(); i++)
        {
            listaBusqueda = mapaArticulos.get(nombresBusqueda.getDato(i));
            for (j = 0; j < listaBusqueda->getTamanio(); j++)
            {
                if (listaBusqueda->getDato(j)->getValor()->getNombre() == nombresBusqueda.getDato(i))
                {
                    listaBusqueda->getDato(j)->getValor()->printDeposito(depos);
                }
            }
        }
    }
    if (argumento[6])
    {
        cout << "Mostrando codigos de productos con " << nMax << " o mas en stock: " << endl
             << endl;
        arbolMaximo.max();
        cout << endl;
    }

    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << endl;
    cout << "Tardo elapsed_secs " << elapsed_secs << "\n"
         << std::endl;
}
