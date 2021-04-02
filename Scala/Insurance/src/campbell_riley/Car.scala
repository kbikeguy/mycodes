package campbell_riley
import scala.collection.mutable
import scala.io.StdIn
import scala.xml.{Elem, Node, Text}

/**
 * author: Riley Campbell
 * name Car
 * this is the class for Car. it extends the RDP for reading/writing XML methods as well as displaying the contents
 * and adding/removing data. the private member variables for this class are make, model, year, and value.
 */
class Car() extends RDP{
  private var make: String = _
  private var model: String = _
  private var year: String = _
  private var value: String = _

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
    print("make: ")
    make = StdIn.readLine().toLowerCase.split(' ').map(_.capitalize).mkString(" ")

    print("model: ")
    model = StdIn.readLine().toLowerCase.split(' ').map(_.capitalize).mkString(" ")

    print("year: ")
    year = StdIn.readLine()

    print("value: ")
    value = StdIn.readLine()
  }

  /**
   * @author Riley Campbell
   * @name deleteData
   * this method allows a user to delete data from this class
   * Note: currently this is a stub method for the class to extend RDP correctly
   */
  def deleteData() :Unit={}

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
    var info = "---" * level
    info += "Make: " + make + " " * (15 - make.length)
    info += "Model: " + model + " " * (15 - model.length)
    info += "Year: " + year + " " * (15 - year.length)
    info += "Value: $" + value + " " * (15 - value.length)

    info
  }

  /**
   * @author Riley Campbell
   * @name getValue
   *      this method returns the value of the Car class
   * @return the value
   */
  def getValue(): Double = {
    value.toDouble
  }

  /**
   * @author Riley Campbell
   * @name readXML
   *  this is method reads an XML file and fills all of the contents of this class
   */
  def readXML(node: Node): Unit={
    make = node.attribute("make").getOrElse("").toString
    model = node.attribute("model").getOrElse("").toString
    year = node.attribute("year").getOrElse("").toString
    value = node.attribute("value").getOrElse("").toString
  }

  /**
   * @author Riley Campbell
   * @name writeXML
   *  this is method writes to an XML file all of the contents of this class
   * @return an Elem of the class XML file
   */
  def writeXML(): Elem = {
    val attr: mutable.HashMap[String, String] = mutable.HashMap(("make", make), ("model", model), ("year", year), ("value", value))
    XMLHelper.makeNode("car", attr)
  }


}
