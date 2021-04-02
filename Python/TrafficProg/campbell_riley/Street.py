from campbell_riley.Block import Block
from campbell_riley.Light import Light


class Street:
    """
    This is the class for Street. it contains the methods for adding a car, initiating the Street, iterating the Street,
    building a road, and printing the road
    """

    def addcar(self):
        """
        This function asks the user which end the the street they wish to add a car to in the form of 0-->left,
        and 1-->right. If an invalid input is given, the function returns without adding a car. If the input is
        valid, the current carID and the users input is passed into an addCar function contained in the first or
        last block depending on which end was selected. Then the carID is incremented by 1 for the next car
        :return:
        """
        direction = int(input('Which end: 0-->left, 1-->right: '))
        if direction == 0:
            self.blocksandlights[0].addCars(self.carid, direction)
        elif direction == 1:
            self.blocksandlights[-1].addCars(self.carid, direction)
        else:
            print('Invalid option')
            return

        self.carid += 1

    def __init__(self):
        """
        @name: __init__
        @author: Riley Campbell
        this is the constructor for Street. it sets up a list of blocks and sets the default street
        """
        self.blocksandlights = []
        self.index = None
        self.carid = 1
        self.blocksandlights.clear()
        self.blocksandlights.append(Block(0, 0.5, 30))
        self.size = 1

    # GRADING: INTER_STREET
    def __iter__(self):
        """
        @name: __iter__
        @author: Riley Campbell
        this is the iterator for street
        :return:
        """
        self.index = 0
        return self

    def __next__(self):
        """
        @name: __next__
        @author: Riley Campbell
        This is the Next function for the Street iterator. If the current index is less than the class list length,
        the indexed object is stored into x and then the index is incremented by 1 before returning x.
        Otherwise Stop Iteration is raised and the function returns nothing
        :return:    the object stored in x
        """
        if self.index < len(self.blocksandlights):
            x = self.blocksandlights[self.index]
            self.index += 1
            return x
        else:
            raise StopIteration

    def MakeRoad(self):
        """
        @name: MakeRoad
        @author: Riley Campbell
        This function makes a road based on user inputs. First the number of blocks is requested, then the road is
        constructed by iterating through the number of blocks and the user inputs information about each block.
        The user will input the length of the block in miles, the speed of the block in mph, and if it is not the final
        block of the street, the user is also asked for the light cycle time. If all the inputs are valid, the street
        is constructed, otherwise the function returns without building the street
        @return:
        """

        self.blocksandlights.clear()
        blocks = int(input('Number of blocks: '))
        i = 0
        for blockid in range(0, blocks):
            print('\n_____Block', str(blockid) + '_____')

            # get block length
            length = float(input('   Length of block in miles: '))
            if length < 0.5:
                print('A block must be at least 0.5 miles. Got:', length)
                return

            # get block speed
            speed = input('   Speed limit of block in mph: ')
            if not speed.isdigit() or int(speed) < 5:
                print('Speed limit must be at least 5 mph and a whole number. Got:', speed)
                return
            self.blocksandlights.append(Block(i, length, speed))
            i += 1

            # get block light cycle time
            if blockid < blocks - 1:
                cycle = float(input('   Length of cycle in minutes: '))
                if cycle < 0 or cycle % 0.5 != 0:
                    print('Light cycle must be positive and an increment of 0.5 min. Got:', cycle)
                    return
                # add a light
                self.blocksandlights.append(Light(cycle))
                i += 1
        self.size = len(self.blocksandlights)

    def movecar(self, car, index, direction):
        """
        @name: movecar
        @author: Riley Campbell
        this moves a car to an adjacent block. if its is a right facing car, it moves it to the block to in front of it.
        if it is a left facing car, it moves it to the block behind it.
        @param car: the car to be moved
        @param index: the current index of the car
        @param direction: the direction it needed to move
        @return:
        """

        # move a car forward
        if direction == 'F':
            self.blocksandlights[index + 2].rightFacingCars.append(car)
        # move a car backwards
        else:
            self.blocksandlights[index - 2].leftFacingCars.append(car)
