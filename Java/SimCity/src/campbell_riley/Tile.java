package campbell_riley;

/**
 * @name Tile
 * @author Riley Campbell
 * this class makes a tile and the display of the tile is based on what symbol and color are passed in
 */
public abstract class Tile {
    private ColorText.Color color;
    private char symbol;

    /**
     * name:accept
     * @author Riley Campbell
     * this is the accept for the visitor patturn
     * @param v - an object of type Visitor
     */
    abstract void accept(Visitor v);

    /**
     * @name getSymbol
     * @author Riley Campbell
     * this is a getter for the symbol
     * @return - the symbol
     */
    public char getSymbol() {
        return symbol;
    }

    public ColorText.Color getColor() {
        return color;
    }

    /**
     * @name setColor
     * @author Riley Campbell
     * this is the setter for color
     * @param color - the color to be set
     */
    public void setColor(ColorText.Color color) {
        this.color = color;
    }

    /**
     * @name setSymbol
     * @author Riley Campbell
     * this is a setter for symbol
     * @param symbol - the symbol to be set
     */
    public void setSymbol(char symbol) {
        this.symbol = symbol;
    }

    /**
     * @name toString
     * @author Riley Campbell
     * this is the toString method for the Tile class. it displays the color and symbol of a tile
     * @return - the string made up of the color and symbol of a tile
     */
    @Override
    public String toString() {
        return ColorText.colorString(String.valueOf(symbol),color);
    }
}
