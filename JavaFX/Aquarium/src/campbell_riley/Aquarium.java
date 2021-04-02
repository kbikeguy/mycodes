package campbell_riley;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * @author Riley Campbell
 * Description: This class builds the aquarium and keeps track of the total fish, current day, number of dead fish,
 * as well as tracks the aquarium tiles.
 */
public class Aquarium {
    private ArrayList<Tile> tiles = new ArrayList<>();
    private int totalFish = 0;
    private int dayCount = 0;
    private int deadCount = 0;
    private int filled = 0;

    /**
     * @author Riley Campbell
     * @name Aquarium
     * this method is the constructor for Aquarium and builds the aquarium based on the number of rows, columns,
     * and the array list of tile objects
     * @param rows - the number of rows to build
     * @param cols - the number of columns to build
     * @param tileViews - the array list of tile objects
     */
    public Aquarium(int rows, int cols, ArrayList<TileView> tileViews) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                tiles.add(new Tile(tileViews.get(j + cols * i)));

            }
    }

    /**
     * @author Riley Campbell
     * @name changeFish
     * this method changes the selected tile to the requested fish by calling tiles[index].addFish(),
     * and updates the current fish count and filled count
     * @param fish - the requested fish
     * @param index - the index of the selected tile
     * @param curTile - the toString of the selected tile
     */
    public void changeFish(Fish fish, int index, String curTile) {
        if (fish instanceof Goldfish || fish instanceof Angelfish) {
            totalFish++;
            filled++;
        }
        else if (fish instanceof Rock)
            filled++;
        else if (!curTile.contains("Rock")) {
            totalFish--;
            filled--;
        }
        else
            filled--;

        tiles.get(index).addFish(fish);
        if (totalFish < 0)
            totalFish = 0;
    }

    /**
     * @author Riley Campbell
     * @name collectData
     * this method iterates through the aquarium and builds a hashmap of tile names as keys and their unique totals
     * as the values
     * @return list - the hashmap of fish and their counts
     */
    public HashMap<String, Integer> collectData() {
        HashMap<String, Integer> list = new HashMap<>();
        int none, rock, goldfish, angelfish;
        none = rock = goldfish = angelfish = 0;

        for (Tile t : tiles) {
            Fish fish = t.getFish();
            if (fish instanceof None)
                none++;
            else if (fish instanceof Goldfish)
                goldfish++;
            else if (fish instanceof Angelfish)
                angelfish++;
            else
                rock++;
        }
        list.put("None", none);
        list.put("Rock", rock);
        list.put("Goldfish", goldfish);
        list.put("Angelfish", angelfish);

        return list;
    }

    /**
     * @author Riley Campbell
     * @name getDay
     * this method is a getter for the current day count
     * @return dayCount - the current day count
     */
    public int getDay() {
        return dayCount;
    }

    /**
     * @author Riley Campbell
     * @name getDeadCount
     * this method is a getter for the current dead count
     * @return deadCount - the current dead count
     */
    public int getDeadCount() {
        return deadCount;
    }

    /**
     * @author Riley Campbell
     * @name getFilled
     * this method is a getter for the current filled count
     * @return filled - the current filled count
     */
    public int getFilled(){
        return filled;
    }

    /**
     * @author Riley Campbell
     * @name getFishCount
     * this method is a getter for the current fish count
     * @return totalFish - the current fish count
     */
    public int getFishCount() {
        return totalFish;
    }

    /**
     * @author Riley Campbell
     * @name feedFish
     * this method feeds all of the fish in the aquarium by taking in the amount of food and dividing it equally
     * among the fish to reduce hunger by 1% for each unit of food received
     * @param totalFeed - the total amount of food to distribute
     */
    public void feedFish(int totalFeed) {
        if (totalFish * totalFeed > 0) {
            int feedAmount = totalFeed / totalFish;
            for (Tile t : tiles)
                if (t.isFish())
                    t.feedFish(feedAmount);
        }
    }

    /**
     * @author Riley Campbell
     * @name newDay
     * this method advances the day by 1 and then iterates through the array list of tiles and calls newDay() at each
     * tile that is a GoldFish or Angelfish. the fish that die are tallied and the total is returned from this method
     * @return died - the total number of fish that died
     */
    public int newDay() {
        int died = 0;
        dayCount++;
        for (Tile t : tiles) {
            if (t.isFish() && t.newDay()) {
                died++;
                totalFish--;
                filled--;
            }
        }
        deadCount += died;
        return died;
    }

    /**
     * @author Riley Campbell
     * @name reset
     * this method resets the values of dayCount, totalFish, deadCount, and filled all to 0
     */
    public void reset() {
        dayCount = totalFish = deadCount = filled = 0;
    }
}
