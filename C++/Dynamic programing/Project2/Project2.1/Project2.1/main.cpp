#include "Dynamic.h"

void printPara(vector<vector<int>> s, int start, int end)
{
    if (start == end)
        cout << 'A' << start;
    else
    {
        cout << '(';
        printPara(s, start, s[start][end]);
        printPara(s, s[start][ end] + 1, end);
        cout << ')';
    }
}

int main() {
    Dynamic obj;
    vector<vector<int>> s;
    int size = 5;
    int start = 1;
    int end = 4;

    s.resize(size);

    for (int i = 0; i < size; i++)
    {
        vector<int> inner;
        inner.resize(size, -1);
        s[i] = inner;
    }

    //fill
    s[1][4] = 1;
    s[1][3] = 2;
    s[1][2] = 1;

    s[2][4] = 2;
    s[2][3] = 2;

    s[3][4] = 3;

    printPara(s, start, end);
    cout << endl << endl;



    //get all the data
    //obj.fillAds();


    //dynamic call
   // obj.BoardCost();

    //display results
   // obj.print();

    return 0;
}