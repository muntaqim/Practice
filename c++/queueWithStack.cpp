#include <stack>
#include <iostream>

using namespace std;
template<class T>
class myQueue{
    public:
        stack<T> n;
        stack<T> o;

        void refillOldifNeeded()
        {
            if(o.empty())
            {
                while(!n.empty())
                {
                    o.push(n.top());
                    n.pop();
                }
            }
        }
        T top()
        {
            refillOldifNeeded();
            return o.top();
        }
        void pop()
        {
            refillOldifNeeded();
            o.pop();
        }
        void push(T input)
        {
            n.push(input);
        }
};

int main()
{
    myQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);


    cout << q.top() << endl;
    q.pop();
    cout << q.top() << endl;
    q.pop();
    cout << q.top() << endl;
    q.pop();


    q.push(4);
    q.push(5);
    q.pop();
    q.push(6);

    cout << q.top() << endl;
    q.pop();
    cout << q.top() << endl;
    q.pop();


}
