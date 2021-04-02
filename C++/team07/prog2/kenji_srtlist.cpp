/*************************************************************************//**
 * @file
 * @brief Kenji's strlist.cpp functions
 *****************************************************************************/

#include "srtlist.h"

/**************************************************************************//**
 * @author Kenji Johnson
 *
 * @par Description:
 * This function will retrieve the contents of a specific frame. The function
 * will first check to see if the entered frame is within the range of
 * possible frames. If the frame number is not within the range, the function
 * returns false. If the frame number is within the range, the function will
 * move through the lisgt to find the frame to be retrieved. If the frame is
 * found, the starting time, ending time, and caption is copied and the
 * function returns true. If the frame is not found, the function returns
 * false.
 *
 * @param[in] frame - the frame to be retrieved
 *
 * @param[in] startingTime - starting time of the caption
 *
 * @param[in] endingTime - ending time of the caption
 *
 * @param[in] theCaption - the caption contained in the frame
 *
 * @returns true - successfully retrieved the starting time, ending time,
 * and the caption of the frame
 *
 * @returns false - failed to retrieve the contents of the frame
 *
 *****************************************************************************/
bool srtList::retrieve ( int frame, string &startingTime, string &endingTime,
                         string &theCaption )
{
    node *temp = headptr;
    int count = 1;
    
    //check if the frame is valid (if invalid return false)
    //check if less than 1
    if ( frame < 1 || frame > size() + 1 )
    {
        return false;
    }
    
    
    while ( temp != nullptr )
    {
        if ( count == frame )
        {
            //copy starting time
            startingTime = temp->startingTime;
            
            //copy ending time
            endingTime = temp->endingTime;
            
            //copy caption
            theCaption = temp->theCaption;
            
            return true;
            
        }
        
        count++;
        temp = temp->next;
        
    }
    
    return false;
    
}