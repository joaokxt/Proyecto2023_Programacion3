#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_

#include <iostream>
#include "NodoArbolContenedor.h"
#include "../Pila/Pila.h"
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

  ArbolBinarioContenedor(T data, string codigo);

  void put(T data, string codigo);

  T search(T data);

  void remove(T data);

  void preorder();

  void inorder();

  void postorder();

  ~ArbolBinarioContenedor();

  bool esVacio();

  void print();

  Lista<Contenedor<T>>* min();

private:
  T search(T data, NodoArbolContenedor<T> *r);
  NodoArbolContenedor<T> *put(T data, string codigo, NodoArbolContenedor<T> *r);
  void preorder(NodoArbolContenedor<T> *r);
  void inorder(NodoArbolContenedor<T> *r);
  void postorder(NodoArbolContenedor<T> *r);
  void min(NodoArbolContenedor<T> *r, Lista<Contenedor<T>> *li);
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T>
ArbolBinarioContenedor<T>::ArbolBinarioContenedor() { root = nullptr; }

template <class T>
ArbolBinarioContenedor<T>::ArbolBinarioContenedor(T data, string codigo) {
  Contenedor<T> contenedorAux;
  contenedorAux.info = data;
  contenedorAux.codigo = codigo;
  root = new NodoArbolContenedor<T>(contenedorAux); 
}

/**
 * Destructor del Arbol
 */
template <class T>
ArbolBinarioContenedor<T>::~ArbolBinarioContenedor() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T>
T ArbolBinarioContenedor<T>::search(T data)
{
  return search(data, root);
}

template <class T>
T ArbolBinarioContenedor<T>::search(T data, NodoArbolContenedor<T> *r)
{
  if (r == nullptr)
  {
    throw 404;
  }

  if (r->getData()->peek().info == data)
  {
    return r->getData();
  }

  if (r->getData()->peek().info > data)
  {
    return search(data, r->getLeft());
  }
  else
  {
    return search(data, r->getRight());
  }
}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template <class T>
void ArbolBinarioContenedor<T>::put(T data, string codigo) { 
  root = put(data, codigo, root); 
}

template <class T>
NodoArbolContenedor<T> *ArbolBinarioContenedor<T>::put(T data, string codigo, NodoArbolContenedor<T> *r)
{
  Contenedor<T> contenedorAux;

  if (r == nullptr)
  {
    contenedorAux.info = data;
    contenedorAux.codigo = codigo;

    return new NodoArbolContenedor<T>(contenedorAux);
  }

  if (r->getPila()->peek().info == data)
  {
    contenedorAux.info = data;
    contenedorAux.codigo = codigo;

    r->addData(contenedorAux);
  }

  if (r->getPila()->peek().info > data)
  {
    r->setLeft(put(data, codigo, r->getLeft()));
  }
  else
  {
    r->setRight(put(data, codigo, r->getRight()));
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
Lista<Contenedor<T>>* ArbolBinarioContenedor<T>::min()
{
  Lista<Contenedor<T>> *listaContenedores = new Lista<Contenedor<T>>();
  Pila<Contenedor<T>> *pilaAux = root->getPila();
  while(!pilaAux->esVacia()){
    Contenedor<T> dato = pilaAux->pop();
    cout<<dato.codigo<<endl;
    listaContenedores->insertarUltimo(dato);
  }
  min(root, listaContenedores);
  return listaContenedores;
}

template <class T>
void ArbolBinarioContenedor<T>::min(NodoArbolContenedor<T> *r, Lista<Contenedor<T>> *li)
{
  Pila<Contenedor<T>> *pilaAux = r->getPila();
  if (r == nullptr)
  {
    cout<<"final"<<endl;
    return;
  }
  
  while(!pilaAux->esVacia()){
    Contenedor<T> dato = pilaAux->pop();
    cout<<dato.codigo<<endl;
    li->insertarUltimo(dato);
  }
  
  cout<<"hola"<<endl;
  min(r->getLeft(), li);
  if(r != root)
    min(r->getRight(), li);	
}


#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_