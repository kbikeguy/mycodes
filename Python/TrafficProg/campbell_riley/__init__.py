import io
import sys

# This class will test your output against the given file list. This class will be OVERWRITTEN on our end.
#run the code?
#import campbell_riley.TrafficProg

import sys



# argument, try to run tests
from campbell_riley import MainStarter
from campbell_riley.ColorText import ColorText

if(len(sys.argv) > 1):
    tests = ["..\\tier1","..\\tier2","..\\tier3","..\\tier4","..\\tier5"
        ,"..\\tier6","..\\tier7","..\\tier8","..\\tier9","..\\tier10"]

    for base in tests:
        file = base + ".txt"
        outFile = base + "-student.out"
        answerFile = base + ".out"

        # redirect input and output
        output = open(outFile, "w")
        sys.stdout = output
        inf = open(file)
        input = "".join(inf.readlines())
        sys.stdin = io.StringIO(input)

        MainStarter.main()

        inf.close()
        output.close()

        answer = open(answerFile)
        result = open(outFile)

        sys.stderr.write(ColorText.fg.black + "\n\n\n\n\n\n" + ColorText.reset)
        sys.stderr.write(ColorText.fg.black +
                          "----------------------------" + base + "-----------------------------" + ColorText.reset + "\n")

        # check for a mismatch pass
        ansLines = answer.readlines()
        resultLines = result.readlines()
        error = False
        if( len(ansLines) != len(resultLines)):
            error = True
        for i in range(0, min(len(ansLines), len(resultLines))):
            if ansLines[i].rstrip() != resultLines[i].rstrip():
                error = True

        # output pass, or the file with the problem lines
        if not error:
            sys.stderr.write(ColorText.fg.black + "Passed" + ColorText.reset + "")
        else:
            for i in range(0, min(len(ansLines), len(resultLines))):

                if ansLines[i].rstrip() == resultLines[i].rstrip():
                    sys.stderr.write(ColorText.fg.black + ansLines[i] + ColorText.reset + "")
                else:
                    sys.stderr.write(">>>>>>>Error>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n")
                    sys.stderr.write("Got.....|")
                    sys.stderr.write(resultLines[i])
                    sys.stderr.write("Needed..|")
                    sys.stderr.write(ansLines[i])

            if(len(ansLines)< len(resultLines)) :
                for i in range(len(ansLines), len(resultLines) ):
                    sys.stderr.write(">>>>>>>Error>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n")
                    sys.stderr.write("Got.....|")
                    sys.stderr.write(resultLines[i])
                    sys.stderr.write("Needed..|")
                    sys.stderr.write("")

            al = len(ansLines)
            rl = len(resultLines)
            if (len(ansLines) > len(resultLines)):
                for i in range(len(resultLines), len(ansLines)):
                    sys.stderr.write(">>>>>>>Error>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n")
                    sys.stderr.write("Got.....|")
                    sys.stderr.write("")
                    sys.stderr.write("Needed..|")
                    sys.stderr.write(ansLines[i])

    sys.exit()