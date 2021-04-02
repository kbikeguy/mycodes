/*************************************************************************//**
 * @file
 * @brief Contains function for checking command line arguments
 ****************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Belt.h"
#include "unsortedDouble.h"
#include "utilities.h"

/**************************************************************************//** 
 * @author Riley Campbell and Matthew White
 * 
 * @par Description: 
 * This function checks that there are three command line arguments and if the
 * third argument is an integer. It outputs a usage statement if there is a 
 * problem with the number of arguments, and it exits if an non-integer is 
 * entered.
 * 
 * 
 * @param[in]      argc - number of command line arguments
 * @param[out]     argv - the 2d array of command line arguments
 * 
 * @returns true program ran successful.
 * @returns false program ran unsuccessful.
 * 
 *****************************************************************************/
bool check_cmln( int argc, char **argv )
{
    int i = 0;
    
    //check for the correct amount of command line parameters
    if( argc != 3 )
    {
        cout << "Usage: To run this program, the required"
            << "command line arguments are as follows:\n\n1) the program name"
            << "\n2) a file with simulation such as boxes.sim\n3) the"
            << " length of the belts" << endl;
        return false;
    }
    //check if the belt length is valid
    while (argv[2][i])
    {
        if (isalpha(argv[2][i]))
        {
            cout << argv[2] << " is an invalid length parameter" << endl;
            return false;
        }
            i++;
    }
    return true;
}


    

