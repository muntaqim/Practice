#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Stack{
    public:
        vector<T> array;
        int m_size;
        int m_head;
    
        Stack(){}
        Stack(int size):array(size),m_size(size),m_head(-1){}
        T pop()
        {
            m_head --;
            return(array[m_head + 1]);
        }

        void push(T element)
        {
            m_head += 1;
            array[m_head] = element;
        }
        bool isFull(){
            return m_head >= m_size-1;
        }
        bool isEmpty(){
            return m_head < 0;
        }

        void print()
        {
            for(int x = 0; x <= m_head; x++)
            {
                cout << "element " << x << ": " << array[x] << endl;
            }
        }
};

template <class T>
class multiStack{
    public:
        vector<Stack<T>> list;
        int size;
        int curList;
        int stackSize;

        multiStack(){}
        multiStack(int size):list(10,Stack<T>(size))
        {
            // initialize with 10 stacks
            this->curList = 0;
            this->size = 10;
            stackSize = size;
        }

        T pop()
        {
            if(list[curList].isEmpty())
                curList--;

            return list[curList].pop();
        }
        void handleResize()
        {
            curList ++;
            // the array needs to be resized
            if(curList > size)
            {
                size *= 2;
                //create bigger list
                list.resize(size,Stack<T>(stackSize)); 
            }
        }
        void push(T elem)
        {
            if(list[curList].isFull())
                //update list
                handleResize();
            
            list[curList].push(elem);
        }



};

int main()
{
    multiStack<int> st(2);
    st.push(10);
    st.push(20);
    st.push(30);
    st.push(30);


    cout << st.curList << endl;

    cout << st.pop() << endl;
    cout << st.pop() << endl;
    cout << st.pop() << endl;
    cout << st.pop() << endl;
    return 0;
}
