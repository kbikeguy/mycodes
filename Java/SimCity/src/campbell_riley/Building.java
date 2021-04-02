package campbell_riley;

/**
 * @name: Building
 * @author: Riley Campbell
 * this class sets up the symbols for a building and defaults the colors to black as well accepting a visitor.
 * this class extends Tile
 */
public class Building extends Tile {

    /**
     * @name accept
     * @author Riley Campbell
     * this is the accept for the visitor patturn
     * @param v - an object of type Visitor
     */
    @Override
    void accept(Visitor v)
    {
        v.acceptBuilding(this);
    }

    /**
     * @name Building
     * @author Riley Campbell
     * this is the default constructor for Building. It sets the symbol to a building and the color to BLACK using super
     */
    public Building()
    {
        super.setSymbol('⌂');
        super.setColor(ColorText.Color.BLACK);
    }
}
