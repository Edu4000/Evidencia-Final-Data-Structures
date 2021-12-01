#include <iostream>
using namespace std;

template<typename var>
class Node {
	private:
		var data;
		Node<var>* nextPtr;
		Node<var>* prevPtr;
		template<typename T>
		friend class LinkedList;

	public:
		Node(var data) {
			this->data = data;		// O(1)
			this->nextPtr = NULL;	// O(1)
			this->prevPtr = NULL;	// O(1)
		}
};

template<typename var>
class LinkedList {
	private:
	Node<var>* header;
	Node<var>* last;
	bool containsRecursivo(var data, Node<var> * ptr) {
		if (ptr == NULL)
		{
			return false;
		}
		else if(data == ptr->data)
		{
			return true;
		}
		return containsRecursivo(data, ptr->nextPtr);
	}

	int lastIndexOfRecursivo(int index, var data, Node<var> * ptr) {
		if (ptr == NULL)
		{
			return NULL;
		}
		else if(data == ptr->data)
		{
			return index;
		}
		return lastIndexOfRecursivo(index - 1, data, ptr->prevPtr);
	}

	int indexOfRecursivo(int index, var data, Node<var> * ptr) {
		if (ptr == NULL)
		{
			return NULL;
		}
		else if(data == ptr->data)
		{
			return index;
		}
		return indexOfRecursivo(index + 1, data, ptr->nextPtr);
	}

	public:
	// Constructor
	LinkedList(Node<var>* header) {
		this->header = header;
		this->last = header;
	}

	// Add First
	void addFirst(var data) {
		Node<var>* new_node = new Node<var>(data);
		if (header == NULL) {	// Linked list is empty
			header = last = new_node;
		} else {	// It points to one node
			new_node->nextPtr = header;
			header->prevPtr = new_node;
			header = new_node;
		}
	}

	// Add Last							O(n)
	void addLast(var data) {
		Node<var>* curr = header; // Current (temporal) pointer for iteration starts in the header pointer
		Node<var>* new_node = new Node<var>(data); // pointer to a new Node with data is created
		if (this->is_empty() == true) {
			header = last = new_node;
		} else {
			last->nextPtr = new_node;
			new_node->prevPtr = last;
			last = new_node;
		}
	}

	// Is Empty							O(1)
	bool is_empty(){
		return header == NULL ? true : false;	// O(1)
	}

	// Contains							O(n)
	bool contains(var data) {
		Node<var>* ptr = this->header;	// O(1)
		while (ptr != NULL) {			// O(n)
			if (ptr->data == data) {	// O(1)
				return true;			// O(1)
			}
			ptr = ptr->nextPtr;			// O(n)
		}
		return false;					// O(1)
	}

	// Get								O(n)
	var get(int index) {
		try {						// O(1)
			if (index < 0) {		// O(1)
				throw (index);		// O(1)
			} else {
				Node<var>* ptr = header;	// O(1)
				int i = 0;					// O(1)
				while (ptr != NULL) {		// O(n)
					if(i == index) {		// O(1)
						return ptr->data;	// O(1)
					}
					i++;					// O(1)
					ptr = ptr->nextPtr;		// O(1)
				}
				throw (index);	// O(1)
			}
		} catch (int index) {
			if (index < 0) {	// O(1)
				cout << "Error: Index must be above 0" << endl;			// O(1)
			} else {
				cout << "Error: Index out of bounds" << endl;			// O(1)
			}
			return NULL;
		}
	}

	// Remove Front  					O(1)
	var remove_front(){
		try {                        // O(1)
			if (header == last) {	 // O(1)
				var deletedNode = header->data;
				delete header;
				header = NULL;
				last = NULL;
				return deletedNode;
			}
			else if (header != NULL) {    // O(1)
				var deletedNode = header->data;
				header = header->nextPtr;
				header->prevPtr = NULL;
				return deletedNode;
			}
			else {            // O(1)
				throw;
			}
		}
		catch(std::length_error) {     // O(1)
			cout << "Lista vacía";
		}
	}

	// Remove Last						O(n)
	var remove_last() {
		Node<var>* ptr = header;			// O(1)
		Node<var>* ptr2 = header->nextPtr;	// O(1)
		while(ptr2->nextPtr != NULL) {		// O(n)
			ptr = ptr->nextPtr;				// O(1)
			ptr2 = ptr2->nextPtr;			// O(1)
		}
		ptr->nextPtr = NULL;
		last = ptr;
		return ptr2->data;
	}

	// Add At							O(n)
	void add_at(var data, int index) {
		try {						// O(1)
			if (index < 0) {		// O(1)
				throw (index);		// O(1)
			} else {
				Node<var>* ptr = header;
				Node<var>* ptr2;	// O(1)
				if (index == 0) {
					ptr2 = ptr;
					header = new Node<var>(data);
					header->nextPtr = ptr2;
					return;
				} else {
					int i = 1;					// O(1)
					while (ptr != NULL) {		// O(n)
						if(i == index) {		// O(1)
							ptr2 = ptr->nextPtr;				// O(1)
							ptr->nextPtr = new Node<var>(data);	// O(1)
							ptr->nextPtr->nextPtr = ptr2;		// O(1)
							return;
						}
						i++;					// O(1)
						ptr = ptr->nextPtr;		// O(1)
					}
					throw (index);	// O(1)
				}
			}
		} catch (int index) {
			if (index < 0) {	// O(1)
				cout << "Error: Index must be above 0" << endl;			// O(1)
			} else {
				cout << "Error: Index out of bounds" << endl;			// O(1)
			}
		}
	}

	// Size
	int size() {
		Node<var>* curr = header;
		int i = 0;
		while (curr != NULL) {
			i++;
			curr = curr->nextPtr;
		}
		return i;
	}

	// Print
	void print() {
		Node<var>* ptr = header;
		while(ptr != NULL) {
			cout << ptr->data << ":";
			ptr = ptr->nextPtr;
		}
		cout << endl;
	}

	// Reverse Print
	void reverse() {
		Node<var>* ptr = last;
		while(ptr != NULL) {
			cout << ptr->data << ":";
			ptr = ptr->prevPtr;
		}
		cout << endl;
	}

	// Get First
	var get_first() {
		if (header != NULL) {
			return header->data;
		} else {
			return var();
		}
	}

	// Get Last
	var get_last() {
		if (header != NULL) {
			return last->data;
		} else {
			return var();
		}
	}

	// Peek First
	var peekFirst() {
		if (header != NULL) {
			return header->data;
		} else {
			return var();
		}
	}

	// Peek Last
	var peekLast() {
		if (header != NULL) {
			return last->data;
		} else {
			return var();
		}
	}

	// Metodos Recursivos Definidos en Private de LinkedList
	// Contains V2
	bool containsV2(var data) {
		return containsRecursivo(data, header);
	}

	// Last Index Of
	int lastIndexOf(var data) {
		return lastIndexOfRecursivo(-1, data, last);
	}

	// Index
	int indexOf(var data) {
		return indexOfRecursivo(0, data, header);
	}

	// Metodos Adicionales Para Challenge (Reducen la complejidad comparado con el main)
	// Sum								O(n)
	int sum() {
		Node<var>* ptr = this->header;	// O(1)
		int res = 0;					
		while (ptr != NULL) {			// O(n)
			res += ptr->data;			// O(1)
			ptr = ptr->nextPtr;			// O(1)
		}
		return res;	
	}

	// Maximum Node						O(n)
	var max() {
		Node<var>* ptr = this->header;	// O(1)
		var res = ptr->data;					
		while (ptr != NULL) {			// O(n)
			if(res < ptr->data) {		// O(1)
				res = ptr->data;		// O(1)
			}
			ptr = ptr->nextPtr;			// O(1)
		}
		return res;
	}

	// Maximum Node						O(n)
	var min() {
		Node<var>* ptr = this->header;	// O(1)
		var res = ptr->data;					
		while (ptr != NULL) {			// O(n)
			if(res > ptr->data) {		// O(1)
				res = ptr->data;		// O(1)
			}
			ptr = ptr->nextPtr;			// O(1)
		}
		return res;
	}

	// Methods for a Stack
	// Push
	void push(var data) {
		this->addFirst(data);
	}

	// Pop
	var pop() {
		return this->remove_front();
	}

	var peak() {
		return this->header->data;
	}

	// Methods for a Queue
	// Queue
	void queue(var data) {
		this-> addLast(data);
	}

	// Dequeue
	var dequeue() {
		try {                       // O(1)
			if (header == last) {	// O(1)   Only one data in queue
				var deletedNode = header->data;
				header = NULL;
				last = NULL;
				return deletedNode;
			}
			else if (header != NULL) {    // O(1)
				var deletedNode = header->data;
				header = header->nextPtr;
				header->prevPtr = NULL;
				return deletedNode;
			}
			else {            // O(1)
				throw;
			}
		}
		catch(std::length_error) {     // O(1)
			cout << "Lista vacía";
		}
	}

	// Dequeue Max
	var dequeueMax() {
		try {                       // O(1)
			if (header == last) {	// O(1)   Only one data in queue
				var deletedNode = header->data;
				header = NULL;
				last = NULL;
				return deletedNode;
			}
			else if (header != NULL) {    // O(1)
				Node<var>* ptr = header;
				Node<var>* ptr2;
				var max = this->max();

				while(ptr->nextPtr != NULL) {
					if (ptr->data == max) {
						if (ptr == header) {
							return this->remove_front();
						} else if (ptr == last) {
							return this->remove_last();
						} else {
							ptr2->nextPtr = ptr->nextPtr;
							ptr->nextPtr->prevPtr = ptr2;
							delete ptr;
							return max;
						}
					}
					ptr2 = ptr;
					ptr = ptr->nextPtr;
				}
			}
			else {            // O(1)
				throw;
			}
		}
		catch(std::length_error) {     // O(1)
			cout << "Lista vacía";
		}
	}

	// Dequeue Max
	var dequeueMin() {
		try {                       // O(1)
			if (header == last) {	// O(1)   Only one data in queue
				var deletedNode = header->data;
				header = NULL;
				last = NULL;
				return deletedNode;
			}
			else if (header != NULL) {    // O(1)
				Node<var>* ptr = header;
				Node<var>* ptr2;
				var min = this->min();

				while(ptr != NULL) {
					if (ptr->data == min) {
						if (ptr == header) {
							return this->remove_front();
						} else if (ptr == last) {
							return this->remove_last();
						} else {
							ptr2->nextPtr = ptr->nextPtr;
							ptr->nextPtr->prevPtr = ptr2;
							delete ptr;
							return min;
						}
					}
					ptr2 = ptr;
					ptr = ptr->nextPtr;
				}
			}
			else {            // O(1)
				throw;
			}
		}
		catch(std::length_error) {     // O(1)
			cout << "Lista vacía";
		}
	}

	var dequeueMaxO() {
		if (is_empty() == true)
		{
			throw -1;
		}
		var max = this->max(); // Este es el indice con valor minimo
		Node<var> * curr = header;
		Node<var> * next = NULL;
		while (true)
		{
			next = curr->nextPtr;
			if (next->data == max)
			{
				curr->nextPtr->nextPtr = next->nextPtr;
				next->prevPtr = curr;
				return max;
			}
			curr = curr->nextPtr;
		}
	}
};