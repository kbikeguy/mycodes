/**
* @file
*/
#include "utilities.h"

//all other functions except main, classifiers, and dimensions are written here

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function takes in the origonal name of a file, the width, the height,
 * and the type. It then forms a new file name in the form of 
 * name_widthxheight.type
 * 
 * @param[in,out]  file - a string that will be filled with the name of the 
 *                        reformed file name.
 * @param[in]   oldname - the name of the origonal file.
 * @param[in]         W - the width of the file image.
 * @param[in]         H - the height of the file image.
 * @param[in]      type - the type of file that will be renamed.
 *****************************************************************************/
void newFileName ( string &file, char* oldname, int W, int H, int type )
{
    switch ( type )
    {
        //1 = bmp, 2 = gif, 3 = png, 4 = jpg
    case 1:
        file = oldname;
        file += "_" + to_string( W ) + "x" + to_string( H ) + ".bmp";
        break;

    case 2:
        file = oldname;
        file = file + "_" + to_string( W ) + "x" + to_string( H ) + ".gif";
        break;

    case 3:
        file = oldname;
        file = file + "_" + to_string( W ) + "x" + to_string( H ) + ".png";
        break;
        
    case 4:
        file = oldname;
        file += ".jpg";
        break;

    default:
        cout << "Invalid file type" << endl;
    }
}
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
bool checkCommands( int argc )
{
    if ( !( argc > 1 ) )
    {
        return false;
    }
    return true;
}
/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function takes in the file to be renamed and the the name is shall be
 * changed to. It changes the newname string to a cstyle string and uses the 
 * newname function from the c++ library to rename the file. If the file can't
 * be renamed, a message will be display.
 * 
 * @param[in]     oldname - the file to be renamed
 * @param[in]     newname - the name for which the file will be rewritten to
 * 
 *****************************************************************************/
void renameFile( _finddata_t oldname, string newname )
{
    char * cstr = new char [newname.length ( ) + 1];
    strcpy ( cstr, newname.c_str ( ) );
   
    if ( rename ( oldname.name, cstr ) != 0 )
    {
        cout << "Could not change " << oldname.name << " ==> " << cstr << endl;
    }
    delete[] cstr;  
}
/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function handles all the if statements required to call each of the 
 * functions needed to determin the width, height, and new name of each 
 * image file.
 * 
 * @param[in, out]       fin - the file that will be read in
 * @param[in, out]     width - the width of the current image
 * @param[in, out]    height - the height of the current image
 * @param[in, out]  filename - the name the file will be changed to
 * @param[in]        oldname - the origonal name of the file
 * 
 *****************************************************************************/
void dirSearch ( ifstream &fin, unsigned int &width, unsigned int & height,
                 string & filename, char* oldname, _finddata_t name )
{
    //1 = bmp, 2 = gif, 3 = png, 4 = jpg
    if ( isBMP ( fin ) )
    {
        bmpSize ( fin, width, height );
        newFileName ( filename, oldname, width,
            height, bmp );
        fin.close ( );
        renameFile ( name, filename );
    }
    else if ( isGIF ( fin ) )
    {
        gifSize ( fin, width, height );
        newFileName ( filename, oldname, width, 
            height, gif );
        fin.close ( );
        renameFile ( name, filename );
    }
    else if ( isPNG ( fin ) )
    {
        pngSize ( fin, width, height );
        newFileName ( filename, oldname, width,
            height, png );
        fin.close ( );
        renameFile ( name, filename );
    }
    else if ( isJPG ( fin ) )
    {
        newFileName ( filename, oldname, width,
            height, jpg );
        fin.close ( );
        renameFile ( name, filename );
    }
    fin.close ( );
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
        << "Use command lines in the form of: " 
        << "prog1 dir1 dir2 dir3 dirn" << endl
        << "Will be able to handle any amount of directories input from the"
        << endl << "command line." << endl;

}