package edu.sdsmt.campbell_riley;

import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.fragment.app.DialogFragment;
import java.util.Objects;

/**
 * @author Riley Campbell
 * this is the class for the end of game dialog box
 */
public class EndDialog extends DialogFragment {

    private String msg;

    /**
     * @author Riley Campbell
     * this method is a setter for the final score time that will be displayed
     * @param time - the total time played
     */
    public void setMessage(int time){
        msg += time;
    }

    /**
     * @author Riley Campbell
     * this is the constructor for EndDialog. it sets the class member variable to
     * "Your score is: "
     */
    public EndDialog(){
        this.msg = "Your score is: ";
    }

    /**
     * @author Riley Campbell
     * this method creates the dialog box that will be displayed and sets up the onclick for the
     * restart
     */
    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        //GRADING: EXIT
        AlertDialog.Builder builder = new AlertDialog.Builder(Objects.requireNonNull(getActivity()));
        builder.setMessage(msg);
        builder.setPositiveButton(R.string.restart, new BasicClick());
        return builder.create();
    }

    /**
     * @author Riley Campbel
     * this is the onclick class for the dialog box. it impliments the needed code to restart the
     * activity with an Intent
     */
    class BasicClick implements DialogInterface.OnClickListener {

        @Override
        public void onClick(DialogInterface dialog, int which) {
            Intent intent = new Intent(getActivity(), MainActivity.class);
            MainActivity activity = (MainActivity)getActivity();

            assert activity != null;
            activity.finish();
            startActivity(intent);
        }
    }
}
