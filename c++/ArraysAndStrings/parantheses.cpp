#include <iostream>
using namespace std;

int main(void)
{
    string input;

    cout <<  "enter parantheses: ";
    cin >> input;
    
    // if this goes under 0, paranthases is bad
    int isok = 0;
    for (int i=0; i < input.length(); i++)
    {
        if (input[i] == '(')
            isok++;
        else if (input[i] == ')')
            isok--;

        if (isok < 0)
            break;
    }
    if (isok != 0)
        cout << "bad parantheses\n";
    else
        cout << "things are good\n";
}
