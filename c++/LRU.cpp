#include <map>
#include <iostream>
using namespace std;
class Node{
    public:
        int key;
        int value;
        Node *next;
        Node *previous;
        Node();
        Node(int key, int value)
        {
            this->key=key;
            this->value=value;
            next = NULL;
            previous = NULL;
        }
};

class LRUCache {
private:
    map<int, Node*> m;
    Node *head;
    Node *tail;
    int length;
    int cap;
public:
    LRUCache(int capacity) {
        cap = capacity;
        length = 0;
        head = NULL;
        tail = NULL;
    }
    
    void get(int key) {
        int returnValue;
        if(m.find(key) != m.end())
           returnValue = m[key]->value;
        else
            cout << -1 << endl;
        
        // the node has been touched so we must remove it and
        // re-insert it
        removeNode(m[key]);
        insertHead(key,returnValue);
        cout << returnValue << endl;
    }
    
    void removeNode(Node *n)
    {
        //if this was the tail, set tail to
        // previous
        if (tail == n)
        {
            tail = n->previous;
        }
        if(head == n)
            head = n->next;
        // delete the old value
        if(n->previous)
            n->previous->next = n->next;
        if(n->next)
            n->next->previous = n->previous;
        
        delete n;
    }
    void evict()
    {
        if (length == cap)
        {
            
            Node *temp = tail;
            // remove node from map
            m.erase(temp->key);
            // set new tail as last one
            tail = tail->previous;
            // remove node
            removeNode(temp);
            length--;
        }
    }
    void put(int key, int value) {
        
        // remove old version
        if(m.find(key) != m.end())
        {
            removeNode(m[key]);
        }
        // no old version so need to evict
        // if necessary
        else{
            evict();
        }
        insertHead(key, value);
    }
    void insertHead(int key, int value)
    {
        Node *cur = new Node(key,value);
        m[key] = cur;
        
        if(head)
            head->previous = cur;
      
        // no tail means this is the only one in the 
        // list
        if(!tail)
            tail = cur;
        
        cur->next = head;
        head = cur;
        
        length++;
        
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

int main()
{
LRUCache cache(2);

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
}
