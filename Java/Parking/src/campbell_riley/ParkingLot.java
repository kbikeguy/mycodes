package campbell_riley;

/**
 * @Author: Riley Campbell
 * Description: This class builds the individual parking lots and can be used to add new car to a parking lot, remove
 * a car from a parking lot, check if a lot is over 80% full, see how many minutes the lot is above 80% full, and
 * display the status of the lot. this class may be utilized with an API.
 */

import java.text.DecimalFormat;

public class ParkingLot
{
    /**
     * CLOSED_THRESHOLD is the reset constant for the percent of the parking lot to be full to be considered closed
     */
    public static final int CLOSED_THRESHOLD = 80;
    private String lotName;
    private int lotSize;
    protected int carsInLot = 0;
    protected int carID = 0;
    protected int currentTime = 0;
    protected int closedTime = 0;
    protected int totalClosedTime = 0;
    protected boolean closedTimeFound = false;

    /**
     * @author Riley Campbell
     * This method is used to provid access to totalClosedTime outside the class
     * @return totalClosedTime - the total amount of minutes the parking lot has currently been closed
     */
    public int getClosedMinutes()
    {
        return totalClosedTime;
    }

    /**
     * @author Riley Campbell
     * This method is used to provid access to lotName outside the class
     * @return lotName - the name of the lot
     */
    public String getName()
    {
        return lotName;
    }

    /**
     * @author Riley Campbell
     * This method is used to provid access to carsInLot outside the class
     * @return carsInLot - the total amount of vehicles in the lot
     */
    public int getVehiclesInLot()
    {
        return carsInLot;
    }

    /**
     * @author Riley Campbell
     * This method checks to see if the number of vehicles in the parking lot is at least 80% of the lot's capacity.
     * If its currently less than 80%, the methon returns false, otherwise it returns true.
     * @return true - the parking lot is at least 80% full
     * @return false - the parking lot is less than 80% full
     */
    public boolean isClosed()
    {
        return !(((double) carsInLot / lotSize) * 100 < CLOSED_THRESHOLD);
    }

    /**
     * @author Riley Campbell
     * <p>
     *    This method takes in a time. Then it checks to ensure the time parameter is at least equal to the current
     *    time. If this is true, it adds a vehicle to the lot by incrimenting carsInLot and carID, and sets
     *    currentTime to the time parameter. Then it checks to see if the new vehicle entry caused the lot to close.
     *    If it did, closedTimeFound is set to true and the currentTime is stored in closedTime. This will happen if
     *    and only if the addition of the new vehicle caused the lot to close. If it was already closed, no time
     *    is recorded.
     * </p>
     * @param time - the time that the vehicle tries to enter the lot
     * @return id - the vehicle id
     * @return -1 - a vehicle failed to enter the lot
     */
    public int markVehicleEntry(int time)
    {
        if(time >= currentTime && carsInLot < lotSize)
        {
            carsInLot++;
            carID++;
            currentTime = time;

            if(!closedTimeFound && isClosed())
            {
                closedTimeFound = true;
                closedTime = currentTime;
            }
            return carID;
        }

        return -1;
    }

    /**
     * @author Riley Campbell
     * <p>
     *    This method takes in the time a vehicle tries to exit at, and the id of the vehicle that is trying to exit.
     *    If time is not at least equal to the current time, nothing happens and the method exits.
     *    With a valid time, currentTime is set to time and carsInLot is decrimented by 1. If the vehicle leaving
     *    causes the lot to reopen, the amount of time it was closed for is added into totalClosedTime to be used
     *    later. If the lot was already open, this does not happen.
     * </p>
     * @param time - the time a vehicle
     * @param id - the id of the vehicle trying to leave
     */
    public void markVehicleExit(int time, int id)
    {
        if(time >= currentTime)
        {
            currentTime = time;
            carsInLot--;

            if(closedTimeFound && !isClosed())
            {
                closedTimeFound = false;
                totalClosedTime += currentTime - closedTime;
            }
        }
    }

    /**
     * @author Riley Campbell
     * <p>
     * this is the constructor for the ParkingLot class. It takes in name and size then it sets lotName to name and
     * lotSize to size.
     * </p>
     * @param name - the name of the parking lot to be constructed
     * @param size - the size of the parking lot to be constructed
     */
    public ParkingLot(String name, int size)
    {
        this.lotName = name;
        this.lotSize = size;
    }

    /**
     * @author Riley Campbell
     * <p>
     * This is the constructor for the ParkingLot if only the size parameter is given. It calls the default constructor
     * and passes in "test" as the name using this("test", size);
     * </p>
     * @param size - the size of the parking lot to be constructed
     */
    public ParkingLot(int size)
    {
        this("test", size);
    }

    /**
     * @author Riley Campbell
     * <p>
     *     This method prints out the status of the the parking lot in the form of "Status for [name]
     *     parking lot: [x] vehicles ([p])" where [name] is filled in by the name, [x] by the number of
     *     vehicles currently in the lot, and [p] by the percentage of the lot that is occupied. The
     *     percentage may have up to 1 decimal place shown, only if needed. If the percentage is at or
     *     above the threshold, display "CLOSED" for the percentage instead.
     * </p>
     * @return
     */
    public String toString()
    {
        String str = "CLOSED";
        if(!isClosed())
        {
            double percent = ((double)carsInLot / lotSize) * 100;
            DecimalFormat format = new DecimalFormat("##.#");
            str = format.format(percent) + "%";
        }

        return "Status for " + lotName + " parking lot: " + carsInLot + " vehicles (" + str + ")";
    }
}
