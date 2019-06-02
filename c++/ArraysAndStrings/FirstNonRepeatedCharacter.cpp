#include <iostream>
#include <vector>
#include <map>
using namespace std;

char firstNonRepeatedCharacter(string word)
{
    map<char,int> letterCount;
    for(char letter:word)
    {
        cout << letter << endl;
        //add to map
        if (letterCount.find(letter) == letterCount.end())
            letterCount[letter] = 1;
        else
            letterCount[letter]++;
    }
    
    //print dictionary
    cout << "printing Dictionaly: " << endl;
    for (auto& key:letterCount)
    {
        cout << "key: " << key.first << " value: " << key.second << endl;
    }

    //loop through vector to see which is the first one to not have 1 in dict
    for (auto& c:word)
    {
        if(letterCount[c] == 1)
            return c;        
    }
    return '\0';
}

int main()
{
    char c = firstNonRepeatedCharacter("racecar");
    if (c != '\0')
        cout << "letter is: " << c << endl;
    
    
    return 0;
}
