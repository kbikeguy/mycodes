/*************************************************************************//**
 * @file 
 *
 * @mainpage program 1 - prog1
 * 
 * @section course_section Course Information 
 *
 * @author Riley Campbell
 * 
 * @date 2/23/2018
 * 
 * @par Professor: 
 *         Roger Schrader 
 * 
 * @par Course: 
 *         CSC215 - M001 -  11:00 am
 * 
 * @par Location: 
 *         Classroom Building - 205E
 *
 * @section program_section Program Information 
 * 
 * @details This program takes in directories from the command line and goes 
 * file by file through the directory. Everytime it finds an image file, it
 * determines the type of image and if it is a bmp, png, or gif, it also finds 
 * the height and width of the image. Next it renames the file adding in the 
 * width, height, and type extention. Once the end of the directory is reached,
 * the program will change back to the origonal directory and check to see if 
 * there is a new directory in the command line. If there is a new directory,
 * the program will enter into the next directory and resume checking and 
 * renaming image files. If there is no new directory, the program will return
 * zero and exit.
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      takes in directories from the command line. will not run without them. 
 * 
 * @par Usage: 
   @verbatim  
   c:\> prog1.exe dir1 dir2 dir3 dirn
   d:\> c:\bin\prog1.exe 
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug none
 * 
 * @todo none
 * 
 * @par Modifications and Development Timeline: 
 *  
 *
 * <a href = "https://gitlab.mcs.sdsmt.edu/7356506/csc215s18programs/commits/master"
 *         >Commit Log. </a>    
 *
 *****************************************************************************/

#include "imageClassifier.h"
#include "imageDimensions.h"
#include "utilities.h"
using namespace std;

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This funtion takes in the argc and argv command line parameters to find
 * each derectory that will be searched. 
 * 
 * @param[in]      argc - the amount of items in the command line
 * @param[in]      argv - the contents of the command line
 * 
 * @returns 0 program ran successful.
 * 
 *****************************************************************************/
int main ( int argc, char **argv )
{
    int i;
    char origonalDir[_MAX_PATH] = "";
    char tempDir[_MAX_PATH] = "";
    ifstream fin;
    _finddata_t aFile;
    intptr_t dHandle;
    char pattern[30] = "*.*";
    string filename = "";
    unsigned int width = 0, height = 0;
    
    
   //1. Check command line arguments. 
   if ( !checkCommands ( argc ) )
    {
       //program usage
       usageStatement();
       exit ( 1 );
    }
    //set origonal dir
   _getcwd ( origonalDir, _MAX_PATH );
    for ( i = 1; i < argc; i++ )
    {
        //Check that the specified directory exists and 
        //change to that directory
        strcpy ( tempDir, argv[i] );

        if ( strcmp ( tempDir, argv[i] ) == 0 )
        {
            if ( _chdir(tempDir) == 0 )
            {
                //Read in first filename
                dHandle = _findfirst(pattern, &aFile);
                if ( dHandle == -1 )
                    return 1;


                do
                {
                    //Check if it is an image file
                    if ( ! ( aFile.attrib & _A_SUBDIR ) )
                    {
                        fin.open ( aFile.name, ios::in | ios::binary );
                        if ( fin )
                        {
                            dirSearch ( fin, width, height, filename,
                                aFile.name, aFile );
                        }
                        fin.close ( );
                       // renameFile ( aFile, filename );
                    }
                } while ( _findnext ( dHandle, &aFile ) == 0 );
                _findclose ( dHandle );
                _chdir ( origonalDir );    
            }
            else
            {
                cerr << "Unable to process the directory " << tempDir << endl;
            }
        }
    }
    return 0;
}

