// countWords.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <utility>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <cctype>
#include <algorithm>

using namespace std;
string lowerString(string orig)
{
    char r[orig.size()+1];

    for (int x = 0; x < orig.size(); x++)
        r[x] = tolower(orig[x]);

    r[orig.size()] = '\0';
    return string(r);
}
vector<string> parseSentence(string sentence)
{
	vector<string> list;
	string currentWord;
	char punc[] = { '.',',',';',',','\n',' ', '\'' };
	
	// using a set here so that I can use the find function
	// can also use vector here and use -> find(vector.begin(), vector.end(), c)
	set<char> punctuation(punc, punc + sizeof(punc));

    // start and length of copy
    int start = 0;
    int length = 0;

	for (char c : sentence)
	{
		if (punctuation.find(c) == punctuation.end())
		{
            // can remove this copy and just update begin and end
			length ++;
            //currentWord += tolower(c);
		}
		else
		{
			/*if (currentWord.size() > 0)
			{
				list.push_back(currentWord);
				currentWord.clear();
			}*/
            if (length > 0)
            {
                list.push_back(lowerString(sentence.substr(start,length)));
                start += length;
                length = 0;
            }
            start++;
		}
	}
    /*
	if (currentWord.size() > 0)
	{
		list.push_back(currentWord);
		currentWord.clear();
	}*/

    if (length > 0)
    {
        list.push_back(lowerString(sentence.substr(start,length)));
        start += length;
        length = 0;
    }
	return list;
}

bool compareMap(pair<string, int> first, pair <string, int> second)
{
	return first.second > second.second;
}

void countWord(string sentence)
{
	vector<string> words = parseSentence(sentence);
	for (auto word : words)
	{
		cout << word << endl;
	}

	map<string, int> wordCount;

	// map string to map
	for (string word : words)
	{
		if (wordCount.find(word) == wordCount.end())
		{
			wordCount[word] = 1;
		}
		else
		{
			wordCount[word]++;
		}
	}

	cout << "======= PRINTING MAP =======" << endl;
	// printing map
	for (auto x : wordCount)
	{
		cout << x.first << ":" << x.second << endl;
	}

	typedef pair<string, int> p;

	vector<p> vec;

	// copying from map into a vector
	for (p x : wordCount)
	{
		vec.push_back(x);
	}
	//copy(wordCount.begin(), wordCount.end(), back_inserter<vector<p>>(vec));
	
	sort(vec.begin(), vec.end(), compareMap);
	
	cout << "================ FINAL RESULT ===============" << endl;
	//print out final set
	for (auto x : vec)
	{
		cout << x.first << ":" << x.second << endl;
	}
}

int main()
{
	string sentence = "Hello, my name is Muntaqim. My favourite word is hello. It is very cool. We're having fun; yey";
	countWord(sentence);
}


