package campbell_riley;

/**
 * @name checkAdjacent
 * @author Riley Campbell
 * this is a secondary visitor class to assist FixRoad in checking which of the adjacent tiles are roads
 */
public class checkAdjacent implements Visitor {
    private boolean isRoad;

    /**
     * @name acceptBuilding
     * @author Riley Campbell
     * this accepts an obect of type Building and sets isRoad to false
     * @param building - the class to be visited
     */
    @Override
    public void acceptBuilding(Building building) {
        isRoad = false;
    }

    /**
     * @name acceptEmpty
     * @author Riley Campbell
     * this accepts an obect of type Empty and sets isRoad to false
     * @param empty - the class to be visited
     */
    @Override
    public void acceptEmpty(Empty empty) {
        isRoad = false;
    }

    /**
     * @name acceptGreenspace
     * @author Riley Campbell
     * this accepts an obect of type Greenspace and sets isRoad to false
     * @param greenspace - the class to be visited
     */
    @Override
    public void acceptGreenspace(Greenspace greenspace) {
        isRoad = false;
    }

    /**
     * @name acceptRoad
     * @author Riley Campbell
     * this accepts an obect of type Road and sets isRoad to true
     * @param road - the class to be visited
     */
    @Override
    public void acceptRoad(Road road) {
        isRoad = true;
    }

    /**
     * @name isRoad
     * @author Riley Campbell
     * this puts the value of isRoad into ret, resets isRoad to false, and then returns the value of ret
     * @return ret - true if the last class visited was a road, false if it was not a road
     */
    public boolean isRoad() {
        boolean ret = isRoad;
        isRoad = false;
        return ret;
    }
}
