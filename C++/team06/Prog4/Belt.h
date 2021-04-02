/*************************************************************************//**
 * @file
 * @brief Header file to be used with Belt.cpp from each group member.
 ****************************************************************************/

#ifndef __BELT__H
#define __BELT__H
#include <iostream>
#include <fstream>
#include "unsortedDouble.h"

using namespace std;
/*!
* @brief creates a box which contains the number of the box, and it's 3 dimensions
*/
struct box
{
    int boxNumber; /*!< Contains the number of the box  */
    int dim1; /*!< Contains one of the boxe's dimensions  */
    int dim2; /*!< Contains one of the boxe's dimensions  */
    int dim3; /*!< Contains one of the boxe's dimensions  */
};

/*!
* @brief allows for creation and manipulation of the length, width, space,
*   and letter associated with a conveyor belt.
*/
class conveyorBelt
{
    public:

        conveyorBelt();
        void beltValues(char belt, int length, int width);
        ~conveyorBelt();

        bool addBox ( box package, int beltWidth );
        int removeBox (int beltWidth);
        char getLetter();  
        int getWidth();
        void clearBelt();
        bool didBoxFall(int beltWidth);

    private:
        unsortedDouble<box> theBelt; /*!< the belt we will be manipulating  */
        int theLength; /*!< the length of the belt */
        int theWidth;  /*!< the width of the belt */
        int space;     /*!< the amount of length taken up on the belt */
        char letter;   /*!< the letter associated with the belt */
};
#endif