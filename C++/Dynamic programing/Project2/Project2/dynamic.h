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
    string rootPath = "C:\\Users\\7356506\\Desktop\\SDSMT\\Fall2020\\AoA\\Project2\\Project2\\dynamic_tests\\";
    vector<string> testFiles = { "test0.txt", "test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt", "test6.txt", "test7.txt",
                              "test8.txt", "test9.txt", "test10.txt", "test11.txt"};
    string solutions = "Wrap test answers.txt";
   
    vector<int> adLengths;
    vector<int> costs;
    vector<int> split;
    vector<int> cubedVals;
    int billboardLength;
    int numAds;
    int minCost;
    Dynamic();
    ~Dynamic();
    void fillAds(int);
    int BoardCost(int, int);
    int memorized_cut_rod(vector<int> price, int n);
    int memorized_cut_rod();
    int memorized_cut_rod_aux(int n);
    void BoardCostGreedy();
    int cubed(int);
    void setSplit(int, int, int);
    

private:

};

