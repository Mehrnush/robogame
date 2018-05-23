import requests
import time
import sys

sys.path.append('../../robotcontroller')
import robot

robot_one = "192.168.43.159" # "192.168.0.102"
height_mountain = 46


def main():
    last_position = 0
    while True:
        projects_url = "https://todo.ly/api/projects.json"

        projects = requests.get(projects_url, auth=('jackob@gmx.de', 'demodemo')).json()
        project_id = projects[0]["Id"]
        print(str(projects))
        print(str(project_id))
        items_url = "https://todo.ly/api/projects/" + str(project_id) + "/items.json"
        itemsdone_url = "https://todo.ly/api/projects/" + str(project_id) + "/doneitems.json"
        items = requests.get(items_url, auth=('jackob@gmx.de', 'demodemo')).json()

        print(str(items))
        count_items = len(items)
        print(str(count_items))

        items_done = requests.get(itemsdone_url, auth=('jackob@gmx.de', 'demodemo')).json()
        count_itemsdone = len(items_done)
        print(str(count_itemsdone))

        controller = robot.Controller(robot_one)
        robot1 = robot.Robot(controller)

        items_total = count_items + count_itemsdone

        length_per_task = height_mountain/items_total

        new_position = count_itemsdone * length_per_task
        if new_position < last_position:
            robot1.backward(last_position - new_position)
        else:
            robot1.forward(new_position - last_position)

        time.sleep(5)
        last_position = new_position


def test():
    controller = robot.Controller(robot_one)
    robot1 = robot.Robot(controller)
    #robot1.forward(1)
    while True:
        robot1.forward(1)
        robot1.forward(1)
        robot1.forward(1)
        robot1.forward(1)
        robot1.forward(1)
    #while True:
        #robot1.backward(1)
        #robot1.backward(1)
        #robot1.backward(1)
        #robot1.backward(1)
        #robot1.backward(1)



def test2():
    requests.get("http://" + robot_one + "/left?params=10")


if __name__ == "__main__":
    main()
    #test()
    # test2()




