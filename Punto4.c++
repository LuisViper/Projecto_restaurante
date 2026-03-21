void agregarOrden(Plato* platos,int nPlatos,Ingrediente* ingredientes,int nIngredientes){
    int tipos;
    cout<<"Cuantos platos desea: ";
    cin>>tipos;
    int* codigos = new int[tipos];
    int* cantidades = new int[tipos];
    for(int i=0;i<tipos;i++){
        cout<<"Codigo del plato: ";
        cin>>*(codigos+i);
        cout<<"Cantidad: ";
        cin>>*(cantidades+i);
    }
    for(int i=0;i<tipos;i++){
        Plato* platoActual = NULL;
        for(int j=0;j<nPlatos;j++){
            if((platos+j)->codigo == *(codigos+i)){
                platoActual = (platos+j);
            }
        }
        if(platoActual==NULL){
            cout<<"Error: plato no existe"<<endl;
            delete[] codigos;
            delete[] cantidades;
            return;
        }
        for(int k=0;k<platoActual->numIngredientes;k++){
            int codIng = (platoActual->ingredientes+k)->codigoIngrediente;
            int cantNecesaria = (platoActual->ingredientes+k)->cantidad * (*(cantidades+i));
            for(int m=0;m<nIngredientes;m++){
                if((ingredientes+m)->codigo == codIng){
                    if((ingredientes+m)->inventario < cantNecesaria){
                        cout<<"Error: inventario insuficiente"<<endl;
                        delete[] codigos;
                        delete[] cantidades;
                        return;
                    }
                }
            }
        }
    }
    double total=0;
    for(int i=0;i<tipos;i++){
        Plato* platoActual = NULL;
        for(int j=0;j<nPlatos;j++){
            if((platos+j)->codigo == *(codigos+i)){
                platoActual = (platos+j);
            }
        }
        double precioPlato=0;
        for(int k=0;k<platoActual->numIngredientes;k++){
            int codIng = (platoActual->ingredientes+k)->codigoIngrediente;
            int cant = (platoActual->ingredientes+k)->cantidad;
            for(int m=0;m<nIngredientes;m++){
                if((ingredientes+m)->codigo == codIng){
                    precioPlato += (ingredientes+m)->precio * cant;
                    (ingredientes+m)->inventario -= cant * (*(cantidades+i));
                }
            }
        }
        precioPlato *= 1.19;
        total += precioPlato * (*(cantidades+i));
    }
    cout<<"Orden registrada correctamente"<<endl;
    cout<<"Total a pagar: "<<total<<endl;
    delete[] codigos;
    delete[] cantidades;
}

int main(){
    Plato* platos = NULL;
    Ingrediente* ingredientes = NULL;
    int nPlatos = 0;
    int nIngredientes = 0;
    int opcion;
    do{
        cout<<endl;
        cout<<"1. Cargar datos desde archivos"<<endl;
        cout<<"2. Agregar orden"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Opcion: ";
        cin>>opcion;
        switch(opcion){
            case 1:
                leerIngredientes(ingredientes,nIngredientes);
                leerPlatos(platos,nPlatos,ingredientes,nIngredientes);
                cout<<"Datos cargados correctamente"<<endl;
                break;
            case 2:
                if(platos==NULL || ingredientes==NULL){
                    cout<<"Primero debe cargar los datos"<<endl;
                }else{
                    agregarOrden(platos,nPlatos,ingredientes,nIngredientes);
                }
                break;
        }
    }
while(opcion!=0);
    if(platos!=NULL){
        for(int i=0;i<nPlatos;i++){
            delete[] (platos+i)->ingredientes;
        }
        delete[] platos;
    }
    if(ingredientes!=NULL){
        delete[] ingredientes;
    }
    return 0;
}
