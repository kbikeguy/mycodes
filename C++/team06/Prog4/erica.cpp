/*************************************************************************//**
 * @file
 * @brief  Erica's source file to be used with belt.h and utilities.h
 *****************************************************************************/
#include "Belt.h"
#include "unsortedDouble.h"
#include "utilities.h"

/**************************************************************************//**
* @author Erica Keeble
*
* @par Description:
*   Reads in belt widths
*
* @param[in]       fin - input file stream
* @param[in]       belt - array that file stream reads belt widths into
* @param[out]      A - belt A
* @param[out]      B - belt B
* @param[out]      C - belt C
*
* @returns true if read in correctly
* @returns false otherwise
******************************************************************************/
bool readBelts(ifstream &fin, int belt[], int A, int B, int C)
{
    if (fin >> belt[0] >> belt[1] >> belt[2])
        return true;
    else
        return false;
    
    A = belt[0];
    B = belt[1];
    C = belt[2];

    //sort(belt, belt + 3);

    return true;
}

/**************************************************************************//**
* @author Erica Keeble
*
* @par Description:
*   Reads in box dimensions
*
* @param[out]      fin - input file stream
* @param[out]      aBox - a box that we read in
* @param[in]       n - box number
*
* @returns true if read in correctly
* @returns false otherwise
******************************************************************************/
bool readBox(int n, ifstream fin, box aBox)
{
    int boxArr[4];

    //read in box dimensions, sort, then insert into list
    if (fin >> boxArr[0] >> boxArr[1] >> boxArr[2])
        return true;
    else
        return false;

    //sort(boxArr, boxArr + 2);

   
    aBox.dim1 = boxArr[0];
    aBox.dim2 = boxArr[1];
    aBox.dim3 = boxArr[2];

    return true;
}

/**************************************************************************//** 
 * @author Erica Keeble
 * 
 * @par Description: 
 * Clears the belt
 * 
 *****************************************************************************/
void conveyorBelt::clearBelt()
{
    //take the belt that exists, and delete its eliments
    theBelt.clear();

    return;
}

/**************************************************************************//** 
 * @author Erica Keeble
 * @author Matt White
 * 
 * @par Description: 
 * A detailed description of the function.  It can
 * extend to multiple lines
 * 
 * @param[in, out]      package - the box from the box struct
 * @param[in]           beltWidth - width of the belt
 * 
 * @returns true a box was added.
 * @returns false a box was not added.  
 * 
 *****************************************************************************/
bool conveyorBelt::addBox ( box package, int beltWidth )
{
    //we need to see which is the largest of the 2 dimensions that fits on the belt
      
    if (theBelt.push_back(package))
    {
        if (package.dim2 <= beltWidth)
        {
            space += package.dim1;
            cout << "using dim1: " << package.dim1 << endl;
        }
        else
        {
            space += package.dim2;
            cout << "using dim2: " << package.dim2 << endl;
        }

        return true;
    }
    return false;
}

/**************************************************************************//** 
 * @author Erica Keeble
 * @author Matt White
 * 
 * @par Description: 
 * Removes a box from theBelt
 * 
 * @param[in]      beltWidth - the width of the belt we are examining
 *
 * @returns the number box that was removed 
 * 
 *****************************************************************************/
int conveyorBelt::removeBox (int beltWidth)
{
    box package;
    int boxNum = 0;

    //look at first item
    theBelt.retrieve(package, 1);
    boxNum = package.boxNumber;

    //which dimension is sitting on the belt?
    //remove that dimension
    if (package.dim2 <= beltWidth)
    {
        space -= package.dim1;
        theBelt.pop_front(package);
    }
    else if (package.dim1 <= beltWidth)
    {
        space -= package.dim2;
        theBelt.pop_front(package);
    }

    return boxNum;
}

/**************************************************************************//** 
 * @author Erica Keeble
 * 
 * @par Description: 
 * Checks if a box needs to fall off of the conveyor belt
 * 
 * @param[in]      beltWidth - the width of the belt we are examining
 * 
 * @returns true a box needs to fall off
 * @returns false otherwise  
 * 
 *****************************************************************************/
bool conveyorBelt::didBoxFall(int beltWidth)
{
    box package;

    //look at first box in list. So the one that will be at the end of the belt
    //look at first item
    if (theBelt.size() == 0)
        return false;

    theBelt.retrieve(package, 1);

    //what dimension is on the belt? 
    //And is that dimension hanging more than half over?
    if (package.dim2 <= beltWidth && space - theLength > package.dim1 / 2.0)
        return true;

    else if (package.dim1 <= beltWidth && space - theLength > package.dim2 / 2.0)
        return true;    

    else
        return false;
}

/**************************************************************************//** 
 * @author Erica Keeble
 * 
 * @par Description: 
 * Finds the index of the belt that the box is going to be placed on.
 * 
 * @param[in]      aBox - the box we are finding a belt for
 * @param[in]      beltArr[] - the array that holds the 3 belts
 * 
 * @returns index of belt box will be placed on
 * 
 *****************************************************************************/
int whichBelt(box aBox, conveyorBelt beltArr[])
{
    bool found = false;
    int j = 0;

    while (!found && j < 2)
    {
        if (aBox.dim2 <= beltArr[j].getWidth())
            found = true;
        if (!found)
            j++;
    }
    if (!found)
    {
        j = 0;
        while (!found && j < 2)
        {
            //if dim2 is too big for all the belts, check which belt dim1 fits on
            if (aBox.dim1 <= beltArr[j].getWidth())
                found = true;
            if (!found)
                j++;
        }
    }

    return j;
}

/**************************************************************************//** 
 * @author Erica Keeble
 * 
 * @par Description: 
 * Takes a box that was read in, finds the belt to place it on and places it, 
 * checks if placing that box pushed any boxes off, and if so, removes box
 * 
 * @param[in]      aBox - the box we are finding a belt for
 * @param[in]      beltArr[] - the array that holds the 3 belts
 * @param[in]      fout - output file steam
 * 
 *****************************************************************************/
void boxProcessing(box aBox, conveyorBelt beltArr[], ofstream &fout)
{
    int found = false;
    rotateBox(aBox);
    int j = 0;
    int boxNum;

    //find belt to place the box on 
    j = whichBelt(aBox, beltArr);

    //place box on belt
    beltArr[j].addBox(aBox, beltArr[j].getWidth());
    fout << setw(10) << "Box " << aBox.boxNumber
        << " was added to conveyor " << beltArr[j].getLetter() << endl;
    //did a box fall off? and what letter belt had a box fall of?
    //remove all the necessary boxes
    bool removed = true;
    while (removed)
    {
        //if box fell, remove the box
        if (beltArr[j].didBoxFall(beltArr[j].getWidth()))
        {
            boxNum = beltArr[j].removeBox(beltArr[j].getWidth());

            //output statement
            fout << setw(10) << "Box " << boxNum <<
                " fell off conveyor " << beltArr[j].getLetter() << endl;
        }
        else
            removed = false;
    }

}


    


//check command line arguments. Add given error messages

    //open files
    //read second command line into space

  //read belt width from file, so like while(fin >> belt[0][0] >>
            //belt[1][0] >> belt[2][0])
    //if belt[0][0] == 0, return
    //if not, assign to variables A, B, and C to belt[0][1], [1][1], [2][1]

    //sort that array, low to high

    //read in first package dimensions into array of size 3
    //if not -1, do all this
      //sort from lowest to highest
      //take lowest dimension of box and compare it to the smallest belt width
      /*If lowest belt width is smaller than lowest box dimension, 
        move on and check next belt width. Keep doing that for the 3 widhts. */
      /*Once you find the correct belt width, look at the second smallest box
        dimension. If that is less than belt width we are using, add 
        the smaller dimension to usedSpace[belt]. */

    