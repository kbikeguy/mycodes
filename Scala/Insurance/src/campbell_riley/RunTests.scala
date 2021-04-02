package campbell_riley

import java.io.{FileInputStream, IOException, InputStream, PrintStream, SequenceInputStream}
import java.nio.file.Paths
import java.util.Scanner

/**
  * This class will test your output against the given file list. This class will be OVERWRITTEN on our end.
  */
object RunTests {
    val CHECK_CAP = false
    val CHECK_LEFT_SPACING = true
    val CHECK_RIGHT_SPACING = false
    val CHECK_NEW_LINE = false


    //future fix
    def merge(files: List[InputStream]): SequenceInputStream = {
        if (files.length == 2) {
            val t = new SequenceInputStream(files.head, files(1))
            t
        }
        else {
            val t = new SequenceInputStream(files.head, merge(files.slice(1, files.length)))
            t
        }

    }

    @throws[IOException]
    def main(args: Array[String]): Unit = {

        val tests = Array("tier1", "tier2", "tier3", "tier4", "tier5", "tier6", "tier7", "tier8")

        /*
        //future fix when setIn drops, since this works with System.setIn(...)

        val is = tests.map( x => new FileInputStream(x + ".txt"))
        val iss = is.toList
        val inputSet = merge(iss)
         System.setIn(inputSet)
         */


        try {

            for (base <- tests) {
                val file = base + ".txt"
                val outFile = base + "-student.out"
                val answerFile = base + ".out"
                var error = false
                //redirect input and output
                val output = new PrintStream(outFile)
                Console.setOut(output) //System.setOut works only with System.out.print...
                val input = new FileInputStream(base + ".txt")
                Console.setIn(input) //StdIn and System.setIn will work with the above code that merges all files

                //run program
                MainStarterStudent.main(args) //in theory, this is your starter class

                //close files
                output.close()
                input.close()

                //check answers--------------------------------------------------------------------------------
                var answer = new Scanner(Paths.get(answerFile))
                var result = new Scanner(Paths.get(outFile))
                System.err.println("\n\n\n\n\n\n" + "-----------------------------" + base + "-----------------------------")

                //check for a mismatch pass
                while ( {
                    answer.hasNext && result.hasNext
                }) {
                    var ansLine = answer.nextLine
                    var resultLine = result.nextLine
                    ansLine = cleanInput(answer, ansLine)
                    resultLine = cleanInput(result, resultLine)
                    if (!(ansLine == resultLine))
                        error = true
                }
                if (answer.hasNext || result.hasNext)
                    error = true

                //output pass, or the file with the problem lines
                if (!error)
                    System.err.println(ColorText.colorString("Passed", ColorText.Color.BLACK))
                else { //check answers
                    answer = new Scanner(Paths.get(answerFile))
                    result = new Scanner(Paths.get(outFile))

                    //check each line
                    while ( {
                        answer.hasNext && result.hasNext
                    }) {
                        //get next valid lines
                        var ansLine = answer.nextLine
                        var resultLine = result.nextLine
                        ansLine = cleanInput(answer, ansLine)
                        resultLine = cleanInput(result, resultLine)

                        //output in black if a match, and red if not
                        if (ansLine == resultLine)
                            System.err.println(ColorText.colorString(resultLine, ColorText.Color.BLACK))
                        else
                            printError(resultLine, ansLine)
                    }

                    //output remaining answer file
                    while ( {
                        answer.hasNext
                    }) {
                        val ansLine = answer.nextLine
                        printError("", ansLine)
                    }

                    //output remaining student result file
                    while ( {
                        result.hasNext
                    }) {
                        val resultLine = result.nextLine
                        printError(resultLine, "")
                    }
                }
            }
        } catch {
            case e: Exception =>
                //Any error, use normal console input
                System.err.println("Error redirecting input. Breaking...")
                System.err.println(e)
        }

    }

    def printError(resultLine: String, ansLine: String): Unit = {
        System.err.println(">>>>>>>Error>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        System.err.print("Got.....|")
        System.err.println(resultLine + "|")
        System.err.print("Needed..|")
        System.err.println(ansLine + "|")
    }

    def cleanInput(in: Scanner, line: String): String = {
        var newLine = line
        if (!CHECK_NEW_LINE) while ( {
            newLine.trim.length == 0 && in.hasNext
        }) newLine = in.nextLine

        if (!CHECK_CAP)
            newLine = newLine.toLowerCase
        if (!CHECK_LEFT_SPACING)
            newLine = newLine.stripLeading
        if (!CHECK_RIGHT_SPACING)
            newLine = newLine.stripTrailing
        newLine
    }
}



/**
 * author: Dr. Lisa Rebenitsch
 * description: a helper class that will take a string of text and return
 * a ANSI tagged version that can handle a few colors, bolding, and underlining.
 */
object ColorText {

    object Color extends Enumeration {
        val RED, BLUE, GREEN, YELLOW, MAGENTA, CYAN, GRAY, BLACK = Value
    }

    /**
     * ColorString
     *
     * will add ANSI tags to make the text the color given
     *
     * @param text  the text to color
     * @param color the color tou use
     * @return a ANSI colored string
     */
    def colorString(text: String, color: Color.Value): String = colorString(text, color, false, false)

    /**
     * ColorString
     *
     * will add ANSI tags to make the text the color given, and bolded if desired
     *
     * @param text  the text to color
     * @param color the color tou use
     * @param bold  if true, the text will be bolded
     * @return a ANSI colored string
     */
    def colorString(text: String, color: Color.Value, bold: Boolean): String = colorString(text, color, bold, false)

    /**
     * ColorString
     *
     * will add ANSI tags to make the text the color given, and bolded/underlined if desired
     *
     * @param text       the text to color
     * @param color      the color tou use
     * @param bold       if true, the text will be bolded
     * @param underlined if true, the text will be underlined
     * @return
     */
    def colorString(text: String, color: Color.Value, bold: Boolean, underlined: Boolean): String = {
        var cString = "\u001B[" //make that "start tag"
        //append the ANSI color
        if (color eq Color.RED) cString += "31"
        else if (color eq Color.GREEN) cString += "32"
        else if (color eq Color.YELLOW) cString += "33"
        else if (color eq Color.BLUE) cString += "34"
        else if (color eq Color.MAGENTA) cString += "35"
        else if (color eq Color.CYAN) cString += "36"
        else if (color eq Color.GRAY) cString += "37"
        else if (color eq Color.BLACK) cString += "30"
        else cString += "30"
        //append if it following text should be bold or undrlined
        if (bold) cString += ";1"
        if (underlined) cString += ";4"
        //finish the format starting tag, add teh text, and then the "reset" tag.
        cString += "m" + text + "\u001B[0m"
        cString
    }
}
