package campbell_riley;

public class Rock extends Fish {

    /**
     * @author Riley Campbell
     * @name feedFish
     * this method just keeps the compiler happy since Fish is abstract
     * @param amount - the amount of food
     */
    @Override
    void feedFish(int amount) {}

    /**
     * @author Riley Campbell
     * @name getHealth
     * this method just keeps the compiler happy since Fish is abstract
     * @return 0
     */
    @Override
    int getHealth() {
        return 0;
    }

    /**
     * @author Riley Campbell
     * @name newDay
     * this method just keeps the compiler happy since Fish is abstract
     */
    @Override
    void newDay() {}

    /**
     * @author Riley Campbell
     * @name toString
     * this method returns a string of the class name
     * @return None - the class name
     */
    public String toString() {
        return "Rock";
    }
}
