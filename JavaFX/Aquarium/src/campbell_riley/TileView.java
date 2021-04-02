package campbell_riley;

import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Priority;
import javafx.scene.text.TextAlignment;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import static java.lang.Math.*;

/**
 * @author Riley Campbell
 * this class builds the tile views and extends Button while implimenting PropertyChangeListener
 */
public class TileView extends Button implements PropertyChangeListener {
    private int index;

    /**
     * @author Riley Campbell
     * @name getIndex
     * this method is a getter for the index
     * @return index - the tile index assigned to this tile view
     */
    public int getIndex() {
        return index;
    }

    /**
     * @author Riley Campbell
     * @name propertyChange
     * this method sets the text of a tile view on a property change event and calls scaleText() to set the size of the
     * text
     * @param evt - the PropertyChangeEvent
     */
    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        this.setText((String) evt.getNewValue());
        this.scaleText();
    }

    /**
     * @author Riley Campbell
     * @name scaleText
     * this method determines the dimensions of the tile and scales the text accordingly
     */
    public void scaleText() {
        double width = this.getWidth();
        double height = this.getHeight();
        double pWidth = this.prefWidth(-1);
        double pHeight = this.prefHeight(-1);

        if (width * height * pWidth * pHeight == 0)
            return;

        double hScale = width / pWidth;
        double vScale = height / pHeight;

        this.lookup(".text").setScaleX(min(hScale, vScale));
        this.lookup(".text").setScaleY(min(hScale, vScale));
    }

    /**
     * @author Riley Campbell
     * @name TileView
     * this method is a constructor for TileView
     * @param name  - the string to set the button
     * @param index - the index to set the TileView index to
     */
    TileView(String name, int index) {
        this.index = index;
        this.setText(name);
        this.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        this.setTextAlignment(TextAlignment.CENTER);

        GridPane.setFillHeight(this, true);
        GridPane.setFillWidth(this, true);
        GridPane.setHgrow(this, Priority.ALWAYS);
        GridPane.setVgrow(this, Priority.ALWAYS);

        this.layoutBoundsProperty().addListener((obs, oldBounds, newBounds) -> scaleText());
        scaleText();
    }

}
