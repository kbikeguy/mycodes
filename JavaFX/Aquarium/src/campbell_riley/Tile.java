package campbell_riley;

import java.beans.PropertyChangeSupport;

/**
 * @author Riley Campbell
 * this class holds the tile and handles all the observer pattern for changing fish, feeding fish, and advancing the day
 */
public class Tile {
    //GRADING: OBSERVE
    private PropertyChangeSupport subject;
    private Fish myfish;

    /**
     * @author Riley Campbell
     * @name addFish
     * this method takes in a fish, rock, or none as its parameter and sets myfish to it. then using a
     * firePropertyChange, it changes the tile to myfish
     * @param fish - the object of Fish
     */
    public void addFish(Fish fish) {
        myfish = fish;
        //GRADING: TRIGGER
        subject.firePropertyChange("", null, myfish.toString());
    }

    /**
     * @author Riley Campbell
     * @name feedFish
     * this method takes in the amount to feed a fish and calls myfish.feedFish() with the given amount. next the
     * tile view is updated with firePropertychange()
     * @param amount - the amount to feed the fish
     */
    public void feedFish(int amount) {
        myfish.feedFish(amount);
        subject.firePropertyChange("fed", null, myfish.toString());
    }

    /**
     * @author Riley Campbell
     * @name getFish
     * this method is a getter for myfish
     * @return myfish - the object of Fish for this instance
     */
    public Fish getFish() {
        return myfish;
    }

    /**
     * @author Riley Campbell
     * @name isFish
     * this method checks the instanceof myfish and will return true if myfish is a Goldfish or Angelfish
     * @return true - myfish is a goldfish or angelfish, otherwise return false
     */
    public boolean isFish() {
        return myfish instanceof Goldfish || myfish instanceof Angelfish;
    }

    /**
     * @author Riley Campbell
     * @name newDay
     * this method advances the day by one by calling myfish.newDay(). if myfish's health goes below 1, died is set
     * to true. finally the tileview is updated with firePropertyChange().
     * @return died - true if myfish died, false otherwise
     */
    public boolean newDay() {
        boolean died = false;
        myfish.newDay();
        if (myfish.getHealth() < 1) {
            myfish = new None();
            died = true;
        }
        subject.firePropertyChange("", null, myfish.toString());

        return died;
    }

    /**
     * @author Riley Campbell
     * @name Tile
     * this method is the constructor for Tile. this is were the property change support is initiated
     * @param tileView - this is the object of TileView
     */
    public Tile(TileView tileView) {
        myfish = new None();
        subject = new PropertyChangeSupport(this);
        //GRADING: SUBJECT
        subject.addPropertyChangeListener(tileView);
    }

}
