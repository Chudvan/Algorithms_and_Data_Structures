#include <iostream>

using namespace std;

const int n = 8;

int a[n] = {14, 33, 27, 10, 35, 19, 42, 44};
int b[n];

void merging(int low, int mid, int high){
    int l1, l2, i;
    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++){
        if(a[l1] > a[l2]){
            b[i] = a[l2++];
        }
        else{
            b[i] = a[l1++];
        }
    }

    while (l1 <= mid){
        b[i++] = a[l1++];
    }

    while (l2 <= high){
        b[i++] = a[l2++];
    }

    for(int i = low; i <= high; i++){
        a[i] = b[i];
    }
}

void sort(int low, int high){
    int mid;
    if (low < high){
        mid = (low + high) / 2;
        sort(low, mid);
        sort(mid + 1, high);
        merging(low, mid, high);
    }
    else{
        return;
    }
}

int main()
{    
    cout << "List before sorting\n";

    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }

    cout << endl;

    sort(0, n - 1);

    cout << "List after sorting\n";

    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }

    return 0;
}
