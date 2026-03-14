#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;
struct Ingredientes{
    char codigo[100];
    char nombre[100];
    int precioUnitario;
    char descripcion_unidad[100];
    int inventario;
    int minimo;
};
void agregarIngrediente(Ingredientes* ingredientes, char nombre_archivo[]){

    int contador = 0;
    int token_n = 0;
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
    archivoEntrada.close();
}
//Punto 3
int cantidadplatos(char nombre_Archivo[]){
int nplato=0;
char* linea = new char [200];
ifstream archivo(nombre_Archivo);
archivo.getline(linea,200);
while(archivo.getline(linea,200)){
    nplato++;
}
delete [] linea;
return nplato;
}

void calcularPrecio(Ingredientes* ingredientes, int n){
float preciofinal[100];
for (int i = 0; i<n; i++){
preciofinal[i] =((ingredientes + i)->precioUnitario)*1.19;
(ingredientes + i)->precioUnitario=preciofinal[i];
}
}
void imprimirmenu(Ingredientes* ingredientes, int n){
calcularPrecio(ingredientes, n);
cout<<"--MENU DEL RESTAURANTE: lista de platos ofrecidos:"<<endl;
    cout << left << setw(10) << "Codigo"
     << setw(20) << "Nombre"
     << setw(10) << "Precio"
     << endl;
for (int i = 0; i<n; i++){
     cout << left << setw(10) << (ingredientes + i)->codigo
     << setw(20) << (ingredientes + i)->nombre
     << setw(10) << (ingredientes + i)->precioUnitario
     << endl;
}
}


int main(){
char nombre_Archivo[20];
cout<<"Ingrese el nombre del archivo: ";
cin>>nombre_Archivo;
int nplato;
char preciofinal;
nplato =cantidadplatos(nombre_Archivo);
Ingredientes* ingredientes = new Ingredientes[nplato];
agregarIngrediente(ingredientes,nombre_Archivo);
calcularPrecio(ingredientes, nplato);
imprimirmenu(ingredientes, nplato);
}
