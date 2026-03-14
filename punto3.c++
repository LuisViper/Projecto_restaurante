#include <iostream>
#include <iomanip>
using namespace std;
struct Ingrediente
{
    int codigo;
    char nombre[50];
    float precioUnitario;
};
struct IngredientePlato
{
    int codigoIngrediente;
    int cantidad;
};
struct Plato
{
    int codigo;
    char nombre[50];
    IngredientePlato *ingredientes;
    int numIngredientes;
};
int buscarIngrediente(Ingrediente *ingredientes, int n, int codigo)
{
    for(int i = 0; i < n; i++)
    {
        if(ingredientes[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;
}
float calcularPrecio(Plato *plato, Ingrediente *ingredientes, int n)
{
    float precioBase = 0;
    for(int i = 0; i < plato->n; i++)
    {
        int cod = plato->ingredientes[i].codigoIngrediente;
        int cant = plato->ingredientes[i].cantidad;
        int pos = buscarIngrediente(ingredientes, n, cod);
        if(pos != -1)
        {
            precioBase += ingredientes[pos].precioUnitario * cant;
        }
    }
    float precioFinal = precioBase * 1.19;
    return precioFinal;
}
void mostrarMenu(Plato *platos, int nPlatos, Ingrediente *ingredientes, int n)
{
    cout << "Menu: lista de platos ofrecidos:" << endl;
    cout << endl;
    cout << left << setw(10) << "codigo"
         << setw(20) << "nombre"
         << setw(10) << "precio" << endl;
    for(int i = 0; i < nPlatos; i++)
    {
        float precio = calcularPrecio(&platos[i], ingredientes, n);
        cout << left << setw(10) << platos[i].codigo
             << setw(20) << platos[i].nombre
             << setw(10) << precio
             << endl;
    }
}
