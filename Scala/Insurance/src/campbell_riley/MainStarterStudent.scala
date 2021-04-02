package campbell_riley

import java.io.FileNotFoundException

import scala.io.StdIn
import scala.xml.XML

/**
 * Program name: Java City
 * Author: Riley Campbell
 * Class: CSC 461
 * Language\Compiler: Scala/InelliJ JDK 11 Scala plugin with the Scala SDK of 2.12.#
 * Description: This program allows a user to load XML insurance data and write out the insurance data to an XML file.
 * This program also allows a user to display a string of all the stored information(except car shops), Add new
 * insurance information, delete a zip code, find the first mechanic shop handling a specific requested code, determine
 * the value of all cars within a given zip code, and determine the monthly insurance rate for a customer.
 *
 * Known Bugs: None
 */

/**
 * @author Dr. Rebenitsch and Riley Campbell
 * this object extends App and handles the menu display and choice selection. the start of the program is called in a
 * catch block that will display any error messages that are generated.
 */
object MainStarterStudent extends App {

    //TO DO Add anything else you need here

    private val menuhelper = new Menu()

    private var choice = -1

    private val menu =
        """
          |1) Load XML
          |2) Write XML
          |3) Display data
          |4) Add data
          |5) Remove zip code
          |6) Find service
          |7) Total value insured
          |8) Insurance for
          |0) Quit
          |Choice: """.stripMargin

    while (choice != 0) try {
        print(menu)
        choice = StdIn.readInt()

       //TO DO add rest of your code
        menuhelper.switch(choice)

    } catch {
        case e: FileNotFoundException =>
            print("could not open file: " + e.getMessage)
    }
}
