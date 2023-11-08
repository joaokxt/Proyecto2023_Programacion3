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
  NodoCola<T> *frente;
public:
  Cola();
  ~Cola();
  void encolar(T dato);
  void encolarPrioridad(T dato, int prioridad);
  T desencolar();
  T peek();
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
  NodoCola<T> *aux, *nuevo = new NodoCola<T>();

  nuevo->setDato(dato);
  nuevo->setSiguiente(nullptr);

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

/**
 * Obtener el dato de la Cola
 * @tparam T
 * @return dato almacenado en el nodo
 */
template <class T> T Cola<T>::desencolar(){
  NodoCola<T>* aBorrar;
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

template <class T> T Cola<T>::peek(){
  return frente->getDato();
}

template <class T> int Cola<T>::getTamanio(){
  NodoCola<T>* aux = new NodoCola<T>();
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
  NodoCola<T>* aux = frente;

  while(aux != nullptr){
    std::cout<<aux->getDato()<<"->";
    aux = aux->getSiguiente();
  }
  std::cout<<"FINAL"<<std::endl;
}

#endif // U04_COLAS_COLA_COLA_H_