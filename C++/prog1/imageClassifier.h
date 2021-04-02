/**
* @file
*/
#ifndef __IMAGECLASSIFIER__H__
#define __IMAGECLASSIFIER__H__
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
using namespace std;

bool isBMP ( ifstream &fin );
bool isGIF ( ifstream &fin );
bool isJPG ( ifstream &fin );
bool isPNG ( ifstream &fin );


#endif 
