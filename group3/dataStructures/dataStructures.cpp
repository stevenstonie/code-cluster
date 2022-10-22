#include <iostream>
#include <vector>
#include <random>
#include <list>
#include <queue>

class DoublyLinkedList{
	class Node{
	public:
		int value = 0;
		Node* prev = nullptr, * next = nullptr;
	};
public:
	Node* head, * tail;
	int lengthOfList;
	DoublyLinkedList() :head(nullptr), tail(nullptr), lengthOfList(0){}

	void push_front(int value){
		Node* newNode = new Node;
		newNode->value = value;
		newNode->prev = nullptr;
		newNode->next = head;
		if(head == nullptr) tail = newNode;
		else head->prev = newNode;
		head = newNode;
		lengthOfList++;
	}

	void push_back(int value){
		Node* newNode = new Node;
		newNode->value = value;
		newNode->prev = tail;
		newNode->next = nullptr;
		if(tail == nullptr) head = newNode;
		else tail->next = newNode;
		tail = newNode;
		lengthOfList++;
	}

	void pop_front(){
		if(head == nullptr){
			std::cout << "cannot pop_front if there are no elements in the list.. \n";
			return;
		}
		else if(head == tail){
			delete head;
			head = tail = nullptr;
			lengthOfList = 0;
		}
		else{
			Node* kill = head;
			head = head->next;
			head->prev = nullptr;
			delete kill;
			lengthOfList--;
		}
	}

	void pop_back(){
		if(tail == nullptr){
			std::cout << "cannot pop_back if there are no elements in the list.. \n";
			return;
		}
		else if(tail == head){
			delete tail;
			tail = head = nullptr;
			lengthOfList = 0;
		}
		else{
			Node* kill = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete kill;
			lengthOfList--;
		}
	}

	Node* find(int value){
		Node* currNode = head;
		while(currNode != nullptr){
			if(currNode->value == value)
				return currNode;
			currNode = currNode->next;
		}
		std::cout << "the list doesnt have a node of value " << value << ".. \n";
		return nullptr;
	}

	void erase(Node* node){
		if(node == nullptr){
			std::cout << "cannot remove a node that does not exist.. \n";
			return;
		}
		else if(node == head) pop_front();
		else if(node == tail) pop_back();
		else{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;
			lengthOfList--;
		}
	}

	void remove(int value){
		Node* node = find(value);
		erase(node);
	}

	void insert_before(Node* givenNode, int value){
		if(givenNode == nullptr || givenNode == head)
			push_front(value);
		else{
			Node* newNode = new Node;
			newNode->value = value;
			newNode->prev = givenNode->prev;
			givenNode->prev->next = newNode;
			newNode->next = givenNode;
			givenNode->prev = newNode;
			lengthOfList++;
		}
	}

	bool checkIfEmpty(){
		if(head == nullptr) return true;
		else return false;
	}

	void clear(){
		while(head != nullptr) pop_front();
	}

	void print(){
		for(Node* node = head; node != nullptr; node = node->next)
			std::cout << node->value << " ";
		std::cout << "\n";
	}

	int size(){
		return lengthOfList;
	}

}DoublyLinkedList;

class SinglyLinkedList{
	class Node{
	public:
		std::string info;
		Node* next = nullptr;
	};
public:
	Node* head, * tail;
	int nbOfElem;
	SinglyLinkedList() :head(nullptr), tail(nullptr), nbOfElem(0){}

	void push(std::string newName){
		Node* newNode = new Node;
		if(head == nullptr)
			head = newNode;
		else
			tail->next = newNode;
		tail = newNode;
		newNode->info = newName;
		newNode->next = nullptr;
		nbOfElem++;
	}

	void pop(){
		if(head == nullptr){
			std::cout << "cannot delete an element if the list is empty.. \n";
			return;
		}
		else if(head == tail){
			delete head;
			head = tail = nullptr;
			nbOfElem = 0;
		}
		else{
			Node* kill = head;
			head = head->next;
			delete kill;
			nbOfElem--;
		}
	}

	Node* front(){
		return head;
	}

	Node* back(){
		return tail;
	}

	bool empty(){
		if(head == nullptr) return true;
		else return false;
	}

	void clear(){
		while(head != nullptr)
			pop();
		std::cout << "cleared the list. \n";
	}

	int size(){
		return nbOfElem;
	}
}SinglyLinkedList;

class HashTableWithLists{
	int lengthOfTable, nbOfEntries;
	std::list<std::pair<int, int>>* table;
public:
	HashTableWithLists(int n) :lengthOfTable(getNextPrime(n)), nbOfEntries(0){
		table = new std::list<std::pair<int, int>>[lengthOfTable];
	}

	void insertItem(std::pair<int, int> pair){
		if(find(pair.first) == nullptr){
			++nbOfEntries;
			if(nbOfEntries > lengthOfTable)
				rehash();
			int index = hashFunction(pair.first);
			table[index].push_back(pair);
		}
		else
			std::cout << "the key " << pair.first << " already exists.. \n";
	}

	int* find(int key){
		int index = hashFunction(key);
		std::list<std::pair<int, int>>::iterator currPair;
		for(currPair = table[index].begin(); currPair != table[index].end(); currPair++)
			if(currPair->first == key)
				return &currPair->first;
		return nullptr;
	}

	void deleteItem(int key){
		if(&key == nullptr) return;
		nbOfEntries--;
		int i = hashFunction(key);
		std::list<std::pair<int, int>>::iterator pair;
		for(pair = table[i].begin(); pair != table[i].end(); pair++)
			if(pair->first == key)
				break;
		if(pair != table[i].end())
			table[i].erase(pair);
	}

	void printTable(){
		for(int i = 0; i < lengthOfTable; i++){
			std::cout << i;
			for(auto pair : table[i])
				std::cout << " --> " << pair.first << " " << pair.second;
			std::cout << "\n";
		}
	}

	void rehash(){
		std::list<std::pair<int, int>>* newTable;
		int oldLengthOfTable = lengthOfTable;
		lengthOfTable = getNextPrime(lengthOfTable * 2);		//make 'lenOfTable' the new one so hashFunction() can work with it
		newTable = new std::list<std::pair<int, int>>[lengthOfTable];
		for(int i = 0; i < oldLengthOfTable; i++){
			std::list<std::pair<int, int>>::iterator pair;
			for(pair = table[i].begin(); pair != table[i].end(); pair++){
				int index = hashFunction(pair->first);
				std::pair<int, int> copyPair(pair->first, pair->second);
				newTable[index].push_back(copyPair);
			}
		}
		delete[] table;
		table = newTable;
	}

	int hashFunction(int x){
		return x % lengthOfTable;
	}

	bool isEmpty(){
		for(int i = 0; i < lengthOfTable; i++)
			if(table[i].size() > 0)
				return false;
		return true;
	}

	bool checkIfPrime(int number){
		if(number == 0 || number == 1)
			return false;
		if(number == 2 || number == 3)
			return true;
		if(number % 2 == 0)
			return false;
		for(int d = 5; d < number / 2; d += 2)
			if(number % d == 0)
				return false;
		return true;
	}

	int getNextPrime(int number){
		if(number % 2 == 0)
			number++;
		while(!checkIfPrime(number))
			number += 2;
		return number;
	}

	void clearTable(){
		delete[] table;
		table = nullptr;
		lengthOfTable = 0;
		nbOfEntries = 0;
	}

	~HashTableWithLists(){
		if(!isEmpty())
			clearTable();
	}

}HashTable1(5);

class HashTableWithOpenAdressing{

};
//make a hashtable with open adressing!!!!

class BinaryTree{
	class Node{
	public:
		int value;
		Node* left, * right, * parent;
	};

	int getHeightOfSubtree(Node* node){
		if(node == nullptr) return 0;
		int left_height = getHeightOfSubtree(node->left);
		int right_height = getHeightOfSubtree(node->right);
		if(left_height > right_height) return left_height;
		else return right_height;
	}

	void printInorder(Node* node){
		if(node != nullptr){
			printInorder(node->left);
			std::cout << node->value << " ";
			printInorder(node->right);
		}
	}

	void printPreorder(Node* node){
		if(node != nullptr){
			std::cout << node->value << " ";
			printPreorder(node->left);
			printPreorder(node->right);
		}
	}

	void printPostorder(Node* node){
		if(node != nullptr){
			printPostorder(node->left);
			printPostorder(node->right);
			std::cout << node->value << " ";
		}
	}

	void printAllLeaves(Node* node){
		if(node->left != nullptr) printAllLeaves(node->left);
		if(node->right != nullptr) printAllLeaves(node->right);
		if(node->left == nullptr && node->right == nullptr)
			std::cout << node->value << " ";
	}

	int findDepthOfNode(Node* node, int value, int depth){
		if(node == nullptr)
			return -1;
		else{
			if(node->value == value) return depth;
			return std::max(findDepthOfNode(node->left, value, depth + 1),
							findDepthOfNode(node->right, value, depth + 1));
		}
	}
public:
	Node* root;
	BinaryTree() :root(nullptr){}

	void readTree(){
		std::vector<int> arr{7, 4, 9, -1, 8, 11, 2, -1, -1, 13, -1, 6, 9};
		root = new Node;
		root->value = arr[0];
		root->parent = nullptr;
		std::queue<Node*> q;
		q.push(root);
		for(int i = 1; i < arr.size(); i += 2){
			if(arr[i] == -1)
				q.front()->left = nullptr;
			else{
				Node* newNode = new Node;
				newNode->value = arr[i];
				newNode->parent = q.front();
				q.front()->left = newNode;
				q.push(newNode);
			}
			if(i + 1 >= arr.size() || arr[i + 1] == -1)
				q.front()->right = nullptr;
			else{
				Node* newNode = new Node;
				newNode->value = arr[i + 1];
				newNode->parent = q.front();
				q.front()->right = newNode;
				q.push(newNode);
			}
			q.pop();
		}
		while(q.size() > 0){
			q.front()->left = q.front()->right = nullptr;
			q.pop();
		}
	}

	void printHeightOfSubtree(Node* node){
		std::cout << getHeightOfSubtree(node) << "\n";
	}

	void printInorder(){
		printInorder(root);
		std::cout << "\n";
	}

	void printPreorder(){
		printPreorder(root);
		std::cout << "\n";
	}

	void printPostorder(){
		printPostorder(root);
		std::cout << "\n";
	}

	void printByLevel(){
		std::queue<Node*> q;
		if(root != nullptr)
			q.push(root);
		while(q.empty() == false){
			Node* node = q.front();
			std::cout << node->value << " ";
			q.pop();
			if(node->left != nullptr)
				q.push(node->left);
			if(node->right != nullptr)
				q.push(node->right);
		}
		std::cout << "\n";
	}

	void printAllLeaves(){
		printAllLeaves(root);
		std::cout << "\n";
	}

	void printDepthOfNode(int value){
		int depth = findDepthOfNode(root, value, 0);
		if(depth == -1)
			std::cout << "the node doesnt exist..\n";
		else
			std::cout << "the depth of the node is: " << depth << " \n";
	}

	~BinaryTree(){

	}
}BinaryTree;

class BinarySearchTree{
	class Node{
	public:
		int value;
		Node* left, * right, * parent;
		Node(int value) :value(value), left(nullptr), right(nullptr), parent(nullptr){}
	};
	Node* root;

	Node* insert(int value, Node* node){
		if(node == nullptr)
			return new Node(value);
		if(value < node->value){
			node->left = insert(value, node->left);
			node->left->parent = node;
		}
		else if(value > node->value){
			node->right = insert(value, node->right);
			node->right->parent = node;
		}
		return node;
	}

	int maxNode(Node* node){
		Node* rightmostNode = node;
		while(rightmostNode->right != nullptr)
			rightmostNode = rightmostNode->right;
		return rightmostNode->value;
	}

	int minNode(Node* node){
		Node* leftmostNode = node;
		while(leftmostNode->left != nullptr)
			leftmostNode = leftmostNode->left;
		return leftmostNode->value;
	}

	Node* successor(Node* node){
		if(node == nullptr || node->right == nullptr) return nullptr;
		Node* succ = node->right;
		while(succ->left != nullptr)
			succ = succ->left;
		return succ;
	}

	Node* predecessor(Node* node){
		if(node == nullptr || node->left == nullptr) return nullptr;
		Node* pred = node->left;
		while(pred->right != nullptr)
			pred = pred->right;
		return pred;
	}

	Node* find(int value, Node* node){
		if(node == nullptr || value == node->value)
			return node;
		if(value < node->value)
			return find(value, node->left);
		if(value > node->value)
			return find(value, node->right);
	}

	void eraseNode(Node* node){
		if(node == nullptr){
			std::cout << "the node doesnt exist..\n";
			return;
		}
		if(node == root){
			if(root->left == nullptr && root->right == nullptr){
				delete root;
				root = nullptr;
			}
			else if(root->right == nullptr){
				root = root->left;
				delete root->parent;
				root->parent = nullptr;
			}
			else if(root->left == nullptr){
				root = root->right;
				delete root->parent;
				root->parent = nullptr;
			}
			else{
				Node* succ = successor(root);
				if(succ != root->right){
					succ->parent->left = nullptr;
					succ->right = root->right;
					root->right->parent = succ;
				}
				succ->parent = nullptr;
				succ->left = root->left;
				root->left->parent = succ;
				Node* kill = root;
				root = succ;
				delete kill;
			}
		}
		else{
			if(node->left == nullptr && node->right == nullptr){
				if(node == node->parent->left)
					node->parent->left = nullptr;
				else if(node == node->parent->right)
					node->parent->right = nullptr;
				delete node;
			}
			else if(node->right == nullptr){
				if(node == node->parent->left)
					node->parent->left = node->left;
				else if(node == node->parent->right)
					node->parent->right = node->left;
				node->left->parent = node->parent;
				delete node;
			}
			else if(node->left == nullptr){
				if(node == node->parent->left)
					node->parent->left = node->right;
				else if(node == node->parent->right)
					node->parent->right = node->right;
				node->right->parent = node->parent;
				delete node;
			}
			else{
				Node* succ = successor(node);
				if(succ != node->right){
					succ->parent->left = nullptr;
					succ->right = node->right;
					node->right->parent = succ;
				}
				if(node == node->parent->left)
					node->parent->left = succ;
				else if(node == node->parent->right)
					node->parent->right = succ;
				succ->parent = node->parent;
				succ->left = node->left;
				node->left->parent = succ;
				delete node;
			}
		}
	}

	void printTreeInorder(Node* node){
		if(node == nullptr) return;
		printTreeInorder(node->left);
		std::cout << node->value << " ";
		printTreeInorder(node->right);
	}

	void printTreePreorder(Node* node){
		if(node == nullptr) return;
		std::cout << node->value << " ";
		printTreePreorder(node->left);
		printTreePreorder(node->right);
	}

	void printTreePostorder(Node* node){
		if(node == nullptr) return;
		printTreePostorder(node->left);
		printTreePostorder(node->right);
		std::cout << node->value << " ";
	}
public:
	BinarySearchTree() : root(nullptr){}

	void insert(int value){
		root = insert(value, root);
	}

	void maxNode(){
		std::cout << "max node=" << maxNode(root) << "\n";
	}

	void minNode(){
		std::cout << "min node=" << minNode(root) << "\n";
	}

	void successorOfRoot(){
		Node* succ = successor(root);
		if(succ == nullptr) std::cout << "the specified node doesnt exist or it doesnt have a successor.. \n";
		else std::cout << "the specified node's successor is: " << succ->value << " \n";
	}

	void predecessorOfRoot(){
		Node* pred = predecessor(root);
		if(pred == nullptr) std::cout << "the specified node doesnt exist or it doesnt have a predecessor.. \n";
		else std::cout << "the specifies node's predecessor is: " << pred->value << " \n";
	}

	Node* find(int value){
		return find(value, root);
	}

	void deleteNode(int value){
		eraseNode(find(value));
	}

	void constructTree(std::vector<int> arr){
		for(int a : arr) insert(a);
	}

	bool isEmpty(){
		return root == nullptr;
	}

	void clear(){
		while(root != nullptr)
			eraseNode(root);
	}

	void printTreeInorder(){
		printTreeInorder(root);
		std::cout << "\n";
	}

	void printTreePreorder(){
		printTreePreorder(root);
		std::cout << "\n";
	}

	void printTreePostorder(){
		printTreePostorder(root);
		std::cout << "\n";
	}

	void printTreeByLevel(){
		std::queue<Node*> q;
		q.push(root);
		while(q.size() > 0){
			if(q.front()->left != nullptr){
				q.push(q.front()->left);
			}
			if(q.front()->right != nullptr){
				q.push(q.front()->right);
			}
			std::cout << q.front()->value << " ";
			q.pop();
		}
		std::cout << "\n";
	}

	~BinarySearchTree(){
		if(!isEmpty())
			clear();
	}
}BST;

class RedBlackTree{
	class Node{
	public:
		int value;
		Node* parent, * left, * right;
		bool color;	//0=black, 1=red
		Node(int value) :value(value), parent(nullptr), left(nullptr), right(nullptr), color(true){}
	};

	void rotateLeft(Node* x){
		Node* y = x->right;
		x->right = y->left;
		if(y->left != NIL)
			y->left->parent = x;
		y->parent = x->parent;
		if(y->parent == NIL)
			this->root = y;
		else if(x == x->parent->left)
			x->parent->left = y;
		else if(x == x->parent->right)
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rotateRight(Node* x){
		Node* y = x->left;
		x->left = y->right;
		y->parent = x->parent;
		if(y->parent == NIL)
			this->root = y;
		else if(x == x->parent->left)
			x->parent->left = y;
		else if(x == x->parent->right)
			x->parent->right = y;
		y->right = x;
		x->parent = y;
	}

	void rbTransplant(Node* u, Node* v){
		if(u->parent == NIL)
			this->root = v;
		else if(u == u->parent->left)
			u->parent->left = v;
		else if(u == u->parent->right)
			u->parent->right = v;
		v->parent = u->parent;
	}

	void insertFix(Node* node){
		if(node == root){
			node->color = 0;
			return;
		}
		if(node->parent = root)
			return;
		Node* uncle;
		while(node->parent->color == 1){
			if(node->parent == node->parent->parent->right){
				uncle = node->parent->parent->left;
				if(uncle->color == 1){
					uncle->color = 0;
					node->parent->color = 0;
					node->parent->parent->color = 1;
					node = node->parent->parent;
				}
				else{
					if(node == node->parent->left){
						node = node->parent;
						rotateRight(node);
					}
					node->parent->color = 0;
					node->parent->parent->color = 1;
					rotateLeft(node->parent->parent);
				}
			}
			else{
				uncle = node->parent->parent->right;

				if(uncle->color == 1){
					uncle->color = 0;
					node->parent->color = 0;
					node->parent->parent->color = 1;
					node = node->parent->parent;
				}
				else{
					if(node == node->parent->right){
						node = node->parent;
						rotateLeft(node);
					}
					node->parent->color = 0;
					node->parent->parent->color = 1;
					rotateRight(node->parent->parent);
				}
			}
			if(node == root)
				break;
		}
		root->color = 0;
	}
	//https://www.codesdope.com/course/data-structures-red-black-trees-insertion/

	///DISCONTINUED
	/*special case: node is root or root's child
	while the parent is red and not NIL
		case 1 - uncle is red ==> p_color is black, u_color is black, gp_color is red, node=gp (because gp and ggp may be both red)
		case 2 - uncle is black ==> check if node is a left or a right child. check if parent is a left or a right child.
			case 2.1 - angle (parent is left and node is right or parent is right and node is left)
				==> rotate the parent opposite of node
			case 2.2 - line (both parent and node are either right or left)
				==> rotate the gp opposite of node, p_color is black, gp_color is red
		if node is root break;
	root_color is black
	similar explanation: https://www.youtube.com/watch?v=5IBxA-bZZH8	*/
	/*void insertFix(Node* node){
		if(node == root){
			node->color = 0;
			return;
		}
		if(node->parent = root)
			return;
		Node* uncle;
		while(node->parent->color == 1){
			if(node->parent == node->parent->parent->left)
				uncle = node->parent->parent->right;
			else
				uncle = node->parent->parent->left;
			if(uncle->color == 1){		//case 1
				node->parent->color = 0;
				uncle->color = 0;
				node->parent->parent->color = 1;
				node = node->parent->parent;
			}
			else{						//case 2
				bool parent_position = 0, node_position = 0;	//0 is left, 1 is right
				if(node == node->parent->left)
					node_position = 0;
				else
					node_position = 1;
				if(node->parent == node->parent->parent->left)
					parent_position = 0;
				else
					parent_position = 1;
				if(node_position != parent_position){	//case 2.1
					if(node_position == 0) rotateRight(node->parent);
					else rotateLeft(node->parent);
				}
				else{									//case 2.2
					if(node_position == 0) rotateRight(node->parent->parent);
					else rotateLeft(node->parent->parent);
					node->parent->color = 0;
					node->parent->parent->color = 1;
				}
			}
			if(node == root)
				break;
		}
		root->color = 0;
	}*/

	void deleteFix(Node* node){
		Node* s;
		while(node != root && node->color == 0){
			if(node == node->parent->left){
				s = node->parent->right;
				if(s->color == 1){
					s->color = 0;
					node->parent->color = 1;
					rotateLeft(node->parent);
					s = node->parent->right;
				}
				if(s->left->color == 0 && s->right->color == 0){
					s->color = 1;
					node = node->parent;
				}
				else{
					if(s->right->color == 0){
						s->left->color = 0;
						s->color = 1;
						rotateRight(s);
						s = node->parent->right;
					}
					s->color = node->parent->color;
					node->parent->color = 0;
					s->right->color = 0;
					rotateLeft(node->parent);
					node = root;
				}
			}
			else{
				s = node->parent->left;
				if(s->color == 1){
					s->color = 0;
					node->parent->color = 1;
					rotateRight(node->parent);
					s = node->parent->left;
				}
				if(s->right->color == 0 && s->right->color == 0){
					s->color = 1;
					node = node->parent;
				}
				else{
					if(s->left->color == 0){
						s->right->color = 0;
						s->color = 1;
						rotateLeft(s);
						s = node->parent->left;
					}
					s->color = node->parent->color;
					node->parent->color = 0;
					s->left->color = 0;
					rotateRight(node->parent);
					node = root;
				}
			}
		}
		node->color = 0;
	}
	//https://www.codesdope.com/course/data-structures-red-black-trees-deletion/

	void clear(Node* node){
		if(node == NIL) return;
		clear(node->left);
		clear(node->right);
		delete node;
	}

	void printTreePreorder(Node* node){
		if(node != NIL){
			std::cout << node->value << " ";
			printTreePreorder(node->left);
			printTreePreorder(node->right);
		}
	}

	void printTreeInorder(Node* node){
		if(node != NIL){
			printTreeInorder(node->left);
			std::cout << node->value << " ";
			printTreeInorder(node->right);
		}
	}

	void printTreePostorder(Node* node){
		if(node != NIL){
			printTreePostorder(node->left);
			printTreePostorder(node->right);
			std::cout << node->value << " ";
		}
	}

	void printTree(Node* node, std::string indent, bool last){
		if(node != NIL){
			std::cout << indent;
			if(last){
				std::cout << "R----";
				indent += "   ";
			}
			else{
				std::cout << "L----";
				indent += "|  ";
			}

			std::string sColor = node->color ? "RED" : "BLACK";
			std::cout << node->value << "(" << sColor << ")" << std::endl;
			printTree(node->left, indent, false);
			printTree(node->right, indent, true);
		}
	}
public:
	Node* root, * NIL;
	RedBlackTree(){
		NIL = new Node(0);
		NIL->color = 0;
		NIL->left = NIL->right = nullptr;
		root = NIL;
		root->parent = NIL;
	}

	/*create the node and assign its attributes. find where it should be placed with 'x' as pos
	and 'y' as its parent. if the node is the root paint it black. insertFix(node)*/
	void insertNode(int value){
		Node* newNode = new Node(value);
		Node* y = NIL;
		Node* x = this->root;
		while(x != NIL){
			y = x;
			if(newNode->value < x->value)
				x = x->left;
			else
				x = x->right;
		}
		newNode->parent = y;
		if(y == NIL)
			root = newNode;
		else if(newNode->value < y->value)
			y->left = newNode;
		else
			y->right = newNode;
		insertFix(newNode);
	}
	//either this or insertFix may have some problems

	/*we need to delete a node 'z'. find it.
	if its found there are 2 cases (+save replacing node's color)
	case 1 - z has no children ==> case 2 (NIL is a left child basically)
	case 2 - z has 1 child ==> link its child to its grandparent
	case 3 - z has 2 children ==> the leftmost(smallest) node from z's right side is the replacing node 'y', save y's color
		==> assign 'x' as y's right child.
		case 3.1 - y is a child of z ==> link x to y
		case 3.2 - y is not a child of z ==> link x to gp, link y with z's right child
		==> link y with z's parent, link y with z's left child, y's color = z's color
	delete z
	if the original color of the replacing node (y) is black deleteFix(x);	*/
	void deleteNode(int value){
		Node* node_to_delete = this->root;
		while(node_to_delete != NIL){
			if(node_to_delete->value == value)
				break;
			if(value > node_to_delete->value)
				node_to_delete = node_to_delete->right;
			else if(value < node_to_delete->value)
				node_to_delete = node_to_delete->left;
		}
		if(node_to_delete == NIL){
			std::cout << "the value could not be found..\n";
			return;
		}
		bool origColor = node_to_delete->color;
		Node* auxNode;
		if(node_to_delete->left == NIL){
			auxNode = node_to_delete->right;
			rbTransplant(node_to_delete, auxNode);
		}
		else if(node_to_delete->right == NIL){
			auxNode = node_to_delete->left;
			rbTransplant(node_to_delete, auxNode);
		}
		else{
			Node* replacingNode = minimum(node_to_delete->right);
			origColor = replacingNode->color;
			auxNode = replacingNode->right;
			if(replacingNode->parent == node_to_delete)
				auxNode->parent = replacingNode;
			else{
				rbTransplant(replacingNode, auxNode);
				replacingNode->right = node_to_delete->right;
				node_to_delete->right->parent = replacingNode;
			}
			rbTransplant(node_to_delete, replacingNode);
			replacingNode->left = node_to_delete->left;
			replacingNode->left->parent = replacingNode;
			replacingNode->color = node_to_delete->color;
		}
		delete node_to_delete;
		if(origColor == 0)
			deleteFix(auxNode);
	}

	Node* predecessor(Node* node){
		if(node->left != NIL)
			return maximum(node->left);
		else
			return nullptr;
	}

	Node* successor(Node* node){
		if(node->right != NIL)
			return minimum(node->right);
		else
			return nullptr;
	}

	Node* findNode(int value){
		Node* node = root;
		while(node != NIL){
			if(node->value = value)
				break;
			else if(value < node->value)
				node = node->left;
			else
				node = node->right;
		}
		if(node->value == value) return node;
		return nullptr;
	}

	void clear(){
		clear(root);
		root = NIL;
	}

	bool isEmpty(){
		if(root == NIL) return true;
		else return false;
	}

	void construct(std::vector<int> arr){
		for(int a : arr)
			insertNode(a);
	}

	//returns the leftmost node on the branch
	Node* minimum(Node* node){
		while(node->left != NIL)
			node = node->left;
		return node;
	}

	//return the rightmost node on the branch
	Node* maximum(Node* node){
		while(node->right != NIL)
			node = node->right;
		return node;
	}

	~RedBlackTree(){
		if(!isEmpty())
			clear();
	}
}RBTree;
//https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
//https://medium.com/smucs/red-black-trees-in-c-a3453f1a7000

class OtherDataStructures{
public:
	//avl trees, b trees, queue, stack, graphs, map, set;
}skskskskskks;

int main(){

}