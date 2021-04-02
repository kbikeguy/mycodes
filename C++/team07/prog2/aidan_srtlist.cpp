/*************************************************************************//**
 * @file
 *
 * @brief Aidan's srtlist.cpp functions
 *
 *****************************************************************************/
#include "srtlist.h"

/**************************************************************************//**
 * @author Aidan Anderson
 *
 * @par Description:
 * This function will remove a frame from the srtList
 *
 * @param[in] frame - the position of the frame to remove
 *
 * @returns true - the frame was removed
 *
 * @returns false - the frame was not removed
 *
 *****************************************************************************/
bool srtList::remove ( int frame )
{
    node *curr = headptr;
    node *prev = headptr;
    int count = 1;
    
    //returns false if user tries to remove a frame before 0 or 0
    if ( frame <= 0 )
    {
        return false;
    }
    
    //returns false if user tries to remove a frame after the last frame
    if ( frame > size() )
	{
        return false;
    }
    
    //covers the case of removing the first frame
    if ( frame == 1 )
    {
        headptr = headptr->next;
        delete curr;
        return true;
    }
    
    //traversal
    while ( count != frame )
    {
        prev = curr;
        curr = prev->next;
        count++;
    }
    
    //middle
    if ( curr->next != nullptr )
    {
        prev->next = curr->next;
        delete curr;
        return true;
    }
    
    //end
    if ( curr->next == nullptr )
    {
        prev->next = curr->next;
        delete curr;
        return true;
    }
    return false;
}

/**************************************************************************//**
 * @author Aidan Anderson
 *
 * @par Description:
 * This function will return the number of items in an srtList
 *
 * @returns count - the size of the srt list
 *
 *****************************************************************************/
int srtList::size()
{
    node *temp = headptr;
    int count = 0;
    
    //walk through and count each item
    while ( temp != nullptr )
    {
        count++;
        temp = temp->next;
    }
    
    //return the number
    return count;
}

