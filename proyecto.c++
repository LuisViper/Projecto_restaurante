#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Ingredientes{
    char codigo[100];
    char nombre[100];
    int precioUnitario;
    char descripcion_unidad[100];
    int inventario;
    int minimo;  
};

void agregarIngrediente(Ingredientes* ingredientes){

    int contador = 0;
    int token_n = 0;
    char nombre_archivo[100];
    cout << "Ingrese el nombre el nombre del archivo" << endl;
    cin >> nombre_archivo;
    
    ifstream archivoEntrada(nombre_archivo);

    if(!archivoEntrada.is_open()){
        cout << "Hubo un error para abrir el archivo" << endl;
    }

    char linea[100];

    while(archivoEntrada.getline(linea,100)){
        if(linea[0] == '#'){
            continue;
        }
        if(linea[0] == '0'){
            break;
        }
        else{
            char* codigo = strtok(linea,"*");
            strcpy((ingredientes + contador)->codigo,codigo);   
            char* nombre = strtok(nullptr,"*");
            strcpy((ingredientes + contador)->nombre,nombre);
            char* preciou = strtok(nullptr,"*");
            token_n = atoi(preciou);
            (ingredientes + contador)->precioUnitario = token_n;
            char* descrip = strtok(nullptr,"*");
            strcpy((ingredientes + contador)->descripcion_unidad,descrip);
            char* invetario = strtok(nullptr,"*");
            token_n = atoi(invetario);
            (ingredientes + contador)->inventario = token_n;
            char* minimo = strtok(nullptr,"*");
            token_n = atoi(minimo);
            (ingredientes + contador)->minimo = token_n;
            contador++;
        }
    }
}

int main(){

int tam = 0;
char linea[100];

ifstream archivoEntrada("ingredientes.txt");

if (!archivoEntrada.is_open()) {
    cerr << "No se pudo abrir el archivo para lectura." << endl;
    return 1;
}

// Hacemos esto para crear el vector de ingredientes del tamaño del total de ingredientes, puede cambiar
while(archivoEntrada.getline(linea,100)){
    tam++;
}

tam -= 2;

Ingredientes* ingredientes = new Ingredientes[tam];

agregarIngrediente(ingredientes);

for(int i = 0; i < tam; i++){
    cout << "Codigo: " << (ingredientes + i)->codigo << endl;
    cout << "Nombre: " << (ingredientes + i)->nombre << endl;
    cout << "Precio Unitario: " << (ingredientes + i)->precioUnitario << endl;
    cout << "Descripcion Unidad: " << (ingredientes + i)->descripcion_unidad << endl;
    cout << "Inventario: " << (ingredientes + i)->inventario << endl;
    cout << "Minimo: " << (ingredientes + i)->minimo << endl;
    cout << "--------------------------" << endl;
}



    return 0;
}