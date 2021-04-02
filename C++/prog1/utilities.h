/**
 * @file
 */

#ifndef __UTILITIES__H__
#define __UTILITIES__H__
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <io.h>
#include "imageClassifier.h"
#include "imageDimensions.h"


using namespace std;
/**
 * @brief Constants for image Type 
 */
const enum imageType{bmp = 1, /*!< Contains the value 1 representing bmp */
gif,/*!< Contains the value 2 representing gif */
png,/*!< Contains the value 3 representing png */
jpg/*!< Contains the value 4 representing jpg */
};

void newFileName ( string &file, char* oldname, int W, int H, int type );
bool checkCommands ( int argc );
void renameFile ( _finddata_t oldname, string newname );
void dirSearch ( ifstream &fin, unsigned int &width, unsigned int & height,
    string & filename, char* oldname, _finddata_t name );
void usageStatement ( );
#endif

