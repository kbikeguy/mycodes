/**************************************************************************//**
 * @file
 * @brief Menu
 .cpp functions
 *****************************************************************************/
#include "menu.h"

/**************************************************************************//**
 * @author Riley Campbell
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
 * @author Riley Campbell
 *
 * @par Description:
 * This is a menu contructtor
 *
 * @param[in, out] menuList - a vector of strings containing a menu
 *
 *****************************************************************************/
menu::menu ( vector<string> &menuList )
{
    //makes the menu items the elements of the passed in vector
    theMenu = menuList;
}

/**************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This is a menu constructor
 *
 * @param[in, out] aMenu - an already existing menu
 *
 *****************************************************************************/
menu::menu ( menu &aMenu )
{
    //makes a new menu with that is identical to a passed in menu
    theMenu = aMenu.theMenu;
}

/**************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This is the deconstructor function for the menu class
 *
 *****************************************************************************/
menu:: ~menu()
{

}

/**************************************************************************//**
 * @author Riley Campbell
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
    if ( pos < 0 || pos > (int)theMenu.size() )
    {
        return false;
    }
    
    //insert the item and return true
    theMenu.insert ( theMenu.begin() + pos, item );
    return true;
}

/**************************************************************************//** 
 * @author Riley Campbell
 *
 * @par Description:
 * This function removes a section of the menu
 *
 * @param[in]      pos - the position of the menu that will be erased
 *
 * @returns true the menue item was successfully erased.
 * @returns false the menue item was not successfully erased.
 *
 *****************************************************************************/
bool menu:: removeMenuItem ( int pos )
{
    //return false if the position is invalid
    if ( pos < 1 || pos > ( int ) theMenu.size() )
    {
        return false;
    }
    
    //remove the item and return true
    theMenu.erase ( theMenu.begin() + ( pos - 1 ) );
    return true;
}

/**************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This function updates a menu item
 *
 * @param[in]      item - the string for the new menu item
 * @param[in]      pos  - the position in the menu where
 *                        the update will be made
 *
 * @returns true the update was made
 * @returns false the the update was not made.
 *
 *****************************************************************************/
bool menu:: updateMenuItem ( string item, int pos )
{
    pos--;
    if ( ( int ) theMenu.size ( ) >= pos  && pos >= 0 )
    {
        theMenu.at ( pos ) = item;

        if ( theMenu.at ( pos ) == item )
        {
            return true;
        }
    }

    return false;
}

/**************************************************************************//**
* @author Riley Campbell
*
* @par Description:
* This function prints out a menu
*
******************************************************************************/
void menu::printMenu()
{
    int i;
    
    //for every menu item
    for ( i = 0; i < (int)theMenu.size(); i++ )
    {
        //print the name of the menu item
        cout << "  " << i + 1 << ".) " << theMenu.at ( i ) << endl;
    }
}

/**************************************************************************//**
 * @author Riley Campbell
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
    while ( user_choice < 1 || user_choice > (int)theMenu.size() )
    {
        cout << "\nInvalid Option\n\n";
        cout << "Enter Choice: ";
        cin >> user_choice;
    }
    
    //return the user input
    return user_choice;
}

/**************************************************************************//**
 * @author Riley Campbell
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
 * @author Riley Campbell
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