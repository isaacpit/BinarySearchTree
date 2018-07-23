#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include <stack>
#include <cmath>



using namespace std;

enum color {red, black};

template <typename T>
struct Node
{
	T value;
	Node<T>* left;
	Node<T>* right;
    Node<T>* parent;

    int search_time;
    color node_color; //don't need to worry about this for the regular BTree

    Node(int val = 0, Node<T>* l = NULL, Node<T>* r = NULL,  
		Node<T>* p = NULL, color col = black) 
		: value(val), left(l), right(r), parent(p), search_time(0), 
		node_color(col) {}

	Node(const Node<T>* other)
	{
		value = other->value;
		node_color = other->node_color;
		search_time = other->search_time;
	}

	bool is_leaf(){return (left == 0 && right == 0);}
};

template <typename T>
struct BTree
{
protected: 
	int size;
	int height = 0;
public:
	Node<T>* root;
	
	int getHeight() { return height; }
	int getSize() { return size; }
	
    BTree() : root(NULL),size(0), height(0) {}

	BTree(const BTree<T>& other);
	BTree<T> operator=(const BTree<T>& other);
	void deleteTree(Node<T> *root);
	Node<T>* get_root(){return root;}
	const Node<T>* get_root() const {return root;} 
	virtual Node<T>* insert(const T obj);
	Node<T>* search(int obj);
	void update_search_times();
	float get_average_search_time();
	ostream& inorder(ostream& out);
	virtual ostream& print_level_by_level(ostream& out);
	void print_val(Node<T>* node, int level = 1);
	void print_ref(Node<T>* node, int& level);
	virtual void pretty_print_node(ostream& out,Node<T>* node);


	ostream& level_helper(ostream& out, Node<T>* node);

private: 

	void delete_helper(Node<T>* node);
	Node<T>* copy_helper(Node<T> *node, const Node<T> *otherNode);

	virtual Node<T>* insert_helper(T obj, Node<T>* node);
	Node<T>* search_helper(T obj, Node<T>* node);
	ostream& inorder_helper(ostream& out, Node<T>* node);
	void update_search_times_helper(Node<T>* node, int depth);
	T get_total_search_time(Node<T>* node);


};

template <typename T>
ostream& operator<<(ostream& out, BTree<T> tree)
{

	if (tree.getSize() <= pow(2,4)) {
		tree.print_level_by_level(out);
		out << "tree size: " << tree.getSize() << endl;
		out << "average search cost: " << tree.get_average_search_time() << endl;
	}
	// else {
	// 	tree.print_level_by_level(out);
	// 	out << "tree size: " << tree.getSize() << endl;
	// 	out << "average search cost: " << tree.get_average_search_time() << endl;
	// }

	return out;
}

// template<typename T>
// void BTree<T>::print_val(Node<T>* node, int level) {
// 	if (node == get_root()) {
// 		level = 1;
// 	}
// 	if (node != NULL) {

// 		cout << "print_val : (" << node->value << ", " << level << ")" << endl;
// 		level++;
// 		cout << "node->val : " << node->value << "\ti: " << level << endl;
// 		print_val(node->right, level);
// 		cout << "node->val : " << node->value << "\ti: " << level << endl;
// 		level++;
// 		print_val(node->left, level);
// 	}

// 	return;
// }

template<typename T> 
void BTree<T>::print_ref(Node<T>* node, int& level) {
	if (node == get_root()) {
		level = 1;
	}
	if (node != NULL) {


		cout << "print_ref : (" << node->value << ", " << level << ")" << endl;
		++level;
		print_ref(node->right, level);
		// ++level;
		print_ref(node->left, level);
	}

}


template <typename T>
ostream& operator<<(ostream& out, Node<T> node)
{
	return out << "( " << node.value << ", " << node.search_time << ", " 
		<< node.node_color << " )";
}

template <typename T>
void BTree<T>::pretty_print_node(ostream& out,Node<T>* node)
{
	out << node->value << "["<<node->search_time<<"] ";
}

template <typename T>
istream& operator>>(istream& in, BTree<T>& tree)
{
	T temp;
	in >> temp;
	tree.insert(temp);
	return in;
}


template<typename T> 
Node<T>* BTree<T>::copy_helper(Node<T> *node, const Node<T> *otherNode) {
	if (otherNode != NULL) {
		Node<T>* newNode= new Node<T> (otherNode);
		insert(otherNode->value);

		if (otherNode->left != NULL) {
			Node<T>* newLeft = new Node<T>(otherNode->left);
			copy_helper(newLeft, otherNode->left);
		}
		if (otherNode->right != NULL) {
			Node<T>* newRight = new Node<T>(otherNode->right);
			copy_helper(newRight, otherNode->right);
		}
		return newNode;
	}
	else {
		return nullptr;
	}

}

template <typename T>
BTree<T>::BTree(const BTree<T>& other)
{
	/*
		complete this copy constructor
		make sure when copying nodes to copy
			the value
			the relative parent, and left and right children
			the node_color
				not important for this part but will be used later
	*/
	Node<T> *node = get_root();
	const Node<T> *otherNode = other.get_root();
	// pretty_print_node(cout, otherNode);
	deleteTree(node);
	copy_helper(node, otherNode);
	// inorder(cout);

}



template <typename T>
BTree<T> BTree<T>::operator=(const BTree<T>& other)
{

	/*
		complete this assignment operator
		make sure when copying nodes to copy
			the value
			the relative parent, and left and right children
			the node_color
				not important for this part but will be used later
				
	*/

	BTree<T> newTree(other);
	size = newTree.size;
	height = newTree.height;
	this->root = newTree.get_root();

	return newTree;
}

template<typename T>
void BTree<T>::deleteTree(Node<T> *node) {
	delete_helper(node);
}

template<typename T> 
void BTree<T>::delete_helper(Node<T> *node) {
	if (node != NULL) {
		delete_helper(node->left);
		delete_helper(node->right);
		delete node;
	}

}

template <typename T>
Node<T>* BTree<T>::insert_helper(T obj, Node<T>* curr)
{ 

    return nullptr;
}

template <typename T>
Node<T>* BTree<T>::insert(const T obj) 
{
	Node<T>* newNode = new Node<T>(obj);
	int i = 0;
	if (root == NULL) {
		root = newNode;
		root->search_time = i + 1;
		if (root->search_time > height) {
			height = root->search_time;
		}
		size++;
		return newNode;
	}
	else {
		++i;
	}
	bool go = true;
	Node<T>* p = root;
	while (go) {
		if (obj < p->value) {
			// case if the pointer is at a null space
			if (p->left == NULL) {
				newNode->search_time = i + 1;
				if (newNode->search_time > height) {
					height = newNode->search_time;
				}
				newNode->parent = p;
				p->left = newNode; 
				size++;
				go = false;
			}
			// case if the pointer must continue traversing 
			else {
				i++;
				p = p->left;
			}
		}
		else if (obj > p->value) {
			if (p->right == NULL) {
				newNode->search_time = i + 1;
				if (newNode->search_time > height) {
					height = newNode->search_time;
				}
				newNode->parent = p;
				size++;
				p->right = newNode;
				go = false;
			}
			else {
				i++;
				p = p->right;
			}
		}
	}
	return NULL;
}

template <typename T>
Node<T>* BTree<T>::search_helper(T obj, Node<T>* node)
{
	Node<T>* result;

	if (node->value == obj) {
		return node;
	}
	
	result = search_helper(obj, node->left);
	if (result != NULL) {
		return result;
	}

	result = search_helper(obj, node->right);
	if (result != NULL) {
		return result;
	}

	return NULL;

}

template <typename T>
Node<T>* BTree<T>::search(int obj)
{

	Node<T>* p = get_root();
	p = search_helper(obj, p);
	return p;

}

template <typename T>
void BTree<T>::update_search_times_helper(Node<T>* node, int depth)
{
	if (node != NULL) {
		node->search_time = depth;
		update_search_times_helper(node->left, depth + 1);
		update_search_times_helper(node->right, depth + 1);
	}
}

template <typename T>
void BTree<T>::update_search_times()
{

	Node<T> *p = get_root();
	int i = p->search_time;
	update_search_times_helper(p, i);

}

template <typename T>
ostream& BTree<T>::inorder_helper(ostream& out, Node<T>* node)
{
	if (node != NULL) {
		inorder_helper(out, node->left);
		pretty_print_node(out, node);
		// if (node->parent != NULL) {
		// 	out << " | parent = " << node->parent->value;
		// }
		// if (node->left != NULL) {
		// 	out << " | left = " << node->left->value;
		// }
		// if (node->right != NULL) {
		// 	out << " | right = " << node->right->value;
		// }
		// out << endl;

		inorder_helper(out, node->right);
	}
    return out;
}

template <typename T>
ostream& BTree<T>::inorder(ostream& out)
{
	inorder_helper(out, get_root());
	out << "size: " << size << endl;
	out << "height: " << height << endl;
	return out;
}

template <typename T>
ostream& BTree<T>::print_level_by_level(ostream& out)
{
	queue<Node<T> * > q1;
	queue<Node<T> * > q2;
	Node<T> *p = get_root();
	q1.push(p);
	int level = p->search_time;
	Node<T>* current = p;

	while (level < height) {

		while (q1.size() > 0) {
			current = q1.front();
			if (current->left == NULL) {
				q2.push(NULL);
			}
			else {
				q2.push(current->left);
			}

			if (current->right == NULL) {
				q2.push(NULL);
			}
			else {
				q2.push(current->right);
			}

			if (current->value < 0) {
				out << "X ";
			}
			else {
				pretty_print_node(out, current);
			}
			level = q1.front()->search_time;
			q1.pop();
			
		}
		out << endl;
		while (q2.size() > 0) {
			if (q2.front() != NULL) {
				q1.push(q2.front());
				q2.pop();
			}
			else {
				// INSERTS DUMMY INTEGER VALUE
				q1.push(new Node<T>(-1000000));
				q2.pop();
			}

		}

	}

	

	return out;
}

template<typename T> 
ostream& BTree<T>::level_helper(ostream& out, Node<T>* node) {
	if (node == NULL) {
		out << "X ";
	}
	else {
		out << node->value << " ";
	}
	if (node->left != NULL) {
		level_helper(out, node->left);
	}
	if (node->right != NULL) {
		level_helper(out, node->right);
	}


	return out;
}

template <typename T>
T BTree<T>::get_total_search_time(Node<T>* node)
{
	T total = 0;
	if (node != NULL) {
		total += node->search_time;
		total += get_total_search_time(node->left);
		total += get_total_search_time(node->right);
	}
	else {
		total += 0;
	}
	return total;
}

template <typename T>
float BTree<T>::get_average_search_time()
{
	Node<T> *p = get_root();
	float total = get_total_search_time(get_root());
	// cout << "total: " << total << endl;
    return total / (float) size;
}

