#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    
    std::ifstream archivoCSV("Inventariado Fisico.csv");

    const int buffer_size = 4096;  // Tamaño del búfer (ajusta según tus necesidades)
    char buffer[buffer_size];

    archivoCSV.getline(buffer, buffer_size);  // Lee una línea del archivo en el búfer

    std::stringstream ss(buffer);
    std::string columna;
    int contadorColumnas = 0;

    while (std::getline(ss, columna, ',')) {
        contadorColumnas++;
    }

    std::cout << "El archivo CSV tiene " << contadorColumnas << " columnas." << std::endl;

    char seprador = ',';
    string linea;
    getline(archivoCSV,linea);

    cout<<linea<<endl;
    
    contadorColumnas -= 3;
    string* d = new string[contadorColumnas];

    while(getline(archivoCSV,linea)){
        stringstream stream(linea);
        string grupo,codigo,articulo;

        getline(stream,grupo,seprador);
        getline(stream,codigo,seprador);
        getline(stream,articulo,seprador);
        cout<<"================"<<endl;
        cout<<"Grupo: "<<grupo<<endl;
        cout<<"Codigo: "<<codigo<<endl;
        cout<<"Articulo: "<<articulo<<endl;
        
        for(int i=0; i<contadorColumnas; i++){
            getline(stream, d[i], seprador);
            cout<<"Deposito "<<i+1<<": "<<d[i]<<endl;
        }

    } 
    archivoCSV.close();
    
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;
}


  
