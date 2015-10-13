#include "start.cpp"

int partition(int data[], int start, int end)
{
    int pivot = end;
    int wall = start;

    for (int i = start ; i < pivot ; i++)
    {
        if (data[i] <= data[pivot])
        {
            swap(data[i], data[wall]);
            wall++;
        }
    }
    swap(data[pivot], data[wall]);
    return wall;
}

void sort(int data[], int start, int end) {
    if(start < end) {
        int pivot = partition(data, start, end);

        sort(data, start, pivot-1);
        sort(data, pivot+1, end);
    }
}

int main()
{
    int data[] = {6,5,1,3,8,4,7,9,2};
    int SIZE = sizeof(data)/sizeof(*data);

    sort(data,0, SIZE - 1);

    printArr(data,SIZE);


    /*
    int count = 0;



    int pivot = SIZE - 1;
    int wall = 0;

    for (int i = 0 ; i < pivot ; i++) {
        count++;
        if (data[i] <= data[pivot]) {
            swap(data[i], data[wall]);
            wall++;
        }

        if (i == pivot-1) {
            swap(data[pivot], data[wall]);
            i = wall++;
        }


    }

    cout << count << endl;
    printArr(data,SIZE);
    */

    return 0;
}
