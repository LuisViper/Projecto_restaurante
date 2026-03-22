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

// PUNTO 3

int buscarIngrediente(Ingredientes* ingredientes, int nIngredientes, char* codigo){
    for(int i = 0; i < nIngredientes; i++){
        if(strcmp((ingredientes + i)->codigo, codigo) == 0){
            return i;
        }
    }
    return -1;
}

float calcularPrecio(Plato* plato, Ingredientes* ingredientes, int nIngredientes){
    float precioBase = 0;
    IngredientePlato* ingredienteActual = plato->vector_ingredientes;
    for(int i = 0; i < plato->numIngredintes; i++){
        char* codigo = (ingredienteActual + i)->codigoIngrediente;
        int cantidad = (ingredienteActual + i)->cantidad;
        int pos = buscarIngrediente(ingredientes, nIngredientes, codigo);
        if(pos != -1){
            int precioUnitario = (ingredientes + pos)->precioUnitario;
            precioBase += precioUnitario * cantidad;
        }
    }
    float precioFinal = precioBase * 1.19;
    return precioFinal;
}

void mostrarMenu(Plato* platos, int nPlatos, Ingredientes* ingredientes, int nIngredientes){
    cout << left << setw(10) << "codigo"
         << setw(20) << "nombre"
         << setw(10) << "precio" << endl;
    for(int i = 0; i < nPlatos; i++){
        Plato* platoActual = (platos + i);
        float precio = calcularPrecio(platoActual, ingredientes, nIngredientes);
        cout << left << setw(10) << platoActual->codigo
             << setw(20) << platoActual->nombre
             << setw(10) << precio << endl;
    }
}

// FIN PUNTO 3

// PUNTO 4

struct PlatoOrden {
    char codigoPlato[100];
    int cantidad;
};

struct Orden {
    PlatoOrden* platos;
    int numPlatos;
    double total;
};

void agregarOrden(Plato* platos, int nPlatos, Ingredientes* ingredientes, int nIngredientes, Orden* &ordenes, int &nOrdenes) {
    int tipos;
    cout << "Cuantos tipos de platos desea ordenar: ";
    cin >> tipos;

    char** codigos = new char*[tipos];
    int* cantidades = new int[tipos];

    for (int i = 0; i < tipos; i++) {
        codigos[i] = new char[100];
        cout << "Codigo del plato: ";
        cin >> codigos[i];
        cout << "Cantidad: ";
        cin >> cantidades[i];
    }

    // Validar existencia e inventario
    for (int i = 0; i < tipos; i++) {
        Plato* platoActual = nullptr;
        for (int j = 0; j < nPlatos; j++) {
            if (strcmp((platos + j)->codigo, codigos[i]) == 0) {
                platoActual = (platos + j);
            }
        }
        if (platoActual == nullptr) {
            cout << "Error: el plato con codigo " << codigos[i] << " no existe." << endl;
            for (int k = 0; k < tipos; k++) delete[] codigos[k];
            delete[] codigos;
            delete[] cantidades;
            return;
        }
        for (int k = 0; k < platoActual->numIngredintes; k++) {
            char* codIng = (platoActual->vector_ingredientes + k)->codigoIngrediente;
            int cantNecesaria = (platoActual->vector_ingredientes + k)->cantidad * cantidades[i];
            int pos = buscarIngrediente(ingredientes, nIngredientes, codIng);
            if (pos != -1 && (ingredientes + pos)->inventario < cantNecesaria) {
                cout << "Error: inventario insuficiente para el ingrediente " << codIng << endl;
                for (int k2 = 0; k2 < tipos; k2++) delete[] codigos[k2];
                delete[] codigos;
                delete[] cantidades;
                return;
            }
        }
    }

    // Registrar orden y calcular total
    double total = 0;
    for (int i = 0; i < tipos; i++) {
        Plato* platoActual = nullptr;
        for (int j = 0; j < nPlatos; j++) {
            if (strcmp((platos + j)->codigo, codigos[i]) == 0) {
                platoActual = (platos + j);
            }
        }
        double precioPlato = 0;
        for (int k = 0; k < platoActual->numIngredintes; k++) {
            char* codIng = (platoActual->vector_ingredientes + k)->codigoIngrediente;
            int cant = (platoActual->vector_ingredientes + k)->cantidad;
            int pos = buscarIngrediente(ingredientes, nIngredientes, codIng);
            if (pos != -1) {
                precioPlato += (ingredientes + pos)->precioUnitario * cant;
                (ingredientes + pos)->inventario -= cant * cantidades[i];
            }
        }
        precioPlato *= 1.19;
        total += precioPlato * cantidades[i];
    }

    // Guardar la orden en el arreglo de ordenes
    Orden* nuevasOrdenes = new Orden[nOrdenes + 1];
    for (int i = 0; i < nOrdenes; i++) {
        (nuevasOrdenes + i)->numPlatos = (ordenes + i)->numPlatos;
        (nuevasOrdenes + i)->total = (ordenes + i)->total;
        (nuevasOrdenes + i)->platos = (ordenes + i)->platos;
    }
    (nuevasOrdenes + nOrdenes)->numPlatos = tipos;
    (nuevasOrdenes + nOrdenes)->total = total;
    (nuevasOrdenes + nOrdenes)->platos = new PlatoOrden[tipos];
    for (int i = 0; i < tipos; i++) {
        strcpy(((nuevasOrdenes + nOrdenes)->platos + i)->codigoPlato, codigos[i]);
        ((nuevasOrdenes + nOrdenes)->platos + i)->cantidad = cantidades[i];
    }

    delete[] ordenes;
    ordenes = nuevasOrdenes;
    nOrdenes++;

    cout << "Orden registrada correctamente." << endl;
    cout << "Total a pagar: " << total << endl;

    for (int i = 0; i < tipos; i++) delete[] codigos[i];
    delete[] codigos;
    delete[] cantidades;
}

// FIN PUNTO 4

// FUNCION 5

int* mostrarMasSolicitados(Plato* platos, int nPlatos, Orden* ordenes, int nOrdenes) {
    int* contador = new int[nPlatos];
    for (int i = 0; i < nPlatos; i++) {
        *(contador + i) = 0;
    }
    for (int i = 0; i < nOrdenes; i++) {
        for (int j = 0; j < (ordenes + i)->numPlatos; j++) {
            char* cod = ((ordenes + i)->platos + j)->codigoPlato;
            int cant = ((ordenes + i)->platos + j)->cantidad;
            for (int k = 0; k < nPlatos; k++) {
                if (strcmp((platos + k)->codigo, cod) == 0) {
                    *(contador + k) += cant;
                }
            }
        }
    }
    cout << "PLATOS MAS SOLICITADOS:" << endl;
    cout << left << setw(10) << "codigo" << setw(20) << "nombre" << setw(10) << "solicitudes" << endl;
    for (int i = 0; i < 3; i++) {
        int max = -1;
        int pos = -1;
        for (int j = 0; j < nPlatos; j++) {
            if (*(contador + j) > max) {
                max = *(contador + j);
                pos = j;
            }
        }
        if (pos != -1) {
            cout << left << setw(10) << (platos + pos)->codigo
                 << setw(20) << (platos + pos)->nombre
                 << setw(10) << *(contador + pos) << endl;
            *(contador + pos) = -1;
        }
    }
    return contador;
}

struct Plato_final_precio{
    char codigo[100];
    char nombre[100];

    float precio_final;
};

// PUNTO 6

void Platos_mas_rentables(Plato* platos, int nPlatos, Orden* ordenes, int nOrdenes, Ingredientes* ingredientes,int nIngredientes){

    int* contador = new int[nPlatos];
    for (int i = 0; i < nPlatos; i++) {
        *(contador + i) = 0;
    }
    for (int i = 0; i < nOrdenes; i++) {
        for (int j = 0; j < (ordenes + i)->numPlatos; j++) {
            char* cod = ((ordenes + i)->platos + j)->codigoPlato;
            int cant = ((ordenes + i)->platos + j)->cantidad;
            for (int k = 0; k < nPlatos; k++) {
                if (strcmp((platos + k)->codigo, cod) == 0) {
                    *(contador + k) += cant;
                }
            }
        }
    }

    Plato_final_precio* plato_final = new Plato_final_precio[nPlatos];

    for(int i = 0; i < nPlatos; i++){

        strcpy((plato_final + i)->nombre,(platos + i)->nombre);
        strcpy((plato_final + i)->codigo,(platos + i)->codigo);
        Plato* platoActual = (platos + i);
        float precio = calcularPrecio(platoActual, ingredientes, nIngredientes);
        precio *= *(contador + i);

        (plato_final + i)->precio_final = precio;
    }

    for(int i = 1; i < nPlatos; i++){
        Plato_final_precio key = *(plato_final + i);
        int j = i - 1;

        while(j >= 0 && (plato_final + j)->precio_final < key.precio_final){
            *(plato_final + (j+1)) = *(plato_final + j);
            j--;
        }
        *(plato_final + (j + 1)) = key;
    }

    for(int i = 0; i < 3; i++){
    cout << "Codigo: " << (plato_final + i)->codigo << endl;
    cout << "Nombre: " << (plato_final + i)->nombre << endl;
    cout << "Precio final: " << (plato_final + i)->precio_final << endl;
    cout << "--------------------------" << endl;

}


delete[] plato_final;
delete[] contador;
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

    Ingredientes* ingredientes = nullptr;
    int tam = 0;

    Orden* ordenes = nullptr;
    int nOrdenes = 0;

    int opcion;

    do {
        cout << "\n1. Cargar ingredientes" << endl;
        cout << "2. Cargar platos" << endl;
        cout << "3. Mostrar menu con precios" << endl;
        cout << "4. Agregar orden" << endl;
        cout << "5. Mostrar los platos mas solicitados" << endl;
        cout << "6. Mostrar los 3 platos mas rentables  " << endl;
        cout << "7. Salir" << endl;


        cin >> opcion;

        switch(opcion){

            case 1:{
                char linea[100];
                ifstream archivoEntradaIngredientes("ingredientes.txt");

                if (!archivoEntradaIngredientes.is_open()) {
                    cerr << "No se pudo abrir el archivo para lectura." << endl;
                    break;
                }

                while(archivoEntradaIngredientes.getline(linea,100)){
                    tam++;
                }
                tam -= 2;
                archivoEntradaIngredientes.close();

                ingredientes = new Ingredientes[tam];
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
                mostrar_platos(platos, numero_platos);
                break;
            }

            case 3:{
                if(ingredientes == nullptr){
                    cout << "Primero debe cargar los ingredientes (opcion 1)" << endl;
                    break;
                }
                mostrarMenu(platos, numero_platos, ingredientes, tam);
                break;
            }

            case 4:{
                if (platos == nullptr || ingredientes == nullptr) {
                    cout << "Primero debe cargar los datos" << endl;
                } else {
                    agregarOrden(platos, numero_platos, ingredientes, tam, ordenes, nOrdenes);
                    
                }
                break;
            }

            case 5:{
                if (nOrdenes == 0) {
                    cout << "No hay ordenes registradas." << endl;
                } else {
                    int* resultado = mostrarMasSolicitados(platos, numero_platos, ordenes, nOrdenes);
                    delete[] resultado;

                }
                break;            
            }

            case 6:{
                Platos_mas_rentables(platos,numero_platos,ordenes,nOrdenes,ingredientes,tam);
                break;            
            }
            case 7:{
                cout << "Saliendo. " << endl;
                break;            
            }

            default:{
                cout << "Opcion invalida" << endl;
            }
        }

    } while(opcion != 7);


    for (int i = 0; i < nOrdenes; i++) {
        delete[] (ordenes + i)->platos;
    }
    delete[] ordenes;
    delete[] platos;
    delete[] ingredientes;
    return 0;
}