package campbell_riley;

import static java.lang.Math.*;

/**
 * @author Riley Campbell
 * Description: This class builds the Angelfish and is a child of Fish
 */
public class Angelfish extends Fish {
    private int health = 10;
    private int hunger = 0;

    /**
     * @author Riley Campbell
     * @name feedFish
     * this method feeds this fish by reducing hunger by the amount of food in the parameter, giving a lower threshold
     * of 0 for hunger.
     * @param amount - the amount to reduce hunger
     */
    @Override
    public void feedFish(int amount) {
        hunger = max(0, hunger - amount);
    }

    /**
     * @author Riley Campbell
     * @name getHealth
     * this is a getter for the current health of a fish
     * @return health - the current health of this fish
     */
    @Override
    public int getHealth() {
        return health;
    }

    /**
     * @author Riley Campbell
     * @name newDay
     * this method updates the health and hunger for a fish when a new day is selected. hunger is increased by 20,
     * capped at 100. health is reduced by 1, unless hunger is 90 or greater, then it is reduced by 3.
     */
    @Override
    public void newDay() {
        hunger = min(100, hunger + 20);
        if (hunger > 90)
            health -= 3;
        else
            health--;
    }

    /**
     * @author Riley Campbell
     * @name toString
     * this method builds and returns the an overwritten toString for Angelfish
     * @return the string of class information
     */
    @Override
    public String toString() {
        return "Angelfish\nHealth: " + health + "\nHunger: " + hunger + "%";
    }
}


