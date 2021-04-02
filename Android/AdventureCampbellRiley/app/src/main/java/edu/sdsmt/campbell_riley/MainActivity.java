package edu.sdsmt.campbell_riley;

import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Objects;

public class MainActivity extends AppCompatActivity {

    private static final String DISPLAYTIMER = "displayTimer" ;
    private static final String DISPLAYDIRECTION = "displayDirection";
    private static final String EXITALLOWED = "exitAllowed";
    private static final String EXIT = "exit";
    private static final String INSTRUCTIONS = "instructions";
    private static final String GAMEBOOLS = "gameBools";
    private static final String GAMEUSED = "gameused";
    private static final String BUTTONORDER = "buttonOrder";
    private static final String DISPLAYFAB = "displayFAB";
    private static final String VIEWSTATE = "viewState";
    private static final String ENDGAME = "endgame";
    private static final String PLAYERMOVING = "playerMoving";
    private static final String PLAYERLOCATION = "playerLocation";
    private static final String DIRECTION = "direction";
    private static final String VIEWWIDTH = "viewWidth";
    private static final String PLAYERWIDTH = "playerWidth";
    private ImageView player;
    private ImageView left;
    private ImageView right;
    private static final String DISPLAYSCORE = "displayScore";
    private static final String DISPLAYNINJA = "displayNinja";
    private TextView score;
    private FloatingActionButton black;
    private FloatingActionButton yellow;
    private boolean isFABOpen = false;
    private boolean isYellow = false;
    private float pressX;
    private GameView gameView;
    private int time = 0;
    private ArrayList<Button> gameButtons = new ArrayList<>();
    private TextView instructions;
    private ArrayList<Integer> shuffled = new ArrayList<>();
    private EndDialog result = new EndDialog();
    private boolean endGame = false;

    /**
     * @author Riley Campbell
     * this method sets inFABOpen to false and closes the menu by setting the Y translation of black
     * and yellow to 0
     */
    private void closeFABMenu() {
        isFABOpen = false;
        black.animate().translationY(0);
        yellow.animate().translationY(0);
    }

    /**
     * @author Riley Campbell
     * this method clears the screen upon finishing the game by callings setVisibility() on left,
     * right, player, gameView, instructions, and score. it also calls gameView.setEndgame(endGame)
     * and calls .hide() on the floating action buttons.
     */
    private void clearScreen() {
        left.setVisibility(View.INVISIBLE);
        right.setVisibility(View.INVISIBLE);
        gameView.setEndGame(endGame);
        FloatingActionButton burst = findViewById(R.id.floatBurst);
        burst.hide();
        black.hide();
        yellow.hide();
        player.setVisibility(View.GONE);
        gameView.setVisibility(View.GONE);
        instructions.setVisibility(View.INVISIBLE);
        score.setVisibility(View.INVISIBLE);
    }

    /**
     * @author Riley Campbell
     * this method takes in a float of a do value and converts it to its pixel equivalent
     * @param dp - the dp value
     * @return - the pixel equivalent
     */
    public float DpToPixels(float dp) {
        float pxPerDp = (float) getResources().getDisplayMetrics().densityDpi
                / DisplayMetrics.DENSITY_DEFAULT;
        return dp * pxPerDp;
    }

    /**
     * @author Riley Campbell
     * this method take in a boolean and if it is false, the shuffled integer array is filled with
     * values 0 through 3 and then the values are shuffled with Collections.shuffled(). if the
     * boolean is true, the shuffled array is already filled and shuffled and this method is being
     * used for restoring the state after a screen rotate. next the int array is itterated through
     * and the value at each index will be the button number stored at the current index. for example,
     * if shuffled[0] == 3, gameButtons[0] == button3.
     * @param restore = the bool
     */
    public void randomizer(boolean restore){
        if(!restore) {
            for (int i = 0; i < 4; i++)
                shuffled.add(i + 1);

            Collections.shuffle(shuffled);
        }

        int index = 0;
        for(Integer i : shuffled){
            if(i == 1) {
                gameButtons.set(index, (Button) findViewById(R.id.button1));
            }
            else if(i == 2) {
                gameButtons.set(index, (Button) findViewById(R.id.button2));
            }
            else if(i == 3) {
                gameButtons.set(index, (Button) findViewById(R.id.button3));
            }
            else {
                gameButtons.set(index, (Button) findViewById(R.id.button4));
            }

            index++;
        }

    }

    /**
     * @author Riley Campbell
     * this is method is the onclick for the for the game buttons. when activated, gameView.miniGame()
     * will be called. if it returns true, the text for instructions will be set to R.strings.go
     */
    public void onGame(View view) {
        if(gameView.miniGame(view))
            instructions.setText(R.string.go);
    }

    /**
     * @author Riley Campbell
     * this method takes in the View, sets player resource to R.drawable.black_ninja and isYellow
     * to false
     * @param view - the View
     */
    public void onBlack(View view) {
        //GRADING: EXTENSION 1b
        player.setImageResource(R.drawable.black_ninja);
        isYellow = false;
    }

    /**
     * @author Riley Campbell
     * this method takes in the View and if isFABOpen is false, showFABMenu() is called, otherwise
     * closeFABMenue() is called
     * @param view - the View
     */
    public void onBurst(View view) {
        if (!isFABOpen) {
            showFABMenu();
        } else {
            closeFABMenu();
        }
    }

    /**
     * @author Riley Campbel
     * this method is the onCreat for this program. it initializes all the member variables and
     * calls restore() if saved isnt null. lastly, startTimer() is called to set up the parallel
     * threaded timer
     * @param saved the saved state from a rotation
     */
    @Override
    protected void onCreate(Bundle saved) {
        super.onCreate(saved);
        setContentView(R.layout.activity_main);
        gameView = findViewById(R.id.gameView);
        //set up minigame buttons
        gameButtons.add(null);
        gameButtons.add(null);
        gameButtons.add(null);
        gameButtons.add(null);
        instructions = findViewById(R.id.textView2);

        if(saved == null) {
            randomizer(false);
            gameView.setButtons(gameButtons);
        }

        gameView.setStateMachine(instructions);

        black = findViewById(R.id.floatBlack);
        yellow = findViewById(R.id.floatYellow);
        score = findViewById(R.id.textView);
        player = findViewById(R.id.ninja);

        gameView.setNinja(player);
        left = findViewById(R.id.left_arrow);
        right = findViewById(R.id.right_arrow);
        gameView.setArrows(left, right);


        //handle rotation
        if(saved != null)
            restore(saved);

        startTimer();
    }

    /**
     * @author Riley Campbell
     * this method overrides onSaveInstanceState to save all of the needed values for a restore
     * @param saved - the saved state
     */
    @Override
    public void onSaveInstanceState(@NonNull Bundle saved) {
        super.onSaveInstanceState(saved);

        ////////////SAVE MOVING PLAYER/////////////////////////////////////
        Boolean moving = gameView.getMove();
        saved.putBoolean(PLAYERMOVING, moving);
        if(moving) {
            saved.putFloat(PLAYERWIDTH, player.getWidth());
            saved.putFloat(VIEWWIDTH, gameView.getWidth());
            saved.putFloat(PLAYERLOCATION, player.getX());
            saved.putString(DIRECTION, gameView.getDir());
        }
        //////////////////////////////////////////////////////////////////////


        ////////////SAVE MINIGAME/////////////////////////
        //save button order
        saved.putIntegerArrayList(BUTTONORDER, shuffled);
        //save end of game
        saved.putBoolean(ENDGAME, endGame);
        //save game used
        saved.putIntArray(GAMEUSED, gameView.getUsed());
        //save game booleans
        saved.putBooleanArray(GAMEBOOLS, gameView.getGameBools());
        //save exit allowed status
        saved.putBoolean(EXITALLOWED, gameView.getExitAllowed());
        //save exit
        saved.putBoolean(EXIT, gameView.getExit());
        //save instructions
        saved.putString(INSTRUCTIONS, (String) instructions.getText());
        ///////////////////////////////////////////////////////////////////

        // save the time
        saved.putInt(DISPLAYTIMER, time);
        //save the score display
        saved.putString(DISPLAYSCORE, (String) score.getText());
        //save the player color
        saved.putBoolean(DISPLAYNINJA, isYellow);
        //save state of the floating action buttons
        saved.putBoolean(DISPLAYFAB, isFABOpen);
        //save direction
        saved.putString(DISPLAYDIRECTION, gameView.getDir());
        //save state
        saved.putInt(VIEWSTATE, gameView.getState());
    }

    /**
     * @author Riley Campbell
     * this method handles the on touch event for moving the player left or right. ACTION_DOWN
     * records the X location of the touch. upon ACTION_UP, the new X location is compaired to the
     * ACTION_DOWN X location. if ACTION_DOWN_X is less than ACTION_UP_X, gameView.move() will be
     * called with the first parameter set to 1 and the second parameter is set to "right".
     * otherwise, gameView.move() is called with the first parameter set to -1 and the second
     * parameter set to "left".
     * @param event The motion event describing the touch
     * @return true if the touch is handled, otherwise false
     */
    public boolean onTouchEvent(MotionEvent event) {
        boolean handled = false;
        switch (event.getActionMasked()) {
            case MotionEvent.ACTION_DOWN:
                pressX = event.getX();
                handled = true;
                break;

            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_CANCEL:
                //moving right
                if(pressX < event.getX()){
                    gameView.move(1,"right");
                }
                //moving move left
                else {
                    gameView.move(-1, "left");

                }
                handled = true;
                break;

            case MotionEvent.ACTION_MOVE:
                break;
        }

        return handled;
    }

    /**
     * @author Riley Campbell
     * this method takes in the View and set the player resource to R.drawable.yellow_ninja and
     * sets isYellow to true
     * @param view - the View
     */
    public void onYellow(View view) {
        //GRADING: EXTENSION 1b
        player.setImageResource(R.drawable.yellow_ninja);
        isYellow = true;
    }

    /**
     * @author Riley Campbell
     * this method takes in the saved state bundle and restores all the matching variables values
     * to their preview state
     * @param saved - the saved state Bundle
     */
    private void restore(Bundle saved) {



        //restore end of game
        endGame = saved.getBoolean(ENDGAME);
        gameView.setEndGame(endGame);
        /////////////RESTORE MINIGAME////////////////////////////////
        //instructions.setText(saved.getString(INSTRUCTIONS));
        shuffled = saved.getIntegerArrayList(BUTTONORDER);
        randomizer(true);
        gameView.setButtons(gameButtons);
        gameView.setRestoredBools(saved.getBoolean(EXITALLOWED), saved.getBoolean(EXIT));
        gameView.setMiniGame(saved.getIntArray(GAMEUSED), saved.getBooleanArray(GAMEBOOLS));
        /////////////////////////////////////////////////////////////////


        // restore the score display
        score.setText(saved.getString(DISPLAYSCORE));

        //restore the player
        if (saved.getBoolean(DISPLAYNINJA)) {
            player.setImageResource(R.drawable.yellow_ninja);
            isYellow = true;
        }

        //restore player direction
        String dir = saved.getString(DISPLAYDIRECTION);
        if(dir != null)
            gameView.setDir(dir);

        //restore state
        gameView.restoreState(StateMachine.StateEnum.values()[saved.getInt(VIEWSTATE)]);

        //restore FABs
        isFABOpen = saved.getBoolean(DISPLAYFAB);
        if (isFABOpen)
            showFABMenu();

        //restore the current time
        time = saved.getInt(DISPLAYTIMER);


        /////////////////RESTORE MOVEMENT/////////////////////////////////
        if(saved.getBoolean(PLAYERMOVING)){
            float gameWidth = saved.getFloat(VIEWWIDTH);
            float playerWidth = saved.getFloat(PLAYERWIDTH);
            dir = saved.getString(DIRECTION);
            float loc = saved.getFloat(PLAYERLOCATION);
            assert dir != null;
            gameView.restoreMove(dir, loc, gameWidth, playerWidth);
        }
        //////////////////////////////////////////////////////////////////
    }

    /**
     * @author Riley Campbell
     * this method sets isFABOpen to true and opens the menu by translating the Y location of black
     * by 55 dp and translating the Y lovation of yellow by 105 dp. both of these utilize DptoPixel()
     * to handle giving the translationY() calls the needed pixels
     */
    private void showFABMenu() {
        isFABOpen = true;
        black.animate().translationY(DpToPixels(55));
        yellow.animate().translationY(DpToPixels(105));
    }

    /**
     * @author Riley Campbell
     * this method sets up a parallel thread and handles the timer for tracking the current time used
     * in the game. this is also where the ending of the game is continually checked and if a user
     * makes a valid exit of the game, clearScreen() is called to erase the gameView, calls
     * result.setMassage() to give it the ending time and then result.show() to display the final
     * dialog box
     */
    private void startTimer() {
        //GRADING: EXTENSION 2c
        Thread timer = new Thread(){
            @Override
            public void run(){
                while(!isInterrupted()){

                    //this is used to end the game and exit the thread
                    if(gameView.getExit()) {
                        gameView.post(new Runnable() {
                            @Override
                            public void run() {
                                endGame = true;
                                clearScreen();
                                result.setMessage(time);
                                //GRADING: EXIT
                                result.show(getSupportFragmentManager(), "load");
                            }
                        });
                        return;
                    }

                    try {
                        //handles the 1 second counter
                        Thread.sleep(1000);
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                time++;
                                String temp = getString(R.string.display_time) + " " + time;
                                score.setText(temp);
                            }
                        });
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        timer.start();
    }

}
