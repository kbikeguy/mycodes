package campbell_riley;

/**
 * @name ColorTiles
 * @author Riley Campbell
 * this class holds all the accept methods to change the color of a tile given the type of tile that needs to be colored
 */
public class ColorTiles implements Visitor {
    private ColorText.Color color;
    private char symbol;


    /**
     * @name acceptBuilding
     * @author Riley Campbell
     * this accepts an object of type acceptBuilding and sets it to the color to the correct color
     * if has the correct sybmol
     * @param building - the object
     */
    @Override
    public void acceptBuilding(Building building)
    {
        if(symbol == building.getSymbol())
            building.setColor(color);
    }

    /**
     * @name acceptEmpty
     * @author Riley Campbell
     * this accepts an object of type acceptEmpty and sets it to the color to the correct color
     * if has the correct sybmol
     * @param empty - the object
     */
    @Override
    public void acceptEmpty(Empty empty)
    {
        if(symbol == empty.getSymbol())
            empty.setColor(color);
    }

    /**
     * @name acceptGreenspace
     * @author Riley Campbell
     * this accepts an object of type Greenspace and sets it to the color to the correct color
     * if has the correct sybmol
     * @param greenspace - the object
     */
    @Override
    public void acceptGreenspace(Greenspace greenspace)
    {
        if(symbol == greenspace.getSymbol())
            greenspace.setColor(color);
    }

    /**
     * @name acceptRoad
     * @author Riley Campbell
     * this accepts an object of type acceptRoad and sets it to the color to the correct color
     * if the sybmol is greater than ascii index 9472 and less than ascii value 9549
     * @param road - the object
     */
    @Override
    public void acceptRoad(Road road)
    {
        if((int)symbol > 9472 && (int)symbol < 9549)
            road.setColor(color);
    }

    /**
     * @name ColorTiles
     * @author Riley Campbell
     * this is the constructor for ColorTiles. it takes in the color and symbol to be colored
     * @param c - the color
     * @param s - the symbol
     */
    public ColorTiles(ColorText.Color c, char s)
    {
        color = c;
        symbol = s;
    }
}
