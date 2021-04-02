class Behavior:
    """
    @name Behavior
    @author Riley Campbell
    this is the behavior class for a driver. it contains the methods to modify mood of the driver by -5 mph, 0 mph,
    or 5 mph
    """

    # GRADING: AGGRESSIVE
    def fast(self):
        """
        @name fast
        @author Riley Campbell
        this function sets the strategy of the driver to 5 mph
        @return: the strategy of the driver
        """
        return 5

    # GRADING: NORM
    def norm(self):
        """
        @name norm
        @author Riley Campbell
        this function sets the strategy of the driver to 0 mph
        @return: the strategy of the driver
        """
        return 0

    # GRADING: NERVOUS
    def slow(self):
        """
        @name slow
        @author Riley Campbell
        this function sets the strategy of the driver to -5 mph
        @return: the strategy of the driver
        """
        return -5




