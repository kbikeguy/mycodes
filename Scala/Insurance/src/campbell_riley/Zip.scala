package campbell_riley
import scala.collection.mutable
import scala.collection.mutable.ListBuffer
import scala.io.StdIn
import scala.xml.{Elem, Node}

/**
 * author: Riley Campbell
 * name: Zip
 * this is the class for Zip. it extends the RDP for reading/writing XML methods as well as displaying the contents,
 * finding services, totaling insurance, calculating payments and adding/removing data. the private member variables
 * for this class are owners, and code.
 */
class Zip(num: String) extends RDP {
  private var owners = ListBuffer[Owner]()
  private var code: String = num

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
   * @param name the string of new data
   */
  def addData(name: String): Unit = {
    var found: Boolean = false
    // GRADING: ADD
    for (owner <- owners) {
      if (owner.get().toLowerCase == name) {
        owner.addData()
        found = true
      }
    }

    if(!found){
      print("Added owner")
      val newowner = new Owner(name.toLowerCase.split(' ').map(_.capitalize).mkString(" "))
      owners += newowner
    }
  }

  /**
   * @author Riley Campbell
   * @name calcInsurance
   *      this method ask for the owner name and searches the ListBuffer of owners in parallel till it finds it.
   *      then calcInsurance is called on that index of owners
   */
  def calcInsurance(): Unit={
    print("What owner: ")
    val name = StdIn.readLine().toLowerCase()
    val parOwners = owners.par
    val owner = parOwners.filter(_.get().toLowerCase == name)
    owner.head.calcInsurance()
  }

  /**
   * @author Riley Campbell
   * @name deleteData
   * this method asked allows for the removal of data in this class.
   * Note: this method is a stub to allow the RDP interface to work properly
   */
  def deleteData(): Unit = ???

  /**
   * @author Riley Campbell
   * @name display
   *      this method builds a string of the class information and returns it. the string is preceded by "---" times
   *      the level of depth in the class tree
   * @param level the scaler for the --- output format
   * @return info: the string of the class information
   */
  def display(level: Int): String = {
    //GRADING: DISPLAY
    var ownerInfo: String = code
    for (owner <- owners) {
      ownerInfo += "\n" + "---" * level + "Name: " + owner.display(level + 1)
    }

    ownerInfo
  }

  /**
   * @author Riley Campbell
   * @name get
   *      this returns the value of code
   * @return code: the numerical code of Zip
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
    val num = node.attribute("code")
    code = num.getOrElse("").toString
    val children = node.child //grab all owner nodes

    for(child <- children){
      val tag = child.label
      tag match{
        case "owner" =>
          val owner = new Owner(null)
          owner.readXML(child)
          owners += owner
        case _ => null
      }
    }
  }

  /**
   * @author Riley Campbell
   * @name totalInsurence
   *      this method sums the  values of each owner. if no owners are found,
   *      0.0 will be returned.
   * @return the total value insured of every owner in this class
   */
  def totalInsurance(): Double ={
    var total: Double = 0
    for(owner <- owners){
      total += owner.totalInsurance()
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
    val attr: mutable.HashMap[String, String] = mutable.HashMap(("code", code))

    //make car/accident nodes
    val ownersXml = owners.map(x => x.writeXML())
    val children = ownersXml //need ALL siblings at one time

    XMLHelper.makeNode("zip", attr, children)
  }
}

