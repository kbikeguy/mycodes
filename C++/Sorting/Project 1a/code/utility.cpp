#include "Utility.h"


vector<int> getInput() {
    vector<int> vals;
    int curr;

    while (cin >> curr && curr !=  -999)
        vals.push_back(curr);

    return vals;
}

void insert(vector<int> &A) {
    //GRADING: INSERT
    int i, j, key, sizeA = (int)A.size();
    for (j = 1; j < sizeA; j++) {
        key = A.at(j);
        i = j - 1;

        while (i >= 0 && A.at(i) > key) {
            A.at(i + 1) = A.at(i);
            i = i - 1;
        }

        A.at(i + 1) = key;
    }
}

void merge(vector<int> &A, int p, int q, int r) {
    //GRADING: MERGE
    int i, j, k;
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> L(n1 + 2) , R(n2 + 2);

    //fill left

    for (i = 1; i <= n1; i++)
        L[i] = A[p + i - 1];

    //fill right
    for (j = 1; j <= n2; j++)
        R[j] = A[q + j];

    //assign sentinels and reset i j
    L[n1 + 1] = R[n2 + 1] = INT_MAX;
    i = j = 1;

    for (k = p; k <= r; k++) {
        if (L.at(i) <= R.at(j)) {
            A.at(k) = L.at(i);
            i++;
        }
        else {
            A.at(k) = R.at(j);
            j++;
        }
    }
}

void mergeSort(vector<int> &A, int p, int r) {
    //GRADING: MERGE
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

void print(vector<int> vec) {
    cout << "SORTED: ";
    for (auto v : vec)
        cout << v << " ";

    cout << endl;
}

void timeTests(ofstream &csv) {
    csv << "size, insert, merge\n";

    for (int i = 2; i <= 100; i += 2) {
        vector<int> insertVals = randomInput(i);
        vector<int> mergeVals = insertVals;

        csv << i << ", ";
        //time insert
        auto start = chrono::steady_clock::now();
        insert(insertVals);
        auto end = chrono::steady_clock::now();
        csv << chrono::duration_cast<chrono::microseconds>(end - start).count() << ", ";

        //time merge
        start = chrono::steady_clock::now();
        mergeSort(mergeVals, 0, i - 1);
        end = chrono::steady_clock::now();
        csv << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
    }
}

vector<int> randomInput(int size) {
    vector<int> vals(size);

    for (auto v : vals)
        v = (rand() % 100) + 1;

    return vals;
}