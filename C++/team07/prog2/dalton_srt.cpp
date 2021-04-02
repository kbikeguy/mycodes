/*************************************************************************//**
 * @file
 * @brief Dalton's str.cpp functions
 ****************************************************************************/
#include "srt.h"


/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will check a time to make sure it is in the valid form.
 *
 * @param[in] time - the time to be checked
 *
 * @returns true - time is valid
 *
 * @returns false - time is invalid
 *
 *****************************************************************************/
bool checkTime ( string time )
{
    //check length of stiring
    if ( time.size() != 12 )
    {
        return false;
    }
    
    bool check = true;
    
    //check hour location
    check = check && isdigit ( time.at ( 0 ) ) && isdigit ( time.at ( 1 ) );
    //check minute location
    check = check && isdigit ( time.at ( 3 ) ) && isdigit ( time.at ( 4 ) );
    //check second location
    check = check && isdigit ( time.at ( 6 ) ) && isdigit ( time.at ( 7 ) );
    //check milliseconds location
    check = check && isdigit ( time.at ( 9 ) ) && isdigit ( time.at ( 10 ) )
            && isdigit ( time.at ( 11 ) );
    //check punctuation
    check = check && ( time.at ( 2 ) == ':' ) && ( time.at ( 5 ) == ':' ) &&
            ( time.at ( 8 ) == ',' );
            
    return check;
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will give you to contents of the main menu
 *
 * @returns menu - the main menu contents
 *
 *****************************************************************************/
vector<string> mainMenuContents ()
{
    vector<string> menu;
    
    menu = { "Add a Subtitle Frame", "Remove a frame",
             "Retrieve a frame", "Update a frame",
             "Print subtitles to screen",
             "Print range of subtitles", "Exit"
           };
           
    return menu;
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will give you to contents of the sub menu
 *
 * @param[in] file_name - the name of the default file
 *
 * @returns menu - the sub menu contents
 *
 *****************************************************************************/
vector<string> subMenuContents ( string file_name )
{
    vector<string> menu;
    
    menu = { "Save to \"" + file_name + "\" and exit", "Save to a new file",
             "Exit without saving"
           };
           
    return menu;
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will give you to contents of the sub menu
 *
 * @param[in] selection - the menu selection
 *
 * @param[in] list - the srtList containing the frames to be prcessed
 *
 * @returns true - the menu should continue to display
 *
 * @returns false - the user wants to exit
 *
 *****************************************************************************/
bool processMainMenu ( int selection, srtList &list )
{
    cout << endl;
    
    //process proper choice
    switch ( selection )
    {
        case 1:
            //Add a Subtitle Frame
            addFrame ( list );
            cout << endl;
            return true;
            
        case 2:
            //Remove a frame
            removeFrame ( list );
            cout << endl;
            return true;
            
        case 3:
            //Retrieve a frame
            retrieveFrame ( list );
            return true;
            
        case 4:
            //Update a frame
            updateFrame ( list );
            return true;
            
        case 5:
            //Print subtitles to screen
            list.printSrt ( cout );
            return true;
            
        case 6:
            //Print range of subtitles
            printRange ( list );
            return true;
            
        case 7:
            return false;
    }
    
    //only here to stop the compiler from complaining
    return true;
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will read all contents of an srt file to an srtList
 *
 * @param[in] list - the list we will save all the file contents to
 *
 * @param[in] file_name - name of the file to read from
 *
 *****************************************************************************/
void readFileContents ( srtList &list, string file_name )
{
    //temporary variable to hold each srt entry
    int tempFrame;
    string startTime;
    string endTime;
    string caption;
    string captionTemp;
    
    //open file and test if it's open
    ifstream srtFile ( file_name.c_str() );
    
    /*if ( !srtFile.is_open() )
    {
        cout << "Input file \"" << file_name;
        cout << "\" could not be opened" << endl;
        exit ( 1 );
    }*/
    
    while ( srtFile >> tempFrame )
    {
        //read in times
        srtFile.ignore ( 1 );
        getline ( srtFile, startTime, ' ' );
        srtFile.ignore ( 4 );
        getline ( srtFile, endTime );
        
        //read a caption untill an empty line
        getline ( srtFile, caption );
        
        while ( srtFile.peek() != '\n' )
        {
            getline ( srtFile, captionTemp );
            caption += "\n" + captionTemp;
        }
        
        //ignore empty line
        srtFile.ignore ( 1 );
        
        //store the entry to the list
        if ( checkTime ( startTime ) && checkTime ( endTime ) )
        {
            list.insert ( startTime, endTime, caption );
        }
    }
    
    //close the file
    srtFile.close();
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will save the contents of the srtList to the file
 *
 * @param[in] list - the contents of the list
 *
 * @param[in] file_name - the name of the default file
 *
 *****************************************************************************/
void saveSrtFile ( srtList &list, string file_name )
{
    //open file and test if it's open
    ofstream srtFile;
    srtFile.open (  file_name.c_str(), ios::out | ios::trunc );
    
    if ( !srtFile.is_open() )
    {
        cout << "Input file \"" << file_name;
        cout << "\" could not be opened" << endl;
        exit ( 1 );
    }
    
    //write data to file
    list.printSrt ( srtFile );
    
    //close file
    srtFile.close();
}

/**************************************************************************//**
 * @author Dalton Baker
 *
 * @par Description:
 * This function will add a frame to the srtList provided
 *
 * @param[in] list - the srtList to add a frame to
 *
 *****************************************************************************/
void addFrame ( srtList &list )
{
    //temporary variable to hold user input data
    string startTime;
    string endTime;
    string caption;
    string captionTemp;
    
    //get start time from user
    cout << "Enter the starting time for the new frame: ";
    cin >> startTime;
    
    //get end time from user
    cout << "Enter the ending time for the new frame: ";
    cin >> endTime;
    
    //get caption from user
    cout << "Enter the new caption: ";
    cin.ignore();
    getline ( cin, caption );
    getline ( cin, captionTemp );
    
    while ( captionTemp != "" )
    {
        caption += "\n" + captionTemp;
        getline ( cin, captionTemp );
    }
    
    //check that the entries were valid
    if ( !checkTime ( startTime ) )
    {
        cout << "Starting time is not valid" << endl;
        return;
    }
    
    if ( !checkTime ( endTime ) )
    {
        cout << "Ending time is not valid" << endl;
        return;
    }
    
    if ( startTime > endTime )
    {
        cout << "Start time must come before end time" << endl;
        return;
    }
    
    if ( caption == "" )
    {
        cout << "The caption is empty" << endl;
        return;
    }
    
    //insert the frame
    if ( !list.insert ( startTime, endTime, caption ) )
    {
        cout << "Unable to insert the frame into the SRT list" << endl;
    }
}