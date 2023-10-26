#ifndef U05_ARBOL_ARBOL_NODOARBOL_H_
#define U05_ARBOL_ARBOL_NODOARBOL_H_
#include <iostream>
#include <string.h>
<<<<<<< HEAD
#include "../Pila/Pila.h"
=======
#include <iostream>
>>>>>>> 800261a0708e16f14002fca66c400cc15284f64c
using namespace std;

template <class T, class N>
class NodoArbol
{
private:

    Pila<T> *pila;
  T data;
  N valor;
  NodoArbol *left, *right;

public:
  NodoArbol()
  {
    left = nullptr;
    right = nullptr;
  }

  NodoArbol(T d, N v)
  {
    data = d;
    valor = v;
    left = nullptr;
    right = nullptr;
  }

  T getData() const
  {
    return data;
  }

  void setData(T d)
  {
    this->data = d;
  }

  NodoArbol *getRight() const
  {
    return right;
  }

  void setRight(NodoArbol *r)
  {
    this->right = r;
  }
  NodoArbol *getLeft() const
  {
    return left;
  }

  void setLeft(NodoArbol *l)
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
    cout << valor << endl;
    if (left != NULL) {
        left->print(false, identacion + (esDerecho ? "|    " : "     "));
    }
}

  };

#endif // U05_ARBOL_ARBOL_NODOARBOL_H_
