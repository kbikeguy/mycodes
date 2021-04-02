package campbell_riley;

/**
 * @name Road
 * @author Riley Campbell
 * this class sets a tile to a road of color black if a color is provided
 */
public class Road extends Tile {

    /**
     * @name accept
     * @author Riley Campbell
     * this is the accept for the visitor patturn
     * @param v - an object of type Visitor
     */
    @Override
    void accept(Visitor v)
    {
        v.acceptRoad(this);
    }

    /**
     * @name Road
     * @author Riley Campbell
     * this is the constructor for road, it sets the tile to ━ and the color to BLACK
     */
    public Road()
    {
        super.setSymbol('━');
        super.setColor(ColorText.Color.BLACK);
    }

    /**
     * @name Road
     * @author Riley Campbell
     * this is the constructor for road, it sets the tile to char c
     * @param c - the type of road to construct
     */
    public Road(char c)
    {
        super.setSymbol(c);
    }
}
