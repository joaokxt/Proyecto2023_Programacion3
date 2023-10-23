#ifndef U03_PILAS_PILA_PILA_H_
#define U03_PILAS_PILA_PILA_H_
#include <iostream>
#include "nodo.h"
/**
 * Clase que implementa una Pila generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T> class Pila {
private:
  NodoPila<T>* tope;
public:
  Pila();
  ~Pila();
  void push(T dato);
  T pop();
  T peek();
  bool esVacia();
  int getTamanio();
  void print();
};

/**
 * Constructor de la clase Pila
 * @tparam T
 */
template <class T> Pila<T>::Pila(){
  	tope = nullptr;
}

/**
 * Destructor de la clase Lista, se encarga de liberar la memoria de todos los
 * nodos utilizados en la lista
 * @tparam T
 */
template <class T> Pila<T>::~Pila(){
  while(!this->esVacia()){
    pop();
  }
  delete tope;
}

/**
 * Inserta un dato en la pila
 * @tparam T
 * @param dato  dato a insertar
 */
template <class T> void Pila<T>::push(T dato){
  NodoPila<T>* nuevo;
  nuevo = new NodoPila<T>;
  nuevo->setDato(dato);
  nuevo->setSiguiente(tope);
  tope = nuevo;
}

/**
 * Obtener el dato de la pila
 * @tparam T
 * @return dato almacenado en el nodo
 */
template <class T> T Pila<T>::pop(){
  if(this->esVacia()){
    throw 404;
  }

  T dato = tope->getDato();
  NodoPila<T>* aBorrar = tope;
  tope = tope->getSiguiente();

  delete aBorrar;
  return dato;
}

template <class T> T Pila<T>::peek(){
  return tope->getDato();
}

/**
 * Responde si la pila se encuentra Vacía
 * @tparam T
 * @return
 */
template <class T> bool Pila<T>::esVacia(){
  return tope == nullptr;
}

template <class T> int Pila<T>::getTamanio(){
  NodoPila<T>* aux = tope;
  int tamanio = 0;

  if(this->esVacia())
    return 0;
  
  while(aux != nullptr){
    tamanio++;
    aux = aux->getSiguiente();
  }
  
  return tamanio;
}

template <class T> void Pila<T>::print(){
  NodoPila<T>* aux = tope;
  while(aux != nullptr){
    std::cout<<aux->getDato()<<"|";
    aux = aux->getSiguiente();
  }
  std::cout<<"|"<<std::endl;
  return;
}

#endif // U03_PILAS_PILA_PILA_H_
