package campbell_riley

import scala.collection.mutable.ListBuffer
import scala.xml.{Elem, Node}

/**
 * author: Riley Campbell
 * name CarShops
 * this is the manager class for CarShop. It helps in finding services and adding/removing data. the private member
 * variables for this class are carshops.
 */
class CarShops  {
  private var carshops = ListBuffer[CarShop]()

  /**
   * @author Riley Campbell
   * @name findServices
   *      this method recursively searches through the ListBuffer of carshops for the given the code number of
   *      the needed service. If no matching code is found, the method is recursively called again with the rest of the
   *      list. if it is found, displayService is called for the current shop and this method returns true
   * @param code the needed service code
   * @param shops the list of shops to be searched
   * @return true the service code was found
   * @return false the service code was not found
   */
  def findService(code: String, shops: ListBuffer[CarShop]): Boolean ={
    if(shops.isEmpty)
      return false
    // GRADING: FIND
    if(shops.head.findService(code)){
      print(shops.head.displayService())
      return true
    }
    // GRADING: CHAIN
    findService(code, shops.tail)
  }

  /**
   * @author Riley Campbell
   * @name findServices
   *      this method recursively searches through the ListBuffer of carshops for the given the code number of
   *      the needed service. If no matching code is found, the method is recursively called again with the rest of the
   *      list. if it is found, displayService is called for the current shop and this method returns true
   * @param code the needed service code
   * @return true the service code was found
   * @return false the service code was not found
   */
  def findService(code: String): Boolean ={
    // GRADING: FIND
    if(carshops.head.findService(code)){
      print(carshops.head.displayService())
      return true
    }
    //GRADING: CHAIN
    findService(code, carshops.tail)
  }

  /**
   * @author Riley Campbell
   * @name readXML
   *  this is method reads an XML file and fills all of the contents of this class
   */
  def managerReadXML(node: Node): Unit = {
    val carShop = new CarShop()
    carShop.readXML(node)
    carshops += carShop
  }

  /**
   * @author Riley Campbell
   * @name writeXML
   *  this is method writes to an XML file all of the contents of this class
   * @return an Elem of the class XML file
   */
  def managerWriteXML():ListBuffer[Elem] = {
    carshops.map(x => x.writeXML())
  }
}
