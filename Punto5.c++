void mostrarMasSolicitados(Plato* platos,int nPlatos,Orden* ordenes,int nOrdenes){
    int* contador = new int[nPlatos];
    for(int i=0;i<nPlatos;i++){
        *(contador+i)=0;
    }
    for(int i=0;i<nOrdenes;i++){
        for(int j=0;j<(ordenes+i)->numPlatos;j++){
            int cod = ((ordenes+i)->platos+j)->codigoPlato;
            int cant = ((ordenes+i)->platos+j)->cantidad;
            for(int k=0;k<nPlatos;k++){
                if((platos+k)->codigo == cod){
                    *(contador+k) += cant;
                }
            }
        }
    }
    cout<<"PLATOS MAS SOLICITADOS:"<<endl;
    cout<<"codigo nombre solicitudes"<<endl;
    for(int i=0;i<3;i++){
        int max = -1;
        int pos = -1;
        for(int j=0;j<nPlatos;j++){
            if(*(contador+j) > max){
                max = *(contador+j);
                pos = j;
            }
        }
        if(pos!=-1){
            cout<<(platos+pos)->codigo<<" "
                <<(platos+pos)->nombre<<" "
                <<*(contador+pos)<<endl;
            *(contador+pos) = -1;
        }
    }
    delete[] contador;
}

//pon esto en el main campeon 👹
case 5:
        mostrarMasSolicitados(platos,nPlatos,ordenes,nOrdenes);
    break;
