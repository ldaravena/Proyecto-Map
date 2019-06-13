#include "MapSV.h"
#include <algorithm>

MapSV::MapSV(){

	tam = 0;
}


int MapSV::bs(std::string k){

	std::sort(v.begin(),v.end());

    int liminf = 0;       //Límite inferior de búsqueda
    int limsup = (tam-1); //Límite superior de búsqueda
    int mit = (liminf+limsup)/2; //Mitad del arreglo a buscar

    while(true){

        //Si el límite superior es menor al límite inferior es porque no se encontró el elemento a buscar
        if(limsup < liminf) return -1;

        //Si el elemento de la mitad del arreglo es menor al número buscado:
        if((v.at(mit)).first < k){

            //Se establece como límite inferior el elemento siguiente a la mitad y se define la nueva mitad
            liminf = mit+1;
            mit = (liminf+limsup)/2;
        }
        //En caso de que el elemento en la mitad del arreglo es mayor al número buscado:
        else if((v.at(mit)).first > k){

            //Se establece como límite superior el elemento anterior a la mitad y se defina la nueva mitad
            limsup = mit-1;
            mit = (liminf+limsup)/2;
        }
        
        else return mit;
    }
}


void MapSV::insert(std::pair<std::string,int> p){

	v.push_back(p);
	
	tam++;
}

int MapSV::at(std::string k){

	int i = bs(k);

	if(i!=-1) return (v.at(i)).second;
	
	else return std::numeric_limits<int>::min();
}
		
void MapSV::erase(std::string k){

	int i = bs(k);
	
	if(i!=-1){
	
		while(i+1 < v.size()){
		
			v.at(i)=v.at(i+1);
			i++;
		}
		
		v.pop_back();
		
		tam--;
	}
}
		
int MapSV::size(){

	return tam;
}		
		
bool MapSV::empty(){

	return tam==0?true:false;
}
