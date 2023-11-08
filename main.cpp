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

int i, j, nMin, nMax, *nDeposito, cantArticulosDiferentes = 0, cantArticulos = 0, cantDepositos, depos; //   depos los utilizo momentáneamente para el argumento 5
bool argumento[7] = {false};
string comandos[5] = {"total_art_dif", "total_art", "min_stock", "stock", "max_stock"};
Lista<string> nombresBusqueda;

unsigned int hashFuncString(string clave)
{
    try
    {
        return (unsigned int)stoi(clave);
    }
    catch (std::invalid_argument)
    {
        return 0;
    }
}

HashMapL<string, Articulo *> *mapaArticulos = new HashMapL<string, Articulo *>(1024, *hashFuncString);
Lista<ArbolBinarioContenedor<int>> *listaArbolesDepositos = new Lista<ArbolBinarioContenedor<int>>();
ArbolBinarioContenedor<int> *arbolMinimo;
ArbolBinarioContenedor<int> *arbolMaximo;

int contarColumnasCSV()
{
    ifstream archivoCSV("Inventariado Fisico.csv");

    const int bufferSize = 4096;
    char buffer[bufferSize];

    archivoCSV.getline(buffer, bufferSize);

    stringstream ss(buffer);
    string columna;
    int contadorColumnas = 0;

    while (getline(ss, columna, ';'))
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
    for(i = 0; i<cantDepositos; i++){
        nDeposito[i] = 0;
    }

    if (argv[1] == comandos[0])
    {
        argumento[0] = true;
    }
    if (argv[1] == comandos[1])
    {
        argumento[1] = true;
    }
    if (argv[1] == comandos[2])
    {
        if(argc == 3){
            argumento[2] = true;
            nMin = stoi(argv[2]);
        }else{
            argumento[3] = true;
            nDeposito[stoi(argv[3])-1] = stoi(argv[2]);
        }
    }
    if (argv[1] == comandos[3])
    {
        if(argc == 3){
            argumento[4] = true;
            nombresBusqueda.insertarUltimo(argv[2]);
        }else{
            argumento[5] = true;
            nDeposito[stoi(argv[3])-1] = stoi(argv[2]);
        }
    }
    if (argv[i] == comandos[4])
    {
        argumento[6] = true;
        nMax = stoi(argv[i + 1]);
    }

arbolMinimo = new ArbolBinarioContenedor<int>(nMin, new Articulo());
arbolMaximo = new ArbolBinarioContenedor<int>(nMax, new Articulo());

ifstream archivoCSV("Inventariado Fisico.csv");
int *deposito = new int[cantDepositos];

for (i = 0; i < cantDepositos; i++)
{
    ArbolBinarioContenedor<int> arbolDeposito(nDeposito[i], new Articulo());
    listaArbolesDepositos->insertarUltimo(arbolDeposito);
}

int total;
char separador = ';';
string grupo, codigo, nombreArticulo, linea, *d;
bool presente;

deposito = new int[cantDepositos];
d = new string[cantDepositos];

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

    Lista<HashEntry<string, Articulo *> *> *listaPrueba;
    try
    {
        listaPrueba = mapaArticulos->get(codigo);
        for (i = 0; i < listaPrueba->getTamanio(); i++)
        {
            if (listaPrueba->getDato(i)->getValor()->getCodigo() == codigo)
            {
                presente = true;
            }
        }
        if (!presente)
        {
            mapaArticulos->put(codigo, articuloActual);
            cantArticulos += total;
            cantArticulosDiferentes++;
        }
    }
    catch (int e)
    {
        mapaArticulos->put(codigo, articuloActual);
        cantArticulos += total;
        cantArticulosDiferentes++;
    }

    for (i = 0; i < cantDepositos; i++)
    {
        listaArbolesDepositos->getDato(i).put(deposito[i], articuloActual);
    }

    arbolMinimo->put(total, articuloActual);
    arbolMaximo->put(total, articuloActual);
}

archivoCSV.close();

clock_t begin;
std::cout << "Comenzando a medir Tiempo\n" << endl;
begin = clock();

switch (argumento[0])
{
case 0:
    break;
case 1:
    std::cout << "La cantidad total de articulos diferentes es de: " << cantArticulosDiferentes << endl;
    break;
}
switch (argumento[1])
{
case 0:
    break;
case 1:
    std::cout << "La cantidad total de articulos es de: " << cantArticulos << endl;
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
        listaArbolesDepositos->getDato(i).min();
    break;
}
switch (argumento[4])
{
case 0:
    break;
case 1:
    Lista<HashEntry<string, Articulo *> *> *listaBusqueda;
    for (int i = 0; i < nombresBusqueda.getTamanio(); i++)
    {
        listaBusqueda = mapaArticulos->get(nombresBusqueda.getDato(i));
        for (j = 0; j < listaBusqueda->getTamanio(); j++)
        {
            if (listaBusqueda->getDato(j)->getValor()->getCodigo() == nombresBusqueda.getDato(i))
            {
                listaBusqueda->getDato(j)->getValor()->printStock();
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
    Lista<HashEntry<string, Articulo *> *> *listaBusqueda;
    for (int i = 0; i < nombresBusqueda.getTamanio(); i++)
    {
        listaBusqueda = mapaArticulos->get(nombresBusqueda.getDato(i));
        for (j = 0; j < listaBusqueda->getTamanio(); j++)
        {
            if (listaBusqueda->getDato(j)->getValor()->getCodigo() == nombresBusqueda.getDato(i))
            {
                listaBusqueda->getDato(j)->getValor()->printDeposito(depos);
            }
        }
    }
    break;
}
switch (argumento[6])
{
case 0:
    break;
case 1:
    arbolMaximo->max();
    break;
}

clock_t end = clock();
double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
cout << "Tardo elapsed_secs" << elapsed_secs << "\n"
     << std::endl;
}
