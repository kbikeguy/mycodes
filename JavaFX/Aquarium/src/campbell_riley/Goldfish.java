package campbell_riley;

import static java.lang.Math.*;

/**
 * @author Riley Campbell
 * Description: This class build a goldfish and contains its health and hunger
 */
public class Goldfish extends Fish {
    private int health = 6;
    private int hunger = 0;

    /**
     * @author Riley Campbell
     * @name toString
     * this method is builds and returns a string with the information of fish type, health, and hunger
     * @return the string
     */
    @Override
    public String toString() {
        return "Goldfish\nHealth: " + health + "\nHunger: " + hunger + "%";
    }

    /**
     * @author Riley Campbell
     * @name newDay
     * this method moves time forward by one day and adds 40 hunger to the fish(capped at 100) and takes away 1 health
     * from the fish. if its hunger is greater than 90, an additional 2 health are subtracted for a total of -3 health
     */
    @Override
    public void newDay(){
        hunger = min(100, hunger + 40);
        health = hunger > 90 ? health - 3 : health - 1;
    }

    /**
     * @author Riley Campbell
     * @name getHealth
     * this method is a getter for health
     * @return health -the current level of health
     */
    @Override
    public int getHealth(){
        return health;
    }

    /**
     * @author Riley Campbell
     * @name feedFish
     * this method feeds the fish to reduce hunger by the amount passed in, limiting the hunger to a minimum of 0
     * @param amount - the amount of food to feed
     */
    @Override
    public void feedFish(int amount){
        hunger = max(0, hunger - amount);
    }
}
