#include <iostream>
#include "../HashMap/HashLista.h"
#include <sstream>
#include <fstream>
#define nombre_archivo "Inventario.csv"
using namespace std;

int main(){

    ifstream archivo(nombre_archivo);
    string linea;
    char seprador = ',';
    getline(archivo,linea);

    cout<<"a";
    while(getline(archivo,linea)){
        stringstream stream(linea);
        string grupo,codigo,articulo,d1,d2,d3,d4,d5;

        getline(stream,grupo,seprador);
        getline(stream,codigo,seprador);
        getline(stream,articulo,seprador);
        getline(stream,d1,seprador);
        getline(stream,d2,seprador);
        getline(stream,d3,seprador);
        getline(stream,d4,seprador);
        getline(stream,d5,seprador);


        cout<<"================"<<endl;
        cout<<"Grupo: "<<grupo<<endl;
        cout<<"Codigo: "<<codigo<<endl;
        cout<<"Articulo: "<<articulo<<endl;\
        cout<<"D1: "<<d1<<endl;
        cout<<"D2: "<<d2<<endl;
        cout<<"D3: "<<d3<<endl;
        cout<<"D4: "<<d4<<endl;
        cout<<"D5: "<<d5<<endl;


    }
    archivo.close();
}