package campbell_riley;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.paint.Color;

import java.util.ArrayList;

/**
 * @author Riley Campbell
 * Description: This class controls the interface between the view and the model
 */
public class Controller implements EventHandler<ActionEvent> {
    private Layout layout;
    private Aquarium aquarium;
    private String fishName;
    Label output = new Label("test");
    ArrayList<TextField> myList = new ArrayList<>();
    Button input = new Button();

    /**
     * @author Riley Campbell
     * @name Controller
     * this method is the constructor for Controller. Controller is set up with the buttons from Layout
     * @param layout1 - the object from Layout
     */
    public Controller(Layout layout1) {
        layout = layout1;
        Button fb = layout.getFeedBtn();

        //test question 2
        input.addEventFilter(ActionEvent.ACTION, event -> {
            if (output.getTextFill() == Color.RED)
                output.setTextFill(Color.BLUE);
            else
                output.setTextFill(Color.RED);
        });

        //test question 3
        input.addEventFilter(ActionEvent.ACTION, event -> {
            for(int i = 0; i < myList.size(); i++){
                if (myList.get(i).getText().contains("here")){
                    output.setText(String.valueOf(i));
                    return;
                }
            }
        });


        fb.addEventFilter(ActionEvent.ACTION, event -> handleFeedEvent());

        Button nd = layout.getNewDayBtn();
        nd.addEventFilter(ActionEvent.ACTION, event -> handleNewDayEvent());

        Button size3x3 = layout.get3x3Btn();
        size3x3.addEventFilter(ActionEvent.ACTION, event -> handleResize(3, 3));

        Button size4x5 = layout.get4x5Btn();
        size4x5.addEventFilter(ActionEvent.ACTION, event -> handleResize(4, 5));

        Button size6x8 = layout.get6x8Btn();
        size6x8.addEventFilter(ActionEvent.ACTION, event -> handleResize(6, 8));

        layout.setController(this);
        aquarium = layout.getAquarium();
        if(aquarium != null)
            layout.setPieChart(aquarium.collectData());
        else
            layout.setDefaultPieChart(9);
    }

    /**
     * @author Riley Campbell
     * @name handle
     * this method hands adding and removing fish and rocks to the aquarium. it does error checking to prevent fish
     * and rocks from being stacked, and empty tiles from being removed. then the fish/rocks are added or removed if
     * everything passed error checking and the stats are updated.
     * @param actionEvent - the tile action event
     */
    @Override
    public void handle(ActionEvent actionEvent) {
        String fish = ((Button) actionEvent.getSource()).getText();
        fishName = layout.getComboBoxVal();
        Fish currFish;
        if ("Goldfish".equals(fishName) && fish.contains("None")) {
            currFish = new Goldfish();
        } else if ("Angelfish".equals(fishName) && fish.contains("None")) {
            currFish = new Angelfish();
        } else if ("Rock".equals(fishName) && fish.contains("None")) {
            currFish = new Rock();
        } else if ("Remove".equals(fishName) && !fish.contains("None")) {
            currFish = new None();
        } else
            return;
        int index = ((TileView) actionEvent.getSource()).getIndex();

        if (aquarium != null) {
            aquarium.changeFish(currFish, index, fish);
            layout.setCountText(aquarium.getFilled());
            layout.setPieChart(aquarium.collectData());
        }
    }

    /**
     * @author Riley Campbell
     * @name handleFeedEvent
     * this method handles the request to feed the fish by checking how much food was added with getTextField() in
     * Layout, calling feedFish() in Aquarium, and updating the moral meter based on how many fish were fed
     */
    private void handleFeedEvent() {
        int feedAmount = layout.getTextField();

        if(feedAmount > 0) {
            aquarium.feedFish(feedAmount);
            layout.setMorality(0, aquarium.getFishCount());
        }
    }

    /**
     * @author Riley Campbell
     * @name handleNewDayEvent
     * this method handles the request of a new day by calling newDay() in Aquarium, updating the stats with
     * updateStats(), and updating the moral meter based on how many fish died
     */
    private void handleNewDayEvent() {
        int dead = aquarium.newDay();
        updateStats();
        layout.setMorality(dead, 0);
    }

    /**
     * @author Riley Campbell
     * @name handleResize
     * this method handles all of the resizing of the tank based on the dimensions that are passed in as well as
     * clearing the stored information in Aquarium, the pie chart, and the moral meter
     * @param row - the number of rows to resize to
     * @param col - the number of columns to resize to
     */
    private void handleResize(int row, int col) {
        layout.clearTank();
        layout.resize(row, col);
        aquarium.reset();
        layout.resetMeter();
        layout.setDayText(0);
        layout.setDeadText(0);
        layout.setCountText(0);
        layout.setDefaultPieChart(row * col);
    }

    /**
     * @author Riley Campbell
     * @name setAquarium
     * this is a setter for this.aquarium
     * @param aquarium - the Aquarium object to set this.aquarium equal to
     */
    public void setAquarium(Aquarium aquarium) {
        this.aquarium = aquarium;
    }

    /**
     * @author Riley Campbell
     * @name setComboSelection
     * this method is a setter for fishName based on the current fish selected in the combo box
     * @param fish - the fish to set fishName equal to
     */
    public void setComboSelection(String fish) {
        fishName = fish;
    }

    /**
     * @author Riley Campbell
     * @name updateStats
     * this method calls all of the stats displays in Layout to update them with current information. these includeL
     * setDayText(), setDeadText(), setCountText(), and setPieChart().
     */
    private void updateStats(){
        layout.setDayText(aquarium.getDay());
        layout.setDeadText(aquarium.getDeadCount());
        layout.setCountText(aquarium.getFilled());
        layout.setPieChart(aquarium.collectData());
    }
}
