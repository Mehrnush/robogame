import requests



class Controller:

    def __init__(self, ip):
        self.ip = ip
        self.left = "http://" + ip + "/left?params="
        self.right = "http://" + ip + "/right?params="
        self.forward = "http://" + ip + "/forward?params="
        self.backward = "http://" + ip + "/backward?params="
        return

    def move_left(self, length):
        requests.get(self.left + str(length))

    def move_right(self, length):
        requests.get(self.right + str(length))

    def move_forward(self, length):
        requests.get(self.forward + str(length))

    def move_backward(self, length):
        requests.get(self.backward + str(length))


class Robot:

    def __init__(self, controller):
        self.position = 0
        self.controller = controller

    def left(self, length):
        self.controller.move_left(length)

    def right(self, length):
        self.controller.move_right(length)

    def forward(self, length):
        self.controller.move_forward(length)

    def backward(self, length):
        self.controller.move_backward(length)
