#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_

#include <iostream>
#include "NodoArbolContenedor.h"
#include "../Cola/Cola.h"
#include "../Lista/Lista.h"
#include "../structs.h"
using namespace std;

template <class T>
class ArbolBinarioContenedor
{
protected:
  NodoArbolContenedor<T> *root;

public:
  ArbolBinarioContenedor();

  ArbolBinarioContenedor(T data, Articulo *a);

  void put(T data, Articulo *a);

  void preorder();

  void inorder();

  void postorder();

  ~ArbolBinarioContenedor();

  bool esVacio();

  void print();

  void min();

  void max();

private:
  T search(T data, NodoArbolContenedor<T> *r);
  NodoArbolContenedor<T> *put(T data, Articulo *a, NodoArbolContenedor<T> *r);
  void preorder(NodoArbolContenedor<T> *r);
  void inorder(NodoArbolContenedor<T> *r);
  void postorder(NodoArbolContenedor<T> *r);
  void min(NodoArbolContenedor<T> *r);
  void max(NodoArbolContenedor<T> *r);
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T>
ArbolBinarioContenedor<T>::ArbolBinarioContenedor() { root = nullptr; }

template <class T>
ArbolBinarioContenedor<T>::ArbolBinarioContenedor(T data, Articulo *a) {
  Contenedor<T> contenedorAux;
  contenedorAux.info = data;
  contenedorAux.puntero = a;
  root = new NodoArbolContenedor<T>(contenedorAux); 
}

/**
 * Destructor del Arbol
 */
template <class T>
ArbolBinarioContenedor<T>::~ArbolBinarioContenedor() {}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template <class T>
void ArbolBinarioContenedor<T>::put(T data, Articulo *a) { 
  root = put(data, a, root); 
}

template <class T>
NodoArbolContenedor<T> *ArbolBinarioContenedor<T>::put(T data, Articulo *a, NodoArbolContenedor<T> *r)
{
  Contenedor<T> contenedorAux;

  if (r == nullptr)
  {
    contenedorAux.info = data;
    contenedorAux.puntero = a;

    return new NodoArbolContenedor<T>(contenedorAux);
  }

  if (r->getCola()->peek().info == data)
  {
    contenedorAux.info = data;
    contenedorAux.puntero = a;

    r->addData(contenedorAux);
  }
  else if (r->getCola()->peek().info > data)
  {
    r->setLeft(put(data, a, r->getLeft()));
  }
  else
  {
    r->setRight(put(data, a, r->getRight()));
  }

  return r;
}

/**
 * Informa si un árbol esta vacío
 * @return
 */
template <class T>
bool ArbolBinarioContenedor<T>::esVacio() { return root == nullptr; }

/**
 * Se obtienen los datos más chicos del árbol (lado izquierdo)
  * @return
  */
template <class T>
void ArbolBinarioContenedor<T>::min()
{
  Cola<Contenedor<T>> *colaAux = root->getCola();
  Contenedor<T> dato = colaAux->desencolar();
  while(!colaAux->esVacia()){
    Contenedor<T> dato = colaAux->desencolar();
    dato.puntero->printCodigo();
  }
  min(root);
}

template <class T>
void ArbolBinarioContenedor<T>::min(NodoArbolContenedor<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  Cola<Contenedor<T>> *colaAux = r->getCola();
  while(!colaAux->esVacia()){
    Contenedor<T> dato = colaAux->desencolar();
    dato.puntero->printCodigo();
  }

  min(r->getLeft());
  if(r != root)
    min(r->getRight());	
}
/**
 * Se obtienen los datos más grandes del árbol (lado derecho)
  * @return
  */
template <class T>
void ArbolBinarioContenedor<T>::max()
{
  Cola<Contenedor<T>> *colaAux = root->getCola();
  Contenedor<T> dato = colaAux->desencolar();
  while(!colaAux->esVacia()){
    Contenedor<T> dato = colaAux->desencolar();
    dato.puntero->printCodigo();
  }
  max(root);
}

template <class T>
void ArbolBinarioContenedor<T>::max(NodoArbolContenedor<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  Cola<Contenedor<T>> *colaAux = r->getCola();
  while(!colaAux->esVacia()){
    Contenedor<T> dato = colaAux->desencolar();
    dato.puntero->printCodigo();
  }

  max(r->getRight());
  if(r != root)
    max(r->getLeft());	
}


#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_