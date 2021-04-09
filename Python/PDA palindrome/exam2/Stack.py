class Stack:
    """
    this class replicates the functionality of a stack. the methods include a push(), pop(), and top()
    """
    def __init__(self):
        """
        this is the constructor for Stack and initializes the member variable stack to an empty list
        """
        self.stack = []

    def push(self, val):
        """
        this method takes in a value and pushes it onto the stack
        :param val: the value to be pushed onto the stack
        :return:
        """
        self.stack.append(val)

    def pop(self):
        """
        this method removes the top item from the stack and returns it. if the stack is empty, it returns None
        :return: the top item or None
        """
        if len(self.stack) > 0:
            val = self.stack.pop()
            return val

        return None

    def top(self):
        """
        this method returns the item at the top of the stack. if the stack is empty, it returns None
        :return: the value at the top of the stack, or None
        """
        if len(self.stack) > 0:
            val = self.stack[-1]
            return val

        return None
