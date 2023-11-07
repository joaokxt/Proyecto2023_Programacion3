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

int i, n, cantArticulosDiferentes = 0, cantArticulos = 0;

unsigned int hashFuncString(string clave)
{
  return (unsigned int)stoi(clave);
}

ArbolBinarioAVL<Contenedor<int>*> *arbolTotales = new ArbolBinarioAVL<Contenedor<int>*>();
HashMapL<string, Articulo*> *mapaArticulos = new HashMapL<string, Articulo*>(1024, *hashFuncString);
Lista<ArbolBinarioContenedor<int>> *listaArbolesDepositos = new Lista<ArbolBinarioContenedor<int>>();


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

    for(i=0; i<cantDepositos; i++){
        ArbolBinarioContenedor<int> arbolDeposito(n, "--");
        listaArbolesDepositos->insertarUltimo(arbolDeposito);
    }
    
    
    getline(archivoCSV,linea);
    while(getline(archivoCSV,linea)){
        struct Articulo *articuloActual;
        struct Contenedor<int> *contenedorTotal = new Contenedor<int>;
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

        articuloActual = new Articulo(grupo, codigo, articulo, deposito, total);

        contenedorTotal->info = total;
        contenedorTotal->puntero = articuloActual;

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


  
