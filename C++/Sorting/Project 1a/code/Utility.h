#pragma once
#include <iostream>
#include <iomanip>
#include <time.h>
#include <chrono>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

vector<int> getInput();
void insert(vector<int> &);
void merge(vector<int> &, int, int, int);
void mergeSort(vector<int> &, int, int);
void print(vector<int>);
void timeTests(ofstream &);
vector<int> randomInput(int);