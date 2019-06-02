#ifndef NODE_H
#define NODE_H

#include "BST.h"

template <class A>
class Node
{
    template <class B>
    friend class BST;
public:
	Node(A data)
	{
		this->data = data;
		this->right = 0;
		this->left = 0;
	};
	~Node();
	A getData();
	Node * left;
	Node * right;
	A data;

};

template<class A>
inline Node<A>::~Node()
{
}

template <class A>
A Node<A>::getData() {
	return this.data;
}



#endif
