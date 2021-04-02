/***************************************************************************//**
 * @file
 *
 * @brief Has all functions from the menu class written by Aidan Anderson
 *
 ******************************************************************************/
#include "menu.h"

/***************************************************************************//**
 * @author Aidan anderson
 *
 * @par Description:
 * This is a menu constructor
 *
 * @param[in] aMenu - an already existing menu
 *
 ******************************************************************************/
menu::menu ( menu &aMenu )
{
    //makes a new menu with that is identical to a passed in menu
    theMenu = aMenu.theMenu;
}

/***************************************************************************//**
 * @author Aidan Anderson
 *
 * @par Description:
 * This is a menu contructtor
 *
 * @param[in] menuList - a vector of strings containing a menu
 *
 ******************************************************************************/
menu::menu ( vector<string> &menuList )
{
    //makes the menu items the elements of the passed in vector
    theMenu = menuList;
}

/***************************************************************************//**
* @author Aidan anderson
*
* @par Description:
* This function prints out a menu
*
******************************************************************************/
void menu::printMenu()
{
    int i;
    
    //for every menu item
    for ( i = 0; i < theMenu.size(); i++ )
    {
        //print the name of the menu item
        cout << "  " << i + 1 << ".) " << theMenu.at ( i ) << endl;
    }
}