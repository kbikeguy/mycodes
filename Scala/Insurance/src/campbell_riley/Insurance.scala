package campbell_riley

import scala.collection.mutable
import scala.collection.mutable.ListBuffer
import scala.io.StdIn
import scala.reflect.io.ZipArchive
import scala.xml.{Elem, Node}

/**
 * author: Riley Campbell
 * name: Insurance
 * this is the class for Insurance. it extends the RDP for reading/writing XML methods as well as displaying the contents,
 * finding services, totaling insurance, calculating  and adding/removing data. the private member variables for this
 * class are zips, carshops, and carshop.
 */
class Insurance extends RDP{
  private var zips = ListBuffer[Zip]()
  private val carshops = new CarShops
  private var  carshop: Boolean = false

  /**
   * @author Riley Campbell
   * @name addData
   * this method allows a user to add new data to this class from user inputs.
   * note: this method is a stub to allow the RDP interface to work properly
   */
  def addData(): Unit = ???

  /**
   * @author Riley Campbell
   * @name addData
   *       this method allows a user to add data to this class from the string parameter
   * @param zip the string of new data
   */
  def addData(zip: String): Unit = {
    var found: Boolean = false
    //GRADING: ADD
    for (x <- zips) {
      if (x.get() == zip) {
        print("what owner: ")
        val owner = StdIn.readLine().toLowerCase()
        x.addData(owner)
        found = true
      }
    }

    if (!found) {
      print("added zip code")
      val newzip = new Zip(zip)
      zips += newzip
    }
  }

  /**
   * @author Riley Campbell
   * @name calcInsurance
   *      this method ask for the zip code and searches the ListBuffer of zipcodes in parallel till it finds it.
   *      then calcInsurance is called on that index of zipcodes
   */
  def calcInsurance(): Unit = {
    print("what zip code: ")
    val code = StdIn.readLine()
    //GRADING: INSURANCE
    val parZips = zips.par
    val zip = parZips.filter(_.get() == code)
    zip.head.calcInsurance()
  }

  /**
   * @author Riley Campbell
   * @name deleteData
   * this method asked for the zipcode to be removed, then it searches the zipcodes for that code in parallel till it
   * finds the correct index, then removes that index from zipcodes and displays "removed zipcode"
   */
  def deleteData():Unit={
    print("what zip code: ")
    val code = StdIn.readLine()
    val parZips = zips.par //makes it parallel
    val delZip = parZips.filter(_.get() == code)
    if(delZip.nonEmpty) {
      zips -= delZip.head
      print("removed " + code)
    }
  }

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
    var zipInfo: String = ""
    for(zip <- zips){
      zipInfo += "Zip Code: " + zip.display(level + 1) + "\n"
    }
    zipInfo
  }

  /**
   * @author Riley Campbell
   * @name findServices
   *      this method asked for the needed service code and calls the recursive findService method in carshops.
   *      if no matching service code is found, "Service Not Found" is displayed
   */
  def findService():Unit= {
    print("code: ")
    val code = StdIn.readLine()
    // GRADING: FIND
    if(!carshops.findService(code))
      print("Service Not Found")
  }

  /**
   * @author Riley Campbell
   * @name readXML
   *  this is method reads an XML file and fills all of the contents of this class
   */
  def readXML(node: Node): Unit={
    val children = node.child //grab all zip codes

    for(child <- children) {
      val tag = child.label
      tag match {
        case "zip" =>
          val zip = new Zip(null)
          zip.readXML(child)
          zips += zip
        case "carShop" =>
          carshop = true
          carshops.managerReadXML(child)
        case _ => null
      }
    }
  }

  /**
   * @author Riley Campbell
   * @name totalInsurence
   *      this method asks for the zipcode to total the insured values from and then searches zipcodes in parallel till
   *      a matching zipcode is found then called totalInsurence on that index. the value from that call will be
   *      returned. if no matching zipcode is found, 0.0 will be returned
   * @return the total value insured in the requested zip code
   */
  def totalInsurence():Double= {
    var total: Double = 0

    print("what zip code: ")
    val code = StdIn.readLine()
    // GRADING: TOTAL
    val parZips = zips.par
    val zip = parZips.filter(_.get() == code)
    if(zip.nonEmpty)
      total = zip.head.totalInsurance()

    total
  }

  /**
   * @author Riley Campbell
   * @name writeXML
   *  this is method writes to an XML file all of the contents of this class
   * @return an Elem of the class XML file
   */
  def writeXML(): Elem = {
    // GRADING: WRITE
    //make car/accident nodes
    val zipsXml = zips.map(x => x.writeXML())
    if(carshop) {
      val carshopXml = carshops.managerWriteXML()
      val children = zipsXml ++ carshopXml
      return XMLHelper.makeNode("insurance", null, children)
    }
    //else just car node
    XMLHelper.makeNode("insurance", null, zipsXml)
  }
}
