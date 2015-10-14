#include <iostream>
#include <iomanip>
using namespace std;

const int row = 3;
const int col = 3;
int arr[row][col] = {0};

void fill(int r = 0, int c = 0){
    if (r < row && c < col) {    
        int num;
        cout << "arr[" << r << "]" << "[" << c << "]" << " = ";
        cin >> num;
        arr[r][c] = num;
        
        if (c == col - 1)
            fill(r+1, 0);
        else 
            fill(r, c+1);    
    }
}

void print(int r = 0, int c = 0)
{
    if (r < row && c < col) {    
        cout << arr[r][c] << "\t";
        
        if (c == col - 1) {
            cout << endl;
            print(r+1, 0);
        }
        else 
            print(r, c+1);    
    }    
}


int main() {
   fill(0,0);
   cout << endl << endl;
   print(0,0);
}