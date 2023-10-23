#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>

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
    std::string codigo;
};

#endif