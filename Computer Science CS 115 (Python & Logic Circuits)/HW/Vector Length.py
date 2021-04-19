
import math

def vectorLen(L,P):
    
    deltaX = P[0]-L[0]
    deltaY = P[1]-L[1]

    return math.sqrt((deltaX * deltaX) + (deltaY * deltaY))
