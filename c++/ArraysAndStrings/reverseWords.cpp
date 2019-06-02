#include <iostream>
#include <string>

using namespace std;


void swap(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}
void swapWord(int left, int right, string &myString)
{
    while (left < right)
    {
        swap(myString[left], myString[right]);
        left++;
        right --;
    }
}
void reverseString(string &myString)
{
    //first reverse the entire thing
    int left = 0;
    int right = myString.size()-1;

    while (left < right)
    {
        swap(myString[left], myString[right]);
        left++;
        right --;
    }
    cout << "my string is now: " << myString << endl;

    //flip each word
    right = 0;
    left = 0;

    while (right < myString.size())
    {
        if(myString[right] != ' ')
        {
            right++;
        }
        else
        {
            swapWord(left, right-1, myString);
            while(myString[right] == ' ')
            {
                right++;
            }
            left = right;
        }
    }
    swapWord(left, right-1, myString);
}


int main()
{
    string myString = "hello world what is up";
    reverseString(myString);

    cout << myString << endl;
    return 0;
}
