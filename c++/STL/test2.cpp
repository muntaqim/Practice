#include <iostream>
#include <vector>
using namespace std;

int main()
{
    
  vector<int> nums{-2147483648, 2147483647};
  
  long firstNum = nums[1];
  long secondNum = nums[0];
  long long diff =  firstNum - secondNum;
  
  
  cout << diff << endl;


   return 0;
}
