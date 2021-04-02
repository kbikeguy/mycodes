package campbell_riley;

/**
 * @name FixRoad
 * @author Riley Campbell
 * this is the visitor class for fixing the patern of the roads to make adjacent roads connect
 */
public class FixRoad implements Visitor {

    City city ;
    setAdjacencies adj =  new setAdjacencies();

    /**
     * @name acceptBuilding
     * @author Riley Campbell
     * this is here to keep the compiler happy
     * @param building - the visiting class
     */
    @Override
    public void acceptBuilding(Building building)
    {
    }

    /**
     * @name acceptEmpty
     * @author Riley Campbell
     * this is here to keep the compiler happy
     * @param empty - the visiting class
     */
    @Override
    public void acceptEmpty(Empty empty)
    {
    }

    /**
     * @name acceptGreenspace
     * @author Riley Campbell
     * this is here to keep the compiler happy
     * @param greenspace - the visiting class
     */
    @Override
    public void acceptGreenspace(Greenspace greenspace)
    {
    }

    /**
     * @name acceptRoad
     * @author Riley Campbell
     * this takes in an object of type Road and then locates where the object is located in the city. then it calls an
     * additional visitor to visit the tiles to the top, left, bottom, and right if they exist. if the visited tiles
     * are roads, those corasponding bools are set to true. then the shape of the road is set in the city by using
     * adj.setAdjacencies() and city.SingleTile()
     * @param road - the visiting class
     */
    @Override
    public void acceptRoad(Road road)
    {
        city.setXY(road);
        int col = city.getY();
        int row = city.getX();
        Tile tile;
        checkAdjacent adjacent = new checkAdjacent();
        boolean left, right, top, bottom;
        left = right = top = bottom = false;

        //start the left tile check
        if(col > 0)
        {
            tile = city.getTile(row, col - 1);
            //GRADING: NESTED
            tile.accept(adjacent);
            left = adjacent.isRoad();
        }
        //start right check
        if(col < 4)
        {
            tile = city.getTile(row, col + 1);
            //GRADING: NESTED
            tile.accept(adjacent);
            right = adjacent.isRoad();
        }
        //start top check
        if(row > 0)
        {
            tile = city.getTile(row - 1, col);
            //GRADING: NESTED
            tile.accept(adjacent);
            top = adjacent.isRoad();
        }
        //start bottom check
        if(row < 4 )
        {
            tile = city.getTile(row + 1, col);
            //GRADING: NESTED
            tile.accept(adjacent);
            bottom = adjacent.isRoad();
        }

        //set the tile
        adj.setAdjacencies(left, top, bottom, right);
        city.SingleTile(row, col, new Road(adj.getAdjCode()));
    }

    /**
     * @name FixRoad
     * @author Riley Campbell
     * this is the constructor for FixRoad. it sets city to the current City object
     * @param myCity - the current object of City
     */
    public FixRoad(City myCity)
    {
        city = myCity;
    }
}

