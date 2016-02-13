import os
from neb.plugins import Plugin

class EV3Plugin(Plugin):
    """Make the EV3 dance
    ev3 dance : make ev3 dance!
    """
    name = "ev3"

    def cmd_dance(self, event):
        cmd = "ev3 dance"
        os.popen(cmd)
