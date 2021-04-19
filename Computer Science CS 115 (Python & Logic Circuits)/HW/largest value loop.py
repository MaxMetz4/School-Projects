import listGen
def largest(x):
    num = -float('inf')
    counter = 0
    for i in range(len(x)):
        if (x[i] > num):
            num = x[i]
    for i in range(len(x)):
        if num == x[i]:
            return counter
        else:
            counter = counter + 1
