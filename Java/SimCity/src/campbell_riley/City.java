package campbell_riley;

/**
 * @name City
 * @author Riley Campbell
 * this is my City class that manages the 2d array of city tiles. the methods include ways to alter a single tile,
 * loop a visitor through the city, and display the current city layout
 */
public class City {
    /**
     * the array of the city
     */
    private Tile[][] city =  new Tile[5][5];
    private int x;
    private int y;

    /**
     * @name City
     * @author Riley Campbell
     * this is the class constuctor. it initiates the 2d array of the tiles to Empty() by itterating through it
     */
    public City()
    {
        for(int i = 0; i < 5; i++)
            for(int j = 0; j < 5; j++)
                city[i][j] = new Empty();
    }

    /**
     * @name getTile
     * @author Riley Campbell
     * this is a getter for the Tile object stored in city at i and j indexes
     * @param i - the i index
     * @param j - the j index
     * @return the object stored at city[i][j]
     */
    public Tile getTile(int i, int j)
    {
        return city[i][j];
    }

    /**
     * @name getX
     * @author Riley Campbell
     * this is a getter for x
     * @return y - the index of x
     */
    public int getX() {
        return x;
    }

    /**
     * @name getY
     * @author Riley Campbell
     * this is a getter for y
     * @return y - the index of y
     */
    public int getY() {
        return y;
    }

    /**
     * @name setXY
     * @author Riley Campbell
     * this takes in a object of Tile and itterates throught the city until it finds it. then it sets x and y to the
     * corrasponding indexes it was found at.
     * @param tile - an object of Tile
     */
    public void setXY(Tile tile)
    {
        for(int i = 0; i < 5; i++)
            for(int j = 0; j < 5; j++)
                if(tile == city[i][j])
                {
                    x = i;
                    y = j;
                    return;
                }
    }

    /**
     * @name SingleTile
     * @author Riley Campbell
     * this takes in an i and j index and the type of object to be placed there and sets the value of the array to
     * the ojbect that was passed in.
     * @param i - the i index
     * @param j - the j index
     * @param symbol - the type of object to be placed on the array
     */
    public void SingleTile(int i, int j, Tile symbol)
    {
        city[i][j] = symbol;
    }

    /**
     * @name toString
     * @author Riley Campbell
     * this builds a string to display the contents of the 2D array of tiles by itterating throught it
     * @return curCity - the string containing the display of the city
     */
    @Override
    public String toString() {
        String curCity = "";

        for(Tile[] row : city)
        {
            for(Tile col : row)
                curCity += col;
            curCity += "\n";
        }

        return curCity;
    }

    /**
     * @name VisitorLoops
     * @author Riley Campbell
     * this loops a visitor through the city
     * @param v - the type of visitor
     */
    public void VisitorLoops(Visitor v)
    {
        for (Tile[] row : city)
            for (Tile col : row)
                col.accept(v);
    }

}
