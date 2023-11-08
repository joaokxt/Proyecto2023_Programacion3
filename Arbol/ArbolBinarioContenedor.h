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

  Cola<Contenedor<T>> min();

  Lista<Contenedor<T>> max();

private:
  T search(T data, NodoArbolContenedor<T> *r);
  NodoArbolContenedor<T> *put(T data, Articulo *a, NodoArbolContenedor<T> *r);
  void preorder(NodoArbolContenedor<T> *r);
  void inorder(NodoArbolContenedor<T> *r);
  void postorder(NodoArbolContenedor<T> *r);
  void min(NodoArbolContenedor<T> *r, Cola<Contenedor<T>> &co);
  void max(NodoArbolContenedor<T> *r, Lista<Contenedor<T>> &li);
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

  if (r->getCola()->peek().info > data)
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

template <class T>
Cola<Contenedor<T>> ArbolBinarioContenedor<T>::min()
{
  Cola<Contenedor<T>> colaContenedores;
  Cola<Contenedor<T>> *colaAux = root->getCola();
  Contenedor<T> dato = colaAux->desencolar();
  while(!colaAux->esVacia()){
    Contenedor<T> dato = colaAux->desencolar();
    dato.puntero->printCodigo();
  }
  min(root, colaContenedores);
  return colaContenedores;
}

template <class T>
void ArbolBinarioContenedor<T>::min(NodoArbolContenedor<T> *r, Cola<Contenedor<T>> &co)
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

  min(r->getLeft(), co);
  if(r != root)
    min(r->getRight(), co);	
}

template <class T>
Lista<Contenedor<T>> ArbolBinarioContenedor<T>::max()
{
  Lista<Contenedor<T>> listaContenedores;
  Cola<Contenedor<T>> *colaAux = root->getCola();
  while(!colaAux->esVacia()){
    Contenedor<T> dato = colaAux->desencolar();
    listaContenedores.insertarUltimo(dato);
  }
  max(root, listaContenedores);
  return listaContenedores;
}

template <class T>
void ArbolBinarioContenedor<T>::max(NodoArbolContenedor<T> *r, Lista<Contenedor<T>> &li)
{
  if (r == nullptr)
  {
    return;
  }

  Cola<Contenedor<T>> *colaAux = r->getCola();
  while(!colaAux->esVacia()){
    Contenedor<T> dato = colaAux->desencolar();
    li.insertarUltimo(dato);
  }

  max(r->getRight(), li);
  if(r != root)
    max(r->getLeft(), li);	
}


#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_