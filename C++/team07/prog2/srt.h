/*************************************************************************//**
 * @file
 * @brief Header file to be used with str.cpp from each group member.
 ****************************************************************************/

#ifndef __SRT__H__

#define __SRT__H__

#include <iostream>
#include <fstream>
#include <string.h>
#include <cctype>
#include <vector>
#include <string>
#include "srtlist.h"
#include "menu.h"

using namespace std;

bool checkCommands ( int argc );
void usageStatement();
bool checkTime ( string time );
vector<string> mainMenuContents();
vector<string> subMenuContents ( string file_name );
bool processMainMenu ( int selection, srtList &list );
void readFileContents ( srtList &list, string file_name );
void saveSrtFile ( srtList &list, string file_name );
void addFrame ( srtList &list );
void removeFrame ( srtList &list );
void retrieveFrame ( srtList &list );
void updateFrame ( srtList &list );
void printRange ( srtList &list );

#endif