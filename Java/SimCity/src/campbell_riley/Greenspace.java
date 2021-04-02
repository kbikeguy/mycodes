package campbell_riley;

/**
 * @name Greenspace
 * @author Riley Campbell
 * this class creates an greenspace tile of the color black
 */
public class Greenspace extends Tile {

    /**
     * name:accept
     * @author Riley Campbell
     * this is the accept for the visitor patturn
     * @param v - an object of type Visitor
     */
    @Override
    void accept(Visitor v)
    {
        v.acceptGreenspace(this);
    }

    /**
     * @name Greenspace
     * @author Riley Campbell
     * this is the constructor for Greenspace, it sets the tile to ⚵ and the color to BLACK
     */
    public Greenspace()
    {
        super.setSymbol('⚵');
        super.setColor(ColorText.Color.BLACK);
    }
}
