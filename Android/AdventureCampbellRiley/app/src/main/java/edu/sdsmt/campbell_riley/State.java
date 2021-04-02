package edu.sdsmt.campbell_riley;

import android.widget.Button;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * @author Riley Campbell
 * this is the abstract class for States. it takes in the GameView, StateMachine, gameButtons, and
 * the instructions TextView.
 */
public abstract class State {

   // protected StateDiagram diagram;
    protected GameView gameView;
    protected StateMachine machine;
    protected  ArrayList<Button> gameButtons;
    protected TextView instructions;

    public State(GameView gameView, StateMachine machine, ArrayList<Button> gameButtons, TextView instructions){
        this.gameView = gameView;
        this.machine = machine;
        this.gameButtons = gameButtons;
        this.instructions = instructions;
    }

    public abstract void endActivity();
    public abstract void startActivity();
    public abstract void doTask();

}
