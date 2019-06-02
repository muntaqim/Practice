#include <iostream>
using namespace std;

class A{
public:
    int i;
    A()
    {
        cout << "calling A constructor 1" << endl;

    }
    A(int x)
    {

        cout << "calling A constructor 2" << endl;
        this->i = x;
    }
    A(const A& x){
        this->i = x.i;
        cout << "calling A constructor 3" << endl;
    }
    ~A()
    {
        cout << "calling A destructor" << endl;
    }
};

class B{
    public:

    A x;
    
    B():x(){
        cout << "calling B constructor" << endl;
    }
    ~B()
    {
        cout << "calling B destructor" << endl;
    }
    void someFunction(A x);
};

void foo(){
    A a(1);
}
int main()
{
    B b;
    foo();

}
