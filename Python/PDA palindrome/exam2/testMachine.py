from StateMachine import StateMachine
from Stack import Stack

# from exam2.StateMachine import StateMachine
# from exam2.Stack import Stack

stack = Stack()
alphabet = list()
length = 0
firstElement = 'Z0'


def q1_state_transitions(txt):
    """
    this method attempts the initial transition from the start state to q2. it takes in the whole input string and
    checks the first symbol against the alphabet of the language. if the symbol is found in the alphabet, the new
    state to transition to is set to 'q2' and the first element symbol is pushed onto the stack, else it is set
    to 'error_state' which is the dead state. finally the method returns the name of the new state and the input string.
    :param txt: the input string
    :return: the new state, and the input string
    """
    if txt != '' and txt[0] in alphabet:
        newState = "q2"
        stack.push(firstElement)
    else:
        newState = "error_state"
    return newState, txt


def q2_state_transitions(txt):
    """
    this method attempts the transition from the q2 state to the next state. it takes in the input string and
    checks if the string has been read in half way yet. if it has, it sets the next state to 'q3' and returns the name
    of the next state and the input text. else, it checks the first symbol to see if it's in the alphabet. if it is,
    the new state to transition to is set to 'q2' and the symbol is pushed onto the stack if it needs to be. if it is
    not in the alphabet, the new transition state is set to 'error_state which is the dead state. finally the method
    returns the name of the new state and the input string minus its first symbol.
    :param txt: the input string
    :return: the name of the new state, the input string minus the first symbol
    """

    # if we are halfway through the input
    if len(txt) == length // 2 or (length % 2 and len(txt) == length // 2 - 1):
        newState = 'q3'
        return newState, txt

    # else there is more to read in
    elif txt[0] in alphabet:
        newState = "q2"
        if shouldPush(len(txt)):
            stack.push(txt[0])

    else:
        newState = "error_state"

    return newState, txt[1:]


def q3_state_transitions(txt):
    """
        this method attempts the transition from the q3 state to the next state. it takes in the input string and
        checks if the length of the string is 0. if it is, it sets the next state to 'q4' and
        returns the next state and the txt. else, it checks the first symbol to see if it's in the alphabet. if it is,
        the new state  is set to 'q3'. if it is not in the alphabet, the next state is set to 'error_state which is the
        dead state. finally the method returns the name of the new state and the input string minus its first symbol.
        :param txt: the input string
        :return: the name of the new state, the input string minus the first symbol
        """
    if len(txt) == 0:
        newState = 'q4'
        return newState, txt

    elif txt[0] in alphabet:
        newState = "q3"
        if txt[0] == stack.top():
            stack.pop()

    else:
        newState = "error_state"

    return newState, txt[1:]


def q4_state_transitions():
    """
    this method checks if the top element of the stack is the first element. if is is, a message is printed stating
    that the user input was a palindrome. if is not, a message prints stating that the user input was not a
    palindrome
    :return:
    """
    if stack.top() == firstElement:
        print("and user input was a palindrome")
    else:
        print("but user input was not a palindrome")


def shouldPush(index):
    """
    this method takes in the length of the string and checks it against the length of the original string. if the
    length of the string is an even number or if the index isn't the center of an odd string, it returns true.
    otherwise, it returns false
    :param index: the length of the string and current index
    :return: true or false
    """
    if length % 2 == 0:
        return True

    if index != length // 2 + 1:
        return True

    return False


def setAlphabet(alpha):
    """
    this method takes in the user input for what to construct the alphabet from and fills the alphabet
    list from it
    :param alpha: the user input
    :return:
    """
    for x in alpha:
        if x not in alphabet:
            alphabet.append(x)


def printLanguage():
    """
    this method prints out all of the information about the language the user input
    :return:
    """
    print("The language chosen shall be as follows")
    print("L = {ww^R | w = (", end='')
    for x in alphabet:
        if x == alphabet[-1]:
            print(x, end='')
        else:
            print("{}+".format(x), end='')

    print(")^*}\nInput must be a combination of 1 or more", end='')

    for x in alphabet:
        if x == alphabet[-1]:
            print(" and {}'s".format(x), end='')
        else:
            print(" {}'s,".format(x), end='')

    print()


if __name__ == "__main__":
    m = StateMachine()
    m.add_state("q1", q1_state_transitions)
    m.add_state("q2", q2_state_transitions)
    m.add_state("q3", q3_state_transitions, )
    m.add_state("q4", q4_state_transitions, final_state=1)
    m.add_state("error_state", None, end_state=1)
    m.set_start("q1")
    sigma = ''
    run = 'Y'

    print("Welcome, this is a simple PDA for a palindrome with the characteristics as follows:")

    while run == 'Y':
        alphabet.clear()
        setAlphabet(input("Enter symbols for the alphabet you wish to use, no duplicates: "))
        printLanguage()

        sigma = input('Enter the input string you would like to test: ').lower()

        length = len(sigma)
        m.run(sigma)
        run = input('Do you wish to continue (Y,N)? ').upper()
        while run != 'Y' and run != 'N':
            run = input('Invalid entry.\nDo you wish to continue (Y,N)? ').upper()
