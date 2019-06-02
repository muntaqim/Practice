#include <iostream>
using namespace std;


void replaceSpace(char *input, int size)
{
    int ss = 0;
    while(input[ss] != '\0')
        ++ss;

    int cur,i;
    for (cur = ss, i = size -1; cur >=0; cur--, i--)
    {
        if (input[cur]==' ')
        {
            input[i] = '0';
            input[i-1] = '2';
            input[i-2] = '%';
            i -= 2;  
        }
        else
            input[i] = input[cur];
    }
    cur=0;
    i++;
    while(cur < size)
    {
        input[cur] = input[i];
        i++;
        cur++;
    }
}

int main()
{
    char input[100] = "Hello world there!";
    replaceSpace(input, 100);
    cout << input << endl;
}
