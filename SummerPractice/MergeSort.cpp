#include "start.cpp"

void merge(int *a, int low, int high, int mid)
{
    int i, j, k, c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            c[k] = a[i];
            k++;
            i++;
        }
        else
        {
            c[k] = a[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        c[k] = a[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = a[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)
    {
        a[i] = c[i];
    }
}

void sort(int data[], int start, int end){
   if(start < end){
        int mid = (end+start) / 2;
        sort(data, start, mid);
        sort(data, mid+1, end);
        merge(data, start, end, mid);

    }
}

int main()
{
    const int SIZE = 10;
    int data[SIZE] = {2,4,3,8,5,6,4,9,3,2};
    sort(data,0,SIZE-1);

    printArr(data,SIZE);

    return 0;
}
