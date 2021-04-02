/*************************************************************************//**
 * @file
 * @brief Header file to be used with menu.cpp from each group member.
 ****************************************************************************/

#ifndef __MENU__H__
#define __MENU__H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*!
* @brief A class to easily create and manipulate a menu
*/
class menu
{
    public:
        menu ( ); /*!<Constructor for the menu*/
        menu ( vector<string> &menuList );
        menu ( menu &aMenu );
        ~menu ( );
        
        bool addMenuItem ( string item, int pos );
        bool removeMenuItem ( int pos );
        bool updateMenuItem ( string item, int pos );        
        void printMenu();
        int getMenuSelection ( bool withMenu = true );
        int size();
        void clear();
        
    private:
        /*! A vector of strings containg all menu options */
        vector<string> theMenu;
};

#endif