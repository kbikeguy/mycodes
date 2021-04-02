package campbell_riley;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Paths;
import java.util.Scanner;

/**
 * This class will test your output against the given file list. This class will be OVERWRITTEN on our end.
 */
public class RunTests {
    public static void main(String[] args) throws IOException {

        //no argument try once to get it from the user
        if (args.length >= 1) {
            try {
                String[] tests = {"tier1", "tier2", "tier3", "tier4", "tier5", "tier6", "tier7"};

                for (String base : tests) {
                    String file = base + ".txt";
                    String outFile = base + "-student.out";
                    String answerFile = base + ".out";
                    boolean error = false;

                    //redirect input and output
                    PrintStream output = new PrintStream(outFile);
                    System.setOut(output);
                    FileInputStream is = new FileInputStream(file);
                    System.setIn(is);

                    //run program
                    Menu.main(args);

                    //close files
                    output.close();
                    is.close();

                    //check answers--------------------------------------------------------------------------------
                    Scanner answer = new Scanner(Paths.get(answerFile));
                    Scanner result = new Scanner(Paths.get(outFile));

                    System.err.println("\n\n\n\n\n\n" +
                            "-----------------------------" + base + "-----------------------------");

                    //check for a mismatch pass
                    while (answer.hasNext() && result.hasNext()) {
                        String ansLine = answer.nextLine();
                        String resultLine = result.nextLine();

                        if (!ansLine.equals(resultLine)) {
                            error = true;
                        }
                    }

                    //output pass, or the file with the problem lines
                    if (!error) {
                        System.err.println(ColorText.colorString("Passed", ColorText.Color.BLACK));
                    } else {
                        //check answers
                        answer = new Scanner(Paths.get(answerFile));
                        result = new Scanner(Paths.get(outFile));

                        while (answer.hasNext() && result.hasNext()) {
                            String ansLine = answer.nextLine();
                            String resultLine = result.nextLine();

                            if (ansLine.equals(resultLine)) {
                                System.err.println(ColorText.colorString(ansLine, ColorText.Color.BLACK));
                            } else {
                                System.err.println(">>>>>>>Error>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
                                System.err.print("Got.....");
                                System.err.println(resultLine);
                                System.err.print("Needed..");
                                System.err.println(ansLine);
                            }
                        }
                    }
                }
            } catch (Exception e) {
                //Any error, use normal console input
                System.out.println("Error redirecting input. Continue with console input");
            }
        }else{
            //run normally
            Menu.main(args); 
        }



    }
}
