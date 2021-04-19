import random

def listGen(num = 30, minimum = 0, maximum = 100):
    myList = []
    for i in range(int(num)):
        myList = myList + [random.randint(int(minimum), int(maximum))]
    return myList