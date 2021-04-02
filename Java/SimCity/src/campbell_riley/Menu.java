package campbell_riley;

/**
 * Program name: Insurance
 * Author: Riley Campbell
 * Class: CSC 461
 * Language\Compiler: Scala/InelliJ JDK 11
 * Description: This class is the manager class for Java City. It will handle all of the methods selected from main
 * as well as setting up the original city of empty tiles.
 *
 * Known Bugs: None
 */

import java.util.Scanner;

/**
 * The type Menu.
 */
public class Menu {
    public static Scanner input;

    /**
     * Method: Main()
     * Author: Riley Campbell
     * The entry point of application.
     *
     * @param args - the commandline arguments
     * @name main
     * @author Riley Campbell this is the main method for the program. it handles the menu and calling the different methods depending on which menu selection was made. if any invalid options are requested an exception is thrown and displays "Invalid option: ". if a number not listed in the menu is requested, "Unknown menu option." will display and the city and menue till redisplay. used may continue to selection of the menu until a 0 is selected, then the program will end.
     */
    public static void main(String[] args)
    {
        input = new Scanner(System.in);
        Menu myMenu = new Menu();
        City myCity = new City();

        int choice = -1;
        do {
            System.out.println(myCity.toString() );
            try {
                    choice = myMenu.DisplayMenu();
                    switch (choice)
                    {
                        case 1:
                            myMenu.SetTile(myCity);
                            break;
                        case 2:
                            myMenu.RemoveTile(myCity);
                            break;
                        case 3:
                            myMenu.DefaultCity(myCity);
                            break;
                        case 4:
                            myMenu.CountTiles(myCity);
                            break;
                        case 5:
                            myMenu.SetColor(myCity);
                            break;
                        case 6:
                            myMenu.FixRoads(myCity);
                            break;
                        case 0:
                            break;
                        default:
                            System.out.println("Unknown menu option.");
                    }
                }catch(Exception e){System.out.println("Invalid option");}
            } while (choice != 0) ;
    }

    /**
     * Method: Count tiles()
     * Author: Riley Campbell
     * Count tiles.
     *
     * @param myCity - an object of City
     * @name CountTiles
     * @author Riley Campbell this method counts the number of different types of tiles in the city by creating a new opject of Count and calling the VisitorLoops with the opject of Count. after this finished, the Count toString is called to display the results of the current count.
     */
    public void CountTiles(City myCity)
    {
        Count c = new Count();

        //GRADING: COUNT
        myCity.VisitorLoops(c);
        System.out.println(c.toString() + "\n");
    }

    /**
     * Method: Default city()
     * Author: Riley Campbell
     * Default city.
     *
     * @param myCity - an object of type City
     * @name DefaultCity
     * @author Riley Campbell This method buildings the default map by itterating through the 5x5 map and sets each index to match the pattern listed below by calling the singleTile() method in the City class with the right object.                                      ━ ━ ━ ⚵ ⚵                                      ━ ━ ━ ⚵ ▫                                      ━ ━ ━ ⌂ ▫                                      ▫ ▫ ▫ ⌂ ▫                                      ▫ ▫ ▫ ▫ ⚵
     */
    public void DefaultCity(City myCity)
    {
        int i, j;
        for(i = 0; i < 5; i++)
            for(j = 0; j < 5; j++)
            {
                if (j < 3)
                    myCity.SingleTile(i, j, i < 3 ? new Road() : new Empty());
                else if (j == 3)
                    myCity.SingleTile(i, j, i < 2 ? new Greenspace() : i < 4 ? new Building() : new Empty());
                else
                    myCity.SingleTile(i, j, i == 0 || i == 4 ? new Greenspace() : new Empty());
            }
    }

    /**
     * Method: Display menu()
     * Author: Riley Campbell
     * Display menu int.
     *
     * @return ret - the selection
     * @name DisplayMenu
     * @author Riley Campbell This displays the menue for the program function selection
     */
    public int DisplayMenu()
    {
        System.out.print("1) Set Tile\n2) Remove tile\n3) Make default City\n4) Count Zones\n5) Set tile color\n6) " +
                "Fix roads\n0) Quit\n\nChoice: ");

        return Integer.parseInt(input.nextLine().strip());
    }

    /**
     * Method: Fix roads()
     * Author: Riley Campbell
     * Fix roads.
     *
     * @param myCity - an object of City
     * @name FixRoads
     * @author Riley Campbell this is the method for fixing the shape of the current roads to make them connect to adjacent roads if they exist. a visitor pattern is used for this as well as a nested visitor to check the adjacent roads
     */
    public void FixRoads(City myCity)
    {
        FixRoad fixroad = new FixRoad(myCity);
        myCity.VisitorLoops(fixroad);
    }

    /**
     * Method: Remove tile()
     * Author: Riley Campbell
     * Remove tile.
     *
     * @param myCity - an object of type City
     * @name RemoveTile
     * @author Riley Campbell this removes an object from an index by asking for the x and y coordinents of the tile to be cleared. this input is verified for a correct string of x and y. If the input is valid, the SingleTile method from the City class is used to set the tile to an Empty() object at the x and y coordinent. If the input was not valid, the method returns without setting a tile to Empty().
     */
    public void RemoveTile(City myCity)
    {
        System.out.print("Input location (x y): ");
        String coord = input.nextLine();

        if(!TestInput(coord))
            return;

        int x = Integer.valueOf(coord.charAt(0)) - 48;
        int y = Integer.valueOf(coord.charAt(2)) - 48;

        myCity.SingleTile(x, y, new Empty());
    }

    /**
     * Method: Set color()
     * Author: Riley Campbell
     * Set color.
     *
     * @param myCity - an object of City
     * @name SetColor
     * @author Riley Campbell this method sets the color of a symbol to a requested color. it firsts asks the user for which symbol needs to change colors, and which color to change it to. If an non integer selection is made, the method returns. if an unknown menue integer is requested for symbol, the defaulted symbol is an empty tile. if an unknown menu integer is requested, the defaulted color is BLACK. once the selections are made and validated, the method calls the VisitorLoops in the City class called with an object of ColorTiles.
     */
    public void SetColor(City myCity)
    {
        System.out.print("Input tile type 1) greenspace 2) building 3) road #) empty: ");
        String temp = input.nextLine();
        int t = Integer.valueOf(temp);
        System.out.print("Input color 1) red 2) yellow 3) blue 4) green #) black: ");
        temp = input.nextLine();
        int c = Integer.valueOf(temp);
        char symbol = t == 1 ? '⚵' : t == 2 ? '⌂' : t == 3 ? '━' : '▫';
        ColorText.Color color = c == 1 ? ColorText.Color.RED : c == 2 ? ColorText.Color.YELLOW : c == 3 ?
                                ColorText.Color.BLUE : c == 4 ? ColorText.Color.GREEN : ColorText.Color.BLACK;

        ColorTiles colorTiles = new ColorTiles(color, symbol);
        //GRADING: COLOR
        myCity.VisitorLoops(colorTiles);
    }

    /**
     * Method: Set tile()
     * Author: Riley Campbell
     * Set tile.
     *
     * @param myCity - an object of type City
     * @name SetTile
     * @author Riley Campbell this sets an object onto a tile by first asking for the type of object to be used and then the x and y coordinants of the tile. the coordinants are verified as a valid location. if the location is valid, an object is placed at the location using SingleTile() from the City class. if a valid location is not given, the method returns without placing an object. the object that is placed will either be the object requested if a valid selection was made, or will default to an Empty() lot if no valid object was selected.
     */
    public void SetTile(City myCity)
    {

        System.out.print("Input tile type 1) greenspace 2) building 3) road #) empty: ");
        int type = Integer.parseInt(input.nextLine().strip());
        System.out.print("Input location (x y): ");
        String coord = input.nextLine();

        if(!TestInput(coord))
            return;

        int x = Integer.valueOf(coord.charAt(0)) - 48;
        int y = Integer.valueOf(coord.charAt(2)) - 48;
        switch (type)
        {
            case 1:
                myCity.SingleTile(x, y, new Greenspace());
                break;
            case 2:
                myCity.SingleTile(x, y, new Building());
                break;
            case 3:
                myCity.SingleTile(x, y, new Road());
                break;
            default:
                myCity.SingleTile(x, y, new Empty());
        }
    }


    /**
     * Method: Test input()
     * Author: Riley Campbell
     * Test input boolean.
     *
     * @param s the s
     * @return the boolean
     */
    public boolean TestInput(String s)
    {
        int x, y;
        if(s.length() != 3)
        {
            System.out.println("Invalid option");
            return false;
        }
        try
        {
            x = Integer.valueOf(s.charAt(0)) - 48;
            y = Integer.valueOf(s.charAt(2)) - 48;
        }
        catch (Exception e)
        {
            System.out.println("Invalid option");
            return false;
        }
        if(x < 0 || x > 4 || y < 0 || y > 4)
        {
            System.out.println("Invalid option");
            return false;
        }

        return true;
    }
}
