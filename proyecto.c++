#include <iostream>
#include <fstream>

using namespace std;

struct Ingredientes{
    char codigo;
    char nombre[100];
    int precioUnitario;
    char descripcion_unidad[100];
    int inventario;
    int minimo;  
};

void agregarIngrediente(Ingredientes* ingredientes){

    char nombre_archivo[100];
    cout << "Ingrese el nombre el nombre del archivo" << endl;
    cin >> nombre_archivo;
    
    ifstream archivoEntrada(nombre_archivo);

    




}