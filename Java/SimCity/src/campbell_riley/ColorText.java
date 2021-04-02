package campbell_riley;

/**
 * author: Dr. Lisa Rebenitsch
 * description: a helper class that will take a string of text and return
 * a ANSI tagged version that can handle a few colors, bolding, and underlining.
 */
public class ColorText {
    public enum Color{
        RED, BLUE, GREEN, YELLOW, MAGENTA, CYAN, GRAY, BLACK
    }

    /**
     * ColorString
     *
     * will add ANSI tags to make the text the color given
     * @param text the text to color
     * @param color the color tou use
     * @return a ANSI colored string
     */
    public static String colorString(String text, Color color) {
        return colorString(text, color, false, false);
    }

    /**
     * ColorString
     *
     * will add ANSI tags to make the text the color given, and bolded if desired
     * @param text the text to color
     * @param color the color tou use
     * @param bold if true, the text will be bolded
     * @return a ANSI colored string
     */
    public static String colorString(String text, Color color,
                                     boolean bold) {
        return colorString(text, color, bold, false);
    }

    /**
     * ColorString
     *
     * will add ANSI tags to make the text the color given, and bolded/underlined if desired
     * @param text the text to color
     * @param color the color tou use
     * @param bold if true, the text will be bolded
     * @param underlined if true, the text will be underlined
     * @return
     */
    public static String colorString(String text, Color color,
                                     boolean bold, boolean underlined) {


        String cString = "\u001B["; //make that "start tag"

        //append the ANSI color
        if(color == Color.RED) {
            cString+="31";
        }
        else if(color == Color.GREEN) {
            cString+="32";
        }
        else if(color == Color.YELLOW) {
            cString+="33";
        }
        else if(color == Color.BLUE) {
            cString+="34";
        }
        else if(color == Color.MAGENTA) {
            cString+="35";
        }
        else if(color == Color.CYAN) {
            cString+="36";
        }
        else if(color == Color.GRAY) {
            cString+="37";
        }
        else if(color == Color.BLACK) {
            cString+="30";
        }
        else
        {
            cString+="30";
        }

        //append if it following text should be bold or undrlined
        if(bold) {
            cString+=";1";
        }
        if(underlined) {
            cString+=";4";
        }

        //finish the format starting tag, add teh text, and then the "reset" tag.
        cString+="m" + text + "\u001B[0m";
        return cString;
    }

}
