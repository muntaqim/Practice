// WaysToSum.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <array>

using namespace std;

int sumWaysRecurse(std::array<int, 5> &numbers, int sum, int size)
{
	if (size == 0)
		return 0;

	//subtract from sum
	int tempSum = sum;
	tempSum -= numbers[size - 1];
	if (tempSum == 0)
		return 1;

	//use the current num and see if you can get the sum with and without it
	return sumWaysRecurse(numbers, tempSum, size - 1) + sumWaysRecurse(numbers, sum, size - 1);
}
int sumWays(std::array<int, 5> &numbers, int sum)
{
	// for each number, find out if remaining sum is possible
	// call internal function that will be used to recurse. Need to pass in where in the
	// array we start from
	//
	return sumWaysRecurse(numbers, sum, numbers.size());
}


int main()
{
	// for the values below, there are two ways to get 11
	// {5.6}
	// {10,1}
	// our function should return 2
	array<int, 5> numbers = { 10, 5, 6 ,5, 1 };
	int sum = 11;

	int ways = sumWays(numbers, sum);
}



