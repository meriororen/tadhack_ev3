import os
from neb.plugins import Plugin

class EV3Plugin(Plugin):
    """Make the EV3 dance
    ev3 dance : make ev3 dance!
    ev3 go speed duration : go forward with speed (-100 -> 100) and duration (in second)
    ev3 turn direction : turn either direction (left, right, back)
    """
    name = "ev3"

    def __init__(self, *args, **kwargs):
        super(Plugin, self).__init__(*args, **kwargs)

    def cmd_dance(self, event):
        cmd = "ev3 dance"
        os.popen(cmd)

    def cmd_turn(self, event, direction):
        cmd = "ev3 turn %s" % direction
        os.popen(cmd)

    def cmd_go(self, event, speed, duration):
        cmd = "ev3 go %s %s" % (speed, duration)
        return cmd
        os.popen(cmd)
