#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <numeric>

using namespace std;


class Dynamic
{
public:

    vector<int> adLengths;
    vector<vector<int>> splits;
    vector<int> cubedVals;
    vector<int> costs = { 0 };
    int billboardLength;
    int numAds;
    int minCost;
    Dynamic();
    ~Dynamic();
    void fillAds();
    void BoardCost();
    int cubed(int);
    void setSplit(int, int, int);
    void print();


private:

};

#pragma once
