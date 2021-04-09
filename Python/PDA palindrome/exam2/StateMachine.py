
class StateMachine:
    """
    this class builds a state machine based off of the inputs from the user. the methods are the constructor,
    add_state(), set_state(), ad run()

    """
    def __init__(self):
        """
        this method is the constructor for StateMachine. if sets handlers to an empty dictionary, startState to None,
        endStates to an empty list, and finalStates to an empty list
        """
        self.handlers = {}
        self.startState = None
        self.endStates = []
        self.finalStates = []

    def add_state(self, name, handler, end_state=0, final_state=0):
        """
        This method takes in a state, the method that will handle the operations within the state, information about
        the state being an end state, and information about the state being a final state. the method will first change
        the name of the state to all uppercase. next if will insert the handler method into the handler dictionary with
        the key of the states name. if the state is an end state(end_state = 1), than the state will be appended to the
        endState list. if the state is a final state(final_state=1), than the state will be appended to the finalState
        list.
        :param name: the name of the state to be assigned as a key within the dictionary for the handler
        :param handler: the function that will handle the operation with the state
        :param end_state: a condition that will be 1 if name is an end state or 0 if it is not
        :param final_state: a condition that will be 1 if name is an final state or 0 if it is not
        :return:
        """
        name = name.upper()
        self.handlers[name] = handler
        if end_state:
            self.endStates.append(name)
        if final_state:
            self.finalStates.append(name)

    def set_start(self, name):
        """
        This method is a setter for startState
        :param name: the name to set startState to
        :return:
        """
        self.startState = name.upper()

    def run(self, cargo):
        """
        this method takes in the input string and controls the process of moving through the
        PDA by assigning functions calls based on the outputs of the previous function calls. these function
        calls are all previously stored within the dictionary of function calls where the keys are the states
        to transition to. if the return from a function is an "end state", the process ends and outputs a message
        of which state it is in and that the string has been rejected. if the return from a function is a "final state",
        the process ends and outputs that the message has been accepted. next it will check if the input was a
        palindrome or not by calling the final state method. this method will continue looping through the states
        until either a final state or an end state is reached.
        :param cargo:
        :return:
        """
        try:
            handler = self.handlers[self.startState]
        except Exception:
            raise InitializationError("must call .set_start() before .run()")
        if not self.endStates:
            raise InitializationError("at least one state must be an end_state")
        if not self.finalStates:
            raise InitializationError("at least one state must be a final_state")
        while True:
            (newState, cargo) = handler(cargo)
            if newState.upper() in self.finalStates:
                print("reached", newState, "a final State ", end='')
                self.handlers[newState.upper()]()
                break
            elif newState.upper() in self.endStates:
                print("reached", newState, "a non-final State")
                break
            else:
                handler = self.handlers[newState.upper()]
