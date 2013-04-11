import json

class Beacon(object):

    def __init__(self, redisclient):
        self.client = redisclient

    def publish(self, channel, dict_msg):
        self.client.publish(channel, json.dumps(dict_msg))

    def blue(self, dict_msg={}):
        self.publish('blue_beacon', dict_msg)

    def red(self, dict_msg={}):
        self.publish('red_beacon', dict_msg)

    def yellow(self, dict_msg={}):
        self.publish('yellow_beacon', dict_msg)
