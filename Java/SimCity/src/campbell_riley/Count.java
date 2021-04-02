package campbell_riley;

/**
 * @name Count
 * @author Riley Campbell
 * this class counts the number of each different type of sybmols. it implements Visitor
 */
public class Count implements Visitor {
    private int numEmpty = 0;
    private int numGreen = 0;
    private int numRoad = 0;
    private int numBuilding = 0;

    /**
     * @name acceptBuilding
     * @author Riley Campbell
     * this method increments the number of numBuilding by one
     * @param building
     */
    @Override
    public void acceptBuilding(Building building)
    {
        numBuilding++;
    }

    /**
     * @name acceptGreenspace
     * @author Riley Campbell
     * this method increments the number of numGreen by one
     * @param greenspace
     */
    @Override
    public void acceptGreenspace(Greenspace greenspace)
    {
        numGreen++;
    }

    /**
     * @name acceptEmpty
     * @author Riley Campbell
     * this method increments the number of numEmpty by one
     * @param empty
     */
    @Override
    public void acceptEmpty(Empty empty)
    {
        numEmpty++;
    }

    /**
     * @name acceptRoad
     * @author Riley Campbell
     * this method increments the number of numRoad by one
     * @param road
     */
    @Override
    public void acceptRoad(Road road)
    {
        numRoad++;
    }

    /**
     * @name Count
     * @author Riley Campbell
     * this is the constructor for Count
     */
    public Count(){
    }

    /**
     * @name toString
     * @author Riley Campbell
     * this builds the toString for the class. it tells then number of empty, greenspace, road, and building tile are
     * in the city
     *
     * @return a string of the stats for the city
     */
    public String toString()
    {
        return "Empty: " + numEmpty +
                "\nGreenspaces: " + numGreen +
                "\nRoads: " + numRoad +
                "\nBuildings: " + numBuilding;
    }
}
