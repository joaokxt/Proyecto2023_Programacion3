#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_
<<<<<<< HEAD
=======

>>>>>>> 800261a0708e16f14002fca66c400cc15284f64c
#include <iostream>
#include "NodoArbol.h"
#include "../Cola/Cola.h"
using namespace std;

template <class T, class N>
class ArbolBinario
{
protected:
  NodoArbol<T,N> *root;

public:
   ArbolBinario();

  void put(T data,N valor);

  T search(T data);

  void remove(T data);

  void preorder();

  void inorder();

  void postorder();

  ~ArbolBinario();

  bool esVacio();

  void print();

  int contarPorNivel(int nivel);

  void espejo();

private:
<<<<<<< HEAD
  T search(T data, NodoArbol<T,N> *r);
  NodoArbol<T,N> *put(T data, N& valor,NodoArbol<T,N> *r);
  NodoArbol<T,N> *remove(T data, NodoArbol<T,N> *r);
  NodoArbol<T,N> *findMaxAndRemove(NodoArbol<T,N> *r, bool *found);
  void preorder(NodoArbol<T,N> *r);
  void inorder(NodoArbol<T,N> *r);
  void postorder(NodoArbol<T,N> *r);
=======
  T search(T data, NodoArbol<T> *r);
  NodoArbol<T> *put(T data, NodoArbol<T> *r);
  NodoArbol<T> *remove(T data, NodoArbol<T> *r);
  NodoArbol<T> *findMaxAndRemove(NodoArbol<T> *r, bool *found);
  void preorder(NodoArbol<T> *r);
  void inorder(NodoArbol<T> *r);
  void postorder(NodoArbol<T> *r);
  void espejoProceso(NodoArbol<T> *r);
>>>>>>> 800261a0708e16f14002fca66c400cc15284f64c
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T,class N>
ArbolBinario<T,N>::ArbolBinario() { root = nullptr; }

/**
 * Destructor del Arbol
 */
template <class T,class N>
ArbolBinario<T,N>::~ArbolBinario() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T,class N>
T ArbolBinario<T,N>::search(T data)
{
  return search(data, root);
}

template <class T,class N>
T ArbolBinario<T,N>::search(T data, NodoArbol<T,N> *r)
{
  if (r == nullptr)
  {
    throw 404;
  }

  if (r->getData() == data)
  {
    return r->getData();
  }

  if (r->getData() > data)
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
template <class T,class N>
void ArbolBinario<T,N>::put(T data,N valor) { root = put(data,valor, root); }

template <class T,class N>
NodoArbol<T,N> *ArbolBinario<T,N>::put(T data,N& valor, NodoArbol<T,N> *r)
{
<<<<<<< HEAD
    //Contenedor<T> *contenedorAux;
=======
  //para cada nodo su padre es la raíz.
>>>>>>> 800261a0708e16f14002fca66c400cc15284f64c
  if (r == nullptr)
  {
    return new NodoArbol<T,N>(data , valor);
  }

  if (r->getData() == data)
  {
    //throw 200;


  }

  if (r->getData() > data)
  {
    r->setLeft(put(data,valor, r->getLeft()));
  }
  else
  {
    r->setRight(put(data,valor, r->getRight()));
  }

  return r;
}

/**
 * Elimina un dato del árbol
 * @param clave Clave para identificar el nodo a borrar
 */
template <class T,class N>
void ArbolBinario<T,N>::remove(T data)
{
  root = remove(data, root);
}

template <class T,class N>
NodoArbol<T,N> *ArbolBinario<T,N>::remove(T data, NodoArbol<T,N> *r)
{
  NodoArbol<T,N> *aux;

  if (r == nullptr)
  {
    throw 404;
  }

  if (r->getData() == data)
  {

    if (r->getLeft() == nullptr && r->getRight() == nullptr)
    {
      delete r;
      return nullptr;
    }
    else if (r->getLeft() != nullptr && r->getRight() == nullptr)
    {
      aux = r->getLeft();
      delete r;
      return aux;
    }
    else if (r->getLeft() == nullptr && r->getRight() != nullptr)
    {
      aux = r->getRight();
      delete r;
      return aux;
    }
    else if (r->getLeft() != nullptr && r->getRight() != nullptr)
    {

      if (r->getLeft()->getRight() != nullptr)
      {
        // Aca tenemos que buscar el valor maximo
        bool found;
        aux = findMaxAndRemove(r->getLeft(), &found);
        aux->setRight(r->getRight());
        aux->setLeft(r->getLeft());
      }
      else
      {
        aux = r->getLeft();
        r->getLeft()->setRight(r->getRight());
      }
      delete r;
      return aux;
    }
  }
  else if (r->getData() > data)
  {
    r->setLeft(remove(data, r->getLeft()));
  }
  else
  {
    r->setRight(remove(data, r->getRight()));
  }

  return r;
}

template <class T,class N>
NodoArbol<T,N> *ArbolBinario<T,N>::findMaxAndRemove(NodoArbol<T,N> *r, bool *found)
{
  NodoArbol<T,N> ret;
  *found = false;

  if (r->getRight() == nullptr)
  {
    *found = true;
    return r;
  }

  ret = findMaxAndRemove(r->getRight(), found);
  if (*found)
  {
    r->setRight(nullptr);
    *found = false;
  }

  return ret;
}

/**
 * Informa si un árbol esta vacío
 * @return
 */
template <class T,class N>
bool ArbolBinario<T,N>::esVacio() { return root == nullptr; }

/**
 * Recorre un árbol en preorden
 */
template <class T,class N>
void ArbolBinario<T,N>::preorder()
{
  preorder(root);
  std::cout << std::endl;
}

template <class T,class N>
void ArbolBinario<T,N>::preorder(NodoArbol<T,N> *r)
{
  if (r == nullptr)
  {
    return;
  }

  std::cout << r->getData() << " ";
  preorder(r->getLeft());
  preorder(r->getRight());
}

/**
 * Recorre un árbol en orden
 */
template <class T,class N>
void ArbolBinario<T,N>::inorder()
{
  inorder(root);
  std::cout << std::endl;
}

template <class T,class N>
void ArbolBinario<T,N>::inorder(NodoArbol<T,N> *r)
{
  if (r == nullptr)
  {
    return;
  }

  inorder(r->getLeft());
  std::cout << r->getData() << " ";
  inorder(r->getRight());
}

/**
 * Recorre un árbol en postorden
 */
template <class T,class N>
void ArbolBinario<T,N>::postorder()
{
  postorder(root);
  std::cout << std::endl;
}

template <class T,class N>
void ArbolBinario<T,N>::postorder(NodoArbol<T,N> *r)
{
  if (r == nullptr)
  {
    return;
  }

  postorder(r->getLeft());
  postorder(r->getRight());
  std::cout << r->getData() << " ";
}

/**
 * Muestra un árbol por consola
 */
template <class T,class N>
void ArbolBinario<T,N>::print()
{
  if (root != NULL)
    root->print(false, "");
}

template <class T>
int ArbolBinario<T>::contarPorNivel(int nivel){
  NodoArbol<T>* aux = root;
  Cola<NodoArbol<T>*> colaNodos;
  Cola<int> colaNiveles;
  int nivelActual = 1, cantNodos = 0;

  colaNodos.encolar(aux);
  colaNiveles.encolar(nivelActual);

  while(nivelActual <= nivel){
    aux = colaNodos.desencolar();
    nivelActual = colaNiveles.desencolar();

    if(nivelActual == nivel){
      cantNodos++;
    }
    if(aux->getLeft() != nullptr){
      colaNodos.encolar(aux->getLeft());
      colaNiveles.encolar(nivelActual+1);
    }
    if(aux->getRight() != nullptr){
      colaNodos.encolar(aux->getRight());
      colaNiveles.encolar(nivelActual+1);
    }
  }

  return cantNodos;
}

template <class T>
void ArbolBinario<T>::espejo(){
  NodoArbol<T> *aux;

  espejoProceso(root->getLeft());
  espejoProceso(root->getRight());

  aux = root->getLeft();
  root->setLeft(root->getRight());
  root->setRight(aux);

  return;
}

template <class T>
void ArbolBinario<T>::espejoProceso(NodoArbol<T> *r){
  NodoArbol<T> *aux;

  if(r == nullptr){
    return;
  }

  aux = r->getLeft();
  r->setLeft(r->getRight());
  r->setRight(aux);

  espejoProceso(r->getLeft());
  espejoProceso(r->getRight());

}

#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_