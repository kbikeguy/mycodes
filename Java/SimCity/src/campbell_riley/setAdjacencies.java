package campbell_riley;

/**
 * @name setAdjacencies
 * @author Dr. Lisa Rebenitsch and Riley Campbell
 * this is the class to set the type of road needed depending on the locations of roads around it
 */
public class setAdjacencies {

    private char adjCode = '━';

    /**
     * @name getAdjCode
     * @author Riley Campbell
     * this is a getter for adjCode
     * @return adjCode - the type of road needed
     */
    public char getAdjCode() {
        return adjCode;
    }

    /**
     * @name setAdjacencies
     * @author Dr. Lisa Rebenitsch and Riley Campbell
     * Indicate the road tiles adjacent to this one
     *
     * The road time image chosen is dependent on the tiles around
     * it. This is where the adjacency of road tiles is indicated.
     *
     * @param left True if road tile to left
     * @param top True if road tile to top
     * @param bot True if road tile to bottom
     * @param right True if road tile to right
     */
    void setAdjacencies(boolean left, boolean top, boolean bot, boolean right)
    {
        // Create the adjacency code
        int code = (left ? 1 : 0) | (top ? 2 : 0) | (bot ? 4 : 0) | (right ? 8 : 0);
        if (0 == code)
        {
            // We are already set. Do nothing
            return;
        }

        //unicode starts at 2510
        char symbols[] = {
                '━',      // 0 right
                '━',      // 1 right
                '┃',      // 2 ud
                '┛',      // 3 lu
                '┃',      // 4 ud
                '┓',      // 5 ld
                '┃',      // 6 ud
                '┫',     // 7 lud
                '━',      // 8 right
                '━',      // 9 right
                '┗',      // 10 top
                '┻',     // 11 lur
                '┏',      // 12 dr
                '┳',    // 13 ldr
                '┣',     // 14 udr
                '╋'    // 15 ludr
        };

        // Select the appropriate unicode
        adjCode = symbols[code];
    }

}
