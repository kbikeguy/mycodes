package edu.sdsmt.campbell_riley;

import android.animation.Animator;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import androidx.annotation.Nullable;
import androidx.core.content.ContextCompat;
import java.util.ArrayList;

/**
 * @author Riley Campbell
 * this is the class for GameView and it extends View. this class impliments the methods needed to
 * get the view of the game
 */
public class GameView extends View {
    private boolean exit = false;
    private boolean exitAllowed = false;
    private boolean moving = false;
    private boolean endGame = false;
    private boolean[] checker = {false, false, false, false};
    private StateMachine stateMachine;
    private String direction = null;
    private ArrayList<Button> gameButtons = new ArrayList<>();
    private int[] used = {-1, -1, -1, -1};
    private ImageView player;
    private ImageView left;
    private ImageView right;

    /**
     * @author Riley Campbell
     * this method checks if the minigame has been won by itterating through checker[] and returning
     * false if a false exhists in the array. otherwise, it returns true
     * @return the result of the check
     */
    private boolean checkForWinner() {
        for(int i = 0; i < 4; i++)
            if(!checker[i])
                return false;

        return true;
    }

    /**
     * @author Riley Campbell
     * this method takes in a button obhect and an index i. this is called when a user makes a
     * correct guess in the minigame. the button is set to the background color GREEN and the used
     * array at index i is set to the button's ID. the checker array at index i is also set to true
     * @param button - the Button to be altered
     * @param i - the index
     */
    private void correctGuess(Button button, int i) {
        used[i] = button.getId();
        checker[i] = true;
        button.setBackgroundColor(Color.GREEN);
    }

    /**
     * @author Riley Campbell
     * this method is the constructor for GameView
     * @param context - the Context
     * @param attrs - the AttributeSet
     */
    public GameView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        this.setBackground(ContextCompat.getDrawable(context, R.drawable.grey_temple));
    }

    /**
     * @author Riley Campbell
     * this methid is a getting for direction
     * @return direction
     */
    public String getDir() {
        return direction;
    }

    /**
     * @author Riley Campbell
     * this methid is a getting for the checker array
     * @return checker
     */
    public boolean[] getGameBools() {
        return checker;
    }

    /**
     * @author Riley Campbell
     * this methid is a getting for endGame
     * @return endGame
     */
    public boolean getEndGame(){
        return endGame;
    }

    /**
     * @author Riley Campbell
     * this methid is a getting for exit
     * @return exit
     */
    public boolean getExit(){
        return exit;
    }

    /**
     * @author Riley Campbell
     * this methid is a getting for exitAllowed
     * @return exitAllowed
     */
    public boolean getExitAllowed(){
        return exitAllowed;
    }

    /**
     * @author Riley Campbell
     * this methid is a getting for return value of stateMachine.GetState() as the integer value of
     * the current state enum
     * @return the integer value of the current state enum
     */
    public int getState() {
        return stateMachine.GetState().ordinal();
    }

    /**
     * @author Riley Campbell
     * this method is a getter for the used array
     * @return used
     */
    public int[] getUsed() {
        return used;
    }

    /**
     * @author Riley Campbell
     * this methid sets exit to true if exitAllowed is true
     */
    public void leaveGame() {
        if(exitAllowed)
            exit = true;
    }

    /**
     * @author Riley Campbell
     * this methos impliments the minigame extention i added into this program. when a button in the
     * blue room is clicked, the order it is clicked in is checked or the button id is already stored
     * at the same index in the used array. if the clicked id of the clicked button matches the id
     * of the Button in gameButtons at the index of the first availible false value in checker[],
     * the button will be passed to correctGuess(). otherwise, resetGame will be called. before
     * returning, exitAllowed is set equal to checkForWinner(),then exitAllowed is returned.
     * @param v - the View
     * @return - exitAllowed
     */
    public boolean miniGame(View v) {
        //GRADING: EXTENSION 4
        int id = v.getId();
        if(!checker[0] || id == used[0]){
            if(id == gameButtons.get(0).getId())
                correctGuess(gameButtons.get(0), 0);
            else
                resetGame();
        }
        else if(!checker[1] || id == used[1]){
            if(id == gameButtons.get(1).getId())
                correctGuess(gameButtons.get(1), 1);
            else
                resetGame();
        }
        else if(!checker[2] || id == used[2]){
            if(id == gameButtons.get(2).getId())
                correctGuess(gameButtons.get(2), 2);
            else
                resetGame();
        }
        else if(!checker[3] || id == used[3]){
            if(id == gameButtons.get(3).getId())
                correctGuess(gameButtons.get(3), 3);
            else
                resetGame();
        }

        exitAllowed = checkForWinner();

        return exitAllowed;
    }

    /**
     * @author Riley Campbell
     * this method moves the player left or right on the screen by calling and overwriting Animate.
     * inside onAnimatonStart(), setMoving is called to set the moving bool to true. inside
     * onAnimationEnd(), moving is checked and if true, then stateMachine() is called and passes in
     * dir. this method allowed for the directon of the player to be changed as a player is moving
     * to allow for GRADING EXTENSION 2b.
     * @param scale - -1 for moving left or 1 for moving right
     * @param dir - the direction to move
     */
    public void move(final int scale, final String dir) {

        direction = dir;

        int time = 5000;

        float move = (float) (this.getWidth()/2.0 - player.getWidth()/2.0);

        player.animate().setListener(new Animator.AnimatorListener() {
            @Override
            public void onAnimationStart(Animator animation) {
                setMoving();
            }

            @Override
            public void onAnimationEnd(Animator animation) {
                if(moving) {
                    stateMachine.reachedEdge(dir);
                }

                moving = false;

            }

            @Override
            public void onAnimationCancel(Animator animation) {
                Log.i("move","animation was cancelled");
                moving = false;
            }

            @Override
            public void onAnimationRepeat(Animator animation) {

            }
        }).setDuration(time).translationX(scale * move);


    }

    /**
     * @author Riley Campbell
     * this method resets the play to the center of a room with setTranslationX(0)
     */
    public void moveToCenter() {
        player.setTranslationX(0);
    }

    /**
     * @author Riley Campbell
     * this method draws the canvas with super.onDraw()
     * @param canvas - the Canvas
     */
    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
    }

    /**
     * @author Riley Campbell
     * this method resets is called when an invalid selection is made in the mini game. first a
     * toast is displayed stating "invalid selection" with a diration of LENGTH_SHORT. then all the
     * buttons colors are reset to LTGRAY. then all values in checker are set to false. lastly, all
     * values in used are set to -1
     */
    private void resetGame() {
        Toast.makeText(getContext(), R.string.invalid, Toast.LENGTH_SHORT).show();

        for(Button b : gameButtons)
            b.setBackgroundColor(Color.LTGRAY);

        checker[0] = checker[1] = checker[2] = checker[3] = false;
        used[0] = used[1] = used[2] = used[3] = -1;
    }

    /**
     * @author Riley Campbell
     * restore moving
     */
    public void restoreMove(final String dir, float start, float gameWidth, float playerWidth){
        //TODO: add code to restore moving and rotate
        direction = dir;
        int scale = 1;
        if(dir.equals("left"))
            scale = -1;

        int time = 5000;

        float move = (float) (gameWidth/2.0 - playerWidth/2.0) + start;
        //float leftSide = this.getLeft();
        player.setTranslationX(start * scale);
/*
        player.animate().setListener(new Animator.AnimatorListener() {
            @Override
            public void onAnimationStart(Animator animation) {
                setMoving();
            }

            @Override
            public void onAnimationEnd(Animator animation) {
                if(moving) {
                    stateMachine.reachedEdge(dir);
                }

                moving = false;

            }

            @Override
            public void onAnimationCancel(Animator animation) {
                Log.i("move","animation was cancelled");
                moving = false;
            }

            @Override
            public void onAnimationRepeat(Animator animation) {

            }
        }).setDuration(time).translationX(scale * move);

 */
    }

    /**
     * @author Riley Campbell
     * this method calls stateMachine.setState for restoring the state after a screen rotation
     * @param value - the state to restore to
     */
    public void restoreState(StateMachine.StateEnum value) {

        stateMachine.setState(value);
    }

    /**
     * @author Riley Campbell
     * this method is a setter for left and right
     * @param left - the left arrow
     * @param right - the right arrow
     */
    public void setArrows(ImageView left, ImageView right) {
        this.left = left;
        this.right = right;
    }

    /**
     * @author Riley Campbell
     * this method is a setter for gameButtons
     * @param buttons - the ArrayList of buttons to set gameButtons equal to
     */
    public void setButtons(ArrayList<Button> buttons){
        gameButtons.addAll(buttons);
    }

    /**
     * @author Riley Campbell
     * this method is a setter for direction
     * @param dir - the value to set direction equal to
     */
    public void setDir(String dir) {
        direction = dir;
    }

    /**
     * @author Riley Campbell
     * this method is a setter for endGame
     * @param endGame - the value to set endGame equal to
     */
    public void setEndGame( boolean endGame) {
        this.endGame = endGame;
    }

    /**
     * @author Riley Campbell
     * this method is a setter for the background image that the currect state will display
     * @param id - the drawable id to set the background image to
     */
    public void setImage(int id){
        //GRADING: EXTENSION 1a
        this.setBackground(ContextCompat.getDrawable(getContext(), id));
    }

    /**
     * @author Riley Campbell
     * this method is a setter for restoring the state of the minigame after a reset
     * fist the used array is set equal to ints, then the checker array is set equal to bools. finally
     * the gameButtons array is itterated through and if any idexes in bools are true, the background
     * color in the matching index of gameButtons is set to GREEN.
     * @param ints - the restoring int array
     * @param bools - the restoring bool array
     */
    public void setMiniGame(int[] ints, boolean[] bools) {
        used = ints;
        checker = bools;

        //set button colors
        for(int i = 0; i < 4; i++)
            if(bools[i]){
                gameButtons.get(i).setBackgroundColor(Color.GREEN);
            }
    }

    /**
     * @author Riley Campbell
     * this method sets moving to true
     */
    private void setMoving() {
        moving = true;
    }
    /**
     * @author Riley Campbell
     * this method is a setter for player
     * @param player - the imageView player will be set equal to
     */
    public void setNinja(ImageView player) {
        this.player = player;
    }
    /**
     * @author Riley Campbell
     * this method is a setter for exitAllowed and exit
     * @param exitAllowed - the value exitAllowed with be set equal to
     * @param exit - the value exit will be set equal to
     */
    public void setRestoredBools(boolean exitAllowed, boolean exit) {
        this.exitAllowed = exitAllowed;
        this.exit = exit;
    }

    /**
     * @author Riley Campbell
     * this method constructs a new object of stateMachine and sets it equal to stateMachine
     * @param instructions - the Textview the new StateMachine will be constructed with
     */
    public void setStateMachine(TextView instructions){

        stateMachine = new StateMachine(this, gameButtons, instructions);
    }

    /**
     * @author Riley Campbell
     * this method takes the current state enum and sets the visibility of the direction arrows
     * accordingly. if the state is Blue, the left facing arrow is set to invisible. if the state is
     * Red and getExitAllowed() returns false, the right facing arrow is set to invisible. else,
     * both the left and right faing arrows are set to visible.
     * @param state - the current state
     */
    public void showArrows(StateMachine.StateEnum state) {
        if(state == StateMachine.StateEnum.Blue)
            left.setVisibility(INVISIBLE);
        else if(state == StateMachine.StateEnum.Red && !getExitAllowed())
            right.setVisibility(INVISIBLE);
        else{
            left.setVisibility(VISIBLE);
            right.setVisibility(VISIBLE);
            }
    }

    public Boolean getMove() {
        return moving;
    }
}
