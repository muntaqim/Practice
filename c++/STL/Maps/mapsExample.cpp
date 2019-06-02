#include <map>
#include <iterator>
#include <string>
#include <iostream>

using namespace std;
int main(void)
{
    map<string,int> m;

    m["hello"] = 1;
    m["bye"] = 2;
    m["bob"] = 3;
    m["kick"] = 4;

    cout << "ranged Based loop " << endl;
    for (auto&& i  : m)
    {

        cout << "key: " << i.first << " value: "<< i.second << endl;
    }



    return 0;
}
