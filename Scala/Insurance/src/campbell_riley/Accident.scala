package campbell_riley
import scala.io.StdIn
import scala.xml.{Elem, Node, Text}

/**
 * author: Riley Campbell
 * name Accident
 * this is the class for Accident. it extends the RDP for reading/writing XML methods as well as displaying the contents
 * and adding/removing data. the private member variables for this class are date, the date of the accident.
 */
class Accident() extends RDP{
  private var date: String = ""

  /**
   * @author Riley Campbell
   * @name addData
   * this method allows a user to add data to this class from the string parameter
   * Note: currently this is a stub method for the class to extend RDP correctly
   * @param str the string of new data
   */
  def addData(str: String): Unit = {}

  /**
   * @author Riley Campbell
   * @name addData
   * this method allows a user to add new data to this class from user inputs
   */
  def addData():Unit={
    // GRADING: ADD
    print("date: ")
    date = StdIn.readLine().toLowerCase()
  }

  /**
   * @author Riley Campbell
   * @name deleteData
   * this method allows a user to delete data from this class
   * Note: currently this is a stub method for the class to extend RDP correctly
   */
  def deleteData():Unit={}

  /**
   * @author Riley Campbell
   * @name display
   *      this method builds a string of the class information and returns it. the string is preceded by "---" times
   *      the level of depth in the class tree
   * @param level the scaler for the --- output format
   * @return info: the string of the class information
   */
  def display(level: Int): String = {
    // GRADING: PRINT
    val info = "\n" + ("---" * level) + "Accident date: " + date + " " * (15 - date.length)

    info
  }

  /**
   * @author Riley Campbell
   * @name readXML
   *  this is method reads an XML file and fills all of the contents of this class
   */
  def readXML(node: Node): Unit={
    date = node.text.toString.strip()
  }

  /**
   * @author Riley Campbell
   * @name writeXML
   *  this is method writes to an XML file all of the contents of this class
   * @return an Elem of the class XML file
   */
  def writeXML(): Elem = {
    val text = Text(date) //ending node
    val children = XMLHelper.makeNode("date", null,  text)
    XMLHelper.makeNode("accident", null, children)

  }
}
