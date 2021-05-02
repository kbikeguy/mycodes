from StringAcceptorTM import StringAcceptor
from TransducerTM import Transducer
from ComplexTM import Complex

"""
this file controls the user interface of the program. it contains methods to display the menu and accept user input,
and methods to direct each of the menu selections.
"""


def leave():
    """
    this method displays the exiting program message and returns the signal to exit
    :return: 'q'
    """
    print("Thanks for playing")
    return 'q'


def complicatedTM():
    """
    this method handles the choice of a complicated turing machine operation. it constructs an object of the Complex
    class and calls the class menu. if a '1' is returned and the input for unary multiplication is valid, then the
    unary multiplication machine is run. if a '2' is returned and the input for unary division is valid, then the
    machine for unary division is run. then this method returns 'y'
    :return: 'y'
    """
    compex = Complex()
    choice = compex.menu()

    # if unary multiplication was selected
    if choice == '1' and compex.setInput1():
        compex.run()

    # if unary division was selected
    elif choice == '2' and compex.setInput2():
        compex.run()
    return 'y'


def transducerTM():
    """
    this method handles the choice of a transducer turing machine operation. it constructs an object of the Transducer
    class and calls the class menu. if a '1' is returned and the input for unary addition is valid, then the
    unary addition machine is run. if a '2' is returned and the input for binary addition is valid, then the
    machine for binary addition is run. then this method returns 'y'
    :return: 'y'
    """
    trans = Transducer()
    choice = trans.menu()

    # if unary addition was selected
    if choice == '1' and trans.setInput1():
        trans.run()

    # if binary number was chosen
    elif choice == '2' and trans.setInput2():
        trans.run()

    return 'y'


def stringAcceptorTM():
    """
    this method handles the choice of a String Acceptor turing machine operation. it constructs an object of the
    StringAcceptor class and calls the class menu. if a '1' is returned then the a^nb^nc^n machine is run. if a '2' is
    returned and the input for ww^R is valid, then the machine for ww^R is run. then this method returns 'y'
    :return: 'y'
    """
    SA = StringAcceptor()
    choice = SA.menu()

    # if a^nb^nc^n was selected
    if choice == '1':
        SA.setInput1()
        SA.runSelection1()

    # if ww^R was selected
    elif choice == '2' and SA.setInput2():
        SA.runSelection2()

    return 'y'


def menu():
    """
    this method displays the menu for the program. selecting option 1 will select the Language Acceptor Machine,
    option 2 will select Transducer Machine, option 3 will select the Complex Machine, and option 4 will end the
    program.
    :return: the selected menu option
    """
    msg = "Please make a selection of '1', '2', '3', or '4' below\n"
    msg += "1. Turing Language Acceptor Machine:\n"
    msg += "2. Turing Unary and Binary Adder Machine:\n"
    msg += "3. Turing Unary Multiplier and Divider Machine:\n"
    msg += "4. Quit:\n"
    msg += "Selection: "
    return msg


def main():
    """
    this is the main program method. it builds the dictionary of function calls for this file and runs the program
    loop.
    :return:
    """
    handlers = {'1': stringAcceptorTM, '2': transducerTM, '3': complicatedTM, '4': leave}
    run = 'y'

    while run == 'y':
        selection = input(menu()).lower().strip()
        while selection not in "1234":
            selection = input(menu()).lower().strip()

        handler = handlers[selection]
        run = handler()


if __name__ == '__main__':
    main()
