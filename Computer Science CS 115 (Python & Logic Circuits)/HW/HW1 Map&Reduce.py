tay
#  Maxwell Metzner
#
#  CS115-B/C HW1 ~ Applications of Map & Reduce
#
#  Due : Sep. 20th, 2019
#
#  I pledge my honor that I have abided by the Stevens Honor System

from functools import reduce
from math import factorial, sqrt

def taylorApprox(lastIter):
    iterated = list(range(lastIter+1)) #expands lastIter into list from 0 until lastIter
    def sum(x,y):
        return x + y
    def inverseFactorial(x):
        return 1/factorial(x)
    if reduce(sum,map(inverseFactorial,iterated))%1 != 0: #checks if it's an interger, gets rid of decimal if it is
        return reduce(sum,map(inverseFactorial,iterated))
    else:
        return (int)(reduce(sum,map(inverseFactorial,iterated)))
    

def vectorNorm(vect1):
    def sum(x,y):
        return x+y
    def square(x):
        return x**2
    def root(x):
        return x**(0.5)
    return root(reduce(sum,list(map(square,vect1)))) #squares all terms in vect1, adds them together, and then takes sqrt of that

def arithMean(vect1):
    def sum(x,y):
        return x + y
    length = len(vect1)
    return reduce(sum,vect1)/length #take sum of all terms of vect1 and divide by length
