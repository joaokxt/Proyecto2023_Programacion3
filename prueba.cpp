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
    Articulo *articulo = new Articulo();
    ArbolBinarioContenedor<int> *arbolPrueba = new ArbolBinarioContenedor<int>(3, articulo);

    for(int i=0; i<10; i++){
        string grupo = "contenedor", codigo = "contenedor", nombre = "nombre";
        codigo+=i+48;
        int *deposito = new int[5];
        articulo = new Articulo(grupo, codigo, nombre, deposito, i);
        arbolPrueba->put(i, articulo);
    }

    Lista<Contenedor<int>> listaContenedores;
    listaContenedores = arbolPrueba->max();
    for(int i=0; i<listaContenedores.getTamanio(); i++){
        articulo = listaContenedores.getDato(i).puntero;
        if(articulo->getGrupo() != "NULO"){
            articulo->print();
        }
    }
    
}