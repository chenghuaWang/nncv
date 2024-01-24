"""
Module: Auto Scheduler
"""

from ..vm import runner


class AutoScheduler():
    """
    The auto scheduler class.
    """

    def __init__(self) -> None:
        self._runner = runner.Runner()

    def schedule(self) -> None:
        """
        do schedule in schedule space
        """
        pass
