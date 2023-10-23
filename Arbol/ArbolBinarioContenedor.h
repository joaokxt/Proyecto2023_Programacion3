#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_

#include <iostream>
#include "NodoArbolContenedor.h"
#include "../Cola/Cola.h"
using namespace std;

template <class T>
class ArbolBinarioContenedor
{
protected:
  NodoArbolContenedor<T> *root;

public:
  ArbolBinarioContenedor();

  void put(T data);

  T search(T data);

  void remove(T data);

  void preorder();

  void inorder();

  void postorder();

  ~ArbolBinarioContenedor();

  bool esVacio();

  void print();

  int contarPorNivel(int nivel);

  void espejo();

private:
  T search(T data, NodoArbol<T> *r);
  NodoArbolContenedor<T> *put(T data, NodoArbolContenedor<T> *r);
  NodoArbolContenedor<T> *remove(T data, NodoArbolContenedor<T> *r);
  NodoArbolContenedor<T> *findMaxAndRemove(NodoArbolContenedor<T> *r, bool *found);
  void preorder(NodoArbolContenedor<T> *r);
  void inorder(NodoArbolContenedor<T> *r);
  void postorder(NodoArbolContenedor<T> *r);
  void espejoProceso(NodoArbolContenedor<T> *r);
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T>
ArbolBinarioContenedor<T>::ArbolBinarioContenedor() { root = nullptr; }

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
T ArbolBinarioContenedor<T>::search(T data, NodoArbol<T> *r)
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
template <class T>
void ArbolBinarioContenedor<T>::put(T data) { root = put(data, root); }

template <class T>
NodoArbol<T> *ArbolBinarioContenedor<T>::put(T data, NodoArbol<T> *r)
{
  //para cada nodo su padre es la raíz.
  if (r == nullptr)
  {
    return new NodoArbol<T>(data);
  }

  if (r->getData() == data)
  {
    throw 200;
  }

  if (r->getData() > data)
  {
    r->setLeft(put(data, r->getLeft()));
  }
  else
  {
    r->setRight(put(data, r->getRight()));
  }

  return r;
}

/**
 * Elimina un dato del árbol
 * @param clave Clave para identificar el nodo a borrar
 */
template <class T>
void ArbolBinario<T>::remove(T data)
{
  root = remove(data, root);
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::remove(T data, NodoArbol<T> *r)
{
  NodoArbol<T> *aux;

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

template <class T>
NodoArbol<T> *ArbolBinario<T>::findMaxAndRemove(NodoArbol<T> *r, bool *found)
{
  NodoArbol<T> ret;
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
template <class T>
bool ArbolBinario<T>::esVacio() { return root == nullptr; }

/**
 * Recorre un árbol en preorden
 */
template <class T>
void ArbolBinario<T>::preorder()
{
  preorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::preorder(NodoArbol<T> *r)
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
template <class T>
void ArbolBinario<T>::inorder()
{
  inorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::inorder(NodoArbol<T> *r)
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
template <class T>
void ArbolBinario<T>::postorder()
{
  postorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::postorder(NodoArbol<T> *r)
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
template <class T>
void ArbolBinario<T>::print()
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