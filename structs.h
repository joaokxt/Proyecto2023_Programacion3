#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>

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
        std::cout<<"GRUPO: "<<this->grupo<<std::endl;
        std::cout<<"CODIGO: "<<this->codigo<<std::endl;
        std::cout<<"NOMBRE: "<<this->nombreArticulo<<std::endl;
        for(int i=0; i<sizeof(deposito); i++){
            std::cout<<"DEPOSTIO "<<i+1<<": "<<this->deposito[i]<<std::endl;
        }
        std::cout<<"STOCK TOTAL: "<<this->total<<std::endl;
    }
};

template <class T>
struct Contenedor{
    T info; //cant deposito
    std::string codigo;
};

#endif