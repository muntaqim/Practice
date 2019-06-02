/*
 * QUESTION:
 *
 * - Given a compressed string in which a number followed by [] indicate how many times those characters occur, decompress the string
Eg. : a3[b2[c1[d]]]e will be decompressed as 
abcdcdbcdcdbcdcde.
abcdcdbcdcdbcdcde

*/


#include <ctype.h>
#include <string>
#include <iostream>

using namespace std;

string uncompress(string input)
{
    string ret ="";
    string inter;
    string curDigit;
    int bracketCount = 0;

    for (int i = 0; i < input.size(); i++)
    {
        if(isdigit(input[i]))
        {
            while(isdigit(input[i]))
            {
                curDigit += input[i];
                i++;
            }
            i++; // skipping the first [

            while (bracketCount != -1)
            {
                if (input[i] == '[') bracketCount++;
                else if (input[i] == ']') bracketCount --;
                if(bracketCount != -1) 
                {
                    inter += input[i];
                    i++;
                }
                  
            }
            string temp = uncompress(inter);
            for (int count = 0; count < stoi(curDigit); count++)
            {
                ret += temp;
            }
            inter = "";
            curDigit = "";
            bracketCount = 0;
        }
        else
        {
            ret += input[i];
        }
    }

    cout << "ret is " << ret << endl;
    return ret;
}

int main()
{

    cout << "hello world";
    string ex = "a3[b2[c1[d]]]e";


    cout << uncompress(ex); 
}
