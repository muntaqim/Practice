// copy algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::copy
#include <vector>       // std::vector
#include <string>
using namespace std;

int main () {
  int myints[]={10,20,30,40,50,60,70};
  std::vector<int> myvector (7);

  std::copy ( myints, myints+7, myvector.begin() );
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it = myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;

  string a = "hello";
  string &b = a;
  string c = b;

  b = "hello1";
  std::cout << "a is " << a << endl;
  std::cout << "b is " << b << '\n';
  std::cout << "c is" << c << '\n';

  cout << b.substr(0,4);



  cout << endl << " ======= negative test ======== " << endl;

  vector<int> nums{-2147483648, 2147483647};
  
  int diff =  nums[1] - (nums[0]);
  cout << diff << endl;

}
