#include <iostream>
#include <algorithm>
#include <ctime>


template<typename T>
void print(T *arr, const int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}


template<typename T>
void maxHeap(T *arr, const int SIZE, const int icurr) {
    int leftChild = 2 * icurr;
    int rightChild = 2 * icurr + 1;

    int max = (leftChild <= SIZE - 1 && arr[leftChild] > arr[icurr]) ? leftChild : icurr;

    if (rightChild <= SIZE - 1 && arr[rightChild] > arr[max]) {
        max = rightChild;
    }

    if (max != icurr) {
        std::swap(arr[icurr], arr[max]);
        maxHeap(arr, SIZE, max);
    }
}


template<typename T>
void minHeap(T *arr, const int SIZE, const int icurr) {
    int leftChild = 2 * icurr;
    int rightChild = 2 * icurr + 1;

    int min = (leftChild <= SIZE - 1 && arr[leftChild] < arr[icurr]) ? leftChild : icurr;

    if (rightChild <= SIZE - 1 && arr[rightChild] < arr[min]) {
        min = rightChild;
    }

    if (min != icurr) {
        std::swap(arr[icurr], arr[min]);
        minHeap(arr, SIZE, min);
    }
}


template<typename T>
void buildHeap(T *arr, const int SIZE, const bool isReverse) {
    for (int i = (SIZE - 1) / 2; i >= 0; i--)
        isReverse ? minHeap(arr, SIZE, i) : maxHeap(arr, SIZE, i);
}


template<typename T>
void heapSort(T *arr, const int SIZE, const bool isReverse = false) {
    int heapSize = SIZE;

    buildHeap(arr, SIZE, isReverse);

    while (heapSize > 1) {
        isReverse ? minHeap(arr, heapSize, 0) : maxHeap(arr, heapSize, 0);
        std::swap(arr[0], arr[heapSize - 1]);
        heapSize--;
    }
}


void generateArrayValues(int *arr, const int SIZE, const int MAX_VALUE) {
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % MAX_VALUE;
}


bool check(int *arr, const int SIZE, const bool isReverse) {
    for (int i = 0; i < SIZE - 1; i++) {
        if (isReverse) {
            if (arr[i] < arr[i + 1])
                return false;
        } else {
            if (arr[i] > arr[i + 1])
                return false;
        }
    }

    return true;
}


int main() {
    srand(time(NULL));

    const int N = 10000;
    const int MAX_VALUE = 100;

    int *a = new int[N];

    generateArrayValues(a, N, MAX_VALUE);

    heapSort(a, N);
    std::cout << "To increase: ";
    std::cout << (check(a, N, false) ? "true" : "false") << std::endl;

    heapSort(a, N, true);
    std::cout << "To decrease: ";
    std::cout << (check(a, N, true) ? "true" : "false") << std::endl;

    delete[] a;

    return 0;
}
