package campbell_riley
import scala.collection.mutable
import scala.collection.mutable.ListBuffer
import scala.xml.{Elem, Node}

/**
 * author: Riley Campbell
 * name CarShop
 * this is the class for CarShop. it extends the RDP for reading/writing XML methods as well as displaying the contents,
 * finding services and adding/removing data. the private member variables for this class are name, services,
 * and neededindex.
 */
class CarShop() extends RDP {

  private var name: String = _
  private  var services = ListBuffer[Service]()
  private var neededindex: Int = _

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
   * @param info the string of new data
   */
  def addData(info: String):Unit = ???

  /**
   * @author Riley Campbell
   * @name deleteData
   * this method allows a user to delete data from this class
   * Note: currently this is a stub method for the class to extend RDP correctly
   */
  def deleteData():Unit = ???

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
   *      this method generates a string of the name of the carshop and the needed service that is required
   * @return the string of information
   */
  def displayService(): String = {
    "\"" + name + "\" handles code: " + services(neededindex).displayService()
  }

  /**
   * @author Riley Campbell
   * @name findServices
   *      this method recursively searches through the ListBuffer of services for this CarShop given the code number of
   *      the needed service. If no matching code is found, the method is recursively called again. if it is found,
   *      neededindex is set to the current index of the ListBuffer and it returns true
   * @param code the needed service code
   * @return true the service code was found
   * @return false the service code was not found
   */
  def findService(code: String): Boolean= {
    val i: Int = 0
    // GRADING: FIND
    if(services.head.get() == code) {
      neededindex = i
      return true
    }
    // GRADING: CHAIN
    findService(code, services.tail, i + 1)
  }

  /**
   * @author Riley Campbell
   * @name findServices
   *      this method recursively searches through the ListBuffer of services for this CarShop given the code number of
   *      the needed service. If no matching code is found, the method is recursively called again. if it is found,
   *      neededindex is set to the current index of the ListBuffer and it returns true
   * @param code the needed service code
   * @param servs the ListBuffer to be searched
   * @param index the current index value
   * @return true the service code was found
   * @return false the service code was not found
   */
  def findService(code: String,servs: ListBuffer[Service], index: Int): Boolean= {
      if(servs.isEmpty)
        return false
      if(servs.head.get() == code) {
        neededindex = index
        return true
      }
      // GRADING: CHAIN
      findService(code, servs.tail, index + 1)
    }

  /**
   * @author Riley Campbell
   * @name readXML
   *  this is method reads an XML file and fills all of the contents of this class
   */
  def readXML(node: Node): Unit= {
    /* general pattern
            grab attributes
            foreach childNode
                if the tag is something we care about
                     make child class
                     child.readXML(childNode)
    */
    name = node.attribute("name").getOrElse("").toString

    val children = node.child
    for (child <- children) {
      val tag = child.label
      tag match {
        case "service" =>
          val service = new Service()
          service.readXML(child)
          services += service
        case _ => null
      }
    }
  }

  /**
   * @author Riley Campbell
   * @name writeXML
   *  this is method writes to an XML file all of the contents of this class
   * @return an Elem of the class XML file
   */
  def writeXML(): Elem = {
    val attr: mutable.HashMap[String, String] = mutable.HashMap(("name", name))
    val servicesXml = services.map(x => x.writeXML())
    val children =  servicesXml //need ALL siblings at one time
    XMLHelper.makeNode("carShop", attr, children)
  }
}
