#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>
using namespace std;

class Articulo{
private:
    std::string grupo;
    std::string codigo;
    std::string nombreArticulo;
    int *deposito;
    int total;
public:
    Articulo(std::string grupo, std::string codigo, std::string nombreArtiuclo, int *deposito, int total){
        this->grupo = grupo;
        this->codigo = codigo;
        this->nombreArticulo = nombreArticulo;
        this->deposito = deposito;
        this->total = total;
    }
    ~Articulo(){
        delete deposito;
    }
    void print(){
        cout<<"GRUPO: "<<this->grupo<<endl;
        cout<<"CODIGO: "<<this->codigo<<endl;
        cout<<"NOMBRE: "<<this->nombreArticulo<<endl;
        for(int i=0; i<sizeof(deposito); i++){
            cout<<"DEPOSTIO "<<i+1<<": "<<this->deposito[i]<<endl;
        }
        cout<<"STOCK TOTAL: "<<this->total<<endl;
    }
};

template <class T>
struct Contenedor{
    T info; //cant deposito
    std::string codigo;
};

#endif