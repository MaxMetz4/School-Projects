def myFactorial(x):
    '''return he facotrial of x which is a natural number'''
    if x == 0:
        return 1
    else:
        return x * myFactorial(x-1)

def altFactorial(x):
    return 1 if x== 0 else x * altFactorial(x-1)
    
def myLength(L):
    '''return the length of a L '''
    if L == []:
        return 0
    else:
        return 1 + myLength(L[1:])
