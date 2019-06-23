#include "MapAVL.h"


#include <iostream>

#include <algorithm>

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
	
	
	if(a->left!= NULL){
	
		updateHeight(a->left);
	}
	
	else if(a->right!=NULL){
	
		updateHeight(a->right);
	}
	
	
	else{
	
		a->height = 0;
		a->diff = 0;
		
		updateHeight(a);
	}
}	


void MapAVL::rightRotation(Nodo* a){

	Nodo* b = a->left;
	
	a->left = b->right;
	
	if(b->right != NULL){
	
		b->right->father = a;
	}
	
	if(a->father == NULL) root = b;
	
	else if(a == a->father->left) a->father->left = b;  

	else if(a == a->father->right) a->father->right = b;
	
	b->father = a->father;
	
	a->father = b;
	
	b->right = a;


	if(a->right!= NULL){
	
		updateHeight(a->right);
	}
	
	
	else if(a->left!= NULL){
	
		updateHeight(a->left);
	}
	
	else{
		
		a->height = 0;
		a->diff = 0;
		
		updateHeight(a);
	}
}



void MapAVL::leftRightRotation(Nodo* a){

	Nodo* c = a->right;
	Nodo* b = c->left;
	
	a->right = b->left;
	
	if(b->left!=NULL){
	
		b->left->father = a;
	}
	
	if(a->father == NULL){
	
		root = b;
	}
	
	else if(a == a->father->left){
	
		a->father->left = b;
	}
	
	else if(a == a->father->right){
	
		a->father->right = b;
	}
	
	b->father = a->father;
	
	a->father = b;
	b->left = a;
	
	c->left = b->right;
	
	if(b->right!=NULL){
	
		b->right->father = c;
	}
	
	c->father = b;
	b->right = c;
	
	if(a->left == NULL && a->right == NULL){
	
		a->height = 0;
		a->diff = 0;
	}
	
	else if(a->left != NULL && a->right!= NULL){
		
		a->height = std::max(a->left->height,a->right->height) +1;
		a->diff = a->right->height - a->left->height; 
	}
	
	else{
	
		if(a->left==NULL){
		
			a->height = a->right->height +1;
			a->diff =1;
		}
		
		else if(a->right == NULL){
		
			a->height = a->left->height +1;
			a->diff = -1;
		}
	}
	
	if(c->left == NULL && c->right == NULL){
	
		c->height = 0;
		c->diff = 0;
	}
	
	else if(c->left != NULL && c->right!= NULL){
		
		c->height = std::max(c->left->height,c->right->height) +1;
		c->diff = c->right->height - c->left->height; 
	}
	
	else{
	
		if(c->left==NULL){
		
			c->height = c->right->height +1;
			c->diff =1;
		}
		
		else if(c->right == NULL){
		
			c->height = c->left->height +1;
			c->diff = -1;
		}
	}
	
	updateHeight(c);
	
}


void MapAVL::rightLeftRotation(Nodo* c){

	Nodo* a = c->left;
	Nodo* b = a->right;
	
	a->right = b->left;
	
	if(b->left!=NULL){
	
		b->left->father = a;
	}
	
	if(c->father == NULL){
	
		root = b;
	}
	
	else if(c == c->father->right){
	
		c->father->right = b;
	}
	
	else if(c == c->father->left){
	
		c->father->left = b;
	}
	
	c->left = b->right;
	
	if(b->right!=NULL){
	
		b->right->father = c;
	}
	
	b->father = c->father;
		
	b->left = a;
	
	b->right = c;
	
	a->father = b;
	
	c->father = b;
	
		
	if(a->left == NULL && a->right == NULL){
	
		a->height = 0;
		a->diff = 0;
	}
	
	else if(a->left != NULL && a->right!= NULL){
		
		a->height = std::max(a->left->height,a->right->height) +1;
		a->diff = a->right->height - a->left->height; 
	}
	
	else{
	
		if(a->left==NULL){
		
			a->height = a->right->height +1;
			a->diff =1;
		}
		
		else if(a->right == NULL){
		
			a->height = a->left->height +1;
			a->diff = -1;
		}
	}
	
	
	
	if(c->left == NULL && c->right == NULL){
	
		c->height = 0;
		c->diff = 0;
	}
	
	else if(c->left != NULL && c->right!= NULL){
		
		c->height = std::max(c->left->height,c->right->height) +1;
		c->diff = c->right->height - c->left->height; 
	}
	
	else{
	
		if(c->left==NULL){
		
			c->height = c->right->height +1;
			c->diff =1;
		}
		
		else if(c->right == NULL){
		
			c->height = c->left->height +1;
			c->diff = -1;
		}
	}
	
	updateHeight(c);
}


void MapAVL::balance(Nodo* n){

	if(n->diff > 0){
	
		if(n->right->diff < 0){
			
			leftRightRotation(n);
			
		}
			
		else{
			
			leftRotation(n);
		}	
	}
		
	else if(n->diff < 0){
	
		if(n->left->diff > 0){
			
			rightLeftRotation(n);
		}
		
		else{
		
			rightRotation(n);
		}
	}
}


void MapAVL::updateHeight(Nodo* n){
	
	if(n == NULL) return;

	if(n->father->left == NULL || n->father->right == NULL){

		n->father->height = n->height +1;
		
		if(n->father->left == NULL){
		
			n->father->diff += 1;
		}
		
		else if(n->father->right == NULL){
		
			n->father->diff -= 1;
		}
	
	}
	
	else{
	
		n->father->height = std::max(n->father->left->height, n->father->right->height) +1;
		
		n->father->diff = n->father->right->height - n->father->left->height;
	}
	
	
	if(n->father->diff < (-1) || n->father->diff > 1){
	
		balance(n->father);
//		return;
	}
	
	n = n->father;
	
	if(n!=root) updateHeight(n);

}

void MapAVL::insert(std::pair<std::string,int> p){

	if(root == NULL){

    	root = new Nodo();
    	root->key = p.first;
    	root->data = p.second;


		root->height = 0;
		
		root->diff = 0;
		
		current = root;

		tam++;
    }

	else{

		if( (current->key).compare(p.first) > 0 ){

			if(current->left == NULL){
				
				current->left = new Nodo();

				current->left->father = current;
				current->left->key = p.first;
				current->left->data = p.second;

				current->left->height = 0;
				
				current->left->diff = 0;
				
				updateHeight(current->left);				
				
				tam++;

				current = root;
			}

			else{
			
				current = current->left;
				insert(p);
			}
		}

		else if((current->key).compare(p.first) < 0 ){

			if(current->right == NULL){
				
				//std::cout<<" Right";
				
				current->right = new Nodo();
				current->right->father = current;
				current->right->key = p.first;
				current->right->data = p.second;
				
				current->right->height = 0;
				
				current->right->diff = 0;
				
				updateHeight(current->right);				
				
				current = root;  

				tam++;
			}

			else{
			
				current = current->right;
				insert(p);
			}
		}

		else{

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
	
	bool fr = false;
	
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
	
		if(current->left == NULL && current->right == NULL){
		
			if(current == root){
				
				fr = true;
			
			}
		
			else if(current == current->father->left){
			
					
				current->father->left = NULL;


			}
			
			else if(current = current->father->right){
			
				current->father->right = NULL;
		
			}
			
			updateHeight(current->father);
			
			delete current;
		}
		
		
		else if(current->left == NULL || current->right == NULL){
		
			if(current->left == NULL){
			
				current->father->right = current->right;
				
				current->right->father = current->father;
				
				updateHeight(current->father->right);

			
			}
			
			else if(current->right == NULL){
			
				current->father->left = current->left;
				
				current->left->father = current->father;
				
				updateHeight(current->father->left);

			}
	
			delete current;
		}
		
		else{
			
			Nodo* up;
			
			Nodo* newCurrent = current->right;
	
			
			while(newCurrent->left!=NULL){
			
				newCurrent = newCurrent->left;
			}
			
			newCurrent->father->left = newCurrent->right;
			
			if(newCurrent->right!=NULL){
			
				newCurrent->right->father = newCurrent->father;
				up = newCurrent->right;
			}
			
			else{
			
				up = newCurrent->father;
			
			}
			
			newCurrent->father = current->father;
			
			newCurrent->left = current->left;
			
			newCurrent->right = current->right;
			
			if(current->left!=NULL){
			
				current->left->father = newCurrent;
			}
			
			if(current->right!=NULL){
			
				current->right->father = newCurrent;
			}
			
			if(current == root){
			
				root = newCurrent;
			}
			
			else if(current == current->father->right){
			
				current->father->right = newCurrent;
			}
			
			else if(current == current->father->left){
			
				current->father->left = newCurrent;
			}
			
			updateHeight(up);
			
			delete current;						
		
		}
		
		tam--;

	}
}


int MapAVL::size(){
	
	//Se entrega la cantidad de elementos existentes
	return tam;
}

bool MapAVL::empty(){

	return tam==0?true:false;
}

