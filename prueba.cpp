#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Lista/Lista.h"
#include "Arbol/ArbolBinarioAVL.h"
#include "Arbol/ArbolBinarioContenedor.h"
#include "structs.h"

using namespace std;

int i, j, nMin, nMax, *nDeposito, cantArticulosDiferentes = 0, cantArticulos = 0, cantDepositos;
bool argumento[7] = {false};
string comandos[5] = {"total_art_dif", "total_art", "min_stock", "stock", "max_stock"};
Lista<string> nombresBusqueda;

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
    bool check;
    cantDepositos = contarColumnasCSV() - 3;
    for (i = 1; i < argc; i++)
    {
        check = false;
        if (argv[i] == comandos[2])
        {
            argumento[2] = true;
            nMin = stoi(argv[i + 1]);
        }
    }

    ArbolBinarioContenedor<int> *arbolMinimo = new ArbolBinarioContenedor<int>(nMin, new Articulo());
    ifstream archivoCSV("Inventariado Fisico.csv");

    int total, *deposito = new int[5];
    char separador = ';';
    string grupo, codigo, nombreArticulo, linea, *d = new string[5];
    bool presente;

    Articulo **articulosPunteros = new Articulo*[1000];

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

        for (i = 0; i < 5; i++)
        {
            getline(stream, d[i], separador);
            try{
                deposito[i] = stoi(d[i]);
            }catch(std::invalid_argument){
                deposito[i] = 0;
            } 
            total += deposito[i];
        }

        articuloActual = new Articulo(grupo, codigo, nombreArticulo, deposito, total);
        articulosPunteros[cantArticulos] = articuloActual;
        arbolMinimo->put(total, articuloActual);
        cantArticulos ++;
    }

    archivoCSV.close();

    clock_t begin;
    cout << "Comenzando a medir Tiempo\n"
         << endl;
    begin = clock();

    arbolMinimo->min();

    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << "Tardo elapsed_secs" << elapsed_secs << "\n"
         << std::endl;

}