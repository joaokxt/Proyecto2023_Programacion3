#ifndef COLA_NODO_H
#define COLA_NODO_H

template <class T>
class NodoCola{
    private:
        T dato;
        NodoCola<T>* siguiente;
        int prioridad;
    public:
        T getDato();
        void setDato(T dato);
        NodoCola<T>* getSiguiente();
        void setSiguiente(NodoCola<T>* s);
};

template <class T>
T NodoCola<T>::getDato(){
    return this->dato;
}

template <class T>
void NodoCola<T>::setDato(T dato){
    this->dato = dato;
}

template <class T>
NodoCola<T>* NodoCola<T>::getSiguiente(){
    return this->siguiente;
}

template <class T>
void NodoCola<T>::setSiguiente(NodoCola<T>* s){
    this->siguiente = s;
}



#endif