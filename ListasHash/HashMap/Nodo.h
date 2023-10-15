//
// Created by frant on 17/8/2023.
//

#ifndef INC_2021A2_U02_LISTAS_FRANTMATEOS_NODO_H
#define INC_2021A2_U02_LISTAS_FRANTMATEOS_NODO_H
#ifndef NODO_H
#define NODO_H

template<class T>
class Nodo{
private:
    T dato;
    Nodo<T> *siguiente;

public:

    Nodo(T d, Nodo<T> *s) : dato(d), siguiente(s) {}
    T getDato(){
        return dato;
    }

    void setDato(T d){
        dato = d;
    }

    Nodo<T> *getSiguiente(){
        return siguiente;
    }

    void setSiguiente(Nodo<T> *siguiente){
        this->siguiente = siguiente;
    }


};

#endif //NODO_H
#endif //INC_2021A2_U02_LISTAS_FRANTMATEOS_NODO_H
