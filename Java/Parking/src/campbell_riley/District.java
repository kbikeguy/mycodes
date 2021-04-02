package campbell_riley;

/**
 * Program name: Parking
 * Author: Riley Campbell
 * Class: CSC 4161
 * Language\Compiler: Java/InelliJ JDK 11
 * Description: This class is the manager class for ParkingLot and its child class PayParkingLot. It creates an
 * ArrayList of objects from the ParkingLot class and can be used to add more objects, get the total time all the lats
 * are closed at the same time, extract a lot, see if all the lots are over 80% full, add a car to one of the lots,
 * remove a car from the a lot, get the total money collected from all the lots, count how many cars are parked
 * on all the lots, and display the statuses of every lot. This class can me utilized from an API.
 *
 * Known Bugs: None
 */

import java.util.ArrayList;

public class District {
    private ArrayList<ParkingLot> lots = new ArrayList<>();
    private int currentTime;
    private int closedTime;
    private int totalClosedMin = 0;
    private boolean closedTimeFound = false;

    /**
     * @author Riley Campbell
     * <p>
     *     Takes in an object of ParkingLot and inserts it into the lots ArrayList then returns the index
     *     of the object.     *
     * </p>
     * @param lot - An object of type ParkingLot
     * @return lots.size()-1 - The index of the object that was inserted
     */
    public int add(ParkingLot lot)
    {
        lots.add(lot);
        return lots.size() - 1;
    }

    /**
     * @author Riley Campbell
     * This is the constructor for the District class
     */
    public District()
    {
    }

    /**
     * @author Riley Campbell
     * gives access to the private totalClosedMin variable
     * @return totalClosedMin - the cumulative number of minutes that all the lots have been closed at the same time
     */
    public int getClosedMinutes()
    {
        return totalClosedMin;
    }

    /**
     * @author Riley Campbell
     * Takes in an index of the needed ParkingLot object and returns the ParkingLot object
     * @param index - the index of a Parkinglot object
     * @return lots.get(index) - the ParkingLot object
     */
    public ParkingLot getLot(int index)
    {
        return lots.get(index);
    }

    /**
     * @author Riley Campbell
     * <p>
     *     this iterates through the objects stored in the lot ArrayList and sums up all the results of
     *     object.getProfit() and then returns the total sum.
     * </p>
     * @return total - the sum of all the profits of the lots in the lot ArrayList
     */
    public double getTotalMoneyCollected()
    {
        double total = 0;

        //iterate through the ArrayList of parking lots and sum up all the profits in each lot
        for(ParkingLot i : lots)
        {
            //disregard all the free lots
            if(i instanceof PayParkingLot)
                total += ((PayParkingLot) i).getProfit();
        }

        return total;
    }

    /**
     * @author Riley Campbell
     * <p>
     *     This method sums up the returns of the getVehiclesInLot methods in each of the objects stored in the
     *     ArrayList of ParkingLot objects
     * </p>
     * @return total - the sum of vehicles in each lot
     */
    public int getVehiclesParkedInDistrict()
    {
        int total = 0;
        for(ParkingLot i : lots)
        {
            total += i.getVehiclesInLot();
        }
        return total;
    }

    /**
     * @ Riley Campbell
     * <p>
     * This method iterates through the ArrayList of ParkingLot objects and calls object.isClosed() at each
     * iteration. If any object.isClosed() returns false, this method returns false. If none of the object.isClosed()
     * returns false, this method returns true.
     * </p>
     * @return false - at least one of the parking lots are open
     * @return true - all of the parking lots are closed
     */
    public boolean isClosed()
    {
        for (ParkingLot i : lots)
        {
            if(!i.isClosed())
                return false;
        }
        return true;
    }

    /**
     * @author Riley Campbell
     * <p>
     *    This method takes in a lotID and the a time. It calls the markVehicleEntry() method for the object
     *    stored in the opject list at the lotID index and stores that result into a variable. Then it checks
     *    to ensure the time parameter is at least equal to the current time. If this is true, it checks to
     *    see if the new vehicle entry caused the lot to close. If it did, closedTimeFound is set to true
     *    and the currentTime is stored in closedTime. This will happen if and only if the addition of the new
     *    vehicle caused the lot to close. If it was already closed, no time is recorded.
     * </p>
     * @param lotID - the index of the lot to add a vehicle to
     * @param time - the time that the vehicle tries to enter the lot
     * @return id - the vehicle id
     */
    public int markVehicleEntry(int lotID, int time)
    {
        int id = lots.get(lotID).markVehicleEntry(time);

        if(time >= currentTime)
        {
            currentTime = time;
            if (!closedTimeFound && isClosed())
            {
                closedTimeFound = true;
                closedTime = currentTime;
            }
        }
        return id;
    }

    /**
     * @author Riley Campbell
     * <p>
     *     This method takes in the index of the parking lot to remove a vehicle from, the time it tries to exit at,
     *     and the id of the vehicle that is trying to exit. If time is not at least equal to the current time, nothing
     *     happens and the method exits. With a valid time, markVehicleExit() is called for the object at the lotID
     *     index. If the vehicle leaving causes the lot to reopen, the amount of time it was closed for is added into
     *     totalClosedMin to be used later. If the lot was already open, this does not happen.
     * </p>
     * @param lotID - the index of the required object
     * @param time - the time a vehicle is trying to leave
     * @param carID - the id of the car trying to leave
     */
    public void markVehicleExit(int lotID, int time, int carID)
    {
        if(time >= currentTime)
        {
            lots.get(lotID).markVehicleExit(time, carID);
            currentTime = time;

            if (closedTimeFound && !isClosed()) {
                closedTimeFound = false;
                totalClosedMin += currentTime - closedTime;
            }
        }
    }

    /**
     * @author Riley Campbell
     * <p>
     *     This method initializes a String to "District status:\n" and then appends object.toString() and a newline
     *     for each lot in the ArrayList of ParkingLot objects. After the String is built, it is returned.
     * </p>
     * @return str - The String that was built
     */
    public String toString()
    {
        String str = "District status:\n";

        for (ParkingLot lot : lots)
        {
            str += lot.toString() + "\n";
        }

        return str;
    }
}
