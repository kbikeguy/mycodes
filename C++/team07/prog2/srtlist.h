/*************************************************************************//**
 * @file
 * @brief Header file to be used with strlist.cpp from each group member.
 ****************************************************************************/

#ifndef __SRTLIST__H__
#define __SRTLIST__H__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*!
* @brief A class designed to hold and manipulate the data of an SRT file
*/
class srtList
{
    public:
        srtList();
        ~srtList();
        
        bool insert ( string startingTime, string endingTime,
                      string theCaption );
        bool remove ( int frame );
        bool retrieve ( int frame, string &startingTime, string &endingTime,
                        string &theCaption );
        bool update ( int frame, string theCaption );
        void printSrt ( ostream &out );
        int  size ( );
        
    private:
        /*!
        * @brief Structure to hold the data for each node
        */
        struct node
        {
            string startingTime;    /*!< The starting time of a caption*/
            string endingTime;      /*!< The ending time of a caption*/
            string theCaption;      /*!< The caption contents*/
            node *next;             /*!< Pointer to the next node in the list*/
        };
        
        node *headptr;              /*!< The head pointer for the linked list*/
};

#endif