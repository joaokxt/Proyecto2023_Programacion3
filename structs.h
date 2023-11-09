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
    Articulo(){
        this->grupo = "NULO";
        this->codigo = "NULO";
        this->nombreArticulo = "NULO";
        this->deposito = nullptr;
        this->total = -1;
    }
    Articulo(std::string grupo, std::string codigo, std::string nombreArticulo, int *deposito, int total){
        this->grupo = grupo;
        this->codigo = codigo;
        this->nombreArticulo = nombreArticulo;
        this->deposito = deposito;
        this->total = total;
    }
    ~Articulo(){
        delete deposito;
    }
    std::string getGrupo(){
        return this->grupo;
    }
    std::string getCodigo(){
        return this->codigo;
    }
    std::string getNombre(){
        return this->nombreArticulo;
    }
    int getTotal(){
        return this->total;
    }
    void print(){
        std::cout<<"|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|"<<endl;
        std::cout<<" GRUPO: "<<this->grupo<<endl;
        std::cout<<" CODIGO: "<<this->codigo<<endl;
        std::cout<<" NOMBRE: "<<this->nombreArticulo<<endl;
        for(int i=0; i<sizeof(deposito)-3; i++) std::cout<<" DEPOSITO "<<i+1<<": "<<this->deposito[i]<<endl;
        std::cout<<"    STOCK TOTAL: "<<this->total<<std::endl;
    }
    void printStock(){
        std::cout<<"STOCK DE ["<<this->nombreArticulo<<"]: "<<this->total<<std::endl;
    }
    void printCodigo(){
        std::cout<<this->codigo<<endl;
    }
    void printNombre(){
        std::cout<<this->nombreArticulo<<endl;
    }
    void printDeposito(int numDeposito){
        std::cout<<"STOCK EN DEPOSITO ["<<numDeposito<<"]  DE ["<<this->nombreArticulo<<"]: "<<this->deposito[numDeposito-1]<<std::endl;
    }
};



template <class T>
struct Contenedor{
    T info;
    Articulo *puntero;
};

#endif