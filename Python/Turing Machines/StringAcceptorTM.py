class StringAcceptor:
    """
    this is the class for the String Acceptor. It has the ability to determine if a string is in the form of
    symbol1^n + symbol2^n + symbol3^n and if a string is in the form of ww^R, an even palindrome. the methods include a
    menu, setting up symbol1^n + symbol2^n + symbol3^n, setting up ww^R, running the tape, the constructor, the states
    for symbol1^n + symbol2^n + symbol3^n, and the states for ww^R.
    """
    def __init__(self):
        """
        this is the constructor for for StringAcceptor. it gives the class a blank, an empty tape, a final state, a
        start state, the input string, a dead state, a placeholder for symbol 1, a placeholder for symbol 2,
        a placeholder for symbol 3, a visitedX symbol, a visitedY symbol, a visitedZ symbol, an index pointer,
        a dictionary handler for the state function calls, and a target symbol placeholder
        """
        self.blank = '□'
        self.tape = []
        self.finalState = ''
        self.startState = ''
        self.string = ''
        self.deadState = ''
        self.symbol1 = ''
        self.symbol2 = ''
        self.symbol3 = ''
        self.visitedX = 'visitX'
        self.visitedY = 'visitY'
        self.visitedZ = 'visitZ'
        self.index = None
        self.handlers = dict()
        self.calculating = False
        self.target = ''
        self.R = 1
        self.L = -1

    def menu(self):
        """
        this method displays the menu for the StringAcceptor class. selecting option 1 will select, a^nb^nc^n and where
        a, b, and c are any three user input values. option 2 will select ww^R and where the string (ww^R) is even.
        option 3 will go back to the main menu.
        :return: the selected menu option
        """
        selection = '0'
        while selection not in "123":
            print("Make a selection of '1', '2, or '3' below")
            print("1. The language is a^nb^nc^n and where a, b, and c are any three user input values")
            print("2. The language is ww^R and where the string (ww^R) is even")
            selection = input("3. Go back\nSelection: ")

        return selection

    '''Start of the first machine'''

    def setInput1(self):
        """
        this method sets the input for the a^nb^nc^n language. it takes in a the input string for the machine to test,
        sets the final state to 'q5a', the dead state to 'q6a', and the start state to 'q0a'. next it begins making the
        first part of the tape. it checks that the input string has at least 1 symbol and if so, saves that to the
        symbol1 holder then transfers all of the matching symbols to the tape till a symbol is found that doesnt
        match or the end of the input string is found. then this same process is done to store symbol2 and symbol3 and
        transfer all their matching symbols to the tape. next it adds a blank to the tape. after this it sets up the
        handler dictionary of keys q0a to q4a with values for function calls of state_q0a to state_q4a.
        :return:
        """
        string = input("Enter the input string: ")

        self.finalState = 'q5a'
        self.deadState = 'q6a'
        self.startState = 'q0a'

        # make start of tape
        if len(string):
            self.symbol1 = string[0]
            while len(string) and string[0] == self.symbol1:
                self.tape.append(string[0])
                string = string[1:]

        # make middle of tape
        if len(string):
            self.symbol2 = string[0]
            while len(string) and string[0] == self.symbol2:
                self.tape.append(string[0])
                string = string[1:]

        # make end of tape
        if len(string):
            self.symbol3 = string[0]
            while len(string) and string[0] == self.symbol3:
                self.tape.append(string[0])
                string = string[1:]

        self.tape.append(self.blank)

        # set states
        self.handlers = {'q0a': self.state_q0a, 'q1a': self.state_q1a, 'q2a': self.state_q2a, 'q3a': self.state_q3a,
                         'q4a': self.state_q4a}

    def runSelection1(self):
        """
        this method runs the a^n+b^n+c^n. it sets the index to -1, the direction to 'R', and the handler to the initial
        state method. then it begins the Turing machine run by calling the state functions and checking the states that
        are returned. if the Dead State is returned, display the message that the input resulted in a dead state and
        the machine stops. if a final state is returned, display the message that the Final State was reached and the
        language was accepted, and the machine ends. otherwise, the new state is traversed to.
        :return:
        """
        self.index = -1
        direction = 'R'
        handler = self.handlers[self.startState]
        while True:
            newState, direction = handler(direction)

            if newState == self.deadState:
                print("Reached", newState + ", a Dead State, your language was not accepted")
                break
            elif newState == self.finalState:
                print("Reached", newState + ", a Final State, your language was accepted")
                break
            else:
                handler = self.handlers[newState]

    def state_q0a(self, direction):
        """
        this method checks the input direction and if it is a 'R', move the index right and checks the tape at the
        current index. if it is a symbol1, set the tape at the index to a visitedX then return 'q1a' and 'R'. if the tape
        at index is a visitedY, set the tape at index to visitedY, then return 'q2a' and 'R'. otherwise return the
        Dead State and None
        :param direction: the direction to move the index
        :return: the state to go to next, the direction to travel
        """
        if direction == 'R':
            self.index += self.R

        if self.tape[self.index] == self.symbol1:
            self.tape[self.index] = self.visitedX
            return 'q1a', 'R'
        elif self.tape[self.index] == self.visitedY:
            self.tape[self.index] = self.visitedY
            return 'q4a', 'R'

        # else its invalid
        return self.deadState, None

    def state_q1a(self, direction):
        """
        this method checks the input direction and if it is a 'R', move the index right and checks the tape at the
        current index. if it is a symbol1, set the tape at the index to a symbol1 then return 'q1a' and 'R'. if the tape
        at index is a visitedY, set the tape at index to visitedY, then return 'q1a' and 'R'. if the tape at index is a
        symbol2, set the tape at index to visitedY, and return 'q2a' and 'R'. otherwise return the
        Dead State and None
        :param direction: the direction to move the index
        :return: the state to go to next, the direction to travel
        """
        if direction == 'R':
            self.index += self.R

        if self.tape[self.index] == self.symbol1:
            self.tape[self.index] = self.symbol1
            return 'q1a', 'R'
        elif self.tape[self.index] == self.visitedY:
            self.tape[self.index] = self.visitedY
            return 'q1a', 'R'
        elif self.tape[self.index] == self.symbol2:
            self.tape[self.index] = self.visitedY
            return 'q2a', 'R'

        # else its invalid
        return self.deadState, None

    def state_q2a(self, direction):
        """
        this method checks the input direction and if it is a 'R', move the index right then it checks the tape at the
        current index. if it is a symbol2, set the tape at the index to a symbol2 then return 'q2a' and 'R'. if the tape
        at index is a visitedZ, set the tape at index to visitedZ, then return 'q2a' and 'R'. if the tape at index is a
        symbol3, set the tape at index to visitedZ, and return 'q3a' and 'L'. otherwise return the
        Dead State and None
        :param direction: the direction to move the index
        :return: the state to go to next, the direction to travel
        """
        if direction == 'R':
            self.index += self.R

        if self.tape[self.index] == self.symbol2:
            self.tape[self.index] = self.symbol2
            return 'q2a', 'R'
        elif self.tape[self.index] == self.visitedZ:
            self.tape[self.index] = self.visitedZ
            return 'q2a', 'R'
        elif self.tape[self.index] == self.symbol3:
            self.tape[self.index] = self.visitedZ
            return 'q3a', 'L'

        # else its invalid
        return self.deadState, None

    def state_q3a(self, direction):
        """
        this method checks the input direction and if it is a 'L', move the index left then it checks the tape at the
        current index. if it is a symbol1, set the tape at the index to a symbol1 then return 'q3a' and 'L'. if the tape
        at index is a symbol2, set the tape at index to symbol2, then return 'q3a' and 'L'. if the tape at index is a
        visitedY, set the tape at index to visitedY, and return 'q3a' and 'L'. if the tape at index is a
        visitedZ, set the tape at index to visitedZ, and return 'q3a' and 'L'. if the tape at index is a
        visitedX, set the tape at index to visitedX, and return 'q0a' and 'R'. otherwise return the
        Dead State and None
        :param direction: the direction to move the index
        :return: the state to go to next, the direction to travel
        """
        if direction == 'L':
            self.index += self.L

        if self.tape[self.index] == self.symbol1:
            self.tape[self.index] = self.symbol1
            return 'q3a', 'L'
        elif self.tape[self.index] == self.symbol2:
            self.tape[self.index] = self.symbol2
            return 'q3a', 'L'
        elif self.tape[self.index] == self.visitedY:
            self.tape[self.index] = self.visitedY
            return 'q3a', 'L'
        elif self.tape[self.index] == self.visitedZ:
            self.tape[self.index] = self.visitedZ
            return 'q3a', 'L'
        elif self.tape[self.index] == self.visitedX:
            self.tape[self.index] = self.visitedX
            return 'q0a', 'R'

        # else its invalid
        return self.deadState, None

    def state_q4a(self, direction):
        """
        this method checks the input direction and if it is a 'R', move the index right then it sets the calculating bool
        to True and checks the tape at the current index. if it is visitedY, set the tape at the index to visitedY
        then return 'q4a' and 'R'. if the tape at index is a visitedZ, set the tape at index to visitedZ, then return
        'q4a' and 'R'. if the tape at index is a blank,  return 'q5a' and None. otherwise return the Dead State and None
        :param direction: the direction to move the index
        :return: the state to go to next, the direction to travel
        """
        if direction == 'R':
            self.index += self.R
        self.calculating = True

        if self.tape[self.index] == self.visitedY:
            self.tape[self.index] = self.visitedY
            return 'q4a', 'R'
        elif self.tape[self.index] == self.visitedZ:
            self.tape[self.index] = self.visitedZ
            return 'q4a', 'R'
        elif self.tape[self.index] == self.blank:
            return 'q5a', None

        # else its invalid
        return self.deadState, None

    '''Start of the second machine'''

    def setInput2(self):
        """
        this method sets the input for the wwR language. it takes in a the input string for the machine to test, if the
        length of the string is zero, display an error message and return False. then set the target symbol to the first
        symbol in the input string, push the input string into the tape, and append on a blank symbol. then it sets the
        final state to 'q5b', the dead state to 'q4b', and the start state to 'q0b'. after this it sets up the
        handler dictionary of keys q0b to q3b with values for function calls of state_q0b to state_q3b. then return True
        :return: true or false
        """
        string = input("Enter a string to test for (ww^R): ").strip()

        # set states
        if len(string) == 0:
            print("Invalid entry")
            return False

        self.target = string[0]
        self.tape = list(string)
        self.tape.append(self.blank)
        self.startState = 'q0b'
        self.finalState = 'q5b'
        self.deadState = 'q4b'
        self.handlers = {'q0b': self.state_q0b, 'q1b': self.state_q1b, 'q2b': self.state_q2b, 'q3b': self.state_q3b}

        return True

    def runSelection2(self):
        """
        this method runs the wwR machine. it sets the index to -1, the direction to 'R', and the handler to the initial
        state method. then it begins the Turing machine run by calling the state functions and checking the states that
        are returned. if the Dead State is returned, display the message that the input resulted in a dead state and
        the machine stops. if a final state is returned, display the message that the Final State was reached and the
        language was accepted, and the machine ends. otherwise, the new state is traversed to.
        :return:
        """
        self.index = -1
        direction = 'R'
        handler = self.handlers[self.startState]
        while True:
            newState, direction = handler(direction)

            if newState == self.deadState:
                print("Reached", newState + ", a Dead State, your language was not accepted")
                break
            elif newState == self.finalState:
                print("Reached", newState + ", a Final State, your language was accepted")
                break
            else:
                handler = self.handlers[newState]

    def state_q0b(self, direction):
        """
        this method checks the input direction and if it is a 'R', move the index right, otherwise move the index left.
        then it checks the tape at the current index. if it is blank, set the tape at the index to blank then return
        the Final State and None. otherwise, set the target symbol to tape at the index, set the tape at the index a
        blank and return 'q1b and 'R'.
        :param direction: the direction to move the index
        :return: the state to go to next, the direction to travel
        """
        if direction == 'R':
            self.index += self.R
        else:
            self.index += self.L

        if self.tape[self.index] == self.blank:
            self.tape[self.index] = self.blank
            return self.finalState, None

        self.target = self.tape[self.index]
        self.tape[self.index] = self.blank
        return 'q1b', 'R'

    def state_q1b(self, direction):
        """
        this method checks the input direction and if it is a 'R', move the index right, then it checks the tape at the
        current index. if it is blank, set the tape at the index to blank then return 'q2b' and 'L'. otherwise, set the
        tape at the index to itself and return 'q1b and 'R'.
        :param direction: the direction to move the index
        :return: the state to go to next, the direction to travel
        """
        if direction == 'R':
            self.index += self.R
        if self.tape[self.index] == self.blank:
            self.tape[self.index] = self.blank
            return 'q2b', 'L'

        self.tape[self.index] = self.tape[self.index]
        return 'q1b', 'R'

    def state_q2b(self, direction):
        """
        this method checks the input direction and if it is a 'L', move the index left, then it checks the tape at the
        current index. if it is the target symbol, set the tape at the index to blank then return the 'q3b' and 'L'.
        otherwise, return the Dead State and 'L'.
        :param direction: the direction to move the index
        :return: the state to go to next, the direction to travel
        """
        if direction == 'L':
            self.index += self.L

        if self.tape[self.index] == self.target:
            self.tape[self.index] = self.blank
            return 'q3b', 'L'

        return self.deadState, None

    def state_q3b(self, direction):
        """
        this method checks the input direction and if it is a 'L', move the index left, then it checks the tape at the
        current index. if it is blank, set the tape at the index to blank then return the 'q0b' and 'R'.
        otherwise, return 'q3b' and 'L'.
        :param direction: the direction to move the index
        :return: the state to go to next, the direction to travel
        """
        if direction == 'L':
            self.index += self.L

        if self.tape[self.index] == self.blank:
            self.tape[self.index] = self.blank
            return 'q0b', 'R'

        return 'q3b', 'L'
