def reverse(L):
    if not L:
        return []
    else:
        head, tail = L[0], L[1:]
        return reverse(tail) + [head]

def reverse2(L):
    baseVal = []
    def recursiveStep(head, tail):
        return reverse(tail) + [head]
    return baseVal if not L \
           else recursiveStep(L[0], L[1:])

def member(x,L):
    baseVal = False
    def recursiveStep(head, tail):
        return (x == head) or member(x, tail)
    return baseVal if not L \
           else recursiveStep(L[0], L[1:])

def member2(x,L):
    if x in L:
        return True
    else:
        return False
    
global z
z = 1

def fib(x):
    if z > x:
        return z
    else:
        return fib(z+z)

