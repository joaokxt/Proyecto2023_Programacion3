#ifndef U05_ARBOL_ARBOL_NODOARBOL_H_
#define U05_ARBOL_ARBOL_NODOARBOL_H_

#include <string.h>
#include <iostream>
#include "../Cola/Cola.h"
#include "../structs.h"
using namespace std;

template <class T>
class NodoArbolContenedor
{
private:
  Cola<Contenedor<T>> *cola = new Cola<Contenedor<T>>;
  NodoArbolContenedor *left, *right;

public:
  NodoArbolContenedor()
  {
    left = nullptr;
    right = nullptr;
  }

  NodoArbolContenedor(Contenedor<T> data)
  {
    cola = new Cola<Contenedor<T>>();
    cola->encolar(data);
    left = nullptr;
    right = nullptr;
  }

  Cola<Contenedor<T>>* getCola() const
  {
    return cola;
  }

  void addData(Contenedor<T> data)
  {
    cola->encolar(data);
  }

  NodoArbolContenedor *getRight() const
  {
    return right;
  }

  void setRight(NodoArbolContenedor *r)
  {
    this->right = r;
  }
  NodoArbolContenedor *getLeft() const
  {
    return left;
  }

  void setLeft(NodoArbolContenedor *l)
  {
    this->left = l;
  }

};

#endif // U05_ARBOL_ARBOL_NODOARBOL_H_
