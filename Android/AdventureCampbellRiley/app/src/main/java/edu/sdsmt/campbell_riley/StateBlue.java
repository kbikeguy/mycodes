package edu.sdsmt.campbell_riley;

import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import java.util.ArrayList;

/**
 * @author Riley Campbell
 * this is the class for StateBlue that extends State. this utilizes the methods needed for handling
 * the blue state
 */
public class StateBlue extends State {
    /**
     * this is the constructor for BlueState
     * @param gameView - the object of GameView
     * @param machine - the object of StateMachine
     * @param gameButtons - the ArrayList of gameButtons
     * @param instructions the TestView of instructions
     */
    public StateBlue(GameView gameView, StateMachine machine, ArrayList<Button> gameButtons, TextView instructions) {
        super(gameView, machine, gameButtons, instructions);
    }

    /**
     * @author Riley Campbell
     * this is the doTask method for State. for the blue state, it is not needed
     */
    @Override
    public void doTask() {
        //not needed
    }

    /**
     * @author Riley Campbell
     * this is the end activity method for State in the blue state, it itterates through the
     * gameButtons and sets all of their enabled to false and their visibility to INVISIBLE
     */
    @Override
    public void endActivity() {
        for(Button butt : gameButtons){
            butt.setEnabled(false);
            butt.setVisibility(View.INVISIBLE);
        }
    }

    /**
     * @author Riley Campbell
     * this is the start activity method for State. in the blue state, it sets the background
     * image of gameView to R.drawable.blue_temple, calls gameView.moveToCenter() and passes in
     * StateMachine.StateEnum.Blue to gameView.showArrows(). next if gameView.getEndGame() returns
     * false, the gameButtons array is itterated through and each button is set to enabled and
     * visible and the instructions are set to visible
     */
    @Override
    public void startActivity() {
        //GRADING: ROOM
        //GRADING: EXTENSION 1a
        gameView.setImage(R.drawable.blue_temple);

        //GRADING: TRANSITION
        gameView.moveToCenter();

        gameView.showArrows(StateMachine.StateEnum.Blue);

        //GRADING: GUARD
        if(!gameView.getEndGame()) {
            for (Button butt : gameButtons) {
                butt.setEnabled(true);
                butt.setVisibility(View.VISIBLE);
            }

            instructions.setVisibility(View.VISIBLE);
        }
    }


}
