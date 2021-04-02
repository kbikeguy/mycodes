package campbell_riley
import scala.collection.mutable
import scala.collection.mutable.ListBuffer
import scala.io.StdIn
import scala.xml.{Elem, Node}

/**
 * author: Riley Campbell
 * name: Owner
 * this is the class for Owner. it extends the RDP for reading/writing XML methods as well as displaying the contents,
 * totaling insurance, calculating payment and adding/removing data. the private member variables for this class are
 * owner, cars, and accidents.
 */
class Owner(name: String) extends RDP{
  private var owner: String = name
  private var cars = ListBuffer[Car]()
  private var accidents = ListBuffer[Accident]()

  /**
   * @author Riley Campbell
   * @name addData
   * this method allows a user to add data to this class from the string parameter
   * note: this method is a stub to allow the RDP interface to work properly
   * @param str the string of new data
   */
  def addData(str: String): Unit = ???

  /**
   * @author Riley Campbell
   * @name addData
   *      this method allows a user to add new data to this class from user inputs.
   */
  def addData():Unit = {
    // GRADING: ADD
    print("add car y/n? ")
    var add = StdIn.readLine().toLowerCase()
    if(add == "y"){
      val newcar = new Car()
      newcar.addData()
      cars += newcar
    }

    print("add accident y/n? ")
    add = StdIn.readLine().toLowerCase()
    if(add == "y"){
      val  newaccident = new Accident()
      newaccident.addData()
      accidents += newaccident
    }

  }

  /**
   * @author Riley Campbell
   * @name calcInsurance
   *      this method iterates through the ListBuffer of cars and calcInsurance is called on each index to sum the
   *      total values of each car. then the monthly insurance payment is calculated and displayed in the form of
   *      payment = carsTotal * 0.01 + carsTotal * 0.01 * accidentCount
   */
  def calcInsurance():Unit ={
    var total: Double = 0
    for (car <- cars){
      total += car.getValue()
    }
    print("Monthly payment: " + java.text.NumberFormat.getCurrencyInstance.format(total * 0.01 * (1 + accidents.size)))
  }

  /**
   * @author Riley Campbell
   * @name deleteData
   * this method asked allows for the removal of data in this class.
   * Note: this method is a stub to allow the RDP interface to work properly
   */
  def deleteData():Unit = ???

  /**
   * @author Riley Campbell
   * @name display
   *      this method builds a string of the class information and returns it. the string is preceded by "---" times
   *      the level of depth in the class tree
   * @param level the scaler for the --- output format
   * @return info: the string of the class information
   */
  def display(level: Int): String = {
    var info: String = owner + "\n"
    // GRADING: PRINT
    if(cars.nonEmpty){
      info += "---" * level + "Cars: \n"
      for(car <- cars){
        info += car.display(level + 1)
      }
    }

    if( accidents.nonEmpty){
      info += "\n" + "---" * level + "Accidents:\n"
      for(accident <- accidents){
        info += accident.display(level + 1)
      }
    }

    info
  }

  /**
   * @author Riley Campbell
   * @name get
   *      this returns the name of the owner
   * @return owner: the name of the owner
   */
  def get():String = {
    owner
  }

  /**
   * @author Riley Campbell
   * @name readXML
   *  this is method reads an XML file and fills all of the contents of this class
   */
  def readXML(node: Node): Unit= {
    //to do full streaming method, I would get the attributes and then do a for-each
    owner = node.attribute("name").getOrElse("").toString
    val children = node.child //grab all car nodes

    for (child <- children) {
      val tag = child.label
      tag match {
        case "car" =>
          val car = new Car()
          car.readXML(child)
          cars += car
        case "accident" =>
          val accident = new Accident()
          accident.readXML(child)
          accidents += accident
        case _ => null
      }
    }
  }

  /**
   * @author Riley Campbell
   * @name totalInsurence
   *      this method sums the values of each car. if no cars are found,
   *      0.0 will be returned.
   * @return the total value of every car in this class
   */
  def totalInsurance(): Double={
    var total: Double = 0
    for(car <- cars){
      total += car.getValue()
    }
    total
  }

  /**
   * @author Riley Campbell
   * @name writeXML
   *  this is method writes to an XML file all of the contents of this class
   * @return an Elem of the class XML file
   */
  def writeXML(): Elem = {
    //make owner node
    val attr: mutable.HashMap[String, String] = mutable.HashMap(("name", owner))

    //make car nodes
    val carXml = cars.map(x => x.writeXML())

    //make accident nodes
    if(accidents.nonEmpty) {
      val accidentXML = accidents.map(x => x.writeXML())
      val children = carXml ++ accidentXML //need ALL siblings at one time
      return XMLHelper.makeNode("owner", attr, children)
    }

    XMLHelper.makeNode("owner", attr, carXml)
  }
}
