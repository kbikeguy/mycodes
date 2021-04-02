package edu.sdsmt.campbell_riley;

import android.widget.Button;
import android.widget.TextView;
import java.util.ArrayList;

/**
 * @author Riley Campbell
 * this is the class for StateRed that extends State. this utilizes the methods needed for handling
 * the red state
 */
public class StateRed extends State {
    /**
     * this is the constructor for RedState
     * @param gameView - the object of GameView
     * @param machine - the object of StateMachine
     * @param gameButtons - the ArrayList of gameButtons
     * @param instructions the TestView of instructions
     */
    public StateRed(GameView gameView, StateMachine machine, ArrayList<Button> gameButtons, TextView instructions) {
        super(gameView, machine, gameButtons, instructions);
    }

    /**
     * @author Riley Campbell
     * this is the doTask method for State. for the red state, it calls gameView.leaveGame()
     */
    @Override
    public void doTask() {
        gameView.leaveGame();
    }

    /**
     * @author Riley Campbell
     * this is the end activity method for State in the red state, it is not needed in the red state
     */
    @Override
    public void endActivity() {
        //not needed
    }

    /**
     * @author Riley Campbell
     * this is the start activity method for State. in the red state, it sets the background
     * image of gameView to R.drawable.red_temple, calls gameView.moveToCenter() and passes in
     * StateMachine.StateEnum.Red to gameView.showArrows()
     */
    @Override
    public void startActivity() {
        //GRADING: ROOM
        //GRADING: EXTENSION 1a
        gameView.setImage(R.drawable.red_temple);

        gameView.showArrows(StateMachine.StateEnum.Red);

        //GRADING: TRANSITION
        gameView.moveToCenter();
    }

}
