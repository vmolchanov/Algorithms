#include <iostream>


void merge(int *arr, const int left, const int right) {
    int *newArr = new int[right + 1];
    int mid = (left + right) / 2;
    int iarr1 = left;
    int iarr2 = mid + 1;
    int inewArr = left;

    while (iarr1 <= mid && iarr2 <= right) {
        if (arr[iarr1] < arr[iarr2])
            newArr[inewArr++] = arr[iarr1++];
        else
            newArr[inewArr++] = arr[iarr2++];
    }

    if (iarr1 <= mid) {
        for (int i = iarr1; i <= mid; i++)
            newArr[inewArr++] = arr[i];
    }

    if (iarr2 <= right) {
        for (int i = iarr2; i <= right; i++)
            newArr[inewArr++] = arr[i];
    }

    for (int i = left; i <= right; i++) {
        arr[i] = newArr[i];
    }

    delete[] newArr;
}


void mergeSort(int *a, const int left, const int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);

        merge(a, left, right);
    }
}


int main() {
    const int N = 9;

    int *a = new int[N] { 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    mergeSort(a, 0, N - 1);

    for (int i = 0; i < N; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    delete[] a;

    return 0;
}
