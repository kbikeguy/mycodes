/**
* @file
*/
#include "imageDimensions.h"
using namespace std;
/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function takes in a png file and reads the 17, 18, 19, 20 bytes to 
 * find the image width and reads in the 21, 22, 23, 24 bytes to find the 
 * image hight.
 * 
 * @param[in, out] fin - a file that will be read to determin its width/height
 * @param[in, out]   w - the width of the image 
 * @param[in, out]   h - the height of the image
 * 
 *****************************************************************************/
void pngSize ( ifstream &fin, unsigned int &w, unsigned int &h )
{
    unsigned char temp = 0;
    w = 0;
    h = 0;
    //find width
    fin.seekg ( 16, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    w = temp << 24;
    fin.seekg ( 17, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    w = ( temp << 16 ) | w;
    fin.seekg ( 18, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    w = ( temp << 8 ) | w;
    fin.seekg ( 19, ios::beg );
    fin.read ( ( char* )&temp, 1 );
    w = temp | w;

    //find height
    temp = 0;
    fin.seekg ( 20, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    h = temp << 24;
    fin.seekg ( 21, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    h = ( temp << 16 ) | h;
    fin.seekg ( 22, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    h = ( temp << 8 ) | h;
    fin.seekg ( 23, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    h = temp | h;
}
/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function takes in a gif file and reads the 7, 8 bytes to find the 
 * image width and reads in the 9, 10 bytes to find the image hight.
 * 
 * @param[in, out] fin - a file that will be read to determin its width/height
 * @param[in, out]   w - the width of the image 
 * @param[in, out]   h - the height of the image
 * 
 *****************************************************************************/
void gifSize ( ifstream &fin, unsigned int &w, unsigned int &h )
{
    unsigned char temp = 0;
    w = 0;
    h = 0;
    //find width
    fin.seekg ( 7, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    w = temp << 8;
    fin.seekg ( 6, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    w = temp | w;
    //find height
    temp = 0;
    fin.seekg ( 9, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    h = temp << 8;
    fin.seekg ( 8, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    h = temp | h;
}
/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function takes in a bmp file and reads the 19, 20, 21, 22 bytes to 
 * find the image width and reads in the 23, 24, 25, 26 bytes to find the 
 * image hight.
 * 
 * @param[in,out] fin - a file that will be read to determin its width/height
 * @param[in,out]   w - the width of the image 
 * @param[in,out]   h - the height of the image
 * 
 *****************************************************************************/
void bmpSize ( ifstream &fin, unsigned int &w, unsigned int &h )
{
    unsigned char temp = 0;
    w = 0;
    h = 0;
    //find width
    fin.seekg ( 21, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    w = temp << 24;
    fin.seekg ( 20, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    w = ( temp << 16 ) | w;
    fin.seekg ( 19, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    w = ( temp << 8 ) | w;
    fin.seekg ( 18, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    w = temp | w;

    //find height
    temp = 0;
    fin.seekg ( 25, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    h = temp << 24;
    fin.seekg ( 24, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    h = ( temp << 16 ) | h;
    fin.seekg ( 23, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    h = ( temp << 8 ) | h;
    fin.seekg ( 22, ios::beg );
    fin.read ( ( char* ) &temp, 1 );
    h = temp | h;
}