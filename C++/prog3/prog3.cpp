/*************************************************************************//**
 * @file 
 *
 * @mainpage program 3 - The Kight's Tour
 * 
 * @section course_section Course Information 
 *
 * @author Riley Campbell
 * 
 * @date 4/16/2018
 * 
 * @par Professor: 
 *         Roger Schrader
 * 
 * @par Course: 
 *         CSC 215 - Section M001 - 11:00AM
 * 
 * @par Location: 
 *         McLaury - Room 205E
 *
 * @section program_section Program Information 
 * 
 * @details This program will attempt to solve the Kights Tour problem. It 
 * will check to see if any arguments exist in the command line. These 
 * arguments will be -fancy, a text file name, or both. If a file name is given
 * the program will attempt to solve all the boardsizes and starting positions
 * that the file contains and print out the results to a new file. 
 *
 * If no file names are given, the program will open a menu for the user to 
 * choose options from. The default size and position are 8x8 and [7,7]. The
 * user may select to change the board size and starting position so long as
 * the board size and starting position is valid. After the option is chosen to 
 * solve the tour, the results will be printed to the screen
 *
 * If -fancy is passed in as a command line argument, the program will run as
 * it normally would but now a visual display board will be printed for the 
 * solved tour. If just -fancy is in the command line, the board will be 
 * printed to the screen after the menu selection process. If -fancy and
 * a file name is given, it will print the visual display boards to the 
 * along with the tour number, boardsize, and starting position.
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      none
 * 
 * @par Usage: 
   @verbatim  
   c:\> prog3.exe 
   c:\> prog3.exe -fancy
   c:\> prog3.exe file.txt
   c:\> prog3.exe -fancy file.txt
   d:\> c:\bin\prog3.exe 
   d:\> c:\bin\prog3.exe -fancy
   d:\> c:\bin\prog3.exe file.txt
   d:\> c:\bin\prog3.exe -fancy file.txt
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @par Modifications and Development Timeline: 
   <a href="https://gitlab.mcs.sdsmt.edu/7356506/csc215s18programs/commits/master">
 * Click Here </a> for a list of all contributions made to this program.
 *
 *****************************************************************************/

#include "menu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

/*! 
* @brief Global constants for moving the knight up and down
*/
int const row[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
/*! 
* @brief Global constants for moving the knight left and right
*/
int const col[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

/**************************Function Prototypes********************************/
bool checkCommands ( int argc );
bool openFiles(ifstream &fin, char **argv, ofstream &fout);
vector<string> mainMenuContents ( int n, int row, int col );
void processMainMenu ( int selection, int &boardSize, int &rpos, int &cpos, 
    string &str, int **&ptr);
void changeBoardSize ( int &boardSize, int rpos, int cpos, string &str );
void changeStartPosition ( int boardSize, int &rpos, int &cpos, string &str );
template <class TY> bool alloc2d ( TY **&ptr, int row, int col );
template <class TY> void free2d ( TY **&ptr, int row );
void fillArray(int **ptr, int boardsize);
bool solve ( int **ptr, int boardsize, int rpos, int cpos, int step );
void print ( int **ptr, int boardsize, int rpos, int cpos, int &tour,
           ostream &out, bool flag = true);
void fancyPrint ( int **ptr, int boardsize, int rpos, int cpos, int &tour,
    ostream &out, bool flag );
void bottomBar(int boardsize, ostream &out);
void topBar(int boardsize, ostream &out);
void middleBoard(int **ptr, int i, int j, ostream &out, int boardsize);
void midBar(int boardsize, int i, ostream &out);
void superfailure5000(ostream &out);
/*****************************************************************************/

/**************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This is the main function, the program starts here.
 *
 * @param[in]  argc - The number of arguments provided to the program
 * @param[in]  argv - A 2D array containing the arguments provided
 *                      to the program.
 *
 * @returns 0 The program ran with no errors.
 * @returns 1 Something went wrong in the program.
 *
 *****************************************************************************/
int main(int argc, char **argv)
{
    int bsize = 8,
        choice = 0,
        rpos = 7,
        cpos = 7,
        tour = 1,
        step = 1,
        **board = nullptr;
    bool carryOn = true,
        flag = true,
        fileIsEmpty = true;
         
    string newMenu = "";
    ifstream fin;
    ofstream fout;
  
    //check argc
    if (!checkCommands(argc))
    {
        //program usage
        cerr << "Invalid number of command line arguments." << endl;
        exit(1);
    }

    //make main menu
    vector<string> menuCont = mainMenuContents ( bsize, rpos, cpos );
    menu mainMenu ( menuCont );


    //Display menue and navigate
    if (((argc == 1) || ((argc == 2)) && (strcmp(argv[1], "-fancy") == 0)))
    {
        while(choice != 3 )
        {
           choice = mainMenu.getMenuSelection();
           processMainMenu(choice, bsize, rpos, cpos, newMenu, board);
           mainMenu.updateMenuItem(newMenu, choice);
        }
        if(!solve(board, bsize, rpos, cpos, step))
            flag = false;        
        if(argc > 1 && strcmp(argv[1], "-fancy") == 0)
            fancyPrint(board, bsize, rpos, cpos, tour, cout, flag);
        else
            print(board, bsize, rpos, cpos, tour, cout, flag);
    }

    //search through file
    else 
    {
        if (!openFiles(fin, argv, fout))
            exit (1);
        while (fin >> bsize >> rpos >> cpos)
        {
            fileIsEmpty = false;
            alloc2d(board, bsize, bsize);
            fillArray(board, bsize);
            if (!solve(board, bsize, rpos, cpos, step))
                flag = false;
            if(strcmp(argv[1], "-fancy") == 0)
                fancyPrint(board, bsize, rpos, cpos, tour, fout, flag);
            else
                print(board, bsize, rpos, cpos, tour, fout, flag);
            flag = true;
            free2d(board, bsize);
        }
        if (fileIsEmpty)
            cout << "File is empty, try another file" << endl;
        fin.close();
        fout.close();
    }

    return 0;
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
bool checkCommands ( int argc )
{
    if ( ( argc > 3 ) )
        return false;

    return true;
}

/**************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This function will give you the contents of the main menu
 *
 * @param[in]      n - the the width and height of the board
 * @param[in]      row - the starting row position
 * @param[in]      col - the starting column position
 *
 * @returns menu - the main menu contents
 *
 *****************************************************************************/
vector<string> mainMenuContents ( int n, int row, int col )
{
    vector<string> menu;
    
    menu = { "Change Board Size from " + to_string(n) + "x" + to_string(n), 
             "Charge Starting Location from [" + to_string(row) + ", "
              + to_string(col) + "]",
             "Exit and Solve Tour"
           };
           
    return menu;
}

/**************************************************************************//**
 * @author Riley Campbell
 *
 * @par Description:
 * This function lets you navigate the menue and given the selection, it will
 * call the apropriate functions.
 *
 * @param[in] selection - the menu selection
 *
 * @param[in, out] boardSize - the size of the board
 * @param[in, out] rpos - the starting row position
 * @param[in, out] cpos - the starting column position
 * @param[in, out]  str - the string for which the menue will be updated to
 * @param[in, out]  ptr - the 2d array for the tour positions
 *
 *****************************************************************************/
void processMainMenu ( int selection, int &boardSize, int &rpos, int &cpos, 
    string &str, int **&ptr)
{
    cout << endl;
    
    //process proper choice
    switch ( selection )
    {
    case 1:
        //change the board size
        changeBoardSize ( boardSize, rpos, cpos, str );
        break;

    case 2:
        //change starting position
        changeStartPosition ( boardSize, rpos, cpos,str );
        break;

    case 3:
        //build board and exit
        alloc2d(ptr, boardSize, boardSize);
        fillArray(ptr, boardSize);
        break;       

    default:
        cout << "Invalid selection" << endl;
    }
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function selects a new board size and error checks to ensure that the
 * current starting positions are still on the new board. An invalid boardsize
 * is not permitted to be chosen.
 * 
 * @param[in, out] boardSize - the size of the chessboard to be changed
 * @param[in]  rpos - the starting row position
 * @param[in]  cpos - the starting column position
 * @param[in, out] str - the new menue string that will be changed
 * 
 *****************************************************************************/
void changeBoardSize( int &boardSize, int rpos, int cpos, string &str )
{
    int temp = cpos;
    if (rpos > cpos)
        temp = rpos;

    cout << "Enter the size of the NxN Board greater than 3 and " 
         << temp << ": ";
    cin >> boardSize;
    while (boardSize < 4 || boardSize - 1 < temp )
    {
        if ( boardSize < 4 || boardSize - 1 < temp )
        {
            cout << "Invalid size" << endl
                 << "Enter the size of the NxN Board greater than 3 and " 
                 << temp << ": ";
            cin >> boardSize;
        }        
    }
    str = "Change Board Size from " + to_string(boardSize) + "x" +
        to_string(boardSize);
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function selects a new row and column starting position and error
 * checks to ensure that the new position is actually on the current board. 
 * An invalid starting position is not permitted to be chosen.
 * 
 * @param[in]      boardSize - the current boardsize
 * @param[in, out] rpos - the starting row position that will be changed
 * @param[in,out]  cpos - the starting column position that will be changed
 * @param[in,out]  str - the new menue string that will be changed
 * 
 *****************************************************************************/
void changeStartPosition( int boardSize, int &rpos, int &cpos, string &str )
{
    cout << "Enter starting row from 0 to " << boardSize - 1
         << " inclusive: ";
    cin >> rpos;
    while (rpos >= boardSize || rpos < 0)
    {
        cout << "Invalid size" << endl
             << "Enter starting row from 0 to " << boardSize - 1 
             << " inclusive: ";
        cin >> rpos;
    }

    cout << "Enter starting column from 0 to " << boardSize - 1
         << " inclusive: ";
    cin >> cpos;
    while (cpos >= boardSize || cpos < 0)
    {
        cout << "Invalid size" << endl
             << "Enter starting column from 0 to " << boardSize - 1
             << " inclusive: ";
        cin >> cpos;
    }
    str = "Change Starting Location from [" + to_string(rpos) + ", " +
        to_string(cpos) + "]";
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function will solve any valid sized chessboard with any valid starting
 * position using recursion. It will return false if the position it attempts 
 * to change to is not located on the board, or if its a position that has 
 * already been used and step back. If the position is valid, the array 
 * position will be set to the current step value. Next it will check to see if
 * the the current step is equal to boardsize squared, and if so it will return 
 * true. If its neither true or false, it will resume the recursion process. If
 * all the possible moves from the current position are invalid, it will set 
 * that position back to zero and back out till it can attempt a new route.
 * 
 * @param[in, out] ptr - the 2d array that will hold the tour steps
 * @param[in]      boardsize - the width and height of the chessboard
 * @param[in]      rpos - the row position for the step
 * @param[in]      cpos - the column position for the step
 * @param[in]      step - the current number of moves the knight has made
 *
 * @returns true a solution was found
 * @returns false a solution was not found
 * 
 *****************************************************************************/
bool solve ( int **ptr, int boardsize, int rpos, int cpos, int step)
{
    int i;    
    if (rpos >= boardsize || rpos < 0 || cpos >= boardsize || cpos < 0 || 
        ptr[rpos][cpos] != 0  )
        return false;

    ptr[rpos][cpos] = step;

    if (step == boardsize * boardsize)
        return true;
   
    for (i = 0; i < 8; i++)
    {
        if (solve(ptr, boardsize, rpos + row[i], cpos + col[i], step + 1))
            return true;
    }

    ptr[rpos][cpos] = 0;
    return false;
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function dinamically allocates a 2d array. If no memory is avalible, it
 * will return false, else it will return true.
 * 
 * @param[in, out]  ptr - the 2D array
 * @param[in]     row - the number of rows
 * @param[in]     col - the number of columns
 *
 * @returns true a 2d array was allocated
 * @returns false a 2d array was not allocated
 *
 *****************************************************************************/
template<class TY>
bool alloc2d(TY **&ptr, int row, int col)
{
    int i;

    ptr = new (nothrow) TY *[row];
    if (ptr == nullptr)
        return false;

    for (i = 0; i < row; i++)
    {
        ptr[i] = new (nothrow) TY[col];
        if (ptr[i] == nullptr)
        {
            free2d(ptr, i);
            return false;
        }
    }
    return true;
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function deletes a dynamically allocated 2D array
 * 
 * @param[in, out]  ptr - the 2D array
 * @param[in]     row - the number of rows
 * 
 *****************************************************************************/
template <class TY>
void free2d(TY **&ptr, int row)
{
    int i;

    if (ptr == nullptr)
        return;

    for (i = 0; i < row; i++)
    {
        delete[] ptr[i];
    }

    delete [] ptr;
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function prints out the tour number, the boardsize, the starting
 * position, and the solution to the knight's tour. If no solution
 * was found, "No solutions in this case" will be printed instead.
 * 
 * @param[in]      ptr - the array containing the knight's tour.
 * @param[in]     boardsize - the size of the chessboard.
 * @param[in]     rpos - the starting row position.
 * @param[in]     cpos - the starting column position.
 * @param[in, out] tour - the tour number.
 * @param[in, out] out - the output stream.
 * @param[in]      flag - a bool veriable. If true, a solution was found. If
 *                  false, no solution was found.
 * 
 *****************************************************************************/
void print(int **ptr, int boardsize, int rpos, int cpos, int &tour,
           ostream &out, bool flag)
{
    int i, j;  
    
        out << setw(0) << "Tour: # " << tour << endl
            << setw(10) << boardsize << "x" << boardsize 
            << " starting at (" << rpos << ", " << cpos << ")" << endl << endl;
        if (flag)
        {
            for (i = 0; i < boardsize; i++)
            {
                out << setw(11);
                for (j = 0; j < boardsize; j++)
                {
                    out << ptr[i][j] << setw(4);
                }
                out << endl << endl;
            }
            out << endl;
        }
        else
            out << setw(34) << "No solutions in this case" << endl << endl;
    tour++;
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function fills the array with all zeros
 * 
 * @param[in, out]  ptr - the 2D array
 * @param[in]     boardsize - the number of rows and columns of the array
 * 
 *****************************************************************************/
void fillArray(int **ptr, int boardsize)
{
    int i, j;

    for (i = 0; i < boardsize; i++)
    {
        for (j = 0; j < boardsize; j++)
            ptr[i][j] = 0;
    }
}

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
bool openFiles(ifstream &fin, char **argv, ofstream &fout)
{
    if (strcmp(argv[1], "-fancy") == 0)
    {
        fin.open(argv[2]);
        if (!fin.is_open())
        {
            cerr << "File \"" << argv[2] << "\" did not open" << endl;
            return false;
        }
    }
        
    else
    {
        fin.open(argv[1]);
        if (!fin.is_open())
        {
            cerr << "File \"" << argv[1] << "\" did not open" << endl;
            return false;
        }
    }

    fout.open("Solutions.tours", std::ofstream::out | std::ofstream::app);
    if (!fout.is_open())
    {
        cerr << "File Solutions.tours did not open" << endl;
        return false;
    }

    return true;
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function handles printing out the results either to the screen or to a 
 * file, depending on which ostream is passed in. "-fancy" must be the 2nd 
 * parameter in the command line in order for this function to be called.
 * 
 * @param[in]      ptr - the array containing the knight's tour.
 * @param[in]     boardsize - the size of the chessboard.
 * @param[in]     rpos - the starting row position.
 * @param[in]     cpos - the starting column position.
 * @param[in, out] tour - the tour number.
 * @param[in, out] out - the output stream.
 * @param[in]      flag - a bool veriable. If true, a solution was found. If
 *                        false, no solution was found.   
 * 
 *****************************************************************************/
void fancyPrint(int **ptr, int boardsize, int rpos, int cpos, int &tour,
    ostream &out, bool flag)
{    
    int i, j;

    out << setw(0) << "Tour: # " << tour << endl
        << setw(10) << boardsize << "x" << boardsize 
        << " starting at (" << rpos << ", " << cpos << ")" << endl << endl;  

    if (flag)
    {
        topBar(boardsize, out);

        for (i = 0; i < boardsize; i++)
        {
            for (j = 0; j < 3; j++)
            {
                middleBoard(ptr, i, j, out, boardsize);
            }
            midBar(boardsize, i, out);
        }
        //bottom bar
        bottomBar(boardsize, out);
    }
    else
        superfailure5000(out);
        
    tour++; 
    out << endl;
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function prints the bottom bar of the chessboard either to the screen
 * or to a file depending on which ostream is passed in as a parameter.
 * 
 * @param[in]     boardsize - the size of the chessboard.
 * @param[in, out] out - the output stream.  
 * 
 *****************************************************************************/
void bottomBar(int boardsize, ostream &out)
{
    char t = (char)202,
        br = (char)188,
        hor = (char)205,
        bl = (char)200;
    int i;

    out << setw(11) << bl;
    for (i = 0; i < boardsize * 6 + boardsize - 1; i++)
    {
        if ((i + 1) % 7 == 0 )
            out << t;
        else
            out << hor;
    }
    out << br << endl;

}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function prints the top bar of the chessboard either to the screen
 * or to a file depending on which ostream is passed in as a parameter.
 * 
 * @param[in]     boardsize - the size of the chessboard.
 * @param[in, out] out - the output stream.  
 * 
 *****************************************************************************/
void topBar(int boardsize, ostream &out)
{
    int i;
    char hor = (char)205,
        tl = (char)201,
        t = (char)203,
        tr = (char)187;
    
        /********************top bar***********************/
        out << setw(11) << tl;
        for (i = 0; i < boardsize * 6 + boardsize - 1; i++)
        {
            if ((i + 1) % 7 == 0 )
                out << t;
            else
                out << hor;
        }
        out << tr << endl;
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function prints the numbers and colors of the chessboard either to the 
 * screen or to a file depending on which ostream is passed in as a parameter.
 * 
 * @param[in, out]   ptr - the array containing the tour steps
 * @param[in]        i - the current i position
 * @param[in]        j - the current j position
 * @param[in, out] out - the output stream.  
 * @param[in]     boardsize - the size of the chessboard
 * 
 *****************************************************************************/
void middleBoard(int **ptr, int i, int j, ostream &out, int boardsize)
{
    int m,
        k;
    char black = (char)219,
         white = ' ',
         ver = (char)186;

    out << setw(11);
    for (k = 0; k < boardsize; k++)
    {                   
        out << ver;
    for (m = 0; m < 6; m++)
    {
        if (((i + k) & 1) == 1)
        {
            if (j == 1 && m == 2 && ptr[i][k] < 10)
                out << "0";
            else if (j == 1 && m == 3 && ptr[i][k] < 10)
                out << ptr[i][k];
            else if (j == 1 && m == 2 && ptr[i][k] > 9)
            {
                out << ptr[i][k];
                m++;
            }
            else
                out << black;
        }

        else
        {
            if (j == 1 && m == 2 && ptr[i][k] < 10)
                out << "0";
            else if (j == 1 && m == 3 && ptr[i][k] < 10)
                out << ptr[i][k];
            else if (j == 1 && m == 2 && ptr[i][k] > 9)
            {
                out << ptr[i][k];
                m++;
            }
            else
                out << white;
        }
    }
    if(k+1 == boardsize)
        out << ver;
    }
    out << endl;
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function prints the middle bar of the chessboard either to the screen
 * or to a file depending on which ostream is passed in as a parameter.
 * 
 * @param[in]     boardsize - the size of the chessboard.
 * @param[in]      i - the current i position.
 * @param[in, out] out - the output stream.  
 * 
 *****************************************************************************/
void midBar(int boardsize, int i, ostream &out)
{
    int w;
    char leftT = (char)204,
         hor = (char)205,
         rightT = (char)185,
         cross = (char)206;

    if (i != boardsize - 1)
    {
        out << setw(11) << leftT;
        for (w = 0; w < boardsize * 6 + boardsize - 1; w++)
        {
            if ((w + 1) % 7 == 0 )
                out << cross;
            else
                out << hor;
        }
        out << rightT << endl;
    }
}

/**************************************************************************//** 
 * @author Riley Campbell
 * 
 * @par Description: 
 * This function prints out the result if a failed tour to the screen
 * or to a file depending on which ostream is passed in as a parameter.
 * 
 * @param[in, out] out - the output stream.  
 * 
 *****************************************************************************/
void superfailure5000(ostream &out)
{
    out << setw(34) << "No solutions in this case" << endl << endl           
        << "                     qqqqqqqqqqqqqqqqqqq           " << endl
        << "                  qqq                   qqqq       " << endl
        << "                qqq                         qqqq   " << endl
        << "              qq                              qqq  " << endl
        << "           qqq                                 qqq " << endl
        << "         qq                                     qqq" << endl
        << "        qq         qqqqq           qqqqq         qq" << endl
        << "      qq          qqqqqq          qqqqqq         qq" << endl
        << "     qq           qqqq            qqqq           qq" << endl
        << "    qq               *               *           qq" << endl
        << "   qq                *               *          qq " << endl
        << "  qq                    qqqq         *          qq " << endl
        << " qq               qqqqqqqqqqqqqqq              qq  " << endl
        << " qq            qqqq           qqqqq           qq   " << endl
        << "qqq         qqq                  qq          qq    " << endl
        << "qq         q                      qq        qq     " << endl
        << "qqq      q                        qq       qq      " << endl
        << "qqq     q                         qq     qq        " << endl
        << " qqq                                   qq          " << endl
        << "  qqq                                qq            " << endl
        << "   qqq                            qq               " << endl
        << "    qqqq                      qqq                  " << endl
        << "       qqqqqqqqqqqqqqqqqqqqqqq                     " << endl
        << endl << endl;
}