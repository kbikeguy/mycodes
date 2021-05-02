class Transducer:
    """
    this is the class for handling addition of unary and binary numbers. this includes a constructor, a method
    to check inputs for errors, methods to set the input state of the machines, a method to run the machines, and
    methods for all of the states
    """
    def __init__(self):
        """
        this method constructs the class and gives it a blank, 2 tapes with a blank in them, an answer queue, the
        startState, the finalState, a dictionary for the handles of function calls, and the index point
        """
        self.blank = '□'
        self.tape1 = [self.blank]
        self.tape2 = [self.blank]
        self.infinity = [self.blank, self.blank, self.blank, self.blank, self.blank, self.blank, self.blank, self.blank]
        self.answer = []
        self.startState = ''
        self.finalState = ''
        self.handlers = dict()
        self.index = 0
        self.L = -1
        self.R = 1

    def menu(self):
        """
        this method displays the menu for the Transducer class. selecting option 1 will select unary addition,
        option 2 will select binary addition, and option 3 will go back to the main menu.
        :return: the selected menu option
        """
        selection = '0'
        while selection not in "123":
            print("Make a selection of '1', '2, or '3' below")
            print("1. Addition of two unary numbers")
            print("2. Addition of two binary numbers")
            selection = input("3. Go back\nSelection: ")

        return selection

    def checkInput(self, input1, input2, language):
        """
        this method takes in two input strings and checks them against the language for the inputs. if anything in the
        inputs are not found in the language, or if either string is empty, the method returns False. otherwise, it
        returns True
        :param input1: user input 1
        :param input2: user input 2
        :param language: the language
        :return: true or false
        """
        if len(input1) < 1 or len(input2) < 1:
            return False

        for x in input1:
            if x not in language:
                return False

        for x in input2:
            if x not in language:
                return False

        return True

    def setInput2(self):
        """
        this method sets up the machine for binary addition. it asks the user for the two numbers to be added
        together. it then checks those inputs with checkInput() and if that returns False, the method returns False.
        next it pads the input strings with '0's on the left till they are of equal length. then it puts input 1 in
        tape1 with a leading '0', then it puts  input 2 in tape 2 with a leading '0'. then it sets the index to the
        length of the tape1, the start state to 'q0b, the final states to 'q2b', and sets the dictionary handler of
        keys q0b to q2b with values for function calls of state_q0b to state_q2b. lastly the method returns True
        :return: True or False
        """
        string1 = input("Enter the first binary number: ").strip()
        string2 = input("Enter the second binary number: ").strip()

        if not self.checkInput(string1, string2, '10'):
            print("Invalid entry for a binary number")
            return False

        # pad with 0s
        while len(string1) < len(string2):
            string1 = '0' + string1

        while len(string2) < len(string1):
            string2 = '0' + string2

        # put in the tapes
        self.tape1.append('0')
        self.tape2.append('0')
        self.tape1.extend(list(string1))
        self.tape2.extend(list(string2))

        # set handlers
        self.index = len(self.tape1)
        self.startState = 'q0b'
        self.finalState = 'q2b'
        self.handlers = {'q0b': self.state_q0b, 'q1b': self.state_q1b, 'q2b': self.state_q2b}

        return True

    def setInput1(self):
        """
        this method sets up the machine for unary addition. it asks the user for the two numbers to be added
        together. it then checks those inputs with checkInput() and if that returns False, the method returns False.
        next it puts the input 1 in the tape, then it puts a 'c' in the tape for a separator, then it puts input 2 in
        the tape, then it puts the blanks from the infinity list in the tape. after the tape is set up, it sets the
        index to 1, the start state to 'q0a, the final states to 'q5a', and sets the dictionary handler of keys q0a to
        q5a with values for function calls of state_q0a to state_q5a. lastly the method returns True
        :return: True or False
        """
        string1 = input("Enter the first unary number represented by 0s: ").strip()
        string2 = input("Enter the second unary number represented by 0s: ").strip()

        if not self.checkInput(string1, string2, '0'):
            print("Invalid entry for a unary number")
            return False

        # put inputs in the tape
        self.tape1.extend(list(string1))
        self.tape1.append('c')
        self.tape1.extend(list(string2))
        self.tape1.extend(self.infinity)

        # construct the states
        self.index = 1
        self.startState = 'q0a'
        self.finalState = 'q5a'
        self.handlers = {'q0a': self.state_q0a, 'q1a': self.state_q1a, 'q2a': self.state_q2a,
                         'q3a': self.state_q3a, 'q4a': self.state_q4a, 'q5a': self.state_q5a}

        return True

    def run(self):
        """
        this method runs the process for unary and binary addition. it sets a handler to the start state function and
        then begins running the machine by calling functions from the handlers dictionary with the keys returned from
        the state functions. this loop will end when a final state is reached. once that happens, the result from the
        run will be displayed from whichever final state is reached.
        :return:
        """
        handler = self.handlers[self.startState]
        while True:

            # safety check
            if self.index == len(self.tape1) - 1:
                self.tape1.extend(self.infinity)

            newState = handler()

            if newState == self.finalState:
                print("Reached", newState + ", a Final State, the answer is", self.handlers[newState]())
                break
            else:
                handler = self.handlers[newState]

    def state_q0b(self):
        """
        this method moves the index left and combines the values at the index from tape1 and tape2. if there is a blank
        in the value, return the final state. if the value is '11', insert '0' in the answer queue, and return 'q1b'. if
        the value is '01' or '10', insert '1' in the answer queue, and return 'q0b'. if the value is '00', insert '0' in
        the answer queue, and return 'q0b'
        :return: the state which to go to next
        """
        self.index += self.L

        val = self.tape1[self.index] + self.tape2[self.index]

        if self.blank in val:
            return self.finalState
        elif val == '11':
            self.answer.insert(0, '0')
            return 'q1b'
        elif val == '01' or val == '10':
            self.answer.insert(0, '1')
        elif val == '00':
            self.answer.insert(0, '0')

        return 'q0b'

    def state_q1b(self):
        """
        this method moves the index left and combines the values at the index from tape1 and tape2. if there is a blank
        in the value, return the final state. if the value is '00', insert '1' in the answer queue, and return 'q0b'. if
        the value is '01' or '10', insert '0' in the answer queue, and return 'q1b'. if the value is '11', insert '1' in
        the answer queue, and return 'q1b'
        :return: the state which to go to next
        """
        self.index += self.L

        val = self.tape1[self.index] + self.tape2[self.index]

        if self.blank in val:
            return self.finalState

        elif val == '00':
            self.answer.insert(0, '1')
            return 'q0b'
        elif val == '01' or val == '10':
            self.answer.insert(0, '0')
        elif val == '11':
            self.answer.insert(0, '1')

        return 'q1b'

    def state_q2b(self):
        """
        this method is the final state for the binary calculator. it strips all of the leading '0's from the answer
        and then converts the queue to a string to return for printing
        :return: the answer string
        """
        while self.answer[0] == '0':
            self.answer = self.answer[1:]

        return "'" + "".join(self.answer) + "'\n"

    def state_q0a(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to 'X', move the
        index right, then returns 'q1a'. if the tape at index is 'c', set the tape at index to blank, move the index
        right, then return 'q5a'.
        :return: the state which to go to next
        """
        if self.tape1[self.index] == '0':
            self.tape1[self.index] = 'X'
            self.index += self.R
            return 'q1a'

        # else its a 'c'
        self.tape1[self.index] = self.blank
        self.index += self.R
        return 'q5a'

    def state_q1a(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to '0', move the
        index right, then returns 'q1a'. if the tape at index is 'c', set the tape at index to 'c', move the index
        right, then return 'q2a'.
        :return: the state which to go to next
        """
        if self.tape1[self.index] == '0':
            self.tape1[self.index] = '0'
            self.index += self.R
            return 'q1a'

        # else is a c
        self.tape1[self.index] = 'c'
        self.index += 1
        return 'q2a'

    def state_q2a(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to '0', move the
        index right, then returns 'q2a'. if the tape at index is blank, set the tape at index to '0', move the index
        left, then return 'q3a'.
        :return: the state which to go to next
        """
        if self.tape1[self.index] == '0':
            self.tape1[self.index] = '0'
            self.index += self.R
            return 'q2a'

        # else its a blank
        self.tape1[self.index] = '0'
        self.index += self.L
        return 'q3a'

    def state_q3a(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to '0', move the
        index left, then returns 'q3a'. if the tape at index is 'c', set the tape at index to 'c', move the index
        left, then return 'q4a'.
        :return: the state which to go to next
        """
        if self.tape1[self.index] == '0':
            self.tape1[self.index] = '0'
            self.index += self.L
            return 'q3a'

        # else its a 'c'
        self.tape1[self.index] = 'c'
        self.index += self.L
        return 'q4a'

    def state_q4a(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to '0', move the
        index left, then returns 'q4a'. if the tape at index is 'X', set the tape at index to 'X', move the index
        right, then return 'q0a'.
        :return: the state which to go to next
        """
        if self.tape1[self.index] == '0':
            self.tape1[self.index] = '0'
            self.index += self.L
            return 'q4a'

        # else its an 'X'
        self.tape1[self.index] = 'X'
        self.index += self.R
        return 'q0a'

    def state_q5a(self):
        """
        this is the final state for the unary adder. if formats the output by stripping away all of the 'X's and
        blanks before returning the string
        :return: the answer string
        """
        return "'" + ''.join(self.tape1).replace('X', '').replace(self.blank, '') + "'"
