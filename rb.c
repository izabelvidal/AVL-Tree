#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

void start(tree *root) {
	*root = NULL;
}

void insert(int key, tree *root) {
	tree position, parent, nil;
	position = *root;
	parent = NULL;

	while(position != NULL) {
			parent = position;
			if(key > position->data) 
					position = position->right;
			else 
					position = position->left;
	}

	nil = (tree) malloc(sizeof(struct Node));
	nil->data = key;
	nil->left = NULL;
	nil->right = NULL;
	nil->parent = parent;
	nil->color = RED;

	if(is_root(nil))	
			*root = nil;
	else {
		if(key > parent->data)
			parent->right = nil;
		else
			parent->left = nil;
	}

	adjust(root, nil);
}

enum color color(tree element) {
	enum color c;
	if(element == NULL || element->color == BLACK){
		c = BLACK;
	}else if(element->color == RED){
		c = RED;
	}else{
		c = DUBLEBLACK;
	}
	return c;
}

int is_root(tree element){
	return (element->parent == NULL);
}

int is_left(tree element){
	return (element->parent != NULL && element == element->parent->left);
}

tree uncle(tree element){
	return sibiling(element->parent);
}

tree sibiling(tree element){
	if(is_left(element))
		return element->parent->right;
	else
		return element->parent->left;
}

void adjust(tree *root, tree element){
	while(color(element->parent) == RED && color(element) == RED) {
			//caso 1: Cor do tio é vermelha, desce o preto do avô
			if(color(uncle(element)) == RED) {
				uncle(element)->color = BLACK;
				element->parent->color = BLACK;
				element->parent->parent->color = RED;				
				element = element->parent->parent;
				continue;
			} 
			//caso 2a: rotação simples direita
			if(is_left(element) && is_left(element->parent)) {
					rotate_right(root, element->parent->parent);
					continue;
			}
			//caso 2b: rotação simples esquerda
			if(!is_left(element) && !is_left(element->parent)) {

					rotate_left(root, element->parent->parent);
					continue;
            }
			//caso 3a: rotação dupla direita
			if(!is_left(element) && is_left(element->parent)){
					double_rotate_right(root, element->parent->parent);
					continue;
			}
			//caso 3b: rotação dupla esuqerda
			if(is_left(element) && !is_left(element->parent)){
					double_rotate_left(root, element->parent->parent);
					continue;
			}
	}

	(*root)->color = BLACK;
}

void rotate_right(tree *root, tree pivo){
			tree y;
			y = pivo->left;

			int position_pivo_left = is_left(pivo);
			
			//Atualização dos ponteiros
			pivo->left = y->right;
			y->right = pivo;

			y->parent = pivo->parent;
			pivo->parent = y;

			if(pivo->left != NULL)
				pivo->left->parent = pivo;

			//mudança das cores
			pivo->color = RED;
			y->color = BLACK;

			if(is_root(y))
				*root = y;
			else {
					if(position_pivo_left)
							y->parent->left = y;
					else
							y->parent->right = y;
			}
}
void rotate_left(tree *root, tree pivo){
			tree y;
			y = pivo->right;

			int position_pivo_left = is_left(pivo);
			
			//Atualização dos ponteiros
			pivo->right = y->left;
			y->left = pivo;

			y->parent = pivo->parent;
			pivo->parent = y;

			if(pivo->left != NULL)
				pivo->left->parent = pivo;

			//mudança das cores
			pivo->color = RED;
			y->color = BLACK;

			if(is_root(y))
				*root = y;
			else {
					if(position_pivo_left)
							y->parent->left = y;
					else
							y->parent->right = y;
			}
}
void double_rotate_right(tree *root, tree pivo){
			tree y;
			y = pivo->left;
			
			rotate_left(root,pivo->left);
			rotate_right(root,pivo);
			//mudança das cores
			pivo->color = RED;
			y->color = RED;
			pivo->parent->color = BLACK;
			
}
void double_rotate_left(tree *root, tree pivo){
			tree y;
			y = pivo->right;

			rotate_right(root,pivo->right);
			rotate_left(root,pivo);
			//mudança das cores
			pivo->color = RED;
			y->color = RED;
			pivo->parent->color = BLACK;
			
			
}

void print(tree root) {
	printf("(");
	if(root != NULL) {
		print_element(root);
		print(root->left);
		print(root->right);
	}
	printf(")");
}


int major_element(tree root) {
	if(root == NULL)
			return -1;
	if(root->right == NULL)
			return root->data;
	else
			return major_element(root->right);
}

void pre_order(tree root) {
	if(root != NULL) {
		print_element(root);
		pre_order(root->left);
		pre_order(root->right);
	}
}

void print_element(tree root) {
	if(root == NULL){
		printf("\x1b[30m[N]\x1b[0m");
	}else if(color(root) == BLACK){
		printf("\x1b[30m[%d]\x1b[0m", root->data);
	}else if(color(root) == RED){
		printf("\x1b[31m[%d]\x1b[0m", root->data);
	}else{
		printf("\x1b[32m[%d]\x1b[0m", root->data);
	}

}


tree search(int element, tree root){
	if(root == NULL) 
		return NULL;
	
	if(root->data == element) {
		return root;
	}	
	if(element > root->data) {
		return search(element, root->right);
	} else {
		return search(element, root->left);
	}
}

tree remove_cases(tree root, tree sub_root){
	int key = sub_root->data;
	sub_root->color = DUBLEBLACK;
	root = remove_aux(root, sub_root);
	root = remover(key, root);
	return root;
}

tree remove_normal(int key, tree root){
	
	if(root == NULL) 
		return NULL;
	
	if(root->data == key) {
		tree remo = search(key, root);

		if(root->left == NULL){

			if(color(remo) == BLACK){
				root->right->color = BLACK;
				return root->right;
			}else{
				return root->right;
			}
		}

		if(root->right == NULL){

			if(color(remo) == BLACK){
				root->left->color = BLACK;
				return root->left;
			}else{
				return root->left;
			}
			
		}

		root->data = major_element(root->left);
		if(color(remo) == BLACK){
			root->color == BLACK;
		}
		root->left = remover(root->data, root->left);
		return root;
	}	
	if(key > root->data) {
			root->right = remove_normal(key, root->right);
	} else {
			root->left = remove_normal(key, root->left);
	}
	return root;

}


tree remover(int key, tree root){
	tree sub_root = root;
	
	int flag = 1;
	while(flag == 1){
		if(sub_root == NULL){
			return root;
		}
		if(sub_root->data == key){

		
			if(color(sub_root) == BLACK && sub_root->left == NULL && sub_root->right == NULL){
				root = remove_cases(root, sub_root);
				return root;
				
			}else{
				root = remove_normal(key, root);
				flag = 0;
				return root;
			}
		}
		
		if(key > sub_root->data){
			sub_root = sub_root->right;
		} else {
			sub_root = sub_root->left;
		}
		
	
	}
	return root;
}	


tree remove_aux(tree root, tree element){
	while(color(element) == DUBLEBLACK){
		//caso 1
		if(is_root(element)){
			element->color = BLACK;
			return root;
		}
		//caso2a
		if(color(element->parent) == BLACK 
		&& color(element->parent->right) == RED
		&& color(element->parent->right->left) == BLACK 
		&& color(element->parent->right->right) == BLACK){
			root = case2a(root, element);
			element = search(element->data, root);
			continue;
			
		}
		//caso2b
		if(color(element->parent) == BLACK 
		&& color(element->parent->left) == RED 
		&& color(element->parent->left->right) == BLACK 
		&& color(element->parent->left->left) == BLACK){
			root = case2b(root, element);
			element = search(element->data, root);
			continue;
		}
		

		//caso3a
		if(color(element->parent) == BLACK 
		&& color(element->parent->right) == BLACK 
		&& color(element->parent->right->left) == BLACK 
		&& color(element->right->right->right) == BLACK){
			root = case3a(root, element);
			element = search(element->data, root);
			element = element->parent;
			continue;

			
		}

		
		//caso3b
		if(color(element->parent) == BLACK 
		&& color(element->parent->left) == BLACK 
		&& color(element->parent->left->right) == BLACK 
		&& color(element->parent->left->left) == BLACK){
			root = case3b(root, element);
			element = search(element->data, root);
			element = element->parent;
			continue;

		}
		//caso4a
		if(color(element->parent) == RED 
		&& color(element->parent->right) == BLACK 
		&& color(element->parent->right->left) == BLACK 
		&& color(element->parent->right->right) == BLACK){
			root = case4a(root, element);
			element = search(element->data, root);
			continue;
		}
		//caso4b
		if(color(element->parent) == RED 
		&& color(element->parent->left) == BLACK 
		&& color(element->parent->left->right) == BLACK 
		&& color(element->parent->left->left) == BLACK){
			root = case4b(root, element);
			element = search(element->data, root);
			continue;
		}
		
		//caso5a
		if(color(element->parent->right) == BLACK 
		&& color(element->parent->right->left) == RED 
		&& color(element->parent->right->right) == BLACK){
			root = case5a(root, element);
			element = search(element->data, root);
			continue;
		}
		//caso5b
		if(color(element->parent->left) == BLACK 
		&& color(element->parent->left->right) == RED 
		&& color(element->parent->left->left) == BLACK){
			root = case5b(root, element);
			element = search(element->data, root);
			continue;
		}

		//caso6a

		if(color(element->parent->right) == BLACK 
		&& color(element->parent->right->right) == RED){
			root = case6a(root, element);
			element = search(element->data, root);
			continue;
		}

		//caso6b
		if(color(element->parent->left) == BLACK 
		&& color(element->parent->left->left) == RED){
			root = case6b(root, element);
			element = search(element->data, root);
			continue;
		}
	}
	return root;
}

tree case2a(tree root, tree element){
	tree p, y;
	p = element->parent;
	y = p->right;
	
	int position_pivo_left = is_left(p);
	
	p->right = y->left;
	y->left = p;
	
	y->parent = p->parent;
	
	if(p->right != NULL){
		p->right->parent = p;
	}
	p->parent = y;

	p->color = RED;
	y->color = BLACK;
	
	if(is_root(y)){
		root = y;
	}else{
		if(position_pivo_left){
			y->parent->left = y;
		}else{
			y->parent->right = y;
		}
	}
	return y;

}

tree case2b(tree root, tree element){
	tree p, y;
	p = element->parent;
	y = p->left;
	
	int position_pivo_left = is_left(p);
	
	p->left = y->right;
	y->right = p;
	
	y->parent = p->parent;
	
	if(p->left != NULL){
		p->left->parent = p;
	}
	p->parent = y;

	p->color = RED;
	y->color = BLACK;
	
	if(is_root(y)){
		root = y;
	}else{
		if(position_pivo_left){
			y->parent->left = y;
		}else{
			y->parent->right = y;
		}
	}
	return y;

}

tree case3a(tree root, tree element){
	
	if(element->right == NULL && element->left == NULL){
		element->color = RED;
	}else{
		element->color = BLACK;
	}
	element->parent->color = DUBLEBLACK;
	element->parent->right->color = RED;
	
	return root;

}

tree case3b(tree root, tree element){
	
	if(element->right == NULL && element->left == NULL){
		element->color = RED;
	}else{
		element->color = BLACK;
	}
	element->parent->color = DUBLEBLACK;
	element->parent->left->color = RED;
	
	return root;

}

tree case4a(tree root, tree element){
	if(element->right == NULL && element->left == NULL){
		element->color = RED;
	}else{
		element->color = BLACK;
	}
	
	element->parent->color = BLACK;
	element->parent->right->color = RED;
	
	return root;

}

tree case4b(tree root, tree element){
	
	if(element->right == NULL && element->left == NULL){
		element->color = RED;
	}else{
		element->color = BLACK;
	}
	element->parent->color = BLACK;
	element->parent->left->color = RED;
	
	return root;

}

tree case5a(tree root, tree element){
	tree p, y;
	p = element->parent;
	y = p->right;
	
	p->right = y->left;
	y->left = y->left->right;
	p->right->right = y;
	
	p->right->parent = p;
	p->right->right->parent = p->right;
	
	p->right->color = BLACK;
	p->right->right->color = RED;
	
	return root;

}

tree case5b(tree root, tree element){
	tree p, y;
	p = element->parent;
	y = p->parent;
	
	p->left = y->right;
	y->right = y->right->left;
	p->left->left = y;
	
	p->left->parent = p;
	p->left->left->parent = p->left;
	
	p->left->color = BLACK;
	p->left->left->color = RED;
	
	return root;

}

tree case6a(tree root, tree element){
	tree p,y;
	p = element->parent;
	y = p->right;
	
	
	int position_pivo_left = is_left(p);
	
	p->right = y->left;
	y->left = p;
	y->parent = p->parent;
	
	if(p->right != NULL){
		p->right->parent = p;
	}
	p->parent = y;
	
	
	y->color = p->color;
	p->color = BLACK;
	y->right->color = BLACK;
	if(element->right == NULL && element->left == NULL){
		p->left->color = RED;
	}else{
		p->left->color = BLACK;
	}
	

	if(is_root(y)){
		root = y;
		return root;
	
	}else{
		if(position_pivo_left){
			y->parent->left = y;
		}else{

			y->parent->right = y;
		}
	}
	
	
	return root;

}

tree case6b(tree root, tree element){
	tree p, y;
	p = element->parent;
	y = p->left;
	
	int position_pivo_left = is_left(p);
	
	p->left = y->right;
	y->right = p;
	
	y->parent = p->parent;
	
	if(p->left != NULL){
		p->left->parent = p;
	}
	
	
	p->parent = y;

	y->color = p->color;
	p->color = BLACK;
	y->left->color = BLACK;
	
	if(element->right == NULL && element->right == NULL){
		p->right->color = RED;
	}else{
		p->right->color = BLACK;
	}
	
	
	if(is_root(y)){
		
		root = y;
		return root;
		
	}else{
		if(position_pivo_left){
			y->parent->left = y;
		}else{
			y->parent->right = y;
		}
	}
	return root;

}
