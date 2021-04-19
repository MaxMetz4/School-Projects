#I, Max Metzner, pledge my honor that I have abided by the Stevens Honor System

import turtle

def svTree(trunkLength, depth):
    if depth < 1:
        return
    else:
        turtle.forward(trunkLength/2)
        turtle.left(20)
        svTree(trunkLength/2,depth-1)
        turtle.right(40)
        svTree(trunkLength/2, depth-1)
        turtle.left(20)
        turtle.backward(trunkLength/2)
