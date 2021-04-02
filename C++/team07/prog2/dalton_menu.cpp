/*************************************************************************//**
 * @file
 * @brief Daltons menu.cpp functions
 ****************************************************************************/

#include "menu.h"

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function initiates a new menu with nothing stored in it.
 *
 *****************************************************************************/
menu::menu ( )
{
    //make sure the menu is empty
    theMenu = {};
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will add items to the menu in the position the user indicates.
 *
 * @param[in] item - the menu item to be added
 *
 * @param[in] pos - the position in the menu the item will be added to
 *
 * @returns true - succesfuly added menu item
 *
 * @returns false - failed to add menu item
 *
 *****************************************************************************/
bool menu::addMenuItem ( string item, int pos )
{
    //reduce position by one so it works with vector functions
    pos -= 1;
    
    //return false if the position is invalid
    if ( pos < 0 || pos > theMenu.size() )
    {
        return false;
    }
    
    //insert the item and return true
    theMenu.insert ( theMenu.begin() + pos, item );
    return true;
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will give you the size of the menu
 *
 * @returns size - the size of the menu
 *
 *****************************************************************************/
int menu::size()
{
    //get the size of the menu
    int size = ( int ) theMenu.size();
    
    //return the menu size
    return size;
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will completely clear the menu
 *
 *****************************************************************************/
void menu::clear()
{
    //clear the menu
    theMenu.clear();
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will get a selection from the user, it will also optionally
 * print the menu
 *
 * @param[in] withMenu - this will determine if the manu is printed or not
 *
 * @returns user_choice - the integer that the user chose
 *
 *****************************************************************************/
int menu::getMenuSelection ( bool withMenu )
{
    //vaiable to hold users input
    int user_choice = 0;
    
    //print menu if it's required
    if ( withMenu )
    {
        menu::printMenu();
    }
    
    //get the users selection
    cout << "Enter Choice: ";
    cin >> user_choice;
    
    //check the users input
    while ( user_choice < 1 || user_choice > theMenu.size() )
    {
        cout << "\nInvalid Option\n\n";
        cout << "Enter Choice: ";
        cin >> user_choice;
    }
    
    //return the user input
    return user_choice;
}