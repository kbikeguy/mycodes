import sys
# import readline
from RunProg import Run


class Load:

    def __init__(self):
        # set up symulated memory
        self.mem = bytearray(65536)

    # test function
    def printArray(self):
        for i in range(0, len(self.mem)):
            print(str(i) + '\t' + str(self.mem[i]))

    # test for exiting
    def exitCheck(self, timeToEnd):
        while (timeToEnd != 'exit'):
            try:
                # input('doing stuff')
                userInput = input('> ')
                timeToEnd = userInput
            except EOFError:
                timeToEnd = 'exit'
            except KeyboardInterrupt:
                timeToEnd = 'exit'

    # set the filepath
    def getfile(self):
        if len(sys.argv) != 1:
            name = sys.argv[1]
        else:
            name = None
        return name

    # filling the sudo memory
    def insertVals(self, start, hexstr):
        if self.testInput(start):
            start = int(start, 16)
            while len(hexstr) > 0:
                val = hexstr[:2]
                self.mem[start] = int(val, 16)
                hexstr = hexstr[2:]
                start += 1

    # print the range function
    def printRange(self, Str, period):
        if len(Str[: period]) == 0 or len(Str[period + 1:]) == 0:
            print('Invalid range entry')
            return

        if self.testInput(Str[: period]) and self.testInput(Str[period + 1:]):
            start = int(Str[: period], 16)
            stop = int(Str[period + 1:], 16) + 1

            if start <= stop:
                print(str(hex(start).lstrip('0x').upper()) or '00', end='\t')
                for i in range(start, stop):
                    hexval = str(hex(self.mem[i]).lstrip('0x').upper()) or '00'
                    if len(hexval) == 1:
                        hexval = '0' + hexval
                    if i != start and (i - start) % 8 == 0:
                        index = str(hex(i).lstrip('0x').upper()) or '00'
                        if len(index) == 1:
                            index = '0' + index
                        print('\n' + index.zfill(3), end='\t')
                    print(hexval.zfill(2), end=' ')
            else:
                print("The starting address can not be greater than the ending address")
            print()

    # edit memory function
    def editMem(self, changes, colon):
        if self.testInput(changes[: colon]):
            index = int(changes[: colon], 16)
            changes = changes[colon + 2:]

            while len(changes) != 0:
                if not self.testInput(changes[: 2]):
                    return
                self.mem[index] = int(changes[: 2], 16)
                index += 1
                changes = changes[3:]

    # test for invalid inputs
    def testInput(self, val):
        legal = '0123456789abcdefABCDEF'

        for i in val:
            if i not in legal:
                print('Not a valid input. Use a hex value')
                return False

        return True

    def openfiles(self):
        # fileName = getfile()

        # load file
        try:
            myObj = open(sys.argv[1], "r")
        except:
            print('Invalid file name', file=sys.stderr)
            pass
        else:
            for Str in myObj:
                if Str[1:3] != '00' and Str != '\n':
                    size = int(Str[1:3], 16) * 2 + 9
                    self.insertVals(Str[3:7], Str[9:size])
            myObj.close()

    # main
    def main(self):
        userInput = ''

        if len(sys.argv) > 1:
            self.openfiles()
            # check to loop again
        while userInput != 'exit':
            try:
                userInput = input('> ')
                # function calls
                # check a memory location
                period = userInput.find('.')
                colon = userInput.find(':')

                if period == -1 and colon == -1:
                    if userInput.endswith('R') and self.testInput(userInput[:-1]):
                        run = Run(userInput, self.mem)
                        run.runProg()
                    else:
                        try:
                            if userInput != 'exit' and self.testInput(userInput):
                                if not (int(userInput, 16) < 0 or int(userInput, 16) > 65535):
                                    hexval = hex(self.mem[int(userInput, 16)]).lstrip('0x').upper() or '0'
                                    print(userInput.zfill(3) + '\t' + hexval.zfill(2))
                                else:
                                    print(str(
                                        userInput) + 'is an invalid address. Choose an address from 0x0000 to 0xFFFF '
                                                     'inclusive')
                        except:
                            userInput = userInput.lower()
                elif period != -1:
                    # call print range
                    self.printRange(userInput, period)
                elif colon != -1:
                    # call change values
                    self.editMem(userInput, colon)

            except EOFError:
                userInput = 'exit'
            except KeyboardInterrupt:
                userInput = 'exit'
                print()


if __name__ == "__main__":
    Load().main()
