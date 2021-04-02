class Light:
    """
    @name: Light
    @author: Riley Campbell
    This is the class for Light, it contains the methods for initializing a light, updating a light,
    and printing a light
    """

    def update(self):
        """
        @name update
        @author Riley Campbell
        this is the update method for light. it subtracts 30 seconds off the remaining countdown time. if the
        countdown goes below 1 second, the light should cycle and any negative time is added to the next
        countdown. if the light state is turned on, the function returns True. if it is turned off, the function
        returns false.
        @return: the state of the light
        """
        time = 30
        self.countdown -= time
        if self.countdown <= 0:
            self.on *= -1
            self.countdown = self.cycle + self.countdown
        return self.on == 1

    def __init__(self, lightLength):
        """
        @name __init__
        @author Riley Campbell
        this is the constructor for light, it takes in the length of the cycle in minutes and converts it to seconds.
        then it sets the light to off initially
        @param lightLength: the length of the cycle in minutes
        """
        self.cycle = self.countdown = lightLength * 60
        self.on = -1

    def __str__(self):
        """
        @name __str__
        @author Riley Campbell
        this is the toString for the Light class. it checks to see if a light is on or off. If it is on, it returns the
        string, ' ::On::' and ' ::Off::' if the light is off
        @return: the state of the light
        """
        if self.on == 1:
            return ' ::On::'
        else:
            return ' ::Off::'
