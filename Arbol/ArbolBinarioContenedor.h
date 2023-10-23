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

  void put(T data, string codigo);

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
  T search(T data, NodoArbolContenedor<T> *r);
  NodoArbolContenedor<T> *put(T data, string codigo, NodoArbolContenedor<T> *r);
  void preorder(NodoArbolContenedor<T> *r);
  void inorder(NodoArbolContenedor<T> *r);
  void postorder(NodoArbolContenedor<T> *r);
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
  root = put(data, string, root); 
}

template <class T>
NodoArbolContenedor<T> *ArbolBinarioContenedor<T>::put(T data, string codigo, NodoArbolContenedor<T> *r)
{
  Contenedor<T> *contenedorAux;

  if (r == nullptr)
  {
    contenedorAux = new Contenedor<T>;
    contenedorAux.info = data;
    contenedorAux.codigo = codigo;

    return new NodoArbolContenedor<T>(contenedorAux);
  }

  if (r->getPila()->peek().info == data.info)
  {
    contenedorAux = new Contenedor<T>;
    contenedorAux.info = data;
    contenedorAux.codigo = codigo;

    r->addData(contenedorAux);
  }

  if (r->getData()->peek().info > data.info)
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

/**
 * Recorre un árbol en preorden
 */
template <class T>
void ArbolBinarioContenedor<T>::preorder()
{
  preorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinarioContenedor<T>::preorder(NodoArbolContenedor<T> *r)
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
void ArbolBinarioContenedor<T>::inorder()
{
  inorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinarioContenedor<T>::inorder(NodoArbolContenedor<T> *r)
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
void ArbolBinarioContenedor<T>::postorder()
{
  postorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinarioContenedor<T>::postorder(NodoArbolContenedor<T> *r)
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
void ArbolBinarioContenedor<T>::print()
{
  if (root != NULL)
    root->print(false, "");
}

#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_