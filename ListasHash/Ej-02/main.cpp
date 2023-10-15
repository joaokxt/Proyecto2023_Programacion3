#include <iostream>
#include "../HashMap/HashLista.h"

using namespace std;


unsigned int funcion(string clave){
    unsigned int num=0;
    for(int i =0;i<3;i++){
        num += clave[i];
    }
    cout<<"Clave de "<<clave<<":  "<<num<<". "<<endl;
    return num;
}

class fabrica{
public:
    string nombre;
    string color;
    int cantidad;

   friend ostream &operator<<(ostream &os, const fabrica &fabrica) {
        os << "-> Nombre: " << fabrica.nombre << ". Color: " << fabrica.color << ". Cantidad: " << fabrica.cantidad;
        return os;
    }

};



int main() {
    std::cout << "Ejercicio 05/01\n" << std::endl;

    HashMapL<string ,fabrica> Hash(15,&funcion);


    fabrica producto1 = {"Martillo", "Amarillo",23};
    fabrica producto2 = {"Tornillo", "Gris", 545};
    fabrica producto3 = {"Destornillador", "Rojo", 3};
    fabrica producto4 = {"Cinta aislante", "Negro", 102};
    fabrica producto5 = {"Tornillo", "azul", 2};

    Hash.putlista(producto1.nombre,producto1);
    Hash.putlista(producto2.nombre,producto2);
    Hash.putlista(producto3.nombre,producto3);
    Hash.putlista(producto4.nombre,producto4);
    Hash.putlista(producto5.nombre,producto4);

    //Hash.print1();
    cout<<"-----"<<endl;

    Hash.print2("K");

    //Hash.print3();
}
