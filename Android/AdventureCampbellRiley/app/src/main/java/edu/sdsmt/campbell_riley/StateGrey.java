package edu.sdsmt.campbell_riley;

import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import java.util.ArrayList;

/**
 * @author Riley Campbell
 * this is the class for StateGrey that extends State. this utilizes the methods needed for handling
 * the grey state
 */
public class StateGrey extends State {
    /**
     * this is the constructor for GreyState
     * @param gameView - the object of GameView
     * @param machine - the object of StateMachine
     * @param gameButtons - the ArrayList of gameButtons
     * @param instructions the TestView of instructions
     */
    public StateGrey(GameView gameView, StateMachine machine, ArrayList<Button> gameButtons, TextView instructions) {
        super(gameView, machine, gameButtons, instructions);
    }

    /**
     * @author Riley Campbell
     * this is the doTask method for State. for the blue state. it is not needed in the grey state
     */
    @Override
    public void doTask() {
        //not needed
    }

    /**
     * @author Riley Campbell
     * this is the end activity method for State in the grey state. it is not needed for the grey
     * state
     */
    @Override
    public void endActivity() {
        //not needed
    }

    /**
     * @author Riley Campbell
     * this is the start activity method for State in the grey state. it sets the background
     * image of gameView to R.drawable.grey_temple, calls gameView.moveToCenter() and passes in
     * StateMachine.StateEnum.Grey to gameView.showArrows(). next if gameView.getEndGame() returns
     * false and gameView.getExitAllowed() returns true, instructions is set to VISIBLE, otherwise
     * it is set to INVIVIBLE
     */
    @Override
    public void startActivity() {
        //GRADING: TRANSITION
        gameView.moveToCenter();

        //GRADING: ROOM
        //GRADING: EXTENSION 1a
        gameView.setImage(R.drawable.grey_temple);

        gameView.showArrows(StateMachine.StateEnum.Grey);

        //GRADING: GUARD
        if(gameView.getExitAllowed() && !gameView.getEndGame())
            instructions.setVisibility(View.VISIBLE);
        else
            instructions.setVisibility(View.INVISIBLE);
    }

}
