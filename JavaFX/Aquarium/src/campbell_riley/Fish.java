package campbell_riley;

/**
 * @author Riley Campbell
 * Description: This class is the abstract class for Fish, its children are Goldfish, Angelfish, Rock, and None
 */
abstract class Fish {

    abstract void feedFish(int amount);

    abstract void newDay();

    abstract int getHealth();
}
