/*************************************************************************//**
 * @file
 * @brief Dalton's strlist.cpp functions
 ****************************************************************************/

#include "srtlist.h"

srtList::~srtList()
{
    node *deleteNode = headptr;
    node *nextNode;
    
    //delete each node in the list
    while ( deleteNode != nullptr )
    {
        nextNode = deleteNode->next;
        delete deleteNode;
        deleteNode = nextNode;
    }
    
    //free headptr
    headptr = nullptr;
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will add a caption to a linked list. It will add it in the
 * correct order by time.
 *
 * @param[in] startingTime - starting time of the caption
 *
 * @param[in] endingTime - ending time of the caption
 *
 * @param[in] theCaption - the caption to be added to the list
 *
 * @returns true - succesfuly added item to list
 *
 * @returns false - failed to add item to list
 *
 *****************************************************************************/
bool srtList::insert ( string startingTime, string endingTime,
                       string theCaption )
{
    node *temp = headptr;
    
    //check if times are valid
    while ( temp != nullptr )
    {
        if ( startingTime > endingTime )
        {
            return false;
        }
        
        if ( temp->endingTime == startingTime || temp->startingTime == endingTime )
        {
            return false;
        }
        
        if ( temp->startingTime == startingTime || temp->endingTime == endingTime )
        {
            return false;
        }
        
        if ( startingTime > temp->startingTime && startingTime < temp->endingTime )
        {
            return false;
        }
        
        if ( endingTime > temp->startingTime && endingTime < temp->endingTime )
        {
            return false;
        }
        
        temp = temp->next;
    }
    
    //create new node check for memory
    temp = new ( nothrow ) node;
    
    if ( temp == nullptr )
    {
        cout << "Not enogh Memory\n";
        return false;
    }
    
    temp->startingTime = startingTime;
    temp->endingTime = endingTime;
    temp->theCaption = theCaption;
    temp->next = nullptr;
    
    //check if the list is empty
    if ( headptr == nullptr )
    {
        headptr = temp;
        return true;
    }
    
    //inserting at front of list
    if ( temp->endingTime <= headptr->startingTime )
    {
        temp->next = headptr;
        headptr = temp;
        return true;
    }
    
    //inserting in middle or end of list
    node *prev = headptr;
    node *curr = headptr;
    
    while ( curr != nullptr && curr->endingTime <= temp->startingTime )
    {
        prev = curr;
        curr = curr->next;
    }
    
    prev->next = temp;
    temp->next = curr;
    
    return true;
}

