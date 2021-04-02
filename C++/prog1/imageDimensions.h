/**
* @file
*/
#ifndef __IMAGEDIMENSIONS__H__
#define __IMAGEDIMENSIONS__H__
#include <fstream>
#include <iostream>
using namespace std;
//void imgDim(ifstream &fin, unsigned int &w, unsigned int &h, int type);
void pngSize ( ifstream &fin, unsigned int &w, unsigned int &h );
void gifSize ( ifstream &fin, unsigned int &w, unsigned int &h );
void bmpSize ( ifstream &fin, unsigned int &w, unsigned int &h );
#endif 