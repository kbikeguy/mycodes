from campbell_riley.Block import Block
from campbell_riley.Light import Light
from campbell_riley.Street import Street


class Menu:
    """
    @name: Menu
    @author: Riley Campbell
    this is the menu selection class. it handles the function calls to show the cars, print the road, and update the
    street
    """

    """
    this is a static class member to make the car ID never reset during tier 1 through 10
    """
    mystreet = Street()

    def printRoad(self):
        """
        @name: printRoad
        @author: Riley Campbell
        this is the function to print out the street by calling the overwritten __str__ function inside of Street
        @return:
        """
        ret = ''
        # GRADING: LOOP_STREET
        for block in self.mystreet:
            ret += str(block)
        print('Entry::' + ret, '::Exit')

    def selection(self, choice):
        """
        @name: selection
        @author: Riley Campbell
        this is the switch case function to handle the user's input from the menu
        @param choice: the menu input selection
        @return:
        """

        if choice == 1:
            self.printRoad()

        elif choice == 2:
            self.mystreet.MakeRoad()

        elif choice == 3:
            self.mystreet.addcar()

        elif choice == 4:
            self.showCars()

        elif choice == 5:
            self.update()

        elif choice == 6:
            self.update()
            self.printRoad()
            self.showCars()

        elif choice == 0:
            # reset the original block just for testing
            self.mystreet.blocksandlights.clear()
            self.mystreet.blocksandlights.append(Block(0, 0.5, 30))
            self.mystreet.size = 1

        else:
            print("Invalid Option")

    def showCars(self):
        """
        @name: showCars
        @author: Riley Campbell
        this is the function for printing out the cars display. it works by iterating through the list of blocks
        and calling a function within each block to display its contents.
        @return:
        """

        for i, v in enumerate(self.mystreet):
            rights = 'Right: '
            lefts = 'Left:  '
            if type(v) is Block:
                print('_____Block', str(i >> 1) + '_____')
                print(v.getCarLocString())
                # GRADING: LOOP_CAR
                for cars in v:
                    if cars[0] is not None:
                        rights += str(cars[0])
                    if cars[1] is not None:
                        lefts += str(cars[1])
                print(lefts, '\n' + rights, end='\n\n')

    def update(self):
        """
        @name: update
        @author: Riley Campbell
        this is the function that handles the updating of the lights and the cars. first the lights are updated by
        iterating through Street. next the cars are updated by iterating through Street and in each block, iterating
        through all of the left and right bound cars. only one car is allowed to move out of a block once per update.
        in the event of a tie, the first cars to come to the end of a block will be the one to leave it
        @return:
        """
        # update the lights first
        lightOn = {}
        lefts = []
        rights = []
        for light in self.mystreet:
            if type(light) is Light:
                lightOn[self.mystreet.index - 1] = light.update()

        # update the right facing cars second
        # get list of blocks
        lastblock = None
        for block in self.mystreet:
            if type(block) is Block:
                moveableR = moveableL = True

                # get lists of cars
                for car in block:
                    # handle right facing facing cars
                    if car[0] is not None:

                        # try to move the car
                        if moveableR and car[0].location == block.length:

                            # see if its at the end of the street
                            if block.ids == self.mystreet.size - 1:
                                rights.append(car[0])
                                moveableR = False
                                # block.rightFacingCars.remove(car[0])

                            # see if you can move it to the next block
                            elif lightOn[block.ids + 1]:
                                car[0].location = 0
                                self.mystreet.movecar(car[0], block.ids, 'F')
                                rights.append(car[0])
                                moveableR = False
                                # block.rightFacingCars.remove(car[0])

                        # update location to at least the end of the current block
                        else:
                            car[0].update(block.speed, block.length)

                    # handle left facing cars
                    if car[1] is not None:

                        # try to move the car
                        if car[1].location == block.length and moveableL:

                            # see if its at the end of the street
                            if block.ids == 0:
                                lefts.append(car[1])
                                moveableL = False

                            # see if you can move it to the previous block
                            elif lightOn[block.ids - 1]:
                                car[1].location = (float(lastblock.speed) + car[1].speedMod) * (1 / 120)
                                self.mystreet.movecar(car[1], block.ids, 'B')
                                lefts.append(car[1])
                                moveableL = False

                        # update location to at least the end of the current block
                        else:
                            car[1].update(block.speed, block.length)

                block.removal(lefts, rights)
                lastblock = block
