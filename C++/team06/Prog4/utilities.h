/**************************************************************************//**
 * @file
 * @brief Header file to be used for each group member's cpp functions.
 *****************************************************************************/


#ifndef __UTILITIEST__H
#define __UTILITIEST__H
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Belt.h"

using namespace std;

bool check_cmln(int argc, char **argv);
void openFiles(ifstream &fin, char **argv, ofstream &fout);
bool readBelts(ifstream &fin, int belt[], int A, int B, int C);
bool readBox(int n, ifstream fin, box aBox);
void sortBelt(int beltWidths[], char beltNames[], int size);
void rotateBox(box &package);
int whichBelt(box aBox, conveyorBelt beltArr[]);
void boxProcessing(box aBox, conveyorBelt beltArr[], ofstream &fout);

#endif