#include <iostream>

using namespace std;

void countSort(int A[], int n) {
    if (n < 1) {
        return;
    }

    int i, R = A[0];
    for (i = 1; i < n; i++) {
        if (A[i] > R) {
            R = A[i];
        }
    }

    int C[R+1];
    for (i = 0; i < R+1; i++) {
        C[i] = 0;
    }
    for (i = 0; i < n; i++) {
        C[A[i]]++;
    }

    int I[R+1];
    I[0] = 0;
    for (i = 1; i <= R+1; i++) {
        I[i] = I[i-1] + C[i-1];
    }

    int B[n];
    for (i = 0; i < n; i++) {
        B[i] = A[i];
    }

    for (i = 0; i < n; i++) {
        A[I[B[i]]] = B[i];
        I[B[i]]++;
    }
}

int main() {
    int n;
    cin >> n;

    int A[n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    countSort(A, n);

    for (int i = 0; i < n; i++) {
        cout << A[i] << endl;
    }

    return 0;
}
