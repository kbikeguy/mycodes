class Complex:
    """
    This is the class for handling unary multiplication and division. the methods include a menu, setting up
    multiplication, setting up division, running the tape, the constructor, the states for multiplication, and the
    states for division
    """
    def __init__(self):
        """
        This is the constructor for Complex. it sets blank to '□', tape to a list with 1 blank, infinity to a list with
        8 blanks, the start state to '', final states to an empty list, the stack to an empty list, the handlers to an
        empty dictionary, the index of the tape to 0, the right direction to 1, and the left direction to -1
        """
        self.blank = '□'
        self.tape = [self.blank]
        self.infinity = [self.blank, self.blank, self.blank, self.blank, self.blank, self.blank, self.blank, self.blank]
        self.startState = ''
        self.finalStates = []
        self.stack = []
        self.handlers = dict()
        self.index = 0
        self.R = 1
        self.L = -1

    def menu(self):
        """
        this method displays the menu for the Complex class. selecting option 1 will select unary multiplication,
        option 2 will select unary division, and option 3 will go back to the main menu.
        :return: the selected menu option
        """
        selection = '0'
        while selection not in "123":
            print("Make a selection of '1', '2, or '3' below")
            print("1. Multiplication of two unary numbers")
            print("2. Division of two unary numbers")
            selection = input("3. Go back\nSelection: ")

        return selection

    def checkInput(self, input1, input2, language):
        """
        this method takes in two input strings and checks them against the language for the inputs. if anything in the
        inputs are not found in the language, the method returns False. otherwise, it returns True
        :param input1: user input 1
        :param input2: user input 2
        :param language: the language
        :return: true or false
        """
        for x in input1:
            if x not in language:
                return False

        for x in input2:
            if x not in language:
                return False

        return True

    def setInput1(self):
        """
        this method sets up the machine for multiplication. it asks the user for the two numbers to be multiplied
        together. it then checks those inputs with checkInput() to see if anything isn't a '0'. if so, it returns False.
        next it puts the input 1 in the tape, then it puts a 'c' in the tape for a separator, then it puts input 2 in
        the tape, then it puts a blank in the tape. after the tape is set up, it sets the index to 1, the start state
        to 'q0a, the final states to 'q12a', and sets the dictionary handler of keys q0a to q12a with values for
        function calls of state_q0a to state_q12a. lastly the method returns True
        :return: True or False
        """
        string1 = input("Enter the first unary number represented by 0s: ").strip()
        string2 = input("Enter the second unary number represented by 0s: ").strip()

        if not self.checkInput(string1, string2, '0'):
            print("Invalid entry for a unary number")
            return False

        # put inputs in the tape
        self.tape.extend(list(string1))
        self.tape.append('c')
        self.tape.extend(list(string2))
        self.tape.append(self.blank)

        # construct the states
        self.index = 1
        self.startState = 'q0a'
        self.finalStates = ['q12a']
        self.handlers = {'q0a': self.state_q0a, 'q1a': self.state_q1a, 'q2a': self.state_q2a, 'q3a': self.state_q3a,
                         'q4a': self.state_q4a, 'q5a': self.state_q5a, 'q6a': self.state_q6a, 'q7a': self.state_q7a,
                         'q8a': self.state_q8a, 'q9a': self.state_q9a, 'q10a': self.state_q10a, 'q11a': self.state_q11a,
                         'q12a': self.state_q12a}

        return True

    def run(self):
        """
        this method runs the process for multiplication and division. it sets a handler to the start state function and
        then begins running the machine by calling functions from the handlers dictionary with the keys returned from
        the state functions. this loop will end when a final state is reached. once that happens, the result from the
        run will be displayed from whichever final state is reached.
        :return:
        """
        handler = self.handlers[self.startState]
        while True:
            newState = handler()

            # safety check
            if self.index == len(self.tape) - 1:
                self.tape.extend(self.infinity)

            if newState in self.finalStates:
                print("Reached", newState + ", a Final State, the answer is", self.handlers[newState]())
                break
            else:
                handler = self.handlers[newState]

    '''********************Start of Multiplication****************************'''

    def state_q0a(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to '0' move the
        index right, then return 'q0a'. if the tape at index is 'c', set the tape at index to 'c', move the tape right,
        then return 'q1a'
        :return: the state which to go to next
        """
        if self.tape[self.index] == '0':
            self.tape[self.index] = '0'
            self.index += self.R
            return 'q0a'

        # else its a 'c'
        self.tape[self.index] = 'c'
        self.index += self.R
        return 'q1a'

    def state_q1a(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to '0' and move the
        index right, then return 'q1a'. if the tape at index is a blank, set the tape at index to 'c', move the index
        left, then return 'q2a'
        :return: the state which to go to next
        """
        if self.tape[self.index] == '0':
            self.tape[self.index] = '0'
            self.index += self.R
            return 'q1a'

        # else its a blank
        self.tape[self.index] = 'c'
        self.index += self.L
        return 'q2a'

    def state_q2a(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to '0', move the
        index left, then returns 'q2a'. if the tape at index is 'c', set the tape at index to 'c', move the index
        right, then return 'q3a'
        :return: the state which to go to next
        """
        if self.tape[self.index] == '0':
            self.tape[self.index] = '0'
            self.index += self.L
            return 'q2a'

        # else its a 'c'
        self.tape[self.index] = 'c'
        self.index += self.R
        return 'q3a'

    def state_q3a(self):
        """
        this method checks the tape at the current index. if it is a 'X', set the tape at the index to 'X', move the
        index right, then returns 'q3a'. if the tape at index is 'c', set the tape at index to blank, move the index
        right, then return 'q12a'. if it is a '0', set the tape at index to 'X', move the index left, then return 'q4a
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'X':
            self.tape[self.index] = 'X'
            self.index += self.R
            return 'q3a'

        elif self.tape[self.index] == 'c':
            self.tape[self.index] = self.blank
            self.index += self.R
            return 'q12a'

        # else its a '0'
        self.tape[self.index] = 'X'
        self.index += self.L
        return 'q4a'

    def state_q4a(self):
        """
        this method checks the tape at the current index. if it is a 'X', set the tape at the index to 'X', move the
        index left, then returns 'q4a'. if the tape at index is 'c', set the tape at index to 'c', move the index
        left, then return 'q5a'
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'X':
            self.tape[self.index] = 'X'
            self.index += self.L
            return 'q4a'

        # else its a 'c'
        self.tape[self.index] = 'c'
        self.index += self.L
        return 'q5a'

    def state_q5a(self):
        """
        this method checks the tape at the current index. if it is a 'Y', set the tape at the index to 'Y', move the
        index left, then returns 'q5a'. if the tape at index is a blank, set the tape at index to blank, move the index
        right, then return 'q11a'. if it is a '0', set the tape at index to 'Y', move the index right, then return 'q6a
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'Y':
            self.tape[self.index] = 'Y'
            self.index += self.L
            return 'q5a'

        elif self.tape[self.index] == self.blank:
            self.tape[self.index] = self.blank
            self.index += self.R
            return 'q11a'

        # else its a '0'
        self.tape[self.index] = 'Y'
        self.index += self.R
        return 'q6a'

    def state_q6a(self):
        """
        this method checks the tape at the current index. if it is a 'Y', set the tape at the index to 'Y', move the
        index right, then returns 'q6a'. if the tape at index is 'c', set the tape at index to 'c', move the index
        right, then return 'q7a'
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'Y':
            self.tape[self.index] = 'Y'
            self.index += self.R
            return 'q6a'

        # else its a 'c'
        self.tape[self.index] = 'c'
        self.index += self.R
        return 'q7a'

    def state_q7a(self):
        """
        this method checks the tape at the current index. if it is a 'c', set the tape at the index to 'c', move the
        index right, then returns 'q8a'. if the tape at index is '0', set the tape at index to '0', move the index
        right, then return 'q7a'. if it is a 'X', set the tape at index to 'X', move the index right, then return 'q7a
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'c':
            self.tape[self.index] = 'c'
            self.index += self.R
            return 'q8a'

        # else its a '0' or 'X'
        self.tape[self.index] = self.tape[self.index]
        self.index += self.R
        return 'q7a'

    def state_q8a(self):
        """
        this method checks the tape at the current index. if it is a blank, set the tape at the index to '0', move the
        index left, then returns 'q9a'. if the tape at index is '0', set the tape at index to '0', move the index
        right, then return 'q8a'
        :return: the state which to go to next
        """
        if self.tape[self.index] == self.blank:
            self.tape[self.index] = '0'
            self.index += self.L
            return 'q9a'

        # else its a '0'
        self.tape[self.index] = '0'
        self.index += self.R
        return 'q8a'

    def state_q9a(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to '0', move the
        index left, then returns 'q9a'. if the tape at index is 'c', set the tape at index to 'c', move the index
        left, then return 'q10a'
        :return: the state which to go to next
        """
        if self.tape[self.index] == '0':
            self.tape[self.index] = '0'
            self.index += self.L
            return 'q9a'

        # else its a 'c'
        self.tape[self.index] = 'c'
        self.index += self.L
        return 'q10a'

    def state_q10a(self):
        """
        this method checks the tape at the current index. if it is a 'c', set the tape at the index to 'c', move the
        index left, then returns 'q5a'. if the tape at index is '0', set the tape at index to '0', move the index
        left, then return 'q10a'. if it is a 'X', set the tape at index to 'X', move the index left, then return 'q10a
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'c':
            self.tape[self.index] = 'c'
            self.index += self.L
            return 'q5a'

        # else its a '0' or 'X'
        self.tape[self.index] = self.tape[self.index]
        self.index += self.L
        return 'q10a'

    def state_q11a(self):
        """
        this method checks the tape at the current index. if it is a 'Y', set the tape at the index to '0', move the
        index right, then returns 'q11a'. if the tape at index is 'c', set the tape at index to 'c', move the index
        right, then return 'q3a'.
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'Y':
            self.tape[self.index] = '0'
            self.index += 1
            return 'q11a'

        # else its a 'c'
        self.tape[self.index] = 'c'
        self.index += 1
        return 'q3a'

    def state_q12a(self):
        """
        this method removes the blank from the left side of the tape, then its searched for first index that a blank is
        found in starting from the left. once it fights that index, it strips everything from that index left. next a
        string is constructed from only the 0s on the tape encased in single quotes before returning it.
        :return: the state which to go to next
        """
        self.tape = self.tape[1:]
        blank = self.tape.index(self.blank)
        self.tape = self.tape[blank:]

        return "'" + ''.join(self.tape).strip(self.blank) + "'"

    '''********************Start of Division****************************'''

    def setInput2(self):
        """
        this method sets up the machine for division. it asks the user for the two numbers to be divided together. it
        then checks those inputs with checkInput() to see if anything isn't a '0'. if so, it returns False. next it
        checks that the divisor is equal to at least a one, if not, it returns False. next it puts the input 1 in the
        tape, then it puts a 'c' in the tape for a separator, then it puts input 2 in the tape, then it puts a 'c' in
        the tape for a separator, then it adds the infinity list to the tape. after the tape is set up, it pushes a 'X'
        onto the stack, sets the index to 1, the start state to 'qa, the final states to ''q8b', 'qd', 'qe'', and sets
        the dictionary handler of keys to 'qa' to 'qe' and 'q0b' to 'q08' with values for function calls of state_qa to
        state_qe and state_q0b to state_q08. lastly the method returns True
        :return: True or False
        """
        string2 = input("Enter the dividend unary number represented by 0s: ").strip()
        string1 = input("Enter the divisor unary number represented by 0s: ").strip()

        if not self.checkInput(string1, string2, '0'):
            print("Invalid entry for a unary number")
            return False

        if len(string1) < 1:
            print("Division by zero is not allowed")
            return False

        # put inputs in the tape
        self.tape.extend(list(string1))
        self.tape.append('c')
        self.tape.extend(list(string2))
        self.tape.append('c')
        self.tape.extend(self.infinity)

        # set the stack
        self.stack.append('X')

        # construct the states
        self.index = 1
        self.startState = 'qa'
        self.finalStates = ['q8b', 'qd', 'qe']
        self.handlers = {'q0b': self.state_q0b, 'q1b': self.state_q1b, 'q2b': self.state_q2b, 'q3b': self.state_q3b,
                         'q4b': self.state_q4b, 'q5b': self.state_q5b, 'q6b': self.state_q6b, 'q7b': self.state_q7b,
                         'q8b': self.state_q8b, 'qa': self.state_qa, 'qb': self.state_qb, 'qc': self.state_qc,
                         'qd': self.state_qd, 'qe': self.state_qe}

        return True

    def state_qa(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to '0', push a '0'
        onto the stack, move the index right, then return 'qa'. if the tape at index is 'c', set the tape at index to
        'c', move the index right, then return 'qb'.
        :return: the state which to go to next
        """
        # if we have 0s to read in, fill the stack with them
        if self.tape[self.index] == '0':
            self.tape[self.index] = '0'
            self.stack.append(self.tape[self.index])
            self.index += self.R
            return 'qa'

        # if we're done reading in 0s, move to state_qb
        elif self.tape[self.index] == 'c':
            self.tape[self.index] = 'c'
            self.index += self.R
            return 'qb'

    def state_qb(self):
        """
        this method checks the tape at the current index. if it is a 'c', set the tape at the index to 'c', move the
        index right, then return 'qd'. if the tape at index is 'c' and the top of the stack is '0', set the tape at
        index to '0', move the index right, then return 'qc'.
        :return: the state which to go to next
        """
        # check if dividend is greater than 0
        if self.tape[self.index] == 'c':
            self.tape[self.index] = 'c'
            self.index += self.R
            return 'qd'

        elif self.tape[self.index] == '0' and self.stack.pop() == '0':
            self.tape[self.index] = '0'
            self.index += self.R
            return 'qc'

    def state_qc(self):
        """
        this method checks the tape at the current index. if it is a 'c' and the top of the stack is not 'X, set the
        tape at the index to 'c', move the index left, then return 'qe'. if the tape at index is '0' and the top of the
        stack is not 'X', set the tape at index to '0', pop the value off the top of the stack, move the index right,
        then return 'qc'. otherwise set index to 1 and return 'q0b'
        :return: the state which to go to next
        """
        # if divisor is greater than dividend
        if self.tape[self.index] == 'c' and self.stack[-1] != 'X':
            self.tape[self.index] = 'c'
            self.index += self.L
            return 'qe'

        elif self.tape[self.index] == '0' and self.stack[-1] != 'X':
            self.tape[self.index] = '0'
            self.stack.pop()
            self.index += self.R
            return 'qc'

        # else its good and we can divide normally now
        self.index = 1
        return 'q0b'

    def state_qe(self):
        """
        this method is one of the final states for the division. it builds the answer string initially with 'Q = , R = '
        and then sets the index to 1. next start walking through the tape and appending all '0's to the answer string
        until a 'c' is found. then return the string.
        :return: the string with the answer
        """
        answer = "'Q = , R = "
        self.index = 1
        while self.tape[self.index] != 'c':
            answer += self.tape[self.index]
            self.index += self.R

        return answer + "'"

    def state_qd(self):
        """
        this method is one of the final states for the division. it builds the answer string initially with
        'Q = , R = ' then return the string.
        :return: the string with the answer
        """
        return "'Q = , R = '"

    def state_q0b(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to blank, move the
        index right, then returns 'q1b'. if the tape at index is 'c', set the tape at index to 'c', move the index
        right, then return 'q4a'.
        :return: the state which to go to next
        """
        if self.tape[self.index] == '0':
            self.tape[self.index] = self.blank
            self.index += self.R
            return 'q1b'

        elif self.tape[self.index] == 'c':
            self.tape[self.index] = 'c'
            self.index += self.R
            return 'q4b'

    def state_q1b(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to '0', move the
        index right, then returns 'q1b'. if the tape at index is 'c', set the tape at index to 'c', move the index
        right, then return 'q2a'.
        :return: the state which to go to next
        """
        if self.tape[self.index] == '0':
            self.tape[self.index] = '0'
            self.index += self.R
            return 'q1b'

        elif self.tape[self.index] == 'c':
            self.tape[self.index] = 'c'
            self.index += self.R
            return 'q2b'

    def state_q2b(self):
        """
        this method checks the tape at the current index. if it is a '0', set the tape at the index to 'x', move the
        index left, then returns 'q3b'. if the tape at index is 'x', set the tape at index to 'x', move the index
        right, then return 'q2b'. if the tape at index is 'c', set the tape at index to 'c', move the index
        left, then return 'q6b'.
        :return: the state which to go to next
        """
        if self.tape[self.index] == '0':
            self.tape[self.index] = 'x'
            self.index += self.L
            return 'q3b'

        elif self.tape[self.index] == 'x':
            self.tape[self.index] = 'x'
            self.index += self.R
            return 'q2b'

        elif self.tape[self.index] == 'c':
            self.tape[self.index] = self.blank
            self.index += self.L
            return 'q6b'

    def state_q3b(self):
        """
        this method checks the tape at the current index. if it is a 'c', set the tape at the index to 'c', move the
        index left, then returns 'q3b'. if the tape at index is '0', set the tape at index to '0', move the index
        left, then return 'q3b'. if the tape at index is 'x', set the tape at index to 'x', move the index
        left, then return 'q3b'. if the tape at index is blank, set the tape at index to '0', move the index
        right, then return 'q0b'.
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'c':
            self.tape[self.index] = 'c'
            self.index += self.L
            return 'q3b'

        elif self.tape[self.index] == '0':
            self.tape[self.index] = '0'
            self.index += self.L
            return 'q3b'

        elif self.tape[self.index] == 'x':
            self.tape[self.index] = 'x'
            self.index += self.L
            return 'q3b'

        elif self.tape[self.index] == self.blank:
            self.tape[self.index] = '0'
            self.index += self.R
            return 'q0b'

    def state_q4b(self):
        """
        this method checks the tape at the current index. if it is a 'x', set the tape at the index to 'x', move the
        index right, then returns 'q4b'. if the tape at index is '0', set the tape at index to '0', move the index
        right, then return 'q4b'. if the tape at index is 'c', set the tape at index to 'c', move the index
        right, then return 'q4b'. if the tape at index is blank, set the tape at index to '0', move the index
        left, then return 'q5b'.
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'x':
            self.tape[self.index] = 'x'
            self.index += self.R
            return 'q4b'

        elif self.tape[self.index] == '0':
            self.tape[self.index] = '0'
            self.index += self.R
            return 'q4b'

        elif self.tape[self.index] == 'c':
            self.tape[self.index] = 'c'
            self.index += self.R
            return 'q4b'

        elif self.tape[self.index] == self.blank:
            self.tape[self.index] = '0'
            self.index += self.L
            return 'q5b'

    def state_q5b(self):
        """
        this method checks the tape at the current index. if it is a 'c', set the tape at the index to 'c', move the
        index left, then returns 'q5b'. if the tape at index is '0', set the tape at index to '0', move the index left,
        then return 'q5b'. if the tape at index is 'x', set the tape at index to 'x', move the index left, then return
        'q5b'. if the tape at index is blank, set the tape at index to blank, move the index right, then return 'q0b'.
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'c':
            self.tape[self.index] = 'c'
            self.index += self.L
            return 'q5b'

        elif self.tape[self.index] == '0':
            self.tape[self.index] = '0'
            self.index += self.L
            return 'q5b'

        elif self.tape[self.index] == 'x':
            self.tape[self.index] = 'x'
            self.index += self.L
            return 'q5b'

        elif self.tape[self.index] == self.blank:
            self.tape[self.index] = self.blank
            self.index += self.R
            return 'q0b'

    def state_q6b(self):
        """
        this method checks the tape at the current index. if it is a 'x', set the tape at the index to blank, move the
        index left, then returns 'q6b'. if the tape at index is 'c', set the tape at index to blank, move the index left,
        then return 'q6b'. if the tape at index is '0', set the tape at index to blank, move the index left, then return
        'q6b'. if the tape at index is blank, set the tape at index to blank, move the index right, then return 'q7b'.
        :return: the state which to go to next
        """
        if self.tape[self.index] == 'x':
            self.tape[self.index] = self.blank
            self.index += self.L
            return 'q6b'

        elif self.tape[self.index] == 'c':
            self.tape[self.index] = self.blank
            self.index += self.L
            return 'q6b'

        elif self.tape[self.index] == '0':
            self.tape[self.index] = self.blank
            self.index += self.L
            return 'q6b'

        elif self.tape[self.index] == self.blank:
            self.tape[self.index] = self.blank
            self.index += self.R
            return 'q7b'

    def state_q7b(self):
        """
        this method checks the tape at the current index. if it is a blank, set the tape at the index to blank, move the
        index right, then returns 'q7b'. if the tape at index is '0', set the tape at index to '0', move the index left,
        then return 'q8b'.
        :return: the state which to go to next
        """
        if self.tape[self.index] == self.blank:
            self.tape[self.index] = self.blank
            self.index += self.R
            return 'q7b'

        elif self.tape[self.index] == '0':
            self.tape[self.index] = '0'
            self.index += self.L
            return 'q8b'

    def state_q8b(self):
        """
        this method formats the result of the division machine. it strips off the leading and trailing blanks, then
        uses all the '0's on the left side of the center blanks for the remainder portion of the answer and then uses
        all the '0's on the right side of the center blanks for the quotient portion of the answer. lastly it returns
        the formatted answer string
        :return: the answer
        """
        # strip off leading blanks
        self.index = 0
        while self.tape[self.index] == self.blank:
            self.tape = self.tape[1:]

        # strip trailing blanks
        self.index = -1
        while self.tape[self.index] == self.blank:
            self.tape = self.tape[:-1]

        # get quotient
        quotient = 'Q = '
        while len(self.tape) > 0 and self.tape[self.index] != self.blank:
            quotient += self.tape[self.index]
            self.tape = self.tape[:-1]

        # get remainder
        self.index = 0
        remainder = ', R = '
        while len(self.tape) > 0 and self.tape[self.index] != self.blank:
            remainder += self.tape[self.index]
            self.tape = self.tape[1:]

        return "'" + quotient + remainder + "'"
