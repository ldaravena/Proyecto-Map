#include "Map.h"

struct Nodo{
	
	//Clave del elemento
	std::string key;
	//Valor del elemento
	int data;
	
	int height;
	
	int diff;
	
	//int balanceFactor;
	
	//Puntero al padre y a los hijos
	Nodo *father;
	Nodo *left;
	Nodo *right;

	//Constructor del nodo
	Nodo(){
		
		father = NULL;
		left = NULL;
		right = NULL;
	}
};	
	
class MapAVL:public Map{

	private:
		
		//Puntero a la raiz
		Nodo *root;
		
		//Puntero auxiliar que apunta al nodo actual para realizar inserciones y búsquedas
		Nodo *current;
		
		//Cantidad de elementos existentes en el Mapa
		int tam;

	public:
	

		MapAVL();
		
		void balance(Nodo* n);
		
		void updateHeight(Nodo* n);
		
		void leftRotation(Nodo* n);
		void rightRotation(Nodo* n);
		
		void leftRightRotation(Nodo* n);
		void rightLeftRotation(Nodo* n);

		void insert(std::pair<std::string,int> p);
		int at(std::string k);
		void erase(std::string k); 
		int size();
		bool empty();
};
