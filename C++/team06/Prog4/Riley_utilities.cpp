/*************************************************************************//**
 * @file
 * @brief  functions from utilities.h
 *****************************************************************************/

#include "utilities.h"
#include "Belt.h"
#include "unsortedDouble.h"


/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function opens the input and output files. If a file fails to open, an
 * error message will display which one failed to open and the funtion will
 * return false. If all files open, the function will return true.
 * 
 * @param[in, out]  fin - the input file
 * @param[in]     argv - the array from the command line
 * @param[in,out]  fout - the output file
 *
 * @return true all the files opened
 * @return false at least one file failed to open
 * 
 *****************************************************************************/
void openFiles(ifstream &fin, char **argv, ofstream &fout)
{
    //input files
    fin.open(argv[1]);
    if (!fin.is_open())
    {
        cerr << "File \"" << argv[1] << "\" did not open" << endl;
        exit(1);
    }
    
    //output files
    fout.open("run.out");
    if (!fout.is_open())
    {
        cerr << "File run.out did not open" << endl;
        exit(1);
    }
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function is for sorting the sizes of the belts in assending order
 * 
 * @param[in, out]  beltWidths - the array of belt widths
 * @param[in, out]  beltNames - the array of belt names
 * @param[in]       size - the size of the arrays 
 * 
 *****************************************************************************/
void sortBelt(int beltWidths[], char beltNames[], int size)
{
    bool swapMade = true;
        int tempWidth,
        i;
        char tempName;

        //reset names from previous run
        beltNames[0] = 'A';
        beltNames[1] = 'B';
        beltNames[2] = 'C';

    do
    {
        swapMade = false;
        for (i = 0; i < size - 1; i++)
        {
            if (beltWidths[i] > beltWidths[i + 1])
            {
                //swap belt widths
                tempWidth = beltWidths[i];
                beltWidths[i] = beltWidths[i + 1];
                beltWidths[i + 1] = tempWidth;

                //swap belt names
                tempName = beltNames[i];
                beltNames[i] = beltNames[i + 1];
                beltNames[i + 1] = tempName;
                swapMade = true;
            }
        }
    } while (swapMade);

}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function rotates the rotates a box till the dimmentions are in 
 * assending order. If the demmentions are all the same, nothing is done and 
 * the function returns.
 * 
 * @param[in, out]  package - the box from the box struct
 * 
 *****************************************************************************/
void rotateBox(box &package)
{
    //veriables
    int temp, 
        i,
        j,
        arr[3] = { package.dim1, package.dim2, package.dim3 };
    bool swap = true;

    //check for a perfect cube
    if (package.dim1 == package.dim2 && package.dim2 == package.dim3)
        return;

    //sort in assending order
    for( i = 0; i < 2 && swap; i++)	
    {	
        swap = false;			
        for( j = 0; j < 2 - i; j++)		
        {
            if(  arr[j] > arr[j+1] )
            {
                swap = true;
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;           
            }
        }
    }
    //set dimmentions 
    package.dim1 = arr[0];
    package.dim2 = arr[1];
    package.dim3 = arr[2];
}