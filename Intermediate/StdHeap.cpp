#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> heap = {4,6,2,4,1,7,9,4,3,6,7,8,4,0};
    make_heap(heap.begin(), heap.end());
    while (!heap.empty()) {
        pop_heap(heap.begin(), heap.end());
        val = heap.front(); 
        heap.pop_back();
        cout << val << endl;
        heap.pop_back();
    }
    return 0;
}