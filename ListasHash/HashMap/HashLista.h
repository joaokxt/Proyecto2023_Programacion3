#ifndef U05_HASH_HASHMAP_HASHMAP_H_
#define U05_HASH_HASHMAP_HASHMAP_H_
using namespace std;
#include "HashEntry.h"
#include <iostream>
#include "Lista.h"


template <class K, class T>
class HashMapL
{
private:
    Lista<HashEntry<K, T>> **tabla;

    unsigned int tamanio;

    static unsigned int hashFunc(K clave);

    unsigned int (*hashFuncP)(K clave);

public:
    explicit HashMapL(unsigned int k);

    HashMapL(unsigned int k, unsigned int (*hashFuncP)(K clave));

    T get(K clave);

    void putlista(K clave, T valor);

    void remove(K clave);

    ~HashMapL();

    bool esVacio();

    void print1();

    void print2(K clave);

    void print3();
};

template <class K, class T>
HashMapL<K, T>::HashMapL(unsigned int k)
{
    tamanio = k;
    tabla = new Lista<HashEntry<K, T>> *[tamanio];
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
    tabla = new Lista<HashEntry<K, T>> *[tamanio];
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
    if(tabla[pos]->getClave() == clave){
        return tabla[pos]->getValor();
    }else{
        throw 409;
    }
}



template<class K, class T>
void HashMapL<K,T>::putlista(K clave, T valor) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] == NULL)
    {
        //Manejar la Colision!!!!!!!
        tabla[pos] = new Lista<HashEntry<K, T>>();
    }

    tabla[pos]->insertarUltimo(HashEntry<K, T>(clave,valor)); //Corresponde a una fila en la tabla HASH
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
void HashMapL<K, T>::print1()
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

template <class K, class T>
void HashMapL<K, T>::print3()
{
    //unsigned int pos = hashFuncP(clave) % tamanio;
    Nodo<HashEntry<K, T>> *aux = tabla[0]->getInicio();
    std::cout << "i"
              << " "
              << "Clave"
              << "\t\t"
              << "Valor" << std::endl;
    std::cout << "--------------------" << std::endl;
    for (int i = 1; i < tamanio; i++)
    {
        std::cout << i << " ";

        while (aux != NULL) {
            cout<<aux->getDato().getClave()<<endl;
            cout<<aux->getDato().getValor()<<endl;
            aux = aux->getSiguiente();
        }

        std::cout << std::endl;
    }
}


template <class K, class T>
void HashMapL<K, T>::print2(K clave)
{
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL){
        throw 404;
    }
    Nodo<HashEntry<K, T>> *aux = tabla[pos]->getInicio();

    while (aux != NULL) {
        cout<<aux->getDato().getValor()<<endl;
        aux = aux->getSiguiente();
    }
}

#endif // U05_HASH_HASHMAP_HASHMAP_H_