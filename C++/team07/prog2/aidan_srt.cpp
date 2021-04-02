/*************************************************************************//**
 * @file
 *
 * @brief Aidan's srt.cpp functions
 *
 ****************************************************************************/
#include "srt.h"

/**************************************************************************//**
 * @author Aidan Anderson
 *
 * @par Description:
 * This function will get a frame to remove from the user, then remove it
 *
 * @param[in] list - the list we will be removing a frame from
 *
 *****************************************************************************/
void removeFrame ( srtList &list )
{
    //get frame from user
    int frame;
    cout << "Enter the frame number to be removed: ";
    cin >> frame;
    
    //remove the frame
    if ( !list.remove ( frame ) )
    {
        cout << "Unable to remove frame " << frame << " from the SRT list.\n";
    }
}