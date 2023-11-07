#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Lista/Lista.h"
#include "Arbol/ArbolBinarioContenedor.h"
#include "structs.h"

using namespace std;

int main(){
    ArbolBinarioContenedor<int> *arbolPrueba = new ArbolBinarioContenedor<int>(3, "-");

    cout<<"Hola";

    for(int i=0; i<10; i++){
        string codigo = "contenedor";
        codigo+=i+48;
        arbolPrueba->put(i, codigo);
    }

    cout<<"2"<<endl;
    Lista<Contenedor<int>> *listaContenedores;
    listaContenedores = arbolPrueba->min();
    Contenedor<int> contenedor = listaContenedores->getDato(0);
    cout<<contenedor.codigo<<endl;          
}