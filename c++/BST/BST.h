#ifndef BST_H
#define BST_H

#include "Node.h"
#include <vector>
#include <iostream>
using namespace std;

template <typename A>
class BST
{
private:
	Node<A> *head;
	void internalInsert(Node<A> *head, Node<A> *newNode);
    void printInorderInternal(Node<A> *head);
public:
	BST()
	{
		this->head = 0;
	}
    BST(vector<A> input){
        this->head = 0;
        for (A x : input)
        {
            cout << "Proccessing" << x << endl;
            insert(x);

        }
    }
	~BST() {}
	void insert(A value);
    void printInorder();
};

template <typename A>
void BST<A>::internalInsert(Node<A> *head, Node<A> *newNode)
{
	if (head->data >= newNode->data)
	{
		if (head->left == 0)
			head->left = newNode;
		else
			internalInsert(head->left, newNode);
	}
	else if (head->data < newNode->data)
	{
		if (head->right == 0)
			head->right = newNode;
		else
			internalInsert(head->right, newNode);
	}
}

template <typename A>
void BST<A>::insert(A value)
{
	Node<A> * newNode = new Node<A>(value);
	if (!this->head)
		this->head = newNode;
	else
	{
		internalInsert(this->head, newNode);
	}

}


template <typename A>
void BST<A>::printInorder(void){
    printInorderInternal(this->head);
}


template <typename A>

void BST<A>::printInorderInternal(Node<A> *head){
    if (head == NULL)
        return;

    //go left
    printInorderInternal(head->left);

    //print current
    cout << head->data << endl;

    //go right
    printInorderInternal(head->right);
}
#endif
