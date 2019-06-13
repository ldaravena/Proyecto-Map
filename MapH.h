#include "Map.h"

class MapH : public Map{

	private:

		//Arreglo de números primos para el tamaño de la tabla Hash
		int primes[24]={53,97,193,389,769,1543,3079,6151,12289,24593,49157,98317,196613,393241,786433,1572869,3145739,6291469,12582917,25165843,50331653,100663319,201326611,402653189};
		int n; //Tamaño de la tabla Hash
		int ind;
		std::pair<std::string,int> *tabla; //Puntero de la tabla Hash
		int tam; //Cantidad de elementos almacenados en la tabla

	public:

		MapH();
		int funcionHash(std::string k);
		int doubleHash(std::string k);
		void rehashing();
		
		void insert(std::pair<std::string,int> p);
		int at(std::string k);
		void erase(std::string k);
		int size();
		bool empty();
};
