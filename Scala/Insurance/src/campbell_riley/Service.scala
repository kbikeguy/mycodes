package campbell_riley
import scala.collection.mutable
import scala.xml.{Elem, Node, Text}

/**
 * author: Riley Campbell
 * name Service
 * this is the class for Service. it extends the RDP for reading/writing XML methods as well as displaying the contents,
 * finding services and adding/removing data. the private member variables for this class are code, and description.
 */
class Service() extends RDP {
  private var code: String = _
  private var description: String = _

  /**
   * @author Riley Campbell
   * @name addData
   * this method allows a user to add new data to this class from user inputs
   * Note: currently this is a stub method for the class to extend RDP correctly
   */
  def addData(): Unit = ???

  /**
   * @author Riley Campbell
   * @name addData
   *       this method allows a user to add data to this class from the string parameter
   *       Note: currently this is a stub method for the class to extend RDP correctly
   * @param str the string of new data
   */
  def addData(str: String): Unit = ???

  /**
   * @author Riley Campbell
   * @name deleteData
   * this method allows a user to delete data from this class
   * Note: currently this is a stub method for the class to extend RDP correctly
   */
  def deleteData(): Unit = ???

  /**
   * @author Riley Campbell
   * @name display
   *      this method builds a string of the class information and returns it. the string is preceded by "---" times
   *      the level of depth in the class tree
   *      NOTE: this is currently a stub method to keep make the RDP interface work properly
   * @param level the scaler for the --- output format
   * @return info: the string of the class information
   */
  def display(level: Int): String = ???

  /**
   * @author Riley Campbell
   * @name displayService
   *      this method builds a string of the class information and returns it in the form of
   *      "code + ". Description: " + description"
   * @return info: the string of the class information
   */
  def displayService(): String = {
    code + ". Description: " + description
  }

  /**
   * @author Riley Campbell
   * @name get
   *      this returns the value of code
   * @return code: the numerical code of the service
   */
  def get(): String = {
    code
  }

  /**
   * @author Riley Campbell
   * @name readXML
   *  this is method reads an XML file and fills all of the contents of this class
   */
  def readXML(node: Node): Unit = {
    code = node.attribute("code").getOrElse("").toString
    description = node.text
  }

  /**
   * @author Riley Campbell
   * @name writeXML
   *  this is method writes to an XML file all of the contents of this class
   * @return an Elem of the class XML file
   */
  def writeXML(): Elem = {
    val attr: mutable.HashMap[String, String] = mutable.HashMap(("code", code))
    val text = Text(description) //ending node
    XMLHelper.makeNode("service", attr, text)
  }
}