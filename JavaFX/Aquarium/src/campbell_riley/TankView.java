package campbell_riley;

import javafx.event.ActionEvent;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.ArrayList;

/**
 * @author Riley Campbell
 * this class builds the tank by extending GridPane
 */
public class TankView extends GridPane implements PropertyChangeListener {
    private Controller controller;
    private ArrayList<TileView> tileViews = new ArrayList<>();
    private Aquarium aquarium;
    private int rows, cols;

    /**
     * @author Riley Campbell
     * @name clearTank
     * this method clears ArrayList and the children, row constraints, and column constraints of TankView
     */
    public void clearTank() {
        tileViews.clear();
        this.getChildren().clear();
        this.getRowConstraints().clear();
        this.getColumnConstraints().clear();
        this.add(this, 0, 1);
    }

    /**
     * @author Riley Campbell
     * @name getAquarium
     * this method is a getter for this.aquarium
     * @return aquarium - the aquarium
     */
    public Aquarium getAquarium() {
        return aquarium;
    }


    /**
     * @author Riley Campbell
     * @name propertyChange
     * this is the observer for TankView
     * @param evt - the property change event
     */
    @Override //GRADING: OBSERVE
    public void propertyChange(PropertyChangeEvent evt)
    {
        //System.out.println("propertyChange reached");
    }

    /**
     * @author Riley Campbell
     * @name resize
     * this method resizes the tank to the dimensions passed in and builds a 2D gridpane of tileviews
     * @param row - the number of rows to resize to
     * @param col - the number of columns to resize to
     * @return this - the resized gridpane
     */
    public GridPane resize(int row, int col) {
        rows = row;
        cols = col;
        RowConstraints rowConst = new RowConstraints();
        rowConst.setPercentHeight(100.0 / row);
        ColumnConstraints colConst = new ColumnConstraints();
        colConst.setPercentWidth(100.0 / col);

        for (int i = 0; i < row; i++) {
            this.getRowConstraints().add(rowConst);
            for (int j = 0; j < col; j++) {
                if (i == 0)
                    this.getColumnConstraints().add(colConst);
                TileView button = new TileView("None", j + col * i);

                button.setId(String.valueOf(j + col * i));
                this.add(button, j, i);
                button.addEventFilter(ActionEvent.ACTION, controller);
                tileViews.add(button);
            }
        }
        setModel();

        return this;
    }

    /**
     * @author Riley Campbell
     * @name setController
     * this method is a setter for the controller
     * @param controller - the controller to set this.controller to
     */
    public void setController(Controller controller) {
        this.controller = controller;
    }

    /**
     * @author Riley Campbell
     * @name setModel
     * this method is a setter for the aquarium model
     */
    public void setModel() {
        aquarium = new Aquarium(rows, cols, tileViews);
        controller.setAquarium(aquarium);
    }

}
