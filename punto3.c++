#include <iostream>
#include <fstream>
#include <cstring>
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

struct IngredientePlato{
    char codigoIngrediente[100];
    int cantidad;
};

struct Plato{
    char codigo[100];
    char nombre[100];
    IngredientePlato* ingredientesPlato;
    int numIngredintes;
};

int buscarIngrediente(Ingredientes* ingredientes, int nIngredientes, char* codigo){

    for(int i=0;i<nIngredientes;i++){
        if(strcmp((ingredientes+i)->codigo,codigo)==0){
            return i;
        }
    }

    return -1;
}

float calcularPrecio(Plato* plato, Ingredientes* ingredientes, int nIngredientes){

    float precioBase = 0;

    for(int i=0;i<plato->numIngredintes;i++){

        IngredientePlato* ingredienteActual = (plato->ingredientesPlato + i);

        char* codigo = ingredienteActual->codigoIngrediente;
        int cantidad = ingredienteActual->cantidad;

        int pos = buscarIngrediente(ingredientes,nIngredientes,codigo);

        if(pos != -1){

            int precioUnitario = (ingredientes+pos)->precioUnitario;

            precioBase += precioUnitario * cantidad;

        }
    }

    float precioFinal = precioBase * 1.19;

    return precioFinal;
}

void mostrarMenu(Plato* platos,int nPlatos,Ingredientes* ingredientes,int nIngredientes){

    cout<<left<<setw(10)<<"codigo"
        <<setw(20)<<"nombre"
        <<setw(10)<<"precio"<<endl;

    for(int i=0;i<nPlatos;i++){

        Plato* platoActual = (platos+i);

        float precio = calcularPrecio(platoActual,ingredientes,nIngredientes);

        cout<<left<<setw(10)<<platoActual->codigo
            <<setw(20)<<platoActual->nombre
            <<setw(10)<<precio<<endl;

    }

}
