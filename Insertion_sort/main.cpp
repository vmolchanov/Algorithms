#include <stdio.h>

using namespace std;

void sort(int *a, const int N) {
    for (int i = 1; i < N; i++) {
        int j = i;
        while (j > 0 && a[j] < a[j - 1]) {
            int temp = a[j];
            a[j] = a[j - 1];
            a[j - 1] = temp;
            j--;
        }
    }
}

int main() {
    const int N = 6;
    int a[] = { 6, 5, 4, 3, 2, 1 };
    sort(a, N);
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}