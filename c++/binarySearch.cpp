#include <iostream>
using namespace std;

// namespace std have been included for this problem.

bool binary_search_internal(int arr[], int begin, int end, int n)
{
    if (begin == end)
        return arr[begin] == n;
        
    int mid = (begin + end)/2;
    
    if (arr[mid] < n)
    {
        return binary_search_internal(arr, mid+1, end, n);
    }
    else if(arr[mid] > n)
    {
        return binary_search_internal(arr, begin, mid-1, n);
    }
    
    return true;
    
}
// Add any helper functions(if needed) above.
bool binary_search(int arr[], int size, int n)
{
    // Add your code below this line. Do not modify any other code.                   
    if (size == 0)
        return false;
        
    return binary_search_internal(arr, 0, size-1, n);
    // Add your code above this line. Do not modify any other code.
}

int main()
{
    int arr[] = {2,8,9,12};     
    cout << binary_search(arr,4,6) << endl;
}
