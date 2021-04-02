#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;
typedef vector<complex<double>> FFT;
#define PI2 -2 * 3.14159265359 

FFT readFile(char[]);
void print_top_polynomial(vector <complex<double>> &);
FFT recursiveFFT(FFT&);
