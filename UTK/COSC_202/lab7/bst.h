//Nia Maheshwari
//Adam Disney
//COSC 202

#pragma once
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class TKey>
class bst {
  struct node {

    int nodeID; 
    node(int ID = 0); 

    void print();

    TKey key;
    node *parent;
    node *left;
    node *right;
  };
  
  public:
    class iterator {
      public:
        iterator() {p = NULL; };
        iterator(node *n);

        iterator operator++(); 
        iterator operator--();  //-- operator (for mode 4)

        TKey &operator*();  
	
        bool operator!=(const iterator &it);  
        bool operator==(const iterator &it); 
       

      private:
        friend class bst<TKey>;
        iterator(node n); //constructor with argument

        node *p;
    };

    iterator begin(); 
    iterator end(); 

    iterator rbegin(); //extra credit (for mode 4)
    iterator rend();  //extra credit (for mode 4)

  public:
    bst() { Troot=NULL; ID = 0;}
    ~bst() { clear(Troot); }

    bool empty() { return Troot==NULL; }

    void insert(TKey &);

    iterator lower_bound(const TKey &);
    iterator upper_bound(const TKey &);

    void print_bylevel();

  private:
    void clear(node *);
    node *insert(node *, TKey &);

    int ID;
    node *Troot;
};

template <class TKey>
bst<TKey>::node::node(int id) { //node constructor

    nodeID = id;
    key = TKey();
    parent = NULL;
    left = NULL;
    right = NULL;
}

template <class TKey>
bst<TKey>::iterator::iterator(node *n) {
    p = n;
}

template <class TKey>
void bst<TKey>::node::print() { //print function (for int and char)

  cout << setw(3) << nodeID << " " << setw(3) << key << " : " ; 

  //parent node infor
  if (!parent)
    cout << "ROOT ";
  else 
    cout << "P=" << setw(3) << parent->nodeID;

  //left node info
  if (left) 
      cout << " L=" << setw(3) << left->nodeID;
  else       
      cout << "      ";
  
  //right node info
  if (right) 
      cout << " R=" << setw(3) << right->nodeID;
  else       
      cout << "      ";

  cout << endl;
}

template <>
void bst<string>::node::print() { //print function (for strings) 

  cout << setw(3) << nodeID << " "<< setw(20) << key << " : " ;  //key width increased to 20

  //parent node info
  if (!parent)
    cout << "ROOT ";
  else 
    cout << "P=" << setw(3) << parent->nodeID;

  //left node info
  if (left) 
      cout << " L=" << setw(3) << left->nodeID;
  else       
      cout << "      ";
  
  //right node info
  if (right) 
      cout << " R=" << setw(3) << right->nodeID;
  else       
      cout << "      ";

  cout << endl;
}

//bst<TKey>::iterator operators and functions go here
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::iterator::operator++() { //++ operator: purpose is to allow for correct navigation of the bst

    if (p->right != nullptr) { //checking if the node has a right child
        p = p->right;

        while (p->left != nullptr) {
            p = p->left;
        }
    }

    else if (p->parent == nullptr) { //if p's parent is null
        p = NULL;
    }

    else if (p->parent->left == p) { //if p is the left child
            p = p->parent;
    }

    else {

        while (p->parent != nullptr && p == p->parent->right){ //if p is the right child and has a parent
            p = p->parent;
        }

        if (p->parent) {
            p = p->parent;
        }

        else {
            p = NULL;
        }
    }

    return *this;
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::iterator::operator--() { //-- operator: a logically reversed version of the ++ operator

    if (p->left != nullptr) { //if p has a left child
        p = p->left;
        while (p->right != nullptr) {
            p = p->right;
        }
    }

    else if (p->parent == nullptr) {
        p = NULL;
    }

    else if (p == p->parent->right) { //if p is the left child (reversed from ++)
        p = p->parent;
    }

    else {
        while (p->parent != nullptr && p == p->parent->left){ //if p is the left child (reversed from  ++)
            p = p->parent;
        }

        if (p->parent) {
            p = p->parent;
        }

        else {
            p = NULL;
        }
    }

    return *this;
}

template <class TKey>
TKey &bst<TKey>::iterator::operator*() { //* operator: a way to quickly access a node's key
    return p->key;    
}

template <class TKey>
bool bst<TKey>::iterator::operator==(const iterator &it) { //== operator: comparing iterators

    if (it.p == p) {
        return true;
    }
    
    return false;
}

template <class TKey>
bool bst<TKey>::iterator::operator!=(const iterator &it) { //!= operator: comparing iterators

    if (it.p != p) {
        return true;
    }

    else return false;
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::begin() { //iterator that chases pointers from the root of the tree down to the leftmost node

    if (Troot == NULL) {
        return iterator(NULL);
    }

    struct node * node_chaser = Troot; 

    //traverse to the leftmost node
    while (node_chaser->left != nullptr) {
        node_chaser = node_chaser->left;
    }

    return iterator(node_chaser);
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::end() { //simply returns null, which is the end of the tree
    
    return iterator(NULL);
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::rbegin() { //iterator that chases pointers from the root of the tree down to the rightmost node. Reverse of begin()

    if (Troot == NULL) {
        return iterator(NULL);
    }

    struct node * rnode_chaser = Troot; 

    //traverse to the rightmost node
    while (rnode_chaser->right != nullptr) {
        rnode_chaser = rnode_chaser->right;
    }

    return iterator(rnode_chaser);
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::rend() { //returns null
    
    return iterator(NULL);
}

template <class TKey>
void bst<TKey>::clear(node *T) {
  if (T) {
    clear(T->left);
    clear(T->right);
    delete T;
    T = NULL;
  }
}

template <class TKey>
void bst<TKey>::insert(TKey &key) { 
  Troot = insert(Troot, key);
}

template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, TKey &key) {

  if (T == NULL) {

    //update and setting node ID 
    T = new node(ID);
    ID = ID + 1;
    T->key = key;

  } else if (T->key == key) {
      ;
    
  } else if (key < T->key) {
        T->left = insert(T->left, key);
        T->left->parent = T; //setting the parent link for the left child
  } else {
        T->right = insert(T->right, key);
        T->right->parent = T; //setting the parent link for the right child
  }

  return T;
}

//lower_bound function 
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::lower_bound(const TKey &k) { //returns the first key that is >= k

    node * test = Troot; //temporary node pointer that is searching the nodes for the first key value greater than or equal to input key
    node * nodeToReturn = NULL; 

    while (test != nullptr) { 

        if (test->key >= k) {
             nodeToReturn = test; //only set the returning pointer to that node if it meets the >= condition
			 test = test->left;
        }

		else {
            test = test->right;
        }
    }
    return iterator(nodeToReturn);
}


//upper_bound function 
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::upper_bound(const TKey &k) { //returns first key that is >k
    //first key that is > k
    
    node * test = Troot; //searcher node pointer
    node * nodeToReturn = NULL; 

    while (test != nullptr) {
        if (test->key > k) {
			nodeToReturn = test; //only setting the return pointer if it meets the > condition
			test = test->left;
        }
        else {
            test = test->right;
        }
    }

    return iterator(nodeToReturn);
}

template <class TKey>
void bst<TKey>::print_bylevel() {
  if (Troot == NULL)
    return; 

  queue<node *> Q;
  node *T;

  Q.push(Troot);
  while (!Q.empty()) {
    T = Q.front();
    Q.pop();

    T->print();
    if (T->left)  Q.push(T->left);
    if (T->right) Q.push(T->right);
  }
}
