package campbell_riley;

import java.text.DecimalFormat;
import java.util.HashMap;

/**
 * @author Rley Campbell
 *  Discription: This class extends the ParkingLot class. It is used for parking lots that have a hourly fee associated
 *  with it. It builds the individual parking lots and can be used to add new car to a parking lot, remove a car from a
 *  parking lot, check if a lot is over 80% full, see how many minutes the lot is above 80% full, and display the status
 *  of the lot, see how much money the lot had generated. This class allows for the first 15 minutes from entry of a
 *  vehicle to be free as well as the ability to pay as you go, and gives a free 15 minutes after paying to leave the
 *  lot. This class may be utilized with an API.
 */
public class PayParkingLot extends ParkingLot {
    private HashMap<Integer, Integer> pay = new HashMap<>();
    private double hourlyFee;
    private double totalProfit = 0;

    /**
     * @author Riley Campbell
     * <p>
     *     updates the current totalProfit of the parking lot and the entry time of the vehicle id
     * </p>
     * @param time - the time a vehicle pays
     * @param id - the id of the vehicle
     */
    public void collectPay(int time, int id)
    {
        if(time - pay.get(id) > 15)
        {
            totalProfit += hourlyFee * (time - pay.get(id)) / 60.0;
            pay.put(id, time);
        }
    }

    /**
     * @author Riley Campbell
     * gets the total profit that a lot has accumulated
     * @return totalProfit - the current profit made by a parking lot
     */
    public double getProfit()
    {
        return totalProfit;
    }

    /**
     * @author Riley Campbell
     * <p>
     *     Calls markVehicleEntry from the parent class with super and sets that value to a variable called id. If id
     *     doesnt equal -1, put the id into the pay HashMap with a key of id and a value of time.
     * </p>
     * @param time - the time that the vehicle tries to enter the lot
     * @return id - the result of markVehicleEntry from the parent class
     */
    public int markVehicleEntry(int time)
    {
        int id =  super.markVehicleEntry(time);

        if(id != -1)
            pay.put(carID,currentTime);

        return id;
    }

    /**
     * @author Riley Campbell
     * <p>
     *    This method takes in the time a vehicle tries to exit at, and the id of the vehicle that is trying to exit.
     *    If id is unknown, its treated as a glitch and nothing happens. If the ID is valid, collectPay is called to
     *    collect a payment. After that, if time is not less than the last recorded time, markVehicleExit is called from
     *    the parent class with super.markVehicleExit(time, id) and the vehicle is removed from the pay HashMap.
     * </p>
     * @param time - the time a vehicle tries to pay or leave
     * @param id - the id of the vehicle trying to pay or leave
     */
    public void markVehicleExit(int time, int id)
    {
        if(pay.containsKey(id))
        {
            collectPay(time, id);

            if(!(time < currentTime))
            {
                super.markVehicleExit(time, id);
                pay.remove(id);
            }
        }
    }

    /**
     * @author Riley Campbell
     * <p>
     *     the constructor for PayParkingLot if the name of the lot is not given. The main constructer is called with
     *     this("test", size, fee) to default the name of the parking lot to test.
     * </p>
     *
     * @param size - the size of the lot to be constructed
     * @param fee - the associated hourly fee of the lot
     */
    public PayParkingLot(int size, double fee)
    {
        this("test", size, fee);
    }

    /**
     * @author Riley Campbell
     * <p>
     *     The constructor for PayParkingLot if the name of the lot is not given. The main constructer is called with
     *     this(name, size, 1) to default the price of the parking lot to $1/hr.
     * </p>
     * @param name - the name of the parking lot to be constructed
     * @param size - the size of the parking lot to be constructed
     */
    public PayParkingLot(String name, int size)
    {
        this(name, size, 1);
    }

    /**
     * @author Riley Campbell
     * The main constructor of PayParkingLot if all three parameters are given.
     * @param name - the name of the parking lot to be constructed
     * @param size - the size of the parking lot to be constructed
     * @param fee - the hourly fee of the parking lot to be constructed
     */
    public PayParkingLot(String name, int size, double fee)
    {
        super(name, size);
        this.hourlyFee = fee;
    }

    /**
     * @author Riley Campbell
     * <p>
     *   this builds the status string for the PayParkingLot by extending toString in the parent class by using
     *   super.toString() + " Money collected: $" + format.format(getProfit()) where the format patern is 0.00
     * </p>
     *
     * @return str - the status of the lot
     */
    public String toString()
    {
        DecimalFormat format = new DecimalFormat("0.00");
        String str = super.toString() + " Money collected: $" + format.format(getProfit());

        return str;
    }
}