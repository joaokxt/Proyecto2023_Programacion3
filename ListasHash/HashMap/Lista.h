#ifndef U02_LISTAS_LISTA_LISTA_H_
#define U02_LISTAS_LISTA_LISTA_H_
#include "Nodo.h"
/**
 * Clase que implementa una Lista Enlasada generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T> class Lista {
private:
    Nodo<T> *inicio;
public:
    Lista();

    Lista(const Lista<T> &li);

    ~Lista();

    bool esVacia() const ;

    int getTamanio();

    void insertar(int pos, T dato);

    void insertarPrimero(T dato);

    void insertarUltimo(T dato);

    void remover(int pos);

    T getDato(int pos);

    void reemplazar(int pos, T dato);

    void vaciar();
    void Invierte();

    void unir(const Lista<T> &li );

    void insertarAfter(T oldValue, T n, T newValue);

    Nodo<T> *getInicio();
};

/**
 * Constructor de la clase Lista
 * @tparam T
 */
template <class T> Lista<T>::Lista() {
    inicio = nullptr;
}


template<class T> Nodo<T> *Lista<T>::getInicio() {
    return inicio;
}

/**
 * Constructor por copia de la clase Lista
 * @tparam T
 * @param li
 */
template <class T> Lista<T>::Lista(const Lista<T> &li) {}

/**
 * Destructor de la clase Lista, se encarga de liberar la memoria de todos los
 * nodos utilizados en la lista
 * @tparam T
 */
template <class T> Lista<T>::~Lista() {}

/**
 * Metodo para saber si la lista esta vacia
 * @tparam T
 * @return true si la lista esta vacia, sino false
 */
template <class T> bool Lista<T>::esVacia() const{
    if(inicio == nullptr){
        return true;
    }else{
        return false;
    }
}

/**
 * Metodo para obtener la cantidad de nodos de la lista
 * @tparam T
 * @return la cantidad de nodos de la lista
 */
template <class T> int Lista<T>::getTamanio() {
    int tamanio = 0;
    Nodo<T> *acumulador = inicio;
    while(acumulador != nullptr){
        tamanio++;
        acumulador = acumulador->getSiguiente();
    }
    return tamanio;
}

/**
 * Inserta un nodo con el dato en la posicion pos
 * @tparam T
 * @param pos lugar donde será insertado el dato
 * @param dato  dato a insertar
 */
template <class T> void Lista<T>::insertar(int pos, T dato) {

    int actual = 0;
    Nodo<T> *x = inicio;
    Nodo<T> *nodo;

    nodo = new Nodo<T>;
    nodo->setDato(dato);



    if(pos == 0){
        nodo->setSiguiente(inicio);
        inicio = nodo;
        return;
    }
    while(x != nullptr && actual < pos-1){
        x = x->getSiguiente();
        actual++;
    }
    if(x == nullptr){
        throw 404;
    }

    nodo->setSiguiente(x->getSiguiente());
    x->setSiguiente(nodo);
}

/**
 * Inserta un nodo con el dato en la primera posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T> void Lista<T>::insertarPrimero(T dato) {
    Nodo<T> *nodo;
    nodo = new Nodo<T>;
    nodo->setDato(dato);

    nodo->setSiguiente(inicio);
    inicio = nodo;
}

/**
 * Inserta un nodo con el dato en la ultima posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T> void Lista<T>::insertarUltimo(T dato) {
    Nodo<T> *aux = inicio, *nuevo;
    nuevo = new Nodo<T>(dato, inicio);
    nuevo->setDato(dato);

    if (aux == nullptr) {
        nuevo->setSiguiente(inicio);
        inicio = nuevo;
        return;
    }

    while (aux->getSiguiente() != nullptr) {
        aux = aux->getSiguiente();
    }

    nuevo->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(nuevo);
}
/**
 * Elimina el nodo en la posicion 'pos' de la lista enlasada
 * @tparam T
 * @param pos posicion del nodo a eliminar
 */
template <class T> void Lista<T>::remover(int pos) {

    int actual = 0;
    Nodo<T> *x = inicio;
    Nodo<T> *nodo;

    if(pos == 0){
        nodo->setSiguiente(inicio);
        inicio = nodo;
        return;
    }
    while(x != nullptr && actual < pos-1){
        x = x->getSiguiente();
        actual++;
    }
    if(x == nullptr){
        throw 404;
    }

    nodo = x->getSiguiente();
    x->setSiguiente(nodo->getSiguiente());
    delete nodo;
}

/**
 * Obtener el dato del nodo en la posicion pos
 * @tparam T
 * @param pos posicion del dato
 * @return dato almacenado en el nodo
 */
template <class T> T Lista<T>::getDato(int pos) {
    int actual = 0;
    Nodo<T> *aux = inicio;

    if ( esVacia() ) {
        throw 404;
    }

    while ( aux != nullptr && actual < pos ) {
        aux = aux->getSiguiente();
        actual++;
    }

    if (aux == nullptr) throw 404;

    return aux->getDato();
}

/**
 * Reemplaza el dato almacenado en un nodo por este otro
 * @tparam T
 * @param pos posicion donde se desea reemplazar
 * @param dato nuevo dato a almacenar
 */
template <class T> void Lista<T>::reemplazar(int pos, T dato) {}

/**
 * Función que vacia la lista enlazada
 * @tparam T
 */
template <class T> void Lista<T>::vaciar() {}


template <class T> void Lista<T>::Invierte() {
    Nodo<T> *nodoactual = inicio;
    Nodo<T> *aux = inicio->getSiguiente();
    Nodo<T> *sig = nullptr;

    nodoactual->setSiguiente(nullptr);
    while(sig != nullptr){
        aux = nodoactual;
        nodoactual = sig;
        sig = nodoactual->getSiguiente();
        nodoactual->setSiguiente(aux);
    }
    inicio = nodoactual;

}

template<class T> void Lista<T>::unir(const Lista<T> &li) {
    Nodo<T> *nodo = inicio;
    while (nodo->getSiguiente()){
        nodo = nodo->getSiguiente();
    }
    nodo->setSiguiente(li.inicio);
    li.inicio == nullptr;
}


template<class T> void Lista<T>:: insertarAfter(T oldValue, T n, T newValue){
    Nodo<T> *aux = inicio;

    int ocurrencia = 0,posicion;

    while (ocurrencia < n){
        if(aux == nullptr){
            throw 404;
        }
        if(aux->getDato() == oldValue){
            posicion++;
        }
        aux = aux->getSiguiente();
        ocurrencia++;
    }

    insertar(posicion, newValue);

}



#endif // U02_LISTAS_LISTA_LISTA_H_
