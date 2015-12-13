#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> heap = {3,5,4,1,6,8,7,9,0,2};
    make_heap(heap.begin(), heap.end());
    while (!heap.empty()) {
        int val = heap.front();
        cout << val << endl;
        pop_heap(heap.begin(), heap.end());
        heap.pop_back();        
    }
    return 0;
}