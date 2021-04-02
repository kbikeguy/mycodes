from campbell_riley.Behavior import Behavior
from campbell_riley.Car import Car


class Block:
    """
    @name Block
    @author Riley Campbell
    this is the class for Block. it contains the methods for adding a car, constructing a block, printing a block,
    locating a car in block to print it, updating the left bound cars, and updating the right bound cars.
    """

    def addCars(self, carid, direction):
        """
        @name addCars
        @author Riley Campbell
        this is the function for adding a car to a block. the user will input a 0, 1, or 2 for the mood of the driver.
        if a 0 is input, the car will be given a slow driver. if a 1 is input, the car will be given a normal driver.
        if a 2 is input, the car will be given a fast driver. any other input and the function will end after displaying
        'invalid input'.
        @param carid: the id number of the car
        @param direction: the direction to face the car
        @return:
        """
        mood = int(input('Which type: 0-->slow, 1-->norm, 2-->fast: '))
        # GRADING: SET_BEHAVIOR
        if mood == 0:
            # GRADING: USE_BEHAVIOR
            self.rightFacingCars.append(
                Car(self.ohbehave.slow(), carid)) if direction == 0 else self.leftFacingCars.append(
                Car(self.ohbehave.slow(), carid))
        elif mood == 1:
            # GRADING: USE_BEHAVIOR
            self.rightFacingCars.append(
                Car(self.ohbehave.norm(), carid)) if direction == 0 else self.leftFacingCars.append(
                Car(self.ohbehave.norm(), carid))
        elif mood == 2:
            # GRADING: USE_BEHAVIOR
            self.rightFacingCars.append(
                Car(self.ohbehave.fast(), carid)) if direction == 0 else self.leftFacingCars.append(
                Car(self.ohbehave.fast(), carid))
        else:
            print('Invalid Option')
        return

    def getCarLocString(self):
        """
        @name getCarLocString
        @author Riley Campbell
        this function makes a string of the the length and speed of the Block
        @return: the string
        """
        return 'Block Length: ' + '{:.1f}'.format(self.length) + '\nBlock Speed: ' + str(self.speed)

    def __init__(self, ids, length, speed):
        """
        @name: __init__
        @author: Riley Campbell
        this is the constructor for the Block
        @param ids: the block id
        @param length: the length of the block
        @param speed: the speed of the block
        """
        self.ids = ids
        self.length = length
        self.speed = speed
        self.rightFacingCars = []
        self.leftFacingCars = []
        self.ohbehave = Behavior()

    # GRADING: INTER_CAR
    def __iter__(self):
        """
        @name: __iter__
        @author: Riley Campbell
        this is the constructor for the iterator of the Block
        @return: this instance of Block
        """
        self.index = 0
        return self

    def __next__(self):
        """
        @name: __next__
        @author: Riley Campbell
        this is the iterator for the Block class. it creates a list of the current left and right facing cars if there
        is at least one of them. in the event that only one car is available, None is returned in the list for the other
        other spot
        @return: the set of cars
        """
        if self.index < len(self.leftFacingCars) or self.index < len(self.rightFacingCars):
            cars = [None, None]
            if self.index < len(self.leftFacingCars):
                cars[1] = self.leftFacingCars[self.index]

            if self.index < len(self.rightFacingCars):
                cars[0] = self.rightFacingCars[self.index]

            self.index += 1
            return cars
        else:
            raise StopIteration

    def removal(self, lefts, rights):
        """
        @name: removal
        @author: Riley Campbell
        this is the removal function for a block. it takes in a lift of leftbound cars and a list of rightbound cars to
        remove from the block and iterates through the lists removing the cars from the block until the lists are empty
        @param lefts: the list of leftbound cars to remove
        @param rights: the list of rightbound cars to remove
        @return:
        """
        while len(lefts) > 0:
            self.leftFacingCars.remove(lefts.pop())
        while len(rights) > 0:
            self.rightFacingCars.remove(rights.pop())

    def __str__(self):
        """
        @name: __str__
        @author: Riley Campbell
        this is the str function for the block class. it creates a string of the number of left and right facing cars
        in the form of ' -#-> <-#-'
        @return: the string
        """
        ret = ' -' + str(len(self.rightFacingCars)) + '-> <-' + str(len(self.leftFacingCars)) + '-'
        return ret


