#ifndef NODO_H_
#define NODO_H_

template <class T>
class NodoPila{
    private:
        T dato;
        NodoPila<T>* siguiente;
    public:
        T getDato();
        void setDato(T dato);
        NodoPila<T>* getSiguiente();
        void setSiguiente(NodoPila<T>* s);
};

template <class T>
T NodoPila<T>::getDato(){
    return this->dato;
}

template <class T>
void NodoPila<T>::setDato(T dato){
    this->dato = dato;
}

template <class T>
NodoPila<T>* NodoPila<T>::getSiguiente(){
    return this->siguiente;
}

template <class T>
void NodoPila<T>::setSiguiente(NodoPila<T>* s){
    this->siguiente = s;
}


#endif