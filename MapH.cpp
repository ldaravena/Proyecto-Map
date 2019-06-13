#include "MapH.h"

MapH::MapH(){

	tam=0;
	ind=0;
	n=primes[ind]; //Tamaño tabla hash

	tabla = new std::pair<std::string,int>[n];
}

int MapH::funcionHash(std::string k){

	int res=0;

    for(int i=0; i < k.length() ; i++){

        res = (32*res + int(k.at(i)))%n;
	}

	//Función Hash
	return res;
}

//Método para la función Double Hash
int MapH::doubleHash(std::string k){

	int res=0;

	for(int i=0; i < k.length() ; i++){

        res = (32*res + int(k.at(i)));
	}
	
	//Se elige un número primo (47) que sea menor que el tamaño de la tabla
	
	return (47-(res%47));
}


void MapH::insert(std::pair<std::string,int> p){

	//Si la tabla está llena se hace rehashing
	if(tam == n) rehashing();

	std::string k = p.first;

	int i = funcionHash(k);

	//Se calcula el valor del doubleHash y se obtiene el módulo
	int d = doubleHash(k) % n;

	//Variable para avanzar en la tabla con el doubleHash
	int f = 1;

	//Si doubleHash retorna cero, se incrementa a uno
	if(d==0) d++;

	if( (((tabla[i]).first).empty()) || (((tabla[i]).first) == "clear" && (tabla[i]).second == std::numeric_limits<int>::min()) ){

		tabla[i]=p;
		tam++;
	}

	else if((tabla[i]).first == k){

		(tabla[i]).second = p.second;
	}

	else{

		//Se obtiene el nuevo índice con la función hash original y el doubleHash
		int j=(i+f*d)%n;

		//Mientras no encuentre un espacio vacío o desocupado sigue avanzando con la función hash y doubleHash
		while(!((tabla[j]).first).empty()  && !(((tabla[j]).first) == "clear" && (tabla[j]).second == std::numeric_limits<int>::min()) ){

			f++;
			j=(i+f*d)%n;
			
			
			//Si se encuentra la clave duplicada se sobreescribe
			if(tabla[j].first == k) break;			
			
		}

		//Se guarda el elemento
		tabla[j]=p;
		tam++;
	}
}

void MapH::rehashing(){

	std::pair<std::string,int> *tablaux = new std::pair<std::string,int>[n];

	tablaux=tabla;

	int m=n;

	ind++;

	n=primes[ind];

	tabla = new std::pair<std::string,int>[n];

	tam=0;

	for(int i=0; i<m; i++){

		insert(tablaux[i]);
	}

	delete[] tablaux;
}

void MapH::erase(std::string k){

	int i = funcionHash(k);

	if((tabla[i].first) == k){

		tabla[i].first = "clear";
		tabla[i].second = std::numeric_limits<int>::min();

		tam--;
	}

	//Si no encuentra la clave con la funcionHash se busca con el doubleHash
	else{

		int d = doubleHash(k) % n;

		if(d==0) d++;

		int f = 1;

		int j = (i+f*d)%n;

		//Mientras no encuentre una celda vacía
		while( !(((tabla[j]).first).empty()) ){

			//Si se vuelve al índice original, se ha recorrido toda la tabla y no existe el elemento
			if(j == i) break;

			if((tabla[j]).first==k){

				tabla[j].first = "clear";
				tabla[j].second = std::numeric_limits<int>::min();

				tam--;
				break;
			}

			//Se calcula el nuevo índice a buscar
			f++;
			j = (i+f*d)%n;
		}
	}
}

int MapH::at(std::string k){

	int i = funcionHash(k);

	if((tabla[i].first) == k){

		return tabla[i].second;
	}

	else{

		int rep=i;

		int d = doubleHash(k) % n;

		if(d==0) d++;

		int f = 1;

		int j=(i+f*d)%n;

		while( !(((tabla[j]).first).empty()) ){

			if(j==rep) return std::numeric_limits<int>::min();

			if((tabla[j]).first==k){

				return tabla[j].second;
			}

			f++;
			j = (i+f*d)%n;
		}

		return std::numeric_limits<int>::min();
	}
}

int MapH::size(){

	return tam;
}

bool MapH::empty(){

	return tam==0?true:false;
}
