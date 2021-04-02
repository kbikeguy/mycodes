/**
* @file
*/
#include "imageClassifier.h"
#include <iostream>
//write your funtions to classify image here
/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function takes in a file and checked the values of the first 2 bytes.
 * If the bytes contain 'BM' it is a bmp file, otherwise it is not.
 * 
 * 
 * @param[in,out]  fin - the file that will be searched to determin its type
 * 
 * @returns true the file is a bmp
 * @returns false the file is not a bmp
 * 
 *****************************************************************************/
bool isBMP( ifstream &fin )
{
    char bmp[3] = { 'B', 'M' }, 
         temp[3] = "";
    fin.seekg ( 0, ios::beg );
    fin.read ( ( char* ) &temp, 2 );
    if ( strcmp ( bmp, temp ) == 0 )
    {    
         return true;
    }
    return false;
}
/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function takes in a file and checked the values of the first 6 bytes.
 * If the bytes contain "GIF89a" or "GIF87a" it is a gif file, otherwise
 * it is not.
 * 
 * 
 * @param[in,out]  fin - the file that will be searched to determin its type
 * 
 * @returns true the file is a gif
 * @returns false the file is not a gif
 * 
 *****************************************************************************/
bool isGIF( ifstream &fin )
{
    char gif1[] = { "GIF89a" };
    char gif2[] = { "GIF87a" };
    char temp[7] = "";
    fin.seekg ( 0, ios::beg );
    fin.read ( ( char* ) &temp, 6 );
    if ( strcmp ( gif1, temp ) == 0 || strcmp ( gif2, temp ) == 0 )
    {            
         return true;
    }
        
    return false;
}
/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function takes in a file and checked the values of the first 2 bytes
 * and the last 2 bytes. If the bytes contain values ( 255, 216 ) and 
 * ( 255, 217 ) respectivly it is a jpg file, otherwise it is not.
 * 
 * 
 * @param[in,out]  fin - the file that will be searched to determin its type
 * 
 * @returns true the file is a jpg
 * @returns false the file is not a jpg
 * 
 *****************************************************************************/
bool isJPG( ifstream &fin )
{
    unsigned char jpg1[3] = { 255, 216 },
        jpg2[3] = { 255, 217 },
        temp1[3] = { '0' },
        temp2[3] = { '0' };
    int count = 0;
    fin.seekg ( 0, ios::beg );
    fin.read ( ( char* ) &temp1, 2 );
    fin.seekg ( ios::beg, ios::end );
    count = (int)fin.tellg ( );
    count = count - 2;
    fin.seekg ( count, ios::beg );
    fin.read ( ( char* ) &temp2, 2 );

    if ( jpg1[0] == temp1[0] && jpg1[1] == temp1[1] && jpg2[0] == temp2[0] && 
        jpg2[1] == temp2[1] )
    {
        return true;
    }

    return false;
}
/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function takes in a file and checked the values of the first 8 bytes
 * If the bytes contain the values ( 137, 80, 78, 71, 13, 10, 26, 10 )
 * it is a png file, otherwise it is not.
 * 
 * 
 * @param[in,out]  fin - the file that will be searched to determin its type
 * 
 * @returns true the file is a png
 * @returns false the file is not a png
 * 
 *****************************************************************************/
bool isPNG( ifstream &fin )
{
    char arr_png[9] = { (char) 137, 80, 78, 71, 13, 10, 26, 10 }, 
         temp[9] = "";
    
        fin.seekg ( ios::beg );
        fin.read ( ( char* ) &temp, 8 );
        if ( strcmp ( arr_png, temp ) == 0 )
        {
            return true;
        }
            
    return false;
}
