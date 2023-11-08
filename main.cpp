#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "HashMap/HashMap.h"
#include "HashMap/HashLista.h"
#include "HashMap/HashEntry.h"
#include "Lista/Lista.h"
#include "Arbol/ArbolBinarioAVL.h"
#include "Arbol/ArbolBinarioContenedor.h"
#include "structs.h"

using namespace std;

int i, j, nMin, nMax, *nDeposito, cantArticulosDiferentes = 0, cantArticulos = 0, cantDepositos;
bool argumento[7] = {false};
string comandos[5] = {"total_art_dif", "total_art", "min_stock", "stock", "max_stock"};
Lista<string> nombresBusqueda;

unsigned int hashFuncString(string clave)
{
    return (unsigned int)stoi(clave);
}

HashMapL<string, Articulo *> *mapaArticulos = new HashMapL<string, Articulo *>(1024, *hashFuncString);
Lista<ArbolBinarioContenedor<int>> *listaArbolesDepositos = new Lista<ArbolBinarioContenedor<int>>();
ArbolBinarioContenedor<int> *arbolMinimo = new ArbolBinarioContenedor<int>(nMin, new Articulo());
ArbolBinarioContenedor<int> *arbolMaximo = new ArbolBinarioContenedor<int>(nMax, new Articulo());

int contarColumnasCSV()
{
    ifstream archivoCSV("Inventariado Fisico.csv");

    const int bufferSize = 4096;
    char buffer[bufferSize];

    archivoCSV.getline(buffer, bufferSize);

    stringstream ss(buffer);
    string columna;
    int contadorColumnas = 0;

    while (getline(ss, columna, ','))
    {
        contadorColumnas++;
    }

    archivoCSV.close();
    return contadorColumnas;
}

int main(int argc, char *argv[])
{
    // LECTURA ARGUMENTOS LINEA DE COMANDO
    bool check;
    cantDepositos = contarColumnasCSV() - 3;
    nDeposito = new int[cantDepositos];
    for (i = 1; i < argc; i++)
    {
        check = false;
        if (argv[i] == comandos[0])
        {
            argumento[0] = true;
        }
        if (argv[i] == comandos[1])
        {
            argumento[1] = true;
        }
        if (argv[i] == comandos[2])
        {
            for (j = 0; j < 5; j++)
            {
                if (argv[i + 2] == comandos[j])
                {
                    argumento[2] = true;
                    nMin = stoi(argv[i + 1]);

                    i++;
                    check = true;
                }
            }
            if (!check)
            {
                argumento[3] = true;
                nDeposito[stoi(argv[i + 2]) - 1] = stoi(argv[i + 1]);

                i += 2;
            }
        }
        if (argv[i] == comandos[3])
        {
            for (j = 0; j < 5; j++)
            {
                if (argv[i + 2] == comandos[j])
                {
                    argumento[4] = true;
                    nombresBusqueda.insertarUltimo(argv[i + 1]);

                    i++;
                    check = true;
                }
            }
            if (!check)
            {
                argumento[5] = true;
                // deposito a buscar

                i += 2;
            }
        }
        if (argv[i] == comandos[4])
        {
            argumento[6] = true;
            nMax = stoi(argv[i + 1]);
        }
    }

    ifstream archivoCSV("Inventariado Fisico.csv");
    int *deposito = new int[cantDepositos];

    // CREACION: UN ARBOL POR C/ DEPOSITO. NODO INICIAL VALOR N A BUSCAR
    for (i = 0; i < cantDepositos; i++)
    {
        ArbolBinarioContenedor<int> arbolDeposito(nDeposito[i], new Articulo());
        listaArbolesDepositos->insertarUltimo(arbolDeposito);
    }

    int total;
    char separador = ',';
    string grupo, codigo, nombreArticulo, linea, *d = new string[cantDepositos];
    bool presente;

    getline(archivoCSV, linea);
    while (getline(archivoCSV, linea))
    {
        Articulo *articuloActual;

        stringstream stream(linea);
        total = 0;
        presente = false;

        getline(stream, grupo, separador);
        getline(stream, codigo, separador);
        getline(stream, nombreArticulo, separador);
        for (i = 0; i < cantDepositos; i++)
        {
            getline(stream, d[i], separador);
            deposito[i] = stoi(d[i]);
            total += deposito[i];
        }

        articuloActual = new Articulo(grupo, codigo, nombreArticulo, deposito, total);

        Lista<HashEntry<string, Articulo *>> listaPrueba;
        listaPrueba = mapaArticulos->get(codigo);
        for (i = 0; i < listaPrueba.getTamanio(); i++)
        {
            if (listaPrueba.getDato(i).getValor()->getCodigo() == codigo)
            {
                presente = true;
            }
        }

        if (!presente)
        {
            mapaArticulos->put(codigo, articuloActual);
            cantArticulos += total;
            cantArticulosDiferentes ++;
        }

        for (i = 0; i < cantDepositos; i++)
        {
            listaArbolesDepositos->getDato(i).put(deposito[i], articuloActual);
        }
    }

    archivoCSV.close();

    clock_t begin;
    cout << "Comenzando a medir Tiempo\n"
         << endl;
    begin = clock();

    switch (argumento[0])
    {
    case 0:
        break;
    case 1:
        cout << "La cantidad total de articulos diferentes es de: " << cantArticulosDiferentes << endl;
        break;
    }
    switch (argumento[1])
    {
    case 0:
        break;
    case 1:
        cout << "La cantidad total de articulos es de: " << cantArticulos << endl;
        break;
    }
    switch (argumento[2])
    {
    case 0:
        break;
    case 1:
        arbolMinimo->min();
        break;
    }
    switch (argumento[3])
    {
    case 0:
        break;
    case 1:
        for (int i = 0; i < listaArbolesDepositos->getTamanio(); i++)
            listaArbolesDepositos->getDato(i).print();
        break;
    }
    switch (argumento[4])
    {
    case 0:
        break;
    case 1:
        Lista<HashEntry<string, Articulo *>> listaBusqueda;
        for (int i = 0; i < nombresBusqueda.getTamanio(); i++){
            listaBusqueda = mapaArticulos->get(nombresBusqueda.getDato(i));
            for(j = 0; j<listaBusqueda.getTamanio(); j++){
                if(listaBusqueda.getDato(j).getValor()->getCodigo() == nombresBusqueda.getDato(i)){
                    listaBusqueda.getDato(j).getValor()->printStock();
                }
            }
        }
        break;
    }
    switch (argumento[5])
    {
    case 0:
        break;
    case 1:
     for (int i = 0; i < nombresBusqueda.getTamanio(); i++)
     {
        
     }
     

        break;
    }
    switch (argumento[6])
    {
    case 0:
        break;
    case 1:
        Lista<Contenedor<int>> ListaMaximos;
        arbolMaximo->max();
        break;
    }

    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << "Tardo elapsed_secs" << elapsed_secs << "\n"
         << std::endl;
}
