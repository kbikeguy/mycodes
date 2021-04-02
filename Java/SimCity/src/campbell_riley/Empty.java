package campbell_riley;

/**
 * @name Empty
 * @author  Riley Campbell
 * this class creates an empty black tile
 */
public class Empty extends Tile {
    private int x, y;

    /**
     * name:accept
     * @author Riley Campbell
     * this is the accept for the visitor patturn
     * @param v - an object of type Visitor
     */
    @Override
    void accept(Visitor v)
    {
        v.acceptEmpty(this);
    }

    /**
     * @@name Empty
     * @author Riley Campbel
     * this is the constructor for Empty. it sets tile to ▫ and the color BLACK
     */
    public Empty()
    {
        super.setSymbol('▫');
        super.setColor(ColorText.Color.BLACK);
    }
}
