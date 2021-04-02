package campbell_riley

import campbell_riley.MainStarterStudent.choice

import scala.io.StdIn
import scala.xml.XML

/**
 * author: Riley Campbell
 * name Menu
 * this is the class for Menu. it directs the input from the MainStarterStudent menue selection to the corresponding
 * actions. the private member variables are insurance
 */
class Menu() {
  private var insurance: Insurance = new Insurance()

  /**
   * @author Riley Campbell
   * @name loadXML
   *  this is method loads an XML file and checks to ensure it is an insurance file. if is not, "invalid xml file.
   *  needs to be an insurance xml file" is displayed. if is is the correct file, the contences are read in to the
   *  tree of classes
   *  @param name the name of the requested XML file
   */
  def loadXml(name: String): Unit = {
    val topNode = XML.loadFile(name) //XML.loadFile will read in the DOM tree
    if (topNode.label != "insurance") { //.label is the "tag"
      println("invalid xml file. needs to be an insurance xml file")
      return
    }
    //GRADING: READ
    insurance.readXML(topNode)
  }

  /**
   * @author Riley Campbell
   * @name switch
   *      this is a switch method that directs the needed program functionality based on the given input
   * @param choice the menu selection
   */
  def switch(choice: Int): Unit = {
    if(choice == 1) //read XML
    {
        print("file name: ")
        val name = StdIn.readLine()
        loadXml(name)
    }
    else if(choice == 2) //write XML
    {
        print("file name:")
        val name = StdIn.readLine()
        val update = insurance.writeXML()
        XML.save(name, update, "UTF-8", true, null)
    }
    else if(choice == 3) //display data
    {
        if(insurance != null)
          println("\n" + insurance.display(0))
    }
    else if(choice == 4) //add data
    {
        print("what zip code: ")
        val zip = StdIn.readLine()
        insurance.addData(zip)
    }
    else if(choice == 5) //remove data
    {
      insurance.deleteData()
    }
    else if(choice == 6) //find service
    {
      insurance.findService()
    }
    else if(choice == 7) //Total value insured
    {
      val formatter = java.text.NumberFormat.getCurrencyInstance
      val total = insurance.totalInsurence()
      print("value: " + formatter.format(total))
    }
    else if(choice == 8) //find owner payment
    {
      insurance.calcInsurance()
    }
  }
}
