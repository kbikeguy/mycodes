/*************************************************************************//**
 * @file
 * @brief Contains functions for the belt class
 ****************************************************************************/
#include "unsortedDouble.h"
#include "Belt.h"

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * The constructor function for conveyorBelt  
 * 
 *****************************************************************************/
conveyorBelt::conveyorBelt()
{

}

/**************************************************************************//** 
 * @author Matthew White
 * 
 * @par Description: 
 * Adds belt letter, length and width to the belt.
 * 
 * @param[in]      belt - the name of the conveyor belt
 * @param[in]      length - the length of the conveyor belt
 * @param[in]      width - the width of the conveyor belt  
 * 
 *****************************************************************************/
void conveyorBelt::beltValues(char belt, int length, int width)
{
    letter = belt;
    theLength = length;
    theWidth = width;
    space = 0; 
    
    return;
}

/**************************************************************************//** 
 * @author Matthew White
 * 
 * @par Description: 
 * Destructor
 * 
 *****************************************************************************/
conveyorBelt::~conveyorBelt()
{
    theBelt.clear();
    return;
}
/**************************************************************************//** 
 * @author Matthew White
 * 
 * @par Description: 
 * Gives access to letter, which is in the private section of the conveyor 
 * belt class
 * 
 * @returns the letter associated with the box
 * 
 *****************************************************************************/
char conveyorBelt::getLetter()
{
    return letter;
}
/**************************************************************************//** 
 * @author Matthew White
 * 
 * @par Description: 
 * Gives access to the box width, which is in the private section of the 
 * conveyor belt class.
 * 
 * @returns the width of the box
 * 
 *****************************************************************************/
int conveyorBelt::getWidth()
{
    return theWidth;
}

