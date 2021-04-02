/*************************************************************************//**
 * @file
 * @brief Riley's menu
 .cpp functions
 *****************************************************************************/
#include "menu.h"

/*************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This is the deconstructor function for the menu class
 *
 ****************************************************************************/
menu:: ~menu()
{

}

/*************************************************************************//**
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
 ****************************************************************************/
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

/*************************************************************************//**
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
 ****************************************************************************/
bool menu:: updateMenuItem ( string item, int pos )
{
    if ( ( int ) theMenu.size ( ) >= pos && pos > 0 )
    {
        theMenu.at ( pos ) = item;
        
        if ( theMenu.at ( pos ) == item )
        {
            return true;
        }
        
        return false;
    }
    
    return false;
}