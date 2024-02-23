#ifndef __SUPPORT_H__
#define __SUPPORT_H__
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
class sptr {

    //copied from class06_sorting5_handout.pdf
    public:
        sptr(T *_ptr=NULL) { ptr = _ptr; }

		//operator < overloaded to compare smartpointers
        bool operator<(const sptr &rhs) const {
            return *ptr < *rhs.ptr;
        }

        operator T * () const { return ptr; }

    private:
        T *ptr;
};

// CS307 ----------------------------------------- 
/*
template <typename T>
void qsort_r3(vector<T> &A, int left, int right) {
  // modify random pivot quicksort from Lab 2 to 
  // partition A into sublists {<}, {pivot,=}, {>} 
}

template <typename T>
void qsort_r3(vector<T> &A) {
  qsort_r3(A, 0, A.size()-1);
}
*/
//-----------------------------------------------

template <typename T>
class dlist { 

    //copied from class06_sorting5_handout.pdf
    private:
        struct node {
            node() { key = T(); prev = next = this; }
            node(T &n_key) { key = n_key; prev = next = this; }
            T key;
            node *prev;
            node *next;

			// provide less-than operator to compare keys
            bool operator<(const node& rhs) const { return key < rhs.key; }; //less than operator to compare key values in nodes
        };

        node *head;

		//adding private mergesort and merge functions to class
        node* mergesort(node*, node*);  
        node* merge(node*, node*, node*);

    public:

        dlist() { head = new node(); }

        ~dlist() { //list destructor to iterate through list and delete nodes

			node*curNode = head->next;
            while (curNode != head) {

                head->next = curNode->next;
                delete curNode;
				curNode = head->next;
            }

			delete head;
        } 

        void push_back(T &); //push_back function coded to insert a new node into the dlist
        void insertion_sort(); 

        void mergesort(); 
        void quicksort(int); //added quicksort member function that takes in an integer as an argument

        class iterator {

            public:
                iterator() { p = NULL; }

                T & operator*() { return p->key; }
                iterator operator++() { p = p->next; return *this; }
                bool operator!=(iterator &rhs) { return p != rhs.p; }

            private:
                iterator(node *np) { p = np; }
                node *p;

            friend class dlist<T>;
        };

        iterator begin() { return iterator(head->next); }
        iterator end() { return iterator(head); }
};


//am I supposed to also copy the insert and mergesort and push_back
template <typename T>
void dlist<T>::push_back(T &key) { //adding a new node to the dlist

    node *p = new node(key);
    node *pp = head->prev;

	//adjusting pointers to include the new node
    p->next = head;
    p->prev = pp;
    pp->next = p;
    head->prev = p;
}

template <typename T>
void dlist<T>::insertion_sort() {

    node *p = head->next;
    node *pp, *pn, *q;

    while (p != head) {

        pp = p->prev;
        pn = p->next;

        // unlink node p
        pp->next = pn;
        pn->prev = pp;

        // find node q preceeding node p
        q = pp;

        while (q != head && p->key < q->key) {
            q = q->prev;
        }

        // relink node p
        p->next = q->next;
        q->next = p;
        p->prev = q;
        p->next->prev = p;
        p = pn;
    }
}

template <typename T>
struct dlist<T>::node *dlist<T>::mergesort(node *L, node *R) {

    if (L->next == R)
        return L;

    int N = 0;
    node *p = L;

    while (p != R) {
        p = p->next;
        N++;
    }

    node *M = L;
    for (int i=0; i<N/2; i++)
        M = M->next;

    L = mergesort(L, M);
    M = mergesort(M, R);
    L = merge(L, M, R);

    return L;
}

template <typename T>
void dlist<T>::mergesort() {

    if (head->next == head->prev)
        return;

    head->next = mergesort(head->next, head);
}

    
template <typename T>
struct dlist<T>::node *dlist<T>::merge(node *L, node *M, node *R) {
	
	//logic is based on HW5
	//initializing pointers based on particular sublist to be considered
    node * H = L->prev;
    node * p = L;
    node * q = M;
    node * tmp_q;

    while (true) { //iterating through the unsorted list 

       if (p == q || q == R) { //breaking condition indicates sorted 
			break;			   //(p and q are the same/q reaches the end of the sublist)
       }

        if (!(q->key < p->key)) { //checking whether p's key is greater than q's key

            p = p->next; //if not, we increment p forward to next node
        }

        else {

			//initializing temporary var to maintain q's position prior to increment
            tmp_q = q; 

            //incrementing tmp before adjusting q (saving the spot)
            tmp_q = tmp_q->next;

            //relinking ~6 pointers to bring p in front of q
            q->next->prev = q->prev;
            q->prev->next = q->next;
            q->next = p;
            q->prev = p->prev;
            p->prev->next = q;
            p->prev = q;
            
            //updating position of q pointer
            q = tmp_q;
        }
    }

    return H->next;
}

template <typename T>
void dlist<T>::quicksort(int mode) {
    
    //creating a vector of smart pointers (pointers to each node of dlist)
    vector<sptr<node>> Ap; 
    node* p = head->next;

    while (p != head) {

        Ap.push_back(p); //pushing back sptr to Ap
        p = p->next;
    }

    //sorting the vector of pointers
	if (mode == 1) {

		sort(Ap.begin(), Ap.end());
	}

    //relinking the list based on the sorted vector of smartpointers
    p = head;

	//iterating through vector and adjusting pointers
    for (size_t i = 0; i < Ap.size(); i++) {
        
        p->next = Ap[i];
        p = p->next;
    }

	//ensuring that the list is appropriately circularly linked at its 'end'
    p->next = head;
    head->prev = p;
  
}

#endif // __SUPPORT_H__
