#include "LinkedList.h"

template<typename T>
class Nodo{
    private:
		// Definition Complexity O(1)
    	T data;
        Nodo<T>* left;
        Nodo<T>* right;
        template<typename U>
        friend class BST;
    public:
		// Constructor O(1)
        Nodo(T data){
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }
};

template<typename T>
class BST{
	private:
	// Definition Complexity O(1)
	Nodo<T> * root;

	// insertion 			O(n)
	void insert(Nodo<T> * & nodo, T data){
		if(nodo== NULL)		// O(1)
		{
			nodo = new Nodo<T>(data);
		}
		else	// O(n)
		{
			if(data < nodo->data)		// O(1)
			{
				insert(nodo->left, data);	// O(n)
			}
			else if(data > nodo->data)	// O(1)
			{
				insert(nodo->right, data);	// O(n)
			}
		}
	}

	// search				O(n)
	bool search(Nodo<T> * & nodo, T data){
		if (nodo == NULL)	// O(1)
		{
			return false;	// O(1)
		}
		else if (nodo->data == data)	// O(1)
		{
			return true;	// O(1)
		}
		else if (data > nodo->data)		// O(1)
		{
			return search(nodo->right, data);	// O(n)
		}
		else	// O(1)
		{
			return search(nodo->left, data);	// O(n)
		}
	}

	// preOrden				O(n)
	void preOrden(Nodo<T> * & nodo){
		if(nodo != NULL)	// O(1)
		{
			cout << nodo-> data << ":";	// O(1)
			preOrden(nodo->left);		// O(n)
			preOrden(nodo->right);		// O(n)
		}
	}

	// postOrden			O(n)
	void postOrden(Nodo<T> * & nodo){
		if(nodo != NULL)	// O(1)
		{
			postOrden(nodo->left);		// O(n)
			postOrden(nodo->right);		// O(n)
			cout << nodo-> data << ":";	// O(1)
		}
	}

	// InOrden				O(n)
	void inOrden(Nodo<T> * & nodo){
		if(nodo != NULL)	// O(1)
		{
			inOrden(nodo->left);		// O(n)
			cout << nodo-> data << ":";	// O(1)
			inOrden(nodo->right);		// O(n)
		}
	} 

	// Length				O(n)
	int length(Nodo<T> * &nodo) {
		if(nodo == NULL) {	// O(1)
			return 0;		// O(1)
		} else {
			int num = 1;	// O(1)
			num += length(nodo->left);		// O(n)
			num += length(nodo->right);		// O(n)
			return num;		// O(1)
		}
	}

	// max					O(n)
	T max(Nodo<T> * &nodo) {
		if (this->isEmpty()){	// O(1)
			throw -1;			// O(1)
		}
		Nodo<T> * aux = nodo;
		while(aux->right != NULL) {	// O(n)
			aux = aux->right;		// O(1)
		}
		return aux->data;	// O(1)
	}

	// min					O(n)
	T min(Nodo<T> * &nodo) {
		if (this->isEmpty()){	// O(1)
			throw -1;			// O(1)
		}
		Nodo<T> * aux = nodo;
		while(aux->left != NULL) {	// O(n)
			aux = aux->left;		// O(1)
		}
		return aux->data;	// O(1)
	}

	// Flatten				O(n)
	void flatten(Nodo<T> * & nodo, LinkedList<T> &list) {
		if(nodo != NULL){	// O(1)
			list.addLast(nodo->data);	// O(n)
			flatten(nodo->left, list);	// O(n)
			flatten(nodo->right, list);	// O(n)
		}	
	}

	public:
	BST(){
		root = NULL;	//	O(1)
	}

	T first()
	{
		return this->root->data;
	}

	void insert(T data){		// O(n)
		if(isEmpty()){
			root = new Nodo<T>(data);	// O(1)
		}else{
			insert(root, data);			// O(n)
		}
	}

	bool search(T data){	// O(n)
		return search(this->root, data);	// O(n)
	}

	bool isEmpty(){			// O(n)
		return root == NULL;	// O(n)
	}

	// preOrden()		O(n)
	void preOrden(){
		preOrden(root);		// O(n)
	}
	// postOrden()		O(n)
	void postOrden(){
		postOrden(root);	// O(n)
	}
	// inOrden()		O(n)
	void inOrden(){
		inOrden(root);	// O(n)
	}

	// length()			O(n)
	int lenght(){
		if(this->isEmpty()) {	// O(1)
			return 0;			// O(1)
		}
		return length(root);	// O(n)
	}

	T max() {	// O(n)
		return (max(this->root));	// O(n)
	}

	T min() {	// O(n)
		return (min(this->root));	// O(n)
	}
};