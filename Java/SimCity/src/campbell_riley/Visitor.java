package campbell_riley;

/**
 * @name Visitor
 * @author Riley Campbell
 * this is the visitor interface for counting symbols, changing a color, and fixing to roads
 */
public interface Visitor {

    /**
     * @name acceptBuilding
     * @author Riley Campbell
     * this is the visitor method for visiting Building tiles
     * @param building - the class to be visited
     */
    void acceptBuilding(Building building);

    /**
     * @name acceptEmpty
     * @author Riley Campbell
     * this is the visitor method for visiting Empty tiles
     * @param empty - the class to be visited
     */
    void acceptEmpty(Empty empty);

    /**
     * @name acceptGreenspace
     * @author Riley Campbell
     * this is the visitor method for visiting Greenspace tiles
     * @param greenspace - the class to be visited
     */
    void acceptGreenspace(Greenspace greenspace);

    /**
     * @name acceptRoad
     * @author Riley Campbell
     * this is the visitor method for visiting Road tiles
     * @param road - the class to be visited
     */
    void acceptRoad(Road road);
}
