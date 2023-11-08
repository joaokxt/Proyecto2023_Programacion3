#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
    try
    {
        return (unsigned int)stoi(clave);
    }
    catch (std::invalid_argument)
    {
        return 0;
    }
}

//  mapaArticulos es un HashMap que contiene todos los articulos, con su codigo como clave
HashMapL<string, Articulo *> *mapaArticulos = new HashMapL<string, Articulo *>(1024, *hashFuncString);
//  listaArbolesDepositos es una lista de arboles, cada uno contiene los articulos de un deposito
Lista<ArbolBinarioContenedor<int>> *listaArbolesDepositos = new Lista<ArbolBinarioContenedor<int>>();
//  arbolMinimo es un arbol que contiene los articulos con menor stock
ArbolBinarioContenedor<int> *arbolMinimo;
//  arbolMaximo es un arbol que contiene los articulos con mayor stock
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

clock_t begin;
std::cout << "Comenzando a medir Tiempo\n" << endl;
begin = clock();

bool check;
cantDepositos = contarColumnasCSV() - 3;
nDeposito = new int[cantDepositos];
//  Se arman/inicializan los argumentos
for(i = 0; i<cantDepositos; i++){
    nDeposito[i] = 0;
}

for(i = 0; i<argc; i++){
    check = false;
    if (argv[i] == comandos[0]){
        argumento[0] = true;
    }
    else if (argv[i] == comandos[1]){
        argumento[1] = true;
    }
    else if (argv[i] == comandos[2]){     
        if(argc <= i + 2){
            argumento[2] = true;
            nMin = stoi(argv[i+1]);       
        }else{
            for(j = 0; j<5; j++){
                if(argv[i+2] == comandos[j]){
                    check = true;
                    argumento[2] = true;
                    nMin = stoi(argv[i+1]); 
                    i++;
                }
            }
            if(!check){
                argumento[3] = true;
                nDeposito[stoi(argv[3])-1] = stoi(argv[i+1]);
                depos = stoi(argv[3]);
                i+=2;
            }
        }
    }
    else if (argv[i] == comandos[3]){ 
        if(argc <= i + 2){
            argumento[4] = true;
            nombresBusqueda.insertarUltimo(argv[i+1]);     
        }else{
            for(j = 0; j<5; j++){
                if(argv[i+2] == comandos[j]){
                    check = true;
                    argumento[4] = true;
                    nombresBusqueda.insertarUltimo(argv[i+1]);  
                    i++;
                }
            }
            if(!check){
                argumento[5] = true;
                nombresBusqueda.insertarUltimo(argv[i+1]);   
                depos = stoi(argv[i+2]);
                i+=2;
            }
        }       
    }
    else if (argv[i] == comandos[4]){
        argumento[6] = true;
        nMax = stoi(argv[i+1]);
    }
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

    arbolMinimo->put(total, articuloActual);
    arbolMaximo->put(total, articuloActual);

    Lista<HashEntry<string, Articulo *> *> *listaPrueba;
    try
    {
        listaPrueba = mapaArticulos->get(nombreArticulo);
        for (i = 0; i < listaPrueba->getTamanio(); i++)
        {
            if (listaPrueba->getDato(i)->getValor()->getCodigo() == codigo)
            {
                presente = true;
            }
        }
        if (!presente)
        {
            mapaArticulos->put(nombreArticulo, articuloActual);
            cantArticulos += total;
            cantArticulosDiferentes++;
        }
    }
    catch (int e)
    {
        if(e == 404){
            mapaArticulos->put(nombreArticulo, articuloActual);
            cantArticulos += total;
            	cantArticulosDiferentes++;
        }
    }

    for (i = 0; i < cantDepositos; i++)
    {
        listaArbolesDepositos->getDato(i).put(deposito[i], articuloActual);
    }
}
archivoCSV.close();


//  Se procede a mostrar los argumentos ingresados
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
    cout<<"Mostrando códigos de productos con menos de "<<nMin<<" en stock: "<<endl;
    arbolMinimo->min();
    cout<<endl;
    break;
}
switch (argumento[3])
{
case 0:
    break;
case 1:
    /*for (int i = 0; i < cantDepositos; i++)
        listaArbolesDepositos->getDato(i).min();*/
    listaArbolesDepositos->getDato(depos-1).min();
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
    cout<<"Mostrando codigos de productos con mas de "<<nMax<<" en stock: "<<endl<<endl;
    arbolMaximo->max();
    cout<<endl;
    break;
}

clock_t end = clock();
double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
cout << "Tardo elapsed_secs " << elapsed_secs << "\n"
     << std::endl;
}
