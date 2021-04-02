package campbell_riley;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.geometry.Side;
import javafx.scene.chart.PieChart;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.effect.DropShadow;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.shape.Ellipse;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;

import java.awt.event.ActionEvent;
import java.util.HashMap;

/**
 * @author Riley Campbell
 * Description: This class builds the layout of the scene
 */
public class Layout {
    private Controller controller;
    private TankView tankView = new TankView();
    private BorderPane root;
    private Button feedBut;
    private Button newDay;
    private Button button3x3;
    private Button button4x5;
    private Button button6x8;
    private TextField feedAmount;
    private Text filled;
    private Text deadFish;
    private Text dayCount;
    private PieChart pieChart;
    private ObservableList<PieChart.Data> data = FXCollections.observableArrayList();
    private int goodlvl = 50;
    private int evillvl = 50;
    private Text textGood;
    private Text textEvil;
    private Rectangle good;
    private Rectangle evil;
    private double scale = 0.4; //THIS IS FOR EASY ADJUSTMENTS OF THE METER SIZE
    private ComboBox<String> comboBox = new ComboBox<>();


    /**
     * @author Riley Campbell
     * @name addListeners
     * this method add a listener for the combobox and passes the value to the controller
     */
    private void addListeners() {
        comboBox.getSelectionModel().selectedItemProperty().addListener((options, oldValue, newValue)
                -> controller.setComboSelection(newValue));
    }

    /**
     * @author Riley Campbell
     * @name clearTank
     * this method clears the tank by calling clearTank in the tankView class
     */
    public void clearTank() {
        tankView.clearTank();
    }

    /**
     * @return button3x3 - the button that sets the tank size to 3x3
     * @author Riley Campbell
     * @name get3x3Btn
     * this method is a getter for the button that sets the tank size to 3x3
     */
    public Button get3x3Btn() {
        return button3x3;
    }

    /**
     * @return button4x5 - the button that sets the tank size to 4x5
     * @author Riley Campbell
     * @name get4x5Btn
     * this method is a getter for the button that sets the tank size to 4x5
     */
    public Button get4x5Btn() {
        return button4x5;
    }

    /**
     * @return button6x8 - the button that sets the tank size to 6x8
     * @author Riley Campbell
     * @name get6x8Btn
     * this method is a getter for the button that sets the tank size to 6x8
     */
    public Button get6x8Btn() {
        return button6x8;
    }

    /**
     * @return tankView.getAquarium() - the state of the initial Aquarium fom tankView
     * @author Riley Campbell
     * @name getAquarium
     * this method is a getter for building the Aquarium
     */
    public Aquarium getAquarium() {
        return tankView.getAquarium();
    }

    /**
     * @return comboBox.getSelectionModel().getSelectedItem()
     * @author Riley Campbell
     * @name getComboBoxVal
     * This method returns the string value of the combo box.
     */
    String getComboBoxVal() {
        return comboBox.getSelectionModel().getSelectedItem();
    }

    /**
     * @return feedBut - the feed button object
     * @author Riley Campbell
     * @name getFeedBtn
     * this method is a getter for the feed button object, it is used to supply the Controller
     */
    public Button getFeedBtn() {
        return feedBut;
    }

    /**
     * @return newDay - the new day object button
     * @author Riley Campbell
     * @name getNewDayBtn
     * this method is a getter for the new day button object for the controller class
     */
    public Button getNewDayBtn() {
        return newDay;
    }

    /**
     * @return the amount of food to distribute among the fish
     * @author Riley Campbell
     * @name getTextField
     * this method is a getter for the Text Field object used in the scene to input the amount of food to feed the fish.
     * if an invalid user entry was made, this method will return 0 for the amount.
     */
    public int getTextField() {
        try {
            return Integer.parseInt(feedAmount.getText());
        } catch (Exception e) {
            return 0;
        }
    }

    /**
     * @param borderPane - the scene BorderPane
     * @author Riley Campbell
     * @name Layout
     * this method is the constructor for Layout
     */
    Layout(BorderPane borderPane) {
        root = borderPane;
    }

    /**
     * @return bottom - the final hbox
     * @author Riley Campbell
     * @name makeBottom
     * this method makes the bottom borderPane for the scene out of buttons, and texts and storing those elements into
     * a vbox in an hbox
     */
    private HBox makeBottom() {
        newDay = new Button("New Day");
        newDay.setAlignment(Pos.CENTER);

        dayCount = new Text("Day: 0");
        filled = new Text("Filled: 0");
        deadFish = new Text("Dead: 0");
        VBox stats = new VBox(dayCount, filled, deadFish);
        stats.setAlignment(Pos.CENTER);

        button3x3 = new Button("3x3");
        button4x5 = new Button("4x5");
        button6x8 = new Button("6x8");
        HBox dimensions = new HBox(button3x3, button4x5, button6x8);
        dimensions.setAlignment(Pos.CENTER);

        Region r1 = new Region();
        Region r2 = new Region();

        HBox bottom = new HBox(newDay, r1, stats, r2, dimensions);
        HBox.setHgrow(r1, Priority.ALWAYS);
        HBox.setHgrow(r2, Priority.ALWAYS);

        return bottom;
    }

    /**
     * @author Riley Campbell
     * @name makeContents
     * this method assembles the contents of of the scene from setLeft(), makeBottom(), and then addListeners()
     */
    void makeContents() {
        //add these to the end of the children list
        root.setLeft(makeLeft());
        HBox bottom = makeBottom();
        root.setBottom(bottom);
        BorderPane.setMargin(bottom, new Insets(10));

        addListeners();
    }

    /**
     * @param good - a bool for which end to build the handle from
     *             this method builds the handle for the lightsabers by assembling rectangles and an ellipse a hbox, a stackPane,
     *             and vboxes
     * @return handle - the final vbox
     * @author Riley Campbell
     * @name getHandle
     */
    private VBox makeHandle(boolean good) {
        //make button
        Ellipse but = new Ellipse();
        but.setRadiusX((20 / 6.0) * scale);
        but.setRadiusY(but.getRadiusX() * 2 * scale);
        but.setFill(Color.BLACK);
        Rectangle buttonBack = new Rectangle(20 * scale, 20 * scale);
        buttonBack.setFill(Color.DARKGRAY);
        StackPane button = new StackPane(buttonBack, but);

        //make black lines
        Rectangle black1 = new Rectangle((20 / 6.0) * scale, 40 * scale);
        black1.setFill(Color.BLACK);
        Rectangle black2 = new Rectangle((20 / 6.0) * scale, 40 * scale);
        black2.setFill(Color.BLACK);
        Rectangle black3 = new Rectangle((20 / 6.0) * scale, 40 * scale);
        black3.setFill(Color.BLACK);

        //make grey lines
        Rectangle grey1 = new Rectangle((20 / 6.0) * scale, 40 * scale);
        grey1.setFill(Color.DARKGRAY);
        Rectangle grey2 = new Rectangle((20 / 6.0) * scale, 40 * scale);
        grey2.setFill(Color.DARKGRAY);

        //make thin grey lines
        Rectangle side1 = new Rectangle((20 / 12.0) * scale, 40 * scale);
        side1.setFill(Color.DARKGRAY);
        Rectangle side2 = new Rectangle((20 / 12.0) * scale, 40 * scale);
        side2.setFill(Color.DARKGRAY);

        HBox strips = new HBox(side1, black1, grey1, black2, grey2, black3, side2);
        strips.setAlignment(Pos.CENTER);

        VBox handle = new VBox();
        if (good)
            handle.getChildren().addAll(strips, button);
        else
            handle.getChildren().addAll(button, strips);

        handle.setAlignment(Pos.CENTER);
        return handle;
    }

    /**
     * @return left - the final contents of the left borderPane
     * @author Riley Campbell
     * @name makeLeft
     * this method builds the contents of the left borderPane by calling moralityMeter() and building a pie chart,
     * 2 regions, a text, a text area, and a button
     */
    private VBox makeLeft() {
        comboBox.setPromptText("Choose fish");
        comboBox.getItems().addAll("Goldfish", "Angelfish", "Rock", "Remove");
        comboBox.setMaxWidth(Double.POSITIVE_INFINITY);
        pieChart = new PieChart();
        pieChart.setMaxSize(comboBox.getWidth(), comboBox.getWidth());
        pieChart.setLabelsVisible(true);
        pieChart.setLegendVisible(false);
        pieChart.setLegendSide(Side.TOP);
        pieChart.setClockwise(false);

        VBox moralityMeter = moralityMeter();
        moralityMeter.setAlignment(Pos.CENTER);
        moralityMeter.setFillWidth(true);

        pieChart.setTitle("Ratios");

        Text text = new Text("Feed Amount");
        feedAmount = new TextField();

        feedBut = new Button("Feed");
        VBox feedFish = new VBox(text, feedAmount, feedBut);
        feedFish.setAlignment(Pos.BOTTOM_CENTER);

        Region r1 = new Region();
        Region r2 = new Region();

        VBox left = new VBox(comboBox, pieChart, moralityMeter, r2, feedFish);
        VBox.setVgrow(r1, Priority.ALWAYS);
        VBox.setVgrow(r2, Priority.ALWAYS);
        left.setFillWidth(true);
        left.setAlignment(Pos.CENTER);

        return left;
    }

    /**
     * "@author Riley Camobell
     *
     * @return VBox(textGood, goodHandle, lightSide, darkSide, badHandle, textEvil) - the final assembled vbox
     * @name moralityMeter
     * this method builds the contents of the moral meter by calling getHandle() and building the blades out of
     * rectangles, and storing everything in vboxes.
     */
    private VBox moralityMeter() {

        Rectangle goodTip = new Rectangle(15 * scale, 5 * scale);
        goodTip.setFill(Color.AQUA);
        Rectangle badTip = new Rectangle(15 * scale, 5 * scale);
        badTip.setFill(Color.CRIMSON);
        good = new Rectangle();
        evil = new Rectangle();
        good.setFill(Color.AQUA);
        evil.setFill(Color.CRIMSON);
        good.setWidth(20 * scale);
        good.setHeight(175 * scale);
        evil.setWidth(20 * scale);
        evil.setHeight(175 * scale);
        textGood = new Text("Light Side " + goodlvl + "%");
        textEvil = new Text("Dark Side " + evillvl + "%");

        VBox lightSide = new VBox(good, goodTip);
        VBox darkSide = new VBox(badTip, evil);
        int depth = 70;


        DropShadow goodBorderGlow = new DropShadow();
        goodBorderGlow.setOffsetY(0f * scale);
        goodBorderGlow.setOffsetX(0f * scale);
        goodBorderGlow.setColor(Color.BLUE);
        goodBorderGlow.setWidth(depth * scale);
        goodBorderGlow.setHeight(depth * scale);

        VBox goodHandle = makeHandle(true);
        VBox badHandle = makeHandle(false);

        DropShadow EvilBorderGlow = new DropShadow();
        EvilBorderGlow.setOffsetY(0f * scale);
        EvilBorderGlow.setOffsetX(0f * scale);
        EvilBorderGlow.setColor(Color.RED);
        EvilBorderGlow.setWidth(depth * scale);
        EvilBorderGlow.setHeight(depth * scale);

        darkSide.setEffect(EvilBorderGlow);
        darkSide.setAlignment(Pos.CENTER);
        lightSide.setEffect(goodBorderGlow);
        lightSide.setAlignment(Pos.CENTER);

        good.setSmooth(true);
        evil.setSmooth(true);

        return new VBox(textGood, goodHandle, lightSide, darkSide, badHandle, textEvil);
    }

    /**
     * @author Riley Campbell
     * @name resetMeter
     * this method resets the initial values of the moral meter when switching tank sizes. good height = 100,
     * evel height = 100, good value = 50, evil value = 50, textGood = "Light Side " + goodlvl + "%",
     * textEvil = "Dark Side " + evillvl + "%"
     */
    public void resetMeter() {
        good.setHeight(100);
        evil.setHeight(100);
        goodlvl = evillvl = 50;

        textGood.setText("Light Side " + goodlvl + "%");
        textEvil.setText("Dark Side " + evillvl + "%");
    }

    /**
     * @param row - the number of needed rows
     * @param col - the number of needed columns
     * @author Riley Campbell
     * @name resize
     * this method resized the dimensions of the tank to the specified parameters
     */
    void resize(int row, int col) {
        root.setCenter(tankView.resize(row, col));
    }

    /**
     * @param controller - the initial controller object to build from
     * @author Riley Campbell
     * @name setController
     * this method is a setter for the Controller class in the initial construction
     */
    public void setController(Controller controller) {
        this.controller = controller;
        tankView.setController(controller);
    }

    /**
     * @author Riley Campbell
     * @name setCountText
     * this method is a setter for the Text that displays the number of aquarium tiles that are not empty
     */
    public void setCountText(int count) {
        filled.setText("Filled: " + count);
    }

    /**
     * @param day - the current day number
     * @author Riley Campbell
     * @name setDayText
     * this method is a setter for the Text that displays the current day count
     */
    public void setDayText(int day) {
        dayCount.setText("Day: " + day);
    }

    /**
     * @param deadCount - the current number of fish that have died
     * @author Riley Campbell
     * @name setDayText
     * this method is a setter for the Text that displays the current number of fish that have died
     */
    public void setDeadText(int deadCount) {
        deadFish.setText("Dead: " + deadCount);
    }

    /**
     * @author Riley Campbell
     * @name setDefaultPieChart
     * this method sets the default empty pie chart showing the number of empty tiles
     */
    public void setDefaultPieChart(int val) {
        data.clear();
        data.add(new PieChart.Data("None", val));
        pieChart.setData(data);
    }

    /**
     * @param deadFish - the number of fish that died on the most recend day change
     * @param fedFish  - the number of fish that were fed on the most recent feeding
     * @author Riley Campbell
     * @name setMorality
     * this method sets the display lengths of the lighsaber blades and updates the percentage texts
     */
    public void setMorality(int deadFish, int fedFish) {
        goodlvl += fedFish - (deadFish * 3);
        evillvl += (deadFish * 3) - fedFish;
        if (goodlvl < 0) {
            goodlvl = 0;
            evillvl = 100;
        } else if (goodlvl > 100) {
            goodlvl = 100;
            evillvl = 0;
        }
        if (evillvl < 0) {
            goodlvl = 0;
            evillvl = 100;
        } else if (evillvl > 100) {
            goodlvl = 100;
            evillvl = 0;
        }

        textEvil.setText("Dark Side " + evillvl + "%");
        textGood.setText("Light Side " + goodlvl + "%");
        good.setHeight(goodlvl * 3.5 * scale);
        evil.setHeight(evillvl * 3.5 * scale);

    }

    /**
     * @param list - the hashmap of fish to amounts
     * @author Riley Campbelll
     * @name setPieChart
     * this method sets the display of the pie chart based on the values stored in the input
     * hashmap where the key is the name of the objects in the tank and the value is the
     * amount. values less than 1 will not be displayed
     */
    public void setPieChart(HashMap<String, Integer> list) {
        data.clear();
        if (list.get("None") > 0)
            data.add(new PieChart.Data("None", list.get("None")));
        if (list.get("Goldfish") > 0)
            data.add(new PieChart.Data("Goldfish", list.get("Goldfish")));
        if (list.get("Angelfish") > 0)
            data.add(new PieChart.Data("Angelfish", list.get("Angelfish")));
        if (list.get("Rock") > 0)
            data.add(new PieChart.Data("Rock", list.get("Rock")));

        pieChart.setData(data);


    }

}
