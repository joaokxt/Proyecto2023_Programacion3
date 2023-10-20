#ifndef COLA_COLA_H_
#define COLA_COLA_H_
#include "Nodo.h"
#include <iostream>

/**
 * Clase que implementa una Cola generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T> class Cola {
private:
  Nodo<T> *frente;
public:
  Cola();
  ~Cola();
  void encolar(T dato);
  void encolarPrioridad(T dato, int prioridad);
  T desencolar();
  int getTamanio();
  bool esVacia();
  void print();
};

/**
 * Constructor de la clase Cola
 * @tparam T
 */
template <class T> Cola<T>::Cola(){
  frente = nullptr;
}

/**
 * Destructor de la clase Cola, se encarga de liberar la memoria de todos los
 * nodos utilizados en la Cola
 * @tparam T
 */
template <class T> Cola<T>::~Cola(){
  delete frente;
}

/**
 * Inserta un dato en la Cola
 * @tparam T
 * @param dato  dato a insertar
 */
template <class T> void Cola<T>::encolar(T dato){
  Nodo<T> *aux, *nuevo = new Nodo<T>();

  nuevo->setDato(dato);
  nuevo->setSiguiente(nullptr);
  nuevo->setPrioridad(1000);

  if(this->esVacia()){
    frente = nuevo;
  }else{
    aux = frente;
    while(aux->getSiguiente() != nullptr){ 
      aux = aux->getSiguiente();
    }
    aux->setSiguiente(nuevo);
  }
}

template <class T> void Cola<T>::encolarPrioridad(T dato, int prioridad){
  Nodo<T> *aux, *nuevo = new Nodo<T>();

  nuevo->setDato(dato);
  nuevo->setSiguiente(nullptr);
  nuevo->setPrioridad(prioridad);

  if(this->esVacia()){
    frente = nuevo;
  }else if(frente->getPrioridad()>nuevo->getPrioridad()){
    nuevo->setSiguiente(frente);
    frente = nuevo;
  }else{
    aux = frente;
    while(aux->getSiguiente() != nullptr && aux->getSiguiente()->getPrioridad()<=nuevo->getPrioridad()){ 
      aux = aux->getSiguiente();
    }
    nuevo->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(nuevo);
  }
}

/**
 * Obtener el dato de la Cola
 * @tparam T
 * @return dato almacenado en el nodo
 */
template <class T> T Cola<T>::desencolar(){
  Nodo<T>* aBorrar;
  T dato;

  if(this->esVacia()){
    throw 404;
  }

  aBorrar = frente;
  dato = aBorrar->getDato();
  frente = aBorrar->getSiguiente();

  delete aBorrar;
  return dato;
}

template <class T> int Cola<T>::getTamanio(){
  Nodo<T>* aux = new Nodo<T>();
  int tamanio = 0;

  if(esVacia()){
    return tamanio;
  }

  aux = frente;
  while(aux != nullptr){
    tamanio++;
    aux = aux->getSiguiente();
  }

  return tamanio;
}

/**
 * Responde si la Cola se encuentra Vacía
 * @tparam T
 * @return
 */
template <class T> bool Cola<T>::esVacia(){
  return frente == nullptr;
}

template <class T> void Cola<T>::print(){
  Nodo<T>* aux = frente;

  while(aux != nullptr){
    std::cout<<aux->getDato()<<"->";
    aux = aux->getSiguiente();
  }
  std::cout<<"FINAL"<<std::endl;
}

#endif // U04_COLAS_COLA_COLA_H_