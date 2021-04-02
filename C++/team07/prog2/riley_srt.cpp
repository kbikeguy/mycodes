/*************************************************************************//**
 * @file
 * @brief Riley's str.cpp functions
 *****************************************************************************/
#include "srt.h"

/**************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This function takes in the size of argc and checks to ensure there is the
 * proper number of arguments.
 *
 * @param[in]      argc - the number of command line arguments

 * @returns true there is the correct amount of command lines.
 * @returns false there are not the correct number of command lines.
 *
 *****************************************************************************/
bool checkCommands ( int argc )
{
    if ( ( argc != 2 ) )
    {
        return false;
    }
    
    return true;
}
/**************************************************************************//**
* @author Riley Campbell
*
* @par Description:
* This function handles prints out the usage statement for this program.
*
*****************************************************************************/
void usageStatement ( )
{
    cout << "Invalid number of command line arguments." << endl
         << "Use command line in the form of: "
         << "prog2 file.str" << endl
         << "Will be able to handle one str input from the"
         << endl << "command line." << endl;
}

/**************************************************************************//**
 * @author Riley Campbell, Dalton Baker, Kenji Johnson
 *
 * @par Description:
 * This function will prompt the user for a frame number to update. After the
 * frame number has been provided, call the retrieve function. Then ask the
 * user to enter a new caption until a blank line is entered.  After the new
 * caption is provided, call the update funtion.  If the caption is empty, do
 * not do an update and display the main menu.  If the frame number requested
 * could not be displayed, output an error message and continue to the main
 * menu.
 *
 * @param[in] list - the srtList to add a frame to
 *
 *****************************************************************************/
void updateFrame ( srtList &list )
{
    int frame;
    string startingTime;
    string endingTime;
    string theCaption;
    string newCaption;
    string captionTemp;
    
    cout << "Update a frame" << endl;
    
    //ask for frame to be updated
    cout << "Enter the frame to be updated: ";
    cin >> frame;
    
    if ( list.retrieve ( frame, startingTime, endingTime, theCaption ) )
    {
        cout << frame << endl;
        cout << startingTime << " --> " << endingTime << endl;
        cout << theCaption << endl << endl;
    }
    
    else
    {
        cout << "Unable to retrieve frame " << frame << " from the ";
        cout << "SRT list to be updated." << endl;
        
        return;
    }
    
    //get caption from user
    cout << "Enter the new caption: ";
    cin.ignore();
    getline ( cin, newCaption );
    getline ( cin, captionTemp );
    
    while ( captionTemp != "" )
    {
        newCaption += "\n" + captionTemp;
        getline ( cin, captionTemp );
    }
    
    //update the caption
    list.update ( frame, newCaption );
}

/**************************************************************************//**
 * @author Riley Campbell, Kenji Johnson
 *
 * @par Description:
 * This function will prompt for the first and last frame numbers and output
 * just those frames to the screen.  If it fail to retrieve a frame, an error
 * message will output and try to print the next one. If the starting frame
 * entered is greater than the ending frame entered, the funtion will return
 * without attempting to print the range of the list.
 *
 * @param[in] list - the srtList to print a frame from.
 *
 *****************************************************************************/
void printRange ( srtList &list )
{
    int i, first, last;
    string startingTime, endingTime, theCaption;
    
    cout << "Print the range of frames" << endl << endl
         << "Enter starting frame: ";
    cin >> first;
    cout << "Enter ending frame: ";
    cin >> last;
    cout << endl;
    
    //check for valid first and last
    if ( last < first )
    {
        cout << "Starting frame is greater than ending frame." << endl;
        return;
    }
    
    //start printing
    for ( i = first; i <= last; i++ )
    {
        if ( list.retrieve ( i, startingTime, endingTime, theCaption ) )
        {
            cout << i << endl;
            cout << startingTime << " --> " << endingTime << endl;
            cout << theCaption << endl << endl;
        }
        
        else
        {
            cout << "Unable to retrieve frame " << i << " from the ";
            cout << "SRT list." << endl << endl;
        }
    }
}