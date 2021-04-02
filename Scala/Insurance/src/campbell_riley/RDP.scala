package campbell_riley

/**
 * @author Riley Cambell
 * @name RDP
 *      this trait is the interface for the whole program to call readXML, writeXML, display, addData, and deleteData
 */
trait RDP {

  /**
   * @author Riley Campbell
   * @name addData
   *      this is the addData prototype for interfacing the RDP extended classes
   */
  def addData():Unit

  /**
   * @author Riley Campbell
   * @name addData
   *      this is the addData prototype with a String parameter for interfacing the RDP extended classes
   * @param data the data to be added
   */
  def addData(data: String):Unit

  /**
   * @author Riley Campbell
   * @name display
   *      this is the display prototype for interfacing the RDP extended classes
   * @param level the numerical depth of descent into the tree of classes
   * @return the string of class information
   */
  def display(level: Int): String

  /**
   * @author Riley Campbell
   * @name deleteData
   *      this is the deleteData prototype for interfacing the RDP extended classes
   */
  def deleteData():Unit

  /**
   * @author Riley Campbell
   * @name readXML
   *      this is the readXML prototype for interfacing the RDP extended classes
   * @param node the node of XML input
   */
  def readXML(node: scala.xml.Node): Unit

  /**
   * @author Riley Campbell
   * @name writeXML
   *      this is the writeXML prototype for interfacing the RDP extended classes
   * @return the Elem that will be written to a XML file
   */
  def writeXML(): scala.xml.Elem
}
