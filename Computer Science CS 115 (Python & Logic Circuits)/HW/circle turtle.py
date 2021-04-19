import turtle
def circle(length, sides):
    angle = 360/sides
    def recursiveStep(length,sides,count):
        if count == 0:
            return
        else:
            turtle.forward(length)
            turtle.left(angle)
            recursiveStep(length,sides,count-1)
    recursiveStep(length, sides, sides)

def koch(sideLen, order):
    if 0 == order or 3 > sideLen:
        turtle.forward(sideLen)
    else:
        koch(sideLen/3, order-1)
        turtle.left(60.0)

        koch(sideLen/3, order-1)
        turtle.right(180.0-60.0)

        koch(sideLen/3, order-1)
        turtle.left(60.0)

        koch(sideLen/3, order-1)


    
    
        
        
