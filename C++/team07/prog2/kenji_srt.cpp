/*************************************************************************//**
 * @file
 * @brief Kenji's srt.cpp functions
 ****************************************************************************/
#include "srt.h"


/**************************************************************************//**
 * @author Kenji Johnson
 *
 * @par Description:
 * This function retrieves and displays a frame based on the user's frame
 * of choice. Once the menu option is selected for retrieve frame, this
 * function is called, and prompts for the frame number to be retrieved.
 * Once a frame number is entered, the retrieve function is called, and
 * if the frame was successfully retrieved, the frame number, starting time
 * and ending time, and the caption of the frame will be printed. If the
 * retrieve function fails, an error message will be displayed.
 *
 * @param[in] list - the frame to be retrieved
 *
 *****************************************************************************/
void retrieveFrame ( srtList &list )
{
    int frame = 0;
    string startingTime;
    string endingTime;
    string theCaption;
    
    cout << "Enter the frame number to be retrieved: ";
    
    cin >> frame;
    
    cout << endl;
    
    //retrieve and print frame info
    if ( list.retrieve ( frame, startingTime, endingTime, theCaption ) )
    {
        cout << frame << endl;
        cout << startingTime << " --> " << endingTime << endl;
        cout << theCaption << endl << endl;
        
        return;
    }
    
    else
    {
        cout << "Unable to retrieve frame " << frame << " from the ";
        cout << "SRT list." << endl;
        
        return;
    }
    
}