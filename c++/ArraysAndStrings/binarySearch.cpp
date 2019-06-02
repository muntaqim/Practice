#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int binarySearchInternal(vector<int> &arr, int begin, int end, int value)
{

    int mid = (begin + end)/2;
    
    cout << "begin " << begin << " end " << end << 
        " mid " << mid << " mid value " << arr[mid] << endl;
    
    if(arr[mid] == value)
        return mid;
    else if(begin == end)
        return -1;
    else if (arr[mid] > value)
        return binarySearchInternal(arr, begin, mid -1, value);
    else
        return binarySearchInternal(arr, mid+1, end, value);
}
int binarySearch(vector<int> &arr, int value)
{
    return binarySearchInternal(arr, 0, arr.size(), value);
}

int main()
{
    vector <int> arr;
    cout << endl << "insert values (q to exit):" << endl;
    string value;
    while(1)
    {
        cin >> value;
        if (value == "q")
            break;
        arr.push_back(stoi(value));
    }
    
    sort(arr.begin(), arr.end());
    //print all values
    for (int values : arr)
        cout << values << ",";

    cout << "enter number you want to search: ";
    int searchValue;
    cin >> searchValue;

    if(arr.size() > 0)
    {
        cout << endl << "index is: " << binarySearch(arr, searchValue);
    }
}
