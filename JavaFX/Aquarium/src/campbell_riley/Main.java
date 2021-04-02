package campbell_riley;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

/**
 * Program name: Aquarium
 * Author: Riley Campbell
 * Class: CSC 468
 * Language\Compiler: JavaFX/InelliJ
 * Description: This class is the main/starter class for Aquarium. It creates an application and stets up the stage.
 * this program is passing all tiers. my extension to look at first is the moral meter(lightsabors) i created, Dr.
 * Rebenitsch approved this for 15 points. the next extension is the pie chart, Dr. Rebenitsch approved this for 10
 * points. the final extension i made was #12.
 *
 * Known Bugs: None
 */
public class Main extends Application {

    private static final int WIDTH = 700;
    private static final int HEIGHT = 600;

    /**
     * @author Riley Campbell
     * @name main
     * this method calls launch and gets the ball rolling
     * @param args - the arguments
     */
    public static void main(String[] args)
    {
        launch(args);
    }

    /**
     * @author Riley Campbell
     * @name start
     * this method starts the application and builds the scene
     * @param primaryStage - the stage
     */
    @Override
    public void start(Stage primaryStage) {
        //BorderPane is an area that can hold Nodes
        BorderPane root = new BorderPane();
        Layout layout = new Layout(root);

        //Scene is the contents of the window
        //stage is the entire window
        Scene scene = new Scene(root,WIDTH , HEIGHT);
        primaryStage.setScene(scene);
        primaryStage.setMinHeight(HEIGHT);
        primaryStage.setMinWidth(WIDTH);
        primaryStage.setTitle("Aquarium of Death");
        layout.makeContents();
        new Controller(layout);
        layout.resize(3,3);

        //make visible
        primaryStage.show();
    }
}