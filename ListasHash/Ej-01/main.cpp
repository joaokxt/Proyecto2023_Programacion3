#include <iostream>
#include "../HashMap/HashMap.h"

using namespace std;


unsigned int funcion(string clave){
    unsigned int num;
    for(int i =0;i<clave.length();i++){
        num += clave[i];
    }
    return num;
}



int main() {
  std::cout << "Ejercicio 05/01\n" << std::endl;

  HashMap<string ,int> Hash(10,&funcion);

  Hash.put("H235802",2002);
  Hash.put("Jk372LO3",2345);

  Hash.print();
}
