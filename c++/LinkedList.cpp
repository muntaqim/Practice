#include <iostream>
using namespace std;

template <class T>
class Node{
    template<typename C>
    friend class LinkedList;
    private:    
        T m_data;
        Node<T> *m_next;
    public:
        Node(T data):m_data(data),m_next(NULL){}

};

template <class T>
class LinkedList{
    private:
        Node<T> *m_head;
        Node<T> *m_tail;

    public:
        LinkedList();
        ~LinkedList();
        void add(T data);
        void printList();
};
template <class T>
LinkedList<T>::LinkedList():m_head(NULL),m_tail(NULL){}

template <class T>
LinkedList<T>::~LinkedList(){
    cout << "In destructor \n";
    Node<T> *temp = m_head;
    while(m_head)
    {
        cout << "destroying" << m_head->m_data << endl;
        temp = m_head->m_next;
        delete m_head;
        m_head = temp;
    }
}

template <class Y>
void LinkedList<Y>::add(Y data)
{
    Node<Y> *n = new Node<Y>(data);
    if (!m_head && !m_tail)
    {
        m_head = n;
        m_tail = n;
    }
    else
    {
        m_tail->m_next = n;
        m_tail = m_tail->m_next; 
    }
}
template <class Y>
void LinkedList<Y>::printList(){
    Node<Y> *temp = m_head;
    while(temp)
    {
        cout << temp->m_data << "-->";
        temp = temp->m_next;
    }
}
int main()
{
    LinkedList<int> L;
    L.add(1);
    L.add(55);
    L.add(45);

    L.printList();
}
