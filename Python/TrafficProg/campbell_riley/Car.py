class Car:
    """
    @name: Car
    @author Riley Campbell
    this is the class for the cars, it contains the functions for constructing a car, printing the car's information,
    and updating a car
    """

    def __init__(self, mood, carnum):
        """
        @name: __init__
        @author: Riley Campbell
        this is the constructor for a car.
        @param mood: the speed adjustment of the car
        @param carnum: the car ID
        """
        self.carid = carnum
        self.speedMod = mood
        self.location = 0

    def __str__(self):
        """
        @name: __str__
        @author: Riley Campbell
        this is the str function for Car. it creats a string of the car's id and location in the form of ID: Location
        @return: the string
        """
        cars = '{}: {:.2f}'.format(self.carid, self.location)
        return cars.ljust(15, ' ')

    def update(self, mph, length):
        """
        @name: update
        @author: Riley Campbell
        this is the update function for Car. it takes in speed of the block the car is in and its length then calculates
        how far it can travel in 30 seconds factoring in its speedMod offset. if the location it traveled to is greater
        than the length of the block, the car's location is set to the length of the block
        @param mph: the speed of the block
        @param length: the length of the block
        @return:
        """
        time = 1 / 120
        self.location += time * (float(mph) + self.speedMod)

        if self.location > length:
            self.location = length



