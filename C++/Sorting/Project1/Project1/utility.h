#pragma once
#include <iostream>
#include <iomanip>
#include <time.h>
#include <chrono>
#include <vector>
#include <math.h>

using namespace std;

vector<int> getInput();
void insert(vector<int> &v);
void merge(vector<int> &v, int p, int q, int r);
void mergeSort(vector<int> &v, int p, int r);
void print(vector<int> v);