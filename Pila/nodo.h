#ifndef U03_PILAS_PILA_NODO_H_
#define U03_PILAS_PILA_NODO_H_

template <class T>
class Nodo{
    private:
        T dato;
        Nodo<T>* siguiente;
    public:
        T getDato();
        void setDato(T dato);
        Nodo<T>* getSiguiente();
        void setSiguiente(Nodo<T>* s);
};

template <class T>
T Nodo<T>::getDato(){
    return this->dato;
}

template <class T>
void Nodo<T>::setDato(T dato){
    this->dato = dato;
}

template <class T>
Nodo<T>* Nodo<T>::getSiguiente(){
    return this->siguiente;
}

template <class T>
void Nodo<T>::setSiguiente(Nodo<T>* s){
    this->siguiente = s;
}


#endif