/*************************************************************************//**
 * @file
 * @brief Riley's strlist.cpp functions
 *****************************************************************************/
#include <iostream>
#include "srtlist.h"

using namespace std;

/*************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This function sets the headptr, cuff, and temp to NULL.
 *
 ****************************************************************************/
srtList::srtList()
{
    headptr = NULL;
}

/*************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This function prints the contents of the list to a file till it reaches the
 * end of the list.
 *
 * @param[in,out]  out - the file that will be rewritten.
 *
 ****************************************************************************/

void srtList::printSrt ( ostream &out )
{
    int i = 1;
    node *curr = headptr;
    
    while ( curr != NULL )
    {
        out << i << endl << curr->startingTime << " --> " << curr->endingTime
            << endl <<  curr->theCaption << endl << endl;
        curr = curr->next;
        i++;
    }
}

/**************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This function will change a caption to a linked list. If the desired frame
 * does not exist, the update is empty, or a list doesnt exist, the function
 * will return false. If the caption was successfully changed, the function
 * will return true.
 *
 * @param[in] frame - the frame that will be changed
 *
 * @param[in] theCaption - the caption to be rewritten to the list
 *
 * @returns true - succesfuly rewrote item to list
 *
 * @returns false - failed to rewrite item to list
 *
 *****************************************************************************/
bool srtList::update ( int frame, string theCaption )
{
    int i = 1;
    node *curr = headptr;
    
    //check for invalid frame
    if ( frame < 1 || frame > size() )
    {
        return false;
    }
    
    //check for invalid string
    if ( theCaption.empty() )
    {
        return false;
    }
    
    //check for empty list
    if ( headptr == nullptr )
    {
        return false;
    }
    
    //traverse list
    while ( i < frame )
    {
        curr = curr->next;
        i++;
    }
    
    //update caption
    curr->theCaption = theCaption;
    
    //verify update
    if ( curr->theCaption == theCaption )
    {
        return true;
    }
    
    return false;
}