#include <iostream>
#include <vector>


bool isZero(std::vector<std::vector<int>> a, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!a[i][j])
                return true;
    return false;
}


void print(std::vector<std::vector<int>> a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0, space; j < m; j++) {
            if (a[i][j] / 10 == 0)
                space = 3;
            else if (a[i][j] / 100 == 0)
                space = 2;
            else
                space = 1;

            for (int k = 0; k < space; k++)
                std::cout << " ";

            std::cout << a[i][j];
        }
        std::cout << std::endl;
    }
}


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> a(n);

    for (int i = 0; i < n; i++)
        a[i].resize(m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            a[i][j] = 0;

    int count = 1;
    int ii = 0, jj = 0;

    while (isZero(a, n, m)) {

        while (jj != m && a[ii][jj] == 0)
            a[ii][jj++] = count++;
        jj--;
        ii++;

        while (ii != n && a[ii][jj] == 0)
            a[ii++][jj] = count++;
        ii--;
        jj--;

        while (jj >= 0 && a[ii][jj] == 0)
            a[ii][jj--] = count++;
        jj++;
        ii--;

        while (ii >= 0 && a[ii][jj] == 0)
            a[ii--][jj] = count++;
        if (ii < 0)
            ii++;
        ii++;
        jj++;
    }

    print(a, n, m);

    return 0;
}
