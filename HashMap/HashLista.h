#ifndef HASHMAP_HASHLISTA_H_
#define HASHMAP_HASHLISTA_H_

#include <iostream>
#include "../Lista/Lista.h"
#include "HashEntry.h"
using namespace std;

template <class K, class T>
class HashMapL
{
private:
  HashEntry<K, Lista<T>*> **tabla;

  unsigned int tamanio;

  static unsigned int hashFunc(K clave);

  unsigned int (*hashFuncP)(K clave);

public:
  explicit HashMapL(unsigned int k);

  HashMapL(unsigned int k, unsigned int (*hashFuncP)(K clave));

  T get(K clave);

  void put(K clave, T valor);

  void remove(K clave);

  ~HashMapL();

  bool esVacio();

  void print();
};

template <class K, class T>
HashMapL<K, T>::HashMapL(unsigned int k)
{
  tamanio = k;
  tabla = new HashEntry<K, Lista<T>*> *[tamanio];
  for (int i = 0; i < tamanio; i++)
  {
    tabla[i] = NULL;
  }
  hashFuncP = hashFunc;
}

template <class K, class T>
HashMapL<K, T>::HashMapL(unsigned int k, unsigned int (*fp)(K))
{
  tamanio = k;
  tabla = new HashEntry<K, Lista<T>*> *[tamanio];
  for (int i = 0; i < tamanio; i++)
  {
    tabla[i] = NULL;
  }
  hashFuncP = fp;
}

template <class K, class T>
HashMapL<K, T>::~HashMapL()
{
  for (int i = 0; i < tamanio; i++)
  {
    if (tabla[i] != NULL)
    {
      delete tabla[i];
    }
  }
}

template <class K, class T>
T HashMapL<K, T>::get(K clave)
{
  unsigned int pos = hashFuncP(clave) % tamanio;
  if (tabla[pos] == NULL)
  {
    throw 404;
  }
  for(int i=0; i<tabla[pos]->getValor()->getTamanio(); i++){
    T entrada = tabla[pos]->geValor()->getDato(i);
    if(entrada->getClave() == clave)
      return entrada->getValor();
  }
}

template <class K, class T>
void HashMapL<K, T>::put(K clave, T valor)
{
  unsigned int pos = hashFuncP(clave) % tamanio;

  if (tabla[pos] == NULL)
  {
    tabla[pos] = new HashEntry<K, Lista<T>*>(clave, new Lista<T>(valor));
  }else{
    tabla[pos]->getValor()->insertarUltimo(valor);
  }

  return;
}

template <class K, class T>
void HashMapL<K, T>::remove(K clave) {}

template <class K, class T>
bool HashMapL<K, T>::esVacio()
{
  for (int i = 0; i < tamanio; i++)
  {
    if (tabla[i] != NULL)
    {
      return false;
    }
  }
  return true;
}

template <class K, class T>
unsigned int HashMapL<K, T>::hashFunc(K clave)
{
  return (unsigned int)clave;
}

template <class K, class T>
void HashMapL<K, T>::print()
{

  std::cout << "i"
            << " "
            << "Clave"
            << "\t\t"
            << "Valor" << std::endl;
  std::cout << "--------------------" << std::endl;
  for (int i = 0; i < tamanio; i++)
  {
    std::cout << i << " ";
    if (tabla[i] != NULL)
    {
      std::cout << tabla[i]->getClave() << "\t\t";
      std::cout << tabla[i]->getValor();
    }
    std::cout << std::endl;
  }
}

#endif // U05_HASH_HASHMAP_HASHMAP_H_