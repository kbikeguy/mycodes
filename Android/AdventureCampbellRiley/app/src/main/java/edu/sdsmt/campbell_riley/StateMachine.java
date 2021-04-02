package edu.sdsmt.campbell_riley;

import android.widget.Button;
import android.widget.TextView;
import java.util.ArrayList;

/**
 * @author Riley Campbell
 * this is the state machine class for handling the states that each room in the program must be set
 * to.
 */
public class StateMachine {

    public enum StateEnum {Blue, Grey, Red}

    private StateEnum state = StateEnum.Grey;
    private State[] stateArray;

    /**
     * @author Riley Campbell
     * this method is a getter for the current value of state
     * @return state
     */
    public StateEnum GetState() {
        return state;
    }

    /**
     * @author Riley Campbell
     * this method acts as a guard for handling all the states that could be needed. it takes in the
     * movement direction and determines the needed state based on that in relation to what the
     * state currently is set to. if the direction is left and the state is Grey, setState() is called
     * with StateEnum.Blue. if the direction is left and the state is Red, setState() is called
     * with StateEnum.Grey. if the direction is right and the state is Grey, setState() is called
     * with StateEnum.Red. if the direction is right and the state is Blue, setState() is called
     * with StateEnum.Grey. if the direction is right and the state is Red, doTask() is called for
     * the Red state.
     * @param dir - the direction
     */
    public void reachedEdge(String dir) {
        //moving left
        if(dir.equals("left")){
            //GRADING: GUARD
            if(state == StateEnum.Grey)
                setState(StateEnum.Blue);

                //GRADING: GUARD
            else if(state == StateEnum.Red)
                setState(StateEnum.Grey);
        }
        //moving right
        else{
            //GRADING: GUARD
            if(state == StateEnum.Grey)
                setState(StateEnum.Red);

                //GRADING: GUARD
            else if(state == StateEnum.Blue)
                setState(StateEnum.Grey);

                //GRADING: GUARD
            else {// state == StateEnum.Red and attempting to exit
                stateArray[state.ordinal()].doTask( );
            }
        }
    }

    /**
     * @author Riley Campbell
     * this method sets the state of the state machine. it takes in the new state to be set and
     * first calls endActivity() on the current state, then sets the state to the new state, lastly
     * startActivity() is called on the new state
     * @param state - the new state
     */
    public void setState(StateEnum state) {

        //Exit activities
        stateArray[this.state.ordinal()].endActivity();

        //New state
        this.state = state;

        //Entry activities
        stateArray[state.ordinal()].startActivity( );
    }

    /**
     * @author Riley Campbell
     * this method is the constructor for StateMachine. it takes in gameView, gameButtons, and
     * the instructions TextView. it fills the stateArray with new objects of State at the matching
     * indexes of the StateEnum
     * @param gameView - the object of GameView
     * @param gameButtons - the ArrayList of gameButtons
     * @param instructions - the instructions for the game
     */
    public StateMachine(GameView gameView, ArrayList<Button> gameButtons, TextView instructions) {

        stateArray = new State[]{
                new StateBlue( gameView, this, gameButtons, instructions),
                new StateGrey( gameView , this, gameButtons, instructions),
                new StateRed( gameView , this, gameButtons, instructions)
        };
    }

}
