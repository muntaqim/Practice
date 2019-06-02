/* Heap implementation
 * Heap has built in heap sort but it destroys current heap
 *
 */ 


#include <iostream>
#include <vector>
#include <algorithm>    // std::swap
#include <stdlib.h>

using namespace std;

template <class T>
class heap
{
    private:
        vector<T> mHeap;
        bool mMin = true;
        bool compare(int l, int r)
        {
            if(mMin)
                return mHeap[l] > mHeap[r];
            else
                return mHeap[l] < mHeap[r];
        }
        
        void heapify()
        {
            for (int i = (mHeap.size()/2 - 1); i >= 0; i--)
            {
                heapifyDown(i);
            }

        }
        // heapify a last element up
        void heapifyUp()
        {
        
        }

        // heapify the top element down
        void heapifyDown(int elem)
        {
            int left = elem * 2 + 1;
            int right = elem * 2 + 2;
            int curSwap = elem;

            if (left < mHeap.size() && compare(curSwap, left))
            {
                curSwap = left;
            }
            
            if (right < mHeap.size() && compare(curSwap, right))
            {
                curSwap = right;
            }

            if(curSwap != elem)
            {
                swap(mHeap[curSwap], mHeap[elem]);
                heapifyDown(curSwap);
            }
        }
    public:
        bool verifyHeap(int cur)
        {
            if (cur >= mHeap.size())
                return true;
            
            int left = cur * 2 + 1;
            int right = cur * 2 + 2;

            if(left < mHeap.size() && compare(cur, left))
                return false;

            if(right < mHeap.size() && compare(cur, right))
                return false;

            return verifyHeap(right) && verifyHeap(left);
        }

        heap(vector<T> in, bool minHeap=true):mHeap(in.begin(), in.end()),mMin(minHeap)
        {
            heapify();
            if (!verifyHeap(0))
                cout << "HEAP IS NO GOOD" << endl;
        }
        ~heap(){}
        void pop()
        {
            swap(mHeap[0], mHeap[mHeap.size() - 1]);
            mHeap.pop_back();
            heapifyDown(0);

        }
        //void push(T element);
        void printHeap()
        {
            cout << "Printing heap: " << endl;
            for (auto i : mHeap)
                cout << i << " ";

            cout << endl;
        }
        void heapSort()
        {
            while (mHeap.size())
            {
                cout << mHeap[0] << " ";
                this->pop();
            }
        }
};

void generateData(vector<int> &input)
{
    int size = rand() % 100;
    for (int i = 0; i < size; i++)
        input.push_back(i);

    int left;
    int right;

    //swap a random 2x the size
    for(int i = 0; i < size*2; i++)
    {
        left = rand() % size;
        right = rand() % size;

        swap(input[left], input[right]);    
    } 

    cout << "Generate array is: " << endl;

    for (auto i : input)
        cout << i << " ";


    cout << endl;

}

int main()
{
    vector<int> input;
    
    generateData(input);
    
    //generate min heap
    heap<int> h(input);
    h.printHeap();
    h.heapSort();
}
