from campbell_riley.Menu import Menu

"""
 * Program name: Traffic Jam
 * Author: Riley Campbell
 * Class: CSC 461
 * Language\Compiler: Python3.7/PyCharm
 * Description: This program allows a user to build a road of any size and a and add cars to it from either end. Any 
 * invalid user inputs will be handled and the user will be given a warning. the user can chooser to update time 30 
 * seconds at a time and view the updated state of the street. the program will initiate with a default street one 
 * block long, a speed of 30 mph, and a length of 0.5 miles. the options a user will have are to show the street, 
 * build a new street, add a car, display the cars, update time, and update time and display the street and cars after
 * the update
 *
 * Known Bugs: None
 
"""


def main():
    """
    @name: main
    @author Riley Campbell and Dr. Rebenitsch
    this is the main entry point for the program. here the user makes their menu selection until a 0 is input
    @return:
    """
    selection = None
    menu = "\n" \
           "1) Show Street\n" \
           "2) Make Road\n" \
           "3) Add Car\n" \
           "4) Show Cars\n" \
           "5) Update without Debug Info\n" \
           "6) Update with Debug Info\n" \
           "0) Quit\n"

    # add remaining code for main here, you call your class's function that has your menu loop
    m = Menu()

    while selection != 0:
        print(menu)
        try:
            selection = int(input('Choice: '))
            m.selection(selection)
        except KeyboardInterrupt:
            selection = 0
        except ValueError:
            print('Invalid Option')


if __name__ == '__main__':
    main()
