#ifndef U05_ARBOL_ARBOL_NODOARBOL_H_
#define U05_ARBOL_ARBOL_NODOARBOL_H_

#include <string.h>
#include <iostream>
#include "../Pila/Pila.h"
#include "../structs.h"
using namespace std;

template <class T>
class NodoArbolContenedor
{
private:
  Pila<Contenedor<T>> *pila = new Pila<Contenedor<T>>;
  NodoArbolContenedor *left, *right;

public:
  NodoArbolContenedor()
  {
    left = nullptr;
    right = nullptr;
  }

  NodoArbolContenedor(Contenedor<T> data)
  {
    pila = new Pila<Contenedor<T>>();
    pila->push(data);
    left = nullptr;
    right = nullptr;
  }

  Pila<Contenedor<T>>* getPila() const
  {
    return pila;
  }

  void addData(Contenedor<T> data)
  {
    pila->push(data);
  }

  void setPila(Pila<Contenedor<T>> p)
  {
    this->pila = p;
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

   void print(bool esDerecho, string identacion) {
    if (right != NULL) {
        right->print(true, identacion + (esDerecho ? "     " : "|    "));
    }
    cout << identacion;
    if (esDerecho) {
        cout << " /";
    } else {
        cout << " \\";
    }
    cout << "-- ";
    pila->print();
    if (left != NULL) {
        left->print(false, identacion + (esDerecho ? "|    " : "     "));
    }
}

  };

#endif // U05_ARBOL_ARBOL_NODOARBOL_H_
