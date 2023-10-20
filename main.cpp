#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "HashMap/HashMap.h"
#include "HashMap/HashLista.h"
#include "HashMap/HashEntry.h"
#include "Lista/Lista.h"
#include "Arbol/ArbolBinario.h"

using namespace std;

int i, cantArticulosDiferentes = 0, cantArticulos = 0;

struct Articulo{
    std::string grupo;
    std::string codigo;
    std::string nombreArticulo;
    int *deposito;
    int total;
};

template <class T>
struct Contenedor{
    T data;
    string codigo;
};

ArbolBinario<Contenedor<int>*> *arbolTotales = new ArbolBinario<Contenedor<int>*>();
HashMapL<string, Articulo*> *mapaArticulos = new HashMapL<string, Articulo*>(1024);
HashMapL<int, ArbolBinario<Contenedor<int>*>*> *mapaDepositos;


int contarColumnasCSV(){
    ifstream archivoCSV("Inventariado Fisico.csv");

    const int bufferSize = 4096;  
    char buffer[bufferSize];

    archivoCSV.getline(buffer, bufferSize); 

    stringstream ss(buffer);
    string columna;
    int contadorColumnas = 0;

    while (getline(ss, columna, ',')) {
        contadorColumnas++;
    }

    archivoCSV.close();
    return contadorColumnas;
}

int main() {
    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();
    
    ifstream archivoCSV("Inventariado Fisico.csv");

    int total, cantDepositos = contarColumnasCSV() - 3, *deposito = new int[cantDepositos];
    char separador = ',';
    string grupo, codigo, articulo, linea, *d = new string[cantDepositos];
    mapaDepositos = new HashMapL<int, ArbolBinario<Contenedor<int>*>*>(cantDepositos);

    for(i=0; i<cantDepositos; i++){
        ArbolBinario<Contenedor<int>*>* arbol = new ArbolBinario<Contenedor<int>*>();
        mapaDepositos->put(i, arbol);
    }
    
    
    getline(archivoCSV,linea);
    while(getline(archivoCSV,linea)){
        struct Articulo *articuloActual = new Articulo;
        struct Contenedor<int> *contenedorTotal = new Contenedor<int>;
        struct Contenedor<int> *contenedorDeposito = new Contenedor<int>;
        stringstream stream(linea);
        total = 0;

        getline(stream,grupo,separador);
        getline(stream,codigo,separador);
        getline(stream,articulo,separador);
        for(i=0; i<cantDepositos; i++){
            getline(stream, d[i], separador);
            deposito[i] = stoi(d[i]);
            total += deposito[i];
        }

        articuloActual->grupo = grupo;
        articuloActual->codigo = codigo;
        articuloActual->nombreArticulo = articulo;
        articuloActual->deposito = deposito;
        articuloActual->total = total;

        contenedorTotal->data = total;
        contenedorTotal->codigo = codigo;

        for(i=0; i<cantDepositos; i++){
            contenedorDeposito->data = deposito[i];
            contenedorDeposito->codigo = codigo;
            mapaDepositos->get(i)->put(contenedorDeposito);
        }

        mapaArticulos->put(articulo, articuloActual);
        arbolTotales->put(contenedorTotal);

        cantArticulos += total;
        cantArticulosDiferentes ++;
    } 

    archivoCSV.close();
    
    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;
}


  
