#ifndef NODO_H_
#define NODO_H_

template <class T>
class Nodo{
    private:
        T dato;
        Nodo<T>* siguiente;
        int prioridad;
    public:
        T getDato();
        void setDato(T dato);
        Nodo<T>* getSiguiente();
        void setSiguiente(Nodo<T>* s);
        int getPrioridad();
        void setPrioridad(int p);
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

template <class T>
int Nodo<T>::getPrioridad(){
    return prioridad;
}

template <class T>
void Nodo<T>::setPrioridad(int p){
    this->prioridad = p;
}


#endif