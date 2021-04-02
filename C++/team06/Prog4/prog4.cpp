/**************************************************************************//**
* @file
* @brief Puts boxes on conveyor belts and keeps track of when they fall of
*
* @mainpage Program 4 - Conveyor Belts
*
* @section course_section Course Information
*
* @author Erica Keeble
* @author Matthew White
* @author Riley Campbell
*
* @date 4/27/18
*
* @par Instructor:
*       Professor Roger Schrader
*
* @par Course:
*       CSC 215 - Section 1 - 11:00am
*
* @par Location
*       Classroom Building - Room 205E
*
* @section program_section Program Information
*
* @details 
*   This program starts through a command prompt with an input file of 
*   simulation data, and a third parameter for belt length. The file is opened,
*   the program reads in belt and box data from a file. The box data is put
*   into a box struct and the belt data is read into part of the conveyorBelt
*   class that we have written for this program. Specifically, the widths of 
*   three different conveyor belts are read in. The next step is to make 
*   several comparisons between the box's dimensions and the width of the belts.
*   If the box is proven to fit on the belt, the box is added to the back of 
*   the conveyor belt (which operates like a queue). There is a variable called
*   space which accounts for how much space all the boxes on the belt are 
*   occupying. Once the difference between space and the belt length is greater
*   than one half of  the box's dimension lying on the belt, the box is removed, 
*   i.e. it falls off. Note that boxes are removed from the front and added to 
*   the back. Whenever a box is added or falls off of the belt, a message is 
*   output to a file run.out. This program will run through multiple 
*   simulations. A simulation ends with a row in the data file of -1 -1 -1. 
*   The program clears the belts and runs another simulation until it reads in 
*   0. Then the input and output files are closed. The program returns 0.
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*
* @par Usage
* @verbatim
* c:\> prog4.exe boxes.sim beltLength
* @endverbatim
*
* @section todos_bugs_modification_section ToDo, Bugs, and Modifications
*
* @par Modification and Development Timeline:
*   <a href="https://gitlab.mcs.sdsmt.edu/csc215s18prog4/team06.gitr">
Click here for commit log.</a>
*
******************************************************************************/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "unsortedDouble.h"
#include "utilities.h"
#include "Belt.h"

using namespace std;

/**************************************************************************//**
* @author Erica Keeble
* @author Matt White
* @author Riley Campbell
*
* @par Description:
*   Reads in belt and box data from a file, detemines which belt the box goes
*   on and what orientation as to optimize space usage on the belt, and outputs
*   when a box falls off of a belt
*
* @param[in]       argc - number of command line arguments
* @param[in]       argv - array that holds strings of the command line arguments
*
* @returns 0 if ran successfully
******************************************************************************/
int main(int argc, char **argv)
{
    ifstream fin;
    ofstream fout;
    int
        beltLength,
        beltWidths[3],
        i, count = 1;
    conveyorBelt
        beltA, beltB, beltC,
        beltArr[3] = { beltA, beltB, beltC };
    box aBox;
    char beltNames[3] = { 'A', 'B', 'C' };
    bool found = false;
    int boxNum = 0;

    //check command line arguments
    if (!check_cmln(argc, argv))
        exit(1);

    //open files
    openFiles(fin, argv, fout);

    //read in belt length
    beltLength = atoi(argv[2]);

    while (fin >> beltWidths[0] >> beltWidths[1] >> beltWidths[2]
        && beltWidths[0] != 0)
    {
        fout << "Simulation " << count << ":" << endl;
        //create belts
        sortBelt(beltWidths, beltNames, 3);
        for (i = 0; i < 3; i++)
            beltArr[i].beltValues(beltNames[i], beltLength, beltWidths[i]);

        aBox.boxNumber = 0;

        //read in box and process it
        while (fin >> aBox.dim1 >> aBox.dim2 >> aBox.dim3 && aBox.dim1 != -1)
        {
            aBox.boxNumber++;
            boxProcessing(aBox, beltArr, fout);
        }
        fout << endl;
        count++;

        //clears belt space between simulations
        for (int i = 0; i < 3; i++)
        {
            beltArr[i].clearBelt();
            //beltA.clearBelt();
        }
    }

    //close files
    fin.close();
    fout.close();

    return 0;
}