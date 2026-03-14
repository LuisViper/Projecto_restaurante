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
    archivoEntrada.close();
}

struct IngredientePlato{
    char codigoIngrediente[100];
    int cantidad;
};

struct Plato{
    char codigo[100];
    char nombre[100];

    IngredientePlato* vector_ingredientes;
    int numIngredintes;
};

void asignar_tam_v_ingredientes(Plato* platos){
    char linea[500];

    int contador = 0;
    int contador_platos = -1;
    ifstream archivoEntrada("platos.txt");
    while(archivoEntrada.getline(linea,500)){
        if(strcmp(linea,"#ingredientes") == 0){
            contador_platos++;
            while(archivoEntrada.getline(linea,500)){
                if(strcmp(linea,"0") == 0){
                    break;
                }
                else{
                    contador++;
                }
            }
            (platos + contador_platos)->numIngredintes = contador;
            (platos + contador_platos)->vector_ingredientes = new IngredientePlato[contador];
            contador = 0;
        }
    }

    archivoEntrada.close();
}

void agregar_plato(Plato* platos){

    int contar_ingrediente = 0;

    char nombre_doc[100];
    cout << "Introduzca el noombre del archivo de texto" << endl;
    cin >> nombre_doc;

    int n_platos = -1;
    bool b_ingredientes = false;
    bool b_cantidad_ingredientes = false;


    char linea[100];

    ifstream archivoEntrada(nombre_doc);

    if(!archivoEntrada.is_open()){
        cerr << "Hubo un erro abriendo el documento" << endl;
    }

    const char* nom_plato = "#PLATO";
    const char* bandera_ingredientes = "#código------nombre-------------";
    const char* bandera_cantidad_ingredientes = "#ingredientes";

    while(archivoEntrada.getline(linea,500)){
        if(strcmp(linea,nom_plato) == 0){
            n_platos++;
            continue;
        }
        if(strcmp(linea,bandera_ingredientes) == 0){
            b_ingredientes = true;
            continue;
        }
        if(b_ingredientes == true){
            char* token = strtok(linea,"*");
            strcpy((platos + n_platos)->codigo,token);
            char* nombre = strtok(nullptr, "*");
            strcpy((platos + n_platos)->nombre,nombre);
            b_ingredientes = false;
            continue;
        }
        if(strcmp(linea,bandera_cantidad_ingredientes) == 0){
            b_cantidad_ingredientes = true;
            contar_ingrediente = 0;
            continue;
        }

        
        if(b_cantidad_ingredientes == true){
            char* ptr = strtok(linea," ");

                while(ptr != nullptr && contar_ingrediente < (platos + n_platos)->numIngredintes){
                    if(strcmp(ptr,"0") == 0){
                        b_cantidad_ingredientes = false;
                        break;
                    }

                    strcpy(((platos + n_platos)->vector_ingredientes + contar_ingrediente)->codigoIngrediente, ptr);

                    ptr = strtok(nullptr, " ");
                    if(ptr == nullptr) break;

                    int numero = stoi(ptr);
                    ((platos + n_platos)->vector_ingredientes + contar_ingrediente)->cantidad = numero;

                    contar_ingrediente++;
                    ptr = strtok(nullptr," ");
                    
                }
            }
    }

    archivoEntrada.close();
}

void mostrar_platos(Plato* platos, int cantidad_platos){

    for(int i = 0; i < cantidad_platos; i++){

        cout << "Codigo: " << (platos + i)->codigo << endl;
        cout << "Nombre: " << (platos + i)->nombre << endl;
        cout << "Numero de ingredientes: " << (platos + i)->numIngredintes << endl;

        for(int j = 0; j < (platos + i)->numIngredintes; j++){

            cout << "  Ingrediente: "
                 << ((platos + i)->vector_ingredientes + j)->codigoIngrediente
                 << "  Cantidad: "
                 << ((platos + i)->vector_ingredientes + j)->cantidad
                 << endl;
        }

        cout << "----------------------" << endl;
    }
}

int main(){

    ifstream archivoEntradaPlatos("platos.txt");

    char linea[500];

    int numero_platos = 0;
    while(archivoEntradaPlatos.getline(linea,500)){
        if(strcmp(linea,"#PLATO") == 0){
            numero_platos++;
        }
    }
    archivoEntradaPlatos.close();

    Plato* platos = new Plato[numero_platos];

    asignar_tam_v_ingredientes(platos);

    int opcion;
    
    cout << "1. Cargar ingredientes" << endl;
    cout << "2. Cargar platos" << endl;
    cout << "3. Salir" << endl;
    cin >> opcion;
    switch(opcion){
    
        case 1:{
    
            int tam = 0;
            char linea[100];
    
            ifstream archivoEntradaIngredientes("ingredientes.txt");
    
            if (!archivoEntradaIngredientes.is_open()) {
                cerr << "No se pudo abrir el archivo para lectura." << endl;
                return 1;
            }
    
            while(archivoEntradaIngredientes.getline(linea,100)){
                tam++;
            }
    
            tam -= 2;
    
            archivoEntradaIngredientes.close();
    
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
    
            break;
        }
    
        case 2:{

            agregar_plato(platos);
    
            mostrar_platos(platos,numero_platos);

        }
    
        case 3:{
            cout << "Saliendo del programa..." << endl;
            break;
        }
    
        default:{
            cout << "Opcion invalida" << endl;
        }
    }
    return 0;
}