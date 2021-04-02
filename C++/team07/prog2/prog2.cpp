/*************************************************************************//**
 * @file
 * @brief Start of the program, only contains main.
 ****************************************************************************/

/*************************************************************************//**
 * @file
 *
 * @mainpage Program 2 - The SRT Editor
 *
 * @section course_section Course Information
 *
 * @authors Aidan Anderson, Dalton Baker, Riley Campbell, & Kenji Johnson
 *
 * @date 3 / 26 / 2018
 *
 * @par Professor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 215 - Section M001 - 11:00AM
 *
 * @par Location:
 *         McLaury - Room 205E
 *
 * @section program_section Program Information
 *
 * @details This program will allow you to edit an SRT file, which contains the
 *  subtitles of a video file. The program will let you add frames, remove
 *  frames, update existing frames, print all frames, print specific frames,
 *  and save the result to a file of your choice.
 *
 *  The program will be run from a comand line. You will need to pass the file
 *  want to load as an argument. Once opened the program will allow you to
 *  edit the file in the manner stated above.
 *
 *  Once you are finished editing the file you can print the results to the
 *  screen to check your work. When you are happy with your results, you can
 *  save them to the original file, save them to a new file, or throw away all
 *  of your hard work.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      Compile like any normal program
 *
 * @par Usage:
 * You must provide an srt file to the program
   @verbatim
   c:\> prog2.exe example.srt
   c:\> prog2.exe c:\bin\example2.srt
   d:\> c:\bin\prog2.exe exmaple3.srt
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug Nothing known currently
 *
 * @todo Everything is finished, program should be fully functional
 *
 * @par Modifications and Development Timeline:
 * <a href="https://gitlab.mcs.sdsmt.edu/csc215s18prog2/team07/commits/master">
 * Click Here </a> for a list of all contributions made to this program.
 *
 ****************************************************************************/

#include "menu.h"
#include "srt.h"
#include "srtlist.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**************************************************************************//**
 * @author Aidan Anderson, Dalton Baker, Riley Campbell, & Kenji Johnson
 *
 * @par Description:
 * This is the main function, the program starts here.
 *
 * @param[in]  argc - The number of arguments provided to the program
 * @param[in]  argv - A 2D array containing the arguments provided
 *                      to the program.
 *
 * @returns 0 The program ran with no errors.
 * @returns 1 Something went wrong in the program.
 *
 *****************************************************************************/
int main ( int argc, char **argv )
{
    //check argc
    if ( !checkCommands ( argc ) )
    {
        //program usage
        usageStatement();
        exit ( 1 );
    }
    
    //create new srtList and fill with info from file
    srtList ourList;
    readFileContents ( ourList, argv[1] );
    
    //make main menu
    vector<string> menuCont = mainMenuContents();
    menu mainMenu ( menuCont );
    
    //make sub menu
    menuCont = subMenuContents ( argv[1] );
    menu subMenu ( menuCont );
    
    //process file untill we quit
    do
    {
        cout << "Number of frames: " << ourList.size() << endl;
    }
    while ( processMainMenu ( mainMenu.getMenuSelection(), ourList ) );
    
    //show sub menu after quitting
    int subSelection = subMenu.getMenuSelection();
    
    //save file with the default name
    if ( subSelection == 1 )
    {
        saveSrtFile ( ourList, argv[1] );
    }
    
    //save file with user selected name
    else if ( subSelection == 2 )
    {
        string file_name;
        cout << "Enter the new file name: ";
        cin >> file_name;
        saveSrtFile ( ourList, file_name );
    }
    
    return 0;
}