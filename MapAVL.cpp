#include "MapAVL.h"
#include <cmath>

MapAVL::MapAVL(){

	//Se inicia la raiz apuntado a NULL
    root = NULL;
    //La cantidad de elementos existentes se inicia en cero
	tam = 0;
}

void MapAVL::leftRotation(Nodo* a){

	Nodo* b = a->right;
	a->right = b->left;
	
	if(b->left != NULL) b->left->father = a;
	
	if(a->father == NULL) root = b;
	
	else if(a == a->father->left) a->father->left = b;  

	else if(a == a->father->right) a->father->right = b;
	
	b->father = a->father;
	
	a->father = b;
	
	b->left = a;
	
	a->balanceFactor -= 1;
	a->balanceFactor -= b->balanceFactor > 0?b->balanceFactor:0; 
	
	b->balanceFactor -= 1;
	b->balanceFactor += a->balanceFactor < 0?a->balanceFactor:0;
}

void MapAVL::rightRotation(Nodo* a){

	Nodo* b = a->left;
	a->left = b->right;
	
	if(b->right != NULL) b->right->father = a;
	
	if(a->father == NULL) root = b;
	
	else if(a == a->father->left) a->father->left = b;  

	else if(a == a->father->right) a->father->right = b;
	
	a->father = b->father;
	
	a->father = b;
	
	b->right = a;
	
	a->balanceFactor += 1;
	a->balanceFactor -= b->balanceFactor < 0?b->balanceFactor:0; 
	
	b->balanceFactor += 1;
	b->balanceFactor += a->balanceFactor > 0?a->balanceFactor:0;
}


void MapAVL::balance(Nodo* n){

	if(n->balanceFactor > 0){
	
		if(n->right->balanceFactor < 0){
			
			rightRotation(n->right);
				
			leftRotation(n);
		}
			
		else{
			
			leftRotation(n);
		}	
	}
		
	else if(n->balanceFactor < 0){
	
		if(n->left->balanceFactor > 0){
			
			leftRotation(n->left);
			
			rightRotation(n);
		}
		
		else{
		
			rightRotation(n);
		}
	}
}

void MapAVL::updateBalanceFactor(Nodo* n){
	
	if(abs(n->balanceFactor) >1) balance(n);
	
	else if(n->father != NULL){

		if(n == n->father->left) n->father->balanceFactor -=1;
		
		if(n == n->father->right) n->father->balanceFactor +=1;
		
		if(n->father->balanceFactor != 0) updateBalanceFactor(n->father);
	}
}

void MapAVL::insert(std::pair<std::string,int> p){
	
	//Inserción del primer elemento	
	if(root == NULL){

    	root = new Nodo();
    	root->key = p.first;
    	root->data = p.second;
		
		//El nodo actual es la raíz
		current = root;
		
		root->balanceFactor = 0;

		tam++;
    }
    
    //Inserción del resto de los elementos de manera recursiva
	else{

		//Si la clave del elemento a insertar es menor a la clave actual	 	
		if((p.first < current->key) ){
			
			//Si el hijo izquierdo no existe, se crea con el elemento insertado
			if(current->left == NULL){
				
				current->left = new Nodo();

				current->left->father = current;
				current->left->key = p.first;
				current->left->data = p.second;
				
				current->left->balanceFactor = 0;

				
				updateBalanceFactor(current->left);

				//Se aumenta el tamaño de los elementos existentes
				tam++;
				
				//El nodo actual se apunta a la raíz
				current = root;

			}
			
			//Si el hijo izquierdo existe, se cambia el puntero del nodo actual
			else{
			
				current = current->left;
				insert(p);
			}
		}
		
		//Si la clave del elemento a insertar es mayor a la clave actual	 
		else if((p.first > current->key)){
			
			//Si el hijo derecho no existe, se crea con el elemento insertado
			if(current->right == NULL){
	
				current->right = new Nodo();
				current->right->father = current;
				current->right->key = p.first;
				current->right->data = p.second;
				 
				current->right->balanceFactor = 0;

				
				updateBalanceFactor(current->right);
 
				 
				//El nodo actual se apunta a la raíz
				current = root;  
				
				//Se aumenta el tamaño de los elementos existentes
				tam++;
			}
			
			//Si el hijo derecho existe, se cambia el puntero del nodo actual	
			else{
			
				current = current->right;
				insert(p);
			}
		}
		
		//En caso de que se ingrese un elemento con una clave existente
		else{
			
			//Se actualiza el valor
			current->data = p.second;

			current = root;
		}
	}	  	
}

int MapAVL::at(std::string k){

	
	//Si la clave a buscar es menor al nodo actual
	if( k < current->key ){
		
		//Si el hijo izquierdo existe
		if(current->left != NULL){
			
			//Se actualiza el nodo actual
			current = current->left;
			return at(k);
		}
		
		//Si no existe
		else{
			
			//Se vuelve el nodo actual a la raiz
			current = root;
		 	
		 	//Se entrega el mínimo valor entero para indicar que no existe
		 	return std::numeric_limits<int>::min();
		}
	}
	
	//Si la clave a buscar es mayor al nodo actual
	else if( k > current->key ){
		
		//Si el hijo derecho existe
		if(current->right != NULL){
			
			//Se actualiza el nodo actual
			current = current->right;
			return at(k);
		}
		
		//Si no existe	
		else{
			
			//Se vuelve el nodo actual a la raiz
			current = root;
			
			//Se entrega el mínimo valor entero para indicar que no existe
		 	return std::numeric_limits<int>::min();
		}		
	}
	
	//En caso contrario la clave ingresada es igual a la del nodo actual
	else{
		
		//Se obvtiene el valor del nodo actual
		int dato = current->data;
		
		//Se vuelve el nodo acual a la raiz
		current = root;
		
		//Se retorna el valor
		return dato;
	}
}

void MapAVL::erase(std::string k){

	//Si la clave a buscar es menor al nodo actual
	if( k < current->key ){
		
		//Si el hijo izquierdo existe
		if(current->left != NULL){
			
			//Se actualiza el nodo actual
			current = current->left;
			erase(k);
		}
		
		//Si no existe
		else{
			
			//Se vuelve el nodo actual a la raiz
			current = root;
		}
	}
	
	//Si la clave a buscar es mayor al nodo actual
	else if( k > current->key ){
		
		//Si el hijo derecho existe
		if(current->right != NULL){
			
			//Se actualiza el nodo actual
			current = current->right;
			erase(k);
		}
		
		//Si no existe	
		else{
			
			//Se vuelve el nodo actual a la raiz
			current = root;
		}		
	}
	
	//En caso contrario la clave ingresada es igual a la del nodo actual
	else{
	
		Nodo* balanceNode;
	
	
		if(current->left == NULL && current->right == NULL){
		
			if(current == current->father->left){
			
				current->father->left = NULL;
				
				current->father->balanceFactor +=1;
				
			}
			
			else if(current = current->father->right){
			
				current->father->right = NULL;
				
				current->father->balanceFactor -=1;
				
			}
			
			
			
			balanceNode = current->father;
			
			delete current;
		}
		
		
		else if(current->left == NULL || current->right == NULL){
		
			if(current->left == NULL){
			
				current->father->right = current->right;
				
				current->right->father = current->father;
				
				current->father->balanceFactor -=1;
			
			}
			
			else if(current->right == NULL){
			
				current->father->left = current->left;
				
				current->left->father = current->father;
				
				current->father->balanceFactor +=1;
			
			}
			
			balanceNode = current->father;
			
			delete current;
		}
		
		else{
			
			Nodo* newCurrent = current->right;
	
			
			while(newCurrent->left!=NULL){
			
				newCurrent = newCurrent->left;
			}
			
			if(newCurrent->right!=NULL){
			
				newCurrent->right->father = newCurrent->father;
				
				newCurrent->father->right = newCurrent->right;
				
				newCurrent->father->balanceFactor -=1;				
								
			//	balanceNode = newCurrent->right;
				
			}
			
			else{
				
				newCurrent->father->balanceFactor +=1;
				
//				balanceNode = newCurrent->father;
			}
			
			balanceNode = newCurrent->father;
			
			newCurrent->father = current->father;
			
			newCurrent->left = current->left;
			
			newCurrent->right = current->right;
			
			newCurrent->balanceFactor = current->balanceFactor;
			
			
			if(current == current->father->right){
			
				current->father->right = newCurrent;
			}
			
			else if(current == current->father->left){
			
				current->father->left = newCurrent;
			}
			
			delete current;						
		
		}
		
		tam--;
		
		updateBalanceFactor(balanceNode);

	}
}


int MapAVL::size(){
	
	//Se entrega la cantidad de elementos existentes
	return tam;
}

bool MapAVL::empty(){

	return tam==0?true:false;
}


int MapAVL::bRoot(){

	return root->balanceFactor;
}
